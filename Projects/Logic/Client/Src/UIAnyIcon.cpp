//*************************************************************************************************************
#include "stdafx.h"
#include "UIAnyIcon.h"
#include "PlayerItem.h"
#include "CItemManager.h"
#include "ItemPacketProcesser.h"
#include "UIClanInfo.h"
#include "ClientMain.h"
#include "PlayerItem.h"
#include "UIItemTips.h"
#include "UISkillTips.h"
//*************************************************************************************************************
namespace MG
{
//界面的大小限制
#define	 ANY_UI_SCROLL_WIDTH 20
#define  ANY_UI_WIDTH_MAX	159
#define  ANY_UI_HEIGHT_MAX	208
#define  ANY_UI_COL_MAX		4
#define  ANY_UI_ROW_MAX		5
//界面的上下左右的偏移
#define  ANY_UI_LEFT		4
#define  ANY_UI_TOP			4
#define  ANY_UI_BOTTOM		4
#define  ANY_UI_RIGHT		4
//ICON的大小（居中）
#define  ANY_ICON_RIGHT		39
#define  ANY_ICON_MIDDLE	37
#define  ANY_ICON_LEFT		38
#define  ANY_ICON_HEIGHT	40
//TEXT的大小，位置
#define  ANY_TEXT_LEFT		18
#define  ANY_TEXT_TOP		18
#define	 ANY_TEXT_WIDTH		18
#define  ANY_TEXT_BOTTOM	18
	//------------------------------------------------------------------------------------------------
	struct IconResName
	{
		Str8 resname;
		Str8 groupname;
		Str8 itemname;
	};
	//------------------------------------------------------------------------------------------------
	static IconResName gobalIconResName[3] =
	{
		{"Sub_Area_Icon", "Left", "1"},
		{"Sub_Area_Icon", "Middle", "1"},
		{"Sub_Area_Icon", "Right", "1"}
	};
	//------------------------------------------------------------------------------------------------

