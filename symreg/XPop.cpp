#include "XPop.h"
#include "XEnvironment.h"
#include "XProgram.h"

symreg::XPop::XPop(LGPConfig* lgpConfig)
: LGPPop(lgpConfig)
{

}

symreg::XPop::~XPop()
{

}

LGPEnvironment* symreg::XPop::CreateEnvironment(LGPConfig* lgpConfig)
{
	return new symreg::XEnvironment(lgpConfig);
}



LGPProgram* symreg::XPop::CreateProgram(unsigned int size, LGPEnvironment* env)
{
	XProgram* lgp=new XProgram(this);
	lgp->Create(size);

	return lgp;
}