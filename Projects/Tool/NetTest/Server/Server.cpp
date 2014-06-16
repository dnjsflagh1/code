
// Server.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
//#include "ServerNetUdpApplyManager.h";
#include "ServerNetApplyManager.h"
#include "Win32IocpNetUdpData.h"
#include "TestNetPacket.h"
#include "SServerSetting.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerApp

BEGIN_MESSAGE_MAP(CServerApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CServerApp construction
MG::InterLocked CServerApp::mIsStart = 0;
MG::InterLocked CServerApp::mIsConnect = 0;
CServerApp::CServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CServerApp object

CServerApp theApp;


// CServerApp initialization

BOOL CServerApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	if (!MG::SServerSetting::getInstance().loadFile(L"ServerConfig.txt"))
	{
		return FALSE;
	}

#ifdef _USE_UDP_
	MG::ServerNetUdpApplyManager::getInstance().initialize(UDP_SECTION_PACKET_DEFAULT_SIZE);
#else
	MG::ServerNetApplyManager::getInstance().initialize();
#endif
	
	mThreadHandle.create(threadFun,this);

	CServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CServerApp::threadFun( MG::Ptr p )
{
	while(true)
	{
#ifdef _USE_UDP_
		MG::ServerNetUdpApplyManager::getInstance().update();
#else
		MG::ServerNetApplyManager::getInstance().update();
#endif
		if (mIsStart)
		{

		}
		else
		{
			Sleep(1);
		}

	}
}

BOOL CServerApp::ExitInstance()
{
#ifdef _USE_UDP_
	MG::ServerNetUdpApplyManager::getInstance().unInitialize();
#else
	MG::ServerNetApplyManager::getInstance().unInitialize();
#endif
	return CWinAppEx::ExitInstance();
}