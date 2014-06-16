// DbMsgTab.cpp : implementation file
//

#include "stdafx.h"
#include "ServerLauncher.h"
#include "DbMsgTab.h"


// DbMsgTab dialog

IMPLEMENT_DYNAMIC(DbMsgTab, CDialog)

DbMsgTab::DbMsgTab(CWnd* pParent /*=NULL*/)
	: CTabPageSSL(DbMsgTab::IDD, pParent)
{
	mLastAddTime = 0;
	mCount = 0;
	mSelfID = 0;
}

DbMsgTab::~DbMsgTab()
{
}

void DbMsgTab::DoDataExchange(CDataExchange* pDX)
{
	CTabPageSSL::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LTX_DB_LOG, mMsgList);
}


BEGIN_MESSAGE_MAP(DbMsgTab, CTabPageSSL)
END_MESSAGE_MAP()


// DbMsgTab message handlers
BOOL DbMsgTab::OnInitDialog() 
{
	CTabPageSSL::OnInitDialog();
	mLastAddTime = 0;
	mCount = 0;

	return TRUE;
}

void DbMsgTab::addMsg(CString str)
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

void DbMsgTab::clear()
{
	mMsgList.ResetContent();
}
