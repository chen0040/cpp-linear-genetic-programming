#include "XOperatorSet.h"
#include "../LGPOperators/LGPOperator_Plus.h"
#include "../LGPOperators/LGPOperator_Minus.h"
#include "../LGPOperators/LGPOperator_Multiplication.h"
#include "../LGPOperators/LGPOperator_Division.h"
#include "../LGPOperators/LGPOperator_Power.h"

symreg::XOperatorSet::XOperatorSet()
: LGPOperatorSet()
{
	this->AddOperator(new LGPOperator_Plus());
	this->AddOperator(new LGPOperator_Minus());
	this->AddOperator(new LGPOperator_Division());
	this->AddOperator(new LGPOperator_Multiplication());
	this->AddOperator(new LGPOperator_Power());
	this->AddIfltOperator();
}

symreg::XOperatorSet::~XOperatorSet()
{

}