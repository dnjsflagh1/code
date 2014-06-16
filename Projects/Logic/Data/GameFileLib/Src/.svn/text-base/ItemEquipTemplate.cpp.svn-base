//*****************************************************************************************************************
#include "stdafx.h"
#include "ItemEquipTemplate.h"
#include "ArtIconResCsv.h"
//*****************************************************************************************************************
namespace MG
{
    ItemEquipTemplate::~ItemEquipTemplate()
    {
    }
    //--------------------------------------------------------------------------------------------------

    MG::Bool ItemEquipTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/)
    {
        CsvReader csvreader;
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

        const ArtIconResCsvInfo* tempIconArtResInfo = NULL;
        U32 tempIconId = 0;
        CsvData* csvdata = NULL;
        Int RowCount = csvreader.count();

		DYNAMIC_ASSERT(csvreader.getColumnSize() == ItemEquipCsvRow_Max);

        for(int i = 0; i < RowCount; ++i)
        {
            csvdata = csvreader.findValue(i);
            if(!csvdata)
            {
                continue;
            }

			ItemIdType ItemEquipId = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_ItemEquipId].c_str(), ItemEquipId);
			if (true == mItemEquipList.hasData(ItemEquipId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

				
               
               
           
                  
                  
             
         
         
           

			Int  ArtIconId= -1;
			MGStrOp::toI32(csvdata->mData[ItemEquipCsvRow_ArtIconId].c_str(), ArtIconId);

			U32  ArtMashId1= -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_ArtMashId1].c_str(), ArtMashId1);

			U32 ArtMashId2 = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_ArtMashId2].c_str(), ArtMashId2);

			U32 ArtMashId3 = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_ArtMashId3].c_str(), ArtMashId3);


			U64 Price = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_Price].c_str(), Price);

			U64 BuyPrice = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_BuyPrice].c_str(), BuyPrice);

			U64 SellPrice = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_SellPrice].c_str(), SellPrice);

			U64 RepairPrice = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_RepairPrice].c_str(), RepairPrice);

			U64 MaxUpGrade = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_MaxUpGrade].c_str(), MaxUpGrade);

			U64 MaxFixNum = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_MaxFixNum].c_str(), MaxFixNum);

			U64 MaxEquipDurable = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_MaxEquipDurable].c_str(), MaxEquipDurable);

			U64 Score = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_Score].c_str(), Score);

			Int Rank = -1;
			MGStrOp::toI32(csvdata->mData[ItemEquipCsvRow_Rank].c_str(), Rank);

			Int Class = -1;
			MGStrOp::toI32(csvdata->mData[ItemEquipCsvRow_Class].c_str(), Class);

			Int EquipSlotType = -1;
			MGStrOp::toI32(csvdata->mData[ItemEquipCsvRow_EquipSlotType].c_str(), EquipSlotType);

			U32 SuitId = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_SuitId].c_str(), SuitId);

			Int BindType = -1;
			MGStrOp::toI32(csvdata->mData[ItemEquipCsvRow_BindType].c_str(), BindType);

			U32 DisappearType = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_DisappearType].c_str(), DisappearType);

			U32 ForBidType  = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_ForBidType].c_str(), ForBidType);

			Int ExistenceTimeType = -1;
			MGStrOp::toI32(csvdata->mData[ItemEquipCsvRow_ExistenceTimeType].c_str(), ExistenceTimeType);
			
			U32 ExistenceTime = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_ExistenceTime].c_str(), ExistenceTime);

			U32 ClanJudgeid = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_ClanJudgeid].c_str(), ClanJudgeid);

			U32 CharacterJudgeid = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_CharacterJudgeid].c_str(), CharacterJudgeid);

			U32 AbilityAppendId1 = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_AbilityAppendId1].c_str(), AbilityAppendId1);

			U32 AbilityAppendGroupId1 = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_AbilityAppendGroupId1].c_str(), AbilityAppendGroupId1);

			U32 AbilityAppendId2 = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_AbilityAppendId2].c_str(), AbilityAppendId2);

			U32 AbilityAppendGroupId2 = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_AbilityAppendGroupId2].c_str(), AbilityAppendGroupId2);

			U32 SkillTemplateID = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_SkillTemplateID].c_str(), SkillTemplateID);

			U32 StateTemplateID = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_StateTemplateID].c_str(), StateTemplateID);

			U64 StateTemplateNum = -1;
			MGStrOp::toU64(csvdata->mData[ItemEquipCsvRow_StateTemplateNum].c_str(), StateTemplateNum);

			U32 WeaponActionId  = -1;
			MGStrOp::toU32(csvdata->mData[ItemEquipCsvRow_WeaponActionId].c_str(), WeaponActionId);


			ItemEquipInfo* newItemEquipInfo = mItemEquipList.createOrRetrieve(ItemEquipId, false);
			
			newItemEquipInfo->ItemEquipId			= ItemEquipId;
			newItemEquipInfo->Name					= csvdata->mData[ItemEquipCsvRow_Name];
			newItemEquipInfo->Text					= csvdata->mData[ItemEquipCsvRow_Text];
			newItemEquipInfo->ArtIconId				= ArtIconId;
			newItemEquipInfo->ArtMashId1			= ArtMashId1;
			newItemEquipInfo->ArtMashId2			= ArtMashId2;
			newItemEquipInfo->ArtMashId3			= ArtMashId3;
			newItemEquipInfo->Price					= Price;
			newItemEquipInfo->BuyPrice				= BuyPrice;
			newItemEquipInfo->SellPrice				= SellPrice;
			newItemEquipInfo->RepairPrice			= RepairPrice;
			newItemEquipInfo->MaxUpGrade			= MaxUpGrade;
			newItemEquipInfo->MaxFixNum				= MaxFixNum;
			newItemEquipInfo->MaxEquipDurable		= MaxEquipDurable;
			newItemEquipInfo->Score					= Score;
			newItemEquipInfo->Rank					= (ITEM_RANK)Rank;
			newItemEquipInfo->Class					= (ITEM_EQUIP_CLASS)Class;
			newItemEquipInfo->EquipSlotType			= (ITEM_EQUIP_SLOT_TYPE)EquipSlotType;
			newItemEquipInfo->SuitId				= SuitId;
			newItemEquipInfo->BindType				= (ITEM_BIND_TYPE)BindType;
			newItemEquipInfo->DisappearType			= DisappearType;
			newItemEquipInfo->ForBidType			= ForBidType;
			newItemEquipInfo->ExistenceTimeType		= (ITEM_EXISTENCE_TIME_TYPE)ExistenceTimeType;
			newItemEquipInfo->ExistenceTime			= ExistenceTime*TIME_HUNDRED_MS;
			newItemEquipInfo->ClanJudgeid			= ClanJudgeid;
			newItemEquipInfo->CharacterJudgeid		= CharacterJudgeid;
			newItemEquipInfo->AbilityAppendId1		= AbilityAppendId1;
			newItemEquipInfo->AbilityAppendGroupId1	= AbilityAppendGroupId1;
			newItemEquipInfo->AbilityAppendId2		= AbilityAppendId2;
			newItemEquipInfo->AbilityAppendGroupId2	= AbilityAppendGroupId2;
			newItemEquipInfo->SkillTemplateID		= SkillTemplateID;
			newItemEquipInfo->StateTemplateID		= StateTemplateID;
			newItemEquipInfo->StateTemplateNum		= StateTemplateNum;
			newItemEquipInfo->WeaponActionId		= WeaponActionId;
			newItemEquipInfo->EquipSprit			= csvdata->mData[ItemEquipCsvRow_EquipSprit];
        }

        return true;       
    }
    //--------------------------------------------------------------------------------------------------
    const ItemEquipInfo* ItemEquipTemplate::getItemEquipInfo( ItemIdType tempID )
    {
		return mItemEquipList.getData(tempID);
    }

}