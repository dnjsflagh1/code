#pragma once


// COnceOpPage dialog

class COnceOpPage : public CPropertyPage
{
	DECLARE_DYNAMIC(COnceOpPage)

public:
	COnceOpPage();
	virtual ~COnceOpPage();

// Dialog Data
	enum { IDD = IDD_DLG_ONCE_OP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL OnInitDialog();
public:
	void	enableAllWindow(BOOL enable);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnStartOnceOp();
	afx_msg void OnBnClickedBtnConnectLogin();
	afx_msg void OnBnClickedBtnSenddataToLogin();
	afx_msg void OnBnClickedBtnLoginLogin();
	afx_msg void OnBnClickedBtnConnectFront();
	afx_msg void OnBnClickedBtnSenddataToFront();
	afx_msg void OnBnClickedBtnLoginFront();
	afx_msg void OnBnClickedBtnCreateCan();
	afx_msg void OnBnClickedBtnDelClan();
	afx_msg void OnBnClickedBtnCreateCharachter();
	afx_msg void OnBnClickedBtnAccountLogin();
	afx_msg void OnBnClickedBtnJiongame();
	afx_msg void OnBnClickedBtnAutoJoingame();
	afx_msg void OnBnClickedBtnCloseNet();
	afx_msg void OnBnClickedBtnCreateCamp();
	afx_msg void OnBnClickedBtnRandomMove();
};
