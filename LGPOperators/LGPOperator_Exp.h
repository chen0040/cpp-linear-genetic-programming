#ifndef _H_LGP_OPERATOR_EXP_H
#define _H_LGP_OPERATOR_EXP_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Exp : public LGPOperator
{
public:
	LGPOperator_Exp();
	virtual ~LGPOperator_Exp();

public:
	virtual LGPOperator* Clone() const { return new LGPOperator_Exp(*this); }

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);
};
#endif