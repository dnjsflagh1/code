
//*************************************************************************************

#include "stdafx.h"
#include "UICampaignListNew.h"
#include "UIMessageBox.h"
#include "CampaignNetPacketProcesser.h"
#include "CPlayer.h"
#include "MapListCsv.h"
#include "CCampaignManager.h"
#include "CRegionManager.h"
#include "InstanceListCsv.h"

//*************************************************************************************

#define  COMBO_TARGET_LIST	"Combo_Target_List"

//*************************************************************************************

#define 	CAMP_MAIN_RECT_W			430
#define 	CAMP_MAIN_RECT_H			33


#define		CAMP_SPACE_Y				4			//两个房间信息的 间隔


#define		CAMP_STATE_X				8			//【状态】	X
#define		CAMP_STATE_Y				8			//【状态】	Y
#define		CAMP_STATE_W				25			//宽度

#define		CAMP_UID_X					56			//【序号】
#define		CAMP_UID_Y					8
#define		CAMP_UID_W					50

#define		CAMP_TARGET_REGION_X		112			//【攻击目标】
#define		CAMP_TARGET_REGION_Y		8
#define		CAMP_TARGET_REGION_W		80

#define		CAMP_CAMPAIGN_NAME_X		192			//【队伍名称】
#define		CAMP_CAMPAIGN_NAME_Y		8
#define		CAMP_CAMPAIGN_NAME_W		100

#define		CAMP_MEMBER_NUM_X			296			//【人数】
#define		CAMP_MEMBER_NUM_Y			8
#define		CAMP_MEMBER_NUM_W			50

#define		CAMP_ENCRYPTION_X			352			//【加密】
#define		CAMP_ENCRYPTION_Y			8
#define		CAMP_ENCRYPTION_W			20
//*************************************************************************************
namespace MG
{
	UICampaignListNew::UICampaignListNew()
	{
		//testCreateCampaign();
	}

	//------------------------------------------------------------------------
	UICampaignListNew::~UICampaignListNew()
	{

	}

	//------------------------------------------------------------------------
	void UICampaignListNew::setEvent()
	{
		//【新建军队】
		{
			IButton* btnCreateCampaign = getLayout()->getButton("button_CampaignCreate");
			btnCreateCampaign->getWidget()->setMouseButtonClickEvent(onEventCampaignCreate);
		}

		{
			IEdit* editCampaignName = getLayout()->getEdit("edit_CampaignName");
		}

		{
			IComboBox* comboTarget = UICampaignListNew::getInstance().getLayout()->getComboBox(COMBO_TARGET_LIST);
			comboTarget->setComboAcceptEvent(onEventCampaignSelectTarget);
		}
	}

