#include "XEnvironment.h"
#include "XFitnessCase.h"
#include <fstream>
#include <iostream>

spiral_classification::XEnvironment::XEnvironment(LGPConfig* lgpConfig)
: LGPEnvironment(lgpConfig)
{
	std::ifstream dataset_file("spiral_classification\\dataset.txt");

	unsigned int size=0;
	dataset_file >> size;
	for(unsigned int i=0; i<size; i++)
	{
		double x;
		double y;
		int fxy;
		dataset_file >> x;
		dataset_file >> y;
		dataset_file >> fxy;
		std::vector<double> input;
		input.push_back(x);
		input.push_back(y);
		std::pair<std::vector<double>, int> row=std::make_pair<>(input, fxy);
		m_data.push_back(row);
		//std::cout << "x: " << x << "\ty: " << y << "\tf(x, y): " << fxy << std::endl;
	}
}

spiral_classification::XEnvironment::~XEnvironment()
{

}

LGPFitnessCase* spiral_classification::XEnvironment::CreateFitnessCase(unsigned int iFitnessCase)
{
	spiral_classification::XFitnessCase* fitness_case=new spiral_classification::XFitnessCase();
	fitness_case->SetInput(m_data[iFitnessCase].first[0], 0);
	fitness_case->SetInput(m_data[iFitnessCase].first[1], 1);
	fitness_case->SetOutput(m_data[iFitnessCase].second);

	return fitness_case;
}

unsigned int spiral_classification::XEnvironment::GetFitnessCaseCount() const
{
	return static_cast<unsigned int>(m_data.size());
}



