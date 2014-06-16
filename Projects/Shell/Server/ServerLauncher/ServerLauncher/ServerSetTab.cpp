// ServerSetTab.cpp : implementation file
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "ServerSetTab.h"
#include "ServerLauncherDlg.h"

extern char g_szWorkPath[MAX_PATH];
// ServerSetTab dialog

IMPLEMENT_DYNAMIC(ServerSetTab, CDialog)

ServerSetTab::ServerSetTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(ServerSetTab::IDD, pParent)
{
	mSelfID = 0;
}

ServerSetTab::~ServerSetTab()
{
}

void ServerSetTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_OPENINI, m_OpenBtn);
	//DDX_Control(pDX, IDC_RELOAD, m_ReloadBtn);
	
}


BEGIN_MESSAGE_MAP(ServerSetTab, CTabPageSSL)
	ON_BN_CLICKED(IDC_CK_SERVER_ENCRYPT, &ServerSetTab::OnBnClickedCkServerEncrypt)
	ON_BN_CLICKED(IDC_CK_CLIENT_ENCRYPT, &ServerSetTab::OnBnClickedCkClientEncrypt)
	ON_BN_CLICKED(IDC_CK_AUTO_START, &ServerSetTab::OnBnClickedCkAutoStart)
	ON_BN_CLICKED(IDC_CK_SAVE_CORE_LOG, &ServerSetTab::OnBnClickedCkSaveCoreLog)
	ON_BN_CLICKED(IDC_CK_SAVE_DB_LOG, &ServerSetTab::OnBnClickedCkSaveDbLog)
	ON_BN_CLICKED(IDC_CK_SAVE_SHELL_LOG, &ServerSetTab::OnBnClickedCkSaveShellLog)
	ON_BN_CLICKED(IDC_CK_CREAT_DB, &ServerSetTab::OnBnClickedCkCreatDb)
END_MESSAGE_MAP()


// ServerSetTab message handlers
BOOL ServerSetTab::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	loadSetting();
	DWORD style = GetWindowLong(mList.GetSafeHwnd(), GWL_STYLE);
	SetWindowLong(mList.GetSafeHwnd(), GWL_STYLE,style|LVS_REPORT|LVS_NOLABELWRAP|LVS_SHOWSELALWAYS);
	return TRUE;
}

void ServerSetTab::loadSetting()
{
	Str16 str;
	CString buf;
	{
		MG::ServerListenInfo* server = MG::SServerSetting::getInstance().getServerListenInfo();
		I32 bValue;
		if (server)
		{
			MG::MGStrOp::toString(server->addr.getIPStrA(),str);
			GetDlgItem(IDC_ET_SERVER_IP)->SetWindowText(str.c_str());
#ifndef MG_WCHAR_T_STRINGS
			MG::MGStrOp::toString(server->addr.getPortStr(),str);
			GetDlgItem(IDC_ET_SERVER_PORT)->SetWindowText(str.c_str());
#else
			GetDlgItem(IDC_ET_SERVER_PORT)->SetWindowText(server->addr.getPortStr());
#endif
			buf.Format(L"%d",server->maxConnects);
			GetDlgItem(IDC_ET_SERVER_CONNECTIONS)->SetWindowText(buf);
			bValue = (server->isEncrypted) ? BST_CHECKED : BST_UNCHECKED;
			((CButton*)GetDlgItem(IDC_CK_SERVER_ENCRYPT))->SetCheck(bValue);
		}

		MG::ClientListenInfo* client = MG::SServerSetting::getInstance().getClientListenInfo();
		if (client)
		{
			MG::MGStrOp::toString(client->addr.getIPStrA(),str);
			GetDlgItem(IDC_ET_CLIENT_IP)->SetWindowText(str.c_str());
#ifndef MG_WCHAR_T_STRINGS
			MG::MGStrOp::toString(client->addr.getPortStr(),str);
			GetDlgItem(IDC_ET_CLIENT_PORT)->SetWindowText(str.c_str());
#else
			GetDlgItem(IDC_ET_CLIENT_PORT)->SetWindowText(client->addr.getPortStr);
#endif
			buf.Format(L"%d",client->maxConnects);
			GetDlgItem(IDC_ET_CLIENT_CONNECTIONS)->SetWindowText(buf);
			bValue = (client->isEncrypted) ? BST_CHECKED : BST_UNCHECKED;
			((CButton*)GetDlgItem(IDC_CK_CLIENT_ENCRYPT))->SetCheck(bValue);
		}

		
		//core
		MG::CoreInfo* core = MG::SServerSetting::getInstance().getCoreInfo();
		if (core)
		{
			GetDlgItem(IDC_ET_CORE_Name)->SetWindowText(core->name.c_str());
			buf.Format(L"%d",core->id);
			GetDlgItem(IDC_ET_CORE_ID)->SetWindowText(buf);
			buf.Format(L"%d",core->type);
			GetDlgItem(IDC_ET_CORE_TYPE)->SetWindowText(buf);
			buf.Format(L"%d",core->updateTick);
			GetDlgItem(IDC_ET_CORE_UPDATE_TICK)->SetWindowText(buf);
			buf.Format(L"%d",core->closeTime);
			GetDlgItem(IDC_ET_CORE_CLOSE_TIME)->SetWindowText(buf);
			buf.Format(L"%d",core->logLevel);
			GetDlgItem(IDC_ET_CORE_LOG_LEVEL)->SetWindowText(buf);
			//buf.Format(L"%d",client->maxConnects);
			bValue = (core->isAutoStart) ? BST_CHECKED : BST_UNCHECKED;
			((CButton*)GetDlgItem(IDC_CK_AUTO_START))->SetCheck(bValue);
			bValue = (core->isWriteCoreLog) ? BST_CHECKED : BST_UNCHECKED;
			((CButton*)GetDlgItem(IDC_CK_SAVE_CORE_LOG))->SetCheck(bValue);
			bValue = (core->isWriteDbLog) ? BST_CHECKED : BST_UNCHECKED;
			((CButton*)GetDlgItem(IDC_CK_SAVE_DB_LOG))->SetCheck(bValue);
			bValue = (core->isWriteShellLog) ? BST_CHECKED : BST_UNCHECKED;
			((CButton*)GetDlgItem(IDC_CK_SAVE_SHELL_LOG))->SetCheck(bValue);

		}

		//db
		MG::DbConnectInfo* Db = MG::SServerSetting::getInstance().getDbConnectInfo();
		if (Db)
		{
			GetDlgItem(IDC_ET_DB_IP)->SetWindowText(Db->ip.c_str());
			buf.Format(L"%d",Db->port);
			GetDlgItem(IDC_ET_DB_PORT)->SetWindowText(buf);
			GetDlgItem(IDC_ET_DB_NAME)->SetWindowText(Db->name.c_str());
			GetDlgItem(IDC_ET_DB_ACCOUNT)->SetWindowText(Db->account.c_str());
			bValue = (Db->isCreate) ? BST_CHECKED : BST_UNCHECKED;
			((CButton*)GetDlgItem(IDC_CK_CREAT_DB))->SetCheck(bValue);
		}
	
	}

}

