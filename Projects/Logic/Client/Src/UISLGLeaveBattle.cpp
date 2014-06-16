//***************************************************************************************************
#include "stdafx.h"
#include "UISLGLeaveBattle.h"
#include "CSceneManager.h"
#include "ClientMain.h"
#include "CPlayer.h"
#include "PlayerNetPacketProcesser.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "CampaignNetPacketProcesser.h"
//***************************************************************************************************
namespace MG
{
    UISLGLeaveBattle::UISLGLeaveBattle()
    {
		
    }
    //----------------------------------------------------------------------------------------
    UISLGLeaveBattle::~UISLGLeaveBattle()
    {
		
    }
    //----------------------------------------------------------------------------------------
    void UISLGLeaveBattle::setEvent()
    {
		getLayout()->getButton("leave_btn")->getWidget()->setMouseButtonClickEvent(onEventLeave);

    }

	//----------------------------------------------------------------------------------------
	void UISLGLeaveBattle::init()
	{
	}
	
	//------------------------------------------------------------------------
	void UISLGLeaveBattle::onEventLeave(void* widget)
	{
		CPlayer* player = &(CPlayer::getInstance());
		AccountIdType accountId =  CPlayer::getInstance().getAccountID();
		PlayerCharacterIdType playerCharacterId = CPlayer::getInstance().getMainPlayerCharacterId();

		//ÍË³öÕ½³¡
		CampaignNetPacketProcesser::getInstance().sendCampaignLeaveInCampaign(player->getMyCampaignId(), player->getActiveClanId());
		//PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpLastRegion(playerCharacterId);
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountId, playerCharacterId);
	}

}