
/******************************************************************************/

#include "stdafx.h"
#include "CHomeObject.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	CHomeObject::CHomeObject(InstanceListCsvInfo* instanceInfo)
		:CRegionObject(MG_NEW HomeObjectData(instanceInfo))
	{
		DYNAMIC_ASSERT(NULL != instanceInfo);
	}

	//--------------------------------------------------------------------------------------
	CHomeObject::~CHomeObject()
	{
	}

	//--------------------------------------------------------------------------------------
	RegionIdType CHomeObject::getRegionId()
	{
		return getListCsvInfo()->instanceId;
	}

	//--------------------------------------------------------------------------------------
	REGION_OBJ_TYPE CHomeObject::getRegionType() const
	{
		return ROT_HOME;
	}

	DistrictIdType CHomeObject::getDistrictId()
	{
		DYNAMIC_ASSERT(0);
		return -1;
	}

	DistrictRankType CHomeObject::getDistrictRankType()
	{
		DYNAMIC_ASSERT(0);
		return DRT_NULL;
	}


	HomeObjectData* CHomeObject::getHomeData()
	{
		return (HomeObjectData*)getData();
	}

	InstanceListCsvInfo* CHomeObject::getListCsvInfo()
	{
		return getHomeData()->getListCsvInfo();
	}

	InstanceHomeListCsvInfo* CHomeObject::getHomeCsvInfo()
	{
		return getHomeData()->getHomeCsvInfo();
	}

	//--------------------------------------------------------------------------------------
}
