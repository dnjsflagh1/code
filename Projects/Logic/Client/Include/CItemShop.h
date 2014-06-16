//*****************************************************************************************************
#ifndef _H_CITEMSHP_
#define _H_CITEMSHP_
//*****************************************************************************************************
#include "WorldCorePreqs.h"
#include "ItemShopTemplate.h"
//*****************************************************************************************************
namespace MG
{
    class CItemShop
    {
    public:
        CItemShop(U32 shopID);
        virtual ~CItemShop(){;}

    public:
        //Int                 removeRandItem( U32 tempItemId, U32& num );                  //删除随机道具
        //void                addRandItem(ItemNum tempItem);
        U32                 getItemNumNumber(){return mShopItemNormalVector.size()/* + mShopItemRandlist.size()*/;}
        ItemNum             getItemNumByIndex(U32 index);
        const ItemShopInfo* getShopInfo(){return mItemShopInfo;}

        //回购栏位
        void                sellItemToShop(PlayerItem* pItem);
        PlayerItem*         buybackItemToShop(IdType itemDBId, U32& index);
        U32                 getBuybackItemNum();
        PlayerItem*         getBuybackItemByIndex(U32 index);
        std::vector<PlayerItem*>*
                            getBuybackItemVector();

    private:
        void                Init(U32 shopID);

    private:
        const ItemShopInfo*             mItemShopInfo;
        std::vector<ItemNum>            mShopItemNormalVector;
        //std::vector<ItemNum>            mShopItemRandlist;
        std::vector<PlayerItem*>        mBuybackItemVector;

    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************