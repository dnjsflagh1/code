//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: SCampaign.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 10:18
//   Description: 
//			服务器端使用的战斗实例
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-23      add
//////////////////////////////////////////////////////////////

#ifndef _S_CAMPAIGN_H_
#define _S_CAMPAIGN_H_

/******************************************************************************/

#include "WorldCorePreqs.h"
#include "DataSetManager.h"

#include "InstanceTimeListCsv.h"
//#include "Campaign.h"

/******************************************************************************/

#define CAMPAIGN_BATTLE_TIME		(30*1000*1000)		//游戏开始30分钟后结束

/******************************************************************************/
namespace MG
{
	enum ARMY_READY_STATE
	{
		ARMY_READY_INITIAL,
		ARMY_READY_CANCEL,
		ARMY_READY_CONFIRM,
		ARMY_READY_MAX,
	};





	//武将信息
	struct ClanArmyPlayerCharacterInfo	
	{
		U64		playerCharacterId;
		Str16	playerCharacterName;
		U32		charArtIcon;

		ClanArmyPlayerCharacterInfo()
			:playerCharacterId(0)
			,charArtIcon(0)
		{
			playerCharacterName.reserve(MAX_CHARACTER_NAME_LEN);
		}

		void clear()
		{
			playerCharacterId = 0;
			charArtIcon = 0;

		}
	};

	//军队信息
	struct ClanArmyTroopInfo
	{
		U64		troopId;
		U64		troopTemplateId;
		//Char16	troopName[MAX_TROOP_NAME_LEN];
		ClanArmyTroopInfo()
			:troopId(0)
			,troopTemplateId(0)
		{

		}
	};

	//武将和部队列表
	struct ClanArmy
	{
		NetIdType						frontServerNetId;
		NetIdType						clientNetId;
		U64								accountId;
		ClanIdType						clanID;
		Str16							clanName;
		FORCE							force;
		ARMY_READY_STATE				readyState;
		POSITION						position;
		Bool							isLeave;

		ClanArmyPlayerCharacterInfo		playerCharacterInfo;
		
		ClanArmy()
		{
			clear();
		}

		void clear()
		{
			frontServerNetId = 0;
			clientNetId = 0;
			accountId = 0;
			clanID = 0;
			force = FORCE_INIT;
			readyState = ARMY_READY_INITIAL;
			clanName.clear();
			isLeave = false;
			playerCharacterInfo.clear();
		}

		Bool empty()
		{
			if (0 != frontServerNetId	||
				0 != clientNetId		||
				0 != accountId			||
				0 != clanID				||
				FORCE_INIT != force		||
				ARMY_READY_INITIAL != readyState ||
				false == clanName.empty())
			{
				return false;
			}

			return true;
		}

	};

	/******************************************************************************/
	class SCampaign
	{
	public:
		SCampaign(AccountIdType creatorAccountId, ClanIdType creatorClanId, const Char16* creatorClanName, const Char16* campaignName, RegionIdType regionId, REGION_OBJ_TYPE regionType);
		~SCampaign();

		PlaceListCsvInfo*				getPlaceListInfo();
		InstanceAtkListCsvInfo*			getAtkListInfo();
		InstanceTimeListCsvInfo*		getTimeListInfo();

	public:

		AccountIdType	getAttackCampOwnerAccountId() const;
		void			setAttackCampOwnerAccountId(const AccountIdType accountId);
		AccountIdType	getDefenseCampOwnerAccountId() const;
		void			setDefenseCampOwnerAccountId(const AccountIdType accountId);

		//随机在在线玩家中查找 军营控制者
		AccountIdType	getRandomCampOwnerAccountId(const FORCE force, const AccountIdType currentOwnerAccountId);
		AccountIdType	getRandomCampOwnerAccountId(std::map<POSITION, ClanArmy*>* clanList, const AccountIdType currentOwnerAccountId);

		ClanIdType		getCampaignCreatorClanId() const;
		AccountIdType	getCampaignCreatorAccountId() const;
		ClanIdType		getCampaignId() const;
		Str16&			getCampaignName();
		Str16&			getCampaignCreatorClanName();

		RegionIdType	getCampaignTargetRegionId() const;
		REGION_OBJ_TYPE getCampaignTargetRegionType() const;

		//获得战斗开始前准备时间
		void			setPrepareTimeSecond(U32 prepareTime);
		U32				getPrepareTimeSecond() const;

		void					setCampaignTargetInstanceId(InstanceUIdType campaignInstanceUid);
		InstanceUIdType			getCampaignTargetInstance() const;
	
		std::map<POSITION, ClanArmy*>*  getAttackHostList();
		std::map<POSITION, ClanArmy*>*  getAttackMemberList();
		std::map<POSITION, ClanArmy*>*  getDefenseMemberList();

