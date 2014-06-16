#pragma once
#include "TabPageSSL.h"
#include "afxwin.h"

// DbMsgTab dialog

class DbMsgTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(DbMsgTab)

public:
	DbMsgTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~DbMsgTab();

// Dialog Data
	enum { IDD = IDD_LUANCHER_DB_LOG_DLG };

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
