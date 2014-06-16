// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <wmsplaylistparser.h>

////////////////////////////////////////////////////////////

#ifdef _WINDOWS
    //#pragma warning(disable:4018) // signed/unsigned mismatch
    //#pragma warning(disable:4244) // conversion from 'TYPE_A' to 'TYPE_B', possible loss of data
    //#pragma warning(disable:4355) // 'this' : used in base member initializer list

    #pragma warning(disable:4819) // The file contains a character
    #pragma warning(disable:4099) // pdb file  mismatch
#endif

////////////////////////////////////////////////////////////

// TODO: reference additional headers your program requires here
#include "Ogre.h"
#include "OgreAL.h"
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>
#include <Common/Base/StatisticInfo.h>
#include <Common/Base/InputFocusInfo.h>

using namespace Ogre;

////////////////////////////////////////////////////////////

#include <tinyxml2.h>

////////////////////////////////////////////////////////////

#include "MGTypes.h"
#include "MGDefine.h"
#include "MGStd.h"

#include "MGMath.h"
#include "MGMisc.h"
#include "MGMemory.h"
#include "MGThread.h"
#include "MGFile.h"

////////////////////////////////////////////////////////////




