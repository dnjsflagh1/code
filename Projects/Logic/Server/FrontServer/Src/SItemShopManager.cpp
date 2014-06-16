//*****************************************************************************************************
#include "stdafx.h"
#include "SItemShop.h"
#include "SItemShopManager.h"
#include "ItemShopTemplate.h"
#include "ItemTemplate.h"
#include "SClan.h"
#include "SItemManager.h"
#include "ItemPacketProcesser.h"
//*****************************************************************************************************
namespace MG
{
    SItemShopManager::SItemShopManager()
    {
        init();
    }
    //---------------------------------------------------------------------------------
    SItemShopManager::~SItemShopManager()
    {
        clear();
    }
    //---------------------------------------------------------------------------------
    void SItemShopManager::init()
    {
        const std::map<U32, ItemShopInfo*>* pMap = ItemShopTemplate::getInstance().getItemShopInfoMap(); 

        std::map<U32, ItemShopInfo*>::const_iterator front = pMap->begin();
        std::map<U32, ItemShopInfo*>::const_iterator back = pMap->end();
        while (front != back)
        {
            SItemShop* pShop = new SItemShop(front->second);
            mSItemShopMap[front->first] = pShop;

            ++front;
        }
    }
    //---------------------------------------------------------------------------------
    void SItemShopManager::clear()
    {
        std::map<U32, SItemShop*>::iterator front = mSItemShopMap.begin();
        std::map<U32, SItemShop*>::iterator back = mSItemShopMap.end();
        while (front != back)
        {
            delete front->second;
            ++front;
        }

        mSItemShopMap.clear();
    }
    //---------------------------------------------------------------------------------
    MG::shop_buy_res SItemShopManager::handleClientBuyItem( SClan* pClan, U32 shopId, U32 itemTempId, U32 num )
    {
        //����̵��Ƿ����
        std::map<U32, SItemShop*>::iterator front = mSItemShopMap.find(shopId);
        if ( front == mSItemShopMap.end() )
            return shop_buy_res_shop_not_found;
        //������Ҫ������Ǯ
        const ItemInfo* tempItemInfo = ItemTemplate::getInstance().getItemInfo(itemTempId);
        DYNAMIC_ASSERT(tempItemInfo);
        if ( num == 0 )
			num = 1;
        U32 needMoney = tempItemInfo->getItemBaseBuyPrice() * num;

        SItemManager* pSItemManager = pClan->getItemManager();
        DYNAMIC_ASSERT(pSItemManager);
        //��鱳���Ƿ�װ����
        if ( pSItemManager->checkCanAdd(itemTempId,num) == false )
        {   
            return shop_buy_res_bag_capacity_not_enough;  
        }
		
        //���Ǯ������
        if ( pSItemManager->getMoney(ITEM_MONEY_CLASS_MONEY_GAME) < needMoney )
        {    
            return shop_buy_res_not_enough_money;
        }
        //�������Ƿ����
        if ( front->second->checkItemExist(itemTempId) == false )
        {
            return shop_buy_res_item_not_found;
        }

        //��Ǯ���ӵ���
        pSItemManager->handlAddMoney(-needMoney, ITEM_MONEY_CLASS_MONEY_GAME);
        PlayerItem* pItem = NULL;
        pSItemManager->handlAddItem(itemTempId, num);
        return shop_buy_res_success;
    }
    //---------------------------------------------------------------------------------
    //MG::shop_buy_res SItemShopManager::handleMapServerBuyItem( SClan* pClan, U32 shopId, U32 itemTempId, U32 num )
    //{
    //    //����̵��Ƿ����
    //    std::map<U32, SItemShop*>::iterator front = mSItemShopMap.find(shopId);
    //    if ( front == mSItemShopMap.end() )
    //        return shop_buy_res_shop_not_found;
    //    //������Ҫ������Ǯ
    //    const ItemInfo* tempItemInfo = ItemTemplate::getInstance().getItemInfo(itemTempId);
    //    DYNAMIC_ASSERT(tempItemInfo);
    //    DYNAMIC_ASSERT(num);
    //    U32 needMoney = tempItemInfo->getItemBaseBuyPrice() * num;

