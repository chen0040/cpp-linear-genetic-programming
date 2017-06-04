#ifndef _H_LGP_OPERATOR_COS_H
#define _H_LGP_OPERATOR_COS_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Cos : public LGPOperator
{
public:
	LGPOperator_Cos();
	virtual ~LGPOperator_Cos();

public:
	virtual LGPOperator* Clone() const;
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);
};
#endif