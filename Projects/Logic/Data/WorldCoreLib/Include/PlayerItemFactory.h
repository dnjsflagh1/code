//**********************************************************************************************************
#ifndef _H_PLAYERITEMFACTORY_
#define _H_PLAYERITEMFACTORY_
//**********************************************************************************************************
#include "WorldCorePreqs.h"
//**********************************************************************************************************
namespace MG
{
    class PlayerItemFactory
    {
    public:
        PlayerItemFactory(){;}
        ~PlayerItemFactory();
        SINGLETON_INSTANCE(PlayerItemFactory);

    public:

        PlayerItem* addItem(U32 itemID, U32 itemTempID);
        PlayerItem* addItem(ItemRecord* pRecord, U32 itemTempID);
        void        removeItem(PlayerItem* item);

    private:

		ObjectPool<PlayerItem>		mPlayerItemPool;
    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************