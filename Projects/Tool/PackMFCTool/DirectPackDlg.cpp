// DirectPackDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PackMFCTool.h"
#include "DirectPackDlg.h"

#include "GameFilePackManager.h"
#include "MGPackToolManager.h"

#include "MGPackDefine.h"
#include "MGPackManager.h"
//#include "MGPackUpdateManager.h"
// CDirectPackDlg dialog

IMPLEMENT_DYNAMIC(CDirectPackDlg, CDialog)

CDirectPackDlg::CDirectPackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDirectPackDlg::IDD, pParent)
{

}

CDirectPackDlg::~CDirectPackDlg()
{
}

void CDirectPackDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_STARTZIP_BTN, mStartZipBtn);
	DDX_Control(pDX, IDC_SRC_BTN, mSrcDirBtn);
	DDX_Control(pDX, IDC_DES_BTN, mDesDirBtn);
	DDX_Control(pDX, IDC_SRC_TEXT, mSrcText);
	DDX_Control(pDX, IDC_DES_TEXT, mDesText);

	DDX_Control(pDX, IDC_SRCFOLDER_TREE, mSrcFolderTree);
	DDX_Control(pDX, IDC_DESTFOLDER_TREE, mDestFolderTree);

	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDirectPackDlg, CDialog)
	ON_BN_CLICKED(IDC_SRC_BTN, &CDirectPackDlg::OnSrcDirBtnClicked)
	ON_BN_CLICKED(IDC_DES_BTN, &CDirectPackDlg::OnDesDirBtnClicked)
	ON_BN_CLICKED(IDC_STARTZIP_BTN, &CDirectPackDlg::OnStartZipBtnClicked)
END_MESSAGE_MAP()

void CDirectPackDlg::OnSrcDirBtnClicked()
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
		mSrcDirStr.Format("%s", szDir);

		mSrcText.SetWindowText(mSrcDirStr);
		mSrcFolderTree.DisplayTree(mSrcDirStr, TRUE);
	}
}

void CDirectPackDlg::OnDesDirBtnClicked()
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
		mDesDirStr.Format("%s", szDir);
		mDesText.SetWindowText(mDesDirStr);

		mDestFolderTree.DisplayTree(mDesDirStr, TRUE);
	}
}

void CDirectPackDlg::OnStartZipBtnClicked()
{
	if (mSrcDirStr.IsEmpty())
	{
		AfxMessageBox("请选择源目录!");
		return;
	}

	if (mDesDirStr.IsEmpty())
	{
		AfxMessageBox("请选择目标目录!");
		return;
	}

	MG::MGPackToolManager *packManager = MG_NEW MG::MGPackToolManager();
	std::string srcstr, desstr;
	srcstr = mSrcDirStr.GetBuffer(0);
	desstr = mDesDirStr.GetBuffer(0);
	if (!packManager->packGameRes(srcstr, desstr))
	{
		AfxMessageBox("打包失败!");
	}
	else
	{
		AfxMessageBox("打包完成!");
	}

	MG_SAFE_DELETE(packManager);

	//MG::MGPackUpdateManager *packManager = MG_NEW MG::MGPackUpdateManager();
	//if (!packManager->resUpdate("res1/update/update.zip", "res1/upzip", "", "res1/tempGamefolder"))
	//	AfxMessageBox("失败!");
	//else
	//	AfxMessageBox("成功!");

	//MG_SAFE_DELETE(packManager);

}
// CDirectPackDlg message handlers
