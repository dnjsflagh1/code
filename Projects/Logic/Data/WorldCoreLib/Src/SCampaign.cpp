/******************************************************************************/

#include "stdafx.h"
#include "SCampaign.h"

#include "PlaceListCsv.h"
#include "InstanceListCsv.h"
#include "InstanceAtkListCsv.h"
#include "InstanceTimeListCsv.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SCampaign::SCampaign(AccountIdType creatorAccountId, ClanIdType creatorClanId, const Char16* creatorClanName, const Char16* campaignName, RegionIdType regionId, REGION_OBJ_TYPE regionType)
		:mAttackCampOwnerAccountId(creatorAccountId)
		,mDefenseCampOwnerAccountId(0)

		,mCampaignCreatorAccountId(creatorAccountId)
		,mCampaignCreatorClanId(creatorClanId)
		,mCampaignCreatorClanName(creatorClanName)
		,mCampaignName(campaignName)
		,mCampaignTargetRegionId(regionId)
		,mCampaignTargetRegionType(regionType)
		,mCampaignInstanceUid(0)

		,mPrepareEndTime(0)
		
		,mPlaceListInfo(NULL)
		,mAtkListInfo(NULL)
		,mTimeListInfo(NULL)


		,mStartBattleTime(0)
		,mEndBattleTime(0)
		,mDestoryBattleTime(0)
		,mMarchTime(0)
		,mReachTime(0)
		
		,mWinnerForce(FORCE_INIT)
		,mIsStart(false)

		,mAttackMemberNum(0)
		,mDefenseMemberNum(0)
	{
		mStartBattleTime = GetCurrentTime();

		mPlaceListInfo = PlaceListCsv::getInstance().getPlaceListInfo(mCampaignTargetRegionId);
		DYNAMIC_ASSERT(NULL != mPlaceListInfo);

		InstanceListCsvInfo* instanceInfo = InstanceListCsv::getInstance().getInfoById(mPlaceListInfo->instanceId);
		mAtkListInfo =  InstanceAtkListCsv::getInstance().getInfoById(instanceInfo->instanceListId);
		DYNAMIC_ASSERT(NULL != mAtkListInfo);

		mTimeListInfo = InstanceTimeListCsv::getInstance().getInfoById(mAtkListInfo->intanceTimeId);
		DYNAMIC_ASSERT(NULL != mTimeListInfo);

		setEndBattleTime(mTimeListInfo->time2);

		for (Int i=0; i<POSITION_MAX; ++i)
		{
			ClanArmy* createAttack = mClanAttackList.createOrRetrieve((POSITION)i);
			createAttack->position = (POSITION)i;
			
			ClanArmy* createDefense = mClanDenfenseList.createOrRetrieve((POSITION)i);
			createDefense->position = (POSITION)i;
		}

		mClanAttackHost.createOrRetrieve(POSITION_1);
	}

	//-----------------------------------------------------------------------------
	SCampaign::~SCampaign()
	{
	}

	PlaceListCsvInfo* SCampaign::getPlaceListInfo()
	{
		return mPlaceListInfo;
	}

	InstanceAtkListCsvInfo* SCampaign::getAtkListInfo()
	{
		return mAtkListInfo;
	}

	InstanceTimeListCsvInfo* SCampaign::getTimeListInfo()
	{
		return mTimeListInfo;
	}
	//-----------------------------------------------------------------------------
	AccountIdType SCampaign::getAttackCampOwnerAccountId() const
	{
		return mAttackCampOwnerAccountId;
	}

	//-----------------------------------------------------------------------------
	void SCampaign::setAttackCampOwnerAccountId(const AccountIdType accountId)
	{
		mAttackCampOwnerAccountId = accountId;
	}

	//-----------------------------------------------------------------------------
	AccountIdType SCampaign::getDefenseCampOwnerAccountId() const
	{
		return mDefenseCampOwnerAccountId;
	}

	//-----------------------------------------------------------------------------
	void SCampaign::setDefenseCampOwnerAccountId(const AccountIdType accountId)
	{
		mDefenseCampOwnerAccountId = accountId;
	}

	//-----------------------------------------------------------------------------
	ClanIdType SCampaign::getCampaignCreatorClanId() const
	{
		return mCampaignCreatorClanId;
	}

	//-----------------------------------------------------------------------------
	AccountIdType SCampaign::getCampaignCreatorAccountId() const
	{
		return mCampaignCreatorAccountId;
	}

	//-----------------------------------------------------------------------------
	AccountIdType SCampaign::getRandomCampOwnerAccountId(const FORCE force, const AccountIdType currentOwnerAccountId)
	{
		AccountIdType targetCampOwnerAccountId = 0;
		if (FORCE_ATTACK == force)
		{
			targetCampOwnerAccountId = getRandomCampOwnerAccountId(mClanAttackList.getDataSet(), currentOwnerAccountId);
		}
		else if(FORCE_DEFENSE == force)
		{
			targetCampOwnerAccountId = getRandomCampOwnerAccountId(mClanDenfenseList.getDataSet(), currentOwnerAccountId);
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		return targetCampOwnerAccountId;
	}

	//-----------------------------------------------------------------------------
	AccountIdType SCampaign::getRandomCampOwnerAccountId(std::map<POSITION, ClanArmy*>* clanList, const AccountIdType currentOwnerAccountId)
	{
		for (std::map<POSITION, ClanArmy*>::iterator iter = clanList->begin(); iter != clanList->end(); ++iter)
		{
			ClanArmy* tempClanArmy = iter->second;
			DYNAMIC_ASSERT(NULL != tempClanArmy);
			if (false == tempClanArmy->empty() && currentOwnerAccountId != tempClanArmy->accountId)
			{
				return tempClanArmy->accountId;
			}
		}
		
		return 0;
	}

	//-----------------------------------------------------------------------------
	ClanIdType SCampaign::getCampaignId() const
	{
		return mCampaignCreatorClanId;
	}

	//-----------------------------------------------------------------------------
	Str16& SCampaign::getCampaignName()
	{
		return mCampaignName;
	}

	//-----------------------------------------------------------------------------
	Str16& SCampaign::getCampaignCreatorClanName()
	{
		return mCampaignCreatorClanName;
	}

	//-----------------------------------------------------------------------------
	RegionIdType SCampaign::getCampaignTargetRegionId() const
	{
		return mCampaignTargetRegionId;
	}

	REGION_OBJ_TYPE SCampaign::getCampaignTargetRegionType() const
	{
		return mCampaignTargetRegionType;
	}

	U32 SCampaign::getPrepareTimeSecond() const
	{
		return (mPrepareEndTime - GetCurrentTime()) / 1000;
	}
	
	void SCampaign::setPrepareTimeSecond(U32 prepareTime)
	{
		mPrepareEndTime = prepareTime * 1000 + GetCurrentTime();
	}

	//-----------------------------------------------------------------------------
	void SCampaign::setCampaignTargetInstanceId(InstanceUIdType campaignInstanceUid)
	{
		mCampaignInstanceUid = campaignInstanceUid;
	}

	//-----------------------------------------------------------------------------
	InstanceUIdType SCampaign::getCampaignTargetInstance() const
	{
		return mCampaignInstanceUid;
	}

	//-----------------------------------------------------------------------------
	std::map<POSITION, ClanArmy*>* SCampaign::getAttackMemberList()
	{
		return mClanAttackList.getDataSet();
	}

	//-----------------------------------------------------------------------------
	std::map<POSITION, ClanArmy*>* SCampaign::getDefenseMemberList()
	{
		return mClanDenfenseList.getDataSet();
	}

	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getAttackHostInfoByClanId()
	{
		DYNAMIC_ASSERT(mClanAttackHost.getDataSet()->size() == 1);

		return mClanAttackHost.getDataSet()->begin()->second;
	}

	//-----------------------------------------------------------------------------
	Int SCampaign::getDefenseMemberSize()
	{
		return mClanDenfenseList.getDataSet()->size();
	}

	//-----------------------------------------------------------------------------
	std::map<POSITION, ClanArmy*>* SCampaign::getAttackHostList()
	{
		return mClanAttackHost.getDataSet();
	}

	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getAttackHostClanArmyInfo()
	{
		DYNAMIC_ASSERT(getAttackHostList()->size() == 1);
		ClanArmy* hostArmy = getAttackHostList()->begin()->second;
		DYNAMIC_ASSERT(NULL != hostArmy && false == hostArmy->empty());
		return hostArmy;
	}


	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getMemberInfoByClanId(const ClanIdType clanId, std::map<POSITION, ClanArmy*>* memberList)
	{
		for (std::map<POSITION, ClanArmy*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			if (iter->second->clanID == clanId)
			{
				return iter->second;
			}
		}
		return NULL;
	}

	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getArmyByEmptyPosition(std::map<POSITION, ClanArmy*>* memberList)
	{
		for (std::map<POSITION, ClanArmy*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			if (iter->second->empty() == true)
			{
				return iter->second;
			}
		}
		return NULL;
	}

	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getAttackArmyByEmptyPosition()
	{
		return getArmyByEmptyPosition(getAttackMemberList());
	}

	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getDefenseArmyByEmptyPosition()
	{
		return getArmyByEmptyPosition(getDefenseMemberList());
	}

	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getAttackMemberInfoByClanId(const ClanIdType clanId)
	{
		return getMemberInfoByClanId(clanId, mClanAttackList.getDataSet());
	}

	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getAttackHostMemberInfoByClanId(const ClanIdType clanId)
	{
		return getMemberInfoByClanId(clanId, mClanAttackHost.getDataSet());
	}



	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getDefenseMemberInfoByClanId(const ClanIdType clanId)
	{
		return getMemberInfoByClanId(clanId, mClanDenfenseList.getDataSet());
	}

	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getClanArmyByClanId(const ClanIdType clanId)
	{
		ClanArmy* myInfo = getMemberInfoByClanId(clanId, mClanAttackHost.getDataSet());
		if (NULL != myInfo && false == myInfo->empty())
		{
			//找到了
			return myInfo;
		}

		//未找到， 继续找 【攻击方】
		myInfo = getMemberInfoByClanId(clanId, mClanAttackList.getDataSet());
		if (NULL != myInfo && false == myInfo->empty())
		{
			//找到了
			return myInfo;
		}

		//未找到， 继续找 【防守方】
		myInfo = getMemberInfoByClanId(clanId, mClanDenfenseList.getDataSet());
		if (NULL != myInfo && false == myInfo->empty())
		{
			//找到了
			return myInfo;
		}

		return NULL;
	}

	//-----------------------------------------------------------------------------
	Bool SCampaign::joinAttackList(NetIdType frontServerNetId, const U64 accountId,ClanIdType clanId, const Char16* clanName)
	{
		ClanArmy* army = NULL;
		if (clanId == getCampaignId())
		{
			//房主进来
			DYNAMIC_ASSERT(false == mClanAttackHost.empty());
			army = mClanAttackHost.getDataSet()->begin()->second;
			DYNAMIC_ASSERT(true == army->empty());

			army->readyState = ARMY_READY_CONFIRM;		//默认为准备完成
			army->position = POSITION_1;
		}
		else
		{
			// 普通玩家
			army = getAttackMemberInfoByClanId(clanId);
			DYNAMIC_ASSERT(NULL == army);
			army = getAttackArmyByEmptyPosition();
			army->readyState	= ARMY_READY_CANCEL;
		}
		
		if (NULL == army)
		{
			DYNAMIC_ASSERT(0);
		}

		army->accountId		= accountId;
		army->clanID		= clanId;
		army->force			= FORCE_ATTACK;
		army->frontServerNetId = frontServerNetId;
		army->clanName		= clanName;
		
		return true;
	}

	//-----------------------------------------------------------------------------
	Bool SCampaign::joinDefenseList(NetIdType frontServerNetId, const U64 accountId,ClanIdType clanId, const Char16* clanName)
	{
		ClanArmy* army	= getDefenseMemberInfoByClanId(clanId);
		DYNAMIC_ASSERT(NULL == army);
		army = getDefenseArmyByEmptyPosition();
		DYNAMIC_ASSERT(NULL != army && true == army->empty());
		army->readyState	= ARMY_READY_CONFIRM;
		army->accountId		= accountId;
		army->clanID		= clanId;
		army->force			= FORCE_DEFENSE;
		army->frontServerNetId = frontServerNetId;
		army->clanName		= clanName;

		return true;
	}

#if 0
	//-----------------------------------------------------------------------------
	POSITION SCampaign::getPositionByClan(ClanIdType clanId)
	{
		return (POSITION)(mClanAttackList.getDataSet()->size() - 1);
		//POSITION position = POSITION_INIT;
		//for (Int index = 0; index != mClanAttackList.getDataSet()->size(); ++index)
		//{
		//	if (true == mClanAttackList.hasData(clanId))
		//	{
		//		position = (POSITION)index;
		//		break;
		//	}
		//}

		//return position;
	}
#endif
	//-----------------------------------------------------------------------------
	Bool SCampaign::setCampaignReadyStateMySelf(ClanIdType myClanId, ARMY_READY_STATE readyState)
	{
		ClanArmy* army = getAttackMemberInfoByClanId(myClanId);
		if (NULL == army)
		{
			return false;
		}

		//if (army->position != position)
		//{
		//	return false;
		//}

		if (army->readyState == readyState)
		{
			return false;
		}

		army->readyState = readyState;
		//army->playerCharacterInfo.playerCharacterId = myHeroId;
		//army->playerCharacterInfo.playerCharacterName = playerCharacterName;
		//army->troopInfo.troopId = myTroopId;
		//army->troopInfo.troopTemplateId = myTroopTemplateId;
		return true;
	}

#if 0
	//-----------------------------------------------------------------------------
	ClanArmy* SCampaign::getClanArmyFromStandbyListById(const FORCE force, const ClanIdType clanId)
	{
		ClanArmy* army = NULL;
		if (force == FORCE_ATTACK)
		{
			army = getAttackMemberInfoByClanId(clanId);
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		return army;
	}
#endif
	//-----------------------------------------------------------------------------
	void SCampaign::setEndBattleTime(const U64 seconds)
	{ 
		mEndBattleTime = GetCurrentTime() + (seconds * 1000); 
	}

	//-----------------------------------------------------------------------------
	U64 SCampaign::getEndBattleTime() const
	{
		return mEndBattleTime;
	}

	//-----------------------------------------------------------------------------
	void SCampaign::setDestroyBattleTime(const U64 seconds)
	{ 
		mDestoryBattleTime = GetCurrentTime() + (seconds * 1000);
	}

	//-----------------------------------------------------------------------------
	U64 SCampaign::getDestroyBattleTime() const
	{
		return mDestoryBattleTime;
	}
	

	//-----------------------------------------------------------------------------
	Bool SCampaign::canStartBattle(const ClanIdType hostClanId)
	{
		//1. 检查 hostClanId 是不是主人
		if (NULL == getAttackHostMemberInfoByClanId(hostClanId))
		{
			return false;
		}
		
		//2. 检查 所有人是否准备好
		std::map<POSITION, ClanArmy*>* attackList = mClanAttackList.getDataSet();
		for (std::map<POSITION, ClanArmy*>::iterator iter = attackList->begin(); iter != attackList->end(); ++iter)
		{
			ClanArmy* clanArmy = iter->second;
			if (false == clanArmy->empty() && clanArmy->readyState == ARMY_READY_CANCEL)
			{
				return false;
			}
		}
	


		return true;
	}

	//-----------------------------------------------------------------------------
	Bool SCampaign::setReady(const ClanIdType myClanId)
	{
		ClanArmy* myClanArmy = getAttackMemberInfoByClanId(myClanId);
		if (NULL == myClanArmy || true == myClanArmy->empty())
		{
			return false;
		}

		if (ARMY_READY_CANCEL == myClanArmy->readyState)
		{
			myClanArmy->readyState = ARMY_READY_CONFIRM;
		}
		else if(ARMY_READY_CONFIRM == myClanArmy->readyState)
		{
			myClanArmy->readyState = ARMY_READY_CANCEL;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		return true;
	}

	//-----------------------------------------------------------------------------
	void SCampaign::setAttackRealMemberNum(Int num)
	{
		mAttackMemberNum = num;
	}

	//-----------------------------------------------------------------------------
	Int SCampaign::getAttackRealMemberNum() const
	{
		return mAttackMemberNum;
	}

	//-----------------------------------------------------------------------------
	void SCampaign::setDefenseRealMemberNum(Int num)
	{
		mDefenseMemberNum = num;
	}

	//-----------------------------------------------------------------------------
	Int SCampaign::getDefenseRealMemberNum() const
	{
		return mDefenseMemberNum;
	}

	//-----------------------------------------------------------------------------
	Bool SCampaign::isAllClanLeave()
	{
		std::map<POSITION, ClanArmy*>* clanList = NULL;
		
		//遍历
		{
			clanList = mClanAttackHost.getDataSet();
			for (std::map<POSITION, ClanArmy*>::iterator iter = clanList->begin(); iter != clanList->end(); ++iter)
			{
				if (false == iter->second->empty() && false == iter->second->isLeave)
				{
					return false;
				}
			}
		}

		//遍历
		{
			clanList = mClanAttackList.getDataSet();
			for (std::map<POSITION, ClanArmy*>::iterator iter = clanList->begin(); iter != clanList->end(); ++iter)
			{
				if (false == iter->second->empty() && false == iter->second->isLeave)
				{
					return false;
				}
			}
		}

		//遍历
		{
			clanList = mClanDenfenseList.getDataSet();
			for (std::map<POSITION, ClanArmy*>::iterator iter = clanList->begin(); iter != clanList->end(); ++iter)
			{
				if (false == iter->second->empty() && false == iter->second->isLeave)
				{
					return false;
				}
			}
		}
		
		return true;
	}
	//-----------------------------------------------------------------------------
}