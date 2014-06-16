
// PackMFCToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PackMFCTool.h"
#include "PackMFCToolDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPackMFCToolDlg dialog
CPackMFCToolDlg::CPackMFCToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPackMFCToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPackMFCToolDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TAB1,mTabCtrl);
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPackMFCToolDlg, CDialog)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CPackMFCToolDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CPackMFCToolDlg message handlers

BOOL CPackMFCToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	mTabCtrl.InsertItem(0, "对比打包");
	mTabCtrl.InsertItem(1, "直接打包");

	mDirectPackDlg.Create(IDD_DIR_PACK_DLG, &mTabCtrl);
	mComparePackDlg.Create(IDD_COMP_PACK_DLG, &mTabCtrl);

	CRect rc;
	::GetClientRect(::GetDlgItem(m_hWnd, IDC_TAB1), &rc);
	rc.top += 21;
	rc.bottom -= 8;
	rc.left += 8;
	rc.right -= 8;

	mDirectPackDlg.MoveWindow(&rc);
	mComparePackDlg.MoveWindow(&rc);

	mDirectPackDlg.ShowWindow(SW_HIDE);
	mComparePackDlg.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPackMFCToolDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	switch(mTabCtrl.GetCurSel())
	{
	case 0:
		mDirectPackDlg.ShowWindow(SW_HIDE);
		mComparePackDlg.ShowWindow(SW_SHOW);
		break;
	case 1:
		mComparePackDlg.ShowWindow(SW_HIDE);
		mDirectPackDlg.ShowWindow(SW_SHOW);
		break;
	}
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
