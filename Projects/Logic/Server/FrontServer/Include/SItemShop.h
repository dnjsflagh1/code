//*****************************************************************************************************
#ifndef _H_SITEMSHP_
#define _H_SITEMSHP_
//*****************************************************************************************************
#include "WorldCorePreqs.h"
//*****************************************************************************************************
namespace MG
{
    class SItemShop
    {
    public:
        SItemShop(const ItemShopInfo* pInfo);
        virtual ~SItemShop(){;}

    public:
        Bool                checkItemExist(U32 itemTempID);                  //ɾ���������
        const ItemShopInfo* getItemShopInfo();

        //�ع���λ
        void                sellItemToShop(ClanIdType clanId, PlayerItem* pItem);
        PlayerItem*         buybackItemToShop(ClanIdType clanId, IdType itemDBId);
        PlayerItem*         findBuybackItem(ClanIdType clanId, IdType itemDBId);

    private:
        void                Init();

    private:
        const ItemShopInfo*             mItemShopInfo;
        std::vector<ItemNum>            mItemNormalVector;
        std::map<ClanIdType, std::vector<PlayerItem*>> mMapBuybackItemVector;
    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************