void ServerSetTab::OnBnClickedCkServerEncrypt()
{
	// TODO: 在此添加控件通知处理程序代码
	MG::ServerListenInfo* server = MG::SServerSetting::getInstance().getServerListenInfo();
	if (server)
	{
		I32 bValue = (server->isEncrypted) ? BST_CHECKED : BST_UNCHECKED;
		((CButton*)GetDlgItem(IDC_CK_SERVER_ENCRYPT))->SetCheck(bValue);
	}
}

void ServerSetTab::OnBnClickedCkClientEncrypt()
{
	// TODO: 在此添加控件通知处理程序代码
	MG::ServerListenInfo* client = MG::SServerSetting::getInstance().getServerListenInfo();
	if (client)
	{
		I32 bValue = (client->isEncrypted) ? BST_CHECKED : BST_UNCHECKED;
		((CButton*)GetDlgItem(IDC_CK_CLIENT_ENCRYPT))->SetCheck(bValue);
	}
}

void ServerSetTab::OnBnClickedCkAutoStart()
{
	// TODO: 在此添加控件通知处理程序代码
	MG::CoreInfo* core = MG::SServerSetting::getInstance().getCoreInfo();
	if (core)
	{
		I32 bValue = (core->isAutoStart) ? BST_CHECKED : BST_UNCHECKED;
		((CButton*)GetDlgItem(IDC_CK_AUTO_START))->SetCheck(bValue);
	}
}

void ServerSetTab::OnBnClickedCkSaveCoreLog()
{
	// TODO: 在此添加控件通知处理程序代码
	MG::CoreInfo* core = MG::SServerSetting::getInstance().getCoreInfo();
	if (core)
	{
		I32 bValue = (core->isWriteCoreLog) ? BST_CHECKED : BST_UNCHECKED;
		((CButton*)GetDlgItem(IDC_CK_SAVE_CORE_LOG))->SetCheck(bValue);
	}
}

void ServerSetTab::OnBnClickedCkSaveDbLog()
{
	// TODO: 在此添加控件通知处理程序代码
	MG::CoreInfo* core = MG::SServerSetting::getInstance().getCoreInfo();
	if (core)
	{
		I32 bValue = (core->isWriteDbLog) ? BST_CHECKED : BST_UNCHECKED;
		((CButton*)GetDlgItem(IDC_CK_SAVE_DB_LOG))->SetCheck(bValue);
	}
}

void ServerSetTab::OnBnClickedCkSaveShellLog()
{
	// TODO: 在此添加控件通知处理程序代码
	MG::CoreInfo* core = MG::SServerSetting::getInstance().getCoreInfo();
	if (core)
	{
		I32 bValue = (core->isWriteShellLog) ? BST_CHECKED : BST_UNCHECKED;
		((CButton*)GetDlgItem(IDC_CK_SAVE_SHELL_LOG))->SetCheck(bValue);
	}
}

void ServerSetTab::OnBnClickedCkCreatDb()
{
	// TODO: 在此添加控件通知处理程序代码
	MG::DbConnectInfo* Db = MG::SServerSetting::getInstance().getDbConnectInfo();
	if (Db)
	{
		I32 bValue = (Db->isCreate) ? BST_CHECKED : BST_UNCHECKED;
		((CButton*)GetDlgItem(IDC_CK_CREAT_DB))->SetCheck(bValue);
	}
}
