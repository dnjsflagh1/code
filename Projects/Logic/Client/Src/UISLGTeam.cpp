#include "stdafx.h"
#include "UISLGTeam.h"
#include "SCampaign.h"
#include "CPlayer.h"
#include "ArtIconResCsv.h"
#include "UISLGSkillInfo.h"
#include "CPlayerCharacterEntity.h"
#include "CSceneManager.h"
//***************************************************************************************************
namespace MG
{
	UISLGTeam::UISLGTeam()
    {

    }
    //----------------------------------------------------------------------------------------
    UISLGTeam::~UISLGTeam()
    {
		mTeamList.clear();
    }
	 //----------------------------------------------------------------------------------------
	void UISLGTeam::restore()
	{
		clear();
		for (Int i = 0; i < 4; ++i)
		{
			char tempStr[32] = "";
			sprintf(tempStr, "Teamer_%d", i);
			IImage *headimg = getLayout()->getImage(tempStr);
			headimg->setItemGroup("");
			headimg->setItemResource("");
			headimg->setItemName("");
			headimg->getWidget()->setUserData(-1);
		}
	}
	//----------------------------------------------------------------------------------------
	void UISLGTeam::setEvent()
	{
		for (Int i = 0; i < 4; ++i)
		{
			char tempStr[32] = "";
			sprintf(tempStr, "Teamer_%d", i);
			IImage *headimg = getLayout()->getImage(tempStr);
			DYNAMIC_ASSERT(headimg);
			headimg->getWidget()->setMouseButtonClickEvent(onClickHeadEvent);
			headimg->getWidget()->setUserData(-1);
		}
	}
	//----------------------------------------------------------------------------------------
	void UISLGTeam::onClickHeadEvent( void* widget )
	{
		IWidget* iWidget = (IWidget*)widget;
		IAny* anyData = iWidget->getUserData();
		Int* index = anyData->castType<Int>();
		if (*index > POSITION_INIT)
		{
			UISLGSkillInfo::getInstance().UIRefresh(false,*index);
		}
	}
	//----------------------------------------------------------------------------------------
	void UISLGTeam::clear()
	{
		mTeamList.clear();
	}
	//----------------------------------------------------------------------------------------
	POSITION	 UISLGTeam::findShowPosition(POSITION pos)
	{
		SCampaign* myCampain = CPlayer::getInstance().getMyCampaign();
		Int realPos = -1;
		if (myCampain)
		{	
			//小于自己在campain中的位置+1，大于自己的不变
			FORCE myForce = CPlayer::getInstance().getForce();
			ClanArmy* myArmy = NULL;
			POSITION myPos = POSITION_INIT;
			
			if (myForce == FORCE_ATTACK)
			{
				myArmy = myCampain->getAttackMemberInfoByClanId(CPlayer::getInstance().getActiveClanId());
			}
			else if (myForce == FORCE_DEFENSE)
			{
				myArmy = myCampain->getDefenseMemberInfoByClanId(CPlayer::getInstance().getActiveClanId());
			}
			if (myArmy)
			{
				Int myPos= (Int)myArmy->position;
			}
			if (pos < myPos)
			{
				realPos = pos + 1;
			}
			else
				realPos = pos;
		}
		return (POSITION)realPos;
	}
	//----------------------------------------------------------------------------------------
	void UISLGTeam::addTeamMember(Byte pos, Int playerCharId)
	{
		POSITION position = (POSITION)pos;

		DYNAMIC_ASSERT(pos > POSITION_INIT && pos < POSITION_MAX);

		POSITION realPos = findShowPosition(position);
		mTeamList[realPos] = playerCharId;
		UIFreshByIndex(realPos);
	}
	//----------------------------------------------------------------------------------------
	void UISLGTeam::deleteTeamMember(Byte pos)
	{
		POSITION position = (POSITION)pos;

		DYNAMIC_ASSERT(pos > POSITION_INIT && pos < POSITION_MAX);

		POSITION realPos = findShowPosition(position);
		if (realPos > POSITION_INIT)
		{
			std::map<POSITION, Int>::iterator iter = mTeamList.find(realPos);
			if (iter != mTeamList.end())
			{
				mTeamList.erase(realPos);
			}
			UIDeleteMemberByIndex(realPos);
		}
	}
	//----------------------------------------------------------------------------------------
	void UISLGTeam::UIDeleteMemberByIndex(POSITION pos)
	{
		Int i =(Int)pos;
		char tempStr[32] = "";
		sprintf(tempStr, "Teamer_%d", i);
		IImage *headimg = getLayout()->getImage(tempStr);
		headimg->setItemGroup("");
		headimg->setItemResource("");
		headimg->setItemName("");
		headimg->getWidget()->setUserData(-1);
	}
	//----------------------------------------------------------------------------------------
	void  UISLGTeam::UIFreshByIndex(POSITION pos)
	{
		std::map<POSITION, Int>::iterator iter = mTeamList.find(pos);
		if (iter != mTeamList.end())
		{
			Int charId = iter->second;
			if (charId > 0)
			{
				CPlayerCharacterEntity* entity = CSceneManager::getInstance().getPlayerCharacterEntity(charId);
				if (entity)
				{
					U32 charArtIcon = entity->getDynamicData()->charArtIcon;
					const ArtIconResCsvInfo* tempResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(charArtIcon);   

					char tempStr[32] = "";
					sprintf(tempStr, "Teamer_%d", pos);

					IImage *headimg = getLayout()->getImage(tempStr);
					headimg->setItemGroup(tempResInfo->GroupName);
					headimg->setItemResource(tempResInfo->ResName);
					headimg->setItemName(tempResInfo->ItemName);
					headimg->getWidget()->setUserData(pos);
				}
			}
		}
	}
	//----------------------------------------------------------------------------------------
	void UISLGTeam::UIFresh()
	{
		if (false == UISLGTeam::getInstance().isOpen())
		{
			return;
		}
		//清空UI
		
		for (Int i = 0; i < 4; ++i)
		{
			char tempStr[32] = "";
			sprintf(tempStr, "Teamer_%d", i);
			IImage *headimg = getLayout()->getImage(tempStr);
			headimg->setItemGroup("");
			headimg->setItemResource("");
			headimg->setItemName("");
			headimg->getWidget()->setUserData(-1);
		}		
		for (std::map<POSITION, Int>::iterator iter = mTeamList.begin(); iter != mTeamList.end(); ++iter)
		{
			Int charId = iter->second;
			if (charId > 0)
			{
				CPlayerCharacterEntity* entity = CSceneManager::getInstance().getPlayerCharacterEntity(charId);
				if (entity)
				{
					U32 charArtIcon = entity->getDynamicData()->charArtIcon;
					const ArtIconResCsvInfo* tempResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(charArtIcon);   

					char tempStr[32] = "";
					sprintf(tempStr, "Teamer_%d", iter->first);

					IImage *headimg = getLayout()->getImage(tempStr);
					headimg->setItemGroup(tempResInfo->GroupName);
					headimg->setItemResource(tempResInfo->ResName);
					headimg->setItemName(tempResInfo->ItemName);
					headimg->getWidget()->setUserData(iter->first);
				}
			}
		}
	}
}