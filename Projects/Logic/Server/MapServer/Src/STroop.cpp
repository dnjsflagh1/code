/******************************************************************************/

#include "stdafx.h"
#include "STroop.h"
#include "SCamp.h"
#include "CharacterList.h"
#include "SSkillOwnManager.h"
#include "SCDManager.h"
#include "IdManager.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	STroop::STroop(TroopIdType soldierId, STroopGroup* ownerTroopGroup,Int soldierNum, RegionIdType regionId, InstanceUIdType instanceId, Int troopTemplateId)
		:SCharacter(GOT_TROOP, MG_NEW TroopData())
		,mOwnerTroopGroup(ownerTroopGroup)
	{
		DYNAMIC_ASSERT(NULL != mOwnerTroopGroup);

		getTroopData()->mCharacterTemplateID = troopTemplateId;
		getTroopData()->mSoldierNum = soldierNum;
		getTroopData()->mRegionID = regionId;
		getTroopData()->mInstanceUId = instanceId;
        getTroopData()->mLevel = 1;
		//for (Int index=0; index<soldierNum; ++index)
		//{
		//	mTroopSoldierList.createOrRetrieve<TroopSoldierIdType, STroop*, RegionIdType, InstanceUIdType>(index, index, this,regionId, instanceId);
		//}
		//
        //获得角色模板。
		setCharacterTempInfo();
        
        //计算属性。
        calAttr();

		//获得技能
		getSkillOwnManager()->getDefultSkill();
		//CD
		setSCDManager(CD_MASTER_TYPE_TROOP, this);

		//SCharacter::init();
	}

	//-----------------------------------------------------------------------------
	STroop::~STroop()
	{
		IdManager::getInstance().releaseId(getTroopData()->mId);
	}

	//-----------------------------------------------------------------------------
	void STroop::update(Flt delta)
	{
		//SCharacter::update(delta);

		//std::map<TroopSoldierIdType, STroopSoldier*>* troopSoldierList = getTroopSoldierList();
		//STroopSoldier* troopSoldier = NULL;

		//for(std::map<TroopSoldierIdType, STroopSoldier*>::iterator it = troopSoldierList->begin(); it != troopSoldierList->end(); ++it)
		//{
		//	troopSoldier = it->second;
		//	if(!troopSoldier)
		//	{
		//		continue;
		//	}

		//	troopSoldier->update(delta);
		//}
	}


	//-----------------------------------------------------------------------------
	void STroop::dead(SCharacter* murderer)
	{
		//setIsInitTroopPos(false);
		//DYNAMIC_ASSERT(NULL != mOwnerArmy);

	}


	//-----------------------------------------------------------------------------
	SArmy* STroop::getOwnerArmy()
	{
		return NULL;

		//return mOwnerTroopGroup->getOwnerArmy();
	}

	//-----------------------------------------------------------------------------
	SCamp* STroop::getOwnerCamp()
	{
		//if (NULL != mOwnerTroopGroup)
		//{
		//	return mOwnerTroopGroup->getOwnerCamp();
		//}

		return NULL;
	}

	//-----------------------------------------------------------------------------
	SPlayer* STroop::getParentPlayer()
	{
		//if (NULL != mOwnerTroopGroup)
		//{
		//	return mOwnerTroopGroup->getParentPlayer();
		//}

		DYNAMIC_ASSERT(0);
		return NULL;
	}


	//-----------------------------------------------------------------------------
	U64 STroop::getTroopTemplateId()
	{
		return getTroopData()->mCharacterTemplateID;
	}


	//-----------------------------------------------------------------------------
	TroopData* STroop::getTroopData()
	{
		return (TroopData*)getGameObjectData();
	}

#if 0
	//-----------------------------------------------------------------------------
	Bool STroopNew::getIsInitTroopPos() const
	{
		return mIsActiveInCampaign;
	}

	//-----------------------------------------------------------------------------
	void STroopNew::setIsInitTroopPos(Bool isInit)
	{
		mIsActiveInCampaign = isInit;
	}
#endif



	////-----------------------------------------------------------------------
	//void STroopNew::moveToPos( Vec3 startMovePos, Vec3 MoveToPos, Bool isBlockCheck )
	//{
	//	NetVec2 startMovePosdata;
	//	startMovePosdata = startMovePos;

	//	NetVec2 endMovePosdata;
	//	endMovePosdata = MoveToPos;

	//	STroopNetPacketProcesser::getInstance().broadcastTroopMove(this, (NetVec2)startMovePosdata, (NetVec2)endMovePosdata, isBlockCheck);

	//	SCharacter::moveToPos(startMovePos, MoveToPos);
	//}

	////-----------------------------------------------------------------------
	//void STroopNew::stopMove()
	//{
	//	LinedStateObject* linedStateObject = mActionManager->getState("SCharacterMoveToAction", false);
	//	if(linedStateObject)
	//	{
	//		STroopNetPacketProcesser::getInstance().broadcastTroopStopMove(this);
	//	}

	//	SCharacter::stopMove();
	//}

	void STroopPtr::destroy(void)
	{
		//mFactory->de
	}
}