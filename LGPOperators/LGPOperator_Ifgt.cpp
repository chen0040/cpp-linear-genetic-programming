#include "LGPOperator_Ifgt.h"

LGPOperator_Ifgt::LGPOperator_Ifgt()
: LGPOperator("If>")
{
	m_bIsConditionalConstruct=true;
}

LGPOperator_Ifgt::~LGPOperator_Ifgt()
{

}

int LGPOperator_Ifgt::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	if(operand1->ToDouble() > operand2->ToDouble())
	{
		return LGP_EXECUTE_NEXT_INSTRUCTION;
	}
	else
	{
		return LGP_SKIP_NEXT_INSTRUCTION;
	}
}

LGPOperator* LGPOperator_Ifgt::Clone() const
{
	return new LGPOperator_Ifgt(*this);
}