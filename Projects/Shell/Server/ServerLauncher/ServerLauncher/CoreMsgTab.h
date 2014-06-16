#pragma once
#include "TabPageSSL.h"
#include "afxwin.h"

// GCoreMsgTab dialog

class CoreMsgTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(CoreMsgTab)

public:
	CoreMsgTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~CoreMsgTab();

// Dialog Data
	enum { IDD = IDD_LUANCHER_CORE_LOG_DLG };

	void addMsg(CString str);
	void clear();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int			mSelfID;
	CListBox	mMsgList;
	DWORD		mLastAddTime;
	int			mCount;
};
