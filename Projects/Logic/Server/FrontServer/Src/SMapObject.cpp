
/******************************************************************************/

#include "stdafx.h"
#include "SMapObject.h"
#include "MapObjectData.h"

/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------
	SMapObject::SMapObject(MapListCsvInfo* mapCsvInfo)
		:SRegionObjectBase(MG_NEW MapObjectData(mapCsvInfo))
	{
	}

	//-----------------------------------------------------------------------
	SMapObject::~SMapObject()
	{
	}



	//-----------------------------------------------------------------------
	RegionIdType SMapObject::getRegionId()
	{
		DYNAMIC_ASSERT(0);
		return -1;
	}

	//-----------------------------------------------------------------------
	REGION_OBJ_TYPE SMapObject::getRegionType() const
	{
		DYNAMIC_ASSERT(0);
		return ROT_UNKNOWN;
	}
}