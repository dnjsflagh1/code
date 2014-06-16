// E:\workSpace\xh\MGCode\Logic\Projects\Tool\Robot\Src\OnceOpPage.cpp : implementation file
//

#include "stdafx.h"
#include "MGRobot.h"
#include "OnceOpPage.h"
#include "UIOperateSystem.h"
#include "UIOperateManager.h"
#include "MainFrm.h"
#include "RepeatedlyOrderOpPage.h"
#include "RepeatetlyRandomOpPage.h"

#include "ThreadTaskManager.h"
// COnceOpPage dialog

IMPLEMENT_DYNAMIC(COnceOpPage, CPropertyPage)

COnceOpPage::COnceOpPage()
	: CPropertyPage(COnceOpPage::IDD)
{

}

COnceOpPage::~COnceOpPage()
{
}

void COnceOpPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COnceOpPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_START_ONCE_OP, &COnceOpPage::OnBnClickedBtnStartOnceOp)
	ON_BN_CLICKED(IDC_BTN_CONNECT_LOGIN, &COnceOpPage::OnBnClickedBtnConnectLogin)
	ON_BN_CLICKED(IDC_BTN_SENDDATA_TO_LOGIN, &COnceOpPage::OnBnClickedBtnSenddataToLogin)
	ON_BN_CLICKED(IDC_BTN_LOGIN_LOGIN, &COnceOpPage::OnBnClickedBtnLoginLogin)
	ON_BN_CLICKED(IDC_BTN_CONNECT_FRONT, &COnceOpPage::OnBnClickedBtnConnectFront)
	ON_BN_CLICKED(IDC_BTN_SENDDATA_TO_FRONT, &COnceOpPage::OnBnClickedBtnSenddataToFront)
	ON_BN_CLICKED(IDC_BTN_LOGIN_FRONT, &COnceOpPage::OnBnClickedBtnLoginFront)
	ON_BN_CLICKED(IDC_BTN_CREATE_CAN, &COnceOpPage::OnBnClickedBtnCreateCan)
	ON_BN_CLICKED(IDC_BTN_DEL_CLAN, &COnceOpPage::OnBnClickedBtnDelClan)
	ON_BN_CLICKED(IDC_BTN_CREATE_CHARACHTER, &COnceOpPage::OnBnClickedBtnCreateCharachter)
	ON_BN_CLICKED(IDC_BTN_ACCOUNT_LOGIN, &COnceOpPage::OnBnClickedBtnAccountLogin)
	ON_BN_CLICKED(IDC_BTN_JIONGAME, &COnceOpPage::OnBnClickedBtnJiongame)
	ON_BN_CLICKED(IDC_BTN_AUTO_JOINGAME, &COnceOpPage::OnBnClickedBtnAutoJoingame)
	ON_BN_CLICKED(IDC_BTN_CLOSE_NET, &COnceOpPage::OnBnClickedBtnCloseNet)
	ON_BN_CLICKED(IDC_BTN_CREATE_CAMP, &COnceOpPage::OnBnClickedBtnCreateCamp)
	ON_BN_CLICKED(IDC_BTN_RANDOM_MOVE, &COnceOpPage::OnBnClickedBtnRandomMove)
END_MESSAGE_MAP()


// COnceOpPage message handlers
BOOL COnceOpPage::OnInitDialog()
{
	GetDlgItem(IDC_EDT_LOGINDATA_SIZE)->SetWindowText("1000");
	GetDlgItem(IDC_EDT_FRONTDATA_SIZE)->SetWindowText("1000");
	((CEdit*)GetDlgItem(IDC_EDT_MOVE_INTERVAL_OP1))->SetWindowText("100");
	((CEdit*)GetDlgItem(IDC_EDT_MOVE_CYCLE_LIFE_OP1))->SetWindowText("5000");
	enableAllWindow(FALSE);
	GetDlgItem(IDC_BTN_START_ONCE_OP)->EnableWindow(FALSE);
	return CPropertyPage::OnInitDialog();	
}
void COnceOpPage::enableAllWindow( BOOL enable )
{
	GetDlgItem(IDC_BTN_CONNECT_LOGIN)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_LOGIN_LOGIN)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_CONNECT_FRONT)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_LOGIN_FRONT)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_CREATE_CAN)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_DEL_CLAN)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_CREATE_CHARACHTER)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_JIONGAME)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_ACCOUNT_LOGIN)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_AUTO_JOINGAME)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_CLOSE_NET)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_RANDOM_MOVE)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_TEST_SKILL)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_CREATE_CAMP)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_SENDDATA_TO_LOGIN)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_SENDDATA_TO_FRONT)->EnableWindow(enable);
	GetDlgItem(IDC_BTN_START_ONCE_OP)->EnableWindow(!enable);
}

