//*********************************************************************************************************
#include "stdafx.h"
#include "CCDManager.h"
#include "CPlayer.h"
#include "UIClanInfo.h"
#include "UISkillOperate.h"
#include "UISLGSkillInfo.h"
#include "UIManage.h"
//*********************************************************************************************************
namespace MG
{
    CCDManager::CCDManager()
		:isInitialize(false)
    {

    }
    //--------------------------------------------------------------------------------------
    CCDManager::~CCDManager()
    {
        clear();
    }
    //--------------------------------------------------------------------------------------
    void CCDManager::init()
    {
        mClanCDTimer = new CDTimer;
		mCityCDTimer = new CDTimer;
		mForceCDTimer = new CDTimer;

        /*CClan* pClan = CPlayer::getInstance().getActiveClan();

        std::map<PlayerCharacterIdType, CPlayerCharacter*>* tempMapCharList = pClan->getPlayerCharacterList();
        std::map<PlayerCharacterIdType, CPlayerCharacter*>::iterator front = tempMapCharList->begin();
        std::map<PlayerCharacterIdType, CPlayerCharacter*>::iterator back = tempMapCharList->end();
        while (front != back)
        {
            addCharacter(CD_MASTER_TYPE_CHARACTER, front->second->getID());
			isInitialize = true;
            ++front;
        }*/

        /*std::map<PlayerCharacterIdType, c*>* tempMapCharList = pClan->getPlayerCharacterList();
        std::map<PlayerCharacterIdType, CPlayerCharacter*>::iterator front = tempMapCharList->begin();
        std::map<PlayerCharacterIdType, CPlayerCharacter*>::iterator back = tempMapCharList->end();
        while (front != back)
        {
            addCharacter(CD_MASTER_TYPE_CHARACTER, front->second->getID());
            ++front;
        }*/
    }
    //--------------------------------------------------------------------------------------
    void CCDManager::addCharacter( CD_MASTER_TYPE type, IdType id )
    {
        switch ( type )
        {
        case CD_MASTER_TYPE_CHARACTER:
            {
				std::map<IdType, CDTimer*>::iterator iter = mMapGenrealCDTimer.find(id);
				if ( iter  == mMapGenrealCDTimer.end() )
				{
					CDTimer* tempTimer = new CDTimer;
					mMapGenrealCDTimer[id] = tempTimer;
				}      
            }
            break;
        case CD_MASTER_TYPE_TROOP:
            {
				std::map<IdType, CDTimer*>::iterator iter = mMapTroopCDTimer.find(id);
				if ( iter  == mMapTroopCDTimer.end() )
				{
					CDTimer* tempTimer = new CDTimer;
					mMapTroopCDTimer[id] = tempTimer;
				}
            }
            break;
        }
    }
    //--------------------------------------------------------------------------------------
    void CCDManager::deleteCharacter( CD_MASTER_TYPE type, IdType id )
    {
        switch ( type )
        {
        case CD_MASTER_TYPE_CHARACTER:
            {
                std::map<IdType, CDTimer*>::iterator iter = mMapGenrealCDTimer.find(id);
                if ( iter != mMapGenrealCDTimer.end() )
                {  
                    delete iter->second; 
                    mMapGenrealCDTimer.erase(iter);
                }
            }
            break;
        case CD_MASTER_TYPE_TROOP:
            {
                std::map<IdType, CDTimer*>::iterator iter = mMapTroopCDTimer.find(id);
                if ( iter != mMapTroopCDTimer.end() )
                {  
                    delete iter->second;   
                    mMapTroopCDTimer.erase(iter);
                }
            }
            break;
        }
    }
    //--------------------------------------------------------------------------------------
    MG::Bool CCDManager::checkCD( CD_MASTER_TYPE type, IdType id, U32 cdid )
    {
		if (isInitialize == false)
		{
            init();
		}
		if (cdid == 0)
		{
			return false;
		}
		const CDTempInfo* pCDTempInfo = CDTemplate::getInstance().getCDTempInfo(cdid);
		if(!pCDTempInfo)
		{
			return false;
		}

		if (pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CLAN)
			return mClanCDTimer->ifGoing(cdid);
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CITY )
			return mCityCDTimer->ifGoing(cdid);
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_FROCE )
			return mForceCDTimer->ifGoing(cdid);
		else
		{
			switch ( type )
			{
			case CD_MASTER_TYPE_CHARACTER:
				{
					std::map<IdType, CDTimer*>::iterator iter = mMapGenrealCDTimer.find(id);
					if ( iter != mMapGenrealCDTimer.end() )
					{  
						return iter->second->ifGoing(cdid);   
					}
				}
				break;
			case CD_MASTER_TYPE_TROOP:
				{
					std::map<IdType, CDTimer*>::iterator iter = mMapTroopCDTimer.find(id);
					if ( iter != mMapTroopCDTimer.end() )
					{  
						return iter->second->ifGoing(cdid);   
					}
				}
				break;
			}
		}

        return false;
    }
    //--------------------------------------------------------------------------------------
    void CCDManager::addCD( CD_MASTER_TYPE type, IdType id, U32 cdid, U32 liveTime, U32 totalTime )
    {
		
		if (isInitialize == false)
		{
			init();
		}
		if (cdid == 0)
		{
			return;
		}
		const CDTempInfo* pCDTempInfo = CDTemplate::getInstance().getCDTempInfo(cdid);
		if(!pCDTempInfo)
		{
			return;
		}

		if (pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CLAN)
			mClanCDTimer->addTimer(cdid, liveTime, totalTime);
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CITY )
			mCityCDTimer->addTimer(cdid, liveTime, totalTime);
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_FROCE )
			mForceCDTimer->addTimer(cdid, liveTime, totalTime);
		else
		{
			switch ( pCDTempInfo->SaveEntityType )
			{
			case CD_MASTER_TYPE_CHARACTER:
				{
					std::map<IdType, CDTimer*>::iterator iter = mMapGenrealCDTimer.find(id);
					if ( iter != mMapGenrealCDTimer.end() )
					{  
						iter->second->addTimer(cdid, liveTime, totalTime);   
					}
				}
				break;
			case CD_MASTER_TYPE_TROOP:
				{
					std::map<IdType, CDTimer*>::iterator iter = mMapTroopCDTimer.find(id);
					if ( iter != mMapTroopCDTimer.end() )
					{  
						iter->second->addTimer(cdid, liveTime, totalTime);  
					}
				}
				break;
			}
		}
		if ( type == CD_MASTER_TYPE_CHARACTER )
		{	
			//背包相关
			UIClanInfo::getInstance().notifyUIAddCD(cdid, liveTime, totalTime, id);
			//技能相关
			if (UIManager::getInstance().getGameType() == GameType_Slg)
			{
				if (UISLGSkillInfo::getInstance().opreatorIsMe())
				{
					UISLGSkillInfo::getInstance().notifyUIAddCD(cdid,liveTime,totalTime,id);
				}
			}
			else if (UIManager::getInstance().getGameType() == GameType_Rpg)
				UISkillOperate::getInstance().notifyUIAddCD(cdid,liveTime,totalTime,id);
		}
        
    }
    //--------------------------------------------------------------------------------------
    void CCDManager::removeCD( CD_MASTER_TYPE type, IdType id, U32 cdid )
    {
		const CDTempInfo* pCDTempInfo = CDTemplate::getInstance().getCDTempInfo(cdid);
		if(!pCDTempInfo)
		{
			return ;
		}
		if (pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CLAN)
			mClanCDTimer->removeTimer(cdid);
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CITY )
			mCityCDTimer->removeTimer(cdid);
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_FROCE )
			mForceCDTimer->removeTimer(cdid);
		else
		{
			switch ( type )
			{
			case CD_MASTER_TYPE_CHARACTER:
				{
					std::map<IdType, CDTimer*>::iterator iter = mMapGenrealCDTimer.find(id);
					if ( iter != mMapGenrealCDTimer.end() )
					{  
						iter->second->removeTimer(cdid);   
					}
				}
				break;
			case CD_MASTER_TYPE_TROOP:
				{
					std::map<IdType, CDTimer*>::iterator iter = mMapTroopCDTimer.find(id);
					if ( iter != mMapTroopCDTimer.end() )
					{  
						iter->second->removeTimer(cdid);  
					}
				}
				break;
			}
		}

		if ( type == CD_MASTER_TYPE_CHARACTER )
		{	
			//背包相关
			UIClanInfo::getInstance().notifyUIDeleteCD(cdid, id);
			//技能相关
			if (UIManager::getInstance().getGameType() == GameType_Slg)

			{
				if (UISLGSkillInfo::getInstance().opreatorIsMe())
				{
					UISLGSkillInfo::getInstance().notifyUIDeleteCD(cdid,id);
				}
			}
			else if (UIManager::getInstance().getGameType() == GameType_Rpg)
				UISkillOperate::getInstance().notifyUIDeleteCD(cdid,id);
			
		}
        
    }
    //--------------------------------------------------------------------------------------
    void CCDManager::removeGroupCD( CD_MASTER_TYPE type, IdType id, U32 cdGroupId )
    {
		const CDTempInfo* pCDTempInfo = CDTemplate::getInstance().getCDTempInfo(cdGroupId);
		if(!pCDTempInfo)
		{
			return;
		}
		if (pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CLAN)
			mClanCDTimer->removeGroupTimer(cdGroupId);
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_CITY )
			mCityCDTimer->removeGroupTimer(cdGroupId);
		else if ( pCDTempInfo->SaveEntityType == CD_MASTER_TYPE_FROCE )
			mForceCDTimer->removeGroupTimer(cdGroupId);
		else
		{
			switch ( type )
			{
			case CD_MASTER_TYPE_CHARACTER:
				{
					std::map<IdType, CDTimer*>::iterator iter = mMapGenrealCDTimer.find(id);
					if ( iter != mMapGenrealCDTimer.end() )
					{  
						iter->second->removeGroupTimer(cdGroupId);  
					}
				}
				break;
			case CD_MASTER_TYPE_TROOP:
				{
					std::map<IdType, CDTimer*>::iterator iter = mMapTroopCDTimer.find(id);
					if ( iter != mMapTroopCDTimer.end() )
					{  
						iter->second->removeGroupTimer(cdGroupId);  
					}
				}
				break;
			}
		}

		if ( type == CD_MASTER_TYPE_CHARACTER )
		{	
			//背包相关
			UIClanInfo::getInstance().updateItemCD();
			//技能相关
		}
        
    }
    //--------------------------------------------------------------------------------------
    void CCDManager::clear()
    {
        delete mClanCDTimer;
		delete mCityCDTimer;
		delete mForceCDTimer;

        std::map<IdType, CDTimer*>::iterator front = mMapGenrealCDTimer.begin();
        std::map<IdType, CDTimer*>::iterator back = mMapGenrealCDTimer.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }
        mMapGenrealCDTimer.clear();

        std::map<IdType, CDTimer*>::iterator front1 = mMapTroopCDTimer.begin();
        std::map<IdType, CDTimer*>::iterator back1 = mMapTroopCDTimer.end();
        while (front1 != back1)
        {
            delete front1->second;
            ++front1;
        }
        mMapTroopCDTimer.clear();
    }
	//--------------------------------------------------------------------------------------
	const CDTimer* CCDManager::getForceCDTimer()
	{
		return mForceCDTimer;
	}
	//--------------------------------------------------------------------------------------
	const CDTimer* CCDManager::getCityCDTimer()
	{
		return mCityCDTimer;
	}
	//--------------------------------------------------------------------------------------
	const CDTimer* CCDManager::getClanCDTimer()
	{
		return mClanCDTimer;
	}
	//--------------------------------------------------------------------------------------
	const CDTimer* CCDManager::getGenrealCDTimer( IdType genrealid )
	{
		std::map<IdType, CDTimer*>::iterator iter = mMapTroopCDTimer.find(genrealid);
		if ( mMapGenrealCDTimer.end() != iter )
			return iter->second;

		return NULL;
	}
	//--------------------------------------------------------------------------------------
	CDTimerData* CCDManager::findCD( CD_MASTER_TYPE type, IdType id, U32 cdid )
	{
		if (isInitialize == false)
		{
			init();
		}
		CDTimerData* pCDTimerData = mCityCDTimer->findTimer(cdid);
		if ( pCDTimerData )
			return pCDTimerData;

		pCDTimerData = mForceCDTimer->findTimer(cdid);
		if ( pCDTimerData )
			return pCDTimerData;

		pCDTimerData = mClanCDTimer->findTimer(cdid);
		if ( pCDTimerData )
			return pCDTimerData;

		if ( type == CD_MASTER_TYPE_CHARACTER )
		{
			std::map<IdType, CDTimer*>::iterator iter =  mMapGenrealCDTimer.find(id);
			if ( iter != mMapGenrealCDTimer.end() )
				return iter->second->findTimer(cdid);
		}
		else if ( type == CD_MASTER_TYPE_TROOP )
		{
			std::map<IdType, CDTimer*>::iterator iter =  mMapTroopCDTimer.find(id);
			if ( iter != mMapTroopCDTimer.end() )
				return iter->second->findTimer(cdid);
		}

		return NULL;
	}
}