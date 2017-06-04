#ifndef _H_LGP_OPERATOR_MINUS_H
#define _H_LGP_OPERATOR_MINUS_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Minus : public LGPOperator
{
public:
	LGPOperator_Minus();
	virtual ~LGPOperator_Minus();

public:
	virtual LGPOperator* Clone() const { return new LGPOperator_Minus(*this); }

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);
};

#endif