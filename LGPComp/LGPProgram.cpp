#include "LGPProgram.h"
#include "../LGPUtil/LGPRandom.h"
#include <sstream>
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "LGPPop.h"
#include <iomanip>
#include <iostream>

LGPProgram::LGPProgram(LGPPop * lgpPop)
: m_parent(lgpPop)
, m_dFitness(0)
, m_bFitnessValid(false)
, m_bSetup(false)
{

}

LGPProgram::~LGPProgram()
{	
	EraseInstructions();

	if(m_operator_set != NULL)
	{
		delete m_operator_set;
		m_operator_set = NULL;
	}

	if(m_register_set != NULL)
	{
		delete m_register_set;
		m_register_set = NULL;
	}

	if(m_constant_set != NULL)
	{
		delete m_constant_set;
		m_constant_set=NULL;
	}
}

const LGPConfig* LGPProgram::GetConfig() const
{
	return this->m_parent->GetConfig(); 
}

void LGPProgram::EvaluateFitness()
{
	this->MarkStructuralIntrons();

	LGPEnvironment* env=m_parent->GetEnvironment();
	unsigned int iFitnessCaseCount=env->GetFitnessCaseCount();
	std::vector<LGPFitnessCase*> cases;
	for(unsigned int i=0; i<iFitnessCaseCount; i++)
	{
		LGPFitnessCase* fitness_case=env->CreateFitnessCase(i);
		m_parent->InitializeProgramRegisters(this, fitness_case);
		this->EvaluateFitnessCase(fitness_case);
		cases.push_back(fitness_case);
	}

	m_objective_value=EvaluateFitness(cases);
	if(this->GetConfig()->IsMaximization())
	{
		m_dFitness=m_objective_value;
	}
	else
	{
		m_dFitness=-m_objective_value;
	}

	for(unsigned int i=0; i<iFitnessCaseCount;  i++)
	{
		delete cases[i];
	}

	m_bFitnessValid=true;
}

void LGPProgram::EraseInstructions()
{
	for(size_t i=0; i<m_instructions.size(); i++)
	{
		delete m_instructions[i];
	}
	m_instructions.clear();
}

unsigned int LGPProgram::GetEffectiveInstructionCount() const
{
#ifdef LGP_DEBUG
	if(!m_bFitnessValid)
	{
		LGPExitSystem("LGPProgram::GetEffectiveInstructionCount() const", "Fitness not valid implying introns are not marked correctly at the current stage\nPlease call MarkedStructuralIntrons() first before calling this function");
	}
#endif

	std::vector<LGPInstruction*>::const_iterator pos_instruction;
	unsigned int count=0;
	for(pos_instruction=m_instructions.begin(); pos_instruction != m_instructions.end(); ++pos_instruction)
	{
		if(!(*pos_instruction)->IsStructuralIntron())
		{
			count++;
		}
	}
	return count;
}

LGPProgram::LGPProgram(const LGPProgram& rhs)
{
	m_bSetup=rhs.m_bSetup;
	m_dFitness=rhs.m_dFitness;
	m_objective_value=rhs.m_objective_value;
	m_bFitnessValid=rhs.m_bFitnessValid;

	m_register_set=rhs.m_register_set->Clone();
	m_operator_set=rhs.m_operator_set->Clone();
	m_constant_set=rhs.m_constant_set->Clone();

	m_parent=rhs.m_parent;

	m_instructions.reserve(rhs.m_instructions.size());

	for(size_t i=0; i<rhs.m_instructions.size(); i++)
	{
		m_instructions.push_back(rhs.m_instructions[i]->Clone());
		m_instructions[i]->SetOwnership(this);
	}
}

std::string LGPProgram::ToString(bool effective_only) const
{
	std::ostringstream oss;

	for(size_t i=0; i<m_instructions.size(); i++)
	{
		if(effective_only)
		{
			if(!m_instructions[i]->IsStructuralIntron())
			{
				oss << "instruction[" << std::setw(2) << std::setfill('0')  << i << "]: " << m_instructions[i]->ToString() << std::endl;
			}
		}
		else
		{
			oss << "instruction[" << std::setw(2) << std::setfill('0')  << i << "]: " << m_instructions[i]->ToString() << std::endl;
		}
	}

	if(m_bFitnessValid)
	{
		oss << "objective_value: " << m_objective_value << std::endl;
		oss << "fitness: " << m_dFitness << std::endl;
	}
	else
	{
		oss << "Invalid Fitness" << std::endl;
	}

	return oss.str();
}

