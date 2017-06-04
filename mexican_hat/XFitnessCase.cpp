#include "XFitnessCase.h"
#include <sstream>
#include <iostream>

mexican_hat::XFitnessCase::XFitnessCase()
: LGPFitnessCase()
{

}

mexican_hat::XFitnessCase::~XFitnessCase()
{

}

std::string mexican_hat::XFitnessCase::ToString() const
{
	std::ostringstream oss;

	return oss.str();
}

void mexican_hat::XFitnessCase::Update(const LGPOperator* op, const LGPRegister* operand1, const LGPRegister* operand2, const LGPRegister* destination_register, const LGPRegisterSet* lgpRegSet)
{

}

void mexican_hat::XFitnessCase::Update(const LGPRegisterSet* lgpRegSet)
{
	SetLGPOutput(lgpRegSet->GetRegister(0)->ToDouble());	
}