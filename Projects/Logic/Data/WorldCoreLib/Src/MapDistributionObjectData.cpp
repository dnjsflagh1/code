/******************************************************************************/

#include "stdafx.h"
#include "MapDistributionObjectData.h"
#include "District.h"
#include "VassalCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	MapDistributionObjectData::MapDistributionObjectData(MapDistributionCsvInfo* mapDistributionCsvInfo, const DistrictIdType districtId)
		:mMapDistributionCsvInfo(mapDistributionCsvInfo)
		,mDistrictListCsvInfo(NULL)
	{
		DYNAMIC_ASSERT(NULL != mapDistributionCsvInfo);
		setMapListCsvInfoByMapId(mapDistributionCsvInfo->mapId);


		mDistrictListCsvInfo = District::getInstance().getDistrictInfo(districtId);
		DYNAMIC_ASSERT(NULL != mDistrictListCsvInfo);
	}

	//--------------------------------------------------------------------------------------
	MapDistributionObjectData::~MapDistributionObjectData()
	{
	}

	MapDistributionCsvInfo* MapDistributionObjectData::getMapDistributionCsvInfo()
	{
		return mMapDistributionCsvInfo;
	}

	DistrictListCsvInfo* MapDistributionObjectData::getDistrictListCsvInfo()
	{
		return mDistrictListCsvInfo;
	}
}