// E:\workSpace\xh\MGCode\Logic\Projects\Tool\Robot\Src\CampaignPage.cpp : implementation file
//

#include "stdafx.h"
#include "MGRobot.h"
#include "CampaignPage.h"
#include "ClientManager.h"
#include "CCampaignManager.h"
#include "CCampaign.h"
#include "CampaignNetPacketProcesser.h"
// CCampaignPage dialog

IMPLEMENT_DYNAMIC(CCampaignPage, CPropertyPage)

CCampaignPage::CCampaignPage()
	: CPropertyPage(CCampaignPage::IDD)
{

}

CCampaignPage::~CCampaignPage()
{

}

void CCampaignPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMB0_CREATED,mCombCanntCreateCampaign);
	DDX_Control(pDX, IDC_COMBO_CAN_CREATE, mCombCreateCampaign);
}


BEGIN_MESSAGE_MAP(CCampaignPage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_CREATE_CAMPAGIN, &CCampaignPage::OnBnClickedBtnCreateCampagin)
	ON_BN_CLICKED(IDC_BTN_DESTORY_CAMPAGIN, &CCampaignPage::OnBnClickedBtnDestoryCampagin)
	ON_CBN_SELCHANGE(IDC_COMB0_CREATED, &CCampaignPage::OnCbnSelchangeComb0Created)
	ON_BN_CLICKED(IDC_BTN_STRAT_CAMPAGIN, &CCampaignPage::OnBnClickedBtnStratCampagin)
END_MESSAGE_MAP()


// CCampaignPage message handlers

void CCampaignPage::OnBnClickedBtnCreateCampagin()
{
	// TODO: Add your control notification handler code here
	//MG::CCampaignManager::getInstance().createCampaign();
	handleCreateCampagin(ONCE_CREATE_CAMPAGIN);
    
}

void CCampaignPage::OnBnClickedBtnDestoryCampagin()
{
	// TODO: Add your control notification handler code here
}

void CCampaignPage::uiFlash()
{
	mCombCanntCreateCampaign.ResetContent();
	mCanntCreateRegion.clear();
	std::map<MG::RegionIdType,MG::Str16>* regions = MG::CCampaignManager::getInstance().getRegionsCanntCreate();
	for (std::map<MG::RegionIdType,MG::Str16>::iterator it = regions->begin(); it != regions->end(); it++)
	{
		MG::Str8 str;
		MG::MGStrOp::toString(it->second.c_str(),str);
		mCombCanntCreateCampaign.AddString(str.c_str());
		mCanntCreateRegion.push_back(it->first);
	}

	mCombCreateCampaign.ResetContent();
	std::map<MG::RegionIdType,MG::Str16>* regionCanntCreate = MG::CCampaignManager::getInstance().getRegionsCanCreate();
	int i = 0;
	for (std::map<MG::RegionIdType,MG::Str16>::iterator it = regionCanntCreate->begin(); it != regionCanntCreate->end(); it++)
	{
		MG::Str8 str;
		MG::MGStrOp::toString(it->second.c_str(),str);
		mCombCreateCampaign.AddString(str.c_str());
		//((CComboBox*)GetDlgItem(IDC_COMB0_CREATED))->GetDlgItem(i)->SetDlgItemText(i,str.c_str());
		
		i++;
	}
}

BOOL CCampaignPage::OnSetActive()
{
	uiFlash();
	RECT rect;
	mCombCreateCampaign.GetWindowRect(&rect);
	ScreenToClient( &rect );
	mCombCreateCampaign.SetWindowPos(NULL,rect.left,rect.top,80,200,SWP_DEFERERASE);
	mCombCanntCreateCampaign.GetWindowRect(&rect);
	ScreenToClient( &rect );
	mCombCanntCreateCampaign.SetWindowPos(NULL,rect.left,rect.top,80,200,SWP_DEFERERASE);
	return CPropertyPage::OnSetActive();	
}
void CCampaignPage::OnCbnSelchangeComb0Created()
{
	// TODO: Add your control notification handler code here
	int index = mCombCanntCreateCampaign.GetCurSel();
	if (index < 0)
	{
		return;
	}
	MG::CampaignIdType campaignId = 0;
	MG::CCampaign* campaign = MG::CCampaignManager::getInstance().getCampaignByRegionId(mCanntCreateRegion[index],campaignId);

	MG::Str8 str;
	MG::MGStrOp::toString(campaignId,str);
	((CEdit*)GetDlgItem(IDC_EDIT_CAMPAIGN_ID))->SetWindowText(str.c_str());
	MG::MGStrOp::toString(campaign->getMemberNum(),str);
	((CEdit*)GetDlgItem(IDC_EDIT_MENBER_COUNT))->SetWindowText(str.c_str());
	if (!campaign->isOwned())
	{
		return;
	}
	MG::MGStrOp::toString(campaign->getHost()->getPlayerObj()->getActiveClan()->getName().c_str(),str);
	((CEdit*)GetDlgItem(IDC_EDIT_ROOM_MASTER))->SetWindowText(str.c_str());

	
}

