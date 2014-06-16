
// ClientLuancher.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ClientLuancher.h"
#include "ClientLuancherDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CClientLuancherApp

BEGIN_MESSAGE_MAP(CClientLuancherApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CClientLuancherApp 构造

CClientLuancherApp::CClientLuancherApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CClientLuancherApp 对象

CClientLuancherApp theApp;

std::string gAppPath;

// CClientLuancherApp 初始化

BOOL CClientLuancherApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	char			szFileName[256]; 
	char			szDrive[256]; 
	char			szDir[256]; 
	char			szPath[256]; 
	GetModuleFileNameA(NULL,szFileName,256); 
	_splitpath(szFileName,szDrive,szDir,NULL,NULL); 
	sprintf(szPath, "%s%s",szDrive,szDir);
	gAppPath = szPath;                       //当前应用程序所在路径

	CClientLuancherDlg dlg;

	m_pMainWnd = &dlg;
	mIsRun = false;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。

	

	return FALSE;
}

void CClientLuancherApp::gameThread( MG::Ptr ptr )
{
	OneThreadHandle* thd = (OneThreadHandle* )ptr;
	if ( thd && thd->getParam())
	{
		CClientLuancherApp* app = (CClientLuancherApp*)thd->getParam();
		DllLoader dllLoader;
		MG::IClientMain* clientInterface = NULL;

		GET_MGCLIENT_INTERFACE_PROC proc; 
		std::string dllName;

		HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
		if (hConsole)
		{
			FreeConsole();
		}
#ifdef _DEBUG
		dllName = "Core\\MGClient_d.dll";
#else
		dllName = "Core\\MGClient.dll";
#endif

		if (dllLoader.load(dllName.c_str(),false)) 
		{ 
			proc = (GET_MGCLIENT_INTERFACE_PROC) dllLoader.getProcAddress("GET_MGCLIENT_INTERFACE"); 
			if (NULL != proc) 
			{
				clientInterface = (MG::IClientMain*)proc(); 
				if (clientInterface==NULL)
				{
					MessageBoxA(NULL,"Load IClientMain Failed!","error",MB_OK );
					exit(0);
					return;
				}
			}
			else
			{
				MessageBoxA(NULL,"Don't Find IClientMain Entry!","error",MB_OK);
				exit(0);
				return;
			}
		}
		else
		{
			MessageBoxA(NULL,"Don't Load MGClient DLL!","error",MB_OK);
			exit(0);
			return;
		}

		app->mIsRun = true;
		bool isSuccess = clientInterface->initialize();
		if (isSuccess)
		{	
			app->GetMainWnd()->ShowWindow(SW_HIDE);
			clientInterface->run();
			clientInterface->uninitialize();
			dllLoader.unload();

			HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
			if (hConsole)
			{
				FreeConsole();
			}
		}

		exit(0);
	}
}