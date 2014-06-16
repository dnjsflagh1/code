//*************************************************************************************

#include "stdafx.h"
#include "UICampaignBarrack.h"
#include "CPlayer.h"
#include "CampaignNetPacketProcesser.h"
#include "ArtIconResCsv.h"

//*************************************************************************************

#define 	MAIN_RECT_W			144
#define 	MAIN_RECT_H			33

#define		SPACE_Y				4			//间隔


//*************************************************************************************
namespace MG
{
	//------------------------------------------------------------------------
	UICampaignBarrack::UICampaignBarrack()
		:mCampId(0)
		,mCampOwnerId(0)
		,mTargetAccountId(0)
	{
		//testCreate();
	}

	//------------------------------------------------------------------------
	UICampaignBarrack::~UICampaignBarrack()
	{
	}

	//------------------------------------------------------------------------
	void UICampaignBarrack::testCreate()
	{
		for (Int i=1; i<= 10; ++i)
		{
			NetTroopControllerInfo info;
			info.accountId = i+1;
			WStrnCpyS(info.playerCharacterName, MAX_CHARACTER_NAME_LEN,  L"CHaracter %d",i);
			//sprintf( info.playerCharacterName, L"fdgre%d", i+1 );
			//loadData(11,22,1, &info);
		}

		int ii = 0;
	}

	//------------------------------------------------------------------------
	void UICampaignBarrack::setEvent()
	{
		//【确认按钮】
		{
			IButton* btnConfirm = getLayout()->getButton("Btn_Confirm");
			btnConfirm->getWidget()->setMouseButtonClickEvent(onEventConfirm);
		}
	}

	//------------------------------------------------------------------------
	void UICampaignBarrack::onEventConfirm(void* widget)
	{

		CPlayer* myPlayer = &(CPlayer::getInstance());

		const AccountIdType myAccountId		= myPlayer->getAccountID();
		const CampaignIdType myCampaignId	= myPlayer->getMyCampaignId();
		const CampIdType myCampId			= UICampaignBarrack::getInstance().getCampId();
		const AccountIdType targetAccountId = UICampaignBarrack::getInstance().getTargetAccountId();

		DYNAMIC_ASSERT(myAccountId > 0 && myCampaignId > 0 && myCampId > 0 && targetAccountId > 0);

		if (targetAccountId < 0)
		{
			UICampaignBarrack::getInstance().closeGui();
			return;
		}

		const AccountIdType campOwnerAccountId = UICampaignBarrack::getInstance().getCampOwnerId();
		if (campOwnerAccountId == myAccountId)
		{
			//我是这个军营的所有者
			CampaignNetPacketProcesser::getInstance().sendCampaignChangeCampControl(myCampaignId, myAccountId, myCampId, targetAccountId);
		}

		UICampaignBarrack::getInstance().closeGui();
	}

	//------------------------------------------------------------------------
	Bool UICampaignBarrack::openGui()
	{
		if (  false == UIObject::isOpen() )
		{
			UIObject::openGui();
			UIFresh();
		}
		else
		{
			UIObject::closeGui();
		}

		return false;
	}

	//------------------------------------------------------------------------
	void UICampaignBarrack::UIFresh()
	{
		IMixList* listMainZone = getLayout()->getMixList("troopControllerList");
		DYNAMIC_ASSERT(listMainZone);

		listMainZone->setClickMixListRow(onClickChangeTroopInfo);

		listMainZone->removeAllLine();
		char creatorName[32]	= "";

		for (Int i=0; i<mControllerList.size(); ++i)
		{
			
			listMainZone->addLine(i,L"");
			IMixListRow* row = listMainZone->getMixListRow(i);
			
			//一行数据
			CampControllerInfo* campController = &(mControllerList.at(i));

			Color color = ColorSet::white();
			if (true == campController->isController)
			{
				color = ColorSet::yellow();
			}
			row->getChildWidget(0)->setCaption(campController->name);
			row->getText(0)->setTextColour(color);
			row->getText(0)->setTextAlign(Center);
			row->getWidget()->setUserData(*campController);
		}


		//军营信息
		{
			//耐久度
			{
				IText* text_level = getLayout()->getText("CampHp");
				text_level->getWidget()->setCaption(mCampInfo.campHp);
			}

			//军队数
			{
				IText* text_level = getLayout()->getText("Camp_TroopNum");
				text_level->getWidget()->setCaption(mCampInfo.campTroopNum);
			}

			//所有军队数
			{
				IText* text_level = getLayout()->getText("Camp_AllTroopNum");
				text_level->getWidget()->setCaption(mCampInfo.campAllTroopNum);
			}
			
		}
		
#if 0
		IViewScroll* pTroopControllerList = getLayout()->get("troopControllerList");
		{
			assert(pTroopControllerList);
			pTroopControllerList->clear();
		}

		char mainName[32]		= "";
		char creatorName[32]	= "";


		Int nCount = mControllerList.size();

		for (Int i=0; i < nCount; i++)
		{
			CampControllerInfo* campController = &(mControllerList.at(i));
			DYNAMIC_ASSERT( NULL != campController );

			sprintf( mainName, "mainName%d", i+1 );
			Int y = SPACE_Y + i * MAIN_RECT_H;
			CoordI tempMainRect(0, y, MAIN_RECT_W, MAIN_RECT_H);
			IWidget*  mainButton = pTroopControllerList->getWidget()->createWidget(WIDGET_BUTTON, "MGButton1002", tempMainRect, Default, mainName);

			//拷贝内存到控件， 控件释放的时候内存也自动释放
			mainButton->setUserData(*campController);
			mainButton->setMouseButtonClickEvent(onClickChangeTroopInfo);


			//创建 两个 子text
			sprintf( creatorName, "creatorName%d", i+1 );
			CoordI creatorNameRect(0, 10, MAIN_RECT_W, 13);
			IWidget*  creatorNameText	= mainButton->createWidget(WIDGET_TEXT, "StaticText", creatorNameRect, Default, creatorName);

			Color color = ColorSet::white();
			if (true == campController->isController)
			{
				color = ColorSet::red();
			}

			getLayout()->getText(creatorName)->setTextColour(color);
			creatorNameText->setCaption(campController->name);
			creatorNameText->setNeedKeyFocus(false);
			creatorNameText->setNeedMouseFocus(false);

			
			
			
		}

		Vec2 size;
		size.x = pTroopControllerList->getWidget()->getSize().x;
		size.y = (MAIN_RECT_H + SPACE_Y) * nCount;
		pTroopControllerList->setCanvasSize(size);
#endif
	}

