//*************************************************************************************
#ifndef _UICAMPAIGNLIST_NEW_H_
#define _UICAMPAIGNLIST_NEW_H_

//*************************************************************************************

#include "UIObject.h"
#include "ClientPreqs.h"

//*************************************************************************************

namespace MG
{

	//*************************************************************************************
	struct UICampaignSingleInfo	//显示的UI信息
	{
		CampaignIdType		campaignUId;
		RegionIdType		targetRegionId;
		Int					curPlayerNum;		//当前人数
		Int					maxPlayerNum;		//最大人数

		Str16				strState;
		Str16				strUId;
		Str16				strTargetRegionName;
		Str16				strCampaignName;

		Str16				strCurPlayerStr;
		Str16				strEnctryptionName;

		UICampaignSingleInfo()
			:campaignUId(0)
			,targetRegionId(0)
			,curPlayerNum(0)
			,maxPlayerNum(0)
		{

		}
		void clear()
		{
			campaignUId = 0;
			targetRegionId = 0;
			curPlayerNum = 0;
			maxPlayerNum = 0;
			
			strState.clear();
			strUId.clear();
			strTargetRegionName.clear();
			strCampaignName.clear();

			strCurPlayerStr.clear();
			strEnctryptionName.clear();
		}
	};

	//*************************************************************************************
	struct UITargetRegionSingleInfo
	{
		RegionIdType	regionId;
		REGION_OBJ_TYPE regionType;
		std::wstring regionName;

		UITargetRegionSingleInfo()
			:regionId(0)
			,regionType(ROT_UNKNOWN)
		{
			regionName.clear();
		}
	};


	//*************************************************************************************
	class  UICampaignListNew : public UIObject
	{
	public:
		UICampaignListNew();
		virtual ~UICampaignListNew();
		SINGLETON_INSTANCE(UICampaignListNew);


	public:
		virtual void setEvent();
		virtual Bool openGui();

	public:
		static void onEventCampaignCreate(void* widget);

		static void onEventCampaignSelectTarget(void* widget, Int index);

		static void onDoubleClickCampaignInfo( void* widget,Int index );		//双击某个房间
		static void onClickCampaignInfo( void* widget,Int index );				//单击某个房间

	public:
		void UIReFresh();
		void UIReFreshCampaignList();
		void UIReFreshTargetRegionList();

		void loadTargetRegionList();


	public:

		void loadCampaignList();
		void addCampaignInfo(UICampaignSingleInfo* info);
		void clearCampaignList();

	private:
		void setButtonState(IWidget* pWidget);

	private:
		void testCreateCampaign();
	private:
		std::vector<UICampaignSingleInfo>				mCampaignList;


		std::vector<UITargetRegionSingleInfo>			mTargetRegionList;

	};
}

#endif	//_UICAMPAIGNLIST_NEW_H_