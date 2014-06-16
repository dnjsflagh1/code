
/******************************************************************************/

#include "stdafx.h"
#include "SPlaceMapManager.h"
#include "SPlaceMapObject.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SPlaceMapManager::SPlaceMapManager()
	{
	}

	//-----------------------------------------------------------------------------
	SPlaceMapManager::~SPlaceMapManager()
	{
	}

	SMapObject* SPlaceMapManager::createPlaceMapObject(PlaceListCsvInfo* placeInfo, DistrictIdType districtId)
	{
		return new SPlaceMapObject(placeInfo, districtId);
	}
	//-----------------------------------------------------------------------------
	REGION_OBJ_TYPE SPlaceMapManager::getRegionType() const
	{
		return ROT_PLACE;
	}
}	//namespace MG