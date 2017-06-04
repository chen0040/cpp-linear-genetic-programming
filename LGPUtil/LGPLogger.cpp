#include "LGPLogger.h"

LGPLogger::LGPLogger()
{
	err.open("lgp_err.txt");
}

LGPLogger::~LGPLogger()
{
	err.close();
}

LGPLogger* LGPLogger::Instance()
{
	static LGPLogger theInstance;
	return &theInstance;
}