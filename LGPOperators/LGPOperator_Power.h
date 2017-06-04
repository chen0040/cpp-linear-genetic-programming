#ifndef _H_LGP_OPERATOR_POWER_H
#define _H_LGP_OPERATOR_POWER_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Power : public LGPOperator
{
public:
	LGPOperator_Power();
	virtual ~LGPOperator_Power();

public:
	virtual LGPOperator* Clone() const { return new LGPOperator_Power(*this); }

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);

};
#endif