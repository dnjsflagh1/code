// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
//#include "LoginPage.h"
#include "ItemView.h"
#include "MainView.h"
#include "MainFrm.h"
#include "NewMainView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)
//-----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	// 全局帮助命令
	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	ON_WM_GETMINMAXINFO()
	ON_WM_CLOSE()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
// CMainFrame 构造/析构
CMainFrame::CMainFrame()
{
}
//-----------------------------------------------------------------------------
CMainFrame::~CMainFrame()
{
}
//-----------------------------------------------------------------------------
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	//// create a splitter with 1 row, 2 columns
	//if (!mWndSplitter.CreateStatic(this , 1, 2))
	//{
	//	MG::LogSystem::getInstance().log(MG::out_error,"Failed to CreateStaticSplitter\n");
	//	return FALSE;
	//}

	//// add the first splitter pane - the default view in column 0
	//if (!mWndSplitter.CreateView(0, 0,
	//	RUNTIME_CLASS(CItemView), CSize(200, 0), pContext))
	//{
	//	MG::LogSystem::getInstance().log(MG::out_error,"Failed to create first pane\n");
	//	return FALSE;
	//}

	//// add the second splitter pane - an input view in column 1
	//if (!mWndSplitter.CreateView(0, 1,
	//	RUNTIME_CLASS(CMainView), CSize(300, 0), pContext))
	//{
	//	MG::LogSystem::getInstance().log(MG::out_error,"Failed to create second pane\n");
	//	return FALSE;
	//}

	//mWndSplitter.SetColumnInfo(0, 240, 200);
	//mWndSplitter.SetColumnInfo(1, 540, 500);
	//mWndSplitter.RecalcLayout();

	//mItemView = (CItemView*)mWndSplitter.GetPane(0,0);
	//mMainView = (CMainView*)mWndSplitter.GetPane(0,1);
	//mItemView->initView();
	//mMainView->initView();
	//SetTimer(1,800,NULL);


	// create a splitter with 1 row, 2 columns
	if (!mWndSplitter.CreateStatic(this , 2, 1))
	{
		MG::LogSystem::getInstance().log(MG::out_error,"Failed to CreateStaticSplitter\n");
		return FALSE;
	}
	if (!mWndSplitter.CreateView(0, 0,
		RUNTIME_CLASS(CNewMainView), CSize(0, 0), pContext))
	{
		MG::LogSystem::getInstance().log(MG::out_error,"Failed to create first pane\n");
		return FALSE;
	}
	if (!mWndSplitter.CreateView(1, 0,
		RUNTIME_CLASS(CNewMainView), CSize(700, 540), pContext))
	{
		MG::LogSystem::getInstance().log(MG::out_error,"Failed to create first pane\n");
		return FALSE;
	}
	mWndSplitter.SetRowInfo(0, 500, 450);
	mWndSplitter.SetRowInfo(1, 0, 0);
	
	mWndSplitter.RecalcLayout();
	mNewMainView	= (CNewMainView*)mWndSplitter.GetPane(0,0);
	mNewMainView->initView();

	return CFrameWnd::OnCreateClient(lpcs,pContext);
}
//-----------------------------------------------------------------------------
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}
//-----------------------------------------------------------------------------
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式
	cs.style 		&= ~ WS_MAXIMIZEBOX;
	cs.dwExStyle 	&= ~WS_EX_CLIENTEDGE;

	//cs.style = DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_SYSMENU;

	cs.cy = ::GetSystemMetrics(SM_CYSCREEN) * 3 / 4;
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN) * 3 / 4;
	//设置窗口位置 (居中)
	cs.y = (cs.cy*4/3 - cs.cy) / 2;
	cs.x = (cs.cx*4/3 - cs.cx) / 2;

	cs.lpszClass	= AfxRegisterWndClass(0);
	cs.cx			= 700;
	cs.cy			= 540;


	return TRUE;
}
//-----------------------------------------------------------------------------
// CMainFrame 诊断
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}
//-----------------------------------------------------------------------------
void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG
//-----------------------------------------------------------------------------

// CMainFrame 消息处理程序
void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// 将焦点前移到视图窗口
	//m_wndView.SetFocus();
}
//-----------------------------------------------------------------------------
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO  *info)
{
	
}
//-----------------------------------------------------------------------------
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// 让视图第一次尝试该命令
	//if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		//return TRUE;

	// 否则，执行默认处理
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
//-----------------------------------------------------------------------------
CItemView*	CMainFrame::GetItemView()
{
	return mItemView;
}
//-----------------------------------------------------------------------------
CLoginPage* CMainFrame::GetLoginPage()
{
	return &(mItemView->mLoginPage);
}
//-----------------------------------------------------------------------------
void CMainFrame::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	CFrameWnd::OnClose();
}
//-----------------------------------------------------------------------------
LRESULT CMainFrame::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	UINT ret=CFrameWnd::OnNcHitTest(point);
	if (ret==HTRIGHT || ret==HTLEFT || ret==HTTOP || ret==HTBOTTOM || 
		ret==HTTOPLEFT || ret==HTBOTTOMRIGHT || ret==HTBOTTOMLEFT || ret==HTTOPRIGHT)
	{
		return HTCLIENT;
	}
	return ret;
}
//-----------------------------------------------------------------------------
void CMainFrame::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==1)
	{
		//g_AutoPublishMgr.Run();
	}
	CFrameWnd::OnTimer(nIDEvent);
}

CCampaignPage* CMainFrame::GetCampaignPage()
{
	return &mItemView->mCampaignPage;
}
//-----------------------------------------------------------------------------
CNewMainView* CMainFrame::GetNewView()
{
	return mNewMainView;
}

COnceOpPage* CMainFrame::GetOnceOpPage()
{
	return &mNewMainView->mOnceOpPage;
}

CRepeatetlyRandomOpPage* CMainFrame::GetRepeatetlyRandomOpPage()
{
	return &mNewMainView->mRandomOpPage;
}

CRepeatedlyOrderOpPage* CMainFrame::GetRepeatedlyOrderOpPage()
{
	return &mNewMainView->mOrderOpPage;
}
//-----------------------------------------------------------------------------