void COnceOpPage::OnBnClickedBtnStartOnceOp()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().setOperateMode(MG::UIOperateMode::UIOperateMode_Once);
	enableAllWindow(TRUE);
	//((CMainFrame*)theApp.m_pMainWnd)->GetRepeatedlyOrderOpPage()->enableAllWindow(FALSE);
	((CMainFrame*)theApp.m_pMainWnd)->GetRepeatetlyRandomOpPage()->enableAllWindow(FALSE);
	((CMainFrame*)theApp.m_pMainWnd)->GetRepeatedlyOrderOpPage()->enableAllWindow(FALSE);
}

void COnceOpPage::OnBnClickedBtnConnectLogin()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addConnectLsOp();
}

void COnceOpPage::OnBnClickedBtnSenddataToLogin()
{
	// TODO: Add your control notification handler code here
	CString temp;
	GetDlgItem(IDC_EDT_LOGINDATA_SIZE)->GetWindowText(temp);
	MG::I32 size = 0;
	MG::MGStrOp::toI32(temp.GetBuffer(),size);

	MG::UiOperateSystem::getInstance().addSendDataToLsOp(size,0,0);
}

void COnceOpPage::OnBnClickedBtnLoginLogin()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addLoginLsOp();
}

void COnceOpPage::OnBnClickedBtnConnectFront()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addConnectFsOp();
}

void COnceOpPage::OnBnClickedBtnSenddataToFront()
{
	// TODO: Add your control notification handler code here
	CString temp;
	GetDlgItem(IDC_EDT_FRONTDATA_SIZE)->GetWindowText(temp);
	MG::I32 size = 0;
	MG::MGStrOp::toI32(temp.GetBuffer(),size);

	MG::UiOperateSystem::getInstance().addSendDataToFsOp(size,0,0);
}

void COnceOpPage::OnBnClickedBtnLoginFront()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addLoginFsOp();
}

void COnceOpPage::OnBnClickedBtnCreateCan()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addCreateClanOp();
}

void COnceOpPage::OnBnClickedBtnDelClan()
{
	// TODO: Add your control notification handler code here
	//MG::UiOperateSystem::getInstance().();
}

void COnceOpPage::OnBnClickedBtnCreateCharachter()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addCreateCharacterOp();
}

void COnceOpPage::OnBnClickedBtnAccountLogin()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addAccountLoginOp();
}

void COnceOpPage::OnBnClickedBtnJiongame()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addJoinGameOp();
}

void COnceOpPage::OnBnClickedBtnAutoJoingame()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addAutoJoinGameOp();
}

void COnceOpPage::OnBnClickedBtnCloseNet()
{
	// TODO: Add your control notification handler code here
	MG::UiOperateSystem::getInstance().addCloseNetOp();
}

void COnceOpPage::OnBnClickedBtnCreateCamp()
{
	// TODO: Add your control notification handler code here
	
	// 添加战场操作：
	MG::ThreadTaskManager::getInstance().startCampaign();
	
	

}

void COnceOpPage::OnBnClickedBtnRandomMove()
{
	// TODO: Add your control notification handler code here
	// MG::UiOperateSystem::getInstance().addRandMoveOp()
	CString str;
	((CButton*)GetDlgItem(IDC_EDT_MOVE_INTERVAL_OP1))->GetWindowText(str);
	int intervalTime = atoi(str.GetBuffer());
	((CButton*)GetDlgItem(IDC_EDT_MOVE_CYCLE_LIFE_OP1))->GetWindowText(str);
	int cycleLifeTime = atoi(str.GetBuffer());
	MG::UiOperateSystem::getInstance().addRandMoveOp(intervalTime,cycleLifeTime);
}
