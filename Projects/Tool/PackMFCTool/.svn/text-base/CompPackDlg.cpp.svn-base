// CompPackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PackMFCTool.h"
#include "CompPackDlg.h"

#include "GameFilePackManager.h"
#include "MGPackToolManager.h"
// CCompPackDlg dialog

IMPLEMENT_DYNAMIC(CCompPackDlg, CDialog)

CCompPackDlg::CCompPackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompPackDlg::IDD, pParent)
{

}

CCompPackDlg::~CCompPackDlg()
{
}

void CCompPackDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_COMPARE_BTN, mCompareCopyBtn);

	DDX_Control(pDX, IDC_LAST_RES_BTN, mLastResDirBtn);
	DDX_Control(pDX, IDC_NEW_RES_BTN, mNewResDirBtn);
	DDX_Control(pDX, IDC_PACK_RES_BTN, mPackResDirBtn);

	DDX_Control(pDX, IDC_LAST_RES_TEXT, mLastResText);
	DDX_Control(pDX, IDC_NEW_RES_TEXT, mNewResText);
	DDX_Control(pDX, IDC_PACK_RES_TEXT, mPackResText);

	DDX_Control(pDX, IDC_LASTRES_TREE, mlastResTree);
	DDX_Control(pDX, IDC_NEWRES_TREE, mnewResTree);
	DDX_Control(pDX, IDC_PACKRES_TREE, mpackResTree);

	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCompPackDlg, CDialog)
	ON_BN_CLICKED(IDC_LAST_RES_BTN, &CCompPackDlg::OnBnClickedLastResBtn)
	ON_BN_CLICKED(IDC_NEW_RES_BTN, &CCompPackDlg::OnBnClickedNewResBtn)
	ON_BN_CLICKED(IDC_COMPARE_BTN, &CCompPackDlg::OnBnClickedCompareBtn)
	ON_BN_CLICKED(IDC_PACK_RES_BTN, &CCompPackDlg::OnBnClickedPackResBtn)
END_MESSAGE_MAP()


// CCompPackDlg message handlers

void CCompPackDlg::OnBnClickedLastResBtn()
{
	char szDir[MAX_PATH];
	BROWSEINFO bi; 
	ITEMIDLIST *pidl; 

	bi.hwndOwner = this->m_hWnd; 
	bi.pidlRoot = NULL; 
	bi.pszDisplayName = szDir; 
	bi.lpszTitle = "请选择目录"; 
	bi.ulFlags = BIF_RETURNONLYFSDIRS; 
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi); 
	if(pidl == NULL) 
		return; 

	if(SHGetPathFromIDList(pidl, szDir))
	{
		mLastResDirStr.Format("%s", szDir);

		mLastResText.SetWindowText(mLastResDirStr);
		mlastResTree.DisplayTree(mLastResDirStr, TRUE);
	}
}

void CCompPackDlg::OnBnClickedNewResBtn()
{
	char szDir[MAX_PATH];
	BROWSEINFO bi; 
	ITEMIDLIST *pidl; 

	bi.hwndOwner = this->m_hWnd; 
	bi.pidlRoot = NULL; 
	bi.pszDisplayName = szDir; 
	bi.lpszTitle = "请选择目录"; 
	bi.ulFlags = BIF_RETURNONLYFSDIRS; 
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi); 
	if(pidl == NULL) 
		return; 

	if(SHGetPathFromIDList(pidl, szDir))
	{
		mNewResDirStr.Format("%s", szDir);

		mNewResText.SetWindowText(mNewResDirStr);
		mnewResTree.DisplayTree(mNewResDirStr, TRUE);
	}
}

void CCompPackDlg::OnBnClickedPackResBtn()
{
	char szDir[MAX_PATH];
	BROWSEINFO bi; 
	ITEMIDLIST *pidl; 

	bi.hwndOwner = this->m_hWnd; 
	bi.pidlRoot = NULL; 
	bi.pszDisplayName = szDir; 
	bi.lpszTitle = "请选择目录"; 
	bi.ulFlags = BIF_RETURNONLYFSDIRS; 
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	pidl = SHBrowseForFolder(&bi); 
	if(pidl == NULL) 
		return; 

	if(SHGetPathFromIDList(pidl, szDir))
	{
		mPackResDirStr.Format("%s", szDir);

		mPackResText.SetWindowText(mPackResDirStr);
		mpackResTree.DisplayTree(mPackResDirStr, TRUE);
	}
}

void CCompPackDlg::OnBnClickedCompareBtn()
{
	if (mLastResDirStr.IsEmpty())
	{
		AfxMessageBox("请选择上一版本资源目录!");
		return;
	}

	if (mNewResDirStr.IsEmpty())
	{
		AfxMessageBox("请选择新版本资源目录!");
		return;
	}

	if (mPackResDirStr.IsEmpty())
	{
		AfxMessageBox("请选择资源打包目录!");
		return;
	}

	MG::MGPackToolManager *packManager = MG_NEW MG::MGPackToolManager();
	std::string lastResstr, newResstr, packResstr;
	lastResstr = mLastResDirStr.GetBuffer(0);
	newResstr = mNewResDirStr.GetBuffer(0);
	packResstr = mPackResDirStr.GetBuffer(0);
	packManager->loadNewResFolder(newResstr.c_str());
	if (!packManager->compareAndCopy(lastResstr.c_str(), newResstr.c_str(), packResstr.c_str()))
	{
		AfxMessageBox("对比拷贝发生错误!");
	}
	else
	{
		AfxMessageBox("拷贝完成!");
	}

	MG_SAFE_DELETE(packManager);
}
