//*****************************************************************************************************************
#include "stdafx.h"
#include "ItemOtherTemplate.h"
#include "ArtIconResCsv.h"
//*****************************************************************************************************************
namespace MG
{
    ItemOtherTemplate::~ItemOtherTemplate()
    {
    }
    //--------------------------------------------------------------------------------------------
    // MG_CN_MODIFY
	MG::Bool ItemOtherTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
    {
        CsvReader csvreader;
		// MG_CN_MODIFY
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }

		DYNAMIC_ASSERT(csvreader.getColumnSize() == ItemOtherCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			ItemIdType ItemOtherId = -1;
			MGStrOp::toU64(csvdata->mData[ItemOtherCsvRow_ItemOtherId].c_str(), ItemOtherId);
			if (true == mItemOtherList.hasData(ItemOtherId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int ArtIconId = -1;
			MGStrOp::toI32(csvdata->mData[ItemOtherCsvRow_ArtIconId].c_str(), ArtIconId);

			Int ArtMeshId = -1;
			MGStrOp::toI32(csvdata->mData[ItemOtherCsvRow_ArtMeshId].c_str(), ArtMeshId);

			U64 Price = -1;
			MGStrOp::toU64(csvdata->mData[ItemOtherCsvRow_Price].c_str(), Price);

			U64 BuyPrice = -1;
			MGStrOp::toU64(csvdata->mData[ItemOtherCsvRow_BuyPrice].c_str(), BuyPrice);

			U64 SellPrice = -1;
			MGStrOp::toU64(csvdata->mData[ItemOtherCsvRow_SellPrice].c_str(), SellPrice);

			U32 MaxPileNum = -1;
			MGStrOp::toU32(csvdata->mData[ItemOtherCsvRow_MaxPileNum].c_str(), MaxPileNum);

			U64 Score = -1;
			MGStrOp::toU64(csvdata->mData[ItemOtherCsvRow_Score].c_str(), Score);

			Int Rank = -1;
			MGStrOp::toI32(csvdata->mData[ItemOtherCsvRow_Rank].c_str(), Rank);

			Int Class = -1;
			MGStrOp::toI32(csvdata->mData[ItemOtherCsvRow_Class].c_str(), Class);

			Int BindType = -1;
			MGStrOp::toI32(csvdata->mData[ItemOtherCsvRow_BindType].c_str(), BindType);

			U32 DisappearType = 0;
			MGStrOp::toU32(csvdata->mData[ItemOtherCsvRow_DisappearType].c_str(), DisappearType);

			U32 ForbidType = 0;
			MGStrOp::toU32(csvdata->mData[ItemOtherCsvRow_ForbidType].c_str(), ForbidType);

			Int  ExistenceTimeType= -1;
			MGStrOp::toI32(csvdata->mData[ItemOtherCsvRow_ExistenceTimeType].c_str(), ExistenceTimeType);

			U64  ExistenceTime= -1;
			MGStrOp::toU64(csvdata->mData[ItemOtherCsvRow_ExistenceTime].c_str(), ExistenceTime);

			SkillIdType SkillId = -1;
			MGStrOp::toU32(csvdata->mData[ItemOtherCsvRow_SkillId].c_str(), SkillId);

			ItemOtherInfo* newItemInfo = mItemOtherList.createOrRetrieve(ItemOtherId, false);
			newItemInfo->ItemOtherId		= ItemOtherId;
			newItemInfo->Name					= csvdata->mData[ItemOtherCsvRow_ItemName];
			newItemInfo->Text					= csvdata->mData[ItemOtherCsvRow_ItemText];
			newItemInfo->ArtIconId				= ArtIconId;
			newItemInfo->ArtMeshId				= ArtMeshId;
			newItemInfo->Price					= Price;
			newItemInfo->BuyPrice				= BuyPrice;
			newItemInfo->SellPrice				= SellPrice;
			newItemInfo->MaxPileNum				= MaxPileNum;
			newItemInfo->Score					= Score;
			newItemInfo->Rank					= (ITEM_RANK)Rank;
			newItemInfo->Class					= (ITEM_OTHER_CLASS)Class;
			newItemInfo->BindType				= (ITEM_BIND_TYPE)BindType;
			newItemInfo->DisappearType			= DisappearType;
			newItemInfo->ForBidType				= ForbidType;
			newItemInfo->ExistenceTimeType		= (ITEM_EXISTENCE_TIME_TYPE)ExistenceTimeType;
			newItemInfo->ExistenceTime			= ExistenceTime*TIME_HUNDRED_MS;
			newItemInfo->SkillId				= SkillId;

        }

        return true;
    }
    //--------------------------------------------------------------------------------------------
    const ItemOtherInfo* ItemOtherTemplate::getItemOtherInfo( ItemIdType tempID )
    {
		return mItemOtherList.getData(tempID);
    }
}