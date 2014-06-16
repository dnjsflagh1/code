//*************************************************************************************

#include "stdafx.h"
#include "UITiroChangeInstance.h"
#include "CPlayer.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "IButton.h"
#include "PlayerNetPacketProcesser.h"
#include "UIMessageBox.h"

#include "CRegionManager.h"
#include "InstanceListCsv.h"

//*************************************************************************************

#define 	TIRO_SPACE_X		20
#define 	TIRO_SPACE_Y		5

#define 	TIRO_MAIN_RECT_W			180
#define 	TIRO_MAIN_RECT_H			17

#define 	TIRO_CHILD_RECT_W			50

#define		TIRO_INSTANCE_NAME_X		20
#define		TIRO_INSTANCE_CURENT_X		80
#define		TIRO_INSTANCE_STATE_X		150
//*************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------------
	UITiroChangeInstance::UITiroChangeInstance()
		:mCurInstanceInfo(NULL)
		,mTiroInstanceCsvInfo(NULL)
		,mTiroRegionId(0)
	{
		//testCreateTiro();
	}

	//--------------------------------------------------------------------------------
	UITiroChangeInstance::~UITiroChangeInstance()
	{

	}

	//--------------------------------------------------------------------------------
	Bool UITiroChangeInstance::openGui()
	{
		//return false;
		if (  false == UIObject::isOpen() )
		{
			UIObject::openGui();
			//UIReFresh();
			//RegionIdType tiroRegionId = getTiroRegionId();
			sendTiroList();
			return true;
		}
		else
		{
			UIReFresh();
		}

		return false;
	}

	//--------------------------------------------------------------------------------
	InstanceListCsvInfo* UITiroChangeInstance::getTiroInstanceCsvInfo()
	{
		DYNAMIC_ASSERT(0);
		return NULL;

		//if (NULL == mTiroInstanceCsvInfo)
		//{
		//	mTiroInstanceCsvInfo = InstanceListCsv::getInstance().getTiroInstanceInfo();
		//}
		//DYNAMIC_ASSERT(NULL != mTiroInstanceCsvInfo);
		//return mTiroInstanceCsvInfo;
	}

	//--------------------------------------------------------------------------------
	std::wstring& UITiroChangeInstance::getTiroRegionName(RegionIdType tiroId)
	{
		CRegionObject* tiroObj = CRegionManager::getInstance().getRegionObjectById(ROT_TIRO, tiroId);
		mTiroRegionString = tiroObj->getRegionNameStr16();
		return mTiroRegionString;
	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::testCreateTiro()
	{
#if 0
		for (Int i=1; i<= 100; ++i)
		{
			UIInstanceInfo info1;
			info1.instanceUId = 273000+i;
			wchar_t mainName[32] = L"";
			swprintf(mainName,L"nihao%d", i);

			wchar_t mainState[32] = L"";
			swprintf( mainState, L"繁忙%d", i);

			info1.instanceName.append(mainName);
			info1.instanceState.append(mainState);
			addInstanceInfo(&info1);
		}
#endif
	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::setEvent()
	{

		//Title
		{
			IButton* btnCancel = getLayout()->getButton("BTN_CANCEL");
			DYNAMIC_ASSERT(btnCancel);
			btnCancel->getWidget()->setMouseButtonClickEvent(onClickButtonCancel);
		}

		//确定
		{
			IButton* btnOK = getLayout()->getButton("BTN_CONFIRM");
			DYNAMIC_ASSERT(btnOK);
			btnOK->getWidget()->setMouseButtonClickEvent(onClickButtonConfirm);
		}

		//取消
		{
			IButton* btnCancel = getLayout()->getButton("BTN_CANCEL");
			DYNAMIC_ASSERT(btnCancel);
			btnCancel->getWidget()->setMouseButtonClickEvent(onClickButtonCancel);
		}
	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::addInstanceInfo(NetIdType mapServerNetId, UIInstanceInfo* info)
	{
		std::wstring tiroName = getTiroRegionName(info->regionId);
		wchar_t mainName[32] = L"";
		swprintf(mainName,L"%d_%d", info->instanceUId, mapServerNetId);

		wchar_t mainState[32] = L"";
		swprintf( mainState, L"%d/%d", info->curPlayerNum, info->maxPlayerNum);

		info->instanceName.append(mainName);
		info->instanceState.append(mainState);

		std::map<NetIdType, std::vector<UIInstanceInfo>* >::iterator iter = mInstanceList.find(mapServerNetId);
		if (iter != mInstanceList.end())
		{
			iter->second->push_back(*info);
			return;
		}
		else
		{
			std::vector<UIInstanceInfo>* uiInstanceList = MG_NEW std::vector<UIInstanceInfo>;
			uiInstanceList->push_back(*info);
			mInstanceList[mapServerNetId] = uiInstanceList;
		}

	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::clearInstanceInfo(NetIdType mapServerNetId)
	{
		std::map<NetIdType, std::vector<UIInstanceInfo>* >::iterator iter = mInstanceList.find(mapServerNetId);
		if (iter != mInstanceList.end())
		{
			iter->second->clear();
			MG_SAFE_DELETE(iter->second);
			mInstanceList.erase(iter);
			return;
		}

	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::onClickTiroInstance(void* widget, Int index)
	{
#if 0
		IButton* pMenu = (IButton*)widget;
		assert ( pMenu );

		UITiroChangeInstance::getInstance().setCurTiroInstanceButton(pMenu);
#endif

		IMixList* listMainZone = (IMixList*)widget;

		IMixListRow* row = listMainZone->getMixListRowByIndex(index);

		IAny* pAny = row->getWidget()->getUserData();
		UIInstanceInfo* info = pAny->castType<UIInstanceInfo>(pAny);
		DYNAMIC_ASSERT(NULL != info);
		UITiroChangeInstance::getInstance().setCurTiroInstanceInfo(info);

		//UICampaignBarrack::getInstance().UIFreshCharIcon(info);
	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::onClickButtonConfirm( void* widget )
	{
		UIInstanceInfo* instanceInfo = UITiroChangeInstance::getInstance().getCurTiroInstanceInfo();
		if (NULL == instanceInfo)
		{
			return;
		}
		UITiroChangeInstance::getInstance().sendJumpTiroInstance(instanceInfo);
	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::onClickButtonCancel(void* widget)
	{
		UITiroChangeInstance::getInstance().closeGui();
	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::UIReFresh()
	{
		IMixList* listMainZone = getLayout()->getMixList("view_showInstanceInfo");
		DYNAMIC_ASSERT(listMainZone);

		listMainZone->setClickMixListRow(onClickTiroInstance);

		listMainZone->removeAllLine();
		char creatorName[32]	= "";

		Int index = 0;
		std::map<NetIdType, std::vector<UIInstanceInfo>* >::iterator iter = mInstanceList.begin();

		for (; iter != mInstanceList.end(); ++iter)
		{

			listMainZone->addLine(0,L"");
			IMixListRow* row = listMainZone->getMixListRowByIndex(index);

			//一行数据
			std::vector<UIInstanceInfo>* instanceList = &(*(iter->second));

			for (std::vector<UIInstanceInfo>::iterator instanceIter = instanceList->begin(); instanceIter != instanceList->end(); ++instanceIter)
			{
				UIInstanceInfo* instanceInfo = &(*instanceIter);

				Color color = ColorSet::white();

				row->getChildWidget(0)->setCaption(instanceInfo->instanceName);
				row->getText(0)->setTextColour(color);
				row->getText(0)->setTextAlign(Center);

				if (true == instanceInfo->instanceCurrent)
				{
					//IImage* imageCurrent = getLayout()->getImage(childInstanceCurrent);
					//DYNAMIC_ASSERT(imageCurrent);
					row->getImage(1)->setTexture("Sub_Icon_State", "Nows", "1");
				}
				//row->getImage(1)->setItemName(instanceInfo->instanceState);

				row->getChildWidget(2)->setCaption(instanceInfo->instanceState);
				row->getText(2)->setTextColour(color);
				row->getText(2)->setTextAlign(Center);

				row->getWidget()->setUserData(*instanceInfo);
			}



			index++;
		}

#if 0
		IViewScroll* pRegion = getLayout()->getViewScroll("view_showInstanceInfo");
		{
			assert(pRegion);
			pRegion->clear(); 
		}

		char mainName[32]			= "";
		char childInstanceName[32]	= "";
		char childInstanceCurrent[32] = "";
		char childInstanceState[32] = "";

		Int nCount = mInstanceList.size();
		
		for (Int i=0; i<nCount; i++)
		{
			UIInstanceInfo* instanceInfo = &(mInstanceList.at(i));
			assert( instanceInfo );

			sprintf( mainName, "mainName%d", i+1 );
			Int y = TIRO_SPACE_Y + i * TIRO_MAIN_RECT_H;
			CoordI tempMainRect(0, y, TIRO_MAIN_RECT_W, TIRO_MAIN_RECT_H);
			IWidget*  mainButton = pRegion->getWidget()->createWidget(WIDGET_BUTTON, "MGButton1002", tempMainRect, Default, mainName);
			
			//拷贝内存到控件， 控件释放的时候内存也自动释放
			mainButton->setUserData(*instanceInfo);
			mainButton->setMouseButtonClickEvent(onClickTiroInstance);


			//创建 两个 子text
			sprintf( childInstanceName, "childInstanceName%d", i+1 );
			sprintf( childInstanceCurrent, "childInstanceCurrent%d", i+1 );
			sprintf( childInstanceState, "childInstanceState%d", i+1 );
			CoordI tempInstanceNameRect(TIRO_INSTANCE_NAME_X, 0, TIRO_CHILD_RECT_W, TIRO_MAIN_RECT_H);
			CoordI tempInstanceCurrentRect(TIRO_INSTANCE_CURENT_X, 0, 33, 13);
			CoordI tempInstanceStateRect(TIRO_INSTANCE_STATE_X, 0, TIRO_CHILD_RECT_W, TIRO_MAIN_RECT_H);
			IWidget*  InstanceNameText		= mainButton->createWidget(WIDGET_TEXT, "StaticText", tempInstanceNameRect, Default, childInstanceName);
			IWidget*  InstanceCurrentText	= mainButton->createWidget(WIDGET_IMAGE, "StaticImage", tempInstanceCurrentRect, Default, childInstanceCurrent);
			IWidget*  InstanceStateText		= mainButton->createWidget(WIDGET_TEXT, "StaticText", tempInstanceStateRect, Default, childInstanceState);
			InstanceNameText->setCaption(instanceInfo->instanceName);
			InstanceNameText->setNeedKeyFocus(false);
			InstanceNameText->setNeedMouseFocus(false);

			if (true == instanceInfo->instanceCurrent)
			{
				IImage* imageCurrent = getLayout()->getImage(childInstanceCurrent);
				DYNAMIC_ASSERT(imageCurrent);
				imageCurrent->setTexture("Sub_Icon_State", "Nows", "1");
			}

			InstanceStateText->setCaption(instanceInfo->instanceState);
			InstanceStateText->setNeedKeyFocus(false);
			InstanceStateText->setNeedMouseFocus(false);
			
			getLayout()->getButton(mainName)->setTextColour(Color(1, 1, 1, 1));
		}

		Vec2 size = pRegion->getWidget()->getSize();
		size.y = (TIRO_SPACE_Y+TIRO_MAIN_RECT_H) * nCount;
		pRegion->setCanvasSize(size);
#endif
	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::setCurTiroInstanceInfo(UIInstanceInfo* instanceInfo)
	{
		mCurInstanceInfo = instanceInfo;
	}

	//--------------------------------------------------------------------------------
	UIInstanceInfo* UITiroChangeInstance::getCurTiroInstanceInfo() const
	{
		return mCurInstanceInfo;
	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::sendJumpTiroInstance(const UIInstanceInfo* instanceInfo)
	{
		const InstanceUIdType instanceUId = CPlayer::getInstance().getInstanceUid();
		if (instanceUId == instanceInfo->instanceUId)
		{
			UIMessageBox::getInstance().showHint(L"不能跳到当前副本");
			return;
		}

		U64 generalId = CPlayer::getInstance().getMainGenreal()->getID();
		PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpTiroRegion(instanceInfo->mapServerNetId, generalId, ROT_TIRO, instanceInfo->regionId, instanceInfo->instanceUId);
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(CPlayer::getInstance().getAccountID(), generalId);
	}

	//--------------------------------------------------------------------------------
	void UITiroChangeInstance::sendTiroList()
	{
		PlayerNetPacketProcesser::getInstance().sendTiroList();
	}

}