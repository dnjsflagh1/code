//*****************************************************************************************************************
#include "stdafx.h"
#include "ItemTemplate.h"
#include "ArtIconResCsv.h"
#include "ItemEquipTemplate.h"
#include "ItemUseTemplate.h"
#include "ItemOtherTemplate.h"
#include "ItemMoneyTemplate.h"
#include "ItemExpListCsv.h"
#include "ItemClanListCsv.h"
//*****************************************************************************************************************
namespace MG
{
	ItemTemplate::ItemTemplate()
	{
	}

    ItemTemplate::~ItemTemplate()
    {
    }
    //-------------------------------------------------------------------------------------------------
    // MG_CN_MODIFY
	Bool ItemTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
    {
        CsvReader csvreader;

        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

		DYNAMIC_ASSERT(csvreader.getColumnSize() == ItemTemplateRow_Max);

        CsvData* csvdata = NULL;
        Int RowCount = csvreader.count();

        for(int i = 0; i < RowCount; ++i)
        {
            csvdata = csvreader.findValue(i);
            if(!csvdata)
            {
                continue;
            }

			ItemIdType ItemId = -1;
			MGStrOp::toU64(csvdata->mData[ItemTemplateRow_ItemId].c_str(), ItemId);
			if (true == mItemList.hasData(ItemId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}
           
			Int ItemType = -1;
            MGStrOp::toI32(csvdata->mData[ItemTemplateRow_ItemType].c_str(), ItemType);

			ItemIdType ItemListId = -1;
            MGStrOp::toU64(csvdata->mData[ItemTemplateRow_ItemListId].c_str(), ItemListId);

			ItemInfo* newItemInfo = mItemList.createOrRetrieve(ItemId, false);
			newItemInfo->ItemId		= ItemId;
			newItemInfo->ItemType	= (ITEM_TYPE)ItemType;
			newItemInfo->ItemListId	= ItemListId;

            newItemInfo->init();

			DYNAMIC_ASSERT( NULL != newItemInfo->mItemUseInfo   ||
							NULL != newItemInfo->mItemEquipInfo ||
							NULL != newItemInfo->mItemOtherInfo ||
							NULL != newItemInfo->mItemMoneyInfo ||
							NULL != newItemInfo->mItemExpInfo   ||
							NULL != newItemInfo->mItemClanInfo);
        }

        return true;
    }
    //-------------------------------------------------------------------------------------------------
    const ItemInfo* ItemTemplate::getItemInfo( ItemIdType tempID )
    {
		return mItemList.getData(tempID);
    }

    //*********************************************************************************************************
    //iteminfo
    ItemInfo::ItemInfo()
        :ItemId(0)
        ,ItemType(ITEM_TYPE_NONE)
        ,ItemListId(0)
        ,mItemUseInfo(NULL)
        ,mItemOtherInfo(NULL)
        ,mItemEquipInfo(NULL)
        ,mItemMoneyInfo(NULL)
		,mItemExpInfo(NULL)
		,mItemClanInfo(NULL)
		,mArtIconResCsv(NULL)
    {

    }
    //----------------------------------------------------------------------------------
    MG::Bool ItemInfo::init()
    {
        switch (ItemType)
        {
		case ITEM_TYPE_EXP:
			{
				mItemExpInfo = ItemExpListCsv::getInstance().getInfoById(ItemListId); 
				DYNAMIC_ASSERT_LOG(mItemExpInfo,"error: mItemExpInfo == NULL !");
			}
			break;
        case ITEM_TYPE_MONEY:
            {
                mItemMoneyInfo = ItemMoneyTemplate::getInstance().getItemMoneyInfo(ItemListId); 
                DYNAMIC_ASSERT_LOG(mItemMoneyInfo,"error: mItemMoneyInfo == NULL !");
				mArtIconResCsv = ArtIconResCsv::getInstance().getIconArtResInfo(mItemMoneyInfo->atrIconId);

            }
            break;
		case ITEM_TYPE_USE_CLAN:
			{
				mItemClanInfo = ItemClanListCsv::getInstance().getInfoById(ItemListId); 
                DYNAMIC_ASSERT_LOG(mItemClanInfo,"error: mItemClanInfo == NULL !");

				mArtIconResCsv = ArtIconResCsv::getInstance().getIconArtResInfo(mItemClanInfo->ArtIconId);

			}
			break;
        case ITEM_TYPE_EQUIP_GENERAL:
            {    
                mItemEquipInfo = ItemEquipTemplate::getInstance().getItemEquipInfo(ItemListId);
				DYNAMIC_ASSERT_LOG(mItemEquipInfo,"error: mItemEquipInfo == NULL !");

				mArtIconResCsv = ArtIconResCsv::getInstance().getIconArtResInfo(mItemEquipInfo->ArtIconId);
            }
            break;
        case ITEM_TYPE_USE_GENERAL:
            {
                mItemUseInfo = ItemUseTemplate::getInstance().getItemUseInfo(ItemListId); 
                DYNAMIC_ASSERT_LOG(mItemUseInfo,"error: mItemUseInfo == NULL !");
				mArtIconResCsv = ArtIconResCsv::getInstance().getIconArtResInfo(mItemUseInfo->ArtIconId);
            }
            break;
        case ITEM_TYPE_OTHER:
            {
                mItemOtherInfo = ItemOtherTemplate::getInstance().getItemOtherInfo(ItemListId);
				DYNAMIC_ASSERT_LOG(mItemOtherInfo,"error: mItemOtherInfo == NULL !");

				mArtIconResCsv = ArtIconResCsv::getInstance().getIconArtResInfo(mItemOtherInfo->ArtIconId);
            }
            break;
        default:
			DYNAMIC_ASSERT_LOG(0,"error : ItemType undefined!");
            return false;
        }

        return true;
    }
    //----------------------------------------------------------------------------------
    const ItemUseInfo* ItemInfo::getItemUseInfo() const
    {
        return mItemUseInfo;
    }
    //----------------------------------------------------------------------------------
    const ItemEquipInfo* ItemInfo::getItemEquipInfo() const
    {
        return mItemEquipInfo;
    }
    //----------------------------------------------------------------------------------
    const ItemOtherInfo* ItemInfo::getItemOtherInfo() const
    {
        return mItemOtherInfo;
    }
    //----------------------------------------------------------------------------------
    const ItemMoneyInfo* ItemInfo::getItemMoneyInfo() const
    {
        return mItemMoneyInfo;
    }

	const ItemExpListCsvInfo* ItemInfo::getItemExpInfo()const
	{
		return mItemExpInfo;
	}

	const ItemClanListCsvInfo* ItemInfo::getItemClanInfo()const
	{
		return mItemClanInfo;
	}

    //----------------------------------------------------------------------------------
    MG::Str16 ItemInfo::getItemBaseItemName() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->Name;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->Name;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->Name;
        else if ( mItemMoneyInfo )
            return mItemMoneyInfo->Name;
		else if (mItemExpInfo)
			return mItemExpInfo->name;
		else if (mItemClanInfo)
			return mItemClanInfo->Name;
        else
            DYNAMIC_ASSERT(0);

        return L"";
    }
    //----------------------------------------------------------------------------------
    MG::Str16 ItemInfo::getItemBaseItemText() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->Text;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->Text;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->Text;
        else if ( mItemMoneyInfo )
            return mItemMoneyInfo->Text;
		else if ( mItemExpInfo )
			return mItemExpInfo->text;
		//else if ( mItemClanInfo )
		//	return mItemClanInfo->text;
        else
            DYNAMIC_ASSERT(0);