    UIAnyIcon::UIAnyIcon()
		:mIconNum(0)
    {

    }
    //--------------------------------------------------------------------------------------------
    UIAnyIcon::~UIAnyIcon()
    {

    }
    //--------------------------------------------------------------------------------------------
    void UIAnyIcon::addItemIcon( IconInfo* pIconInfo, U32 index )
    {
		IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
		Int nCount = pWidget->getChildCount();

		IImage* pImage = NULL;
		IWidget* pChildWidget = NULL;
		Char8 tempName[32] = "";
		Char16 tempWName[32] = L"";
		IWidget* pGrandsonWidget = NULL;
		//如果有现成的控件
		if ( nCount > index )
		{
			pChildWidget = pWidget->getChildAt(index);
			pChildWidget->setVisible(true);
			pChildWidget->setUserData(*pIconInfo);
			//设置图片
			sprintf_s(tempName, 32, "anyiconImage%d", index);
			pGrandsonWidget = pChildWidget->findWidget(tempName);
			pGrandsonWidget->getImage()->setTexture(pIconInfo->resouceName, pIconInfo->groupName, pIconInfo->itemName);
			//设置信息
			sprintf_s(tempName, 32, "anyiconText%d", index);
			pGrandsonWidget = pChildWidget->findWidget(tempName);
			PlayerItem* pItem = CItemManager::getInstance().findItem(pIconInfo->dbID, ITEM_SITE_TYPE_CLAN);
			DYNAMIC_ASSERT(pItem);
			if ( pItem->getItemNum() > 1 )
			{
				swprintf_s(tempWName, 32, L"%d", pItem->getItemNum());
				pGrandsonWidget->setCaption(tempWName);
			}
			else
			{
				pGrandsonWidget->setCaption(L"");
			}
		} 
		else
		{
			CoordI tempCoordI;
			sprintf_s(tempName, 32, "anyicon%d", index);
			pChildWidget = pWidget->createWidget(WIDGET_IMAGE, "StaticImage", tempCoordI, MGAlign::Default, tempName);
			pChildWidget->setUserData(*pIconInfo);
			pChildWidget->setMouseButtonClickEvent(onClickIcon);
			pChildWidget->setNeedToolTip(true);
			pChildWidget->setToolTipsEvent(onEventToolTips);
			//获得控件的位置,控件的底图
			U32 mod = index%ANY_UI_COL_MAX;
			U32 row = (index-1)/ANY_UI_COL_MAX +1;
			if ( mod == 1 )
			{	
				tempCoordI.left = ANY_UI_LEFT;
				tempCoordI.width = ANY_ICON_LEFT;
				//设置背景图片和信息
				pChildWidget->getImage()->setTexture(
					gobalIconResName[0].resname, 
					gobalIconResName[0].groupname,
					gobalIconResName[0].itemname
					);
			}
			else if ( mod == 0 )
			{	
				tempCoordI.left = ANY_ICON_LEFT + ANY_ICON_MIDDLE + ANY_ICON_MIDDLE;
				tempCoordI.width = ANY_ICON_RIGHT;
				//设置背景图片和信息
				pChildWidget->getImage()->setTexture(
					gobalIconResName[2].resname,
					gobalIconResName[2].groupname,
					gobalIconResName[2].itemname
					);
			}
			else
			{	
				tempCoordI.left = ANY_ICON_LEFT + ANY_ICON_MIDDLE*(mod-2);
				tempCoordI.width = ANY_ICON_MIDDLE;
				//设置背景图片和信息
				pChildWidget->getImage()->setTexture(
					gobalIconResName[1].resname,
					gobalIconResName[1].groupname,
					gobalIconResName[1].itemname
					);
			}
			tempCoordI.top = (row-1)*ANY_ICON_HEIGHT + ANY_UI_TOP;
			tempCoordI.height = ANY_ICON_HEIGHT;
			pChildWidget->setCoord(tempCoordI);

			//设置Icon
			sprintf_s(tempName, 32, "anyiconImage%d", index);
			pGrandsonWidget = pChildWidget->createWidget(WIDGET_IMAGE, "StaticImage", CoordI(2, 4, 32, 32), MGAlign::Center, tempName);
			pGrandsonWidget->setNeedKeyFocus(false);
			pGrandsonWidget->setNeedMouseFocus(false);
			pGrandsonWidget->getImage()->setTexture(pIconInfo->resouceName, pIconInfo->groupName, pIconInfo->itemName);
			//设置Text
			sprintf_s(tempName, 32, "anyiconText%d", index);
			pGrandsonWidget = pChildWidget->createWidget(WIDGET_TEXT, "StaticText", CoordI(20, 2, 20, 20), MGAlign::Default, tempName);
			pGrandsonWidget->setNeedKeyFocus(false);
			pGrandsonWidget->setNeedMouseFocus(false);
			PlayerItem* pItem = CItemManager::getInstance().findItem(pIconInfo->dbID, ITEM_SITE_TYPE_CLAN);
			DYNAMIC_ASSERT(pItem);
			if ( pItem->getItemNum() > 1 )
			{
				swprintf_s(tempWName, 32, L"%d", pItem->getItemNum());
				pGrandsonWidget->setCaption(tempWName);
			}
		}
    }
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::loadItem( ITEM_SITE_TYPE sitetype, UInt index, CoordI screenCoord, Bool isAddButton )
	{
		//关闭所有子控件
		closeAllChild();
		
		//设置控件信息
		mOldItemSiteType = sitetype;
		mOldItemIndex = index;
		mWidgetCoord = screenCoord;
		mIsAddButton = isAddButton;

		//加载图片（道具）
		loadItem();

		//调整界面的位置。
		adjustUIPos();

		UIObject::openGui();

		//激活界面
		IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
		DYNAMIC_ASSERT(pWidget);
		pWidget->setKeyFocus(true);
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::loadItem()
	{
		//获取道具list
		std::vector<IconInfo> vectorIconInfo;
		getItemList(vectorIconInfo);

		//获得显示物品的数量
		mIconNum = vectorIconInfo.size();
		if ( mIsAddButton )
			++mIconNum;

		//将道具加到界面中
		std::vector<IconInfo>::iterator front = vectorIconInfo.begin();
		std::vector<IconInfo>::iterator back = vectorIconInfo.end();
		U32 index = 0;
		while (front != back)
		{
			addItemIcon( &(*front), ++index );
			++front;
		}

		//加按钮
		addUninstallButton();
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::onClickIcon( void* pWidget )
	{
		DYNAMIC_ASSERT(pWidget);
		IWidget* pTempWidget = (IWidget*)pWidget;

		IconInfo*  pIconInfo = pTempWidget->getUserData()->castType<IconInfo>();
		DYNAMIC_ASSERT(pIconInfo);

		UIAnyIcon::getInstance().sendChangeItem(ITEM_SITE_TYPE_CLAN, pIconInfo->index, false);
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::onClickUninstall( void* pWidget )
	{
		DYNAMIC_ASSERT(pWidget);
		
		UIAnyIcon::getInstance().onHandleUninstall();
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::sendChangeItem(ITEM_SITE_TYPE sitetype, UInt index, Bool isUninstall)
	{
		if ( isUninstall )
			ItemPacketProcesser::getInstance().sendChangePos(mOldItemIndex, index, mOldItemSiteType, sitetype, UIClanInfo::getInstance().getCurGenrealId());
		else
			ItemPacketProcesser::getInstance().sendChangePos(index, mOldItemIndex, sitetype, mOldItemSiteType, UIClanInfo::getInstance().getCurGenrealId());
		
		closeGui();
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::setEvent()
	{
		IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
		pWidget->setKeyLostFocusEvent(notifyKeyLostFocusEvent);

		pWidget = getLayout()->getWidget("button");
		pWidget->setMouseButtonClickEvent(onClickUninstall);
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::notifyKeyLostFocusEvent( void* widget, void* newWidget )
	{
		UIAnyIcon::getInstance().closeGui();
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::onHandleUninstall()
	{
		if ( CItemManager::getInstance().checkItemFull(ITEM_SITE_TYPE_CLAN) )
		{
			//提示不能脱装；
			closeGui();
		}
		else
		{
			U32 recvIndex = CItemManager::getInstance().getClanItems()->getFreeIndex();
			sendChangeItem(ITEM_SITE_TYPE_CLAN, recvIndex, true);
		}
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::adjustUIPos()
	{
		CoordI tempCoord;
		IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);

		Int mod = mIconNum%ANY_UI_COL_MAX;
		Int row = ((Int)mIconNum-1)/((Int)ANY_UI_COL_MAX) + 1;
		//设置UI的大小
		if ( row > 1 )
		{	
			if ( row > ANY_UI_ROW_MAX )
			{
				tempCoord.width = ANY_UI_WIDTH_MAX + ANY_UI_SCROLL_WIDTH;//常数
				tempCoord.height = ANY_UI_HEIGHT_MAX + ANY_UI_SCROLL_WIDTH;
				//设置滑动条;
				pWidget->getViewScroll()->setCanvasSize(ANY_UI_WIDTH_MAX, tempCoord.height);

				pWidget->getViewScroll()->setVisibleVScroll(true);
			}
			else
			{
				tempCoord.width = ANY_UI_WIDTH_MAX;
				tempCoord.height = ANY_UI_TOP + ANY_UI_BOTTOM + row*ANY_ICON_HEIGHT + ANY_UI_SCROLL_WIDTH;
				pWidget->getViewScroll()->setCanvasSize(ANY_UI_WIDTH_MAX, tempCoord.height);

				pWidget->getViewScroll()->setVisibleVScroll(false);
			}
			
		}
		else if ( row > 0  &&  mIconNum != 0 )
		{
			tempCoord.height = ANY_UI_TOP + ANY_UI_BOTTOM + ANY_ICON_HEIGHT + ANY_UI_SCROLL_WIDTH;
			if ( mod == 1 )
				tempCoord.width = ANY_UI_LEFT + ANY_UI_RIGHT + ANY_ICON_LEFT;
			else if ( mod == 0 )
				tempCoord.width = ANY_UI_WIDTH_MAX;
			else
				tempCoord.width = ANY_UI_LEFT + ANY_UI_RIGHT + ANY_ICON_LEFT + (mod-1)*ANY_ICON_MIDDLE;
			pWidget->getViewScroll()->setCanvasSize(tempCoord.width, tempCoord.height);

			pWidget->getViewScroll()->setVisibleVScroll(false);
			
		}
		else if ( mIconNum == 0 )
		{
			pWidget->setCoord(CoordI(0, 0, 0, 0));
			return;
		}


		//设置UI的位置
		U32 curScreenWidth =  ClientMain::getInstance().getEngine()->display()->getWidth();
		U32 curScreenHeight =  ClientMain::getInstance().getEngine()->display()->getHeight();

		//默认位置为右下角
		if ( mWidgetCoord.left + tempCoord.width < curScreenWidth )
			tempCoord.left = mWidgetCoord.left;
		else
			tempCoord.left = mWidgetCoord.left + mWidgetCoord.width - tempCoord.width;

		if ( mWidgetCoord.top + mWidgetCoord.height + tempCoord.height < curScreenHeight )
			tempCoord.top = mWidgetCoord.top + mWidgetCoord.height;
		else
			tempCoord.top = mWidgetCoord.top - tempCoord.height;

		//设置位置
		pWidget->setCoord(tempCoord);

	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::getItemList( std::vector<IconInfo>& iconlist )
	{
		PlayerItem* pItem = NULL;
		IconInfo tempIconInfo;

		ClanItems* pClanItems = CItemManager::getInstance().getClanItems();
		const std::map<IdType, PlayerItem*>* pItemMap = pClanItems->getPlayerItemMap();
		std::map<IdType, PlayerItem*>::const_iterator front = pItemMap->begin();
		std::map<IdType, PlayerItem*>::const_iterator back = pItemMap->end();
		
		if ( mOldItemSiteType == ITEM_SITE_TYPE_CHARACTER_BAG )
		{
			while (front != back)
			{
				pItem = front->second;
				if (pItem->getItemInfo()->getItemUseInfo())
				{
					tempIconInfo.index = pItem->getItemIndex();
					tempIconInfo.dbID = pItem->getItemDBID();
					tempIconInfo.tempID = pItem->getItemTempID();
					tempIconInfo.group = ICON_GROUP_CLAN_BAG;
					tempIconInfo.type = ICON_TYPE_ITEM;
					pItem->getItemInfo()->getItemBaseIconResouce(tempIconInfo.resouceName, tempIconInfo.groupName, tempIconInfo.itemName);

					iconlist.push_back(tempIconInfo);
				}
				++front;
			}
		}
		else if ( mOldItemSiteType = ITEM_SITE_TYPE_CHARACTER_EQUIP )
		{
			while (front != back)
			{
				pItem = front->second;
				if ( 
					pItem->getItemInfo()->getItemBaseItemType()  == ITEM_TYPE_EQUIP_GENERAL	&&
					pItem->getItemEquipSlotType() == mOldItemIndex
					)
				{
					tempIconInfo.index = pItem->getItemIndex();
					tempIconInfo.dbID = pItem->getItemDBID();
					tempIconInfo.tempID = pItem->getItemTempID();
					tempIconInfo.group = ICON_GROUP_CLAN_BAG;
					tempIconInfo.type = ICON_TYPE_ITEM;
					pItem->getItemInfo()->getItemBaseIconResouce(tempIconInfo.resouceName, tempIconInfo.groupName, tempIconInfo.itemName);

					iconlist.push_back(tempIconInfo);
				}

				++front;
			}
		}
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::addUninstallButton()
	{
		if ( mIsAddButton == false )
		{
			getLayout()->getWidget("anyicon0")->setVisible(false);
		}
		else
		{
			Vec2 tempPos;
			IWidget* pWidget = getLayout()->getWidget(MAIN_WIDGET);
			Int mod = mIconNum%ANY_UI_COL_MAX;
			Int row = (mIconNum-1)/ANY_UI_COL_MAX + 1;
			if ( mod == 1 )
			{	
				tempPos.x = ANY_UI_LEFT;
			}
			else if ( mod == 0 )
			{	
				tempPos.x = ANY_ICON_LEFT + ANY_ICON_MIDDLE + ANY_ICON_MIDDLE;
			}
			else
			{	
				tempPos.x = ANY_ICON_LEFT + ANY_ICON_MIDDLE*(mod-2);
			}
			tempPos.y = (row-1)*ANY_ICON_HEIGHT + ANY_UI_TOP;
			IWidget* pChildWidget = getLayout()->getWidget("anyicon0");
			pChildWidget->setVisible(true);
			pChildWidget->setPosition(tempPos);
		}
	}
	//--------------------------------------------------------------------------------------------
	void UIAnyIcon::closeAllChild()
	{
		IWidget* pWidget = NULL;
		IViewScroll* pViewScroll = getLayout()->getViewScroll(MAIN_WIDGET);
		Int ncount = pViewScroll->getWidget()->getChildCount();
		for (Int i=0; i<ncount; i++)
		{
			pWidget = pViewScroll->getWidget()->getChildAt(i);
			pWidget->setVisible(false);
		}
	}
	//--------------------------------------------------------------------------------------
	void UIAnyIcon::onEventToolTips( void* pWidget, Bool isShow, Int left, Int top )
	{
		DYNAMIC_ASSERT(pWidget);
		IWidget* pIcon = (IWidget*)pWidget;
		IAny* pAny = pIcon->getUserData();
		DYNAMIC_ASSERT(pAny);
		IconInfo* pInfo = pAny->castType<IconInfo>();
		DYNAMIC_ASSERT(pInfo);

		// std::vector<UInt> skillList;
		// getCharacterSkillList( UISkillOperate::mCurrCharacterType, UISkillOperate::mCurrCharacterID, skillList);

		if(pInfo->tempID == 0)
		{
			return;
		}

		UIAnyIcon::getInstance().onHandleTips(isShow,pInfo,pIcon->getAbsoluteCoord());  
	}
	//--------------------------------------------------------------------------------------
	void UIAnyIcon::onHandleTips( Bool isShow, IconInfo* pIconInfo, CoordI coord )
	{
		if ( isShow == false )
		{
			switch (pIconInfo->type)
			{
			case ICON_TYPE_ITEM:
				UIItemTips::getInstance().closeGui();
				break;
			case ICON_TYPE_SKILL:
				UISkillTips::getInstance().closeGui();
				break;
			default:    
				break;
			}
		}
		else
		{
			switch (pIconInfo->type)
			{
			case ICON_TYPE_ITEM:
				{
					PlayerItem* pItem = CItemManager::getInstance().findItem(pIconInfo->dbID);
					DYNAMIC_ASSERT(pItem);
					UIItemTips::getInstance().openItemTips(pItem, coord);
				}
				break;
			default:    
				break;
			}
		}
	}
	//界面的大小限制
#undef	ANY_UI_SCROLL_WIDTH
#undef  ANY_UI_WIDTH_MAX
#undef  ANY_UI_HEIGHT_MAX
#undef  ANY_UI_COL_MAX
#undef  ANY_UI_ROW_MAX
	//界面的上下左右的偏移
#undef  ANY_UI_LEFT	
#undef  ANY_UI_TOP
#undef  ANY_UI_BOTTOM
#undef  ANY_UI_RIGHT
	//ICON的大小（居中）
#undef  ANY_ICON_RIGHT
#undef  ANY_ICON_MIDDLE
#undef  ANY_ICON_LEFT
#undef  ANY_ICON_HEIGHT
	//TEXT的大小，位置
#undef  ANY_TEXT_LEFT
#undef  ANY_TEXT_TOP
#undef	ANY_TEXT_WIDTH
#undef  ANY_TEXT_TOP

}