#ifndef _H_MEXICAN_HAT_PROGRAM_H
#define _H_MEXICAN_HAT_PROGRAM_H

#include "../LGPComp/LGPProgram.h"

namespace mexican_hat
{
	class XProgram : public LGPProgram
	{
	public:
		XProgram(LGPPop* lgpPop);
		virtual ~XProgram();

	protected:
		virtual LGPOperatorSet* CreateOperatorSet();

	protected:
		virtual double EvaluateFitness(std::vector<LGPFitnessCase*>& fitness_cases);

	public:
		virtual LGPProgram* Clone() const;
	};
}

#endif
