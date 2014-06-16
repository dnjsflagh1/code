//**************************************************************************************************************
#ifndef _H_SHOPPACKETPROCESSER_
#define _H_SHOPPACKETPROCESSER_
//**************************************************************************************************************
#include "FrontServerPreqs.h"
#include "ShopNetPacket.h"
//**************************************************************************************************************
namespace MG
{
    class ShopPacketProcesser
    {
    public:
        ShopPacketProcesser(){;}
        ~ShopPacketProcesser(){;}
        SINGLETON_INSTANCE(ShopPacketProcesser);

    public:
        Bool	processClientPacket(I32 id, NetEventRecv* packet);
        //Bool	processMapServerPacket(I32 id, NetEventRecv* packet);

    public:
        void    sendOpenShopToClient(I32 id, U32 shopID, Bool isOpen);
        //void    sendCloseShopToMapServer(I32 id, U32 shopID, PlayerIdType playerID);
        //void    sendShopBuyItemToMapServer(I32 id, U32 shopID, U32 itemTempID, U32 num, PlayerIdType playerID);
        //void    sendShopAddItemToMapServer(I32 id, U32 shopID, U32 itemTempID, U32 num, PlayerIdType playerID);
        void    sendShopBuyItemToClient(I32 id, U32 shopID, U32 itemTempID, U32 num, shop_buy_res res);
        void    sendShopSellItemToClient(I32 id, U32 shopID, IdType itemDBID, shop_sell_item_res res);
        void    sendShopRepairItemToClient(I32 id, U32 shopID, IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType charid, shop_repair_res res);
        void    sendShopBuybackItemToClient(I32 id, U32 shopID, IdType itemDBID, U32 index, shop_buyback_res res);

    private:
        void    recvClientOpenShop(I32 id, PT_SHOP_C2S_OPEN_DATA* pData);
        //void    recvClientCloseShop(I32 id, PT_SHOP_C2S_CLOSE_DATA* pData);
        void    recvClientBuyItem(I32 id, PT_SHOP_C2M_BUY_ITEM_DATA* pData);
        //void    recvMapServerBuyItem(I32 id, PT_SHOP_M2F_BUY_ITEM_DATA* pData);
        void    recvClientSellItem(I32 id, PT_SHOP_C2F_SELL_ITEM_DATA* pData);
        void    recvClientRepairItem(I32 id, PT_SHOP_C2F_REPAIR_ITEM_DATA* pData);
        void    recvClientBuybackItem(I32 id, PT_SHOP_C2F_BUYBACK_ITEM_DATA* pData);

    };

}
//**************************************************************************************************************
#endif
//**************************************************************************************************************