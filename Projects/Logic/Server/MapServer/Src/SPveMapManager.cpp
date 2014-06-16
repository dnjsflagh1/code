/******************************************************************************/

#include "stdafx.h"
#include "SPveMapManager.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SPveMapManager::SPveMapManager()
	{
	}

	//-----------------------------------------------------------------------------
	SPveMapManager::~SPveMapManager()
	{
	}

	REGION_OBJ_TYPE SPveMapManager::getRegionType() const
	{
		return ROT_PVE;
	}
}	//namespace MG