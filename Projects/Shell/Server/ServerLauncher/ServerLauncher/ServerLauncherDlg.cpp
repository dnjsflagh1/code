
// ServerLauncherDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "ServerLauncherDlg.h"
#include "ServerMain.h"
#include "VersionSwitch.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerLauncherDlg 对话框

CServerLauncherDlg::CServerLauncherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerLauncherDlg::IDD, pParent)
{
	//parse cmdfor (int i = 1; i < __argc; i++)
	//TODO：暂时只有第一个参数有效，可添加
	//Str8  tempServerName;
    Str16 serverName;
    for (int i =1; i<__argc; i++)
    {
        Char16* pszParam = __targv[i];
		if (pszParam[0] == '-' || pszParam[0] == '/')
		{
			//过滤掉 - / 等标识符
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
		MG::MsgBox::show("应用程序没有正确参数!");
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


// CServerLauncherDlg 消息处理程序

BOOL CServerLauncherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
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

	//设置服务器，客户端版本号
	std::wstring version = L"Server：";
	version += _T(SERVER_VERSION_NUMBER);
	version += L"， ";
	version += L"Client：";
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
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerLauncherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServerLauncherDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	MG::ServerMain::getInstance().startServer();
}

void CServerLauncherDlg::OnBnClickedStope()
{
	// TODO: 在此添加控件通知处理程序代码
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