void LGPProgram::EvaluateFitnessCase(LGPFitnessCase* lgpFitnessCase)
{
	std::vector<LGPInstruction*>::iterator pos_instruction;
	int command=LGP_EXECUTE_NEXT_INSTRUCTION;
	LGPInstruction* current_effective_instruction=NULL;
	LGPInstruction* prev_effective_instruction=NULL;
	for(pos_instruction=m_instructions.begin(); pos_instruction != m_instructions.end(); ++pos_instruction)
	{
		if((*pos_instruction)->IsStructuralIntron())
		{
			continue;
		}
		prev_effective_instruction=current_effective_instruction;
		current_effective_instruction=*pos_instruction;
		if(command==LGP_EXECUTE_NEXT_INSTRUCTION)
		{
			command=current_effective_instruction->Execute(lgpFitnessCase);
			(*pos_instruction)->UpdateFitnessCase(lgpFitnessCase);
		}
		else
		{
			// Xianshun says:
			// as suggested in Linear Genetic Programming
			// the condictional construct is restricted to single condictional construct
			// an example of single conditional construct would be
			// line 1: if(register[a])
			// line 2: <action1>
			// line 3: <action2>
			// if register[a]==true, then <action1> and <action2> are executed
			// if register[a]==false, then <action1> is skipped and <action2> is executed
			// <action1> and <action2> are restricted to effective instruction
#ifdef LGP_DEBUG
			if(prev_effective_instruction == NULL)
			{
				LGPExitSystem("LGPProgram::Execute()", "prev_effective_instruction == NULL");
			}
#endif
			if(prev_effective_instruction->IsConditionalConstruct())
			{
				command=LGP_EXECUTE_NEXT_INSTRUCTION;	
			}
		}
	}
	
	lgpFitnessCase->Update(this->m_register_set);
}

void LGPProgram::MarkStructuralIntrons(unsigned int stop_point, std::set<unsigned int>& Reff)
{
	 /*
	Source: Brameier, M 2004  On Linear Genetic Programming (thesis)

	Algorithm 3.1 (detection of structural introns)
	1. Let set R_eff always contain all registers that are effective at the current program
	   position. R_eff := { r | r is output register }.
	   Start at the last program instruction and move backwards.
	2. Mark the next preceding operation in program with:
		destination register r_dest element-of R_eff.
	   If such an instruction is not found then go to 5.
	3. If the operation directly follows a branch or a sequence of branches then mark these
	   instructions too. Otherwise remove r_dest from R_eff .
	4. Insert each source (operand) register r_op of newly marked instructions in R_eff
	   if not already contained. Go to 2.
	5. Stop. All unmarked instructions are introns.
	*/

	// Xianshun says:
	// this is a variant of Algorithm 3.1 that run Algorithm 3.1 until stop_point and return the Reff at that stage

	unsigned int instruction_count=static_cast<unsigned int>(m_instructions.size());

#ifdef LGP_DEBUG
	if(instruction_count ==  0)
	{
		LGPExitSystem("LGPProgram::MarkStructuralIntrons(unsigned int stop_point, std::set<unsigned int>& Reff)", "instruction_count ==  0");
	}
#endif

	for(unsigned int i=instruction_count-1; i > stop_point; i--)
	{
		m_instructions[i]->SetStructuralIntronFlag(true);
	}

	Reff.clear();
	unsigned int iNumRegisters=m_parent->GetConfig()->GetNumRegisters();
	for(unsigned int i=0; i < iNumRegisters; ++i)
	{
		Reff.insert(i);
	}

	LGPInstruction* current_instruction=NULL;
	LGPInstruction* prev_instruction=NULL; // prev_instruction is the last visited instruction from bottom up of the program 
	for(unsigned int i=instruction_count - 1; i > stop_point; i--)
	{
		prev_instruction=current_instruction;
		current_instruction=m_instructions[i];
		// prev_instruction is not an structural intron and the current_instruction
		// is a condictional construct then, the current_instruction is not structural intron either
		// this directly follows from Step 3 of Algorithm 3.1
		if(current_instruction->IsConditionalConstruct() && prev_instruction != NULL)
		{
			if(!prev_instruction->IsStructuralIntron())
			{
				current_instruction->SetStructuralIntronFlag(false);
			}
		}
		else
		{
			if(Reff.find(current_instruction->GetDestinationRegisterIndex()) != Reff.end())
			{
				current_instruction->SetStructuralIntronFlag(false);
				Reff.erase(current_instruction->GetDestinationRegisterIndex());

				if(!current_instruction->IsOperand1ConstantRegister())
				{
					Reff.insert(current_instruction->GetOperand1RegisterIndex());
				}
				if(!current_instruction->IsOperand2ConstantRegister())
				{
					Reff.insert(current_instruction->GetOperand2RegisterIndex());
				}
			}
		}
	}
}

