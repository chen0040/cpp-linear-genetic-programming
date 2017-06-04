#include "XEnvironment.h"
#include "XFitnessCase.h"
#include <utility>

symreg::XEnvironment::XEnvironment(LGPConfig* lgpConfig)
: LGPEnvironment(lgpConfig)
{
	double lower_bound=-10;
	double upper_bound=10;
	int period=100;

	double interval=(upper_bound - lower_bound) / period;

	for(int i=0; i<period; i++)
	{
		double x=lower_bound + interval * i;
		m_data.push_back(std::make_pair<>(x, function_x(x)));
	}
}

symreg::XEnvironment::~XEnvironment()
{

}

LGPFitnessCase* symreg::XEnvironment::CreateFitnessCase(unsigned int iFitnessCase)
{
	XFitnessCase* fitness_case=new XFitnessCase();
	fitness_case->SetInput(m_data[iFitnessCase].first);
	fitness_case->SetOutput(m_data[iFitnessCase].second);

	return fitness_case;
}

unsigned int symreg::XEnvironment::GetFitnessCaseCount() const
{
	return static_cast<unsigned int>(m_data.size());
}

double symreg::XEnvironment::function_x(double x)
{
	return x*x + x + 1;
}

