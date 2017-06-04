#ifndef _H_SPIRAL_CLASSIFICATION_ENVIRONMENT_H
#define _H_SPIRAL_CLASSIFICATION_ENVIRONMENT_H

#include "../LGPEnvironment/LGPEnvironment.h"
#include <vector>
#include <utility>

namespace spiral_classification
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
		std::vector<std::pair<std::vector<double>, int> > m_data;
	};
}

#endif