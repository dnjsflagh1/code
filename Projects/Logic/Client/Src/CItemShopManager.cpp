//*****************************************************************************************************
#include "stdafx.h"
#include "CItemShop.h"
#include "CItemShopManager.h"
#include "ItemTemplate.h"
#include "CItemManager.h"
#include "PlayerItem.h"
#include "CPlayer.h"
#include "CClan.h"
#include "UIItemShop.h"
#include "UIClanInfo.h"
//*****************************************************************************************************
namespace MG
{
    CItemShopManager::~CItemShopManager()
    {
        clear();
    }
    //---------------------------------------------------------------------------------
    CItemShop* CItemShopManager::handleOpenShop( U32 shopID )
    {
        std::map<U32, CItemShop*>::iterator iter = mCItemShopMap.find(shopID);
        if ( mCItemShopMap.end() != iter )
        {
            return iter->second;
        }
        else
        {
            CItemShop* pShop = new CItemShop(shopID);
            DYNAMIC_ASSERT(pShop);
            mCItemShopMap[shopID] = pShop;

            return pShop;
        }
    }
    //---------------------------------------------------------------------------------
    void CItemShopManager::clear()
    {
        std::map<U32, CItemShop*>::iterator front = mCItemShopMap.begin();
        std::map<U32, CItemShop*>::iterator back = mCItemShopMap.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }

        mCItemShopMap.clear();
    }
    //---------------------------------------------------------------------------------
    void CItemShopManager::handleBuyItem( U32 shopID, U32 itemTempID, U32 num )
    {
        std::map<U32, CItemShop*>::iterator iter = mCItemShopMap.find(shopID);
        if ( mCItemShopMap.end() != iter )
        {
            //减掉道具
            //Int index = iter->second->removeRandItem(itemTempID, num);
            //减掉钱
            //计算需要花多少钱
            const ItemInfo* tempItemInfo = ItemTemplate::getInstance().getItemInfo(itemTempID);
            DYNAMIC_ASSERT(tempItemInfo);
            DYNAMIC_ASSERT(num);
          	
        }  
    }
    //---------------------------------------------------------------------------------
    void CItemShopManager::handleSellItem( U32 shopID, IdType itemDBID )
    {
        CItemManager* pItemManager = &( CItemManager::getInstance() );

        //检查道具是否存在
        PlayerItem* pItem = pItemManager->findItem(itemDBID);
        if ( pItem == NULL )
            return ;
        //商店是否存在
        std::map<U32, CItemShop*>::iterator iter = mCItemShopMap.find(shopID);
        if ( iter == mCItemShopMap.end() )
            return ;

        //从氏族背包中删除,
        pItemManager->handlRemoveItem(pItem, ITEM_SITE_TYPE_CLAN);
        //加钱
        /*pItemManager->addMoney(pItem->getItemNum()*pItem->getItemInfo()->getItemBaseSellPrice(), ITEM_MONEY_CLASS_MONEY_GAME);
		UIItemShop::getInstance().updateMoney();
		UIClanInfo::getInstance().updateMoney();*/
        //商店回购栏存贮物品
        iter->second->sellItemToShop(pItem);

        //通知UI
        UIItemShop::getInstance().addCallBackItem(pItem);
		

    }
    //---------------------------------------------------------------------------------
    void CItemShopManager::handleRepairItem( U32 shopID, IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType charid )
    {
        CItemManager* pItemManager = &( CItemManager::getInstance() );

        //检查道具是否存在
        PlayerItem* pItem = pItemManager->findItem(itemDBID, type, charid);
        if ( pItem == NULL )
            return ;

        const ItemInfo* pInfo = pItem->getItemInfo();
        DYNAMIC_ASSERT(pInfo);
        //不是装备
        if ( pInfo->ItemType != ITEM_TYPE_EQUIP_GENERAL )
            return ;

        //商店是否存在
        std::map<U32, CItemShop*>::iterator iter = mCItemShopMap.find(shopID);
        if ( iter == mCItemShopMap.end() )
            return ;

        //游戏币不够
        Int repairPrice = (Int)( pInfo->getItemEquitRepairPrice() * pItem->getItemCurDur() / pInfo->getItemEquitMaxEquipDurable() );

        //改变属性，扣钱
        pItemManager->addMoney(-repairPrice, ITEM_MONEY_CLASS_MONEY_GAME);
		UIItemShop::getInstance().updateMoney();
		UIClanInfo::getInstance().updateMoney();
        pItem->setItemDur(pInfo->getItemEquitMaxEquipDurable());
        pItem->setItemRepairNum(pItem->getItemRepairNum() + 1);

        //计算属性。
		

    }
    //---------------------------------------------------------------------------------
    void CItemShopManager::handleBuybackItem( U32 shopID, ItemIdType itemDBID, U32 index )
    {
        //商店是否存在
        std::map<U32, CItemShop*>::iterator iter = mCItemShopMap.find(shopID);
        if ( iter == mCItemShopMap.end() )
            return ;
        //从回购栏中删除。
        U32 uiIndex;
        PlayerItem* pItem = iter->second->buybackItemToShop(itemDBID, uiIndex);
        pItem->setItemIndex(index);

        //减掉钱
        //计算需要花多少钱
        const ItemInfo* tempItemInfo = pItem->getItemInfo();
        DYNAMIC_ASSERT(tempItemInfo);
        U32 needMoney = tempItemInfo->getItemBaseBuyPrice() * pItem->getItemNum();
        CItemManager::getInstance().addMoney(-needMoney, ITEM_MONEY_CLASS_MONEY_GAME);
		UIItemShop::getInstance().updateMoney();
		UIClanInfo::getInstance().updateMoney();
        CItemManager::getInstance().handlAddItem(pItem);
        //通知UI
        UIItemShop::getInstance().deleteCallBackItem(pItem, uiIndex);
    }
}