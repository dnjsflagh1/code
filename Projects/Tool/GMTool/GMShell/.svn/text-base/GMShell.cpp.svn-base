// GMTool.cpp : main project file.

#include "stdafx.h"
#include "MainForm.h"
#include "LoginForm.h"
#include "LoadingForm.h"
#include "GMToolManager.h"
using namespace MG;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	GMToolManager& GMT = GMToolManager::getInstance();

	BOOLEAN initRlt = GMT.initialize();
	if ( initRlt )
	{
		GMT.run();
	}
	GMT.uninitialize();
	return 0;
}
