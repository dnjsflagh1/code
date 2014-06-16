
/******************************************************************************/

#include "stdafx.h"
#include "SMapDistribution.h"
#include "MapDistributionObjectData.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SMapDistribution::SMapDistribution(MapDistributionCsvInfo* mapDistributionCsvInfo, DistrictIdType districtId)
		:SRegionObjectBase(MG_NEW MapDistributionObjectData(mapDistributionCsvInfo, districtId))
	{
	}

	//-----------------------------------------------------------------------
	SMapDistribution::~SMapDistribution()
	{
	}

	RegionIdType SMapDistribution::getRegionId()
	{
		return getMapDistributionCsvInfo()->mapDistributionId;
	}

	MapDistributionObjectData* SMapDistribution::getMapDistributionData()
	{
		return (MapDistributionObjectData*)getRegionData();
	}

	MapDistributionCsvInfo* SMapDistribution::getMapDistributionCsvInfo()
	{
		return getMapDistributionData()->getMapDistributionCsvInfo();
	}

	DistrictListCsvInfo* SMapDistribution::getDistrictListCsvInfo()
	{
		return getMapDistributionData()->getDistrictListCsvInfo();
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE SMapDistribution::getRegionType() const
	{
		return ROT_MAP_DISTRIBUTION;
	}

	DistrictIdType SMapDistribution::getDistrictId()
	{
		return getDistrictListCsvInfo()->getDistrictId();
	}

	DistrictRankType SMapDistribution::getDistrictRankType()
	{
		DistrictListCsvInfo* districtListCsvInfo = getDistrictListCsvInfo();
		DYNAMIC_ASSERT(DRT_ZHOU == districtListCsvInfo->getRank());
		return DRT_ZHOU;
	}

	MapDistributionType SMapDistribution::getMapDistributionType()
	{
		return getMapDistributionCsvInfo()->mapDistrictType;
	}

	//--------------------------------------------------------------------------------------
}
