#ifndef _H_X_POP_H
#define _H_X_POP_H

#include "../LGPComp/LGPPop.h"

namespace symreg
{
	class XPop : public LGPPop
	{
	public:
		XPop(LGPConfig* lgpConfig);
		virtual ~XPop();

	public:
		virtual LGPEnvironment* CreateEnvironment(LGPConfig* lgpConfig);
		virtual LGPProgram* CreateProgram(unsigned int size, LGPEnvironment* env);
	};
}

#endif
