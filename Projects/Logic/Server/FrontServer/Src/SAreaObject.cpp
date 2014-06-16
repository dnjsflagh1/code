
/******************************************************************************/

#include "stdafx.h"
#include "SAreaObject.h"
#include "AreaObjectData.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SAreaObject::SAreaObject(MapListCsvInfo* mapCsvInfo)
		:SRegionObjectBase(MG_NEW AreaObjectData(mapCsvInfo))
	{
	}

	//-----------------------------------------------------------------------
	SAreaObject::~SAreaObject()
	{
	}

	//-----------------------------------------------------------------------
	RegionIdType SAreaObject::getRegionId()
	{
		DYNAMIC_ASSERT(0);
		return -1;
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE SAreaObject::getRegionType() const
	{
		return ROT_UNKNOWN;
	}

	DistrictIdType SAreaObject::getDistrictId()
	{
		DYNAMIC_ASSERT(0);
		return -1;
	}

	//-----------------------------------------------------------------------
	DistrictRankType SAreaObject::getDistrictRankType()
	{
		DYNAMIC_ASSERT(0);
		return DRT_NULL;
	}
}