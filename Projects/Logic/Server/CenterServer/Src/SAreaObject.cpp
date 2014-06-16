
/******************************************************************************/

#include "stdafx.h"
#include "SAreaObject.h"
#include "AreaObjectData.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SAreaObject::SAreaObject(MapListCsvInfo* mapCsvInfo)
	{
		mAreaData = MG_NEW AreaObjectData(mapCsvInfo);
	}

	//-----------------------------------------------------------------------
	SAreaObject::~SAreaObject()
	{
		MG_SAFE_DELETE(mAreaData);
	}

	//-----------------------------------------------------------------------
	RegionIdType SAreaObject::getRegionId()
	{
		return mAreaData->getMapId();
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE SAreaObject::getRegionType() const
	{
		return ROT_UNKNOWN;
	}
}