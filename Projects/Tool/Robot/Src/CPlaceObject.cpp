
//*********************************************************************************************

//*********************************************************************************************

#include "stdafx.h"

#include "CPlaceObject.h"
#include "PlaceObjectData.h"

//*********************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------------------
	CPlaceObject::CPlaceObject(PlaceListCsvInfo* placeInfo, DistrictIdType districtId)
		:CRegionObject(MG_NEW PlaceObjectData(placeInfo, districtId))
	{
	}

	//--------------------------------------------------------------------------------------
	CPlaceObject::~CPlaceObject()
	{
	}

	RegionIdType CPlaceObject::getRegionId()
	{
		return getPlaceData()->getPlaceId();
	}

	REGION_OBJ_TYPE CPlaceObject::getRegionType() const
	{
		return ROT_PLACE;
	}

	DistrictIdType CPlaceObject::getDistrictId()
	{
		return -1;
	}

	DistrictRankType CPlaceObject::getDistrictRankType()
	{
		return DRT_MAX;
	}

	//--------------------------------------------------------------------------------------
	PlaceObjectData* CPlaceObject::getPlaceData()
	{
		return (PlaceObjectData*)getData();
	}

	PlaceListCsvInfo* CPlaceObject::getPlaceListCsvInfo()
	{
		return getPlaceData()->getPlaceListCsvInfo();
	}
	//--------------------------------------------------------------------------------------
}