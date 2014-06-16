#ifndef _CCAMPAIGN_H_
#define _CCAMPAIGN_H_

/******************************************************************************/
#include "WorldCorePreqs.h"
#include "DataSetManager.h"
//#include "SCampaign.h"

/******************************************************************************/

#define CAMPAIGN_BATTLE_TIME		(30*1000*1000*1000)		//游戏开始30分钟后结束

/******************************************************************************/
namespace MG
{
	// 战场军队状态
	enum CCAMPAIGN_ARMY_STATE
	{
		CCAMPAIGN_ARMY_STATE_NULL,
		CCAMPAIGN_ARMY_STATE_ENTER,
		CCAMPAIGN_ARMY_STATE_CANCEL,
		CCAMPAIGN_ARMY_STATE_CONFIRM,
		CCAMPAIGN_ARMY_STATE_MAX,
	};

	// 战场状态
	//-------------------------------------------------------------
	enum CCAMPAIGN_STATE
	{
		CCAMPAIGN_STATE_NULL,
		CCAMPAIGN_STATE_PREASSIGNMENT,
		CCAMPAIGN_STATE_ASSIGNMENT,
		CCAMPAIGN_STATE_APPLIING,
		CCAMPAIGN_STATE_APPLIED,
		CCAMPAIGN_STATE_ENTER,
		CCAMPAIGN_STATE_PREPARED,
		CCAMPAIGN_STATE_START,
		CCAMPAIGN_STATE_ALL_ENTER,
		CCAMPAIGN_STATE_END,
		CCAMPAIGN_STATE_APPLIEDERR,
	};
	
	// 战场军队信息
	//-------------------------------------------------------------
	struct CCampaignArmyInfo
	{
		NetIdType						frontServerNetId;
		NetIdType						clientNetId;
		FORCE							force;
		CCAMPAIGN_ARMY_STATE			state;
		Bool							jumpOut;
		CCampaignArmyInfo()
		{
			frontServerNetId = -1;
			clientNetId = -1;
			force = FORCE_INIT;
			state = CCAMPAIGN_ARMY_STATE_NULL;
			jumpOut = true;
		}
	};
	//-------------------------------------------------------------
	class CCampaignManager;
	class CClient;
	class CCampaign
	{
	public:
		CCampaign();
		~CCampaign();
		void								clear();
		void								reset();
		void								restorePreassignmentState();

	public:
		void								addMember(FORCE force,std::vector<CClient*>& members);
		
	public:
		// 申请战场房间
		void								netCreateCampaign();
		// 销毁房间
		void								netDestoryCampaignRoom();
		// 进入战场房间
		void								enterCampaign();
		// 准备
		void								ready();
		// 取消
		void								cancle();
		// 战场开始
		void								startBattle();
		// 战场是否可以开启
		Bool								canStartBattle();	
		// 防守方进入战场
		void								denfenseEnter();
		// 放弃战场
		void								giveUpCampaign();

	public:
		Str16&								getCampaignName();
		void								setCampaignName(Char16* name);
		RegionIdType						getCampaignTargetRegionId() const;
		void								setRegionId(RegionIdType id);
		CampaignIdType						getCampaignId();
		void								setCampaignId(CampaignIdType id);
	
		InstanceUIdType						getCampaignInstance();
		void								setCampaignInstanceId(InstanceUIdType campaignInstanceUid);
		

		void 								setBattleTime(const U64 seconds);
		U64 								getBattleTime() const;

		Int									getMemberNum() const;
		void								setMemberNum(Int number);

		Int									getEnterCampaignRoomNum();
		Int									getReadyCampaignRoomNum();

		Bool								isOwned();
		void								setOwned(Bool isOwned);

		CClient*							getHost();
		CCAMPAIGN_STATE						getState();
		void								setState(CCAMPAIGN_STATE state);
		CCampaignArmyInfo*					getArmyInfo(CClient* client);
		Bool								isAllJumpOut();
		Bool								isStart();
		
		Bool								checkCompleteEnter();
		Bool								checkCompleteConfirm();

		CCampaignArmyInfo*					getArmyInfo(PlayerCharacterIdType id);

		std::map<CClient*,CCampaignArmyInfo*>* getAttackList();

		Bool								isDenfense(CClient* client);
		Bool								isAttacket(CClient* client);
		
		Int									getCycleCount();
	
	private:
		RegionIdType						mCampaignTargetRegionId;
		InstanceUIdType						mCampaignInstanceUid;

		Str16								mCampaignName;
		
		// 房主
		CClient*							mClanAttackHost;	
		// 攻击方
		std::map<CClient*,CCampaignArmyInfo*>mClanAttackList;
		// 防守方
		std::map<CClient*,CCampaignArmyInfo*>mClanDenfenseList;		
		
		// 战场成员数
		Int									mMemberNum;				
		
		// 赢家势力
		FORCE								mWinner;

		// 是否开启
		Bool								mIsStart;				

		// 开始时间
		U64									mStartBattleTime;
		// 结束时间
		U64									mEndBattleTime;
		
		// 本战场是否受管理
		Bool								mIsOwned;

		// 战场当前状态
		CCAMPAIGN_STATE						mState;

		Int									mCycleCount;

		CampaignIdType						mCampaignId;
	};
}

#endif	//_CCAMPAIGN_H_