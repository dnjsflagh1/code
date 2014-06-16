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
            //��������
            //Int index = iter->second->removeRandItem(itemTempID, num);
            //����Ǯ
            //������Ҫ������Ǯ
            const ItemInfo* tempItemInfo = ItemTemplate::getInstance().getItemInfo(itemTempID);
            DYNAMIC_ASSERT(tempItemInfo);
            DYNAMIC_ASSERT(num);
          	
        }  
    }
    //---------------------------------------------------------------------------------
    void CItemShopManager::handleSellItem( U32 shopID, IdType itemDBID )
    {
        CItemManager* pItemManager = &( CItemManager::getInstance() );

        //�������Ƿ����
        PlayerItem* pItem = pItemManager->findItem(itemDBID);
        if ( pItem == NULL )
            return ;
        //�̵��Ƿ����
        std::map<U32, CItemShop*>::iterator iter = mCItemShopMap.find(shopID);
        if ( iter == mCItemShopMap.end() )
            return ;

        //�����屳����ɾ��,
        pItemManager->handlRemoveItem(pItem, ITEM_SITE_TYPE_CLAN);
        //��Ǯ
        /*pItemManager->addMoney(pItem->getItemNum()*pItem->getItemInfo()->getItemBaseSellPrice(), ITEM_MONEY_CLASS_MONEY_GAME);
		UIItemShop::getInstance().updateMoney();
		UIClanInfo::getInstance().updateMoney();*/
        //�̵�ع���������Ʒ
        iter->second->sellItemToShop(pItem);

        //֪ͨUI
        UIItemShop::getInstance().addCallBackItem(pItem);
		

    }
    //---------------------------------------------------------------------------------
    void CItemShopManager::handleRepairItem( U32 shopID, IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType charid )
    {
        CItemManager* pItemManager = &( CItemManager::getInstance() );

        //�������Ƿ����
        PlayerItem* pItem = pItemManager->findItem(itemDBID, type, charid);
        if ( pItem == NULL )
            return ;

        const ItemInfo* pInfo = pItem->getItemInfo();
        DYNAMIC_ASSERT(pInfo);
        //����װ��
        if ( pInfo->ItemType != ITEM_TYPE_EQUIP_GENERAL )
            return ;

        //�̵��Ƿ����
        std::map<U32, CItemShop*>::iterator iter = mCItemShopMap.find(shopID);
        if ( iter == mCItemShopMap.end() )
            return ;

        //��Ϸ�Ҳ���
        Int repairPrice = (Int)( pInfo->getItemEquitRepairPrice() * pItem->getItemCurDur() / pInfo->getItemEquitMaxEquipDurable() );

        //�ı����ԣ���Ǯ
        pItemManager->addMoney(-repairPrice, ITEM_MONEY_CLASS_MONEY_GAME);
		UIItemShop::getInstance().updateMoney();
		UIClanInfo::getInstance().updateMoney();
        pItem->setItemDur(pInfo->getItemEquitMaxEquipDurable());
        pItem->setItemRepairNum(pItem->getItemRepairNum() + 1);

        //�������ԡ�
		

    }
    //---------------------------------------------------------------------------------
    void CItemShopManager::handleBuybackItem( U32 shopID, ItemIdType itemDBID, U32 index )
    {
        //�̵��Ƿ����
        std::map<U32, CItemShop*>::iterator iter = mCItemShopMap.find(shopID);
        if ( iter == mCItemShopMap.end() )
            return ;
        //�ӻع�����ɾ����
        U32 uiIndex;
        PlayerItem* pItem = iter->second->buybackItemToShop(itemDBID, uiIndex);
        pItem->setItemIndex(index);

        //����Ǯ
        //������Ҫ������Ǯ
        const ItemInfo* tempItemInfo = pItem->getItemInfo();
        DYNAMIC_ASSERT(tempItemInfo);
        U32 needMoney = tempItemInfo->getItemBaseBuyPrice() * pItem->getItemNum();
        CItemManager::getInstance().addMoney(-needMoney, ITEM_MONEY_CLASS_MONEY_GAME);
		UIItemShop::getInstance().updateMoney();
		UIClanInfo::getInstance().updateMoney();
        CItemManager::getInstance().handlAddItem(pItem);
        //֪ͨUI
        UIItemShop::getInstance().deleteCallBackItem(pItem, uiIndex);
    }
}