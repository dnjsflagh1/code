//**********************************************************************************************************
#include "stdafx.h"
#include "PlayerItem.h"
#include "ItemTemplate.h"
#include "ItemMoneyTemplate.h"
#include "ItemEquipTemplate.h"
#include "ItemUseTemplate.h"
#include "ItemOtherTemplate.h"
#include "AttributeAppend.h"
//**********************************************************************************************************
namespace MG
{
    //----------------------------------------------------------------------------------------
    PlayerItem::PlayerItem()
    {
        mItemInfo = NULL;
        mItemRecord = MG_NEW ItemRecord;
    }
    //----------------------------------------------------------------------------------------
    PlayerItem::~PlayerItem()
    {
        DYNAMIC_ASSERT_LOG( mItemRecord != NULL , "PlayerItem::~PlayerItem() : mItemRecord is NULL!" );
        MG_SAFE_DELETE( mItemRecord ) ;
        mItemRecord = NULL;
        mItemInfo = NULL;
    }
    //----------------------------------------------------------------------------------------
    void PlayerItem::reset( U32 itemTemplate, U32 itemID )
    {
        clear();
        
        mItemInfo = ItemTemplate::getInstance().getItemInfo(itemTemplate);
        DYNAMIC_ASSERT(mItemInfo);

        mItemRecord->itemDBID = itemID;
        mItemRecord->itemTempID = itemTemplate;

        //耐久，
        //随机附加ID。
    }
    //----------------------------------------------------------------------------------------
    void PlayerItem::reset( U32 itemTemplate, ItemRecord* pRecord )
    {
        clear();

        mItemInfo = ItemTemplate::getInstance().getItemInfo(itemTemplate);
        *mItemRecord = *pRecord;
        DYNAMIC_ASSERT(pRecord);
        DYNAMIC_ASSERT(mItemInfo);
    }
    //----------------------------------------------------------------------------------------
    void PlayerItem::clear()
    {
        mItemInfo = NULL;

        mItemRecord->clear();
    }
    //----------------------------------------------------------------------------------------
    void PlayerItem::setItemNum( U32 num )
    {
        mItemRecord->curNum = num;
    }
    //----------------------------------------------------------------------------------------
    void PlayerItem::setItemRecord( ItemRecord* pRecord )
    {
        *mItemRecord = *pRecord;
    }
    //----------------------------------------------------------------------------------------
    void PlayerItem::setItemIndex( U32 index )
    {
        //检查是否超出范围
        mItemRecord->slotIndex = index;
    }
    //----------------------------------------------------------------------------------------
    void PlayerItem::setItemPos( ITEM_SITE_TYPE type )
    {
        //检查是否是正确位置
        mItemRecord->belongPos = type;
    }
    //----------------------------------------------------------------------------------------
    MG::Bool PlayerItem::ifOverlying(  ) const
    {
        return mItemInfo->getItemBaseMaxPileNum() > 1;
    }
    //----------------------------------------------------------------------------------------
    MG::ITEM_EQUIP_SLOT_TYPE PlayerItem::getItemEquipSlotType() const
    {
        return mItemInfo->getItemEquitEquipSlotType();
    }
    //----------------------------------------------------------------------------------------
    MG::U32 PlayerItem::getItemPileMaxNum() const
    {
        return mItemInfo->getItemBaseMaxPileNum();
    }
	//----------------------------------------------------------------------------------------
	void PlayerItem::setNewEquip()
	{
		DYNAMIC_ASSERT(mItemInfo->ItemType == ITEM_TYPE_EQUIP_GENERAL);

		mItemRecord->curDurable = mItemInfo->getItemEquitMaxEquipDurable();
		if ( mItemInfo->getItemEquitRandAttrAppendId() )
		{
			const AttributeAppendInfo* pAttributeAppendInfo = 
				AttributeAppend::getInstance().getRandAttributeAppendInfo(mItemInfo->getItemEquitRandAttrAppendId());
			DYNAMIC_ASSERT(pAttributeAppendInfo);
			mItemRecord->randAppendID = pAttributeAppendInfo->AbilityAppendId;
		}
	}
	//----------------------------------------------------------------------------------------
	void PlayerItem::setNewBase( ITEM_BELONG_TYPE type, IdType belongId, UInt slotIndex, UInt num )
	{
		mItemRecord->itemBelongType = type; 
		mItemRecord->itemBelongID = belongId;
		//检查是否超出范围
		mItemRecord->slotIndex = slotIndex;
		mItemRecord->curNum = num;

		if ( ITEM_TYPE_EQUIP_GENERAL == mItemInfo->ItemType )
		{
			setNewEquip();
		}
	}

}