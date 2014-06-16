//***************************************************************************************************
#include "stdafx.h"
#include "UIMainFunction.h"
#include "CampaignNetPacketProcesser.h"
#include "CPlayer.h"
#include "UIClanInfo.h"
#include "UICampaignSystemNew.h"
#include "UIGameOptions.h"
#include "UIQuestManager.h"
//***************************************************************************************************
namespace MG
{
    UIMainFunciton::UIMainFunciton()
    {

    }
    //----------------------------------------------------------------------------------------
    UIMainFunciton::~UIMainFunciton()
    {

    }
    //----------------------------------------------------------------------------------------
    void UIMainFunciton::setEvent()
    {
		 getLayout()->getButton("btn_claninfo")->getWidget()->setMouseButtonClickEvent(OnClickClanInfo);
		 getLayout()->getButton("btn_campaign")->getWidget()->setMouseButtonClickEvent(OnClickCampaign);
		 getLayout()->getButton("btn_friendsinfo")->getWidget()->setMouseButtonClickEvent(OnClickFriendsInfo);
		 getLayout()->getButton("btn_taskinfo")->getWidget()->setMouseButtonClickEvent(OnClickTaskInfo);
		 getLayout()->getButton("btn_force")->getWidget()->setMouseButtonClickEvent(OnClickForce);
		 getLayout()->getButton("btn_systeminfo")->getWidget()->setMouseButtonClickEvent(OnClickSystemInfo);
		
    }
	//----------------------------------------------------------------------------------------

	void UIMainFunciton::OnClickClanInfo( void* widget )
	{
        if ( UIClanInfo::getInstance().isOpen() )
            UIClanInfo::getInstance().closeGui();
        else
            UIClanInfo::getInstance().openGui();
	}
	//----------------------------------------------------------------------------------------
	void UIMainFunciton::OnClickCampaign( void* widget )
	{
		UICampaignSystemNew::getInstance().openGui();
	}
	//----------------------------------------------------------------------------------------
	void UIMainFunciton::OnClickFriendsInfo( void* widget )
	{

	}
	//----------------------------------------------------------------------------------------
	void UIMainFunciton::OnClickTaskInfo( void* widget )
	{
		if (UIQuestManager::getInstance().isOpen())
         {
			UIQuestManager::getInstance().closeGui();
         }
		else
		{
			UIQuestManager::getInstance().openGui();
		}

	}
	//----------------------------------------------------------------------------------------
	void UIMainFunciton::OnClickForce( void* widget )
	{

	}
	//----------------------------------------------------------------------------------------
	void UIMainFunciton::OnClickSystemInfo( void* widget )
	{
		if (UIGameOptions::getInstance().isOpen())
		{
			UIGameOptions::getInstance().closeGui();
		}
		else
		{
			UIGameOptions::getInstance().openGui();
		}

	}
	//----------------------------------------------------------------------------------------

    
}