#include "LGPOperator_Power.h"
#include "../LGPConstants/LGPProtectedDefinition.h"
#include <cmath>

LGPOperator_Power::LGPOperator_Power()
: LGPOperator("^")
{

}

LGPOperator_Power::~LGPOperator_Power()
{

}

int LGPOperator_Power::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	double x=operand1->ToDouble();
	double y=operand2->ToDouble();

	// Xianshun says:
	// This operator use the protected definition defined in Linear Genetic Programming
	
	if(fabs(x) <= 10)
	{
		destination_register->SetValue(pow(fabs(x), y));
	}
	else
	{
		destination_register->SetValue(x+y+LGP_UNDEFINED);
	}

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}