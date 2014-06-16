#pragma once


// CSettingPage dialog

class CSettingPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSettingPage)
public:
	// Dialog Data
	enum { IDD = IDD_DLG_SETTING };

public:
	CSettingPage();
	virtual ~CSettingPage();
	
	virtual	BOOL OnInitDialog();


	int			allocateIndex();
	void		releaseIndex( int index );





protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSetsetting();

private:
	CListCtrl	mAccountLoginList;
	bool		mUsedIndexFlag[ACCOUNT_MAXNUM+1];
public:
	afx_msg void OnBnClickedBtnReflash();
};
