//**************************************************************************//
#include "stdafx.h"
#include "MGRobot.h"
#include "MainFrm.h"
#include "RepeatedlyOrderOpPage.h"
#include "RepeatetlyRandomOpPage.h"
#include "OnceOpPage.h"

#include "UiOperateSystem.h"
#include "UIOperateManager.h"
// CRepeatetlyRandomOpPage dialog
//**************************************************************************//
IMPLEMENT_DYNAMIC(CRepeatetlyRandomOpPage, CPropertyPage)
//**************************************************************************//
CRepeatetlyRandomOpPage::CRepeatetlyRandomOpPage()
	: CPropertyPage(CRepeatetlyRandomOpPage::IDD)
{

}
//--------------------------------------------------------------
CRepeatetlyRandomOpPage::~CRepeatetlyRandomOpPage()
{
}
//--------------------------------------------------------------
void CRepeatetlyRandomOpPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}
//**************************************************************************//

BEGIN_MESSAGE_MAP(CRepeatetlyRandomOpPage, CPropertyPage)
	
	ON_BN_CLICKED(IDOK, &CRepeatetlyRandomOpPage::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_RM_START, &CRepeatetlyRandomOpPage::OnBnClickedBtnRmStart)
	ON_BN_CLICKED(IDC_BTN_RM_START_OP1, &CRepeatetlyRandomOpPage::OnBnClickedBtnRmStartOp1)
	ON_BN_CLICKED(IDC_BTN_RM_END_OP1, &CRepeatetlyRandomOpPage::OnBnClickedBtnRmEndOp1)
	ON_BN_CLICKED(IDC_CHK_RANDOM_MOVE_OP1, &CRepeatetlyRandomOpPage::OnBnClickedChkRandomMoveOp1)

END_MESSAGE_MAP()

