#include "XPop.h"
#include "XEnvironment.h"
#include "XProgram.h"

spiral_classification::XPop::XPop(LGPConfig* lgpConfig)
: LGPPop(lgpConfig)
{

}

spiral_classification::XPop::~XPop()
{

}

LGPEnvironment* spiral_classification::XPop::CreateEnvironment(LGPConfig* lgpConfig)
{
	return new spiral_classification::XEnvironment(lgpConfig);
}



LGPProgram* spiral_classification::XPop::CreateProgram(unsigned int size, LGPEnvironment* env)
{
	spiral_classification::XProgram* lgp=new spiral_classification::XProgram(this);
	lgp->Create(size);

	return lgp;
}