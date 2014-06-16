//*****************************************************************************************************
#include "stdafx.h"
#include "CItemShop.h"
#include "ItemGroupTemplate.h"
#include "PlayerItem.h"
//*****************************************************************************************************
namespace MG
{
    CItemShop::CItemShop( U32 shopID )
        :mItemShopInfo(NULL)
    {
        Init(shopID);
    }
    //--------------------------------------------------------------------------------
    void CItemShop::Init( U32 shopID )
    {
        ItemShopTemplate::getInstance().getItemShopInfo(shopID, mItemShopInfo);
        DYNAMIC_ASSERT(mItemShopInfo);

        ItemGroupTemplate::getInstance().getItemGroupInfo(mItemShopInfo->GroupID, mShopItemNormalVector);
    }
    //--------------------------------------------------------------------------------
    //MG::Int CItemShop::removeRandItem( U32 tempItemId, U32& num )
    //{
    //    U32 nCount = 0;
    //    std::vector<ItemNum>::iterator front =  mShopItemRandlist.begin();
    //    std::vector<ItemNum>::iterator back = mShopItemRandlist.end();
    //    while (front != back)
    //    {
    //        if ( (*front).itemTemplate == tempItemId && (*front).num >= num )
    //        {
    //            (*front).num -= num ;
    //            return nCount + mShopItemNormalVector.size();
    //        }

    //        ++front;
    //        ++nCount;
    //    }

    //    return -1;
    //}
    //--------------------------------------------------------------------------------
    //void CItemShop::addRandItem( ItemNum tempItem )
    //{
    //    mShopItemRandlist.push_back(tempItem);
    //}
    //--------------------------------------------------------------------------------
    MG::ItemNum CItemShop::getItemNumByIndex( U32 index )
    {
        if ( index < mShopItemNormalVector.size())
        {
            return mShopItemNormalVector[index];
        }
        //else
        //{
        //    index -= mShopItemNormalVector.size();
        //    DYNAMIC_ASSERT(index < mShopItemRandlist.size());
        //    return mShopItemRandlist[index];
        //}

        return ItemNum();
    }
    //--------------------------------------------------------------------------------
    void CItemShop::sellItemToShop( PlayerItem* pItem )
    {
        mBuybackItemVector.push_back(pItem);
    }
    //--------------------------------------------------------------------------------
    PlayerItem* CItemShop::buybackItemToShop( IdType itemDBId, U32& index )
    {
        index = 1;
        PlayerItem* tempItem = NULL;
        std::vector<PlayerItem*>::iterator front = mBuybackItemVector.begin();
        std::vector<PlayerItem*>::iterator back = mBuybackItemVector.end();
        while (front != back)
        {
            if ( (*front)->getItemDBID() == itemDBId )
            {
                tempItem =  (*front);
                mBuybackItemVector.erase(front);
                break;
            }
            ++front;
            ++index;
        }
        return tempItem;
    }
    //--------------------------------------------------------------------------------
    std::vector<PlayerItem*>* CItemShop::getBuybackItemVector()
    {
        return &mBuybackItemVector;
    }
    //--------------------------------------------------------------------------------
    MG::U32 CItemShop::getBuybackItemNum()
    {
        return mBuybackItemVector.size();
    }
    //--------------------------------------------------------------------------------
    PlayerItem* CItemShop::getBuybackItemByIndex( U32 index )
    {
        return mBuybackItemVector[index];
    }
}