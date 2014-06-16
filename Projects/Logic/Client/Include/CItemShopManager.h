//*****************************************************************************************************
#ifndef _H_CITEMSHPMANAGER_
#define _H_CITEMSHPMANAGER_
//*****************************************************************************************************
#include "WorldCorePreqs.h"
//*****************************************************************************************************
namespace MG
{
    class CItemShopManager
    {
    public:
        CItemShopManager(){;}
        ~CItemShopManager();
        SINGLETON_INSTANCE(CItemShopManager);

    public:
        CItemShop*                  handleOpenShop(U32 shopID);
        void                        handleBuyItem(U32 shopID, U32 itemTempID, U32 num);
        void                        handleSellItem(U32 shopID, IdType itemDBID);
        void                        handleRepairItem(U32 shopID, IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType charid);
        void                        handleBuybackItem(U32 shopID, ItemIdType itemDBID, U32 index);

    private:
        void                        clear();

    private:
        std::map<U32, CItemShop*>   mCItemShopMap;
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************