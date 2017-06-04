#ifndef _H_LGP_OPERATOR_MULTIPLICATION_H
#define _H_LGP_OPERATOR_MULTIPLICATION_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Multiplication : public LGPOperator
{
public:
	LGPOperator_Multiplication();
	virtual ~LGPOperator_Multiplication();

public:
	virtual LGPOperator* Clone() const { return new LGPOperator_Multiplication(*this); }

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);
};
#endif