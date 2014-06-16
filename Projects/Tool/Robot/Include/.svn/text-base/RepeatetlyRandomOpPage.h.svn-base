#pragma once


// CRepeatetlyRandomOpPage dialog

class CRepeatetlyRandomOpPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CRepeatetlyRandomOpPage)

public:
	CRepeatetlyRandomOpPage();
	virtual ~CRepeatetlyRandomOpPage();

// Dialog Data
	enum { IDD = IDD_DLG_REPEATEDLY_RANDOM_OP };

public:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

public:
	void	enableAllWindow(BOOL enable);
	void	enableOp1(BOOL enable);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedChkRandomMoveOp1();
	afx_msg void OnBnClickedBtnRmStartOp1();
	afx_msg void OnBnClickedBtnRmEndOp1();
	afx_msg void OnBnClickedBtnRmStart();
};
