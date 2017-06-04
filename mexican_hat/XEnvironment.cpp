#include "XEnvironment.h"
#include "XFitnessCase.h"
#include <cmath>

mexican_hat::XEnvironment::XEnvironment(LGPConfig* lgpConfig)
: LGPEnvironment(lgpConfig)
{
	double lower_bound=-4;
	double upper_bound=4;
	int period=16;

	double interval=(upper_bound - lower_bound) / period;

	for(int i=0; i<period; i++)
	{
		double x1=lower_bound + interval * i;
		for(int j=0; j<period; j++)
		{
			double x2=lower_bound + interval * j;
			std::vector<double> row(3, 0);
			row[0]=x1;
			row[1]=x2;
			row[2]=mexican_hat_function(x1, x2);
			m_data.push_back(row);
		}
	}
}

mexican_hat::XEnvironment::~XEnvironment()
{

}

LGPFitnessCase* mexican_hat::XEnvironment::CreateFitnessCase(unsigned int iFitnessCase)
{
	mexican_hat::XFitnessCase* fitness_case=new mexican_hat::XFitnessCase();
	fitness_case->SetInput(m_data[iFitnessCase][0], 0);
	fitness_case->SetInput(m_data[iFitnessCase][1], 1);
	fitness_case->SetOutput(m_data[iFitnessCase][2], 0);

	return fitness_case;
}

unsigned int mexican_hat::XEnvironment::GetFitnessCaseCount() const
{
	return static_cast<unsigned int>(m_data.size());
}

double mexican_hat::XEnvironment::mexican_hat_function(double x1, double x2)
{
	return (1 - x1 * x1 / 4 - x2 * x2 / 4) * exp(- x1 * x2 / 8 - x2 * x2 / 8);
}

