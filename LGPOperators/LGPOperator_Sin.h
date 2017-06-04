#ifndef _H_LGP_OPERATOR_SIN_H
#define _H_LGP_OPERATOR_SIN_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Sin : public LGPOperator
{
public:
	LGPOperator_Sin();
	virtual ~LGPOperator_Sin();

public:
	virtual LGPOperator* Clone() const;
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);
};
#endif