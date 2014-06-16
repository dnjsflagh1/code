//***********************************************************************************************************************
#include "stdafx.h"
#include "BuyBackItem.h"
#include "PlayerItem.h"
#include "ItemSiteTemplate.h"
//***********************************************************************************************************************
namespace MG
{
    //-----------------------------------------------------------------------------------
	BuyBackItem::BuyBackItem()
	{
           setSize( ItemSiteTemplate::getInstance().getItemSiteInfo(ITEM_SITE_TYPE_BUYBACK)->DefaultNum ); 
	}
	//-----------------------------------------------------------------------------------
	void BuyBackItem::addItem( PlayerItem* pItem, Bool isServer )
	{
		pItem->setItemPos(ITEM_SITE_TYPE_BUYBACK);
		pItem->setCharacterID(0);
		//
		//
		Items::addItem(pItem); 
	}
	//-----------------------------------------------------------------------------------

}