void CCampaignPage::OnBnClickedBtnStratCampagin()
{
	// TODO: Add your control notification handler code here
	MG::CCampaignManager::getInstance().startBattle();
}

void CCampaignPage::handleCreateCampagin( CREATE_OPERATE create_operate )
{
	if (create_operate == ONCE_CREATE_CAMPAGIN)
	{
		CString str;
		((CEdit*)GetDlgItem(IDC_EDIT_MEMBER_COUNT_PRE))->GetWindowText(str);
		MG::I32 memberCount = 0;
		MG::MGStrOp::toI32(str.GetBuffer(),memberCount);
		((CEdit*)GetDlgItem(IDC_EDIT_CAMPAGIN_COUNT))->GetWindowText(str);
		MG::I32 campaignCount = 0;
		MG::MGStrOp::toI32(str.GetBuffer(),campaignCount);

		if (MG::CCampaignManager::getInstance().createCampaign(campaignCount,memberCount))
		{
			MG::CampaignNetPacketProcesser::getInstance().isEnd = false;
			MG::CampaignNetPacketProcesser::getInstance().isEndHandle = false;
			MG::ClientManager::getInstance().pushOperate(MG::OperateType_CreateCampaign);
			((CButton*)GetDlgItem(IDC_BTN_CREATE_CAMPAGIN))->EnableWindow(FALSE);
		}
	}
	else if (create_operate == CONTINUOUS_CREATE_CAMPAGIN)
	{
		CString str;
		((CEdit*)GetDlgItem(IDC_EDIT_MEMBER_COUNT_PRE))->GetWindowText(str);
		MG::I32 memberCount = 0;
		MG::MGStrOp::toI32(str.GetBuffer(),memberCount);
		((CEdit*)GetDlgItem(IDC_EDIT_CAMPAGIN_COUNT))->GetWindowText(str);
		MG::I32 campaignCount = 0;
		MG::MGStrOp::toI32(str.GetBuffer(),campaignCount);

		if (MG::CCampaignManager::getInstance().createCampaign(campaignCount,memberCount))
		{
			MG::CampaignNetPacketProcesser::getInstance().isEnd = false;
			MG::CampaignNetPacketProcesser::getInstance().isEndHandle = false;
			((CButton*)GetDlgItem(IDC_BTN_CREATE_CAMPAGIN))->EnableWindow(FALSE);
		}
	}

}

void CCampaignPage::OnlyCreateCampaginData()
{
	CString str;
	((CEdit*)GetDlgItem(IDC_EDIT_MEMBER_COUNT_PRE))->GetWindowText(str);
	MG::I32 memberCount = 0;
	MG::MGStrOp::toI32(str.GetBuffer(),memberCount);
	((CEdit*)GetDlgItem(IDC_EDIT_CAMPAGIN_COUNT))->GetWindowText(str);
	MG::I32 campaignCount = 0;
	MG::MGStrOp::toI32(str.GetBuffer(),campaignCount);

	if (MG::CCampaignManager::getInstance().createCampaign(campaignCount,memberCount))
	{
		MG::CampaignNetPacketProcesser::getInstance().isEnd = false;
		MG::CampaignNetPacketProcesser::getInstance().isEndHandle = false;
		((CButton*)GetDlgItem(IDC_BTN_CREATE_CAMPAGIN))->EnableWindow(FALSE);
	}

}