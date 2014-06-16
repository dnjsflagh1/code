//**********************************************************************************************************
#include "stdafx.h"
#include "PlayerItemFactory.h"
#include "PlayerItem.h"
//********************************************************************************************************** 
namespace MG
{
	//--------------------------------------------------------------------------------------------
    PlayerItemFactory::~PlayerItemFactory()
    {

    }
    //--------------------------------------------------------------------------------------------
    PlayerItem* PlayerItemFactory::addItem( U32 itemID, U32 itemTempID )
    {
        PlayerItem* pItem = NULL;

		mPlayerItemPool.threadLock();
		{
			pItem = MG_POOL_NEW(mPlayerItemPool,PlayerItem,());
		}
		mPlayerItemPool.threadUnLock();

		pItem->reset(itemTempID, itemID);

        return pItem;
    }
    //--------------------------------------------------------------------------------------------
    PlayerItem* PlayerItemFactory::addItem( ItemRecord* pRecord, U32 itemTempID )
    {
		PlayerItem* pItem = NULL;

		mPlayerItemPool.threadLock();
		{
			pItem = MG_POOL_NEW(mPlayerItemPool,PlayerItem,());
		}
		mPlayerItemPool.threadUnLock();

		pItem->reset(itemTempID, pRecord);

        return pItem;
    }
    //--------------------------------------------------------------------------------------------
    void PlayerItemFactory::removeItem( PlayerItem* item )
    {
		mPlayerItemPool.threadLock();
		{
			MG_POOL_DELETE(mPlayerItemPool,item);
		}
		mPlayerItemPool.threadUnLock();
    }

}