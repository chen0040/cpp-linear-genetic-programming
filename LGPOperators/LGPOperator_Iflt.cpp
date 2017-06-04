#include "LGPOperator_Iflt.h"

LGPOperator_Iflt::LGPOperator_Iflt()
: LGPOperator("If<")
{
	m_bIsConditionalConstruct=true;
}

LGPOperator_Iflt::~LGPOperator_Iflt()
{

}

int LGPOperator_Iflt::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	if(operand1->ToDouble() < operand2->ToDouble())
	{
		return LGP_EXECUTE_NEXT_INSTRUCTION;
	}
	else
	{
		return LGP_SKIP_NEXT_INSTRUCTION;
	}
}

LGPOperator* LGPOperator_Iflt::Clone() const
{
	return new LGPOperator_Iflt(*this);
}