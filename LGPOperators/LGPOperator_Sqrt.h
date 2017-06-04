#ifndef _H_LGP_OPERATOR_SQRT_H
#define _H_LGP_OPERATOR_SQRT_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Sqrt : public LGPOperator
{
public:
	LGPOperator_Sqrt();
	virtual ~LGPOperator_Sqrt();

public:
	virtual LGPOperator* Clone() const { return new LGPOperator_Sqrt(*this); }

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);
};

#endif