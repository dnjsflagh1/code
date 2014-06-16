// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here


#include "MGTypes.h"
#include "MGDefine.h"

#include "MGNet.h"
#include <windows.h>
#include "MGMisc.h"
#include "MGMemory.h"
#include "MGMath.h"
#include "MGFile.h"
#include "MGThread.h"
#include "MGLua.h"

//#include <afxdlgs.h>
//#include "Resource.h"
//#include "GameNetPacket.h"
#ifdef _DEBUG
//#include "vld.h"
#endif // _DEBUG
#define MAX_CONNECT 1000
#define THREAD_COUNT 4
#define SEND_COUNT 10