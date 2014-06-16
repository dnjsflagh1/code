
// ClientLuancherDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ClientLuancher.h"
#include "ClientLuancherDlg.h"
#include "Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern std::string gAppPath;
// CClientLuancherDlg 对话框
BYTE* g_MemFileOpen(const char* fileName,int& nSize)
{
	string path = gAppPath;
	path += fileName;                     //CSV文件所在路径
	FILE* fp = fopen( path.c_str(), "rb" );
	if ( !fp ) 
	{
		return false;
	}

	fseek( fp, 0, SEEK_END );
	nSize = ftell( fp );
	fseek( fp, 0, SEEK_SET );

	if ( nSize == 0 ) {
		fclose( fp );
		return false;
	}
	BYTE* pData = (BYTE*)malloc( nSize	+ 1 );
	pData[nSize] = 0;
	fread(pData,nSize,1,fp);
	fclose(fp);
	return pData;
}

void g_MemFileClose(BYTE* pMemFile)
{
	free(pMemFile);
}


Memfile g_xMemFile = {g_MemFileOpen,g_MemFileClose};
UIConfig gUIConfig;


CClientLuancherDlg::CClientLuancherDlg(CWnd* pParent /*=NULL*/)
	: CRGNDlg(CClientLuancherDlg::IDD, pParent,"Update\\Dialog.Rgn")
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CClientLuancherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_1,				mBtnFreeRegistration);
	DDX_Control(pDX, IDC_BTN_2,				mBtnRecharge);
	DDX_Control(pDX, IDC_BTN_3,				mBtnOfficialWebsite);
	DDX_Control(pDX, IDC_BTN_4,				mBtnOfficialForum);
	DDX_Control(pDX, IDC_BTN_5,				mBtnGameSetting);
	DDX_Control(pDX, IDC_BTN_11,			mBtnDownload);
	DDX_Control(pDX, IDC_BTN_22,			mBtnVerCaption);
	DDX_Control(pDX, IDC_BTN_33,			mBtnGameRepair);
	DDX_Control(pDX, IDC_BTN_44,			mBtnManualUpdate);
	DDX_Control(pDX, IDC_BTN_START,			mBtnGameStart);
	DDX_Control(pDX, IDC_STATIC_CURR_VER,	mStaticCurrVer);
	DDX_Control(pDX, IDC_STATIC_NEW_VER,	mStaticNewVer);
	DDX_Control(pDX, IDC_STATIC_DESC,		mStaticVerDesc);
	DDX_Control(pDX, IDC_PROGRESS1,			mProcessCurr);
	DDX_Control(pDX, IDC_PROGRESS2,			mProcessAll);
	DDX_Control(pDX, IDCANCEL,				mBtnExit);
}

BEGIN_MESSAGE_MAP(CClientLuancherDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CClientLuancherDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CClientLuancherDlg::OnBnClickedBtnExit)
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_WM_NCHITTEST()
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_1, &CClientLuancherDlg::OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN_START, &CClientLuancherDlg::OnBnClickedBtnStart)
END_MESSAGE_MAP()


// CClientLuancherDlg 消息处理程序

BOOL CClientLuancherDlg::OnInitDialog()
{
	CRGNDlg::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	SetWindowText(L"英雄志");
	// TODO: 在此添加额外的初始化代码
	if(!gUIConfig.OpenUIConfig("Update//UIConfig.xml"))
	{
		PostMessage(WM_CLOSE,0,0);
		return FALSE;
	}
	//UICell* pCell = gUIConfig.GetUIConfig("MainDlg");
	//if(pCell != NULL)
	//{
	//	SetTransparent(TRUE);
	//	SetStaticTransparent(false);
	//	SetTransColor(pCell->m_xBackgroundColor);
	//	LoadBitmapFromFile(pCell->m_szPicName,g_xMemFile);
	//	SetStaticTransparent (TRUE);
	//	SetClickAnywhereMove (TRUE);
	//}
	InitCtrlPos();
	SetTimer(1,1000,NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientLuancherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRGNDlg::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientLuancherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CClientLuancherDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
}

void CClientLuancherDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
}

