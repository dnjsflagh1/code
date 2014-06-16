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
			//�ҽ���ս������ �л�UI
			UICampaignListNew::getInstance().closeGui();

			if (true == myCampaign->getCampaignIsStart())
			{
				//ս���Ѿ���ʼ
				//UIMessageBox::getInstance().showHint(L"���Ѿ���ս����");
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
