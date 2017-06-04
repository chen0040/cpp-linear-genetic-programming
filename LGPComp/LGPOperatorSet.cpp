#include "LGPOperatorSet.h"
#include "../LGPUtil/LGPRandom.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPOperators/LGPOperator_Iflt.h"
#include "../LGPOperators/LGPOperator_Ifgt.h"
#include <sstream>
#include <iostream>

LGPOperatorSet::LGPOperatorSet()
: m_dWeightSum(0)
{

}

LGPOperatorSet::~LGPOperatorSet()
{
	std::vector<std::pair<LGPOperator*, double> >::iterator pos;
	for(pos=m_registers.begin(); pos != m_registers.end(); ++pos)
	{
		delete (pos->first);
	}
	m_registers.clear();
}

LGPOperatorSet::LGPOperatorSet(const LGPOperatorSet& rhs)
{
	m_dWeightSum=rhs.m_dWeightSum;
	m_registers.reserve(rhs.m_registers.size());

	for(size_t i=0; i<rhs.m_registers.size(); i++)
	{
		m_registers.push_back(std::make_pair<>(rhs.m_registers[i].first->Clone(), rhs.m_registers[i].second));
	}
}

LGPOperator* LGPOperatorSet::GetRandomOperator(LGPOperator* current_register)
{
	for(unsigned int attempts=0; attempts < 10; attempts++)
	{
		double r=m_dWeightSum * lgpRandom.nextDouble();
		std::vector<std::pair<LGPOperator*, double> >::iterator pos=m_registers.begin();
		double current_sum=0;
		while(pos != m_registers.end())
		{
			current_sum+=pos->second;
			if(current_sum >= r)
			{
				if(pos->first != current_register)
				{
					return pos->first;
				}
				else 
				{
					break;
				}
			}

			++pos;
		}
	}

	return current_register;
}
	
void LGPOperatorSet::AddOperator(LGPOperator* lgpOperator, double weight)
{
	m_registers.push_back(std::make_pair<>(lgpOperator, weight));
	lgpOperator->m_iOperatorIndex=static_cast<unsigned int>(m_registers.size()) - 1;
	
#ifdef LGP_DEBUG
	if(lgpOperator->m_iOperatorIndex >= m_registers.size())
	{
		LGPExitSystem("LGPOperatorSet::AddOperator(LGPOperator* lgpOperator, double weight)", "lgpOperator->m_iOperatorIndex >= m_registers.size()");
	}
#endif

	m_dWeightSum+=weight;
}

void LGPOperatorSet::AddIfltOperator(double weight)
{
	this->AddOperator(new LGPOperator_Iflt(), weight);
}

void LGPOperatorSet::AddIfgtOperator(double weight)
{
	this->AddOperator(new LGPOperator_Ifgt(), weight);
}

LGPOperator* LGPOperatorSet::GetOperator(unsigned int iRegisterIndex) const
{
#ifdef LGP_DEBUG
	if(iRegisterIndex >= m_registers.size())
	{
		LGPExitSystem("LGPOperatorSet::GetOperator(unsigned int iRegisterIndex)", "iRegisterIndex >= m_registers.size()");
	}
	if(iRegisterIndex < 0)
	{
		LGPExitSystem("LGPOperatorSet::GetOperator(unsigned int iRegisterIndex)", "iRegisterIndex < 0");
	}
#endif

	return m_registers[iRegisterIndex].first;
}

std::string LGPOperatorSet::ToString() const
{
	std::ostringstream oss;

	for(size_t i=0; i<m_registers.size(); ++i)
	{
		oss << "operators[" << i << "]: " << m_registers[i].first->ToString() << std::endl;
	}
	return oss.str();
}