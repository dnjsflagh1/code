//***************************************************************************************************
#include "stdafx.h"
#include "UISLGTimeLeft.h"
#include "ClientMain.h"
#include "CPlayer.h"
#include "PlayerNetPacketProcesser.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "SCampaign.h"
//***************************************************************************************************
namespace MG
{
	UISLGTimeLeft::UISLGTimeLeft()
    {
		
    }
    //----------------------------------------------------------------------------------------
    UISLGTimeLeft::~UISLGTimeLeft()
    {
		
    }
	//----------------------------------------------------------------------------------------
	bool UISLGTimeLeft::openGui()
	{
		SCampaign* myCampain = CPlayer::getInstance().getMyCampaign();
		if (myCampain)
		{
			setCountDownTime(myCampain->getTimeListInfo()->time2);
		}
		return UIObject::openGui();
	}
	//----------------------------------------------------------------------------------------
	void UISLGTimeLeft::setCountDownTime(Int seconds)
	{
		ITimeText* p = getLayout()->getTimeText("Text_CountDown");
		p->setEventTimeOut(eventTimeFinish, 0);
		p->setCoolDownTime(seconds * 1000);
	}

	void UISLGTimeLeft::eventTimeFinish(void* widget, Int leftTime)
	{
		//离开战场倒计时走完，退出战场
		AccountIdType accountId =  CPlayer::getInstance().getAccountID();
		PlayerCharacterIdType playerCharacterId = CPlayer::getInstance().getMainPlayerCharacterId();

		//退出战场
		PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpLastRegion(playerCharacterId);
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountId, playerCharacterId);
	}

	
}