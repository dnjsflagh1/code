/******************************************************************************/

#include "stdafx.h"
#include "SHomeMapManager.h"

/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
	SHomeMapManager::SHomeMapManager()
	{
	}

	//-----------------------------------------------------------------------------
	SHomeMapManager::~SHomeMapManager()
	{
	}

	REGION_OBJ_TYPE SHomeMapManager::getRegionType() const
	{
		return ROT_TIRO;
	}
}	//namespace MG