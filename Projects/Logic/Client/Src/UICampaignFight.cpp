//*************************************************************************************

#include "stdafx.h"
#include "UICampaignFight.h"
#include "ArtIconResCsv.h"
#include "SCampaign.h"
#include "CPlayer.h"

//*************************************************************************************
namespace MG
{
	UICampaignFight::UICampaignFight()
		:mIsShow(false)
	{

	}

	UICampaignFight::~UICampaignFight()
	{

	}

	Bool UICampaignFight::openGui()
	{
		if (false == mIsShow)
		{

			return false;
		}

		UIObject::openGui();
		UIFresh();
		mIsShow = false;
		
		return true;
	}

	void UICampaignFight::restore()
	{
		clear();
	}

	Bool UICampaignFight::getIsShow() const
	{
		return mIsShow;
	}

	void UICampaignFight::setIsShow(Bool isShow)
	{
		mIsShow = isShow;
	}

	void UICampaignFight::clear()
	{
		mAttackList.clear();
		mDefenseList.clear();
	}

	void UICampaignFight::addCampaignFightInfo(FORCE force, U32 charArtIcon, Byte pos, Bool isHost)
	{
		POSITION position = (POSITION)pos;
		DYNAMIC_ASSERT(pos > POSITION_INIT && pos < POSITION_MAX);
		if (FORCE_ATTACK == force)
		{
			if (false == isHost)
			{
				position = (POSITION)(pos + 1);
			}

			std::map<POSITION, UICampaignFightInfo>::iterator iter = mAttackList.find(position);
			//if (iter != mAttackList.end())
			//{
			//	//重复
			//	DYNAMIC_ASSERT(0);
			//}
			
			UICampaignFightInfo info;
			info.charArtIcon = charArtIcon;
			mAttackList[position] = info;
		}
		else if(FORCE_DEFENSE == force)
		{
			std::map<POSITION, UICampaignFightInfo>::iterator iter = mDefenseList.find(position);
			//if (iter != mDefenseList.end())
			//{
			//	//重复
			//	DYNAMIC_ASSERT(0);
			//}
			UICampaignFightInfo info;
			info.charArtIcon = charArtIcon;
			mDefenseList[position] = info;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
	}


	void UICampaignFight::UIFresh()
	{
		if (false == UICampaignFight::getInstance().isOpen())
		{
			return;
		}
		//清空UI
		{
			//进攻方
			for (Int i = 1; i <= 5; ++i)
			{
				char tempStr[32] = "";
				sprintf(tempStr, "attck_head%d", i);
				IImage *headimg = getLayout()->getImage(tempStr);
				headimg->setItemGroup("");
				headimg->setItemResource("");
				headimg->setItemName("");
			}

			//防守方
			for (Int i = 1; i <= 5; ++i)
			{
				char tempStr[32] = "";
				sprintf(tempStr, "defense_head%d", i);
				IImage *headimg = getLayout()->getImage(tempStr);
				headimg->setItemGroup("");
				headimg->setItemResource("");
				headimg->setItemName("");
			}
		}

		//SCampaign* myCampaign = CPlayer::getInstance().getMyCampaign();
		//if(NULL == myCampaign)
		//{
		//	return;
		//}


		//攻击方其他玩家信息
		{
			Int index = 0;
			for (std::map<POSITION, UICampaignFightInfo>::iterator iter = mAttackList.begin(); iter != mAttackList.end(); ++iter)
			{
				index++;
				U32 charArtIcon = iter->second.charArtIcon;
				const ArtIconResCsvInfo* tempResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(charArtIcon);   

				char tempStr[32] = "";
				sprintf(tempStr, "attck_head%d", index);

				IImage *headimg = getLayout()->getImage(tempStr);
				headimg->setItemGroup(tempResInfo->GroupName);
				headimg->setItemResource(tempResInfo->ResName);
				headimg->setItemName(tempResInfo->ItemName);
			}
		}
			
		//防守方所有玩家信息
		{
			Int index = 0;
			for (std::map<POSITION, UICampaignFightInfo>::iterator iter = mDefenseList.begin(); iter != mDefenseList.end(); ++iter)
			{
				index++;
				U32 charArtIcon = iter->second.charArtIcon;
				const ArtIconResCsvInfo* tempResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(charArtIcon);   

				char tempStr[32] = "";
				sprintf(tempStr, "defense_head%d", index);

				IImage *headimg = getLayout()->getImage(tempStr);
				headimg->setItemGroup(tempResInfo->GroupName);
				headimg->setItemResource(tempResInfo->ResName);
				headimg->setItemName(tempResInfo->ItemName);
			}
		}
		
		
	}
}