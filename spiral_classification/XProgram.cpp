#include "XProgram.h"
#include "XOperatorSet.h"
#include "../LGPComp/LGPPop.h"

spiral_classification::XProgram::XProgram(LGPPop* lgpPop)
: LGPProgram(lgpPop)
{

}

spiral_classification::XProgram::~XProgram()
{

}

LGPOperatorSet* spiral_classification::XProgram::CreateOperatorSet()
{
	return new spiral_classification::XOperatorSet();
}

LGPProgram* spiral_classification::XProgram::Clone() const
{
	return new spiral_classification::XProgram(*this);
}

double spiral_classification::XProgram::EvaluateFitness(std::vector<LGPFitnessCase*>& fitness_cases)
{
	double fitness=0;
	for(size_t i=0; i<fitness_cases.size(); i++)
	{
		int correct_y, computed_y;
		fitness_cases[i]->QueryLGPOutput(0, &computed_y);
		fitness_cases[i]->QueryOutput(0, &correct_y);
		fitness+=(correct_y == computed_y) ? 0 : 1;
	}

	return fitness;
}