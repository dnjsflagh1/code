
// Server.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CServerApp:
// See Server.cpp for the implementation of this class
//

class CServerApp : public CWinAppEx
{
public:
	CServerApp();

	// Overrides
public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();

	// Implementation

	DECLARE_MESSAGE_MAP()
public:
	static	void threadFun(MG::Ptr p);
	MG::OneThreadHandle	mThreadHandle;
	static MG::InterLocked mIsStart;
	static MG::InterLocked mIsConnect;
	static CString mStr;
};

extern CServerApp theApp;