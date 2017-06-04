#include "LGPOperator_Sqrt.h"
#include "../LGPConstants/LGPProtectedDefinition.h"
#include <cmath>

LGPOperator_Sqrt::LGPOperator_Sqrt()
: LGPOperator("sqrt")
{

}

LGPOperator_Sqrt::~LGPOperator_Sqrt()
{

}

int LGPOperator_Sqrt::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	// Xianshun says:
	// the protected definition in Linear Genetic Programming
	// is used here
	double x=operand1->ToDouble();
	destination_register->SetValue(sqrt(fabs(x)));

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}