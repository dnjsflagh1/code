

/******************************************************************************/

#include "stdafx.h"
#include "SPlaceObject.h"
#include "PlaceObjectData.h"
#include "District.h"
#include "PlaceListCsv.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SPlaceObject::SPlaceObject(PlaceListCsvInfo* placeInfo, DistrictIdType districtId)
		:SRegionObjectBase(MG_NEW PlaceObjectData(placeInfo, districtId))
	{
	}

	//-----------------------------------------------------------------------
	SPlaceObject::~SPlaceObject()
	{
	}

	//-----------------------------------------------------------------------
	RegionIdType SPlaceObject::getRegionId()
	{
		return getPlaceData()->getPlaceId();
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE SPlaceObject::getRegionType() const
	{
		return ROT_PLACE;
	}

	DistrictRankType SPlaceObject::getDistrictRankType()
	{
		DistrictListCsvInfo* districtListCsvInfo = getDistrictListCsvInfo();
		DYNAMIC_ASSERT(DRT_ZHOU == districtListCsvInfo->getRank() || 
			DRT_JUN == districtListCsvInfo->getRank() ||
			DRT_XIAN == districtListCsvInfo->getRank());
		return districtListCsvInfo->getRank();
		
	}

	DistrictIdType SPlaceObject::getDistrictId()
	{
		return getDistrictListCsvInfo()->getDistrictId();
	}

	PlaceObjectData* SPlaceObject::getPlaceData()
	{
		return (PlaceObjectData*)getRegionData();
	}

	PlaceListCsvInfo* SPlaceObject::getPlaceListCsvInfo()
	{
		return getPlaceData()->getPlaceListCsvInfo();
	}

	DistrictListCsvInfo* SPlaceObject::getDistrictListCsvInfo()
	{
		return getPlaceData()->getDistrictListCsvInfo();
	}
}