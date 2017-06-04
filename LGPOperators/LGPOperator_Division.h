#ifndef _H_LGP_OPERATOR_DIVISION_H
#define _H_LGP_OPERATOR_DIVISION_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Division : public LGPOperator
{
public:
	LGPOperator_Division();
	virtual ~LGPOperator_Division();

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);

public:
	virtual LGPOperator* Clone() const { return new LGPOperator_Division(*this); }
};
#endif