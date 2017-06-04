#include "XProgram.h"
#include "XOperatorSet.h"
#include "../LGPComp/LGPPop.h"

mexican_hat::XProgram::XProgram(LGPPop* lgpPop)
: LGPProgram(lgpPop)
{

}

mexican_hat::XProgram::~XProgram()
{

}

LGPOperatorSet* mexican_hat::XProgram::CreateOperatorSet()
{
	return new mexican_hat::XOperatorSet();
}

LGPProgram* mexican_hat::XProgram::Clone() const
{
	return new mexican_hat::XProgram(*this);
}

double mexican_hat::XProgram::EvaluateFitness(std::vector<LGPFitnessCase*>& fitness_cases)
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