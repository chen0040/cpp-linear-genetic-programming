#ifndef _H_MEXICAN_HAT_OPERATOR_SET_H
#define _H_MEXICAN_HAT_OPERATOR_SET_H

#include "../LGPComp/LGPOperatorSet.h"

namespace mexican_hat
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
