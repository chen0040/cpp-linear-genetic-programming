#include "LGPConfig/LGPConfig.h"
#include "symreg/XPop.h"
#include "mexican_hat/XPop.h"
#include "spiral_classification/XPop.h"
#include <iostream>
#include "LGPComp/LGPStats.h"

/*
#define VLD_MAX_DATA_DUMP 0
#define VLD_AGGREGATE_DUPLICATES 1

#include <vld.h>
*/

void spiral_classification_demo();
void symreg_demo();
void mexican_hat_demo();

int main()
{
	//spiral_classification_demo();
	//symreg_demo();
	mexican_hat_demo();

	return 0;
}

void mexican_hat_demo()
{
	LGPConfig config("mexican_hat\\LGPConfig.xml");
	std::cout << config.ToString() << std::endl;

	mexican_hat::XPop  pop(&config);
	//LGPStats stats(&pop);

	pop.BreedInitialPopulation();

	while(!pop.Terminated())
	{
		pop.Evolve();
		std::cout << "mexican hat generation: " << pop.GetCurrentGeneration() << std::endl;
		std::cout << "global fitness: " << pop.GetGlobalFittestProgram()->GetFitness() << "\tcurrent fitness: " << pop.GetFittestProgram()->GetFitness() << std::endl;
		//stats.LogStatistics();
	}

	std::cout << pop.GetGlobalFittestProgram()->ToString(true) << std::endl;
}

void spiral_classification_demo()
{
	LGPConfig config("spiral_classification\\LGPConfig.xml");
	std::cout << config.ToString() << std::endl;

	spiral_classification::XPop  pop(&config);
	//LGPStats stats(&pop);

	pop.BreedInitialPopulation();

	while(!pop.Terminated())
	{
		pop.Evolve();
		std::cout << "spiral classification generation: " << pop.GetCurrentGeneration() << std::endl;
		std::cout << "global fitness: " << pop.GetGlobalFittestProgram()->GetFitness() << "\tcurrent fitness: " << pop.GetFittestProgram()->GetFitness() << std::endl;
		//stats.LogStatistics();
	}

	std::cout << pop.GetGlobalFittestProgram()->ToString(true) << std::endl;
}

void symreg_demo()
{
	LGPConfig config("symreg\\LGPConfig.xml");
	std::cout << config.ToString() << std::endl;

	symreg::XPop  pop(&config);
	//LGPStats stats(&pop);

	pop.BreedInitialPopulation();

	while(!pop.Terminated())
	{
		pop.Evolve();
		std::cout << "mexican hat generation: " << pop.GetCurrentGeneration() << std::endl;
		std::cout << "global fitness: " << pop.GetGlobalFittestProgram()->GetFitness() << "\tcurrent fitness: " << pop.GetFittestProgram()->GetFitness() << std::endl;
		//stats.LogStatistics();
	}

	std::cout << pop.GetGlobalFittestProgram()->ToString(true) << std::endl;
}