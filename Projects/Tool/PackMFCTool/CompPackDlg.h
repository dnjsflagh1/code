#pragma once
#include "FileSystemTreeCtrl.h"

// CCompPackDlg dialog

class CCompPackDlg : public CDialog
{
	DECLARE_DYNAMIC(CCompPackDlg)

public:
	CCompPackDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCompPackDlg();

// Dialog Data
	enum { IDD = IDD_COMP_PACK_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CButton mCompareCopyBtn;
	
	CButton	mLastResDirBtn;
	CButton mNewResDirBtn;
	CButton mPackResDirBtn;

	CStatic mLastResText;
	CStatic mNewResText;
	CStatic mPackResText;

	CString mLastResDirStr;
	CString mNewResDirStr;
	CString mPackResDirStr;

	CFileSystemTreeCtrl	mlastResTree;
	CFileSystemTreeCtrl	mnewResTree;
	CFileSystemTreeCtrl	mpackResTree;
public:
	afx_msg void OnBnClickedLastResBtn();
	afx_msg void OnBnClickedNewResBtn();
	afx_msg void OnBnClickedPackResBtn();

	afx_msg void OnBnClickedCompareBtn();
};
