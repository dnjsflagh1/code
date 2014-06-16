#pragma once
#include "resource.h"
// CLoginPage 对话框

class CLoginPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CLoginPage)

public:
	CLoginPage();
	virtual ~CLoginPage();

	virtual void OnFinalRelease();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN };
public:
	int			allocateIndex();
	void		releaseIndex(int index);
	CListCtrl*	getAccountLoginList();
	DWORD		getCurSelectCount();
	DWORD		getCurCheckCount();
    

	//
	static      MG::U32      mMapListId;
	static      MG::Int      mMapListType;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
private:
	CComboBox	mComboService;
	CComboBox	mComboClanSelect;
	CListCtrl	mAccountLoginList;
	CEdit		mEditAccountName;
	CEdit		mEditPassword;
	//CButton		mButtonAddAccount;
	CButton		mButtonDelAccount;
	CButton		mButtonNontReconnect;
	int			mMaxAccountCount;
	int			mMinAccountCount;
	bool		mUsedIndexFlag[ACCOUNT_MAXNUM+1];
public:
	afx_msg void OnBnClickedButtonAddAcount();
	afx_msg void OnBnClickedButtonDeleteAccount();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnBnClickedButtonAccountLogin();
	afx_msg void OnBnClickedButtonCreateClan();
	afx_msg void OnBnClickedButtonDelClan();
	afx_msg void OnBnClickedButtonCreateCharacter();
	afx_msg void OnBnClickedButtonDelCharacter();
	afx_msg void OnBnClickedButtonJoinGame();
	afx_msg void OnBnClickedButtonCloseAll();
	afx_msg void OnBnClickedButtonAutoJoinGame();
};
