
// PackMFCToolDlg.h : header file
//

#pragma once

#include "DirectPackDlg.h"
#include "CompPackDlg.h"


// CPackMFCToolDlg dialog
class CPackMFCToolDlg : public CDialog
{
// Construction
public:
	CPackMFCToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PACKMFCTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CTabCtrl mTabCtrl;

	CDirectPackDlg  mDirectPackDlg;
	CCompPackDlg  mComparePackDlg;


public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
