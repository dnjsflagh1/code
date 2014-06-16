// GThreadMsgTab.cpp : implementation file
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "ThreadMsgTab.h"


// GThreadMsgTab dialog

IMPLEMENT_DYNAMIC(ThreadMsgTab, CDialog)

ThreadMsgTab::ThreadMsgTab(CWnd* pParent /*=NULL*/)
: CTabPageSSL(ThreadMsgTab::IDD, pParent)
{
}

ThreadMsgTab::~ThreadMsgTab()
{
}

void ThreadMsgTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LT_THREAD, mList);
}


BEGIN_MESSAGE_MAP(ThreadMsgTab, CTabPageSSL)
END_MESSAGE_MAP()


// GThreadMsgTab message handlers
BOOL ThreadMsgTab::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	mList.SetColumnHeader(L"TID, 50; Type, 40; Name, 180; Msg, 40; Stat, 40; CPU %, 50; MsgNum, 60; TimeDiff, 60;");
	mList.SetGridLines(TRUE);					// SHow grid lines
	mList.SetCheckboxeStyle(RC_CHKBOX_NONE);	// Enable checkboxes
	mList.SetEditable(FALSE);					// Allow sub-text edit
	mList.m_pClickFunc = NULL;
	return TRUE;
}