void CClientLuancherDlg::InitCtrlPos()
{
	//CenterWindow();
	RECT rect;
	GetClientRect(&rect);
	ScreenToClient(&rect);

	UICell* pCell = gUIConfig.GetUIConfig("ProgressCur");
	if(pCell != NULL)
	{
		mProcessCurr.MoveWindow(pCell->m_rcPosInWnd);
		mProcessCurr.SetBitmapBarFromFile(pCell->m_szPicName,g_xMemFile,pCell->m_xBackgroundColor);
		if(pCell->m_szBkgndPicName != NULL)
			mProcessCurr.SetBitmapBkgndFromFile(pCell->m_szBkgndPicName,g_xMemFile,pCell->m_xBackgroundColor);
		mProcessCurr.SetPoint(100);
		mProcessCurr.SetRange(100);
	}
	pCell = gUIConfig.GetUIConfig("ProgressAll");
	if(pCell != NULL)
	{
		mProcessAll.MoveWindow(pCell->m_rcPosInWnd);
		mProcessAll.SetBitmapBarFromFile(pCell->m_szPicName,g_xMemFile,pCell->m_xBackgroundColor);
		if(pCell->m_szBkgndPicName != NULL)
			mProcessAll.SetBitmapBkgndFromFile(pCell->m_szBkgndPicName,g_xMemFile,pCell->m_xBackgroundColor);
		mProcessAll.SetPoint(100);
		mProcessAll.SetRange(100);
	}

	pCell = gUIConfig.GetUIConfig("BtnFreeRegistration");
	if(pCell != NULL)
	{
		mBtnFreeRegistration.MoveWindow(pCell->m_rcPosInWnd);
		mBtnFreeRegistration.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnFreeRegistration.EnableWindow(TRUE);
		mBtnFreeRegistration.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("BtnRecharge");
	if(pCell != NULL)
	{
		mBtnRecharge.MoveWindow(pCell->m_rcPosInWnd);
		mBtnRecharge.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnRecharge.EnableWindow(TRUE);
		mBtnRecharge.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("BtnOfficialWebsite");
	if(pCell != NULL)
	{
		mBtnOfficialWebsite.MoveWindow(pCell->m_rcPosInWnd);
		mBtnOfficialWebsite.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnOfficialWebsite.EnableWindow(TRUE);
		mBtnOfficialWebsite.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("BtnOfficialForum");
	if(pCell != NULL)
	{
		mBtnOfficialForum.MoveWindow(pCell->m_rcPosInWnd);
		mBtnOfficialForum.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnOfficialForum.EnableWindow(TRUE);
		mBtnOfficialForum.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("BtnGameSetting");
	if(pCell != NULL)
	{
		mBtnGameSetting.MoveWindow(pCell->m_rcPosInWnd);
		mBtnGameSetting.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnGameSetting.EnableWindow(TRUE);
		mBtnGameSetting.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("BtnDownload");
	if(pCell != NULL)
	{
		mBtnDownload.MoveWindow(pCell->m_rcPosInWnd);
		mBtnDownload.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnDownload.EnableWindow(TRUE);
		mBtnDownload.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("BtnVerCaption");
	if(pCell != NULL)
	{
		mBtnVerCaption.MoveWindow(pCell->m_rcPosInWnd);
		mBtnVerCaption.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnVerCaption.EnableWindow(TRUE);
		mBtnVerCaption.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("BtnGameRepair");
	if(pCell != NULL)
	{
		mBtnGameRepair.MoveWindow(pCell->m_rcPosInWnd);
		mBtnGameRepair.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnGameRepair.EnableWindow(TRUE);
		mBtnGameRepair.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("BtnManualUpdate");
	if(pCell != NULL)
	{
		mBtnManualUpdate.MoveWindow(pCell->m_rcPosInWnd);
		mBtnManualUpdate.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnManualUpdate.EnableWindow(TRUE);
		mBtnManualUpdate.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("BtnGameStart");
	if(pCell != NULL)
	{
		mBtnGameStart.MoveWindow(pCell->m_rcPosInWnd);
		mBtnGameStart.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor);
		mBtnGameStart.EnableWindow(TRUE);
		mBtnGameStart.ShowWindow(SW_SHOW);
	}
	
	pCell = gUIConfig.GetUIConfig("BtnExit");
	if(pCell != NULL)
	{
		mBtnExit.MoveWindow(pCell->m_rcPosInWnd);
		mBtnExit.SetBitmapsByFile(pCell->m_szPicName,g_xMemFile,
			&pCell->m_rcOffsetInImg[btn_disable],
			&pCell->m_rcOffsetInImg[btn_mouseout],
			&pCell->m_rcOffsetInImg[btn_mousein],
			&pCell->m_rcOffsetInImg[btn_mousedown],pCell->m_xBackgroundColor,TRUE);
		mBtnExit.EnableWindow(TRUE);
		mBtnExit.ShowWindow(SW_SHOW);
	}
	pCell = gUIConfig.GetUIConfig("StaticCurrVer");
	if(pCell != NULL)
	{
		/*mStaticCurrVer.MoveWindow(pCell->m_rcPosInWnd);
		mStaticCurrVer.SetViewString(L"当前版本1.0.0");
		mStaticCurrVer.SetColor(pCell->m_xKeyColor);
		mStaticCurrVer.ShowWindow(SW_HIDE);
		mStaticCurrVer.ShowWindow(SW_SHOW);*/
		mStaticCurrVer.SetWindowPos(NULL,pCell->m_rcPosInWnd.left,pCell->m_rcPosInWnd.top,pCell->m_rcPosInWnd.Width(),pCell->m_rcPosInWnd.Height(),SWP_NOACTIVATE);
	}
	pCell = gUIConfig.GetUIConfig("StaticNewVer");
	if(pCell != NULL)
	{
		/*mStaticNewVer.MoveWindow(pCell->m_rcPosInWnd);
		mStaticCurrVer.SetViewString(L"最新版本1.0.0");
		mStaticNewVer.SetColor(pCell->m_xKeyColor);
		mStaticCurrVer.ShowWindow(SW_HIDE);
		mStaticNewVer.ShowWindow(SW_SHOW);*/
		mStaticNewVer.SetWindowPos(NULL,pCell->m_rcPosInWnd.left,pCell->m_rcPosInWnd.top,pCell->m_rcPosInWnd.Width(),pCell->m_rcPosInWnd.Height(),SWP_NOACTIVATE);
	}
	pCell = gUIConfig.GetUIConfig("StaticVerDesc");
	if(pCell != NULL)
	{
		/*mStaticVerDesc.MoveWindow(pCell->m_rcPosInWnd);
		mStaticCurrVer.SetViewString(L"已是最新版本");
		mStaticVerDesc.SetColor(pCell->m_xKeyColor);
		mStaticCurrVer.ShowWindow(SW_HIDE);
		mStaticVerDesc.ShowWindow(SW_SHOW);*/
		mStaticVerDesc.SetWindowPos(NULL,pCell->m_rcPosInWnd.left,pCell->m_rcPosInWnd.top,pCell->m_rcPosInWnd.Width(),pCell->m_rcPosInWnd.Height(),SWP_NOACTIVATE);
	}
	pCell = gUIConfig.GetUIConfig("WebNews");
	if (pCell != NULL)
	{
		//mExplorer.Create(NULL,WS_CHILD|WS_VISIBLE|BS_BITMAP,pCell->m_rcPosInWnd,this,0);
		mExplorer.Create(NULL,WS_CHILD|WS_VISIBLE|BS_BITMAP,pCell->m_rcPosInWnd,this,0);
		UpdateExplorer();
	}
}
void CClientLuancherDlg::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	DestroyWindow();
}

HBRUSH CClientLuancherDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CRGNDlg::OnCtlColor(pDC, pWnd, nCtlColor);

	//// TODO:  Change any attributes of the DC here
	//if ((nCtlColor == CTLCOLOR_STATIC)||(nCtlColor == CTLCOLOR_EDIT) ) 
	//{
	//	pDC->SetBkMode(TRANSPARENT); 
	//	//		pDC->SetTextColor(RGB(255,255,150)); 
	//	return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	//}
	switch(pWnd->GetDlgCtrlID()) 
	{ 
	case IDC_STATIC_NEW_VER:
	case IDC_STATIC_DESC:
	case IDC_STATIC_CURR_VER: 
	case IDC_BTN_1:
	case IDC_BTN_2:
	case IDC_BTN_3:
	case IDC_BTN_4:
	case IDC_BTN_5:
	case IDC_BTN_11:
	case IDC_BTN_22:
	case IDC_BTN_33:
	case IDC_BTN_44:
		pDC->SetBkMode(TRANSPARENT); 
		pDC->SetTextColor(RGB(255,255,255)); 
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);

default: 
	break; 
	} 

	return hbr;	
}

void CClientLuancherDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//CSkinDialog::OnClose();
}

LRESULT CClientLuancherDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	LRESULT nHitTest = CDialog::OnNcHitTest(point);
	return (nHitTest==HTCLIENT)?HTCAPTION:nHitTest;
}

void CClientLuancherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnSysCommand(nID, lParam);
}

void CClientLuancherDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (theApp.mIsRun == true )
	{
		if (theApp.mGameThread.getHandle() == NULL)
		{
			exit(0);
		}
		else
		{
			DWORD exitCode;
			GetExitCodeThread(theApp.mGameThread.getHandle(),&exitCode);
			if (exitCode != STILL_ACTIVE)
			{
				exit(0);
			}
		}
	
	}

	CDialog::OnTimer(nIDEvent);
}

void CClientLuancherDlg::OnBnClickedBtn1()
{
	// TODO: Add your control notification handler code here
}

void CClientLuancherDlg::OnBnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	//gAppPath
//#ifdef _DEBUG
//	ShellExecuteA(NULL,"open","MGTestShell_d.exe",NULL,gAppPath.c_str(),SW_SHOW);
//#else
//	ShellExecuteA(NULL,"open","MGTestShell.exe",NULL,gAppPath.c_str(),SW_SHOW);
//#endif
	theApp.mGameThread.create(CClientLuancherApp::gameThread,&theApp);
	//ShowWindow(SW_HIDE); 
	mBtnGameStart.EnableWindow(FALSE);
	//DestroyWindow();
}

void CClientLuancherDlg::UpdateExplorer()
{
		WCHAR dir[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, dir);
		std::wstring final = dir;
		final += L"\\HtmlSurface1.htm";
		FILE* fp = _wfopen(final.c_str(), L"wt");
		if (fp)
		{
			::fprintf(fp, "<html>\n");
			::fprintf(fp, "<FRAMESET COLS=\"100%\" frameborder=\"NO\" border=\"0\" framespacing=\"0\" style=\"border:2px #000000 solid\">\n");

			::fprintf(fp, "<FRAME SRC=\"%s\"\n", "http://cms2.kx1d.com/html/yxz/yxz_news/");// &lt;--- string contain the URL u want to display
			::fprintf(fp, "name=\"DisplayManager\" SCROLLING=\"NO\">\n</FRAMESET>\n");
			::fprintf(fp, "</html>\n");
			::fclose(fp);
			mExplorer.Navigate(final.c_str(), NULL,NULL,NULL,NULL);
		}
}