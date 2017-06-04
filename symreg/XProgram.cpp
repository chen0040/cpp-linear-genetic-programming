#include "XProgram.h"
#include "XOperatorSet.h"
#include "../LGPComp/LGPPop.h"

symreg::XProgram::XProgram(LGPPop* lgpPop)
: LGPProgram(lgpPop)
{

}

symreg::XProgram::~XProgram()
{

}

LGPOperatorSet* symreg::XProgram::CreateOperatorSet()
{
	return new symreg::XOperatorSet();
}

LGPProgram* symreg::XProgram::Clone() const
{
	return new symreg::XProgram(*this);
}

double symreg::XProgram::EvaluateFitness(std::vector<LGPFitnessCase*>& fitness_cases)
{
	double fitness=0;
	for(size_t i=0; i<fitness_cases.size(); i++)
	{
		double correct_y, computed_y;
		fitness_cases[i]->QueryLGPOutput(0, &computed_y);
		fitness_cases[i]->QueryOutput(0, &correct_y);
		fitness+=(correct_y-computed_y) * (correct_y - computed_y);
	}

	return fitness;
}