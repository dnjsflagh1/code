// ShellMsgTab.cpp : implementation file
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "ShellMsgTab.h"


// ShellMsgTab dialog

IMPLEMENT_DYNAMIC(ShellMsgTab, CDialog)

ShellMsgTab::ShellMsgTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(ShellMsgTab::IDD, pParent)
{
	mLastAddTime = 0;
	mCount = 0;
	mSelfID = 0;
}

ShellMsgTab::~ShellMsgTab()
{
}

void ShellMsgTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LTX_SHELL_LOG, mMsgList);
}


BEGIN_MESSAGE_MAP(ShellMsgTab, CTabPageSSL)
END_MESSAGE_MAP()


// ShellMsgTab message handlers
BOOL ShellMsgTab::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	mLastAddTime = 0;
	mCount = 0;

	return TRUE;
}

void ShellMsgTab::addMsg(CString str)
{
	DWORD curr = ::GetTickCount();
	if (curr - mLastAddTime < 5)
	{
		if (++mCount < 30)
		{
			if (mMsgList.GetCount() > 200)
				clear();
			mMsgList.AddString(str);
		}
	}
	else 
	{
		if (mMsgList.GetCount() > 200)
			clear();
		mMsgList.AddString(str);
		if (--mCount < 0) // 减少过快的消息的累积
			mCount = 0;		
	}
}

void ShellMsgTab::clear()
{
	mMsgList.ResetContent();
}
