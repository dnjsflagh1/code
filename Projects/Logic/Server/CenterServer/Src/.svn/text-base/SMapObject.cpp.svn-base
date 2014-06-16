
/******************************************************************************/

#include "stdafx.h"
#include "SMapObject.h"
#include "MapObjectData.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SMapObject::SMapObject(MapListCsvInfo* mapCsvInfo)
		:mMapData(NULL)
		,mMapServerNetId(0)
	{
		mMapData = MG_NEW MapObjectData(mapCsvInfo);
	}

	//-----------------------------------------------------------------------
	SMapObject::~SMapObject()
	{
		MG_SAFE_DELETE(mMapData);
	}

	//-----------------------------------------------------------------------
	void SMapObject::setMapServerNetId(NetIdType mapServerNetId)
	{
		mMapServerNetId = mapServerNetId;
	}

	//-----------------------------------------------------------------------
	NetIdType SMapObject::getMapServerNetId() const
	{
		return mMapServerNetId;
	}

	//-----------------------------------------------------------------------
	RegionIdType SMapObject::getRegionId()
	{
		return mMapData->getMapId();
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE SMapObject::getRegionType() const
	{
		return ROT_UNKNOWN;
	}
}