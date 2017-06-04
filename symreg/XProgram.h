#ifndef _H_X_PROGRAM_H
#define _H_X_PROGRAM_H

#include "../LGPComp/LGPProgram.h"

namespace symreg
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
