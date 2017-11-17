#include "LGPOperator_Multiplication.h"

LGPOperator_Multiplication::LGPOperator_Multiplication()
: LGPOperator("*")
{

}

LGPOperator_Multiplication::~LGPOperator_Multiplication()
{

}

int LGPOperator_Multiplication::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	double x1=operand1->ToDouble();
	double x2=operand2->ToDouble();
	destination_register->SetValue(x1 * x2);

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}
