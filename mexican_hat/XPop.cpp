#include "XPop.h"
#include "XEnvironment.h"
#include "XProgram.h"

mexican_hat::XPop::XPop(LGPConfig* lgpConfig)
: LGPPop(lgpConfig)
{

}

mexican_hat::XPop::~XPop()
{

}

LGPEnvironment* mexican_hat::XPop::CreateEnvironment(LGPConfig* lgpConfig)
{
	return new mexican_hat::XEnvironment(lgpConfig);
}



LGPProgram* mexican_hat::XPop::CreateProgram(unsigned int size, LGPEnvironment* env)
{
	mexican_hat::XProgram* lgp=new mexican_hat::XProgram(this);
	lgp->Create(size);

	return lgp;
}