        return L"";
    }
    //----------------------------------------------------------------------------------
    void ItemInfo::getItemBaseIconResouce( Str8& resName, Str8& groupName, Str8& itemName ) const
    {
		resName = mArtIconResCsv->ResName;
		groupName = mArtIconResCsv->GroupName;
		itemName = mArtIconResCsv->ItemName;
		return;
#if 0
        if ( mItemUseInfo )
        { 
			resName = mArtIconResCsv->ResName;
			groupName = mArtIconResCsv->GroupName;
			itemName = mArtIconResCsv->ItemName;
        }
        else if ( mItemEquipInfo )
        { 
			
        }
        else if ( mItemOtherInfo )
        { 
			
        }
        else if ( mItemMoneyInfo )
        { 
			
        }
		else if(mItemClanInfo)
		{
#if 0
			if (true == mItemClanInfo->ResouceName.empty()	||
				true == mItemClanInfo->GroupName.empty()		||
				true == mItemClanInfo->ItemName.empty())
			{
				const ArtIconResCsvInfo* tempIconArtResInfo = ArtIconResCsv::getInstance().getIconArtResInfo(mItemClanInfo->ArtIconId);
				DYNAMIC_ASSERT(NULL != tempIconArtResInfo);

				mItemClanInfo->ResouceName = tempIconArtResInfo->ResName;
				mItemClanInfo->GroupName = tempIconArtResInfo->GroupName;
				mItemClanInfo->ItemName = tempIconArtResInfo->ItemName;
			}

			resName		= mItemClanInfo->ResouceName;
			groupName	= mItemClanInfo->GroupName;
			itemName	= mItemClanInfo->ItemName;
#endif
		}
        else
		{
            DYNAMIC_ASSERT(0);
		}
#endif
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemBaseDropMashID() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->ArtMeshId;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->ArtMashId1;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->ArtMeshId;
        else if ( mItemMoneyInfo )
            return mItemMoneyInfo->ArtMeshId;
		else if(mItemExpInfo)
			return 0;
		else if(mItemClanInfo)
			return mItemClanInfo->ArtMeshId;
        else
            DYNAMIC_ASSERT(0);

        return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemBasePrice() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->Price;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->Price;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->Price;
        else if ( mItemMoneyInfo )
            return mItemMoneyInfo->Price;
		else if ( mItemExpInfo )
			return mItemExpInfo->price;
        else
            DYNAMIC_ASSERT(0);

        return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemBaseSellPrice() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->SellPrice;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->SellPrice;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->SellPrice;
		else if ( mItemClanInfo )
			return mItemClanInfo->SellPrice;
        else
            DYNAMIC_ASSERT(0);

        return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemBaseBuyPrice() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->BuyPrice;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->BuyPrice;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->BuyPrice;
		else if ( mItemClanInfo )
			return mItemClanInfo->BuyPrice;
        else
            DYNAMIC_ASSERT(0);

        return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemBaseMaxPileNum() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->MaxPlieNum;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->MaxPileNum;

        return 1;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemBaseScore() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->Score;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->Score;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->Score;
        //else if ( mItemMoneyInfo )
        //    return mItemMoneyInfo->Score;
        else
            DYNAMIC_ASSERT(0);

        return 0;
    }
    //----------------------------------------------------------------------------------
    MG::ITEM_RANK ItemInfo::getItemBaseRank() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->Rank;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->Rank;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->Rank;
        else if ( mItemMoneyInfo )
            return mItemMoneyInfo->Rank;
		else if ( mItemClanInfo )
			return mItemClanInfo->Rank;
        else
            DYNAMIC_ASSERT(0);

        return ITEM_RANK_NONE;
    }
    //----------------------------------------------------------------------------------
    MG::ITEM_BIND_TYPE ItemInfo::getItemBaseBindType() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->BindType;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->BindType;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->BindType;
        else
            DYNAMIC_ASSERT(0);

        return ITEM_BIND_TYPE_NULL;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemBaseDisppearType() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->DisappearType;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->DisappearType;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->DisappearType;
        else
            DYNAMIC_ASSERT(0);

        return ITEM_DISPPEAR_TYPE_NULL;
    }
    //----------------------------------------------------------------------------------

    MG::U32 ItemInfo::getItemBaseForbidType() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->ForbidType;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->ForBidType;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->ForBidType;
		else if (mItemClanInfo)
			return mItemClanInfo->ForbidType;
        else
            DYNAMIC_ASSERT(0);

        return ITEM_FORBID_TYPE_NULL;
    }
    //----------------------------------------------------------------------------------
    MG::ITEM_EXISTENCE_TIME_TYPE ItemInfo::getItemBaseExistenceTimeType() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->ExistanceTimeType;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->ExistenceTimeType;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->ExistenceTimeType;
        else
            DYNAMIC_ASSERT(0);

        return ITEM_EXISTENCE_TIME_TYPE_NULL;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemBaseExistenceTime() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->ExistanceTime;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->ExistenceTime;
        else if ( mItemOtherInfo )
            return mItemOtherInfo->ExistenceTime;
        else
            DYNAMIC_ASSERT(0);

        return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemBaseClanJudgeID() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->CharacterJudgeId;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->ClanJudgeid;
        else if ( mItemOtherInfo )
		{
			DYNAMIC_ASSERT(0);
            return 0;
		}
        else
            DYNAMIC_ASSERT(0);

        return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemBaseCharacterJudgeID() const
    {
        if ( mItemUseInfo )
            return mItemUseInfo->CharacterJudgeId;
        else if ( mItemEquipInfo )
            return mItemEquipInfo->CharacterJudgeid;
        else if ( mItemOtherInfo )
		{
			DYNAMIC_ASSERT(0);
            return 0;
		}
        else
            DYNAMIC_ASSERT(0);

        return 0;
    }
    //----------------------------------------------------------------------------------
    MG::ITEM_OTHER_CLASS ItemInfo::getItemOtherClass() const
    {
        DYNAMIC_ASSERT(mItemOtherInfo);
        return mItemOtherInfo->Class;
    }
    //----------------------------------------------------------------------------------
    MG::ITEM_USE_CLASS ItemInfo::getItemUseClass() const
    {
		if (mItemUseInfo)
		{
			return mItemUseInfo->Class;
		}
		else if(mItemClanInfo)
		{
			return mItemClanInfo->Class;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		return ITEM_USE_CLASS_NONE;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemUseCaseTime() const
    {
		if (mItemUseInfo)
		{
			return mItemUseInfo->CastTime;
		}
		else if(mItemClanInfo)
		{
			return mItemClanInfo->CastTime;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}
		return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemUsePublicTimepieceId() const
    {
		if (mItemUseInfo)
		{
			return mItemUseInfo->PublicTimePieceId;
		}
		else if(mItemClanInfo)
		{
			return mItemClanInfo->PublicTimePieceId;
		}
		
		return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemUsePublicTimepieceDelay() const
    {
		if (mItemUseInfo)
		{
			return mItemUseInfo->PublicTimePieceDelay;
		}
		else if(mItemClanInfo)
		{
			return mItemClanInfo->PublicTimePieceDelay;
		}
	
		return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemUseOwnerTimepieceId() const
    {
		if (mItemUseInfo)
		{
			return mItemUseInfo->OwnerTimePieceId;
		}
		else if(mItemClanInfo)
		{
			return mItemClanInfo->OwnerTimePieceId;
		}
		
		return 0;

    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemUseOwnerTimepieceDelay() const
    {
		if (mItemUseInfo)
		{
			return mItemUseInfo->OwnerTimePieceDelay;
		}
		else if(mItemClanInfo)
		{
			return mItemClanInfo->OwnerTimePieceDelay;
		}
		
		return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemUseResetTimepieceId() const
    {
		if (mItemUseInfo)
		{
			return mItemUseInfo->ResetTimePieceId;
		}
		else if(mItemClanInfo)
		{
			return mItemClanInfo->ResetTimePieceId;
		}
		
		return 0;

    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemUseResetTimepieceGroupId() const
    {
		if (mItemUseInfo)
		{
			 return mItemUseInfo->ResetTimePieceGroupId;
		}
		else if(mItemClanInfo)
		{
			return mItemClanInfo->ResetTimePieceGroupId;
		}
		
		return 0;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemUseGiveQuestId() const
    {
        DYNAMIC_ASSERT(mItemClanInfo);
        return mItemClanInfo->GiveQuestId;
    }
    //----------------------------------------------------------------------------------
    MG::ItemIdType ItemInfo::getItemUseGiveItemGroupId() const
    {
		DYNAMIC_ASSERT(mItemClanInfo);
		return mItemClanInfo->GiveItemGroupId;
    }
    //----------------------------------------------------------------------------------
    
	/*MG::U32 ItemInfo::getItemUseSkillId() const
    {
        DYNAMIC_ASSERT(mItemUseInfo);
        return mItemUseInfo->SkillTemplateID;
    }
	*/
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemUseStateId() const
    {
        DYNAMIC_ASSERT(mItemUseInfo);
        return mItemUseInfo->StateId;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemUseStateNum() const
    {
        DYNAMIC_ASSERT(mItemUseInfo);
        return mItemUseInfo->StateNum;
    }
    //----------------------------------------------------------------------------------
    MG::ITEM_USE_RESTORE_TYPE ItemInfo::getItemUseRestoreType() const
    {
        DYNAMIC_ASSERT(mItemUseInfo);
        return mItemUseInfo->RestoreType;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemUseRestoreParameter1() const
    {
        DYNAMIC_ASSERT(mItemUseInfo);
        return mItemUseInfo->RestoreParameter1;
    }

    //----------------------------------------------------------------------------------
    MG::Str16 ItemInfo::getItemUseScript() const
    {
		DYNAMIC_ASSERT(0);
		return Str16(L"");
    }
    //----------------------------------------------------------------------------------
    MG::ITEM_EQUIP_CLASS ItemInfo::getItemEquitClass() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->Class;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitMaleMash() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->ArtMashId2;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitFemaleMash() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->ArtMashId3;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemEquitRepairPrice() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->RepairPrice;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemEquitMaxUpGrade() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->MaxUpGrade;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemEquitMaxFixNum() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->MaxFixNum;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemEquitMaxEquipDurable() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->MaxEquipDurable;
    }
    //----------------------------------------------------------------------------------
    MG::ITEM_EQUIP_SLOT_TYPE ItemInfo::getItemEquitEquipSlotType() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->EquipSlotType;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitSuitId() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->SuitId;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitAttrAppendId() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->AbilityAppendId1;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitRandAttrAppendId() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->AbilityAppendGroupId1;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitStrenAttrAppendId() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->AbilityAppendId2;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitStrenRandAttrAppendId() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->AbilityAppendGroupId2;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitSkillId() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->SkillTemplateID;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitStateId() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->StateTemplateID;
    }
    //----------------------------------------------------------------------------------
    MG::U64 ItemInfo::getItemEquitStateNum() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->StateTemplateNum;
    }
    //----------------------------------------------------------------------------------
    MG::U32 ItemInfo::getItemEquitWeaponActionId() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->WeaponActionId;
    }
    //----------------------------------------------------------------------------------
    MG::Str16 ItemInfo::getItemEquitScript() const
    {
        DYNAMIC_ASSERT(mItemEquipInfo);
        return mItemEquipInfo->EquipSprit;
    }
    //----------------------------------------------------------------------------------
    //MG::U32 ItemInfo::getItemMoneyBaseHoldNum() const
    //{
    //    DYNAMIC_ASSERT(mItemMoneyInfo);
    //    return mItemMoneyInfo->BaseHoldNum; 
    //}
    ////----------------------------------------------------------------------------------
    //MG::U32 ItemInfo::getItemMoneyAddHoldNum() const
    //{
    //    DYNAMIC_ASSERT(mItemMoneyInfo);
    //    return mItemMoneyInfo->AddHoldNum;
    //}
	//----------------------------------------------------------------------------------
	ITEM_MONEY_CLASS  ItemInfo::getItemMoneyClass()const
	{
		DYNAMIC_ASSERT(mItemMoneyInfo);
		return mItemMoneyInfo->Class;
	}
	//----------------------------------------------------------------------------------
	MG::U32 ItemInfo::getItemUseRestoreParameter2() const
	{
		DYNAMIC_ASSERT(mItemUseInfo);
		return mItemUseInfo->RestoreParameter2;
	}
	//----------------------------------------------------------------------------------
	MG::U32 ItemInfo::getItemUseRestoreParameter3() const
	{
		DYNAMIC_ASSERT(mItemUseInfo);
		return mItemUseInfo->RestoreParameter3;
	}
}