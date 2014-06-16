/******************************************************************************/

#include "stdafx.h"
#include "ItemClanListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	ItemClanListCsv::ItemClanListCsv()
	{

	}

	//--------------------------------------------------------------------------
	ItemClanListCsv::~ItemClanListCsv()
	{

	}

	//--------------------------------------------------------------------------
	Bool ItemClanListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == ItemClanListCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			ItemIdType ItemClanId = -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_ItemClanId].c_str(), ItemClanId);
			if (true == mItemClanList.hasData(ItemClanId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int ArtIconId = -1;
			MGStrOp::toI32(csvdata->mData[ItemClanListCsvRow_ArtIconId].c_str(), ArtIconId);

			Int ArtMeshId = -1;
			MGStrOp::toI32(csvdata->mData[ItemClanListCsvRow_ArtMeshId].c_str(), ArtMeshId);

			U64 Price = -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_Price].c_str(), Price);

			U64 BuyPrice = -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_BuyPrice].c_str(), BuyPrice);
			
			U64 SellPrice = -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_SellPrice].c_str(), SellPrice);
			
			U64 MaxPlieNum = -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_MaxPlieNum].c_str(), MaxPlieNum);
			
			U64 Score = -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_Score].c_str(), Score);
			
			Int Rank = -1;
			MGStrOp::toI32(csvdata->mData[ItemClanListCsvRow_Rank].c_str(), Rank);

			Int Class = -1;
			MGStrOp::toI32(csvdata->mData[ItemClanListCsvRow_Class].c_str(), Class);

			Int BindType = -1;
			MGStrOp::toI32(csvdata->mData[ItemClanListCsvRow_BindType].c_str(), BindType);


			U32 DisapprearType = -1;
			MGStrOp::toU32(csvdata->mData[ItemClanListCsvRow_DisapprearType].c_str(), DisapprearType);


			U32 ForbidType = -1;
			MGStrOp::toU32(csvdata->mData[ItemClanListCsvRow_ForbidType].c_str(), ForbidType);

			U64 CastTime = -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_CastTime].c_str(), CastTime);

			U64  ExistanceTimeType= -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_ExistanceTimeType].c_str(), ExistanceTimeType);


			U64  ExistanceTime= -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_ExistanceTime].c_str(), ExistanceTime);

			U32  PublicTimePieceId= -1;
			MGStrOp::toU32(csvdata->mData[ItemClanListCsvRow_PublicTimePieceId].c_str(), PublicTimePieceId);

			U64  PublicTimePieceDelay= -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_PublicTimePieceDelay].c_str(), PublicTimePieceDelay);


			U32  OwnerTimePieceId= -1;
			MGStrOp::toU32(csvdata->mData[ItemClanListCsvRow_OwnerTimePieceId].c_str(), OwnerTimePieceId);

			U64  OwnerTimePieceDelay= -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_OwnerTimePieceDelay].c_str(), OwnerTimePieceDelay);


			U32 ResetTimePieceId = -1;
			MGStrOp::toU32(csvdata->mData[ItemClanListCsvRow_ResetTimePieceId].c_str(), ResetTimePieceId);

			U32 ResetTimePieceGroupId = -1;
			MGStrOp::toU32(csvdata->mData[ItemClanListCsvRow_ResetTimePieceGroupId].c_str(), ResetTimePieceGroupId);


			U32  ClanJudgeId= -1;
			MGStrOp::toU32(csvdata->mData[ItemClanListCsvRow_ClanJudgeId].c_str(), ClanJudgeId);
			
			U32 StateId = -1;
			MGStrOp::toU32(csvdata->mData[ItemClanListCsvRow_StateId].c_str(), StateId);
			
			U64  StateNum = -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_StateNum].c_str(), StateNum);
			
			QuestIdType GiveQuestId = -1;
			MGStrOp::toI32(csvdata->mData[ItemClanListCsvRow_GiveQuestId].c_str(), GiveQuestId);
			
			ItemIdType GiveItemGroupId = -1;
			MGStrOp::toU64(csvdata->mData[ItemClanListCsvRow_GiveItemGroupId].c_str(), GiveItemGroupId);

			ItemClanListCsvInfo* newItemClanInfo = mItemClanList.createOrRetrieve(ItemClanId, false);
			newItemClanInfo->ItemClanId				= ItemClanId;
			newItemClanInfo->Name					= csvdata->mData[ItemClanListCsvRow_Name];
			newItemClanInfo->Text					= csvdata->mData[ItemClanListCsvRow_Text];
			newItemClanInfo->ArtIconId				= ArtIconId;
			newItemClanInfo->ArtMeshId				= ArtMeshId;
			newItemClanInfo->Price					= Price;
			newItemClanInfo->BuyPrice				= BuyPrice;
			newItemClanInfo->SellPrice				= SellPrice;
			newItemClanInfo->MaxPlieNum				= MaxPlieNum;
			newItemClanInfo->Score					= Score;
			newItemClanInfo->Rank					= (ITEM_RANK)Rank;
			newItemClanInfo->Class					= (ITEM_USE_CLASS)Class;
			newItemClanInfo->BindType				= (ITEM_BIND_TYPE)BindType;
			newItemClanInfo->DisappearType			= DisapprearType;
			newItemClanInfo->ForbidType				= ForbidType;
			newItemClanInfo->CastTime				= CastTime*TIME_HUNDRED_MS;
			newItemClanInfo->ExistanceTimeType		= ExistanceTimeType;
			newItemClanInfo->ExistanceTime			= ExistanceTime*TIME_HUNDRED_MS;
			newItemClanInfo->PublicTimePieceId		= PublicTimePieceId;
			newItemClanInfo->PublicTimePieceDelay	= PublicTimePieceDelay*TIME_HUNDRED_MS;
			newItemClanInfo->OwnerTimePieceId		= OwnerTimePieceId;
			newItemClanInfo->OwnerTimePieceDelay	= OwnerTimePieceDelay*TIME_HUNDRED_MS;
			newItemClanInfo->ResetTimePieceId		= ResetTimePieceId;
			newItemClanInfo->ResetTimePieceGroupId	= ResetTimePieceGroupId;
			newItemClanInfo->ClanJudgeId			= ClanJudgeId;
			newItemClanInfo->StateId				= StateId;
			newItemClanInfo->StateNum				= StateNum;
			newItemClanInfo->GiveQuestId			= GiveQuestId;
			newItemClanInfo->GiveItemGroupId		= GiveItemGroupId;


		}

		return true;
	}

	//--------------------------------------------------------------------------
	ItemClanListCsvInfo* ItemClanListCsv::getInfoById(ItemIdType id)
	{
		return mItemClanList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<ItemIdType, ItemClanListCsvInfo*>* ItemClanListCsv::getList()
	{
		return mItemClanList.getDataSet();
	}

}