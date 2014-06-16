// GCoreMsgTab.cpp : implementation file
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "CoreMsgTab.h"


// GCoreMsgTab dialog

IMPLEMENT_DYNAMIC(CoreMsgTab, CDialog)

CoreMsgTab::CoreMsgTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(CoreMsgTab::IDD, pParent)
{
	mLastAddTime = 0;
	mCount = 0;
	mSelfID = 0;
}

CoreMsgTab::~CoreMsgTab()
{
}

void CoreMsgTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LTX_CORE_LOG, mMsgList);
}


BEGIN_MESSAGE_MAP(CoreMsgTab, CTabPageSSL)
END_MESSAGE_MAP()


// GCoreMsgTab message handlers
BOOL CoreMsgTab::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	mLastAddTime = 0;
	mCount = 0;

	return TRUE;
}

void CoreMsgTab::addMsg(CString str)
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

void CoreMsgTab::clear()
{
	mMsgList.ResetContent();
}
