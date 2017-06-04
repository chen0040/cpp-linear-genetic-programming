#ifndef _H_MEXICAN_HAT_FITNESS_CASE_H
#define _H_MEXICAN_HAT_FITNESS_CASE_H

#include "../LGPEnvironment/LGPFitnessCase.h"

namespace mexican_hat
{
	class XFitnessCase : public LGPFitnessCase
	{
	public:
		XFitnessCase();
		virtual ~XFitnessCase();

	public:
		virtual void SetInput(double x, unsigned int index=0) { m_x[index] = x; }
		virtual void SetOutput(double y, unsigned int index=0) { m_y=y; }
		virtual void SetLGPOutput(double computed_y, unsigned int index=0) { m_computed_y=computed_y; }
		virtual void QueryInput(unsigned int index, double* input) const { *input=m_x[index]; }
		virtual void QueryOutput(unsigned int index, double* output) const { *output=m_y; }
		virtual void QueryLGPOutput(unsigned int index, double * output) const { *output=m_computed_y; }

	public:
		unsigned int GetInputCount() const { return 2; }
		unsigned int GetOutputCount() const { return 1; }
		unsigned int GetLGPOutputCount() const { return 1; }

	public:
		virtual std::string ToString() const;
		virtual void Update(const LGPOperator* op, const LGPRegister* operand1, const LGPRegister* operand2, const LGPRegister* destination_register, const LGPRegisterSet* lgpRegSet);
		virtual void Update(const LGPRegisterSet* lgpRegSet);

	protected:
		double m_x[2];
		double m_y;
		double m_computed_y;
	};
}
#endif
