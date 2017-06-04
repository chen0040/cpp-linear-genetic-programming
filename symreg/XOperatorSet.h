#ifndef _H_X_OPERATOR_SET_H
#define _H_X_OPERATOR_SET_H

#include "../LGPComp/LGPOperatorSet.h"

namespace symreg
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
