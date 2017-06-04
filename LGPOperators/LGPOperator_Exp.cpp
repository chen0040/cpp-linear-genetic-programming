#include "LGPOperator_Exp.h"
#include "../LGPConstants/LGPProtectedDefinition.h"
#include <cmath>

LGPOperator_Exp::LGPOperator_Exp()
: LGPOperator("exp")
{

}

LGPOperator_Exp::~LGPOperator_Exp()
{

}

int LGPOperator_Exp::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	// Xianshun says:
	// the protected definition in Linear Genetic Programming is used
	double x=operand1->ToDouble();
	if(fabs(x) < 32)
	{
		destination_register->SetValue(exp(x));
	}
	else
	{
		destination_register->SetValue(x+LGP_UNDEFINED);
	}

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}