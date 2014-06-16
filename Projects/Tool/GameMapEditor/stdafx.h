// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

// TODO: reference additional headers your program requires here
#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#define WIN32_LEAN_AND_MEAN

// Windows Header Files:
#include <windows.h>

#include "MGTypes.h"
#include "MGDefine.h"

#include "MGMisc.h"
#include "MGMemory.h"
#include "MGMath.h"
#include "MGFile.h"
#include "MGThread.h"

#include "MGEngineInterface.h"

using namespace MG;

//delegate
#define DELEGATEFUNC(func) delegate void delegate_##func
#define BEGINDELEGATE(class,func)  if (this->InvokeRequired){\
    System::Delegate^ delegateFunc = gcnew delegate_##func(this, &##class##::##func);\
    this->Invoke(delegateFunc
#define ADDDELEGATEPARAMETER  ,
#define ENDDELEGATE  );return; }