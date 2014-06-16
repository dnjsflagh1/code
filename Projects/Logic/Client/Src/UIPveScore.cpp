//*************************************************************************************

#include "stdafx.h"
#include "UIPveScore.h"
#include "CPlayer.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
#include "ItemPacketProcesser.h"
#include "ItemGroupTemplate.h"
#include "UIItemTips.h"
#include "CItemManager.h"
#include "ItemMoneyTemplate.h"
#include "ItemExpListCsv.h"
//*************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------------
	UIPveScore::UIPveScore()
		:mGroupItemId(0)
	{
	}

	UIPveScore::~UIPveScore()
	{

	}

	void UIPveScore::setEvent()
	{
		//getItem
		{
			IButton* btnLeave = getLayout()->getButton("Btn_get");
			DYNAMIC_ASSERT(btnLeave);
			btnLeave->getWidget()->setMouseButtonClickEvent(onClickButtonGetItem);
		}
		//leave
		{
			IButton* btnLeave = getLayout()->getButton("Btn_Leave");
			DYNAMIC_ASSERT(btnLeave);
			btnLeave->getWidget()->setMouseButtonClickEvent(onClickButtonLeave);
		}

		//icon
		Char8 temp[24] = "";
		IWidget* p = NULL;
		for (Int i=1; i<=5; i++)
		{
			sprintf_s(temp, 24, "gruse%d", i);
			p = getLayout()->getWidget(temp);
			p->setToolTipsEvent(onEventToolTips);
			p->setNeedToolTip(true);
			IconInfo info;
			info.group = ICON_GROUP_ITEMSHOP;
			info.type = ICON_TYPE_ITEM;
			info.index = i;
			p->setUserData(info);
		}
	}

	//--------------------------------------------------------------------------------
	void UIPveScore::onClickButtonLeave(void* widget)
	{
		UIPveScore::getInstance().closeGui();
		PlayerCharacterIdType playerCharacterId = CPlayer::getInstance().getMainPlayerCharacterId();
		PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpLastRegion(playerCharacterId);

		//AccountIdType accountId =  CPlayer::getInstance().getAccountID();
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountId, playerCharacterId);
	}

	void UIPveScore::onClickButtonGetItem(void* widget)
	{
		U32 groupItemId = UIPveScore::getInstance().getGroupItemId();
		ItemPacketProcesser::getInstance().sendRewardItem(groupItemId, CPlayer::getInstance().getMainPlayerCharacterId());
	}

	void UIPveScore::onCloseTimeCallBack(void* widget)
	{
		AccountIdType accountId =  CPlayer::getInstance().getAccountID();
		PlayerCharacterIdType playerCharacterId = CPlayer::getInstance().getMainPlayerCharacterId();
		PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpLastRegion(playerCharacterId);
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountId, playerCharacterId);
	}

	void UIPveScore::onEventToolTips( void* pWidget, Bool isShow, Int left, Int top )
	{
		DYNAMIC_ASSERT(pWidget);
		IWidget* pIcon = (IWidget*)pWidget;
		IAny* pAny = pIcon->getUserData();
		DYNAMIC_ASSERT(pAny);
		IconInfo* pInfo = pAny->castType<IconInfo>();
		DYNAMIC_ASSERT(pInfo);

		if ( pInfo->tempID )
		{
			if ( isShow == false )
			{
				UIItemTips::getInstance().closeGui();
			}
			else
			{
				if ( pInfo->dbID )
				{
					PlayerItem* pItem = CItemManager::getInstance().findItem(pInfo->dbID);
					DYNAMIC_ASSERT(pItem);
					UIItemTips::getInstance().openItemTips(pItem, pIcon->getAbsoluteCoord());
				}
				else
				{
					const ItemInfo* pItemInfo = ItemTemplate::getInstance().getItemInfo(pInfo->tempID);
					UIItemTips::getInstance().openItemTips(pItemInfo, pIcon->getAbsoluteCoord());
				}
			}
		}
	}

	Bool UIPveScore::openGui()
	{
		if (false == UIObject::isOpen() )
		{
			UIObject::openGui();
			return true;
		}
		else
		{
		}
		return false;
	}

	void UIPveScore::setCloseTime(Flt seconds)
	{
		getLayout()->getWidget(MAIN_WIDGET)->setCloseEvent(seconds, onCloseTimeCallBack);
	}

	void UIPveScore::UIShowGroupItem(U32 groupItemId)
	{
		std::vector<const ItemGroupInfo*>* groupList = ItemGroupTemplate::getInstance().getItemGroupListByGroupId(groupItemId);
		DYNAMIC_ASSERT(NULL != groupList);

		Int ItemIndex = 0;
		for (std::vector<const ItemGroupInfo*>::iterator iter = groupList->begin(); iter != groupList->end(); ++iter)
		{
			const ItemGroupInfo* itemGroup = *iter;

			const ItemInfo* iteminfo = ItemTemplate::getInstance().getItemInfo(itemGroup->ItemTemplateId);
			DYNAMIC_ASSERT(iteminfo);
			DYNAMIC_ASSERT(iteminfo->ItemType > ITEM_TYPE_NONE && iteminfo->ItemType < ITEM_TYPE_MAX);
			
			if (ITEM_TYPE_EXP == iteminfo->ItemType)
			{
				Char16 temp[64] = L"";
				swprintf_s(temp, 64, L"%d", iteminfo->mItemExpInfo->price);

				IWidget* pWidget = getLayout()->getWidget("text_exp");
				pWidget->setCaption(temp);
				
			}
			else if(ITEM_TYPE_MONEY == iteminfo->ItemType)
			{
				Char16 temp[64] = L"";
					
				U32 money = iteminfo->mItemMoneyInfo->Price;
				U32 money_guan = money/1000;
				U32 money_wen = money%1000;

				if (money_guan > 0)
				{
					//显示【贯】
					IWidget* pWidgetguan = getLayout()->getWidget("text_money_guan");
					swprintf_s(temp, 64, L"%d", money_guan);
					pWidgetguan->setCaption(temp);
				}


				//显示【文】
				IWidget* pWidgetwen = getLayout()->getWidget("text_money_wen");
				swprintf_s(temp, 64, L"%d", money_wen);
				pWidgetwen->setCaption(temp);

				
				
			}
			else
			{
				IImage* pImage = NULL;
				IWidget* pWidget = NULL;
				Char8 temp[64] = "";

				ItemIndex++;
				//图片
				sprintf_s(temp, 64, "gruse%d", ItemIndex);
				pImage = getLayout()->getImage(temp); 
				Str8 resName, groupName, itemName;
				iteminfo->getItemBaseIconResouce(resName, groupName, itemName);
				pImage->setTexture(resName, groupName, itemName);
				IconInfo* pInfo = pImage->getWidget()->getUserData()->castType<IconInfo>();
				DYNAMIC_ASSERT(pInfo);
				pInfo->tempID = iteminfo->getItemBaseTemplateID();
				//pInfo->dbID = dbId;
				pImage->getWidget()->setUserData(*pInfo);
				
				//数量
				sprintf_s(temp, 64, "grtext%d", ItemIndex);
				pWidget = getLayout()->getWidget(temp);
				Char16 tempNumStr[16] = L"";
				swprintf_s(tempNumStr, 16, L"%d", itemGroup->ItemNum);
				pWidget->setCaption(tempNumStr) ;
			}
			
		}
	}

	void UIPveScore::setGroupItemId(U32 groupItemId)
	{
		mGroupItemId = groupItemId;
		UIShowGroupItem(groupItemId);
	}

	U32 UIPveScore::getGroupItemId() const
	{
		DYNAMIC_ASSERT(mGroupItemId > 0);
		return mGroupItemId;
	}
}
