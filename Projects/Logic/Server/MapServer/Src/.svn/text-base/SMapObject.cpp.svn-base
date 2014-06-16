
/******************************************************************************/

#include "stdafx.h"
#include "SMapObject.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SMapObject::SMapObject(RegionObjectData* regionData)
		:mRegionData(regionData)
	{
		DYNAMIC_ASSERT_LOG(NULL != regionData, "regionData == NULL");
	}

	//-----------------------------------------------------------------------------
	SMapObject::~SMapObject()
	{
	}

	//-----------------------------------------------------------------------------
	RegionObjectData* SMapObject::getRegionData()
	{
		return mRegionData;
	}
}	//namespace MG