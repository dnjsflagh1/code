#pragma once
#include "TabPageSSL.h"
#include "afxwin.h"
#include "NetAddress.h"
// ServerStatusTab dialog
using namespace MG;

struct LuanchServerInfo
{
	MG::NetAddress	addr;
	I32			index;
};
class ServerStatusTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(ServerStatusTab)

public:
	ServerStatusTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~ServerStatusTab();

// Dialog Data
	enum { IDD = IDD_LUANCHER_NET_STATES_DLG };
	
	void onServerChangeState(MG::Char16* name, MG::Bool inAcceptList, MG::Bool isConnected);
	void onServerConnect(MG::Char16* name,MG::NetAddress &addr);
	void onServerDisconnect(MG::U64 uin);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int			mSelfID;
	CListCtrl	mListConnect;
	CListCtrl	mListAccept;

private:
	std::map< Str16, LuanchServerInfo> mConnectServers;
	std::map< Str16, LuanchServerInfo> mAcceptServers;

	MG::I32 _getAcceptServerIndex(MG::CChar16* serverName);
	MG::I32 _getConnectServerIndex(MG::CChar16* serverName);
	MG::I32 _getAcceptServerIndex(MG::U64 uin);
	MG::I32 _getConnectServerIndex(MG::U64 uin);

};
