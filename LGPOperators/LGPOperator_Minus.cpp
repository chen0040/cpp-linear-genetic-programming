#include "LGPOperator_Minus.h"

LGPOperator_Minus::LGPOperator_Minus()
: LGPOperator("-")
{

}

LGPOperator_Minus::~LGPOperator_Minus()
{

}

int LGPOperator_Minus::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	double x=operand1->ToDouble();
	double y=operand2->ToDouble();
	destination_register->SetValue(x - y);

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}