
/******************************************************************************/

#include "stdafx.h"

#include "CPveObject.h"


/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	CPveObject::CPveObject(InstanceListCsvInfo* instanceInfo)
		:CRegionObject(MG_NEW PveObjectData(instanceInfo))
	{
		DYNAMIC_ASSERT(NULL != instanceInfo);
	}

	//--------------------------------------------------------------------------------------
	CPveObject::~CPveObject()
	{
	}

	//--------------------------------------------------------------------------------------
	RegionIdType CPveObject::getRegionId()
	{
		return getListCsvInfo()->instanceId;
	}

	//--------------------------------------------------------------------------------------
	REGION_OBJ_TYPE CPveObject::getRegionType() const
	{
		return ROT_PVE;
	}

	DistrictIdType CPveObject::getDistrictId()
	{
		DYNAMIC_ASSERT(0);
		return -1;
	}

	DistrictRankType CPveObject::getDistrictRankType()
	{
		DYNAMIC_ASSERT(0);
		return DRT_NULL;
	}


	PveObjectData* CPveObject::getPveData()
	{
		return (PveObjectData*)getData();
	}

	InstanceListCsvInfo* CPveObject::getListCsvInfo()
	{
		return getPveData()->getListCsvInfo();
	}

	InstancePVEListCsvInfo* CPveObject::getPveCsvInfo()
	{
		return getPveData()->getPveCsvInfo();
	}

	//--------------------------------------------------------------------------------------
}
