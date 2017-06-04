#include "LGPOperator_Plus.h"

LGPOperator_Plus::LGPOperator_Plus()
: LGPOperator("+")
{

}

LGPOperator_Plus::~LGPOperator_Plus()
{

}

int LGPOperator_Plus::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	double x=operand1->ToDouble();
	double y=operand2->ToDouble();

	destination_register->SetValue(x+y);

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}