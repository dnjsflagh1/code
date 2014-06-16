//*****************************************************************************************************
#ifndef _H_ITEM_SHOP_TEMPLATE_
#define _H_ITEM_SHOP_TEMPLATE_
//*****************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************
namespace MG
{
    //--------------------------------------------------------------------------------------
    struct  ItemShopInfo
    {
        U32             ItemShopID      ;                                   //商店id
        Char16          ShopName[NAME_LENGTH];                              //商店名称
        U32             Repair          ;                                   //功能（修理，买卖）
        U32             MoneyId         ;                                   //除游戏币外的其他货币
        U32             GroupID         ;                                   //群id
    };
    //--------------------------------------------------------------------------------------
    class ItemShopTemplate
    {
    public:
        ItemShopTemplate(){}
        ~ItemShopTemplate();
        SINGLETON_INSTANCE(ItemShopTemplate);

    public:
		// MG_CN_MODIFY
        Bool                    load(Str16 fileName, IMGExternalPackManager* packManager = NULL);
        const ItemShopInfo*     getItemShopInfo(U32 shopId);
        Bool                    getItemShopInfo(U32 shopId, const ItemShopInfo*& info);
        const std::map<U32, ItemShopInfo*>*  getItemShopInfoMap(){return &mItemShopInfoMap;}

    private:
        void                    clear();

    private:
        std::map<U32, ItemShopInfo*>    mItemShopInfoMap;
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************