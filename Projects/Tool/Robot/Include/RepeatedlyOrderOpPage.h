#pragma once


// CRepeatedlyOrderOpPage dialog

class CRepeatedlyOrderOpPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CRepeatedlyOrderOpPage)

public:
	CRepeatedlyOrderOpPage();
	virtual ~CRepeatedlyOrderOpPage();

// Dialog Data
	enum { IDD = IDD_DLG_REPEATEDLY_ORDER_OP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

public:
	void enableAllWindow(BOOL enable);
	void enableOp1(BOOL enable);

public:
	DECLARE_MESSAGE_MAP()
	
public:

	afx_msg void OnBnClickedChkAutojoingaemOrderOp1();
	afx_msg void OnBnClickedChkMoveOrderOp1();
	afx_msg void OnBnClickedChkCloseOrderOp1();

	afx_msg void OnBnClickedBtnOrderStartOp1();
	afx_msg void OnBnClickedBtnOrderEndOp1();

	afx_msg void OnBnClickedBtnOrderStart();
	
};
