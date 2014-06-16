// E:\workSpace\xh\MGCode\Logic\Projects\Tool\Robot\Src\CampaignOpPage.cpp : implementation file
//

#include "stdafx.h"
#include "MGRobot.h"
#include "CampaignOpPage.h"
#include "ThreadTaskManager.h"

// CCampaignOpPage dialog

IMPLEMENT_DYNAMIC(CCampaignOpPage, CPropertyPage)

CCampaignOpPage::CCampaignOpPage()
	: CPropertyPage(CCampaignOpPage::IDD)
{

}

CCampaignOpPage::~CCampaignOpPage()
{
}

void CCampaignOpPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCampaignOpPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_CAMP_SETTING, &CCampaignOpPage::OnBnClickedBtnCampSetting)
END_MESSAGE_MAP()


// CCampaignOpPage message handlers

void CCampaignOpPage::OnBnClickedBtnCampSetting()
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	MG::I32 campaginNum,generalNum,timeOut;
	((CEdit*)GetDlgItem(IDC_EDT_CAMP_NUM))->GetWindowText(strTemp);
	MG::MGStrOp::toI32(strTemp.GetBuffer(),campaginNum);
	((CEdit*)GetDlgItem(IDC_EDT_CAMP_GENERAL_NUM))->GetWindowText(strTemp);
	MG::MGStrOp::toI32(strTemp.GetBuffer(),generalNum);
	((CEdit*)GetDlgItem(IDC_EDT_CAMP_TIMEOUT))->GetWindowText(strTemp);
	MG::MGStrOp::toI32(strTemp.GetBuffer(),timeOut);

	// 战场预分配：
	MG::Bool res = MG::ThreadTaskManager::getInstance().preassignmentCampaginList(campaginNum,generalNum,timeOut);
	if (!res)
	{
		MG::MessageOut("创建战场配置不正确");
		return;
	}
	((CButton*)GetDlgItem(IDC_BTN_CAMP_SETTING))->SetWindowText("重设");
}
