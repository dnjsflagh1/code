

/******************************************************************************/

#include "stdafx.h"
#include "SHomeObject.h"


/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SHomeObject::SHomeObject(InstanceListCsvInfo* instanceInfo)
		:SRegionObjectBase(MG_NEW HomeObjectData(instanceInfo))
	{
		DYNAMIC_ASSERT(NULL != instanceInfo);
	}

	//-----------------------------------------------------------------------
	SHomeObject::~SHomeObject()
	{
	}

	//-----------------------------------------------------------------------
	RegionIdType SHomeObject::getRegionId()
	{
		return getListCsvInfo()->instanceId;
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE SHomeObject::getRegionType() const
	{
		return ROT_HOME;
	}

	DistrictIdType SHomeObject::getDistrictId()
	{
		DYNAMIC_ASSERT(0);
		return -1;
	}

	DistrictRankType SHomeObject::getDistrictRankType()
	{
		DYNAMIC_ASSERT(0);
		return DRT_NULL;
	}

	HomeObjectData* SHomeObject::getHomeData()
	{
		return (HomeObjectData*)getRegionData();
	}

	InstanceListCsvInfo* SHomeObject::getListCsvInfo()
	{
		return getHomeData()->getListCsvInfo();
	}

	InstanceHomeListCsvInfo* SHomeObject::getHomeCsvInfo()
	{
		return getHomeData()->getHomeCsvInfo();
	}
}