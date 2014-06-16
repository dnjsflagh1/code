

/******************************************************************************/

#include "stdafx.h"
#include "SRegionObjectManager.h"

#include "AreaListCsv.h"
#include "MapListCsv.h"
#include "PlaceListCsv.h"
#include "ArtMapResCsv.h"

#include "RelationWorldMapAreaCsv.h"
#include "RelationWorldMapPlaceCsv.h"

/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	SRegionObjectManager::SRegionObjectManager()
	{

	}

	//--------------------------------------------------------------------------
	SRegionObjectManager::~SRegionObjectManager()
	{

	}

	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------
	Bool SRegionObjectManager::loadCsv()
	{
		//1. ¶Ácsv±í
		if(!ArtMapResCsv::getInstance().load(L"Config\\Game\\ArtRes\\ArtMapRes.csv"))
		{
			return false;
		}

		if(!MapListCsv::getInstance().load(L"Config\\Game\\World\\MapList.csv"))
		{
			return false;
		}

		if(!AreaListCsv::getInstance().load(L"Config\\Game\\World\\AreaList.csv"))
		{
			return false;
		}

		if(!PlaceListCsv::getInstance().load(L"Config\\Game\\World\\PlaceList.csv"))
		{
			return false;
		}
        
		/*
		if (false == RelationWorldMapAreaCsv::getInstance().load(L"MapData\\NewMap\\Relation_PlaceMap_Area.csv"))
		{
			return false;
		}

		if (false == RelationWorldMapPlaceCsv::getInstance().load(L"MapData\\NewMap\\Relation_PlaceMap_Place.csv"))
		{
			return false;
		}
     */

		return true;
	}

	Bool SRegionObjectManager::hasAreaObj(AreaIdType areaId)
	{
		return mAreaObjList.hasData(areaId);
	}
	//--------------------------------------------------------------------------------------
	Bool SRegionObjectManager::hasPlaceObj(PlaceIdType placeId)
	{
		return mPlaceObjList.hasData(placeId);
	}

	//--------------------------------------------------------------------------------------
	void SRegionObjectManager::createPlaceObj(PlaceListCsvInfo* placeInfo, MapListCsvInfo* mapCsvInfo)
	{
		SPlaceObject* newPlaceObj = mPlaceObjList.createOrRetrieve<PlaceListCsvInfo*, MapListCsvInfo*>(mapCsvInfo->mapListId, placeInfo, mapCsvInfo);
		DYNAMIC_ASSERT(NULL != newPlaceObj);
		mAllObjectList.addData(mapCsvInfo->mapListId, newPlaceObj);
	}

	//--------------------------------------------------------------------------------------
	void SRegionObjectManager::createAreaObj(MapListCsvInfo* mapCsvInfo)
	{
		SAreaObject* newAreaObj = mAreaObjList.createOrRetrieve(mapCsvInfo->mapListId, mapCsvInfo);
		DYNAMIC_ASSERT(NULL != newAreaObj);
		mAllObjectList.addData(mapCsvInfo->mapListId, newAreaObj);
	}

	//--------------------------------------------------------------------------------------
	std::map<MapIdType,SMapObject*>* SRegionObjectManager::getMapObjectList()
	{
		return mMapObjList.getDataSet();
	}

	//--------------------------------------------------------------------------------------
	std::map<PlaceIdType,SPlaceObject*>* SRegionObjectManager::getPlaceObjectList()
	{
		return mPlaceObjList.getDataSet();
	}

	//--------------------------------------------------------------------------------------
	std::map<AreaIdType,SAreaObject*>* SRegionObjectManager::getAreaObjectList()
	{
		return mAreaObjList.getDataSet();
	}

	//--------------------------------------------------------------------------------------
	std::map<RegionIdType, SRegionObject*>* SRegionObjectManager::getAllObjcetList()
	{
		return mAllObjectList.getDataList();
	}

	//--------------------------------------------------------------------------------------
	SRegionObject* SRegionObjectManager::getMapObject( MapIdType id )
	{
		return mMapObjList.getData(id);
	}

	//--------------------------------------------------------------------------------------
	SRegionObject* SRegionObjectManager::getPlaceObject( PlaceIdType id )
	{
		return mPlaceObjList.getData(id);
	}

	//--------------------------------------------------------------------------------------
	SRegionObject* SRegionObjectManager::getAreaObject( AreaIdType id )
	{
		return mAreaObjList.getData(id);
	}

	//--------------------------------------------------------------------------------------
	SRegionObject* SRegionObjectManager::getRegionObject( RegionIdType id, REGION_OBJ_TYPE type )
	{
		SRegionObject* regionObject = NULL;
#if 0
		switch(type)
		{
		//case ROT_MAP:
		//	{
		//		regionObject = getMapObject(id);
		//	}break;
		case ROT_PLACE:
			{
				regionObject = getPlaceObject(id);
			}break;
		//case ROT_AREA:
		//	{
		//		regionObject = getAreaObject(id);
		//	}break;
		//case ROT_MAP_DISTRIBUTION:
		//	{
		//		regionObject = 
		//	}
		default:
			{
				DYNAMIC_ASSERT(0);
			}break;
		}
#endif
		DYNAMIC_ASSERT(0);
		return regionObject;
	}
	//--------------------------------------------------------------------------------------
}
