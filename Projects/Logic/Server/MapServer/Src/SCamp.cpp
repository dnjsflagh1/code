/******************************************************************************/

#include "stdafx.h"
#include "SCamp.h"
#include "SPlayer.h"
#include "SWorldManager.h"
#include "BuildingData.h"
#include "SCampaignNetPacketProcesser.h"
#include "IdManager.h"

/******************************************************************************/

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SCamp::SCamp()
		:SBuilding(0)
		,mControlTroopGroupAccountId(0)
		,mArmyNum(0) 
		,mCurControlArmy(NULL)
		,mIsDestroyed(false)
		,mIsHeadQuarter(false)
		,mCampaignId(0)
		,mAllTroopNumInCamp(0)
	{
		//DYNAMIC_ASSERT(regionObject->getRegionId() > 0);

		getCharacterData()->mCharacterTemplateID = 0;
		getCharacterData()->mRegionID			 = 0;
		getCharacterData()->mRegionType			 = ROT_UNKNOWN;
		getCharacterData()->mInstanceUId		 = 0;
		
		init();

		//for (Int i=0; i<mArmyNum; ++i)
		//{
		//	ArmyIdType armyId = IdManager::getInstance().createId();//campId * 10 + i + 1;
		//	mArmyList.createOrRetrieve<SCamp*, ArmyIdType, RegionIdType, InstanceUIdType, CampConfigInfo*>(armyId, this, armyId, regionObject->getRegionId(), regionObject->getInstanceUId(), campConfigInfo);
		//}

		//setCurControlArmy(getAliveArmy());

		////统计所有的军队数量
		//for (Int i=0; i<mArmyNum; ++i)
		//{
		//	for (Int j=0; j<campConfigInfo->troopGroupNum; ++j)
		//	{
		//		TroopGroupConfigInfo* tempTroopGroupInfo = &(campConfigInfo->troopGroupInfo[j]);

		//		mAllTroopNumInCamp += tempTroopGroupInfo->troopNum * tempTroopGroupInfo->troopSolierNum;
		//	}
		//}
	}


	//-----------------------------------------------------------------------------
	SCamp::~SCamp()
	{
		IdManager::getInstance().releaseId(getBuildingData()->mId);
	}

	//-----------------------------------------------------------------------------
	void SCamp::update(Flt delta)
	{
		//std::map<CampIdType, SArmy*>* armyList = mArmyList.getDataSet();
		//for (std::map<CampIdType, SArmy*>::iterator iter = armyList->begin(); iter != armyList->end(); ++iter)
		//{
		//	iter->second->update(delta);
		//}
	}

	//-----------------------------------------------------------------------------
	void SCamp::dead(SCharacter* murderer)
	{
		mIsDestroyed = true;
		
		if (true == getIsQuarter())
		{
			//大本营摧毁， 战斗结束
			SCampaignNetPacketProcesser::getInstance().sendMainCampDestroyToCenterServer(getCamaignId(), getForce());
		}
		
	}

	//-----------------------------------------------------------------------------
	void SCamp::createActiveArmy()
	{
		if (true == isAllArmyDead() || true == mIsDestroyed)
		{
			//所有的Army都死了
			//mIsDead = true;
			//mOwnerCamp->createActiveArmy();
			//sendNoTroopMsgToClient();

			int kk = 0;
		}
		else
		{
			//SArmy* newArmy = getAliveArmy();
			//setCurControlArmy(newArmy);
			//DYNAMIC_ASSERT(NULL != newArmy);
			//newArmy->createActiveTroopGroup();
		}
	}

	//-----------------------------------------------------------------------------
	Bool SCamp::isAllArmyDead()
	{
#if 0
		std::map<CampIdType, SArmy*>* armyList = mArmyList.getDataSet();

		for (std::map<CampIdType, SArmy*>::iterator iter = armyList->begin(); iter != armyList->end(); ++iter)
		{
			if (false == iter->second->isDead())
			{
				return false;
			}
		}
#endif
		return true;
	}


	//-----------------------------------------------------------------------------
	void SCamp::setControlTroopGroupAccountId(const AccountIdType targetAccountId)
	{
		mControlTroopGroupAccountId = targetAccountId;
	}

	//-----------------------------------------------------------------------------
	AccountIdType SCamp::getControlTroopGroupAccountId() const
	{
		return mControlTroopGroupAccountId;
	}

	//-----------------------------------------------------------------------------
	SArmy* SCamp::getCurControlArmy()
	{
		return mCurControlArmy;
	}

	//-----------------------------------------------------------------------------
	void SCamp::setCurControlArmy(SArmy* curArmy)
	{
		mCurControlArmy = curArmy;

	}

	//-----------------------------------------------------------------------------
	STroopGroup* SCamp::getCurControlTroopGroup()
	{
		return NULL;
#if 0
		if (NULL == mCurControlArmy)
		{
			return NULL;
		}

		return mCurControlArmy->getCurControlTroopGroup();
#endif
	}

	//-----------------------------------------------------------------------------
	SArmy* SCamp::getAliveArmy()
	{
		//std::map<CampIdType, SArmy*>* armyList = mArmyList.getDataSet();

		//for (std::map<CampIdType, SArmy*>::iterator iter = armyList->begin(); iter != armyList->end(); ++iter)
		//{
		//	if (false == iter->second->isDead())
		//	{
		//		return iter->second;
		//	}
		//}

		return NULL;
	}

	//-----------------------------------------------------------------------------
	STroopGroup* SCamp::getTroopGroupById(TroopIdType troopId)
	{
		return NULL;
		//return mAllTroopGroupList.getSecondData(troopId);
	}

	//-----------------------------------------------------------------------------
	CampIdType SCamp::getCampId()
	{
		return getBuildingData()->mId;
	}

	//-----------------------------------------------------------------------------
	CampaignIdType SCamp::getCamaignId() const
	{
		return mCampaignId;
	}

	//-----------------------------------------------------------------------------
	void SCamp::setCamaignId(const CampaignIdType campaignId)
	{
		mCampaignId = campaignId;
	}

	//-----------------------------------------------------------------------------
	Vec3 SCamp::getPos()
	{
		return getBuildingData()->mPos;
	}

	//-----------------------------------------------------------------------------
	void SCamp::setPos(Vec3& pos)
	{
		getBuildingData()->mPos = pos;
	}

	//-----------------------------------------------------------------------------
	Vec3 SCamp::getDir()
	{
		return getBuildingData()->mDir;
	}

	//-----------------------------------------------------------------------------
	void SCamp::setDir(Vec3& dir)
	{
		getBuildingData()->mDir = dir;
	}

	//-----------------------------------------------------------------------------
	Int SCamp::getArmyNum() const
	{
		return mArmyNum;
	}

	//-----------------------------------------------------------------------------
	U32 SCamp::getCampTemplateId()
	{
		return getBuildingData()->mCharacterTemplateID;
	}

	//-----------------------------------------------------------------------------
	Vec3 SCamp::getTroopBornPos(Int index)
	{
		return mTroopBornPos[index];
	}

	//-----------------------------------------------------------------------------
	void SCamp::setTroopBornPos(Int index, Vec3& pos)
	{
		mTroopBornPos[index] = pos;
	}

	//-----------------------------------------------------------------------------
	Vec3 SCamp::getTroopBornDir(Int index)
	{
		return mTroopBornDir[index];
	}

	//-----------------------------------------------------------------------------
	void SCamp::setTroopBornDir(Int index, Vec3& dir)
	{
#if 0
		mTroopBornDir[index] = dir;
		
		std::map<TroopGroupIdType, STroopGroup*>* toopGroupList = NULL;
		std::map<TroopIdType, STroop*>* troopList = NULL;
		
		std::map<CampIdType, SArmy*>* armyList = mArmyList.getDataSet();
		for (std::map<CampIdType, SArmy*>::iterator iter = armyList->begin(); iter != armyList->end(); ++iter)
		{
			SArmy* army = iter->second;
			toopGroupList = army->getTroopGroupList();
			for (std::map<TroopGroupIdType, STroopGroup*>::iterator iterTroopGroup = toopGroupList->begin();
				iterTroopGroup != toopGroupList->end(); ++iterTroopGroup)
			{
				STroopGroup* troopGroup = iterTroopGroup->second;
				troopGroup->setDir(dir);
				troopList = troopGroup->getTroopList();

				for (std::map<TroopIdType, STroop*>::iterator iterTroop = troopList->begin();
					iterTroop != troopList->end(); ++iterTroop)
				{
					STroop* troop = iterTroop->second;
					troop->setDir(dir);
				}
			}
		}
#endif
	}

	//-----------------------------------------------------------------------------
	Bool SCamp::isDestroyed() const
	{
		return mIsDestroyed;
	}

	//-----------------------------------------------------------------------------
	void SCamp::setIsQuarter(const Bool isQuarter)
	{
		mIsHeadQuarter = isQuarter;
	}

	//-----------------------------------------------------------------------------
	Bool SCamp::getIsQuarter() const
	{
		return mIsHeadQuarter;
	}

	//-----------------------------------------------------------------------------
	void SCamp::addTroopGroupToList(STroopGroup* newTroop)
	{
		//mAllTroopGroupList.addData(newTroop->getID(), newTroop);
	}

	void SCamp::addControlTroopGroup(STroopGroup* troopGroup)
	{
#if 0
		{
			std::map<TroopGroupIdType, STroopGroup*>::iterator iter = mControlTroopGroupList.begin();
			for ( ;iter!=mControlTroopGroupList.end();  )
			{
				if ( iter->second == troopGroup )
				{
					iter = mControlTroopGroupList.erase( iter );
				}else
				if ( iter->first == troopGroup->getID() )
				{
					iter = mControlTroopGroupList.erase( iter );
				}else
				{
					iter++;
				}
			}
		}

		{
			std::map<TroopGroupIdType, STroopGroup*>::iterator iter = mControlTroopGroupList.find(troopGroup->getID());
			if (iter != mControlTroopGroupList.end())
			{
				//找到， 重复
				DYNAMIC_ASSERT(0);
			}
		}

		if (mControlTroopGroupList.size() >= TROOP_GROUP_NUM )
		{
			return;
		}

		mControlTroopGroupList[troopGroup->getID()] = troopGroup;
#endif
	}

	void SCamp::delControlTroopGroup(STroopGroup* troopGroup)
	{
		//mControlTroopGroupList.erase(troopGroup->getID());
	}

	SPlayerIdentifyInfo* SCamp::getSPlayerIdentifyInfo()
	{
		return &mSPlayerIdentifyInfo;
	}
}