	void UICampaignListNew::testCreateCampaign()
	{
#if 0
		for (Int i=1; i<= 10; ++i)
		{
			UICampaignSingleInfo info1;
			info1.campaignUId = i;
			info1.targetRegionId = i;
			info1.curPlayerNum = i;
			info1.maxPlayerNum = i+100;

			wchar_t mainName[32] = L"";
			swprintf(mainName,L"家族%d", i);

			wchar_t mainState[32] = L"";
			swprintf( mainState, L"战斗%d", i);

			info1.creatorClanName.append(mainName);
			info1.campaignName.append(mainState);
			addCampaignInfo(&info1);
		}
#endif

		int ii = 0;
	}
	//--------------------------------------------------------------------------------
	Bool UICampaignListNew::openGui()
	{
		if (  false == UIObject::isOpen() )
		{
			UIObject::openGui();
			
			UIReFreshTargetRegionList();
			UIReFreshCampaignList();
		}
		else
		{
			UIObject::closeGui();
		}
		
		
		
		

		return true;
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::onEventCampaignSelectTarget(void* widget, Int index)
	{
		
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::onEventCampaignCreate(void* widget)
	{
		//读取攻击目标名字
		IComboBox* comboTarget = UICampaignListNew::getInstance().getLayout()->getComboBox(COMBO_TARGET_LIST);
		Int index = comboTarget->getIndexSelected();
		if (index > -1)
		{
			IAny* tempAny = comboTarget->getItemDataAt(index);
			if (NULL == tempAny)
			{
				return ;
			}
			UITargetRegionSingleInfo* targetRegionInfo = tempAny->castType<UITargetRegionSingleInfo>();
			//if (index < 0 || index > UICampaignListNew::getInstance().getTargetListSize())
			//{
			//	//
			//	UIMessageBox::getInstance().showHint(L"错误索引");
			//	return;
			//}
			//targetInfo* target = UICampaignListNew::getInstance().getTargetInfoByIndex(index);

			//读取战斗名字
			IEdit* campaignName = UICampaignListNew::getInstance().getLayout()->getEdit("edit_CampaignName");
			std::wstring campaignNameStr = campaignName->getCaption();

			if (campaignNameStr.empty())
			{
				//名字不能为空
				UIMessageBox::getInstance().showHint(L"战斗名字不能为空");
				return;
			}

			//自己的家族ID
			U64 creatorClanId = CPlayer::getInstance().getActiveClan()->getClanID();

			CampaignNetPacketProcesser::getInstance().sendCampaignCreate(creatorClanId, targetRegionInfo->regionId, campaignNameStr.c_str(), targetRegionInfo->regionType);
			int kk = 0;
		}
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::onClickCampaignInfo( void* widget,Int index )
	{
		//IWidget* curWidget = (IWidget*)widget;
		//if (NULL == curWidget)
		//{
		//	return;
		//}
		//IMixList* pMixList = (IMixList*)widget;
		//IMixListRow* pIMixListRow = pMixList->getMixListRowByIndex(index);
		//DYNAMIC_ASSERT(pIMixListRow);

		//IAny* pAny = pIMixListRow->getWidget()->getUserData();
		//DYNAMIC_ASSERT(pAny);

		//UICampaignSingleInfo* info = pAny->castType<UICampaignSingleInfo>(pAny);
		//DYNAMIC_ASSERT(NULL != info);

		//CampaignNetPacketProcesser::getInstance().sendCampaignEnter( CPlayer::getInstance().getActiveClanId(), info->campaignUId);
		////UICampaignListNew::getInstance().setButtonState(curWidget);
		
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::onDoubleClickCampaignInfo( void* widget,Int index )
	{
		IMixList* pMixList = (IMixList*)widget;
		IMixListRow* pIMixListRow = pMixList->getMixListRowByIndex(index);
		DYNAMIC_ASSERT(pIMixListRow);
		
		IAny* pAny = pIMixListRow->getWidget()->getUserData();
		DYNAMIC_ASSERT(pAny);

		UICampaignSingleInfo* info = pAny->castType<UICampaignSingleInfo>(pAny);
		DYNAMIC_ASSERT(NULL != info);
		
		CampaignNetPacketProcesser::getInstance().sendCampaignEnter( CPlayer::getInstance().getActiveClanId(), info->campaignUId);
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::loadCampaignList()
	{
		std::map<ClanIdType, SCampaign*>* prepareCampaignList = CCampaignManager::getInstance().getPrepareCampaignList();
	
		UICampaignListNew::getInstance().clearCampaignList();
		UICampaignSingleInfo info;
		for (std::map<ClanIdType, SCampaign*>::iterator iter = prepareCampaignList->begin(); iter != prepareCampaignList->end(); ++iter)
		{
			info.clear();

			

			SCampaign* campaignInfo = iter->second;

			

			info.campaignUId		= campaignInfo->getCampaignId();
			info.targetRegionId		= campaignInfo->getCampaignTargetRegionId();
			info.curPlayerNum		= campaignInfo->getAttackRealMemberNum();
			info.maxPlayerNum		= (Int)POSITION_MAX;
			
			

			//
			{
				Char16 campaignUId[20] = { 0 };
				swprintf_s( campaignUId, 20, L"%d", info.campaignUId);
				info.strUId		= campaignUId;
			}
			
			
			CPlaceObject* targetRegion = (CPlaceObject*)CRegionManager::getInstance().getRegionObjectById(ROT_PLACE, info.targetRegionId);
			DYNAMIC_ASSERT(NULL != targetRegion);
			info.strTargetRegionName	= targetRegion->getPlaceData()->getMapListCsvInfo()->mapName;
			info.strCampaignName		= campaignInfo->getCampaignName();


			{
				Char16 curPlayerStr[20] = { 0 };
				swprintf_s( curPlayerStr, 20, L"%d/%d", info.curPlayerNum, info.maxPlayerNum);
				info.strCurPlayerStr		= curPlayerStr;
			}

			UICampaignListNew::getInstance().addCampaignInfo(&info);
		}
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::addCampaignInfo(UICampaignSingleInfo* info)
	{
		mCampaignList.push_back(*info);
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::clearCampaignList()
	{
		mCampaignList.clear();
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::UIReFresh()
	{
		if (true == UICampaignListNew::getInstance().isOpen())
		{
			UICampaignListNew::getInstance().UIReFreshCampaignList();
			UICampaignListNew::getInstance().UIReFreshTargetRegionList();
		}
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::UIReFreshCampaignList()
	{
		{
			IEdit* edit_campaignName = UICampaignListNew::getInstance().getLayout()->getEdit("edit_CampaignName");
			edit_campaignName->setCaption(L"");
		}
		

		loadCampaignList();
		
		IMixList* campaignListView = getLayout()->getMixList("view_campaignList");
		DYNAMIC_ASSERT(campaignListView);
		campaignListView->removeAllLine();


		char mainRectName[32]		= "";
		
		char campaignState[32]		= "";
		char UIdName[32]			= "";
		char targetName[32]			= "";
		char campaignName[32]		= "";
		char memberNumName[32]		= "";
		char enctryptionName[32]	= "";
		

		Int nCount = mCampaignList.size();
		
		Char16 addName[32] = L"";

		for (Int i=0; i<nCount; i++)
		{
			UICampaignSingleInfo* campaignInfo = &(mCampaignList.at(i));
			DYNAMIC_ASSERT( NULL != campaignInfo );
			
			swprintf_s(addName,32,L"campain%d", i+1 );
			campaignListView->addLine(i,Str16(addName));
			IMixListRow* pListRow = campaignListView->getMixListRow(i);
			campaignListView->setClickMixListRow(onClickCampaignInfo);
			campaignListView->setDoubleClickMixListRow(onDoubleClickCampaignInfo);

			pListRow->getWidget()->setUserData(*campaignInfo);
			//pListRow->getChildWidget(0)->getText()->setTextAlign(Center);
			pListRow->getChildWidget(0)->setCaption(campaignInfo->strState);

			//pListRow->getChildWidget(1)->getText()->setTextAlign(Center);
			pListRow->getChildWidget(1)->setCaption(campaignInfo->strUId);

			//pListRow->getChildWidget(2)->getText()->setTextAlign(Center);
			pListRow->getChildWidget(2)->setCaption(campaignInfo->strTargetRegionName);

			//pListRow->getChildWidget(3)->getText()->setTextAlign(Center);
			pListRow->getChildWidget(3)->setCaption(campaignInfo->strCampaignName);

			//pListRow->getChildWidget(4)->getText()->setTextAlign(Center);
			pListRow->getChildWidget(4)->setCaption(campaignInfo->strCurPlayerStr);

			//pListRow->getChildWidget(5)->getText()->setTextAlign(Center);
			pListRow->getChildWidget(5)->setCaption(campaignInfo->strEnctryptionName);	
		}

	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::UIReFreshTargetRegionList()
	{
		//加载攻击目标内存
		loadTargetRegionList();

		//显示目标
		IComboBox* comboTarget = getLayout()->getComboBox(COMBO_TARGET_LIST);
		comboTarget->removeAllItems();
		for (std::vector<UITargetRegionSingleInfo>::iterator iter = mTargetRegionList.begin() ; iter != mTargetRegionList.end(); ++iter)
		{
			UITargetRegionSingleInfo* temp = &(*iter);
			comboTarget->addItem(iter->regionName, *iter);
		}
		if (comboTarget->getItemCount() > 0)
		{
			comboTarget->setIndexSelected(0);
		}
	}

	//--------------------------------------------------------------------------------
	void UICampaignListNew::loadTargetRegionList()
	{
		if (isOpen() == false)
		{
			return;
		}

		mTargetRegionList.clear();
		//读取所有列表
		std::map<PlaceIdType, CPlaceObject*>* placeList = CRegionManager::getInstance().getPlaceObjList();

		for(std::map<PlaceIdType, CPlaceObject*>::iterator iter = placeList->begin(); iter != placeList->end(); ++iter)
		{
			//以后需要 读取副本信息 来确定 是否是 战场副本
			PlaceListCsvInfo* placeListCsvInfo = iter->second->getPlaceListCsvInfo();
			InstanceListCsvInfo* instanceInfo = InstanceListCsv::getInstance().getInfoById(placeListCsvInfo->instanceId);
			if (NULL != instanceInfo && InstanceType_Atk == instanceInfo->instanceType)
			{
				wstring strId;
				MGStrOp::toString(iter->first, strId);
				UITargetRegionSingleInfo tempInfo;
				tempInfo.regionId = iter->first;
				tempInfo.regionType = ROT_PLACE;
				tempInfo.regionName = placeListCsvInfo->placeName/* + strId*/;
				mTargetRegionList.push_back(tempInfo);
			}
		}

#if 0	//2012.12月份版本 暂不此限制（可以无限开副本）
		//删除正在战斗中的列表
		std::map<ClanIdType, SCampaign*>* battleCampaignList = CCampaignManager::getInstance().getOnBattleCampaignList();
		for(std::map<ClanIdType, SCampaign*>::iterator iter = battleCampaignList->begin(); iter != battleCampaignList->end(); ++iter)
		{
			SCampaign* campaign = iter->second;
			const RegionIdType targetRegion = campaign->getCampaignTargetRegionId();
			for (std::vector<UITargetRegionSingleInfo>::iterator iterIner = mTargetRegionList.begin(); iterIner != mTargetRegionList.end(); ++iterIner)
			{
				if (targetRegion == iterIner->regionId)
				{
					mTargetRegionList.erase(iterIner);
					break;
				}
			}
		}
#endif
	}
	//--------------------------------------------------------------------------------
	void UICampaignListNew::setButtonState( IWidget* pWidget )
	{
		Str8 tempName = pWidget->getName();

		IViewScroll* pRegionCampaignList = getLayout()->getViewScroll("view_campaignList");
		Int buttonNum = pRegionCampaignList->getWidget()->getChildCount();

		for (Int i=0; i<buttonNum; i++)
		{
			IWidget* pChildWidget = pRegionCampaignList->getWidget()->getChildAt(i);
			pChildWidget->getButton()->setStateCheck(false);
		}

		pWidget = pRegionCampaignList->getWidget()->findWidget(tempName);
		pWidget->getButton()->setStateCheck(true);
	}
	//--------------------------------------------------------------------------------
}
