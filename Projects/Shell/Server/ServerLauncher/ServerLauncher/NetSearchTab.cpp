// NetSearchTab.cpp : implementation file
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "NetSearchTab.h"
#include "ServerLauncherDlg.h"

extern char g_szWorkPath[MAX_PATH];
// NetSearchTab dialog

IMPLEMENT_DYNAMIC(NetSearchTab, CDialog)

NetSearchTab::NetSearchTab(CWnd* pParent /*=NULL*/)
: CTabPageSSL(NetSearchTab::IDD, pParent)
{
	mSelfID = 0;
}

NetSearchTab::~NetSearchTab()
{
}

void NetSearchTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NetSearchTab, CTabPageSSL)
END_MESSAGE_MAP()


// NetSearchTab message handlers
BOOL NetSearchTab::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	return TRUE;
}

