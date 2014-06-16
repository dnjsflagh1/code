#pragma once
#include "FileSystemTreeCtrl.h"

// CDirectPackDlg dialog

class CDirectPackDlg : public CDialog
{
	DECLARE_DYNAMIC(CDirectPackDlg)

public:
	CDirectPackDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDirectPackDlg();

// Dialog Data
	enum { IDD = IDD_DIR_PACK_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnStartZipBtnClicked();

	afx_msg void OnSrcDirBtnClicked();
	afx_msg void OnDesDirBtnClicked();
	DECLARE_MESSAGE_MAP()

private:
	CButton mStartZipBtn;
	CButton	mSrcDirBtn;
	CButton mDesDirBtn;
	CStatic mSrcText;
	CStatic mDesText;

	CString mSrcDirStr;
	CString mDesDirStr;

	CFileSystemTreeCtrl	mSrcFolderTree;
	CFileSystemTreeCtrl	mDestFolderTree;
};
