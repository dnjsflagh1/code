
/******************************************************************************/

#include "stdafx.h"

#include "CTiroObject.h"


/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	CTiroObject::CTiroObject(InstanceListCsvInfo* instanceInfo)
		:CRegionObject(MG_NEW TiroObjectData(instanceInfo))
	{
		DYNAMIC_ASSERT(NULL != instanceInfo);
	}

	//--------------------------------------------------------------------------------------
	CTiroObject::~CTiroObject()
	{
	}

	//--------------------------------------------------------------------------------------
	RegionIdType CTiroObject::getRegionId()
	{
		return getListCsvInfo()->instanceId;
	}

	//--------------------------------------------------------------------------------------
	REGION_OBJ_TYPE CTiroObject::getRegionType() const
	{
		return ROT_TIRO;
	}

	DistrictIdType CTiroObject::getDistrictId()
	{
		DYNAMIC_ASSERT(0);
		return -1;
	}

	DistrictRankType CTiroObject::getDistrictRankType()
	{
		DYNAMIC_ASSERT(0);
		return DRT_NULL;
	}


	TiroObjectData* CTiroObject::getTiroData()
	{
		return (TiroObjectData*)getData();
	}

	InstanceListCsvInfo* CTiroObject::getListCsvInfo()
	{
		return getTiroData()->getListCsvInfo();
	}

	InstanceTiroListCsvInfo* CTiroObject::getTiroCsvInfo()
	{
		return getTiroData()->getTiroCsvInfo();
	}

	//--------------------------------------------------------------------------------------
}
