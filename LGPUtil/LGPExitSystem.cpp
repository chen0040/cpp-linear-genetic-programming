#include "LGPExitSystem.h"
#include <cstdlib>
#include <iostream>
#include "LGPLogger.h"
#include "../LGPConstants/LGPFlags.h"
#include <cassert>

void LGPExitSystem(const char* fname, const char* ename)
{


	std::cout << "An error has occurred in the LGP System..." << std::endl;
	std::cout << "Source: " << fname << std::endl;
	std::cout << "Error: " << ename << std::endl;

	lgpLogger.err << "An error has occurred in the LGP System..." << std::endl;
	lgpLogger.err << "Source: " << fname << std::endl;
	lgpLogger.err << "Error: " << ename << std::endl;

#ifdef LGP_BUILD_DEBUG
	assert(false);
#else
	std::exit(0);
#endif
}