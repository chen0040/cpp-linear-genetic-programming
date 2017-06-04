#include "LGPOperator_Division.h"
#include "../LGPConstants/LGPProtectedDefinition.h"

LGPOperator_Division::LGPOperator_Division()
: LGPOperator("/")
{

}

LGPOperator_Division::~LGPOperator_Division()
{

}

int LGPOperator_Division::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	if(operand2->ToDouble() == 0)
	{
		destination_register->SetValue(operand1->ToDouble() + LGP_UNDEFINED);
	}
	else
	{
		destination_register->SetValue(operand1->ToDouble() / operand2->ToDouble());
	}

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}