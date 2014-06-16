// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "GMServerManagerMain.h"
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif
	__declspec(dllexport) void* __cdecl DLL_ENTRY_MGSERVERDLL_PROC(void)
	{
		return &MG::GMServerManagerMain::getInstance();
	}
#ifdef __cplusplus
}
#endif