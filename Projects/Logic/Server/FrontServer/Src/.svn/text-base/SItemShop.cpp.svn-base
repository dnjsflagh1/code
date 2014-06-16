//*****************************************************************************************************
#include "stdafx.h"
#include "SItemShop.h"
#include "ItemShopTemplate.h"
#include "ItemGroupTemplate.h"
#include "ItemRandomTemplate.h"
#include "PlayerItem.h"
//*****************************************************************************************************
namespace MG
{
    SItemShop::SItemShop( const ItemShopInfo* pInfo )
        :mItemShopInfo(pInfo)
    {
        Init();
    }
    //-----------------------------------------------------------------------------
    void SItemShop::Init()
    {
        ItemGroupTemplate::getInstance().getItemGroupInfo(mItemShopInfo->GroupID, mItemNormalVector);
    }
    //-----------------------------------------------------------------------------
    MG::Bool SItemShop::checkItemExist( U32 itemTempID )
    {
        std::vector<ItemNum>::const_iterator front = mItemNormalVector.begin();
        std::vector<ItemNum>::const_iterator back = mItemNormalVector.end();
        while (front != back)
        {
            if ( (*front).itemTemplate == itemTempID )
                return true;
            ++front;
        }

        return false;
    }
	//-----------------------------------------------------------------------------
    const ItemShopInfo* SItemShop::getItemShopInfo()
    {
        return mItemShopInfo;
    }
    //-----------------------------------------------------------------------------
    void SItemShop::sellItemToShop( ClanIdType clanId, PlayerItem* pItem )
    {
        pItem->setItemPos(ITEM_SITE_TYPE_BUYBACK);
        std::map<ClanIdType, std::vector<PlayerItem*>>::iterator iter = mMapBuybackItemVector.find(clanId);
        if ( iter != mMapBuybackItemVector.end() )
        {
            iter->second.push_back(pItem);
        }
        else
        {
            std::vector<PlayerItem*> tempVector;
            tempVector.push_back(pItem);
            mMapBuybackItemVector[clanId] = tempVector;
        }
    }
    //-----------------------------------------------------------------------------
    PlayerItem* SItemShop::buybackItemToShop( ClanIdType clanId, IdType itemDBId )
    {
        PlayerItem* tempItem = NULL;
        std::map<ClanIdType, std::vector<PlayerItem*>>::iterator iter = mMapBuybackItemVector.find(clanId);
        if ( iter != mMapBuybackItemVector.end() )
        {
            std::vector<PlayerItem*>::iterator front = iter->second.begin();
            std::vector<PlayerItem*>::iterator back = iter->second.end();
            while (front != back)
            {
                if ( (*front)->getItemDBID() == itemDBId )
                {
                    tempItem =  (*front);
                    iter->second.erase(front);
                    break;
                }
                ++front;
            }
        }
        
        return tempItem;
    }
    //-----------------------------------------------------------------------------
    PlayerItem* SItemShop::findBuybackItem( ClanIdType clanId, IdType itemDBId )
    {
        PlayerItem* tempItem = NULL;
        std::map<ClanIdType, std::vector<PlayerItem*>>::iterator iter = mMapBuybackItemVector.find(clanId);
        if ( iter != mMapBuybackItemVector.end() )
        {
            std::vector<PlayerItem*>::iterator front = iter->second.begin();
            std::vector<PlayerItem*>::iterator back = iter->second.end();
            while (front != back)
            {
                if ( (*front)->getItemDBID() == itemDBId )
                {
                    tempItem =  (*front);
                    break;
                }
                ++front;
            }
        }
		
        return tempItem;
    }
}