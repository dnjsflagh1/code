

/******************************************************************************/

#include "stdafx.h"
#include "SPlaceObject.h"
#include "PlaceObjectData.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SPlaceObject::SPlaceObject(PlaceListCsvInfo* placeInfo, MapListCsvInfo* mapCsvInfo)
	{
		//mPlaceData = MG_NEW PlaceObjectData(mapCsvInfo);
	}

	//-----------------------------------------------------------------------
	SPlaceObject::~SPlaceObject()
	{
		MG_SAFE_DELETE(mPlaceData);
	}

	//-----------------------------------------------------------------------
	RegionIdType SPlaceObject::getRegionId()
	{
		return mPlaceData->getMapId();
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE SPlaceObject::getRegionType() const
	{
		return ROT_PLACE;
	}
}