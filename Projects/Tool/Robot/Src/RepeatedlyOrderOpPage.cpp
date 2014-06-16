// E:\workSpace\xh\MGCode\Logic\Projects\Tool\Robot\Src\RepeatedlyOrderOp.cpp : implementation file
//

#include "stdafx.h"
#include "MGRobot.h"
#include "MainFrm.h"
#include "RepeatedlyOrderOpPage.h"
#include "RepeatetlyRandomOpPage.h"
#include "OnceOpPage.h"
#include "UiOperateSystem.h"
#include "UIOperateManager.h"
// CRepeatedlyOrderOpPage dialog

IMPLEMENT_DYNAMIC(CRepeatedlyOrderOpPage, CPropertyPage)
//---------------------------------------------------------------------------------------
CRepeatedlyOrderOpPage::CRepeatedlyOrderOpPage()
	: CPropertyPage(CRepeatedlyOrderOpPage::IDD)
{

}
//---------------------------------------------------------------------------------------
CRepeatedlyOrderOpPage::~CRepeatedlyOrderOpPage()
{
}
//---------------------------------------------------------------------------------------
void CRepeatedlyOrderOpPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}

//---------------------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CRepeatedlyOrderOpPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHK_AUTOJOINGAEM_ORDER_OP1, &CRepeatedlyOrderOpPage::OnBnClickedChkAutojoingaemOrderOp1)
	ON_BN_CLICKED(IDC_BTN_ORDER_START_OP1, &CRepeatedlyOrderOpPage::OnBnClickedBtnOrderStartOp1)
	ON_BN_CLICKED(DC_BTN_ORDER_END_OP1, &CRepeatedlyOrderOpPage::OnBnClickedBtnOrderEndOp1)
	ON_BN_CLICKED(IDC_BTN_ORDER_START, &CRepeatedlyOrderOpPage::OnBnClickedBtnOrderStart)
	ON_BN_CLICKED(IDC_CHK_MOVE_ORDER_OP1, &CRepeatedlyOrderOpPage::OnBnClickedChkMoveOrderOp1)
	ON_BN_CLICKED(IDC_CHK_CLOSE_ORDER_OP1, &CRepeatedlyOrderOpPage::OnBnClickedChkCloseOrderOp1)
