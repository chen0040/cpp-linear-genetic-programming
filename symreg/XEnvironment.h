#ifndef _H_X_ENVIRONMENT_H
#define _H_X_ENVIRONMENT_H

#include "../LGPEnvironment/LGPEnvironment.h"
#include <vector>

namespace symreg
{
	class XEnvironment : public LGPEnvironment
	{
	public:
		XEnvironment(LGPConfig* lgpConfig);
		virtual ~XEnvironment();

	public:
		virtual LGPFitnessCase* CreateFitnessCase(unsigned int iFitnessCase);
		virtual unsigned int GetFitnessCaseCount() const;

	protected:
		double function_x(double x);
	protected:
		std::vector<std::pair<double, double> > m_data;
	};
}

#endif