
/******************************************************************************/

#include "stdafx.h"
#include "CMapObject.h"
#include "MapObjectData.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	CMapObject::CMapObject(MapListCsvInfo* mapCsvInfo)
		:CRegionObject(MG_NEW MapObjectData(mapCsvInfo))
	{
	}

	//--------------------------------------------------------------------------
	CMapObject::~CMapObject()
	{
	}

	//--------------------------------------------------------------------------
	
}