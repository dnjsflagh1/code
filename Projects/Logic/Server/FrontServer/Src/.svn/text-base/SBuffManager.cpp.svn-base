//************************************************************************************************
#include "stdafx.h"
#include "SBuffManager.h"
#include "PlayerCharacterDB.h"
#include "FrontServerMain.h"
#include "SBuffPacketProcesser.h"
#include "SClan.h"
#include "SPlayer.h"
//************************************************************************************************
namespace MG
{
	void SBuffManager::updateBuff( PlayerCharacterIdType id, UInt timeUse, UInt curAddNum, UInt buffId )
	{
		MapCharacterBuff::iterator iter = mMapCharacterBuff.find(id);
		if ( iter != mMapCharacterBuff.end() )
		{
			MapBuffData::iterator iter2 = iter->second.find(buffId);
			if ( iter2 != iter->second.end() )
			{
				iter2->second.mTimeUse = timeUse;
				iter2->second.mCurAddNum = curAddNum;
			}
			else
			{
				BuffData tempData;
				tempData.mBuffId = buffId;
				tempData.mCurAddNum = curAddNum;
				tempData.mTimeUse = timeUse;
				tempData.mpStatusBaseInfo = StatusList::getInstance().getStatusData(buffId)->mpStatusBaseInfo;
				iter->second[buffId] = tempData;
			}
			//¸üÐÂDB
			PlayerCharacterDBOp::updatePlayerCharacterBuff(*(FrontServerMain::getInstance().getDBDriver()),id, &(iter->second));
		}
		else
			DYNAMIC_ASSERT(0);
	}
	//-------------------------------------------------------------------------------------
	void SBuffManager::deleteBuffByPlayerCharacterId( PlayerCharacterIdType id )
	{
		mMapCharacterBuff.erase(id);
	}
	//-------------------------------------------------------------------------------------
	void SBuffManager::clear()
	{
		mMapCharacterBuff.clear();
	}
	//-------------------------------------------------------------------------------------
	void SBuffManager::sendBuffToMapServer()
	{
		MapCharacterBuff::iterator::iterator frontIter = mMapCharacterBuff.begin();
		MapCharacterBuff::iterator::iterator backIter = mMapCharacterBuff.end();
		while (frontIter != backIter)
		{
			SBuffPacketProcesser::getInstance().sendBuffDataListToMapServer(
				mpParent->getParentPlayer()->getMapServerNetID(),
				frontIter->first,
				&(frontIter->second)
				);
			++frontIter;
		}
	}
	//-------------------------------------------------------------------------------------
	SBuffManager::SBuffManager(  )
		:mpParent(NULL)
	{
		
	}
	//-------------------------------------------------------------------------------------
	void SBuffManager::setParent( SClan* pSClan )
	{
		mpParent = pSClan;
	}
}