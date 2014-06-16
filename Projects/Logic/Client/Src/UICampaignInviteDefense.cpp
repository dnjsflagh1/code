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
		//���μ�ս����
		{
			IButton* btnConfirm = getLayout()->getButton("Btn_ConfirmDefense");
			btnConfirm->getWidget()->setMouseButtonClickEvent(onEventConfirm);
		}

		//���ܾ��μӡ�
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

		//��ȷ�ϰ�ť��

		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Confirm");

			if (true == creatorIsMe)
			{
				//���Ƿ���
				btnConfirm->getWidget()->setCaption(L"��ʼ");
			}
			else
			{
				//
				btnConfirm->getWidget()->setCaption(L"׼��");
			}
		}

		//ȡ����ť
		{
			IButton* btnCancel = getLayout()->getButton("Btn_Cancel");


			if (true == creatorIsMe)
			{
				//���Ƿ���
				btnCancel->getWidget()->setCaption(L"�߳�");
			}
			else
			{
				//
				btnCancel->getWidget()->setCaption(L"ȡ��׼��");
			}
		}


		//��ʼ����ԱUI
		UIReFreshMemberList();
		UIReFreshHost();
#endif
	}


	//------------------------------------------------------------------------
}	//namespace MG