		ClanArmy*		getAttackHostClanArmyInfo();
		
		Int				getDefenseMemberSize();

		// 房主列表中找
		ClanArmy*		getAttackHostMemberInfoByClanId(const ClanIdType clanId);	
		ClanArmy*		getAttackHostInfoByClanId();								//查找房主信息

		//查找空位子
		ClanArmy*		getAttackArmyByEmptyPosition(const ClanIdType clanId);
		
		//查找自己的信息
		ClanArmy*		getAttackMemberInfoByClanId(const ClanIdType clanId);
		ClanArmy*		getDefenseMemberInfoByClanId(const ClanIdType clanId);
		ClanArmy*		getClanArmyByClanId(const ClanIdType clanId);		//所有列表中找
		
		//找空位置
		ClanArmy*		getAttackArmyByEmptyPosition();
		ClanArmy*		getDefenseArmyByEmptyPosition();
		
	
		//所有的玩家都离开， 则立即结束
		Bool			isAllClanLeave();
	public:
		Bool 	joinAttackList(NetIdType frontServerNetId, const U64 accountId,ClanIdType clanId, const Char16* clanName);
		Bool 	joinDefenseList(NetIdType frontServerNetId, const U64 accountId,ClanIdType clanId, const Char16* clanName);
		Bool 	setCampaignReadyStateMySelf(ClanIdType myClanId, ARMY_READY_STATE readyState);

		void 	setEndBattleTime(const U64 seconds);
		U64 	getEndBattleTime() const;

		void	setDestroyBattleTime(const U64 seconds);
		U64		getDestroyBattleTime() const;

		Bool	canStartBattle(const ClanIdType hostClanId);	//检查这个战斗是否满足开始条件
		Bool	setReady(const ClanIdType myClanId);			//设置准备


		void	setAttackRealMemberNum(Int num);
		Int		getAttackRealMemberNum() const;
		void	setDefenseRealMemberNum(Int num);
		Int		getDefenseRealMemberNum() const;
	

		FORCE	getWinnerForce() const						{ return mWinnerForce;			}
		void	setWinnerForce(const FORCE winnerForce)		{ mWinnerForce = winnerForce;	}

		Bool	getCampaignIsStart() const			{ return mIsStart;		}
		void	setCampaignIsStart(Bool isStart)	{ mIsStart = isStart;	}


	private:
		ClanArmy*		getMemberInfoByClanId(const ClanIdType clanId, std::map<POSITION, ClanArmy*>* memberList);
		ClanArmy*		getArmyByEmptyPosition(std::map<POSITION, ClanArmy*>* memberList);


	private:
		//SRealRegionObject*		mOwnerRealRegionObject;				//攻击目标指针

		AccountIdType					mAttackCampOwnerAccountId;			//控制所有军营的分配权，如果该角色离开，则随机选一个 默认是房主
		AccountIdType					mDefenseCampOwnerAccountId;

		AccountIdType					mCampaignCreatorAccountId;					//发起家族AccountId
		ClanIdType						mCampaignCreatorClanId;						//发起家族
		Str16							mCampaignCreatorClanName;					//发起家族名字
		Str16							mCampaignName;								//战役名字
		
		RegionIdType					mCampaignTargetRegionId;
		REGION_OBJ_TYPE					mCampaignTargetRegionType;
		InstanceUIdType					mCampaignInstanceUid;						//MapServer创建的副本
		U64								mPrepareEndTime;							//战斗开始前准备时间 结束时刻

		PlaceListCsvInfo*				mPlaceListInfo;
		InstanceAtkListCsvInfo*			mAtkListInfo;
		InstanceTimeListCsvInfo*		mTimeListInfo;

		U64						mStartBattleTime;							//发起时间
		U64						mEndBattleTime;								//结束时间【关闭战役】
		U64						mDestoryBattleTime;							//真正结束， 玩家跳转地图
		U64						mMarchTime;									//行军时间
		U64						mReachTime;									//到达时间	【需要计算出来】

		FORCE					mWinnerForce;								//胜利者的势力
		Bool					mIsStart;									//是否已经开始

		SimpleMapDataSetManager<POSITION, ClanArmy>		mClanAttackHost;	//攻击方房主
		SimpleMapDataSetManager<POSITION, ClanArmy>		mClanAttackList;	//攻击方列表
		SimpleMapDataSetManager<POSITION, ClanArmy>		mClanDenfenseList;	//防守方列表

		Int						mAttackMemberNum;									// 房间里的人数
		Int						mDefenseMemberNum;									// 房间里的人数
	private:
		SCampaign();
		SCampaign(const SCampaign&);
		SCampaign& operator=(const SCampaign&);
	};
}

#endif	//_S_CAMPAIGN_H_