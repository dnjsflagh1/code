/******************************************************************************/

#include "stdafx.h"
#include "PlaceObjectData.h"
#include "PlaceListCsv.h"
#include "District.h"
#include "VassalCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	PlaceObjectData::PlaceObjectData(PlaceListCsvInfo* placeListCsvInfo, const DistrictIdType districtId)
		:mPlaceListCsvInfo(placeListCsvInfo)
	{
		DYNAMIC_ASSERT(NULL != placeListCsvInfo);
		setMapListCsvInfoByMapId(placeListCsvInfo->mapListId);

		mDistrictListCsvInfo = District::getInstance().getDistrictInfo(districtId);
		DYNAMIC_ASSERT(NULL != mDistrictListCsvInfo);

	}

	//--------------------------------------------------------------------------------------
	PlaceObjectData::~PlaceObjectData()
	{
	}

	InstanceIdType PlaceObjectData::getInstanceId()
	{
		return mPlaceListCsvInfo->instanceId;
	}

	PlaceListCsvInfo* PlaceObjectData::getPlaceListCsvInfo()
	{
		return mPlaceListCsvInfo;
	}

	DistrictListCsvInfo* PlaceObjectData::getDistrictListCsvInfo()
	{
		return mDistrictListCsvInfo;
	}

	PlaceIdType PlaceObjectData::getPlaceId()
	{
		return mPlaceListCsvInfo->placeId;
	}
}