//***********************************************************************************************************
#include "stdafx.h"
#include "GenrealEquip.h"
#include "PlayerItem.h"
#include "PlayerItemFactory.h"
//***********************************************************************************************************
namespace MG
{
    GenrealEquip::GenrealEquip()
    {
        for (Int i=0; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
        {
            mItemEquipArray[i] = NULL;
        }
    }
    //-----------------------------------------------------------------------------------------
    GenrealEquip::~GenrealEquip()
    {
        clear();
    }
    //-----------------------------------------------------------------------------------------
    void GenrealEquip::addItem( PlayerItem* pItem, PlayerCharacterIdType charid, Bool isServer )
    {
        pItem->setItemPos(ITEM_SITE_TYPE_CHARACTER_EQUIP);
        pItem->setItemIndex(pItem->getItemEquipSlotType());
        pItem->setCharacterID(charid);
        mItemEquipArray[pItem->getItemEquipSlotType()] = pItem;
    }
    //-----------------------------------------------------------------------------------------
    PlayerItem* GenrealEquip::removeItem( ITEM_EQUIP_SLOT_TYPE type )
    {
        PlayerItem* tempItem = mItemEquipArray[type];
        mItemEquipArray[type] = NULL;
        tempItem->setCharacterID(0);
        return tempItem;
    }
    //-----------------------------------------------------------------------------------------
    PlayerItem* GenrealEquip::removeItem( IdType itemid )
    {
        PlayerItem* tempItem = NULL;
        for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
        {
            if ( mItemEquipArray[i]  &&  mItemEquipArray[i]->getItemDBID() == itemid )
            {    
                tempItem = mItemEquipArray[i];
                mItemEquipArray[i] = NULL;
                tempItem->setCharacterID(0);
                return tempItem;
            }
        }
        return tempItem;
    }
    //-----------------------------------------------------------------------------------------
    PlayerItem* GenrealEquip::findItem( ITEM_EQUIP_SLOT_TYPE type )
    {
        return mItemEquipArray[type];
    }
    //-----------------------------------------------------------------------------------------
    PlayerItem* GenrealEquip::findItem( IdType itemid )
    {
        for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
        {
            if ( mItemEquipArray[i]  &&  mItemEquipArray[i]->getItemDBID() == itemid )
            {    
                return mItemEquipArray[i]; 
            }
        } 
        return NULL;
    }
    //-----------------------------------------------------------------------------------------
    void GenrealEquip::clear()
    {
        for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
        {
            if ( mItemEquipArray[i] )
            {    
                PlayerItemFactory::getInstance().removeItem(mItemEquipArray[i]);
                mItemEquipArray[i] = NULL;
            }
        } 
    }
    //-----------------------------------------------------------------------------------------
    PlayerItem** GenrealEquip::getEquipItemArray()
    {
        return mItemEquipArray;
    }
}