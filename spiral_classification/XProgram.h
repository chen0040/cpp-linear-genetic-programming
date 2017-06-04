#ifndef _H_SPIRAL_CLASSIFICATION_PROGRAM_H
#define _H_SPIRAL_CLASSIFICATION_PROGRAM_H

#include "../LGPComp/LGPProgram.h"

namespace spiral_classification
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
