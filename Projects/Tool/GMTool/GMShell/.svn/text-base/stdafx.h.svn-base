// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
#pragma once

// TODO: reference additional headers your program requires here
//#include "Windows.h"


#define SINGLETON_INSTANCE(c) public: static c& getInstance(){static c ins;return ins;}
#define REP(   n)   for(int i=(n); --i>= 0 ;    ) // repeat                : n-1 .. 0
#define REPD(i,n)   for(int i=(n); --i>= 0 ;    ) // repeat with definition: n-1 .. 0
#define FREP(   n)  for(int i= 0 ;   i< (n); i++) // forward repeat                :   0 .. n-1
#define FREPD(i,n)  for(int i= 0 ;   i< (n); i++) // forward repeat with definition:   0 .. n-1


//delegate
#define DELEGATEFUNC(func) delegate void delegate_##func
#define BEGINDELEGATE(class,func)  if (this->InvokeRequired){\
	System::Delegate^ delegateFunc = gcnew delegate_##func(this, &##class##::##func);\
	this->Invoke(delegateFunc
#define ADDDELEGATEPARAMETER  ,
#define ENDDELEGATE  );return; }

#define INIT_CONFIG_TEXT IGMClient* config_client = GMToolManager::getInstance().getGMClient();
#define SET_CONFIG_TEXT_GROUP(group) config_client->setNativeGroupByC(group)
#define GET_CONFIG_TEXT(key,text)  Utility::convertAnsiToString(const_cast<char*>(config_client->getNativeValueByC(key,text)))


#include "MGTypes.h"
#include "MGDefine.h"
#include "MGNet.h"

#include <Windows.h>
#include "MGMisc.h"
#include "MGMemory.h"
#include "MGMath.h"
#include "MGFile.h"
#include "MGThread.h"
#include "Utility.h"
#include "DllLoader.h"
#include <time.h>
