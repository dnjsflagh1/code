
// Client.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
//#include "ClientNetUdpApplyManager.h";
#include "ClientNetApplyManager.h"
#include "Win32IocpNetUdpData.h"
#include "TestNetPacket.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CLIENT_COUNT 200
// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClientApp construction

CClientApp::CClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CClientApp object

CClientApp theApp;


// CClientApp initialization
CString CClientApp::mStr;
MG::InterLocked CClientApp::mIsStart = 0;
MG::InterLocked CClientApp::mIsConnect = 0;
BOOL CClientApp::InitInstance()
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





#ifdef _USE_UDP_
	MG::ClientNetUdpApplyManager::getInstance().initialize();
#else
	MG::ClientNetApplyManager::getInstance().initialize();
#endif

	mThreadHandle.create(threadFun,this);
	CClientDlg dlg;
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

BOOL CClientApp::ExitInstance()
{
#ifdef _USE_UDP_
	MG::ClientNetUdpApplyManager::getInstance().unInitialize();
#else
	MG::ClientNetApplyManager::getInstance().unInitialize();
#endif
	return CWinAppEx::ExitInstance();
}

void CClientApp::threadFun( MG::Ptr p )
{
	MG::NetAddress addr("192.168.1.217",2002);
#ifdef _USE_UDP_
	MG::I32 handle = MG::ClientNetUdpApplyManager::getInstance().mNetDriver;
#else

#endif
	static MG::Int x = 0;
	static MG::Char8 buff[512];
	buff[512 - 1] = '\0';
	while(true)
	{
		x++;
#ifdef _USE_UDP_
		MG::ClientNetUdpApplyManager::getInstance().update();
#else
		MG::ClientNetApplyManager::getInstance().update();
#endif
		if (mIsConnect == 1)
		{
#ifdef _USE_UDP_
			for (int i = 0; i < CLIENT_COUNT; i++)
			{
				MG::ClientNetUdpApplyManager::getInstance().connect(0,&addr,i);
			}
#else
			for (int i = 0; i < CLIENT_COUNT; i++)
			{
				MG::ClientNetApplyManager::getInstance().connect(0,&addr);
			}	
#endif
			mIsConnect = 0;

		}
		if (mIsStart == 1)
		{

#ifdef _USE_UDP_
			for (int i = 0; i < 200; i++)
			{
				MG::LogicSendPacket* packet = MG::ClientNetUdpApplyManager::getInstance().getLogicSendPacket(handle,2,1,100,buff);
				packet->send(i,i,0);
			}
#else 
			for (int i = 0; i < CLIENT_COUNT; i++)
			{
				// 获得一个发送【服务端】缓存
				MG::NetSendDataBufferPtr dataPtr = MG::ClientNetApplyManager::getInstance().getSendDataBuffer( );
				MG::GameNetPacketData* packet = (MG::GameNetPacketData*) dataPtr->getData();
				if ( packet )
				{
					// 设置标签
					packet->channel = MG::GameNetPacketChannel::GNPC_TEST;
					packet->type    = MG::TestNetPacket::PT_TEST_CF_BASE;

					// 转换逻辑包
					MG::PT_TEST_BASE_DATA* sendData = (MG::PT_TEST_BASE_DATA*)(packet->data);
					if ( sendData )
					{
						// 填充逻辑包
						// 发送数据
						dataPtr->send(MG::GameNetPacketData_INFO::headSize + MG::PT_TEST_BASE_DATA_INFO::dataSize,i);
					}
				}
			}
#endif
		}
		else
		{
			Sleep(5);
		}

	}
}