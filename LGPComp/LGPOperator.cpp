#include "LGPOperator.h"

LGPOperator::LGPOperator(const char* symbol)
: m_bIsConditionalConstruct(false)
, m_symbol(symbol)
{

}

LGPOperator::LGPOperator(const LGPOperator& rhs)
{
	m_iOperatorIndex=rhs.m_iOperatorIndex;
	m_bIsConditionalConstruct=rhs.m_bIsConditionalConstruct;
	m_symbol=rhs.m_symbol;
}

LGPOperator::~LGPOperator()
{

}

std::string LGPOperator::ToString() const
{
	return m_symbol;
}