//*****************************************************************************************************************
#include "stdafx.h"
#include "ItemUseTemplate.h"
#include "ArtIconResCsv.h"
//*****************************************************************************************************************
namespace MG
{
    ItemUseTemplate::~ItemUseTemplate()
    {
    }
    //-------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
    MG::Bool ItemUseTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
    {
        CsvReader csvreader;
		// MG_CN_MODIFY
        if(!csvreader.create(fileName, packManager))
        {
            return false;
        }


		DYNAMIC_ASSERT(csvreader.getColumnSize() == ItemGeneralUseRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			ItemIdType ItemGeneralUseId = -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_ItemGeneralUseId].c_str(), ItemGeneralUseId);
			if (true == mItemGeneralUseList.hasData(ItemGeneralUseId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int ArtIconId = -1;
			MGStrOp::toI32(csvdata->mData[ItemGeneralUseRow_ArtIconId].c_str(), ArtIconId);

			Int ArtMeshId = -1;
			MGStrOp::toI32(csvdata->mData[ItemGeneralUseRow_ArtMeshId].c_str(), ArtMeshId);

			U64 Price = -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_Price].c_str(), Price);

			U64 BuyPrice = -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_BuyPrice].c_str(), BuyPrice);

			U64 SellPrice = -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_SellPrice].c_str(), SellPrice);

			U64 MaxPlieNum = -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_MaxPlieNum].c_str(), MaxPlieNum);

			U64 Score = -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_Score].c_str(), Score);

			Int Rank = -1;
			MGStrOp::toI32(csvdata->mData[ItemGeneralUseRow_Rank].c_str(), Rank);

			Int Class = -1;
			MGStrOp::toI32(csvdata->mData[ItemGeneralUseRow_Class].c_str(), Class);

			Int BindType = -1;
			MGStrOp::toI32(csvdata->mData[ItemGeneralUseRow_BindType].c_str(), BindType);


			U32 DisapprearType = 0;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_DisapprearType].c_str(), DisapprearType);


			U32 ForbidType = 0;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_ForbidType].c_str(), ForbidType);

			U64 CastTime = -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_CastTime].c_str(), CastTime);

			Int  ExistanceTimeType= -1;
			MGStrOp::toI32(csvdata->mData[ItemGeneralUseRow_ExistanceTimeType].c_str(), ExistanceTimeType);


			U64  ExistanceTime= -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_ExistanceTime].c_str(), ExistanceTime);

			U32  PublicTimePieceId= -1;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_PublicTimePieceId].c_str(), PublicTimePieceId);

			U64  PublicTimePieceDelay= -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_PublicTimePieceDelay].c_str(), PublicTimePieceDelay);


			U32  OwnerTimePieceId= -1;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_OwnerTimePieceId].c_str(), OwnerTimePieceId);

			U64  OwnerTimePieceDelay= -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_OwnerTimePieceDelay].c_str(), OwnerTimePieceDelay);


			U32 ResetTimePieceId = -1;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_ResetTimePieceId].c_str(), ResetTimePieceId);

			U32 ResetTimePieceGroupId = -1;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_ResetTimePieceGroupId].c_str(), ResetTimePieceGroupId);


			U32  CharacterJudgeId= -1;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_CharacterJudgeId].c_str(), CharacterJudgeId);

			U32 StateId = -1;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_StateId].c_str(), StateId);

			U64  StateNum = -1;
			MGStrOp::toU64(csvdata->mData[ItemGeneralUseRow_StateNum].c_str(), StateNum);

			Int RestoreType = -1;
			MGStrOp::toI32(csvdata->mData[ItemGeneralUseRow_RestoreType].c_str(), RestoreType);

			U32 RestoreParameter1 = -1;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_RestoreParameter1].c_str(), RestoreParameter1);

			U32 RestoreParameter2 = -1;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_RestoreParameter2].c_str(), RestoreParameter2);

			U32 RestoreParameter3 = -1;
			MGStrOp::toU32(csvdata->mData[ItemGeneralUseRow_RestoreParameter3].c_str(), RestoreParameter3);

			ItemUseInfo* newItemInfo = mItemGeneralUseList.createOrRetrieve(ItemGeneralUseId, false);
			newItemInfo->ItemGeneralUseId		= ItemGeneralUseId;
			newItemInfo->Name					= csvdata->mData[ItemGeneralUseRow_Name];
			newItemInfo->Text					= csvdata->mData[ItemGeneralUseRow_Text];
			newItemInfo->ArtIconId				= ArtIconId;
			newItemInfo->ArtMeshId				= ArtMeshId;
			newItemInfo->Price					= Price;
			newItemInfo->BuyPrice				= BuyPrice;
			newItemInfo->SellPrice				= SellPrice;
			newItemInfo->MaxPlieNum				= MaxPlieNum;
			newItemInfo->Score					= Score;
			newItemInfo->Rank					= (ITEM_RANK)Rank;
			newItemInfo->Class					= (ITEM_USE_CLASS)Class;
			newItemInfo->BindType				= (ITEM_BIND_TYPE)BindType;
			newItemInfo->DisappearType			= DisapprearType;
			newItemInfo->ForbidType				= ForbidType;
			newItemInfo->CastTime				= CastTime*TIME_HUNDRED_MS;
			newItemInfo->ExistanceTimeType		= (ITEM_EXISTENCE_TIME_TYPE)ExistanceTimeType;
			newItemInfo->ExistanceTime			= ExistanceTime*TIME_HUNDRED_MS;
			newItemInfo->PublicTimePieceId		= PublicTimePieceId;
			newItemInfo->PublicTimePieceDelay	= PublicTimePieceDelay*TIME_HUNDRED_MS;
			newItemInfo->OwnerTimePieceId		= OwnerTimePieceId;
			newItemInfo->OwnerTimePieceDelay	= OwnerTimePieceDelay*TIME_HUNDRED_MS;
			newItemInfo->ResetTimePieceId		= ResetTimePieceId;
			newItemInfo->ResetTimePieceGroupId	= ResetTimePieceGroupId;
			newItemInfo->CharacterJudgeId		= CharacterJudgeId;
			newItemInfo->StateId				= StateId;
			newItemInfo->StateNum				= StateNum;
			newItemInfo->RestoreType			= (ITEM_USE_RESTORE_TYPE)RestoreType;
			newItemInfo->RestoreParameter1		= RestoreParameter1;
			newItemInfo->RestoreParameter2		= RestoreParameter2;
			newItemInfo->RestoreParameter3		= RestoreParameter3;
            
			//judge
			if (PublicTimePieceId == OwnerTimePieceId)
            {
				DYNAMIC_ASSERT_LOG(false,"error:PublicTimePieceId == OwnerTimePieceId");
            }
		}

        return true;
    }
    //-------------------------------------------------------------------------------------------
    const ItemUseInfo* ItemUseTemplate::getItemUseInfo( ItemIdType tempID )
    {
		return mItemGeneralUseList.getData(tempID);
    }
    ////-------------------------------------------------------------------------------------------
    //MG::Bool ItemUseTemplate::getItemUseInfo( U32 tempID, const ItemUseInfo*& info )
    //{
    //    std::map<U64, ItemUseInfo*>::iterator iter = mItemGeneralUseList.find(tempID);
    //    if ( mItemGeneralUseList.end() != iter )
    //    {
    //        info = iter->second;
    //        return true;
    //    }

    //    return false;
    //}
}