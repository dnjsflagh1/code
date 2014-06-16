//**********************************************************************************************************
#include "stdafx.h"
#include "ItemManager.h"
#include "PlayerItemFactory.h"
#include "GenrealEquip.h"
#include "GenrealItem.h"
#include "PlayerItem.h"

//**********************************************************************************************************
namespace MG
{
    ItemManager::ItemManager()
    {
        for (Int i=0; i<ITEM_MONEY_CLASS_MAX/* - ITEM_MONEY_CLASS_OTHER_SPARE_EXP4*/; i++)
        {
            mMoney[i] = 0;
        }
    }
    //-------------------------------------------------------------------------------------------------
    ItemManager::~ItemManager()
    {
        clear();
    }
    //----------------------------------------------------------------------------------------
    void ItemManager::createItemBag( PlayerCharacterIdType charid )
    {
        GenrealItem* tempGenrealItem = new GenrealItem;
        mGenrealItemMap[charid] = tempGenrealItem;

        GenrealEquip* tempGenrealEquip = new GenrealEquip;
        mGenrealEquipMap[charid] = tempGenrealEquip;
    }
    //-------------------------------------------------------------------------------------------------
    void  ItemManager::eraseItemBag(PlayerCharacterIdType charid)
    {
        std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(charid);
        if ( mGenrealItemMap.end() != iter )
        {  
            delete iter->second;
            mGenrealItemMap.erase(iter);    
        }
        else
            DYNAMIC_ASSERT(0);

        std::map<PlayerCharacterIdType, GenrealEquip*>::iterator iter2 = mGenrealEquipMap.find(charid);
        if ( mGenrealEquipMap.end() != iter2 )
        {  
            delete iter2->second;
            mGenrealEquipMap.erase(iter2);    
        }
        else
            DYNAMIC_ASSERT(0);
    }
    //-------------------------------------------------------------------------------------------------
    PlayerItem* ItemManager::addItem( ItemRecord* pRecord, ITEM_SITE_TYPE type, Bool isServer, PlayerCharacterIdType id /*= 0*/)
    {
        //创建PlayerItem。
        PlayerItem* pItem = PlayerItemFactory::getInstance().addItem(pRecord, pRecord->itemTempID);
        //放入格位中;
        addItem(pItem, type, isServer, id);

        return pItem;
    }
    //-------------------------------------------------------------------------------------------------
    void ItemManager::addItem( PlayerItem* pItem, ITEM_SITE_TYPE type, Bool isServer, PlayerCharacterIdType id /*= 0*/ )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            mClanItems.addItem(pItem, isServer);
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find( id );
                if ( mGenrealItemMap.end() != iter )
                    iter->second->addItem(pItem, id, isServer); 
                else
                    DYNAMIC_ASSERT(0);
            }
            break;
        case ITEM_SITE_TYPE_CHARACTER_EQUIP:
            {
                std::map<PlayerCharacterIdType, GenrealEquip*>::iterator iter = mGenrealEquipMap.find( id );
                if ( mGenrealEquipMap.end() != iter )
                    iter->second->addItem(pItem, id, isServer); 
                else
                    DYNAMIC_ASSERT(0);
            }
			break;
		case ITEM_SITE_TYPE_BUYBACK:
			{  
				//回购栏已满,则删除一个物品后在添加
              // if ()
              // {

              // }
				mBuyBackItem.addItem(pItem, isServer);
			}
			break;
		case ITEM_SITE_TYPE_DEL:
			{
				mDeletedItem.addItem(pItem, isServer);
			}
			break;
        default:
            break;
        }
    }
    //----------------------------------------------------------------------------------------
    PlayerItem* ItemManager::findItem( IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            return mClanItems.findItem(itemDBID);
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
                if ( mGenrealItemMap.end() != iter )
                    return iter->second->findItem(itemDBID);
            }
            break;
        case ITEM_SITE_TYPE_CHARACTER_EQUIP:
            {
                std::map<PlayerCharacterIdType, GenrealEquip*>::iterator iter = mGenrealEquipMap.find(id);
                if ( mGenrealEquipMap.end() != iter )
                    return iter->second->findItem(itemDBID);
            }
            break;
		case ITEM_SITE_TYPE_BUYBACK:
			{
				return mBuyBackItem.findItem(itemDBID);
			}
			break;
		case ITEM_SITE_TYPE_DEL:
			{
				;
			}
			break;
        default:
            break;
        }

        return NULL;
    }
	
    //----------------------------------------------------------------------------------------
    PlayerItem* ItemManager::findItem( U32 slotIndex, ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            return mClanItems.findItem(slotIndex);
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
                if ( mGenrealItemMap.end() != iter )
                    return iter->second->findItem(slotIndex);
            }
            break;
        case ITEM_SITE_TYPE_CHARACTER_EQUIP:
            {
                std::map<PlayerCharacterIdType, GenrealEquip*>::iterator iter = mGenrealEquipMap.find(id);
                if ( mGenrealEquipMap.end() != iter )
                    return iter->second->findItem((ITEM_EQUIP_SLOT_TYPE)slotIndex);
            }
            break;
		case ITEM_SITE_TYPE_BUYBACK:
			return mBuyBackItem.findItem(slotIndex);
			break;
        default:
            break;
        }

        return NULL;
    }
    //----------------------------------------------------------------------------------------
    PlayerItem* ItemManager::findItem( IdType itemDBID )
    {
		//
        PlayerItem* tempItem = NULL;
        tempItem = mClanItems.findItem(itemDBID);
        if ( tempItem )
            return tempItem;

        std::map<PlayerCharacterIdType, GenrealItem*>::iterator frontBag = mGenrealItemMap.begin();
        std::map<PlayerCharacterIdType, GenrealItem*>::iterator backBag = mGenrealItemMap.end();
        while (frontBag != backBag)
        {
            tempItem = frontBag->second->findItem(itemDBID);
            if ( tempItem )
                return tempItem;

            ++frontBag;
        }

        std::map<PlayerCharacterIdType, GenrealEquip*>::iterator frontEquip = mGenrealEquipMap.begin();
        std::map<PlayerCharacterIdType, GenrealEquip*>::iterator backEquip = mGenrealEquipMap.end();
        while (frontEquip != backEquip)
        {
            tempItem = frontEquip->second->findItem(itemDBID);
            if ( tempItem )
                return tempItem;

            ++frontEquip;
        }
		
		tempItem = mBuyBackItem.findItem(itemDBID);
		if ( tempItem )
			return tempItem;

        return tempItem;
    }
   
	 //-------------------------------------------------------------------------------------------------
	//PlayerItem* ItemManager::findItemByTemplateId( U32 itemplateId,ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
	/*{
		  switch (type)
		  {
		  case ITEM_SITE_TYPE_CLAN:
			  return mClanItems.findItemByTemplateId(itemplateId);
			  break;
		  }
		  return NULL;

	}
	*/

    //-------------------------------------------------------------------------------------------------
    MG::U32 ItemManager::getItemNum( ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            return mClanItems.getItemNum();
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
                if ( mGenrealItemMap.end() != iter )
                    return iter->second->getItemNum();
            }
            break;
        default:
            break;
        }

        return 0;
    }
    //-------------------------------------------------------------------------------------------------
    void ItemManager::clear()
    {
        mClanItems.clear(); 

        std::map<PlayerCharacterIdType, GenrealItem*>::iterator frontBag = mGenrealItemMap.begin();
        std::map<PlayerCharacterIdType, GenrealItem*>::iterator backBag = mGenrealItemMap.end();
        while (frontBag != backBag)
        {
            delete frontBag->second;
            ++frontBag;
        }
        mGenrealItemMap.clear();

        std::map<PlayerCharacterIdType, GenrealEquip*>::iterator frontEquip = mGenrealEquipMap.begin();
        std::map<PlayerCharacterIdType, GenrealEquip*>::iterator backEquip = mGenrealEquipMap.end();
        while (frontEquip != backEquip)
        {
            delete frontEquip->second;
            ++frontEquip;
        }
        mGenrealEquipMap.clear();
		
		//TOADD:

    }
	void	ItemManager::clearAllItem()
	{
		mClanItems.clear();

		std::map<PlayerCharacterIdType, GenrealItem*>::iterator frontBag = mGenrealItemMap.begin();
		std::map<PlayerCharacterIdType, GenrealItem*>::iterator backBag = mGenrealItemMap.end();
		while (frontBag != backBag)
		{
			frontBag->second->clear();
			++frontBag;
		}

		std::map<PlayerCharacterIdType, GenrealEquip*>::iterator frontEquip = mGenrealEquipMap.begin();
		std::map<PlayerCharacterIdType, GenrealEquip*>::iterator backEquip = mGenrealEquipMap.end();
		while (frontEquip != backEquip)
		{
			frontEquip->second->clear();
			++frontEquip;
		}
	}
    //-------------------------------------------------------------------------------------------------
    MG::Bool ItemManager::checkItemFull( ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            return mClanItems.checkItemFull();
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
                if ( mGenrealItemMap.end() != iter )
                    return iter->second->checkItemFull();
            }
            break;
        default:
            break;
        }

        return false;
    }
    //-------------------------------------------------------------------------------------------------
    void ItemManager::addMoney( Int num, ITEM_MONEY_CLASS type )
    {
		DYNAMIC_ASSERT(ITEM_MONEY_CLASS_NONE<type  &&  type <ITEM_MONEY_CLASS_MAX);
        mMoney[type] += num;
    }
    //-------------------------------------------------------------------------------------------------
    MG::Int ItemManager::getMoney( ITEM_MONEY_CLASS type )
    {
		DYNAMIC_ASSERT(ITEM_MONEY_CLASS_NONE<type  &&  type <ITEM_MONEY_CLASS_MAX);
        return mMoney[type];
    }
    //-------------------------------------------------------------------------------------------------
    PlayerItem* ItemManager::removeItem( IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            return mClanItems.removeItem(itemDBID);
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
                if ( mGenrealItemMap.end() != iter )
                    return iter->second->removeItem(itemDBID);
            }
            break;
        case ITEM_SITE_TYPE_CHARACTER_EQUIP:
            {
                std::map<PlayerCharacterIdType, GenrealEquip*>::iterator iter = mGenrealEquipMap.find(id);
                if ( mGenrealEquipMap.end() != iter )
                    return iter->second->removeItem(itemDBID);
            }
            break;
        default:
            break;
        }

        return NULL;
    }
    //-------------------------------------------------------------------------------------------------
    PlayerItem* ItemManager::removeItem( U32 index, ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            return mClanItems.removeItem(index);
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
                if ( mGenrealItemMap.end() != iter )
                    return iter->second->removeItem(index);
            }
            break;
        case ITEM_SITE_TYPE_CHARACTER_EQUIP:
            {
                std::map<PlayerCharacterIdType, GenrealEquip*>::iterator iter = mGenrealEquipMap.find(id);
                if ( mGenrealEquipMap.end() != iter )
                    return iter->second->removeItem((ITEM_EQUIP_SLOT_TYPE)index);
            }
            break;
        default:
            break;
        }

        return NULL;
    }
    //-------------------------------------------------------------------------------------------------
    ITEM_DELETE_ERROR ItemManager::deleteItem( IdType itemDBID, ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
    {  
        ITEM_DELETE_ERROR ret = ITEM_DELETE_ERROR_SUCCEED;
        PlayerItem* pItem = findItem(itemDBID,type,id);
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
			{
				ret = mClanItems.deleteItem(itemDBID);
				if (ret == ITEM_DELETE_ERROR_SUCCEED)
				{
                   mDeletedItem.addItem(pItem,true);
				}
			}
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
                if ( mGenrealItemMap.end() != iter )
				{ 
					ret =  iter->second->deleteItem(itemDBID);
					if (ret == ITEM_DELETE_ERROR_SUCCEED)
					{
						mDeletedItem.addItem(pItem,true);
					}

				}
            }
            break;
        default:
            break;
        } 

        return ret;
    }
    //-------------------------------------------------------------------------------------------------
    ITEM_DELETE_ERROR ItemManager::deleteItem( U32 slotIndex, ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
    {
        switch (type)
        {
        case ITEM_SITE_TYPE_CLAN:
            return mClanItems.deleteItem(slotIndex);
            break;
        case ITEM_SITE_TYPE_CHARACTER_BAG:
            {
                std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
                if ( mGenrealItemMap.end() != iter )
                    return iter->second->deleteItem(slotIndex);
            }
            break;
        default:
            break;
        }

        return ITEM_DELETE_ERROR_UI;
    }
    //-------------------------------------------------------------------------------------------------
    GenrealItem* ItemManager::getGenrealItem( PlayerCharacterIdType id )
    {
        std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
        if ( mGenrealItemMap.end() != iter )
            return iter->second;

        return NULL;
    }
    //-------------------------------------------------------------------------------------------------
    GenrealEquip* ItemManager::getGenrealEquip( PlayerCharacterIdType id )
    {
        std::map<PlayerCharacterIdType, GenrealEquip*>::iterator iter = mGenrealEquipMap.find(id);
        if ( mGenrealEquipMap.end() != iter )
            return iter->second;

        return NULL;
    }
	PlayerItem**	ItemManager::getEquipArrayByPlayerCharacterId(PlayerCharacterIdType id)
	{
		GenrealEquip* pGenrealEquip = getGenrealEquip(id);
		if ( pGenrealEquip )
		{
			return pGenrealEquip->getEquipItemArray();
		}

		return NULL;
	}
    //-------------------------------------------------------------------------------------------------
    std::map<PlayerCharacterIdType, GenrealItem*>* ItemManager::getGenrealItemMap()
    {
        return &mGenrealItemMap;
    }
    //-------------------------------------------------------------------------------------------------
    std::map<PlayerCharacterIdType, GenrealEquip*>* ItemManager::getGenrealEquipMap()
    {
        return &mGenrealEquipMap;
    }
    //-------------------------------------------------------------------------------------------------
    MG::Bool ItemManager::checkCanAdd( U32 itemTemplateId,U32 num )
    {
        return getClanItems()->checkClanItemsCanAdd(itemTemplateId,num);
    }
	//-------------------------------------------------------------------------------------------------
	MG::Bool ItemManager::checkCanAdd( std::vector<ItemNum>& itemVector )
	{
          return getClanItems()->checkClanItemsCanAdd(itemVector);
	}
	//-------------------------------------------------------------------------------------------------
	MG::Bool ItemManager::checkIsNeedOverlay( U32 itemTemplateId )
	{
		return getClanItems()->checkIsNeedOverlay(itemTemplateId);
	}
	//-------------------------------------------------------------------------------------------------
	MG::U32 ItemManager::findItemCountByTemplateId( U32 itemplateId,ITEM_SITE_TYPE type, PlayerCharacterIdType id /*= 0*/ )
	{
		switch (type)
		{
		case ITEM_SITE_TYPE_CLAN:
			return mClanItems.getItemCount(itemplateId);
			break;
		case ITEM_SITE_TYPE_CHARACTER_BAG:
			{
				std::map<PlayerCharacterIdType, GenrealItem*>::iterator iter = mGenrealItemMap.find(id);
				if ( mGenrealItemMap.end() != iter )
					return iter->second->getItemCount(itemplateId);
			}
			break;
		case ITEM_SITE_TYPE_CHARACTER_EQUIP:
			{
				//不考虑
			}
			break;
		default:
			break;
		}

		return 0;

	}
}