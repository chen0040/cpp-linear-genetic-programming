#ifndef _H_LGP_OPERATOR_If_GREATER_THAN_H
#define _H_LGP_OPERATOR_If_GREATER_THAN_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Ifgt : public LGPOperator
{
public:
	LGPOperator_Ifgt();
	virtual ~LGPOperator_Ifgt();

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);

public:
	LGPOperator* Clone() const;
};
#endif

/* Xianshun says:
  this operator implements the "If greater than" instruction
  Ifgt(operand1 > operand2)
  {
	execute next line
  }
  else
  {
	skip next line
  }
*/
