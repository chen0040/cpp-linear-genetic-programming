# cpp-linear-genetic-programming

Package provides C++ implementation of linear genetic programming algorithms described in the book "Linear Genetic Programming".

# Introduction

Linear Genetic Programming examines the evolution of imperative computer programs written as linear sequences of instructions. In contrast to functional expressions or syntax trees used in traditional Genetic Programming (GP), Linear Genetic Programming (LGP) employs a linear program structure as genetic material whose primary characteristics are exploited to achieve acceleration of both execution time and evolutionary progress (From the book "Linear Genetic Programming").

# Usage

git clone this project to your local computer. The solution file can be open and run using Visual Studio IDE 2017.

Please refers one of the following folders (each of which solve a different optimization problem) on how to create the set of source files that will solve your problem:

* mexican_hat
* spiral_classification
* symreg

The main code to run in the main looks like the following (Note that the C++ code uses xml files for configuration), you can test run the codes in the main.cpp file.

```cpp
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
```
