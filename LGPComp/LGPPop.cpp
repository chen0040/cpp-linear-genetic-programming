#include "LGPPop.h"
#include <sstream>
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPUtil/LGPRandom.h"
#include <iostream>

LGPPop::LGPPop(LGPConfig* lgpConfig)
: m_lgpConfig(lgpConfig)
, m_iCurrentGeneration(0)
, m_bSetup(false)
, m_lgpMutationInstructionFactory(NULL)
, m_lgpCrossoverInstructionFactory(NULL)
, m_lgpPopInitInstructionFactory(NULL)
, m_lgpReproductionSelectionInstructionFactory(NULL)
, m_lgpRegInitInstructionFactory(NULL)
, m_lgpSurvivalInstructionFactory(NULL)
, m_global_fittest_program(NULL)
{
	
}

void LGPPop::Setup()
{
	if(m_bSetup==false)
	{
		m_env=this->CreateEnvironment(this->GetConfig());
		m_lgpMutationInstructionFactory=this->CreateMutationInstructionFactory(m_lgpConfig->GetScript("LGPMutationInstructionFactory").c_str());
		m_lgpCrossoverInstructionFactory=this->CreateCrossoverInstructionFactory(m_lgpConfig->GetScript("LGPCrossoverInstructionFactory").c_str());
		m_lgpPopInitInstructionFactory=this->CreatePopInitInstructionFactory(m_lgpConfig->GetScript("LGPPopInitInstructionFactory").c_str());
		m_lgpReproductionSelectionInstructionFactory=this->CreateReproductionSelectionInstructionFactory(m_lgpConfig->GetScript("LGPReproductionSelectionInstructionFactory").c_str());
		m_lgpRegInitInstructionFactory=this->CreateRegInitInstructionFactory(m_lgpConfig->GetScript("LGPRegInitInstructionFactory").c_str());
		m_lgpSurvivalInstructionFactory=this->CreateSurvivalInstructionFactory(m_lgpConfig->GetScript("LGPSurvivalInstructionFactory").c_str());
		m_bSetup=true;
	}
}

LGPSurvivalInstructionFactory* LGPPop::CreateSurvivalInstructionFactory(const char* filename)
{
	return new LGPSurvivalInstructionFactory(filename);
}

LGPRegInitInstructionFactory* LGPPop::CreateRegInitInstructionFactory(const char* filename)
{
	return new LGPRegInitInstructionFactory(filename);
}

void LGPPop::InitializeProgramRegisters(LGPProgram* lgp, const LGPFitnessCase* fitness_case)
{
	m_lgpRegInitInstructionFactory->InitializeRegisters(lgp->GetRegisterSet(), lgp->GetConstantSet(), fitness_case);
}

void LGPPop::Replace(LGPProgram* program_to_be_replaced, LGPProgram* program_to_replace)
{
	std::replace(m_programs.begin(), m_programs.end(), program_to_be_replaced, program_to_replace);
}

LGPMutationInstructionFactory* LGPPop::CreateMutationInstructionFactory(const char* filename)
{
	return new LGPMutationInstructionFactory(filename);
}

LGPCrossoverInstructionFactory* LGPPop::CreateCrossoverInstructionFactory(const char* filename)
{
	return new LGPCrossoverInstructionFactory(filename);
}

LGPPopInitInstructionFactory* LGPPop::CreatePopInitInstructionFactory(const char* filename)
{
	return new LGPPopInitInstructionFactory(filename);
}

LGPSelectionInstructionFactory* LGPPop::CreateReproductionSelectionInstructionFactory(const char *filename)
{
	return new LGPSelectionInstructionFactory(filename);
}

LGPPop::~LGPPop()
{
	if(m_env != NULL)
	{
		delete m_env;
		m_env=NULL;
	}

	std::vector<LGPProgram*>::iterator pos_prog;
	for(pos_prog=m_programs.begin(); pos_prog != m_programs.end(); ++pos_prog)
	{
		delete (*pos_prog);
	}
	m_programs.clear();

	if(m_lgpMutationInstructionFactory != NULL)
	{
		delete m_lgpMutationInstructionFactory;
		m_lgpMutationInstructionFactory=NULL;
	}
	if(m_lgpPopInitInstructionFactory != NULL)
	{
		delete m_lgpPopInitInstructionFactory;
		m_lgpPopInitInstructionFactory=NULL;
	}
	if(m_lgpCrossoverInstructionFactory != NULL)
	{
		delete m_lgpCrossoverInstructionFactory;
		m_lgpCrossoverInstructionFactory=NULL;
	}
	if(m_lgpReproductionSelectionInstructionFactory != NULL)
	{
		delete m_lgpReproductionSelectionInstructionFactory;
		m_lgpReproductionSelectionInstructionFactory=NULL;
	}
	if(m_lgpRegInitInstructionFactory != NULL)
	{
		delete m_lgpRegInitInstructionFactory;
		m_lgpRegInitInstructionFactory=NULL;
	}
	if(m_lgpSurvivalInstructionFactory != NULL)
	{
		delete m_lgpSurvivalInstructionFactory;
		m_lgpSurvivalInstructionFactory=NULL;
	}

	if(m_global_fittest_program != NULL)
	{
		delete m_global_fittest_program;
		m_global_fittest_program=NULL;
	}
}

void LGPPop::EvaluateFitness()
{
	for(size_t i=0; i<m_programs.size(); i++)
	{
		if(! m_programs[i]->HasValidFitness())
		{
			m_programs[i]->EvaluateFitness();
		}
	}
}

