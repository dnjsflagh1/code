// E:\workSpace\xh\MGCode\Logic\Projects\Tool\Robot\Src\NewMainView.cpp : implementation file
//

#include "stdafx.h"
#include "MGRobot.h"
#include "NewMainView.h"
#include "OnceOpPage.h"
#include "SettingPage.h"
#include "RepeatedlyOrderOpPage.h"
#include "RepeatetlyRandomOpPage.h"


// CNewMainView

IMPLEMENT_DYNCREATE(CNewMainView, CFormView)

CNewMainView::CNewMainView()
	: CFormView(CNewMainView::IDD)
{

}

CNewMainView::~CNewMainView()
{
}

void CNewMainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNewMainView, CFormView)
END_MESSAGE_MAP()


// CNewMainView diagnostics

#ifdef _DEBUG
void CNewMainView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CNewMainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

bool CNewMainView::initView()
{
	mSheetControl.AddPage(&mSettingPage);
	mSheetControl.AddPage(&mOnceOpPage);
	mSheetControl.AddPage(&mOrderOpPage);
	mSheetControl.AddPage(&mRandomOpPage);
	mSheetControl.AddPage(&mCampaignOpPage);

	CRect rcSheet;
	GetDlgItem( IDC_STATIC_SHEET_RECT1 )->GetWindowRect( &rcSheet );
	ScreenToClient( &rcSheet );

	mSheetControl.EnableStackedTabs(false);
	mSheetControl.Create(this,WS_CHILD|WS_VISIBLE);
	mSheetControl.SetWindowPos(NULL,rcSheet.left-5,rcSheet.top-5,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
	
	CTabCtrl* pTabCtrl=mSheetControl.GetTabControl();

	pTabCtrl->MoveWindow(5,5,rcSheet.Width()+10,rcSheet.Height()+10);

	mSheetControl.SetActivePage(4);
	mSheetControl.SetActivePage(3);
	mSheetControl.SetActivePage(2);
	mSheetControl.SetActivePage(1);
	mSheetControl.SetActivePage(0);
	return true;
}
// CNewMainView message handlers
