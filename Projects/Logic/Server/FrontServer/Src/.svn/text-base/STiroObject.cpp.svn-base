

/******************************************************************************/

#include "stdafx.h"
#include "STiroObject.h"


/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	STiroObject::STiroObject(InstanceListCsvInfo* instanceInfo)
		:SRegionObjectBase(MG_NEW TiroObjectData(instanceInfo))
	{
		DYNAMIC_ASSERT(NULL != instanceInfo);
	}

	//-----------------------------------------------------------------------
	STiroObject::~STiroObject()
	{
	}

	//-----------------------------------------------------------------------
	RegionIdType STiroObject::getRegionId()
	{
		return getListCsvInfo()->instanceId;
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE STiroObject::getRegionType() const
	{
		return ROT_TIRO;
	}

	DistrictIdType STiroObject::getDistrictId()
	{
		DYNAMIC_ASSERT(0);
		return -1;
	}

	DistrictRankType STiroObject::getDistrictRankType()
	{
		DYNAMIC_ASSERT(0);
		return DRT_NULL;
	}

	TiroObjectData* STiroObject::getTiroData()
	{
		return (TiroObjectData*)getRegionData();
	}

	InstanceListCsvInfo* STiroObject::getListCsvInfo()
	{
		return getTiroData()->getListCsvInfo();
	}

	InstanceTiroListCsvInfo* STiroObject::getTiroCsvInfo()
	{
		return getTiroData()->getTiroCsvInfo();
	}
}