//*****************************************************************************************************
#ifndef _H_SITEMSHPMANAGER_
#define _H_SITEMSHPMANAGER_
//*****************************************************************************************************
#include "WorldCorePreqs.h"
#include "FrontServerPreqs.h"
#include "ShopNetPacket.h"
//*****************************************************************************************************
namespace MG
{
    class SItemShopManager
    {
    public:
        SItemShopManager();
        ~SItemShopManager();
        SINGLETON_INSTANCE(SItemShopManager);

    public:
		bool						checkShopExist(U32 shopId);
        shop_buy_res                handleClientBuyItem(SClan* pClan, U32 shopId, U32 itemTempId, U32 num);
        //shop_buy_res                handleMapServerBuyItem(SClan* pClan, U32 shopId, U32 itemTempId, U32 num);
        shop_sell_item_res          handleClientSellItem(SClan* pClan, U32 shopId, IdType itemDBId);
        shop_repair_res             handleClientRepairItem(SClan* pClan, U32 shopId, IdType itemDBId, ITEM_SITE_TYPE type, PlayerCharacterIdType charid);
        shop_buyback_res            handleClientBuybackItem(SClan* pClan, U32 shopId, IdType itemDBId, U32& index);

    private:
        void                        init();
        void                        clear();
    private:
        std::map<U32, SItemShop*> mSItemShopMap;

    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************