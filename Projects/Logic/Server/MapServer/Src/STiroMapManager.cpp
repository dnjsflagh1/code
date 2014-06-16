/******************************************************************************/

#include "stdafx.h"
#include "STiroMapManager.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	STiroMapManager::STiroMapManager()
	{
	}

	//-----------------------------------------------------------------------------
	STiroMapManager::~STiroMapManager()
	{
	}

	REGION_OBJ_TYPE STiroMapManager::getRegionType() const
	{
		return ROT_TIRO;
	}
}	//namespace MG