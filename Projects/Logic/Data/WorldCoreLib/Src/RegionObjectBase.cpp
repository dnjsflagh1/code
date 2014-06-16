/******************************************************************************/

#include "stdafx.h"
#include "RegionObjectBase.h"




/******************************************************************************/

namespace MG
{

	RegionObjectBase::RegionObjectBase(RegionObjectData* regionData)
		:mRegionData(regionData)
	{
		DYNAMIC_ASSERT(NULL != regionData);
	}

	RegionObjectBase::~RegionObjectBase()
	{

	}

	//-----------------------------------------------------------------------
	RegionObjectData* RegionObjectBase::getData()
	{
		return mRegionData;
	}
}