bool LGPPop::Terminated() const
{
	return m_iCurrentGeneration >= m_lgpConfig->GetMaxGenerations(); 
}

void LGPPop::Evolve()
{
	// m_lgpStats->Update();

	unsigned int iPopSize=this->m_lgpConfig->GetPopulationSize();
	unsigned int program_count=0;
	while(program_count < iPopSize)
	{
		std::pair<LGPProgram*, LGPProgram*> tournament_winners;
		std::pair<LGPProgram*, LGPProgram*> tournament_losers;
		m_lgpReproductionSelectionInstructionFactory->Select(this, tournament_winners, tournament_losers);
		
		LGPProgram* tp1=tournament_winners.first->Clone();
		LGPProgram* tp2=tournament_winners.second->Clone();

		double r=lgpRandom.nextDouble();
		if(r < this->m_lgpConfig->GetCrossoverRate())
		{
			m_lgpCrossoverInstructionFactory->Crossover(this, tp1, tp2);
		}

		r=lgpRandom.nextDouble();
		if(r < this->m_lgpConfig->GetMacroMutationRate())
		{
			m_lgpMutationInstructionFactory->Mutate(this, tp1);
		}

		r=lgpRandom.nextDouble();
		if(r < this->m_lgpConfig->GetMacroMutationRate())
		{
			m_lgpMutationInstructionFactory->Mutate(this, tp2);
		}

		r=lgpRandom.nextDouble();
		if(r < this->m_lgpConfig->GetMicroMutationRate())
		{
			tp1->MicroMutate();
		}
		
		r=lgpRandom.nextDouble();
		if(r < this->m_lgpConfig->GetMicroMutationRate())
		{
			tp2->MicroMutate();
		}

		if(! tp1->HasValidFitness())
		{
			tp1->EvaluateFitness();
		}
		if(! tp2->HasValidFitness())
		{
			tp2->EvaluateFitness();
		}

		if(tp1->IsBetterThan(tp2))
		{
			if(tp1->IsBetterThan(m_global_fittest_program))
			{
				delete m_global_fittest_program;
				m_global_fittest_program=tp1->Clone();
			}
		}
		else
		{
			if(tp2->IsBetterThan(m_global_fittest_program))
			{
				delete m_global_fittest_program;
				m_global_fittest_program=tp2->Clone();
			}
		}

		LGPProgram* loser1=m_lgpSurvivalInstructionFactory->Compete(this, tournament_losers.first, tp1); // this method returns the pointer to the loser in the competition for survival;
		LGPProgram* loser2=m_lgpSurvivalInstructionFactory->Compete(this, tournament_losers.second, tp2);

		if(loser1==tournament_losers.first)
		{
			++program_count;
		}
		if(loser2==tournament_losers.second)
		{
			++program_count;
		}

		delete loser1;
		delete loser2;

		loser1=NULL;
		loser2=NULL;
	}

	m_iCurrentGeneration++;
}

void LGPPop::SortFittestProgramFirst()
{
	std::sort(m_programs.begin(), m_programs.end(), LGPProgramSort_FittestFirst());
}

void LGPPop::SortFittestProgramLast()
{
	std::sort(m_programs.begin(), m_programs.end(), LGPProgramSort_FittestLast());
}

LGPProgram* LGPPop::GetFittestProgram()
{
	SortFittestProgramFirst();
	return m_programs[0];
}

void LGPPop::BreedInitialPopulation()
{
	Setup();

	unsigned int iPopulationSize=m_lgpConfig->GetPopulationSize();
	m_programs.reserve(iPopulationSize);

	m_lgpPopInitInstructionFactory->Initialize(this);

	this->EvaluateFitness();

#ifdef LGP_DEBUG
	if(m_global_fittest_program != NULL)
	{
		LGPExitSystem("LGPPop::BreedInitialPopulation()", "m_global_fittest_program != NULL");
	}
#endif

	m_global_fittest_program=this->GetFittestProgram()->Clone();
}

const LGPProgram* LGPPop::GetGlobalFittestProgram() const
{
#ifdef LGP_DEBUG
	if(m_global_fittest_program==NULL)
	{
		LGPExitSystem("LGPPop::GetGlobalFittestProgram() const", "m_global_fittest_program==NULL");
	}
#endif
	return m_global_fittest_program;
}

std::string LGPPop::ToString(bool effective_only) const
{
	if(m_bSetup==false)
	{
		LGPExitSystem("LGPPop::ToString() const", "LGPPop object must be set up properly before the function call");
	}

	std::ostringstream oss;

	oss << "register initialization instruction: " << std::endl;
	oss << m_lgpRegInitInstructionFactory->ToString() << std::endl;
	oss << "pop init instruction: " << std::endl;
	oss << m_lgpPopInitInstructionFactory->ToString() << std::endl;
	oss << "macro mutation instruction: " << std::endl;
	oss << m_lgpMutationInstructionFactory->ToString() << std::endl;
	oss << "crossover instruction: " << std::endl;
	oss << m_lgpCrossoverInstructionFactory->ToString() << std::endl;
	oss << "reproduction seletion instruction: " << std::endl;
	oss << m_lgpReproductionSelectionInstructionFactory->ToString() << std::endl;
	oss << "survival instruction: " << std::endl;
	oss << m_lgpSurvivalInstructionFactory->ToString() << std::endl;

	for(unsigned int i=0; i<m_programs.size(); i++)
	{
		oss << "Program[" << i << "]\n";
		oss << m_programs[i]->ToString(effective_only) << std::endl;
		//oss << "Program[" << i << "]: " << m_programs[i]->GetFitness() << std::endl;
	}

	return oss.str();
}