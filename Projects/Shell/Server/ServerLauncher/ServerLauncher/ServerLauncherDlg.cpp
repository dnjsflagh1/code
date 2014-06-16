
// ServerLauncherDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "ServerLauncherDlg.h"
#include "ServerMain.h"
#include "VersionSwitch.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerLauncherDlg �Ի���

CServerLauncherDlg::CServerLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerLauncherDlg::IDD, pParent)
{
	//parse cmdfor (int i = 1; i < __argc; i++)
	//TODO����ʱֻ�е�һ��������Ч�������
	//Str8  tempServerName;
    Str16 serverName;
    for (int i =1; i<__argc; i++)
    {
        Char16* pszParam = __targv[i];
		if (pszParam[0] == '-' || pszParam[0] == '/')
		{
			//���˵� - / �ȱ�ʶ��
			++pszParam;
		}
		if(i ==1)
		{
			serverName = pszParam;
		}
    }

	//////////////////////////////////////////////////////////////////////////////
    
	if (serverName.empty() || serverName == L"")
	{
		//serverName = L"ServerConfig.txt";
		MG::MsgBox::show("Ӧ�ó���û����ȷ����!");
	}
    Str16 serverSettingPath = L"Setting\\" + serverName +L"\\";
	Str16 serverConfigFullName = L"Setting\\" + serverName + L"\\ServerConfig.txt";

	//////////////////////////////////////////////////////////////////////////////

	MG::SServerSetting::getInstance().loadFile(serverConfigFullName.c_str());
	ServerMain::getInstance().setSettingPathName((Char16*)serverSettingPath.c_str());
    ServerMain::getInstance().setConfigKeyName((Char16*)serverName.c_str());

	//////////////////////////////////////////////////////////////////////////////
    Str16 tempLogPathName = L"..\\Log\\" + serverName;
	Str8 LogPathName;
	MGStrOp::toString(tempLogPathName.c_str(),LogPathName);
	MG::LogSystem::getInstance().setSysLogPath(LogPathName.c_str());
	MG::LogSystem::getInstance().setGameLogicLogPath(LogPathName.c_str());
	MG::LogSystem::getInstance().setPartName("Luacher");
	MG::LogSystem::getInstance().setSaveToFile(true);

	//////////////////////////////////////////////////////////////////////////////

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB, mTab);
	DDX_Control(pDX, IDC_STOPE, mCloseBtn);
	DDX_Control(pDX, IDC_START, mStartBtn);

}

BEGIN_MESSAGE_MAP(CServerLauncherDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_START, &CServerLauncherDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOPE, &CServerLauncherDlg::OnBnClickedStope)
	ON_BN_CLICKED(IDCANCEL, &CServerLauncherDlg::OnDlgClose)
END_MESSAGE_MAP()


// CServerLauncherDlg ��Ϣ�������

