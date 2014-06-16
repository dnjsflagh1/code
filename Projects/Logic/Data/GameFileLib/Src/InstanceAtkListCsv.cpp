/******************************************************************************/

#include "stdafx.h"
#include "InstanceAtkListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	InstanceAtkListCsv::InstanceAtkListCsv()
	{

	}

	//--------------------------------------------------------------------------
	InstanceAtkListCsv::~InstanceAtkListCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool InstanceAtkListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == InstanceAtkListCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			InstanceIdType instanceAtkId;
			MGStrOp::toU32(csvdata->mData[InstanceAtkListCsvRow_InstanceAtkId].c_str(), instanceAtkId);
			if (true == mInstanceAtkList.hasData(instanceAtkId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int openType = 0;
			MGStrOp::toI32(csvdata->mData[InstanceAtkListCsvRow_OpenType].c_str(), openType);

			U64 openTimeStart = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_OpenTimeStart].c_str(), openTimeStart);

			U64 openTimeEnd = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_OpenTimeEnd].c_str(), openTimeEnd);

			Int timepieceID = 0;
			MGStrOp::toI32(csvdata->mData[InstanceAtkListCsvRow_TimepieceID].c_str(), timepieceID);

			Int overdueType = 0;
			MGStrOp::toI32(csvdata->mData[InstanceAtkListCsvRow_OverdueType].c_str(), overdueType);

			U64 overdueTime = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_OverdueTime].c_str(), overdueTime);

			U64 campListId1 = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_CampListId1].c_str(), campListId1);

			U64 campListId2 = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_CampListId2].c_str(), campListId2);

			U64 campListId3 = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_CampListId3].c_str(), campListId3);

			U64 campListId4 = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_CampListId4].c_str(), campListId4);

			//U64 destroyTime = 0;
			//MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_DestroyTime].c_str(), destroyTime);

			//U64 finishTime = 0;
			//MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_FinishTime].c_str(), finishTime);

			Int finishQuest = 0;
			MGStrOp::toI32(csvdata->mData[InstanceAtkListCsvRow_FinishQuest].c_str(), finishQuest);

			U64 finishCharacter = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_FinishCharacter].c_str(), finishCharacter);

			U64 finishArmy = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_FinishArmy].c_str(), finishArmy);

			U64 finishBuilding = 0;
			MGStrOp::toU64(csvdata->mData[InstanceAtkListCsvRow_FinishBuilding].c_str(), finishBuilding);

			Int itemGroupId1 = 0;
			MGStrOp::toI32(csvdata->mData[InstanceAtkListCsvRow_ItemGroupId1].c_str(), itemGroupId1);

			Int itemGroupId2 = 0;
			MGStrOp::toI32(csvdata->mData[InstanceAtkListCsvRow_ItemGroupId2].c_str(), itemGroupId2);

			Int itemGroupId3 = 0;
			MGStrOp::toI32(csvdata->mData[InstanceAtkListCsvRow_ItemGroupId3].c_str(), itemGroupId3);

			U32 intanceTimeId = 0;
			MGStrOp::toU32(csvdata->mData[InstanceAtkListCsvRow_IntanceTimeId].c_str(), intanceTimeId);

			InstanceAtkListCsvInfo* newInstanceAtkInfo	= mInstanceAtkList.createOrRetrieve(instanceAtkId, false);
			newInstanceAtkInfo->instanceAtkId	= instanceAtkId;
			newInstanceAtkInfo->openType		= (AtkOpenType)openType;
			newInstanceAtkInfo->openTimeStart	= openTimeStart;
			newInstanceAtkInfo->openTimeEnd		= openTimeEnd;
			newInstanceAtkInfo->timepieceID		= timepieceID;
			newInstanceAtkInfo->overdueType		= (AtkOverdueType)overdueType;
			newInstanceAtkInfo->overdueTime		= overdueTime;
			newInstanceAtkInfo->campListId1		= campListId1;
			newInstanceAtkInfo->campListId2		= campListId2;
			newInstanceAtkInfo->campListId3		= campListId3;
			newInstanceAtkInfo->campListId4		= campListId4;
			newInstanceAtkInfo->finishQuest		= finishQuest;
			newInstanceAtkInfo->finishCharacter	= finishCharacter;
			newInstanceAtkInfo->finishArmy		= finishArmy;
			newInstanceAtkInfo->finishBuilding	= finishBuilding;
			newInstanceAtkInfo->finishScript	= csvdata->mData[InstanceAtkListCsvRow_FinishScript];
			newInstanceAtkInfo->itemGroupId1	= itemGroupId1;
			newInstanceAtkInfo->itemGroupId2	= itemGroupId2;
			newInstanceAtkInfo->itemGroupId3	= itemGroupId3;
			newInstanceAtkInfo->rewardScript	= csvdata->mData[InstanceAtkListCsvRow_RewardScript];
			newInstanceAtkInfo->intanceTimeId	= intanceTimeId;
		}

		return true;
	}

	//--------------------------------------------------------------------------
	InstanceAtkListCsvInfo* InstanceAtkListCsv::getInfoById(InstanceIdType id)
	{
		return mInstanceAtkList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<InstanceIdType, InstanceAtkListCsvInfo*>* InstanceAtkListCsv::getList()
	{
		return mInstanceAtkList.getDataSet();
	}
}