END_MESSAGE_MAP()
//---------------------------------------------------------------------------------------
BOOL CRepeatedlyOrderOpPage::OnInitDialog()
{
	((CButton*)GetDlgItem(IDC_CHK_AUTOJOINGAEM_ORDER_OP1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHK_MOVE_ORDER_OP1))->SetCheck(TRUE);
	((CButton*)GetDlgItem(IDC_CHK_CLOSE_ORDER_OP1))->SetCheck(TRUE);
	((CEdit*)GetDlgItem(IDC_EDT_MOVE_INTERVAL_OP1))->SetWindowText("100");
	((CEdit*)GetDlgItem(IDC_EDT_MOVE_CYCLE_LIFE_OP1))->SetWindowText("5000");
	enableAllWindow(TRUE);
	((CButton*)GetDlgItem(IDC_BTN_ORDER_START))->EnableWindow(FALSE);
	return CPropertyPage::OnInitDialog();

}
//---------------------------------------------------------------------------------------
void CRepeatedlyOrderOpPage::enableAllWindow( BOOL enable )
{
	((CButton*)GetDlgItem(IDC_CHK_AUTOJOINGAEM_ORDER_OP1))->EnableWindow(enable);
	((CButton*)GetDlgItem(IDC_CHK_MOVE_ORDER_OP1))->EnableWindow(enable);
	((CButton*)GetDlgItem(IDC_CHK_CLOSE_ORDER_OP1))->EnableWindow(enable);
	((CButton*)GetDlgItem(IDC_CHK_AUTOJOINGAEM_ORDER_OP1))->EnableWindow(enable);
	((CButton*)GetDlgItem(IDC_BTN_ORDER_START_OP1))->EnableWindow(enable);
	((CButton*)GetDlgItem(DC_BTN_ORDER_END_OP1))->EnableWindow(enable);	
	((CButton*)GetDlgItem(IDC_BTN_ORDER_START))->EnableWindow(!enable);
}
//---------------------------------------------------------------------------------------
// CRepeatedlyOrderOpPage message handlers
void CRepeatedlyOrderOpPage::OnBnClickedChkAutojoingaemOrderOp1()
{
	// TODO: Add your control notification handler code here
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHK_AUTOJOINGAEM_ORDER_OP1))->GetCheck();
	if (isCheck == FALSE)
	{
		((CButton*)GetDlgItem(IDC_CHK_AUTOJOINGAEM_ORDER_OP1))->SetCheck(TRUE);
	}
}
//---------------------------------------------------------------------------------------
void CRepeatedlyOrderOpPage::OnBnClickedChkMoveOrderOp1()
{
	// TODO: Add your control notification handler code here
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHK_MOVE_ORDER_OP1))->GetCheck();
	if (isCheck == FALSE)
	{
		((CButton*)GetDlgItem(IDC_CHK_MOVE_ORDER_OP1))->SetCheck(TRUE);
	}
}
//---------------------------------------------------------------------------------------
void CRepeatedlyOrderOpPage::OnBnClickedChkCloseOrderOp1()
{
	// TODO: Add your control notification handler code here
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHK_CLOSE_ORDER_OP1))->GetCheck();
	if (isCheck == FALSE)
	{
		((CButton*)GetDlgItem(IDC_CHK_CLOSE_ORDER_OP1))->SetCheck(TRUE);
	}
}
//---------------------------------------------------------------------------------------
void CRepeatedlyOrderOpPage::OnBnClickedBtnOrderStart()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().setOperateMode(MG::UIOperateMode::UIOperateMode_Repeatedly_Order);
	enableAllWindow(TRUE);
	((CMainFrame*)theApp.m_pMainWnd)->GetOnceOpPage()->enableAllWindow(FALSE);
	((CMainFrame*)theApp.m_pMainWnd)->GetRepeatetlyRandomOpPage()->enableAllWindow(FALSE);
}
//---------------------------------------------------------------------------------------
void CRepeatedlyOrderOpPage::OnBnClickedBtnOrderEndOp1()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().setOperateMode(MG::UIOperateMode::UIOperateMode_Repeatedly_Order);
	enableOp1(TRUE);
}
//---------------------------------------------------------------------------------------
void CRepeatedlyOrderOpPage::OnBnClickedBtnOrderStartOp1()
{
	// TODO: Add your control notification handler code here
	enableOp1(FALSE);
	MG::UiOperateSystem::getInstance().setOperateMode(MG::UIOperateMode::UIOperateMode_Repeatedly_Order);
	MG::UiOperateSystem::getInstance().addAutoJoinGameOp();
	
	CString str;
	((CButton*)GetDlgItem(IDC_EDT_MOVE_INTERVAL_OP1))->GetWindowText(str);
	int intervalTime = atoi(str.GetBuffer());
	((CButton*)GetDlgItem(IDC_EDT_MOVE_CYCLE_LIFE_OP1))->GetWindowText(str);
	int cycleLifeTime = atoi(str.GetBuffer());

	MG::UiOperateSystem::getInstance().addRandMoveOp(intervalTime,cycleLifeTime);
	MG::UiOperateSystem::getInstance().addCloseNetOp();

}

void CRepeatedlyOrderOpPage::enableOp1( BOOL enable )
{
	((CButton*)GetDlgItem(IDC_CHK_AUTOJOINGAEM_ORDER_OP1))->EnableWindow(enable);
	((CButton*)GetDlgItem(IDC_CHK_MOVE_ORDER_OP1))->EnableWindow(enable);
	((CButton*)GetDlgItem(IDC_CHK_CLOSE_ORDER_OP1))->EnableWindow(enable);
	((CButton*)GetDlgItem(IDC_BTN_ORDER_START_OP1))->EnableWindow(enable);
	((CButton*)GetDlgItem(DC_BTN_ORDER_END_OP1))->EnableWindow(!enable);	
}