    //    SItemManager* pSItemManager = pClan->getItemManager();
    //    DYNAMIC_ASSERT(pSItemManager);
    //    //��鱳���Ƿ�װ����
    //    if ( pSItemManager->checkCanAdd(num) == false )
    //    {   
    //        return shop_buy_res_bag_capacity_not_enough;  
    //    }
    //    //���Ǯ������
    //    if ( pSItemManager->getMoney(ITEM_MONEY_CLASS_GAME) < needMoney )
    //    {    
    //        return shop_buy_res_not_enough_money;
    //    }
    //    //��Ǯ���ӵ���
    //    pSItemManager->addMoney(-needMoney, ITEM_MONEY_CLASS_GAME);
    //    PlayerItem* pItem = pSItemManager->handlAddItem(itemTempId, num);
    //    DYNAMIC_ASSERT(pItem);
    //    ItemPacketProcesser::getInstance().sendAddItemToClient(pClan->getClientNetId(), pItem);
    //    
    //    return shop_buy_res_success;
    //}
    //---------------------------------------------------------------------------------
    MG::shop_sell_item_res SItemShopManager::handleClientSellItem( SClan* pClan, U32 shopId, IdType itemDBId )
    {
        SItemManager* pItemManager = pClan->getItemManager();

        //�������Ƿ����
        PlayerItem* pItem = pItemManager->findItem(itemDBId, ITEM_SITE_TYPE_CLAN);
        if ( pItem == NULL )
            return shop_sell_item_res_item_exist;

        //�̵��Ƿ����
        std::map<U32, SItemShop*>::iterator iter = mSItemShopMap.find(shopId);
        if ( iter == mSItemShopMap.end() )
            return shop_sell_item_res_shop_exist;

        //�����Ƿ����
        if ( pItem->getItemInfo()->getItemBaseForbidType() & ITEM_FORBID_TYPE_SHOP == 1 )
            return shop_sell_item_res_notbuy;

        //�����屳����ɾ��,������DB
        pItemManager->handlSellItemToShop(pItem, ITEM_SITE_TYPE_CLAN, ITEM_SITE_TYPE_BUYBACK);
        //��Ǯ
        pItemManager->handlAddMoney(pItem->getItemNum()*pItem->getItemInfo()->getItemBaseSellPrice(), ITEM_MONEY_CLASS_MONEY_GAME);
        //�̵�ع���������Ʒ
        iter->second->sellItemToShop(pClan->getClanID(), pItem);
        return shop_sell_item_res_suc;
		
    }
    //---------------------------------------------------------------------------------
    MG::shop_repair_res SItemShopManager::handleClientRepairItem( SClan* pClan, U32 shopId, IdType itemDBId, ITEM_SITE_TYPE type, PlayerCharacterIdType charid )
    {
        SItemManager* pItemManager = pClan->getItemManager();

        //�������Ƿ����
        PlayerItem* pItem = pItemManager->findItem(itemDBId, type, charid);
        if ( pItem == NULL )
            return shop_repair_res_item_exist;

        const ItemInfo* pInfo = pItem->getItemInfo();
        DYNAMIC_ASSERT(pInfo);
        //����װ��
        if ( pInfo->ItemType != ITEM_TYPE_EQUIP_GENERAL )
            return shop_repair_res_not_equip;
        
        //���������ˣ�����������������
        if ( pInfo->getItemEquitMaxFixNum() < pItem->getItemRepairNum() )
            return shop_repair_res_notrepair;

        //�̵��Ƿ����
        std::map<U32, SItemShop*>::iterator iter = mSItemShopMap.find(shopId);
        if ( iter == mSItemShopMap.end() )
            return shop_repair_res_shop_exist;

        //��Ϸ�Ҳ���
        Int repairPrice = (Int)( pInfo->getItemEquitRepairPrice() * pItem->getItemCurDur() / pInfo->getItemEquitMaxEquipDurable() );
        if ( pItemManager->getMoney(ITEM_MONEY_CLASS_MONEY_GAME) < repairPrice )
            return shop_repair_res_not_money;

        //�ı����ԣ���Ǯ
        pItemManager->handlAddMoney(-repairPrice, ITEM_MONEY_CLASS_MONEY_GAME);
        pItem->setItemDur(pInfo->getItemEquitMaxEquipDurable());
        pItem->setItemRepairNum(pItem->getItemRepairNum() + 1);
		

        return shop_repair_res_suc;
    }
    //---------------------------------------------------------------------------------
    MG::shop_buyback_res SItemShopManager::handleClientBuybackItem( SClan* pClan, U32 shopId, IdType itemDBId, U32& index )
    {
        SItemManager* pItemManager = pClan->getItemManager();

        //�̵��Ƿ����
        std::map<U32, SItemShop*>::iterator iter = mSItemShopMap.find(shopId);
        if ( iter == mSItemShopMap.end() )
            return shop_buyback_res_shop_exist;

        //�������Ƿ����
        PlayerItem* pItem = iter->second->findBuybackItem(pClan->getClanID(), itemDBId);
        if ( pItem == NULL )
            return shop_buyback_res_item_exist;

        //��Ϸ�Ҳ���
        Int repairPrice = pItem->getItemInfo()->getItemBaseBuyPrice() * pItem->getItemNum();
        if ( pItemManager->getMoney(ITEM_MONEY_CLASS_MONEY_GAME) < repairPrice )
            return shop_buyback_res_not_money;

        //�����Ƿ�����
        if ( pItemManager->checkItemFull(ITEM_SITE_TYPE_CLAN) )
            return shop_buyback_res_clanbag_ful;

        //�̵�۳��ع�������Ǯ
        iter->second->buybackItemToShop(pClan->getClanID(), itemDBId);
		pItemManager->handlAddMoney(-repairPrice, ITEM_MONEY_CLASS_MONEY_GAME);
        pItemManager->handlAddItem(pItem);
        index = pItem->getItemIndex();
        
        return  shop_buyback_res_suc;
    }
	//---------------------------------------------------------------------------------
	bool SItemShopManager::checkShopExist( U32 shopId )
	{
		//����̵��Ƿ����
		std::map<U32, SItemShop*>::iterator front = mSItemShopMap.find(shopId);
		if ( front != mSItemShopMap.end() )
			return true;

		return false;
	}
}