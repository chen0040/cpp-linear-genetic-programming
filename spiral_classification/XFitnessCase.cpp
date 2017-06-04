#include "XFitnessCase.h"
#include <sstream>
#include <iostream>

spiral_classification::XFitnessCase::XFitnessCase()
: LGPFitnessCase()
{

}

spiral_classification::XFitnessCase::~XFitnessCase()
{

}

std::string spiral_classification::XFitnessCase::ToString() const
{
	std::ostringstream oss;

	return oss.str();
}

void spiral_classification::XFitnessCase::Update(const LGPOperator* op, const LGPRegister* operand1, const LGPRegister* operand2, const LGPRegister* destination_register, const LGPRegisterSet* lgpRegSet)
{

}

void spiral_classification::XFitnessCase::Update(const LGPRegisterSet* lgpRegSet)
{
	if(lgpRegSet->GetRegister(0)->ToDouble() < 0.5)
	{
		this->SetLGPOutput(-1);	
	}
	else
	{
		this->SetLGPOutput(1);
	}
}