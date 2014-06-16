//*************************************************************************************

#include "stdafx.h"
#include "UICampaignInviteDefense.h"
#include "CampaignNetPacketProcesser.h"
#include "CPlayer.h"

//*************************************************************************************



//*************************************************************************************
namespace MG
{
	//------------------------------------------------------------------------
	UICampaignInviteDefense::UICampaignInviteDefense()
		:mRegionId(0)
		,mInstanceId(0)
		,mCampaignId(0)
	{

	}

	//------------------------------------------------------------------------
	UICampaignInviteDefense::~UICampaignInviteDefense()
	{

	}

	//------------------------------------------------------------------------
	void UICampaignInviteDefense::setEvent()
	{
		//【参加战斗】
		{
			IButton* btnConfirm = getLayout()->getButton("Btn_ConfirmDefense");
			btnConfirm->getWidget()->setMouseButtonClickEvent(onEventConfirm);
		}

		//【拒绝参加】
		{
			IButton* btnCancel = getLayout()->getButton("Btn_RefuseDefense");
			btnCancel->getWidget()->setMouseButtonClickEvent(onEventCancel);
		}
	}

	//------------------------------------------------------------------------
	Bool UICampaignInviteDefense::openGui()
	{
		if (  false == UIObject::isOpen() )
		{
			UIObject::openGui();
		}

		UIReFresh();
		return false;
	}

	//------------------------------------------------------------------------
	void UICampaignInviteDefense::onEventConfirm(void* widget)
	{
		RegionIdType targetRegionId = UICampaignInviteDefense::getInstance().getCampaignTargetRegionId();
		InstanceIdType instanceId	= UICampaignInviteDefense::getInstance().getCampaignInstanceId();
		CampaignIdType campaignId	= UICampaignInviteDefense::getInstance().getCampaignId();
		ClanIdType		myClanId	= CPlayer::getInstance().getActiveClanId();
		CampaignNetPacketProcesser::getInstance().sendCampaignJoinDefense(targetRegionId, campaignId, myClanId);
		UICampaignInviteDefense::getInstance().closeGui();
	}

	//------------------------------------------------------------------------
	void UICampaignInviteDefense::onEventCancel(void* widget)
	{
		UICampaignInviteDefense::getInstance().closeGui();
	}

	//--------------------------------------------------------------------------------
	void UICampaignInviteDefense::setCampaignInfo(const RegionIdType regionId, const InstanceIdType instanceId, const CampaignIdType campaignId)
	{
		DYNAMIC_ASSERT(regionId > 0 && instanceId > 0 && campaignId > 0);

		mRegionId	= regionId;
		mInstanceId = instanceId;
		mCampaignId = campaignId;
	}

	//--------------------------------------------------------------------------------
	RegionIdType UICampaignInviteDefense::getCampaignTargetRegionId()
	{
		return mRegionId;
	}

	//--------------------------------------------------------------------------------
	InstanceIdType UICampaignInviteDefense::getCampaignInstanceId()
	{
		return mInstanceId;
	}

	//--------------------------------------------------------------------------------
	CampaignIdType UICampaignInviteDefense::getCampaignId()
	{
		return mCampaignId;
	}

	//--------------------------------------------------------------------------------
	void UICampaignInviteDefense::UIReFresh()
	{
#if 0
		Bool creatorIsMe = CPlayer::getInstance().campaignCreatorIsMe();

		//【确认按钮】

		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Confirm");

			if (true == creatorIsMe)
			{
				//我是房主
				btnConfirm->getWidget()->setCaption(L"开始");
			}
			else
			{
				//
				btnConfirm->getWidget()->setCaption(L"准备");
			}
		}

		//取消按钮
		{
			IButton* btnCancel = getLayout()->getButton("Btn_Cancel");


			if (true == creatorIsMe)
			{
				//我是房主
				btnCancel->getWidget()->setCaption(L"踢出");
			}
			else
			{
				//
				btnCancel->getWidget()->setCaption(L"取消准备");
			}
		}


		//开始画成员UI
		UIReFreshMemberList();
		UIReFreshHost();
#endif
	}


	//------------------------------------------------------------------------
}	//namespace MG