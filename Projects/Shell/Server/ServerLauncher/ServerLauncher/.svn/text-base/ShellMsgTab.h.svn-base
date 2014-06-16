#pragma once
#include "TabPageSSL.h"
#include "afxwin.h"

// ShellMsgTab dialog

class ShellMsgTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(ShellMsgTab)

public:
	ShellMsgTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~ShellMsgTab();

// Dialog Data
	enum { IDD = IDD_LUANCHER_SHELL_LOG_DLG };

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
