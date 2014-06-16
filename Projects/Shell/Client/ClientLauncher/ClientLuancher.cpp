
// ClientLuancher.cpp : ����Ӧ�ó��������Ϊ��
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


// CClientLuancherApp ����

CClientLuancherApp::CClientLuancherApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CClientLuancherApp ����

CClientLuancherApp theApp;

std::string gAppPath;

// CClientLuancherApp ��ʼ��

BOOL CClientLuancherApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	char			szFileName[256]; 
	char			szDrive[256]; 
	char			szDir[256]; 
	char			szPath[256]; 
	GetModuleFileNameA(NULL,szFileName,256); 
	_splitpath(szFileName,szDrive,szDir,NULL,NULL); 
	sprintf(szPath, "%s%s",szDrive,szDir);
	gAppPath = szPath;                       //��ǰӦ�ó�������·��

	CClientLuancherDlg dlg;

	m_pMainWnd = &dlg;
	mIsRun = false;
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�

	

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