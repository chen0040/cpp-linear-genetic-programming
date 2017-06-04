#ifndef _H_LGP_OPERATOR_H
#define _H_LGP_OPERATOR_H

#include "LGPRegister.h"
#include "../LGPConstants/LGPFlags.h"
#include <string>

class LGPOperatorSet;

class LGPOperator
{
public:
	LGPOperator(const char* symbol);
	virtual ~LGPOperator();

public:
	LGPOperator(const LGPOperator& rhs);
private:
	LGPOperator& operator=(const LGPOperator& rhs) { return *this; }

protected:
	bool m_bIsConditionalConstruct;
public:
	bool IsConditionalConstruct() { return m_bIsConditionalConstruct; }

protected:
	unsigned int m_iOperatorIndex;
public:
	unsigned int GetOperatorIndex() const { return m_iOperatorIndex; }

public:
	virtual LGPOperator* Clone() const=0;
	virtual std::string ToString() const;

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)=0;

protected:
	friend class LGPOperatorSet;
	std::string m_symbol;
};
#endif