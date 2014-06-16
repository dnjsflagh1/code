//ItemView.cpp : 实现文件

#include "stdafx.h"
#include "MGRobot.h"
#include "ItemView.h"


// CItemView

IMPLEMENT_DYNCREATE(CItemView, CFormView)

CItemView::CItemView()
	: CFormView(CItemView::IDD)
{

}

CItemView::~CItemView()
{
}

void CItemView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CItemView, CFormView)
END_MESSAGE_MAP()


// CItemView 诊断

#ifdef _DEBUG
void CItemView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CItemView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}



#endif
#endif //_DEBUG

bool CItemView::initView()
{
	mSheetControl.AddPage(&mLoginPage);
	mSheetControl.AddPage(&mOperatePage);
	mSheetControl.AddPage(&mCampaignPage);

	CRect rcSheet;
	GetDlgItem( IDC_STATIC_SHEET_RECT )->GetWindowRect( &rcSheet );
	ScreenToClient( &rcSheet );

	mSheetControl.EnableStackedTabs(false);
	mSheetControl.Create(this,WS_CHILD|WS_VISIBLE);
	mSheetControl.SetWindowPos(NULL,rcSheet.left-5,rcSheet.top-5,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE);
	CTabCtrl* pTabCtrl=mSheetControl.GetTabControl();
	pTabCtrl->MoveWindow(5,5,rcSheet.Width()+5,rcSheet.Height()+10);
	
	mSheetControl.SetActivePage(2);
	mSheetControl.SetActivePage(1);
	mSheetControl.SetActivePage(0);
	return true;
}
