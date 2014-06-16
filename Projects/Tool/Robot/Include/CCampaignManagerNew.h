/******************************************************************************/
#ifndef _CCAMPAIGNMANAGERNEW_H_
#define _CCAMPAIGNMANAGERNEW_H_
/******************************************************************************/
#include "ClientPreqs.h"
/******************************************************************************/

/******************************************************************************/

namespace MG
{
	/**********************************************************************/
	class CCampaign;
	enum CampaignCtrlState
	{
		CampaignCtrlState_CanStart,
		CampaignCtrlState_Ending,
		CampaignCtrlState_CanntStart,

	};
	class CCampaignManager
	{
	public:
		CCampaignManager(U32 threadIndex);
		~CCampaignManager();

	public:
		// 重置
		void clear();

		///////////////////////////////////////////////////////////////////////////////////
		// 预分配战场1
		Int preassignmentCampaignList(Int campaignNum,Int armyNum,U32 time); 

		// 获取战场列表
		void getCampaignListFromServer();
		
		//分配战场
		void assignmentCampaign();

		// 向服务器请求创建战场房间1
		void createCampaignRoomListToServer();

		// 向服务器请求创建战场
		void createCampaignListToServer();

		// 向服务器请求结束战场1
		void endBattleToServer();


		Bool				isTimeOut();

		void				update();

		void				setTimeOut(U32 time);

		CampaignCtrlState	getCtrlState();

		Bool				isAllCampaignEnd();
		///////////////////////////////////////////////////////////////////////////////////
		RegionIdType							getCCCRegion();					// 获得可创建战场的地图
		std::map<RegionIdType,Str16>*			getCCCRegions();				// 获得可创建战场的地图链表
		std::map<RegionIdType,Str16>*			getNCCRegions();				// 获得不可创建战场的地图链表
		void									clearCCCRegions();				// 清空战场地图链表
		void									clearNCCRegions();
		void									resetRegions();					// 重设战场地图链表
		
		void									clearCampaignsInServer();		// 清空在服务器战场表
		std::map<RegionIdType,CampaignIdType>*	getCampaignsInServer();			// 获得服务器战场表
		
		void									addOwnedCampaignById(CampaignIdType id,CCampaign* campaign);
		std::map<CampaignIdType,CCampaign*>*	getOwnedCampaigns();			// 获得管理器管理的战场
		CCampaign*								getOwnedCampaignByRegionId(RegionIdType regionId);
		CCampaign*								getOwnedCampaignById(CampaignIdType id);
		CCampaign*								removeOwnedCampaignById(CampaignIdType id);

		std::vector<CCampaign*>					getPreassignmentCampaigns();	// 获得预分配的战场



		Bool									canCreateCampagin();
		Bool									setCanCreateCampagin(Bool canCreate);
		///////////////////////////////////////////////////////////////////////////////////
		void									setThreadIndex(Int threadIndex);
	private:
		// 预分配的战场
		std::vector<CCampaign*>						mPreassignmentCampaigns;

		// 本管理器管理的战场
		std::map<CampaignIdType,CCampaign*>			mOwnedCampaigns;


		// 从服务器获取的最新战场
		std::map<RegionIdType,CampaignIdType>		mCampaignsInServer;

		// 可创建的战争的地图
		std::map<RegionIdType,Str16>				mRegionsCanCreate;

		// 不可创建的战争的地图
		std::map<RegionIdType,Str16>				mRegionsCanntCreate;
		
		Int											mThreadIndex;

		Bool										mIsCanCreateCampaign;

		U64											mEndTime;

		CampaignCtrlState							mCtrlState;

		Bool										mIsEnd;
	};
}

#endif	//_CCAMPAIGNMANAGERNEW_H_