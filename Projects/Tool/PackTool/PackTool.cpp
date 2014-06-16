// PackTool.cpp : main project file.

#include "stdafx.h"
#include "CoreManager.h"

using namespace System;
using namespace PackTool;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	CoreManager& core = CoreManager::getInstance();

	BOOLEAN initRlt = core.initialize();
	if ( initRlt )
	{
		core.run();
	}
	core.uninitialize();

	return 0;
}
