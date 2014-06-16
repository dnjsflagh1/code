//*************************************************************************************

#include "stdafx.h"
#include "UICampaignWinLoseMsg.h"
#include "UIBattleScore.h"
#include "CPlayer.h"
#include "SCampaign.h"

//*************************************************************************************
namespace MG
{
	//------------------------------------------------------------------------
	UICampaignWinLoseMsg::UICampaignWinLoseMsg()
		:mCloseTimeSecond(0)
		,mCampaignResult(CampaignResult_Init)
	{
	}

	UICampaignWinLoseMsg::~UICampaignWinLoseMsg()
	{
	}

	Bool UICampaignWinLoseMsg::openGui()
	{
		if (  false == UIObject::isOpen() )
		{
			DYNAMIC_ASSERT(mCloseTimeSecond > 0);
			setCloseTime(mCloseTimeSecond);
			UIObject::openGui();

			UIShowResult();

			
		}
		else
		{
			UIObject::closeGui();
		}

		return false;
	}

	void UICampaignWinLoseMsg::setEvent()
	{
		//¡¾È·ÈÏ°´Å¥¡¿
		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Confirm");
			btnConfirm->getWidget()->setMouseButtonClickEvent(onEventConfirm);
		}
	}

	//------------------------------------------------------------------------
	void UICampaignWinLoseMsg::onEventConfirm(void* widget)
	{
		UICampaignWinLoseMsg::getInstance().closeGui();
		UIBattleScore::getInstance().openGui();
	}

	void UICampaignWinLoseMsg::setCloseTime(Flt seconds)
	{
		getLayout()->getWidget(MAIN_WIDGET)->setCloseEvent(seconds, onCloseTimeCallBack);
	}

	void UICampaignWinLoseMsg::onCloseTimeCallBack(void* widget)
	{
		UICampaignWinLoseMsg::getInstance().onEventConfirm(widget);
	}

	void UICampaignWinLoseMsg::setTime(U32 time)
	{
		mCloseTimeSecond = time;
	}

	void UICampaignWinLoseMsg::setCampaignResult(CampaignResult result)
	{
		DYNAMIC_ASSERT(result > CampaignResult_Init && result <CampaignResult_Max);
		mCampaignResult = result;
	}

	void UICampaignWinLoseMsg::UIShowResult()
	{
		std::string strItemName = "";
		if (mCampaignResult == CampaignResult_Win)
		{
			strItemName = "1";
		}
		else if(mCampaignResult == CampaignResult_Lose)
		{
			strItemName = "2";
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}


		IImage *headimg = getLayout()->getImage("Image_WinLose");
		headimg->setItemGroup("Image_WinLose");
		headimg->setItemResource("Main_Icon_WinLose");
		headimg->setItemName(strItemName);
	}
}