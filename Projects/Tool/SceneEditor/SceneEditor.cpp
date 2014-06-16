// SceneEditor.cpp : main project file.

#include "stdafx.h"
#include "CoreManager.h"

using namespace System;
using namespace SceneEditor;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{	
	if (args->Length > 0 && args[0] == "multiple")
	{
		
	}
	else
	{
		void* handle = CreateMutex(NULL,false,L"Mutex_SceneEditor");
	}
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        MG_MESSAGE(L"SceneEditor应用程序已经在运行!");
        return false;
    }


	CoreManager& core = CoreManager::getInstance();

    BOOLEAN initRlt = core.initialize();
    if ( initRlt )
    {
        core.run();
    }
    core.uninitialize();

	return 0;
}
