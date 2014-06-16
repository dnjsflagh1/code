

/******************************************************************************/

#include "stdafx.h"
#include "SPveObject.h"


/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SPveObject::SPveObject(InstanceListCsvInfo* instanceInfo)
		:SRegionObjectBase(MG_NEW PveObjectData(instanceInfo))
	{
		DYNAMIC_ASSERT(NULL != instanceInfo);
	}

	//-----------------------------------------------------------------------
	SPveObject::~SPveObject()
	{
	}

	//-----------------------------------------------------------------------
	RegionIdType SPveObject::getRegionId()
	{
		return getListCsvInfo()->instanceId;
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE SPveObject::getRegionType() const
	{
		return ROT_PVE;
	}

	DistrictIdType SPveObject::getDistrictId()
	{
		DYNAMIC_ASSERT(0);
		return -1;
	}

	DistrictRankType SPveObject::getDistrictRankType()
	{
		DYNAMIC_ASSERT(0);
		return DRT_NULL;
	}

	PveObjectData* SPveObject::getPveData()
	{
		return (PveObjectData*)getRegionData();
	}

	InstanceListCsvInfo* SPveObject::getListCsvInfo()
	{
		return getPveData()->getListCsvInfo();
	}

	InstancePVEListCsvInfo* SPveObject::getPveCsvInfo()
	{
		return getPveData()->getPveCsvInfo();
	}
}