BOOL CServerLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	I32 tabid=0;
	mServerSetTab.Create(IDD_LAUNCHER_SETTING_DLG, this);
	mServerSetTab.mSelfID = tabid;
	mTab.AddSSLPage(L"Setting", tabid++, &mServerSetTab);


	mServerStatusTab.Create(IDD_LUANCHER_SERVER_STATES_DLG, this);
	mServerStatusTab.mSelfID = tabid;
	mTab.AddSSLPage(L"Server States", tabid++, &mServerStatusTab);

	mNetStatesTab.Create(IDD_LUANCHER_NET_STATES_DLG, this);
	mNetStatesTab.mSelfID = tabid;
	mTab.AddSSLPage(L"Net States", tabid++, &mNetStatesTab);

	mNetSearchTab.Create(IDD_LUANCHER_SEARCH_DLG, this);
	mNetSearchTab.mSelfID = tabid;
	mTab.AddSSLPage(L"Net Search", tabid++, &mNetSearchTab);

	mShellMsgTab.Create(IDD_LUANCHER_SHELL_LOG_DLG, this);
	mShellMsgTab.mSelfID = tabid;
	mTab.AddSSLPage(L"Shell Log", tabid++, &mShellMsgTab);

	mCoreMsgTab.Create(IDD_LUANCHER_CORE_LOG_DLG, this);
	mCoreMsgTab.mSelfID = tabid;
	mTab.AddSSLPage(L"Core Log", tabid++, &mCoreMsgTab);

	mDbMsgTab.Create(IDD_LUANCHER_DB_LOG_DLG, this);
	mDbMsgTab.mSelfID = tabid;
	mTab.AddSSLPage(L"Db Log", tabid++, &mDbMsgTab);

	mThreadMsgTab.Create(IDD_LUANCHER_THREAD_DLG, this);
	mThreadMsgTab.mSelfID = tabid;
	mTab.AddSSLPage(L"Thread", tabid++, &mThreadMsgTab);

	//���÷��������ͻ��˰汾��
	std::wstring version = L"Server��";
	version += _T(SERVER_VERSION_NUMBER);
	version += L"�� ";
	version += L"Client��";
	version += _T(CLIENT_VERSION_NUMBER);
	GetDlgItem(IDC_ET_VERSION)->SetWindowText(version.c_str());
	
	MG::ServerMain::getInstance().setDialogHandle(GetSafeHwnd());
	//MG::Str8 Str = ::GetCommandLineA();
	//::ParseCommandLine
	MG::CoreInfo* core = MG::SServerSetting::getInstance().getCoreInfo();
	if (core)
	{
#ifdef _DEBUG
		Str16 dlgName = core->name;
		dlgName += L"_D";
		SetWindowText(dlgName.c_str());

#else
		SetWindowText(core->name.c_str());
#endif
		if (core->isAutoStart)
		{
			MG::ServerMain::getInstance().startServerInThread();
		}
		
	}

	gLauncherDlg = this;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerLauncherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CServerLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServerLauncherDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MG::ServerMain::getInstance().startServer();
}

void CServerLauncherDlg::OnBnClickedStope()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MG::ServerMain::getInstance().stopServer();
}

LRESULT CServerLauncherDlg::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{
	case LAUNCH_SERVER_START:
		{
			if ((Bool)(wParam!=0))
			{
				mStartBtn.EnableWindow(FALSE);
				mCloseBtn.EnableWindow(TRUE);
			}
			else
			{
				mStartBtn.EnableWindow(TRUE);
				mCloseBtn.EnableWindow(FALSE);
			}
			
			break;
		}
	case LAUNCH_SERVER_CONNECT:
		{
			Char16* name = (Char16*)wParam;
			MG::NetAddress* addr = (MG::NetAddress* )lParam;
			mServerStatusTab.onServerConnect(name,*addr);
			MG_SAFE_DELETE(name);
			MG_SAFE_DELETE(addr);
			
			break;
		}
	case LAUNCH_SERVER_DISCONNECT:
		{
			U64* uin = (U64*)wParam;
			mServerStatusTab.onServerDisconnect(*uin);
			MG_SAFE_DELETE(uin);

			break;
		}
	case LAUNCH_UPDATE:
		{
			LuanchUpdateInfo* info = (LuanchUpdateInfo*)wParam;
			MG::I32 count = (MG::I32)(lParam);
			mNetStatesTab.updateDate(info,count);
			MG_SAFE_DELETE_ARRAY(info);
			break;
		}
	case LAUNCH_WRITE_DB_LOG:
		{
			Char16* str = (Char16*)wParam;
			mDbMsgTab.addMsg(str);
			MG_SAFE_DELETE_ARRAY(str);
			break;
		}
	case LAUNCH_WRITE_CORE_LOG:
		{
			Char16* str = (Char16*)wParam;
			mCoreMsgTab.addMsg(str);
			MG_SAFE_DELETE_ARRAY(str);
			break;
		}
	case LAUNCH_WRITE_SHELL_LOG:
		{
			Char16* str = (Char16*)wParam;
			mShellMsgTab.addMsg(str);
			MG_SAFE_DELETE_ARRAY(str);
			break;
		}
	}

	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CServerLauncherDlg::OnDlgClose()
{
	MG::ServerMain::getInstance().stopServerInThread();
	OnCancel();
}

void CServerLauncherDlg::writeCoreLog(CString str)
{
	mCoreMsgTab.addMsg(str);
}

void CServerLauncherDlg::writeDbLog(CString str)
{
	mDbMsgTab.addMsg(str);
}

void CServerLauncherDlg::writeShellLog(CString str)
{
	mShellMsgTab.addMsg(str);
}

