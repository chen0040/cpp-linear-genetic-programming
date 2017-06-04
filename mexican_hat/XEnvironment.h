#ifndef _H_MEXICAN_HAT_ENVIRONMENT_H
#define _H_MEXICAN_HAT_ENVIRONMENT_H

#include "../LGPEnvironment/LGPEnvironment.h"
#include <vector>

namespace mexican_hat
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
		double mexican_hat_function(double x1, double x2);
	protected:
		std::vector<std::vector<double> > m_data;
	};
}

#endif
