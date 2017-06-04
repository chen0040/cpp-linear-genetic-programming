#include "XFitnessCase.h"
#include <sstream>
#include <iostream>

symreg::XFitnessCase::XFitnessCase()
: LGPFitnessCase()
{

}

symreg::XFitnessCase::~XFitnessCase()
{

}

std::string symreg::XFitnessCase::ToString() const
{
	std::ostringstream oss;

	return oss.str();
}

void symreg::XFitnessCase::Update(const LGPOperator* op, const LGPRegister* operand1, const LGPRegister* operand2, const LGPRegister* destination_register, const LGPRegisterSet* lgpRegSet)
{

}

void symreg::XFitnessCase::Update(const LGPRegisterSet* lgpRegSet)
{
	SetLGPOutput(lgpRegSet->GetRegister(0)->ToDouble());	
}