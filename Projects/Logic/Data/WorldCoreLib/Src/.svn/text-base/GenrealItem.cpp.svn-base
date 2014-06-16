//***********************************************************************************************************************
#include "stdafx.h"
#include "GenrealItem.h"
#include "PlayerItem.h"
#include "ItemSiteTemplate.h"
//***********************************************************************************************************************
namespace MG
{
    GenrealItem::GenrealItem()
    {
        setSize( ItemSiteTemplate::getInstance().getItemSiteInfo(ITEM_SITE_TYPE_CHARACTER_BAG)->DefaultNum ); 
    }
    //-----------------------------------------------------------------------------------
    void GenrealItem::addItem( PlayerItem* pItem, PlayerCharacterIdType charid, Bool isServer )
    {
        pItem->setItemPos(ITEM_SITE_TYPE_CHARACTER_BAG);
        pItem->setCharacterID(charid);
        Items::addItem(pItem); 
    }
}