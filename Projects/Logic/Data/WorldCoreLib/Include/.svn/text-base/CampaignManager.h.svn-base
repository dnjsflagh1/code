//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\CampaignManager.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 10:06
//   Description: 
//			战斗管理器
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-23      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _CAMPAIGN_MANAGER_H_
#define _CAMPAIGN_MANAGER_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "SCampaign.h"

/******************************************************************************/

/******************************************************************************/
namespace MG
{
	/**********************************************************************/
	class CampaignManager
	{
	public:
		CampaignManager();
		virtual ~CampaignManager();

		void	update();
		virtual void	sendCampaignEndPacket(SCampaign* campaign, const FORCE winnerForce) { }
		virtual void	sendCampaignDestroyPacket(SCampaign* campaign, const FORCE winnerForce) { }

	public:
		SCampaign*	createCampaign(NetIdType frontServerNetId, AccountIdType creatorAccountId, ClanIdType creatorClanId, const Char16* creatorClanName, const Char16* campaignName, 
								RegionIdType regionId,REGION_OBJ_TYPE targetRegionType);

		void	destroyCampaign(CampaignIdType campaignId);
		void	delEndCampaign(CampaignIdType campaignId);
		
		SCampaign*	enterCampaignJoinAttackList(NetIdType frontServerNetId, const AccountIdType accountId, const ClanIdType campainId, const ClanIdType myClanId, const Char16* clanName);
		SCampaign*	enterCampaignJoinAttackList(NetIdType frontServerNetId, const AccountIdType accountId, SCampaign* campaign, const ClanIdType myClanId, const Char16* clanName);

		Bool	setCampaignReadyStateMySelf(CampaignIdType campaignId, ClanIdType myClanId, ARMY_READY_STATE readyState);


		//Bool	startCampaign(CampaignIdType campaignId, ClanIdType myClanId);	//开始战斗
		Bool	addCampaignStart(SCampaign* campaign, U64 battleSecond);


		bool	checkCampaignTimeOut(const U64 curTime);
		bool	checkCampaignDestroy(const U64 curTime);


	public:
		SCampaign*		getBattleCampaign(CampaignIdType campaignId);
		SCampaign*		getPrepareCampaign(CampaignIdType campaignId);
		SCampaign*		popPrepareCampaign(CampaignIdType campaignId);
		SCampaign*		getEndCampaign(CampaignIdType campaignId);
		std::map<ClanIdType, SCampaign*>*		getPrepareCampaignList();
		std::map<ClanIdType, SCampaign*>*		getOnBattleCampaignList();
		std::map<ClanIdType, SCampaign*>*		getEndCampaignList();

		void			clear();
		void			clearPrepareCampaign();

		//主兵营摧毁 战斗结束
		void mainCampDestroy(const CampaignIdType campaignId, const FORCE winnerForce);
	private:
		Bool 				_isCampaignExist(ClanIdType clanID);
		Bool 				_isCampaignNameExist(const Char16* campaignName);

	private:
		SimpleMapDataSetManager<ClanIdType, SCampaign>			mPrepareCompaignList;	//准备中的队列
		MapManager<CampaignIdType, SCampaign*>					mOnBattleList;			//战斗中的队列
		MapManager<CampaignIdType, SCampaign*>					mEndBattleList;			//结束的队列

		U64				mLastCheckEndTime;		//每2秒检查一次 mOnBattleList
		U64				mLastCheckDestroyTime;	//每2秒检查一次 mEndBattleList
	};
}

#endif	//_CAMPAIGN_MANAGER_H_