
/******************************************************************************/

#include "stdafx.h"
#include "CMapDistribution.h"
#include "MapDistributionObjectData.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	CMapDistribution::CMapDistribution(MapDistributionCsvInfo* mapDistributionCsvInfo, DistrictIdType districtId)
		:CRegionObject(MG_NEW MapDistributionObjectData(mapDistributionCsvInfo, districtId))
	{
	}

	//-----------------------------------------------------------------------
	CMapDistribution::~CMapDistribution()
	{
	}

	RegionIdType CMapDistribution::getRegionId()
	{
		return getMapDistributionCsvInfo()->mapDistributionId;
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE CMapDistribution::getRegionType() const
	{
		return ROT_MAP_DISTRIBUTION;
	}

	DistrictIdType CMapDistribution::getDistrictId()
	{
		return getDistrictListCsvInfo()->getDistrictId();
	}

	DistrictRankType CMapDistribution::getDistrictRankType()
	{
		DistrictListCsvInfo* districtListCsvInfo = getDistrictListCsvInfo();
		DYNAMIC_ASSERT(DRT_ZHOU == districtListCsvInfo->getRank());
		return DRT_ZHOU;
	}

	MapDistributionObjectData* CMapDistribution::getMapDistributionData()
	{
		return (MapDistributionObjectData*)getData();
	}

	MapDistributionCsvInfo* CMapDistribution::getMapDistributionCsvInfo()
	{
		return getMapDistributionData()->getMapDistributionCsvInfo();
	}

	DistrictListCsvInfo* CMapDistribution::getDistrictListCsvInfo()
	{
		return getMapDistributionData()->getDistrictListCsvInfo();
	}

	MapDistributionType CMapDistribution::getMapDistributionType()
	{
		return getMapDistributionCsvInfo()->mapDistrictType;
	}
	//--------------------------------------------------------------------------------------
}
