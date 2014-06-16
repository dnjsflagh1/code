// ServerStatusTab.cpp : implementation file
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "ServerStatusTab.h"
#include "ServerLauncherDlg.h"


// ServerStatusTab dialog

IMPLEMENT_DYNAMIC(ServerStatusTab, CDialog)

ServerStatusTab::ServerStatusTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(ServerStatusTab::IDD, pParent)
{
	mSelfID = 0;
}

ServerStatusTab::~ServerStatusTab()
{
}

void ServerStatusTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LT_ACCEPT, mListAccept);
	DDX_Control(pDX, IDC_LT_CONNECT, mListConnect);
}


BEGIN_MESSAGE_MAP(ServerStatusTab, CDialog)
END_MESSAGE_MAP()


// ServerStatusTab message handlers
BOOL ServerStatusTab::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();

	DWORD style = GetWindowLong(mListAccept.GetSafeHwnd(), GWL_STYLE);
	SetWindowLong(mListAccept.GetSafeHwnd(), GWL_STYLE,style|LVS_REPORT|LVS_NOLABELWRAP|LVS_SHOWSELALWAYS);
	mListAccept.InsertColumn(0, L"ServerName", LVCFMT_CENTER, 160);
	mListAccept.InsertColumn(1, L"IP", LVCFMT_CENTER, 110);
	mListAccept.InsertColumn(2, L"PORT", LVCFMT_CENTER, 90);
	mListAccept.InsertColumn(3, L"Status", LVCFMT_CENTER, 100);

	style = GetWindowLong(mListConnect.GetSafeHwnd(), GWL_STYLE);
	SetWindowLong(mListConnect.GetSafeHwnd(), GWL_STYLE,style|LVS_REPORT|LVS_NOLABELWRAP|LVS_SHOWSELALWAYS);
	mListConnect.InsertColumn(0, L"ServerName", LVCFMT_CENTER, 160);
	mListConnect.InsertColumn(1, L"IP", LVCFMT_CENTER, 110);
	mListConnect.InsertColumn(2, L"PORT", LVCFMT_CENTER, 90);
	mListConnect.InsertColumn(3, L"Status", LVCFMT_CENTER, 100);

	MG::ConnectServerCollection* servers = MG::SServerSetting::getInstance().getConnectServers();
	if (servers)
	{	
		Str16 str;
		std::map<MG::U64, MG::ConnectRemoteInfo*>::iterator it = servers->connectServers.begin();
		for (int i = 0; it !=  servers->connectServers.end(); it++,i++)
		{
			LuanchServerInfo info;
			info.addr = it->second->addr;
			info.index = i;
			mConnectServers[it->second->name] = info;
			mListConnect.InsertItem(i, it->second->name.c_str());
			MG::MGStrOp::toString(it->second->addr.getIPStrA(),str);
			mListConnect.SetItemText(i, 1,str.c_str());
#if MG_WCHAR_T_STRINGS
			mListConnect.SetItemText(i ,2, it->second->addr.getPortStr());
#else
			MG::MGStrOp::toString(it->second->addr.getPortStr(),str);
			mListConnect.SetItemText(i ,2, str.c_str());
#endif		
			mListConnect.SetItemText(i, 3, L"0");
		}
	}


	return TRUE;
}


void ServerStatusTab::onServerChangeState( MG::Char16* name, MG::Bool inAcceptList ,MG::Bool isConnect )
{
	if (inAcceptList)
	{
		MG::I32 index = _getAcceptServerIndex(name);
		if (index != -1)
		{
			if (isConnect)
			{
				mListAccept.SetItemText(index, 3, L"1");
			}
			else
			{
				mListAccept.SetItemText(index, 3, L"0");
			}
		}
	}
	else
	{
		MG::I32 index = _getConnectServerIndex(name);
		if (index != -1)
		{
			if (isConnect)
			{
				mListConnect.SetItemText(index, 3, L"1");
			}
			else
			{
				mListConnect.SetItemText(index, 3, L"0");
			}
		}
	}
}

MG::I32 ServerStatusTab::_getAcceptServerIndex(MG::CChar16* serverName)
{
	std::map< MG::Str16, LuanchServerInfo>::iterator it = mAcceptServers.find(serverName);
	if (it != mAcceptServers.end())
	{
		return it->second.index;
	}
	return -1;
}

MG::I32 ServerStatusTab::_getAcceptServerIndex( MG::U64 uin )
{
	std::map< MG::Str16, LuanchServerInfo>::iterator it = mAcceptServers.begin();
	for (; it != mAcceptServers.end(); it++)
	{
		if (it->second.addr.getUin() == uin)
		{
			return it->second.index;
		}
	}
	return -1;
}

MG::I32 ServerStatusTab::_getConnectServerIndex(CChar16* serverName)
{
	std::map< MG::Str16, LuanchServerInfo>::iterator it = mConnectServers.find(serverName);
	if (it != mConnectServers.end())
	{
		return it->second.index;
	}
	return -1;

}

MG::I32 ServerStatusTab::_getConnectServerIndex( U64 uin )
{
	std::map< MG::Str16, LuanchServerInfo>::iterator it = mConnectServers.begin();
	for (; it != mConnectServers.end(); it++)
	{
		if (it->second.addr.getUin() == uin)
		{
			return it->second.index;
		}
	}
	return -1;
}

void ServerStatusTab::onServerConnect( Char16* name,MG::NetAddress &addr )
{
	MG::I32 index = _getConnectServerIndex(name);
	if (index == -1)
	//不是connect
	{
		index = _getAcceptServerIndex(name);
		if (index == -1)
		{
			index = mAcceptServers.size();
			LuanchServerInfo info;
			info.addr = addr;
			info.index = index;
			mAcceptServers[name] = info;
			MG::Str16 str;
			mListAccept.InsertItem(index,name);
			MG::MGStrOp::toString(addr.getIPStrA(),str);
			mListAccept.SetItemText(index, 1,str.c_str());
#if MG_WCHAR_T_STRINGS
			mListAccept.SetItemText(index ,2, addr.getPortStr());
#else
			MG::MGStrOp::toString(addr.getPortStr(),str);
			mListAccept.SetItemText(index ,2, str.c_str());
#endif		
			mListAccept.SetItemText(index, 3, L"1");
		}
		else
		{
			LuanchServerInfo info;
			info.addr = addr;
			info.index = index;
			mAcceptServers[name] = info;
			MG::Str16 str;
			MG::MGStrOp::toString(addr.getIPStrA(),str);
			mListAccept.SetItemText(index, 1,str.c_str());
#if MG_WCHAR_T_STRINGS
			mListAccept.SetItemText(index ,2, addr.getPortStr());
#else
			MG::MGStrOp::toString(addr.getPortStr(),str);
			mListAccept.SetItemText(index ,2, str.c_str());
#endif		
			mListAccept.SetItemText(index, 3, L"1");
		}
	}
	else
	{
		mListConnect.SetItemText(index, 3, L"1");
	}
	
}

void ServerStatusTab::onServerDisconnect( U64 uin )
{
	MG::I32 index = _getConnectServerIndex(uin);
	if (index == -1)
		//不是connect
	{
		index = _getAcceptServerIndex(uin);
		//DYNAMIC_ASSERT(index != -1);
		if (index != -1)
		{
			mListAccept.SetItemText(index, 3, L"0");
		}
	}
	else
	{
		mListConnect.SetItemText(index, 3, L"0");
	}
}
