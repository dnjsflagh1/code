/******************************************************************************/

#include "stdafx.h"
#include "InstanceHomeListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	InstanceHomeListCsv::InstanceHomeListCsv()
	{

	}

	//--------------------------------------------------------------------------
	InstanceHomeListCsv::~InstanceHomeListCsv()
	{

	}

	//--------------------------------------------------------------------------
	Bool InstanceHomeListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager)
	{
		CsvReader csvreader;

		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == InstanceHomeRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			InstanceIdType instanceHomeId;
			MGStrOp::toU32(csvdata->mData[InstanceHomeRow_InstanceHomeId].c_str(), instanceHomeId);
			if (true == mInstanceHomeList.hasData(instanceHomeId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int artIconResId = 0;
			MGStrOp::toI32(csvdata->mData[InstanceHomeRow_ArtIconResId].c_str(), artIconResId);
			Int  needItemId = 0;
			MGStrOp::toI32(csvdata->mData[InstanceHomeRow_NeedItemId].c_str(), needItemId);
			Int  mapListId = 0;
			MGStrOp::toI32(csvdata->mData[InstanceHomeRow_MapListId].c_str(), mapListId);
			Int maxBuildLv = 0;
			MGStrOp::toI32(csvdata->mData[InstanceHomeRow_MaxBuildLv].c_str(), maxBuildLv);
			Int maxBuildNum = 0;
			MGStrOp::toI32(csvdata->mData[InstanceHomeRow_MaxBuildNum].c_str(), maxBuildNum);
			Int maxNpcNum = 0;
			MGStrOp::toI32(csvdata->mData[InstanceHomeRow_MaxNpcNum].c_str(), maxNpcNum);
			Int maxObjectNum = 0;
			MGStrOp::toI32(csvdata->mData[InstanceHomeRow_MaxObjectNum].c_str(), maxObjectNum);
			Int maxUsageTime = 0;
			MGStrOp::toI32(csvdata->mData[InstanceHomeRow_MaxUsageTime].c_str(), maxUsageTime);

			InstanceHomeListCsvInfo* newInstanceHomeInfo = mInstanceHomeList.createOrRetrieve(instanceHomeId, false);
			newInstanceHomeInfo->instanceHomeId		= instanceHomeId;
			newInstanceHomeInfo->name				= csvdata->mData[InstanceHomeRow_Name];
			newInstanceHomeInfo->text				= csvdata->mData[InstanceHomeRow_Text];
			newInstanceHomeInfo->artIconResId		= artIconResId;
			newInstanceHomeInfo->needItemId			= needItemId;
			newInstanceHomeInfo->mapListId			= mapListId;
			newInstanceHomeInfo->maxBuildLv			= maxBuildLv;
			newInstanceHomeInfo->maxBuildNum		= maxBuildNum;
			newInstanceHomeInfo->maxNpcNum			= maxNpcNum;
			newInstanceHomeInfo->maxObjectNum		= maxObjectNum;
			newInstanceHomeInfo->maxUsageTime		= maxUsageTime;
		}

		return true;
	}

	//--------------------------------------------------------------------------
	InstanceHomeListCsvInfo* InstanceHomeListCsv::getInfoById(InstanceIdType id)
	{
		return mInstanceHomeList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<InstanceIdType, InstanceHomeListCsvInfo*>* InstanceHomeListCsv::getList()
	{
		return mInstanceHomeList.getDataSet();
	}
}