void LGPProgram::MarkStructuralIntrons()
{
	 /*
	Source: Brameier, M 2004  On Linear Genetic Programming (thesis)

	Algorithm 3.1 (detection of structural introns)
	1. Let set R_eff always contain all registers that are effective at the current program
	   position. R_eff := { r | r is output register }.
	   Start at the last program instruction and move backwards.
	2. Mark the next preceding operation in program with:
		destination register r_dest element-of R_eff.
	   If such an instruction is not found then go to 5.
	3. If the operation directly follows a branch or a sequence of branches then mark these
	   instructions too. Otherwise remove r_dest from R_eff .
	4. Insert each source (operand) register r_op of newly marked instructions in R_eff
	   if not already contained. Go to 2.
	5. Stop. All unmarked instructions are introns.
	*/

	std::vector<LGPInstruction*>::reverse_iterator ri;
	for(ri=m_instructions.rbegin(); ri !=m_instructions.rend(); ++ri)
	{
		(*ri)->SetStructuralIntronFlag(true);
	}

	std::set<unsigned int> Reff;
	unsigned int iNumRegisters=m_parent->GetConfig()->GetNumRegisters();
	for(unsigned int i=0; i < iNumRegisters; ++i)
	{
		Reff.insert(i);
	}

	LGPInstruction* current_instruction=NULL;
	LGPInstruction* prev_instruction=NULL; // prev_instruction is the last visited instruction from bottom up of the program 
	for(ri=m_instructions.rbegin(); ri != m_instructions.rend(); ++ri)
	{
		prev_instruction=current_instruction;
		current_instruction=*ri;
		// prev_instruction is not an structural intron and the current_instruction
		// is a condictional construct then, the current_instruction is not structural intron either
		// this directly follows from Step 3 of Algorithm 3.1
		if(current_instruction->IsConditionalConstruct() && prev_instruction != NULL)
		{
			if(!prev_instruction->IsStructuralIntron())
			{
				current_instruction->SetStructuralIntronFlag(false);
			}
		}
		else
		{
			if(Reff.find(current_instruction->GetDestinationRegisterIndex()) != Reff.end())
			{
				current_instruction->SetStructuralIntronFlag(false);
				Reff.erase(current_instruction->GetDestinationRegisterIndex());

				if(!current_instruction->IsOperand1ConstantRegister())
				{
					Reff.insert(current_instruction->GetOperand1RegisterIndex());
				}
				if(!current_instruction->IsOperand2ConstantRegister())
				{
					Reff.insert(current_instruction->GetOperand2RegisterIndex());
				}
			}
		}
	}
}

void LGPProgram::Create(unsigned int size)
{
	if(m_bSetup==false)
	{
		this->Setup();
	}

	// Xianshun says:
	// In this method, the instruction created is not garanteed to be structurally effective
	for(unsigned int i=0; i<size; i++)
	{
		LGPInstruction* lgp_instruction=new LGPInstruction(this);
		lgp_instruction->Create();
		m_instructions.push_back(lgp_instruction);
	}
}

void LGPProgram::MicroMutate()
{
	// Xianshun says:
	// the micro-mutation is derived from Linear Genetic Programming 2004 chapter 6 section 6.2.2
	// three type selection probability are first determined and roulette wheel is used to decide which
	// mutation type is to be performed
	// 1. if micro-mutate-operator type is selected, then randomly pick an instruction and
	// randomly select an instruction and mutate its operator to some other operator from the operator set
	// 2. if micro-mutate-register type is selected, then randomly pick an instruction and 
	// randomly select one of the two operands, then
	// 2.1 with a constant selection probability p_{const}, a randomly selected constant register is assigned to the selected operand
	// 2.2 with probability 1-p_{const}, a randomly selected variable register is assigned to the selected operand
	// p_{const} is the proportion of instruction that holds a constant value.
	// 3. if micro-mutate-constant type is selected, then randomly pick an effective instruction with a constant as one
	// of its register value, mutate the constant to c+$N(0, \omega_{\mu}$
	double micro_mutate_operator_rate=m_parent->GetConfig()->GetMicroMutateOperatorRate();
	double micro_mutate_register_rate=m_parent->GetConfig()->GetMicroMutateRegisterRate();
	double micro_mutate_constant_rate=m_parent->GetConfig()->GetMicroMutateConstantRate();

	double operator_sector=micro_mutate_operator_rate;
	double register_sector=operator_sector + micro_mutate_register_rate;
	
	double r=lgpRandom.nextDouble();
	if(r < operator_sector)
	{
		MutateInstructionOperator();
	}
	else if(r < register_sector)
	{
		MutateInstructionRegister();
	}
	else
	{
		MutateInstructionConstant();
	}

	this->TrashFitness();
}

