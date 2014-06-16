/******************************************************************************/

#include "stdafx.h"
#include "MapDistributionCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	MapDistributionCsv::MapDistributionCsv()
	{

	}

	//--------------------------------------------------------------------------
	MapDistributionCsv::~MapDistributionCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	bool MapDistributionCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			I32 openType = -1;
			MGStrOp::toI32(csvdata->mData[OpenType].c_str(), openType);
			DYNAMIC_ASSERT((MapDistributionOpenType)openType > MDOT_Null && (MapDistributionOpenType)openType < MDOT_Max);

			if (MDOT_Open != (MapDistributionOpenType)openType)
			{
				continue;
			}

			MapDistributionIdType mapDistributionId;
			MGStrOp::toU32(csvdata->mData[MapDistributionId].c_str(), mapDistributionId);

			if (true == mMapDistributionCsvList.hasData(mapDistributionId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}


			I32 type = -1;
			MGStrOp::toI32(csvdata->mData[mapDistributionType].c_str(), type);
			DYNAMIC_ASSERT((MapDistributionType)type > MDT_Null && (MapDistributionType)type < MDT_Max);

			I32 mapId = -1;
			MGStrOp::toI32(csvdata->mData[MapId].c_str(), mapId);



			MapDistributionCsvInfo* newMapDistribution = mMapDistributionCsvList.createOrRetrieve(mapDistributionId, false);
			newMapDistribution->mapDistributionId	= mapDistributionId;
			//newMapDistribution->listName			= csvdata->mData[ListName];
			newMapDistribution->name				= csvdata->mData[Name];
			newMapDistribution->text				= csvdata->mData[Text];
			newMapDistribution->openType			= (MapDistributionOpenType)openType;
			newMapDistribution->mapDistrictType		= (MapDistributionType)type;
			newMapDistribution->mapId				= mapId;

		}
		return true;
	}

	std::map<MapDistributionIdType, MapDistributionCsvInfo*>* MapDistributionCsv::getList()
	{
		return mMapDistributionCsvList.getDataSet();
	}
	//--------------------------------------------------------------------------

}