#include "LGPOperator_Sin.h"
#include <cmath>

LGPOperator_Sin::LGPOperator_Sin()
: LGPOperator("sin")
{

}

LGPOperator_Sin::~LGPOperator_Sin()
{

}

LGPOperator* LGPOperator_Sin::Clone() const
{
	return new LGPOperator_Sin(*this);
}

int LGPOperator_Sin::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	double x=operand1->ToDouble();
	destination_register->SetValue(sin(x));

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}