#pragma once
#include "TabPageSSL.h"
#include "afxwin.h"
#include "ReportCtrl.h"
// GThreadMsgTab dialog

class ThreadMsgTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(ThreadMsgTab)

public:
	ThreadMsgTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~ThreadMsgTab();

	// Dialog Data
	enum { IDD = IDD_LUANCHER_THREAD_DLG };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int			mSelfID;
	CReportCtrl	mList;
};