//**************************************************************************//
// CRepeatetlyRandomOpPage message handlers
//--------------------------------------------------------------
BOOL CRepeatetlyRandomOpPage::OnInitDialog()
{
	enableAllWindow(FALSE);
	GetDlgItem(IDC_RM_START)->EnableWindow(FALSE);
	((CEdit*)GetDlgItem(IDC_EDT_MOVE_INTERVAL_OP1))->SetWindowText("100");
	((CEdit*)GetDlgItem(IDC_EDT_MOVE_CYCLE_LIFE_OP1))->SetWindowText("5000");

	((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_FRONT_INTERVAL_OP1))->SetWindowText("100");
	((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_FRONT_CYCLE_LIFE_OP1))->SetWindowText("5000");
	((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_FRONT_SIZE_OP1))->SetWindowText("1000");


	((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_INTERVAL_OP1))->SetWindowText("100");
	((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_CYCLE_LIFE_OP1))->SetWindowText("5000");
	((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_SIZE_OP1))->SetWindowText("1000");

	return CPropertyPage::OnInitDialog();
}
//--------------------------------------------------------------
void CRepeatetlyRandomOpPage::enableAllWindow( BOOL enable )
{
	GetDlgItem(IDC_CHK_RANDOM_MOVE_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_MOVE_INTERVAL_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_MOVE_CYCLE_LIFE_OP1)->EnableWindow(enable);

	GetDlgItem(IDC_CHK_SENDPACKET_FRONT_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_FRONT_INTERVAL_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_FRONT_CYCLE_LIFE_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_FRONT_SIZE_OP1)->EnableWindow(enable);

	GetDlgItem(IDC_CHK_SENDPACKET_LOGIN_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_INTERVAL_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_CYCLE_LIFE_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_SIZE_OP1)->EnableWindow(enable);

	GetDlgItem(IDC_BTN_RM_START_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_RM_END_OP1)->EnableWindow(enable);

	GetDlgItem(IDC_RM_START)->EnableWindow(!enable);
}
//--------------------------------------------------------------
void CRepeatetlyRandomOpPage::enableOp1( BOOL enable )
{
	GetDlgItem(IDC_CHK_RANDOM_MOVE_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_MOVE_INTERVAL_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_MOVE_CYCLE_LIFE_OP1)->EnableWindow(enable);	
	
	GetDlgItem(IDC_CHK_SENDPACKET_FRONT_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_FRONT_INTERVAL_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_FRONT_CYCLE_LIFE_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_FRONT_SIZE_OP1)->EnableWindow(enable);

	GetDlgItem(IDC_CHK_SENDPACKET_LOGIN_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_INTERVAL_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_CYCLE_LIFE_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_SIZE_OP1)->EnableWindow(enable);

	GetDlgItem(IDC_BTN_RM_START_OP1)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_RM_END_OP1)->EnableWindow(!enable);
	
}
//--------------------------------------------------------------
void CRepeatetlyRandomOpPage::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
}
//--------------------------------------------------------------
void CRepeatetlyRandomOpPage::OnBnClickedBtnRmStart()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().setOperateMode(MG::UIOperateMode::UIOperateMode_Repeatedly_Random);
	enableAllWindow(TRUE);
	((CMainFrame*)theApp.m_pMainWnd)->GetOnceOpPage()->enableAllWindow(FALSE);
	((CMainFrame*)theApp.m_pMainWnd)->GetRepeatedlyOrderOpPage()->enableAllWindow(FALSE);
}
//--------------------------------------------------------------
void CRepeatetlyRandomOpPage::OnBnClickedBtnRmStartOp1()
{
	// TODO: Add your control notification handler code here
	enableOp1(FALSE);
	MG::UiOperateSystem::getInstance().setOperateMode(MG::UIOperateMode::UIOperateMode_Repeatedly_Random);
	BOOL isCheck = ((CButton*)GetDlgItem(IDC_CHK_RANDOM_MOVE_OP1))->GetCheck();

	if (isCheck)
	{

		CString str;
		((CButton*)GetDlgItem(IDC_EDT_MOVE_INTERVAL_OP1))->GetWindowText(str);
		int intervalTime = atoi(str.GetBuffer());
		((CButton*)GetDlgItem(IDC_EDT_MOVE_CYCLE_LIFE_OP1))->GetWindowText(str);
		int cycleLifeTime = atoi(str.GetBuffer());
		MG::UiOperateSystem::getInstance().addRandMoveOp(intervalTime,cycleLifeTime);
	}
	isCheck = ((CButton*)GetDlgItem(IDC_CHK_SENDPACKET_FRONT_OP1))->GetCheck();
	if (isCheck)
	{
		CString str;
		((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_FRONT_INTERVAL_OP1))->GetWindowText(str);
		int intervalTime = atoi(str.GetBuffer());
		((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_FRONT_CYCLE_LIFE_OP1))->GetWindowText(str);
		int cycleLifeTime = atoi(str.GetBuffer());
		((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_FRONT_SIZE_OP1))->GetWindowText(str);
		int size  = atoi(str.GetBuffer());
		MG::UiOperateSystem::getInstance().addSendDataToFsOp(intervalTime,cycleLifeTime,size);
	}
	isCheck = ((CButton*)GetDlgItem(IDC_CHK_SENDPACKET_LOGIN_OP1))->GetCheck();
	if (isCheck)
	{
		CString str;
		((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_INTERVAL_OP1))->GetWindowText(str);
		int intervalTime = atoi(str.GetBuffer());
		((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_CYCLE_LIFE_OP1))->GetWindowText(str);
		int cycleLifeTime = atoi(str.GetBuffer());
		((CEdit*)GetDlgItem(IDC_EDT_SENDPACKET_LOGIN_SIZE_OP1))->GetWindowText(str);
		int size  = atoi(str.GetBuffer());
		MG::UiOperateSystem::getInstance().addSendDataToLsOp(size,intervalTime,cycleLifeTime);
	}
}
//--------------------------------------------------------------
void CRepeatetlyRandomOpPage::OnBnClickedBtnRmEndOp1()
{
	// TODO: Add your control notification handler code here
	enableOp1(TRUE);
	MG::UiOperateSystem::getInstance().setOperateMode(MG::UIOperateMode::UIOperateMode_Repeatedly_Random);
}
//--------------------------------------------------------------
void CRepeatetlyRandomOpPage::OnBnClickedChkRandomMoveOp1()
{
	// TODO: Add your control notification handler code here
}