void LGPProgram::MutateInstructionRegister()
{
	LGPInstruction* lgp_instruction=m_instructions[lgpRandom.nextInt(this->GetInstructionCount())];
	double p_const=0;
	std::vector<LGPInstruction*>::const_iterator pos_instruction;
	for(pos_instruction=m_instructions.begin(); pos_instruction != m_instructions.end(); ++pos_instruction)
	{
#ifdef LGP_DEBUG
		if((*pos_instruction)->IsOperand1ConstantRegister() && (*pos_instruction)->IsOperand2ConstantRegister())
		{
			LGPExitSystem("LGPProgram::MutateInstructionRegister()", "(*pos_instruction)->IsOperand1ConstantRegister() && (*pos_instruction)->IsOperand2ConstantRegister()");
		}
#endif
		if((*pos_instruction)->IsOperand1ConstantRegister() || (*pos_instruction)->IsOperand2ConstantRegister())
		{
			p_const+=1.0;
		}
	}
	p_const /= static_cast<double>(this->GetInstructionCount());

	lgp_instruction->MutateRegister(p_const);
}

void LGPProgram::MutateInstructionOperator()
{
	LGPInstruction* lgp_instruction=m_instructions[lgpRandom.nextInt(this->GetInstructionCount())];
	lgp_instruction->MutateOperator();
}

void LGPProgram::MutateInstructionConstant()
{
	// Xianshun says:
	// this is derived from the micro mutation implementation in section
	// 6.2.2 of Linear Genetic Programming
	// 1. randomly select an (effective) instruction with a constant c
	// 2. change constant c through a standard deviation from the current value
	// c:=c + normal(mean:=0, standard_deviation)
	std::vector<LGPInstruction*>::iterator pos_instruction;
	LGPInstruction* selected_instruction=NULL;
	for(pos_instruction=m_instructions.begin(); pos_instruction != m_instructions.end(); ++pos_instruction)
	{
		if((!(*pos_instruction)->IsStructuralIntron()) && ((*pos_instruction)->IsOperand1ConstantRegister() || (*pos_instruction)->IsOperand2ConstantRegister()))
		{
			if(selected_instruction == NULL)
			{
				selected_instruction=*pos_instruction;
			}
			else if(lgpRandom.nextDouble() < 0.5)
			{
				selected_instruction=*pos_instruction;
			}
		}
	}

	if(selected_instruction != NULL)
	{
		selected_instruction->MutateConstant(this->GetConfig()->GetMicroMutateConstantStandardDeviation());
	}
}

bool LGPProgram::IsBetterThan(const LGPProgram* rhs) const
{
#ifdef LGP_DEBUG
	if(!this->HasValidFitness())
	{
		LGPExitSystem("LGPProgram::IsBetterThan(const LGPProgram* rhs) const", "!this->HasValidFitness()");
	}
	if(!rhs->HasValidFitness())
	{
		LGPExitSystem("LGPProgram::IsBetterThan(const LGPProgram* rhs) const", "!rhs->HasValidFitness()");
	}
#endif
	return m_dFitness > rhs->GetFitness();
}

double LGPProgram::GetFitness() const
{
#ifdef LGP_DEBUG
	if(!this->HasValidFitness())
	{
		LGPExitSystem("LGPProgram::GetFitness() const", "!this->HasValidFitness()");
	}
#endif
	return m_dFitness;
}

double LGPProgram::GetObjectiveValue() const
{
#ifdef LGP_DEBUG
	if(!this->HasValidFitness())
	{
		LGPExitSystem("LGPProgram::GetObjectiveValue() const", "!this->HasValidFitness()");
	}
#endif

	return this->m_objective_value;
}

void LGPProgram::Setup()
{
	m_operator_set=this->CreateOperatorSet();
	m_register_set=this->CreateRegisterSet();
	m_constant_set=this->CreateConstantSet();

	m_bSetup=true;
}

LGPRegisterSet* LGPProgram::CreateRegisterSet()
{
	LGPRegisterSet* reg_set=new LGPRegisterSet();
	unsigned int iNumReg=this->GetConfig()->GetNumRegisters();
	for(unsigned int i=0; i<iNumReg; i++)
	{
		reg_set->AddRegister(new LGPRegister());
	}

	return reg_set;
}

LGPConstantSet* LGPProgram::CreateConstantSet()
{
	LGPConstantSet* constant_set=new LGPConstantSet();
	const LGPConfig* lgpConfig=this->GetConfig();
	unsigned int iConstantRegCount=lgpConfig->GetConstantRegCount();
	for(unsigned int i=0; i<iConstantRegCount; i++)
	{
		constant_set->AddConstant(lgpConfig->GetConstantRegValue(i), lgpConfig->GetConstantRegWeight(i));
	}

	return constant_set;
}