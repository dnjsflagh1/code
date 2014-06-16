/******************************************************************************/
#include "stdafx.h"
#include "Player.h"
#include "CommonGameDefine.h"
#include "Clan.h"
#include "ItemSiteTemplate.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
	Clan::Clan()
	{
	}

	//-----------------------------------------------------------------------
	Clan::~Clan()
	{
	}

	//-----------------------------------------------------------------------
	ClanIdType Clan::getClanID()
	{
		return mClanData.clanId;
	}

	//-----------------------------------------------------------------------
	void Clan::setClanID(const ClanIdType& id)
	{
		mClanData.clanId = id;
	}

	//-----------------------------------------------------------------------
	Str16&	Clan::getName()
	{
		return mClanData.clanName;
	}

	//-----------------------------------------------------------------------
	void Clan::setName(const Char16*& name)
	{
		mClanData.clanName = name;
	}
    //-----------------------------------------------------------------------
    void Clan::setName(const Str16& name )
    {
        mClanData.clanName = name;
    }
	//-----------------------------------------------------------------------
	IdType Clan::getFocusRegionID()
	{
		return mClanData.regionID;
	}
	//-----------------------------------------------------------------------
	void Clan::setFocusRegionAttr( RegionIdType mapId, REGION_OBJ_TYPE regionType)
	{
		mClanData.regionID = mapId;
		mClanData.regionType = regionType;
	}
    //-----------------------------------------------------------------------
    PlayerIdType Clan::getAccountID()
    {
        return mClanData.accountId;
    }
    //-----------------------------------------------------------------------
    void Clan::setAccountID( const PlayerIdType& id )
    {
        mClanData.accountId = id;
    }
    //-----------------------------------------------------------------------
    PlayerCharacterIdType Clan::getMainGenrealID()
    {
        return mClanData.mainGenrealId;
    }
    //-----------------------------------------------------------------------
    void Clan::setMainGenrealID( const PlayerCharacterIdType& id )
    {
        mClanData.mainGenrealId = id;
    }
    //-----------------------------------------------------------------------
    Str16& Clan::getClanHomeLandName()
    {
        return mClanData.clanHomeLandName;
    }
    //-----------------------------------------------------------------------
    void Clan::setClanHomeLandName( const Char16*& homelandname )
    {
        mClanData.clanHomeLandName = homelandname;
    }
    //-----------------------------------------------------------------------
    void Clan::setClanHomeLandName( const Str16& homelandname )
    {
        mClanData.clanHomeLandName = homelandname;
    }
    //-----------------------------------------------------------------------
    void Clan::setData(ClanData* clandata)
    {
        mClanData = *clandata;
    }
    //-----------------------------------------------------------------------
    U8 Clan::getStatus()
    {
        return (U8)mClanData.status;
    }
    //-----------------------------------------------------------------------
    void Clan::setStatus( const U8& status )
    {
        mClanData.status = (CLAN_STATUS_TYPE)status;
    }

	//-----------------------------------------------------------------------
	MG::REGION_OBJ_TYPE Clan::getFocusRegionType()
	{
		return (REGION_OBJ_TYPE)mClanData.regionType;
	}

	//-----------------------------------------------------------------------
	/*QuestSysManagerBase* Clan::getQuestManager()
	{
		return mQuestSystem;
	}*/

	//--------------------------------------------------------------------------
	/*QuestTriggerInfo* Clan::getTrigger(QuestIdType questID)
	{
		return mQuestSystem->getTrigger(questID);
	}*/

	//--------------------------------------------------------------------------
	//Bool Clan::addQuest(QuestIdType questID)
	//{
	//	return mQuestSystem->addQuest(questID);
	//}

	//--------------------------------------------------------------------------
	/*Bool Clan::submitQuest(QuestIdType questID)
	{
		return mQuestSystem->submitQuest(questID);
	}*/

	//--------------------------------------------------------------------------
	/*Bool Clan::isQuestSubmited(QuestIdType questID)
	{
		if (!mQuestSystem)
		{
			return false;
		}
		return mQuestSystem->isQuestSubmited(questID);
	}*/

	//--------------------------------------------------------------------------
	/*Bool Clan::giveupQuest(QuestIdType questID)
	{
		return getQuestManager()->giveupQuest(questID);
	}*/

	//--------------------------------------------------------------------------
	/*QuestPlayerCharacter* Clan::getQuestPlayerCharacter()	
	{
		return getQuestManager()->getQuestPlayerCharacter(); 
	}*/
    //--------------------------------------------------------------------------
    void Clan::initItemSiteSize()
    {
        const ItemSiteInfo* ptempInfo = ItemSiteTemplate::getInstance().getItemSiteInfo(ITEM_SITE_TYPE_CLAN);
        mClanData.clanbagSize = ptempInfo->DefaultNum;
    }

	//--------------------------------------------------------------------------
	void Clan::print()
	{
		MG_LOG(out_sys, " ClanID[%I64i], AccountID[%I64i], MainGenrealID[%d], FocusRegionID[%d], FocusRegionType[%d], ",
			getClanID(), getAccountID(), getMainGenrealID(), getFocusRegionID(),getFocusRegionType());
	}
}