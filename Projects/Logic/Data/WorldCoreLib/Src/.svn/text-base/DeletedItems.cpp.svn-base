//***********************************************************************************************************************
#include "stdafx.h"
#include "DeletedItems.h"
#include "PlayerItem.h"
#include "ItemSiteTemplate.h"
//***********************************************************************************************************************
namespace MG
{
    //--------------------------------------------------------------------------------------------
	DeletedItem::DeletedItem()
	{
       //setSize( ItemSiteTemplate::getInstance().getItemSiteInfo(ITEM_SITE_TYPE_CHARACTER_BAG)->DefaultNum ); 
	}
	//--------------------------------------------------------------------------------------------
	void DeletedItem::addItem( PlayerItem* pItem, Bool isServer )
	{
		pItem->setItemPos(ITEM_SITE_TYPE_DEL);
		pItem->setCharacterID(0);
		Items::addItem(pItem); 
	}
	//--------------------------------------------------------------------------------------------
}