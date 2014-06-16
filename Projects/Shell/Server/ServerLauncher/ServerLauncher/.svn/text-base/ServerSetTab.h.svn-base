#pragma once
#include "TabPageSSL.h"
#include "afxcmn.h"
#include "afxwin.h"

// ServerSetTab dialog

class ServerSetTab : public CTabPageSSL
{
	DECLARE_DYNAMIC(ServerSetTab)

public:
	ServerSetTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~ServerSetTab();

// Dialog Data
	enum { IDD = IDD_LAUNCHER_SETTING_DLG };
public:
	void loadSetting();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	int			mSelfID;
	CListCtrl	mList;
	CButton		mOpenBtn;
	CButton		mReloadBtn;
	afx_msg void OnBnClickedCkServerEncrypt();
	afx_msg void OnBnClickedCkClientEncrypt();
	afx_msg void OnBnClickedCkAutoStart();
	afx_msg void OnBnClickedCkSaveCoreLog();
	afx_msg void OnBnClickedCkSaveDbLog();
	afx_msg void OnBnClickedCkSaveShellLog();
	afx_msg void OnBnClickedCkCreatDb();
};
