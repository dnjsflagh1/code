/******************************************************************************/
#ifndef _MAPTYPE_2_REGIONOBJECT_
#define _MAPTYPE_2_REGIONOBJECT_
/******************************************************************************/
#include "WorldCorePreqs.h"
#include "MapListCsv.h"
/******************************************************************************/

namespace MG
{
	class MapType2RegionObject
	{
	public:
		static void MapTypeChangeRegionObject(const MapType mapType, const RegionIdType mapId, REGION_OBJ_TYPE& regionType, RegionIdType& regionId);
	};
}

#endif