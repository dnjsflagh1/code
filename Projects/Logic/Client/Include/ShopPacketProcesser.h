//**************************************************************************************************************
#ifndef _H_SHOPPACKETPROCESSER_
#define _H_SHOPPACKETPROCESSER_
//**************************************************************************************************************
#include "ClientPreqs.h"
#include "ShopNetPacket.h"
#include "GameNetEvent.h"
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
        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

    public:
        void    sendOpenShop(U32 shopID);
        //void    sendCloseShop(U32 shopID);
        void    sendShopBuyItem(U32 shopID, U32 itemTempID, U32 num);
        void    sendShopSellItem(U32 shopID, IdType itemDBId);
        void    sendShopRepairItem(U32 shopID, IdType itemDBId, ITEM_SITE_TYPE type, PlayerCharacterIdType charid = 0);
        void    sendShopBuybackItem(U32 shopID, IdType itemDBId);

    private:
        void    recvOpenShop(I32 id, PT_SHOP_S2C_OPEN_DATA* pData);
        void    recvShopBuyItem(I32 id, PT_SHOP_F2C_BUY_ITEM_DATA* pData);
        void    recvShopSellItem(I32 id, PT_SHOP_F2C_SELL_ITEM_DATA* pData);
        void    recvShopRepairItem(I32 id, PT_SHOP_F2C_REPAIR_ITEM_DATA* pData);
        void    recvShopBuybackItem(U32 shopID, PT_SHOP_F2C_BUYBACK_ITEM_DATA* pData);

    };

}
//**************************************************************************************************************
#endif
//**************************************************************************************************************