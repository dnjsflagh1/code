/******************************************************************************/

#include "stdafx.h"
#include "RegionObjectData.h"

#include "MapListCsv.h"
#include "ArtMapResCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------------------
	RegionObjectData::RegionObjectData(/*MapListCsvInfo* mapCsvInfo*/)
		:mMapListCsvInfo(NULL)
		,mArtMapResCsvInfo(NULL)
	{
	}

	//--------------------------------------------------------------------------------------
	RegionObjectData::~RegionObjectData()
	{
		mMapListCsvInfo		= NULL;
		mArtMapResCsvInfo	= NULL;
	}

	void RegionObjectData::setMapListCsvInfoByMapId(const MapIdType mapId)
	{
		mMapListCsvInfo = MapListCsv::getInstance().getInfoByMapId(mapId);
		DYNAMIC_ASSERT(NULL != mMapListCsvInfo);

		mArtMapResCsvInfo = ArtMapResCsv::getInstance().getArtMapResInfoById(mMapListCsvInfo->artMapResId);
		DYNAMIC_ASSERT(NULL != mArtMapResCsvInfo);
	}

	//--------------------------------------------------------------------------------------
	MapIdType RegionObjectData::getMapId()
	{
		return mMapListCsvInfo->mapListId;
	}

	//--------------------------------------------------------------------------------------
	MapListCsvInfo* RegionObjectData::getMapListCsvInfo()
	{
		return mMapListCsvInfo;
	}

	//--------------------------------------------------------------------------------------
	ArtMapResCsvInfo* RegionObjectData::getArtMapResCsvInfo()
	{
		return mArtMapResCsvInfo;
	}
}