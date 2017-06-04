#ifndef _H_LGP_OPERATOR_LN_H
#define _H_LGP_OPERATOR_LN_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Ln : public LGPOperator
{
public:
	LGPOperator_Ln();
	virtual ~LGPOperator_Ln();

public:
	LGPOperator* Clone() const { return new LGPOperator_Ln(*this); }

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);
};

#endif