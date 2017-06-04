#ifndef _H_LGP_FITNESS_CASE_H
#define _H_LGP_FITNESS_CASE_H

#include "../LGPComp/LGPOperator.h"
#include "../LGPComp/LGPRegisterSet.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <string>

class LGPFitnessCase
{
public:
	LGPFitnessCase();
	virtual ~LGPFitnessCase();

private:
	LGPFitnessCase(const LGPFitnessCase& rhs) { }
	LGPFitnessCase& operator=(const LGPFitnessCase& rhs) { return *this; }

public:
	virtual void SetInput(bool input, unsigned int index) { LGPExitSystem("LGPFitnessCase::SetInput(bool input, unsigned int index)", "this method is called without being overriden"); }
	virtual void SetInput(double input, unsigned int index) { LGPExitSystem("LGPFitnessCase::SetInput(double input, unsigned int index)", "this method is called without being overriden"); }
	virtual void SetInput(int input, unsigned int index) { LGPExitSystem("LGPFitnessCase::SetInput(int input, unsigned int index)", "this method is called without being overriden"); }
	virtual unsigned int GetInputCount() const=0;
	virtual void QueryInput(unsigned int index, int* input) const { LGPExitSystem("LGPFitnessCase::QueryInput(unsigned int index, int* input)", "this method is called without being overriden"); }
	virtual void QueryInput(unsigned int index, double* input) const { LGPExitSystem("LGPFitnessCase::QueryInput(unsigned int index, double* input)", "this method is called without being overriden"); }
	virtual void QueryInput(unsigned int index, bool* input) const { LGPExitSystem("LGPFitnessCase::QueryInput(unsigned int index, bool* input)", "this method is called without being overriden"); }

public:
	virtual void SetOutput(bool output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetOutput(bool output, unsigned int index)", "this method is called without being override"); }
	virtual void SetOutput(double output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetOutput(double output, unsigned int index)", "this method is called without being overriden"); }
	virtual void SetOuput(int output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetOutput(int output, unsigned int index)", "this method is called without being overriden"); }
	virtual unsigned int GetOutputCount() const=0;
	virtual void QueryOutput(unsigned int index, int* output) const { LGPExitSystem("LGPFitnessCase::QueryOutput(unsigned int index, int* output)", "this method is called without being overriden"); }
	virtual void QueryOutput(unsigned int index, double* output) const { LGPExitSystem("LGPFitnessCase::QueryOutput(unsigned int index, double* output)", "this method is called without being overriden"); }
	virtual void QueryOutput(unsigned int index, bool* output) const { LGPExitSystem("LGPFitnessCase::QueryOutput(unsigned int index, bool * output)", "this method is called without being overriden"); }

public:
	virtual void SetLGPOutput(bool output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetLGPOutput(bool output, unsigned int index)", "this method is called without being overriden"); }
	virtual void SetLGPOutput(double output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetLGPOutput(double output, unsigned int index)", "this method is called withtout being overriden"); }
	virtual void SetLGPOutput(int output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetLGPOutput(int output, unsigned int index)", "this method is called without being overriden"); }
	virtual unsigned int GetLGPOutputCount() const=0;
	virtual void QueryLGPOutput(unsigned int index, int* output) const { LGPExitSystem("LGPFitnessCase::QueryLGPOutput(unsigned int index, int* output)", "this method is called without being overriden");}
	virtual void QueryLGPOutput(unsigned int index, bool* output) const { LGPExitSystem("LGPFitnessCase::QueryLGPOutput(unsigned int index, bool* output)", "this method is called without being overriden");}
	virtual void QueryLGPOutput(unsigned int index, double* output) const { LGPExitSystem("LGPFitnessCase::QueryLGPOutput(unsigned int index, double* output)", "this method is called without being overriden");}

public:
	virtual void Update(const LGPOperator* op, const LGPRegister* operand1, const LGPRegister* operand2, const LGPRegister* destination_register, const LGPRegisterSet* lgpRegSet)=0;
	virtual void Update(const LGPRegisterSet* lgpRegSet)=0;

public:
	virtual std::string ToString() const=0;
};
#endif