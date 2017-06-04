#ifndef _H_SPIRAL_CLASSIFICATION_OPERATOR_SET_H
#define _H_SPIRAL_CLASSIFICATION_OPERATOR_SET_H

#include "../LGPComp/LGPOperatorSet.h"

namespace spiral_classification
{
	class XOperatorSet : public LGPOperatorSet
	{
	public:
		XOperatorSet();
		virtual ~XOperatorSet();

	public:
		virtual LGPOperatorSet* Clone() const { return new XOperatorSet(*this); }
	};
}
#endif
