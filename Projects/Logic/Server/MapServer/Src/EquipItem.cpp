//***************************************************************************************************
#include "stdafx.h"
#include "EquipItem.h"
#include "ItemTemplate.h"
#include "SCharacter.h"
#include "SAttributeSystem.h"
#include "AttributeAppend.h"
#include "CharacterList.h"
#include "CharacterGenrealList.h"
#include "SBuffManager.h"
//***************************************************************************************************
namespace MG
{
    EquipItem::EquipItem()
    {
        clear();
    }
    //-----------------------------------------------------------------------------
    EquipItem::~EquipItem()
    {
        clear();
    }
    //-----------------------------------------------------------------------------
    void EquipItem::setEquipItem( U32 equipid, U32 strengthenLv, U32 randAppendID, U32 strengthenAppendID, U32 pos, SCharacter* pSCharacter )
    {
		if ( pSCharacter  &&  mEquipItemDataArray[pos].mItemInfo )
		{	
			calAttr(pSCharacter, pos, false);
			//去除buff
			if ( mEquipItemDataArray[pos].mItemInfo->getItemEquitStateId() )
			{	
				pSCharacter->getSBuffManager()->deleteBuff(mEquipItemDataArray[pos].mItemInfo->getItemEquitStateId());
			}
		}
		if ( equipid != 0  )
		{
			mEquipItemDataArray[pos].mItemInfo = ItemTemplate::getInstance().getItemInfo(equipid);
			mEquipItemDataArray[pos].mStrengthenLv = strengthenLv;
			mEquipItemDataArray[pos].mRandAppendID = randAppendID;
			mEquipItemDataArray[pos].mStrengthenAppendID = strengthenAppendID;
			if ( pSCharacter )
			{	
				calAttr(pSCharacter, pos, true);
				//加buff
				if ( mEquipItemDataArray[pos].mItemInfo->getItemEquitStateId()  &&  
					 mEquipItemDataArray[pos].mItemInfo->getItemEquitStateNum()
					 )
				{
					pSCharacter->getSBuffManager()->addNewBuff(
						mEquipItemDataArray[pos].mItemInfo->getItemEquitStateId()
						, mEquipItemDataArray[pos].mItemInfo->getItemEquitStateNum()
						, pSCharacter->getLevel()
					);
				}
			}
		}
		else
		{
			mEquipItemDataArray[pos].mItemInfo = NULL;
			mEquipItemDataArray[pos].mStrengthenLv = 0;
			mEquipItemDataArray[pos].mRandAppendID = 0;
			mEquipItemDataArray[pos].mStrengthenAppendID = 0;
		}  
    }
	//-----------------------------------------------------------------------------
	void EquipItem::getEquipItemList(U32* equipListid)
    {
		for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
		{
			if ( mEquipItemDataArray[i].mItemInfo )
				equipListid[i] = mEquipItemDataArray[i].mItemInfo->getItemBaseTemplateID();
			else
				equipListid[i] = 0;
		}
    }
	//-----------------------------------------------------------------------------
    MG::Bool EquipItem::checkIsEmpty()
    {
        for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
        {
            if ( mEquipItemDataArray[i].mItemInfo )
                return false;
        }
        return true;
    }
	//-----------------------------------------------------------------------------
	void EquipItem::clear()
	{
		for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
		{
			mEquipItemDataArray[i].clear();
		}
	}
	//-----------------------------------------------------------------------------
	void EquipItem::calAttr( SCharacter* pSCharacter, U32 pos, Bool isAdd )
	{
		SAttributeSystem* pSAttributeSystem = pSCharacter->getSAttributeSystem();
		std::map<U32, Flt> tempAttrMap;	 
		getAttrMapBySlot(pos, &tempAttrMap);

		std::map<U32, Flt>::iterator front = tempAttrMap.begin();
		std::map<U32, Flt>::iterator back = tempAttrMap.end();
		while (front != back)
		{
			if ( isAdd )
			{	
				pSAttributeSystem->calRelateAttr(
					front->first, front->second,
					pSCharacter->getCharacterTempInfo()->getCharacterFormulaType(),
					pSCharacter->getCharacterData()
					);
			}
			else
			{	
				pSAttributeSystem->calRelateAttr(
					front->first, -front->second,
					pSCharacter->getCharacterTempInfo()->getCharacterFormulaType(),
					pSCharacter->getCharacterData()
					);
			}

			++front;
		}
	}
	//-----------------------------------------------------------------------------
	void EquipItem::calAttrAll( SCharacter* pSCharacter )
	{
		for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
		{
			if ( mEquipItemDataArray[i].mItemInfo )
				calAttr(pSCharacter, i, true);
		}
	}
	//-----------------------------------------------------------------------------
	void EquipItem::getAttrMapBySlot( U32 pos, std::map<U32, Flt>* tempAttrMap )
	{
		if ( mEquipItemDataArray[pos].mItemInfo  &&  mEquipItemDataArray[pos].mItemInfo->getItemEquitAttrAppendId() )
		{
			//先找到基本属性。
			const AttributeAppendInfo* tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(mEquipItemDataArray[pos].mItemInfo->getItemEquitAttrAppendId());
			if ( tempAppendAttr )
			{
				for (Int i=0; i<APPENDATTR_NUM; i++)
				{
					if ( tempAppendAttr->AppendAttrList[i].id )
					{  
						if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
							(*tempAttrMap)[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
						else
							(*tempAttrMap)[tempAppendAttr->AppendAttrList[i].id] += 
							tempAppendAttr->AppendAttrList[i].value*mEquipItemDataArray[pos].mItemInfo->getItemBaseScore()*PERMILLAGE_VALUE;
					}
					else
						continue;
				}
			}
			//附加属性
			if ( mEquipItemDataArray[pos].mRandAppendID )
			{
				tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(mEquipItemDataArray[pos].mRandAppendID);
				if ( tempAppendAttr )
				{
					for (Int i=0; i<APPENDATTR_NUM; i++)
					{
						if ( tempAppendAttr->AppendAttrList[i].id )
						{   
							if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
								(*tempAttrMap)[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
							else
								(*tempAttrMap)[tempAppendAttr->AppendAttrList[i].id] += 
								tempAppendAttr->AppendAttrList[i].value*mEquipItemDataArray[pos].mItemInfo->getItemBaseScore()*PERMILLAGE_VALUE;
						}
						else
							continue;
					}
				}
			}
			//强化属性
			if ( mEquipItemDataArray[pos].mStrengthenLv )
			{
				if ( mEquipItemDataArray[pos].mItemInfo->getItemEquitStrenRandAttrAppendId() )
				{
					tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(mEquipItemDataArray[pos].mItemInfo->getItemEquitStrenRandAttrAppendId());
					if ( tempAppendAttr )
					{
						for (Int i=0; i<APPENDATTR_NUM; i++)
						{
							if ( tempAppendAttr->AppendAttrList[i].id )
							{   
								if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL )
									(*tempAttrMap)[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
								else
									(*tempAttrMap)[tempAppendAttr->AppendAttrList[i].id] += 
									tempAppendAttr->AppendAttrList[i].value*mEquipItemDataArray[pos].mStrengthenLv*PERMILLAGE_VALUE;
							}
							else
								break;
						}
					}
					//强化附加属性
					if ( mEquipItemDataArray[pos].mStrengthenAppendID )
					{
						tempAppendAttr = AttributeAppend::getInstance().getAttributeAppendInfo(mEquipItemDataArray[pos].mStrengthenAppendID);
						if ( tempAppendAttr )
						{
							for (Int i=0; i<APPENDATTR_NUM; i++)
							{
								if ( tempAppendAttr->AppendAttrList[i].id )
								{   
									if ( tempAppendAttr->AppendType == APPEND_TYPE_REAL)
										(*tempAttrMap)[tempAppendAttr->AppendAttrList[i].id] += tempAppendAttr->AppendAttrList[i].value;
									else
										(*tempAttrMap)[tempAppendAttr->AppendAttrList[i].id] += 
										tempAppendAttr->AppendAttrList[i].value*mEquipItemDataArray[pos].mStrengthenLv*PERMILLAGE_VALUE;
								}
								else
									break;
							}
						}
					}
				}          
			}
		}
	}
	//-----------------------------------------------------------------------------
	void EquipItem::calAttrAllBase( SCharacter* pSCharacter )
	{
		for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
		{
			if ( mEquipItemDataArray[i].mItemInfo )
			{
				SAttributeSystem* pSAttributeSystem = pSCharacter->getSAttributeSystem();
				std::map<U32, Flt> tempAttrMap;	 
				getAttrMapBySlot(i, &tempAttrMap);

				std::map<U32, Flt>::iterator front = tempAttrMap.begin();
				std::map<U32, Flt>::iterator back = tempAttrMap.end();
				while (front != back)
				{
					pSAttributeSystem->addValue(
						front->first,
						front->second
					);

					++front;
				}
			}
		}
		
	}
	//*******************************************************************************************
	void EquipItemData::clear()
	{
		mItemInfo = NULL;
		mStrengthenLv = 0;
		mRandAppendID = 0;
		mStrengthenAppendID = 0;
	}

}	