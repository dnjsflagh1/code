//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\CenterServer\Include\SCampaignManager.h
//        Author: yuanlinhu
//          Date: 2012-5-14
//          Time: 15:24
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-5-14      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _CCAMPAIGNMANAGER_H_
#define _CCAMPAIGNMANAGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
//#include "CampaignManager.h"

/******************************************************************************/

/******************************************************************************/

namespace MG
{
	/**********************************************************************/
	class CCampaign;
	class CCampaignManager
	{
	public:
		CCampaignManager();
		~CCampaignManager();
		SINGLETON_INSTANCE(CCampaignManager);

	public:

		void		init();
		
		void		netGetCampaignList();
		// �ܹ����ս��
		Bool		createCampaign(Int campaignNum,Int armyNum);
		
		CCampaign*	getCampaign(CampaignIdType id);
		CCampaign*	getCampaignByRegionId(RegionIdType id);
		CCampaign*	getCampaignByRegionId(RegionIdType id, CampaignIdType& campaignId);
		
		// ���ܹ����ս�� �ⲿ��Ҫ������Ƿ����
		void		addCampaign(CampaignIdType id,CCampaign* campaign);
		void		clear();

		void		netCreateCampaign();
		void		startBattle();

		void		removeCampaign(CampaignIdType id);

		Bool		isAllCampaignEnd();
		Bool		isCanCreate();

		void		removeCreateRegion(RegionIdType id,Bool canCreate = true);

		// ��ÿɴ���ս���ĵ�ͼ
		std::map<RegionIdType,Str16>*		getRegionsCanCreate();
		std::map<RegionIdType,Str16>*		getRegionsCanntCreate();

		std::map<CampaignIdType,CCampaign*>* getCampaigns();
		std::map<RegionIdType,Str16>*		 getCanCreateRegions();
		RegionIdType						 getCanCreateRegion();
	private:
		std::map<CampaignIdType,CCampaign*>	mCampaigns;

		// �ɴ�����ս���ĵ�ͼ
		std::map<RegionIdType,Str16>		mRegionsCanCreate;

		// ���ɴ�����ս���ĵ�ͼ
		std::map<RegionIdType,Str16>		mRegionsCanntCreate;
		
		Bool								mIsInit;
		Bool                                mIsCanCreate;

	};
}

#endif	//_C_CAMPAIGN_MANAGER_H_