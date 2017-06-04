#ifndef _H_SPIRAL_CLASSIFICATION_POP_H
#define _H_SPIRAL_CLASSIFICATION_POP_H

#include "../LGPComp/LGPPop.h"

namespace spiral_classification
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
