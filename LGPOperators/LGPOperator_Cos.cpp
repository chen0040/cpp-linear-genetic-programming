#include "LGPOperator_Cos.h"
#include <cmath>

LGPOperator_Cos::LGPOperator_Cos()
: LGPOperator("sin")
{

}

LGPOperator_Cos::~LGPOperator_Cos()
{

}

LGPOperator* LGPOperator_Cos::Clone() const
{
	return new LGPOperator_Cos(*this);
}

int LGPOperator_Cos::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	double x=operand1->ToDouble();
	destination_register->SetValue(cos(x));
	return LGP_EXECUTE_NEXT_INSTRUCTION;
}