	//--------------------------------------------------------------------------------
	void UICampaignBarrack::UIFreshCharIcon(const CampControllerInfo* info)
	{
		//头像
		{
			const ArtIconResCsvInfo* tempResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(info->charArtIcon);
			DYNAMIC_ASSERT(NULL != tempResInfo);
			IImage *headimg = getLayout()->getImage("Image_CharIcon");
			headimg->setItemGroup(tempResInfo->GroupName);
			headimg->setItemResource(tempResInfo->ResName);
			headimg->setItemName(tempResInfo->ItemName);
		}

		//武将名字 
		/*{
			IText* text_level = getLayout()->getText("Text_CharName");
			text_level->getWidget()->setCaption(info->name);
		}*/
		

	}
	

	//--------------------------------------------------------------------------------
	void UICampaignBarrack::onClickChangeTroopInfo(void* widget, Int index)
	{
		IMixList* listMainZone = (IMixList*)widget;

		IMixListRow* row = listMainZone->getMixListRowByIndex(index);

		IAny* pAny = row->getWidget()->getUserData();
		CampControllerInfo* info = pAny->castType<CampControllerInfo>(pAny);
		DYNAMIC_ASSERT(NULL != info);
		UICampaignBarrack::getInstance().setTargetAccountId(info->accountId);

		UICampaignBarrack::getInstance().UIFreshCharIcon(info);
	}

	//------------------------------------------------------------------------
	void UICampaignBarrack::setCampId(const CampIdType campId)
	{
		mCampId = campId;
	}

	//------------------------------------------------------------------------
	CampIdType UICampaignBarrack::getCampId() const
	{
		return mCampId;
	}

	//------------------------------------------------------------------------
	void UICampaignBarrack::setCampOwnerId(const AccountIdType campOwnerId)
	{
		mCampOwnerId = campOwnerId;
	}

	//------------------------------------------------------------------------
	AccountIdType UICampaignBarrack::getCampOwnerId() const
	{
		return mCampOwnerId;
	}

	//------------------------------------------------------------------------
	void UICampaignBarrack::loadData(const CampIdType campId, const AccountIdType troopCurControllerAccountId, const Int addNum, const NetTroopControllerInfo* addInfo, const NetCampInfo* campInfo)
	{
		//mCampId = campId;

		CampControllerInfo tempContrrlerInfo;
		for (Int i=0; i<addNum; ++i)
		{
			tempContrrlerInfo.clear();
			
			Char16 curAccountStr[20] = { 0 };
			swprintf_s( curAccountStr, 20, L"%d", addInfo[i].accountId);

			tempContrrlerInfo.accountId		= addInfo[i].accountId;
			tempContrrlerInfo.accountIdStr	= curAccountStr;

			if (troopCurControllerAccountId == addInfo[i].accountId)
			{
				tempContrrlerInfo.isController = true;
			}

			tempContrrlerInfo.playerCharacterId				= addInfo[i].playerCharacterId;
			tempContrrlerInfo.playerCharacterTemplateId		= addInfo[i].templateId;
			tempContrrlerInfo.charArtIcon					= addInfo[i].charArtIcon;
			
			tempContrrlerInfo.name = addInfo[i].playerCharacterName;
			mControllerList.push_back(tempContrrlerInfo);
		}

		//军营信息
		{
			Char16 temp[20] = { 0 };

			swprintf_s( temp, 20, L"%d", campInfo->campHp);
			mCampInfo.campHp = temp;

			swprintf_s( temp, 20, L"%d", campInfo->troopNum);
			mCampInfo.campTroopNum = temp;

			swprintf_s( temp, 20, L"%d", campInfo->troopNum);
			mCampInfo.campAllTroopNum = temp;
		}
	

	}

	//------------------------------------------------------------------------
	void UICampaignBarrack::clear()
	{
		mControllerList.clear();
	}

	//------------------------------------------------------------------------
	void UICampaignBarrack::setTargetAccountId(AccountIdType accountId)
	{
		mTargetAccountId = accountId;
	}

	//------------------------------------------------------------------------
	AccountIdType UICampaignBarrack::getTargetAccountId() const
	{
		return mTargetAccountId;
	}
	//------------------------------------------------------------------------

}