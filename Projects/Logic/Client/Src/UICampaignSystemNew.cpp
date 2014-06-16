//*************************************************************************************

#include "stdafx.h"
#include "UICampaignSystemNew.h"
#include "UICampaignInfoNew.h"
#include "CampaignNetPacketProcesser.h"
#include "CPlayer.h"
#include "UICampaignListNew.h"
//*************************************************************************************
namespace MG
{
	UICampaignSystemNew::UICampaignSystemNew()
	{
	}

	//------------------------------------------------------------------------
	UICampaignSystemNew::~UICampaignSystemNew()
	{
	}

	//--------------------------------------------------------------------------------
	Bool UICampaignSystemNew::openGui()
	{
		CPlayer* myPlayer = &(CPlayer::getInstance());
		SCampaign* myCampaign = myPlayer->getMyCampaign();


		

		Bool bRet = false;
		if (NULL == myCampaign)
		{
			UICampaignListNew::getInstance().clearCampaignList();
			if (UICampaignListNew::getInstance().isOpen())
			{
				UICampaignListNew::getInstance().closeGui();
			}
			else
			{
				CampaignNetPacketProcesser::getInstance().sendCampaignList();
			}
		}
		else
		{
			//我进入战斗房间 切换UI
			UICampaignListNew::getInstance().closeGui();

			if (true == myCampaign->getCampaignIsStart())
			{
				//战斗已经开始
				//UIMessageBox::getInstance().showHint(L"您已经在战场中");
			}
			else
			{
				UICampaignInfoNew::getInstance().UIClear();
				UICampaignInfoNew::getInstance().openGui();
			}

		}

		return bRet;

	}
	
	//--------------------------------------------------------------------------------
	Bool UICampaignSystemNew::closeGui()
	{
		return true;
	}

}
