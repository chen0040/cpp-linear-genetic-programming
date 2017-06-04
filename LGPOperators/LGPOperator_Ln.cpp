#include "LGPOperator_Ln.h"
#include "../LGPConstants/LGPProtectedDefinition.h"
#include <cmath>

LGPOperator_Ln::LGPOperator_Ln()
: LGPOperator("ln")
{

}

LGPOperator_Ln::~LGPOperator_Ln()
{

}

int LGPOperator_Ln::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	// Xianshun says:
	// The protected definition of Linear Genetic Programming is used here
	double x=operand1->ToDouble();

	if(x != 0)
	{
		destination_register->SetValue(log(x));
	}
	else
	{
		destination_register->SetValue(x+LGP_UNDEFINED);
	}

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}