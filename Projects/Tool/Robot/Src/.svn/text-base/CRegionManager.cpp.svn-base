
//*********************************************************************************************

#include "stdafx.h"
#include "CRegionManager.h"

#include "PlaceListCsv.h"
#include "AreaListCsv.h"
#include "ArtMapResCsv.h"
#include "MapListCsv.h"

#include "RelationWorldMapAreaCsv.h"
#include "RelationWorldMapPlaceCsv.h"

#include "InstanceListCsv.h"
#include "PlaceListCsv.h"
#include "VassalCsv.h"
#include "InstanceHomeListCsv.h"

//*********************************************************************************************

namespace MG
{
	//--------------------------------------------------------------------------------------
	CRegionManager::CRegionManager()
	{

	}

	//--------------------------------------------------------------------------------------
	CRegionManager::~CRegionManager()
	{

	}

	//--------------------------------------------------------------------------------------
	Bool CRegionManager::initialize()
	{
		return loadCsvAndCreateRegion();
	}

	//--------------------------------------------------------------------------------------
	Bool CRegionManager::loadCsv()
	{
		
		//政区
		if(!District::getInstance().load(L"Config\\Game\\World\\DistrictList.csv",
										 L"Config\\Game\\World\\DistrictTree.csv"))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//副本
		if ( InstanceListCsv::getInstance().load(L"Config\\Game\\World\\InstanceList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//新手副本
		if ( InstanceTiroListCsv::getInstance().load(L"Config\\Game\\World\\InstanceTiroList.csv" ) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//PVE副本
		if ( InstancePVEListCsv::getInstance().load(L"Config\\Game\\World\\InstancePvEList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( InstanceHomeListCsv::getInstance().load(L"Config\\Game\\World\\InstanceHomeList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(!ArtMapResCsv::getInstance().load(L"Config\\Game\\ArtRes\\ArtMapRes.csv"))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(!MapListCsv::getInstance().load(L"Config\\Game\\World\\MapList.csv"))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//1. 读csv表

		if(!PlaceListCsv::getInstance().load(L"Config\\Game\\World\\PlaceList.csv"))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(!MapDistributionCsv::getInstance().load(L"Config\\Game\\World\\MapDistrList.csv"))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(!VassalCsv::getInstance().load(L"Config\\Game\\World\\DistrictVassal.csv"))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		return true;
	}



	Bool CRegionManager::hasMapDistributionObj(MapDistributionIdType mapDistributionId)
	{
		return mMapDistributionObjList.hasData(mapDistributionId);
	}

	//--------------------------------------------------------------------------------------
	Bool CRegionManager::hasPlaceObj(PlaceIdType placeId)
	{
		return mPlaceObjList.hasData(placeId);
	}

	Bool CRegionManager::hasTiroInstanceObj(InstanceIdType instanceId)
	{
		return mTiroObjList.hasData(instanceId);
	}

	Bool CRegionManager::hasPveInstanceObj(InstanceIdType instanceId)
	{
		return mPveObjList.hasData(instanceId);
	}

	Bool CRegionManager::hasHomeInstanceObj(InstanceIdType instanceId)
	{
		return mHomeObjList.hasData(instanceId);
	}

	void CRegionManager::createMapDistributionObj(MapDistributionCsvInfo* mapDistributionCsvInfo)
	{
		const MapDistributionIdType	mapDistributionId = mapDistributionCsvInfo->mapDistributionId;

		VassalCsvInfo* tempVassalInfo = VassalCsv::getInstance().getVassalCsvInfoByRegionId(Vassal_MapDistribution, mapDistributionId);
		if (NULL == tempVassalInfo)
		{
			//该 MapDistriction 未挂接到政区， 所以不创建
			return;
		}


		CMapDistribution* newMapDistribution = mMapDistributionObjList.createOrRetrieve<MapDistributionCsvInfo*,DistrictIdType>
											(mapDistributionId, mapDistributionCsvInfo, tempVassalInfo->districtId);
		
		DYNAMIC_ASSERT(NULL != newMapDistribution);
		DYNAMIC_ASSERT(newMapDistribution->getRegionId() == mapDistributionId);
		
		//mRegionObjectList.addData(mapDistributionId, newMapDistribution);
	}

	//--------------------------------------------------------------------------------------
	void CRegionManager::createPlaceObj(PlaceListCsvInfo* placeListCsvInfo)
	{
		const PlaceIdType placeId = placeListCsvInfo->placeId;

		VassalCsvInfo* tempVassalInfo = VassalCsv::getInstance().getVassalCsvInfoByRegionId(Vassal_Place, placeId);
		if (NULL == tempVassalInfo)
		{
			//该 place 未挂接到政区， 所以不创建
			return;
		}

		CPlaceObject* newPlaceObj = mPlaceObjList.createOrRetrieve<PlaceListCsvInfo*, DistrictIdType>
									(placeId, placeListCsvInfo, tempVassalInfo->districtId);
		DYNAMIC_ASSERT(NULL != newPlaceObj);
		DYNAMIC_ASSERT(newPlaceObj->getRegionId() == placeId);

		//mRegionObjectList.addData(placeId, newPlaceObj);
	}

	void CRegionManager::createTiroInstanceObj(InstanceListCsvInfo* instanceInfo)
	{
		const InstanceIdType instanceId = instanceInfo->instanceId;

		CTiroObject* newTiro = mTiroObjList.createOrRetrieve<InstanceListCsvInfo*>(instanceId, instanceInfo);

		DYNAMIC_ASSERT(NULL != newTiro);
		DYNAMIC_ASSERT(newTiro->getRegionId() == instanceId);
	}

	void CRegionManager::createPveInstanceObj(InstanceListCsvInfo* instanceInfo)
	{
		const InstanceIdType instanceId = instanceInfo->instanceId;

		CPveObject* newPve = mPveObjList.createOrRetrieve<InstanceListCsvInfo*>(instanceId, instanceInfo);

		DYNAMIC_ASSERT(NULL != newPve);
		DYNAMIC_ASSERT(newPve->getRegionId() == instanceId);
	}

	void CRegionManager::createHomeInstanceObj(InstanceListCsvInfo* instanceInfo)
	{
		const InstanceIdType instanceId = instanceInfo->instanceId;

		CHomeObject* newHome = mHomeObjList.createOrRetrieve<InstanceListCsvInfo*>(instanceId, instanceInfo);

		DYNAMIC_ASSERT(NULL != newHome);
		DYNAMIC_ASSERT(newHome->getRegionId() == instanceId);
	}

	//--------------------------------------------------------------------------------------
	CRegionObject* CRegionManager::getRegionObjectById(const REGION_OBJ_TYPE regionType, const RegionIdType regionId)
	{
		switch(regionType)
		{
		case ROT_MAP_DISTRIBUTION:
			{
				return mMapDistributionObjList.getData(regionId);
			}
			break;
		case ROT_PLACE:
			{
				return mPlaceObjList.getData(regionId);
			}
			break;
		case ROT_TIRO:
			{
				return mTiroObjList.getData(regionId);
			}
			break;
		case ROT_PVE:
			{
				return mPveObjList.getData(regionId);
			}
			break;
		case ROT_HOME:
			{
				return mHomeObjList.getData(regionId);
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(0);
				return NULL;
			}
		}
		DYNAMIC_ASSERT(0);
		return NULL;
	}

	////--------------------------------------------------------------------------------------
	//CAreaObject* CRegionManager::getAreaObjectById(AreaIdType areaId)
	//{
	//	return mAreaObjList.getData(areaId);
	//}

	//--------------------------------------------------------------------------------------
	CPlaceObject* CRegionManager::getPlaceObjectById(PlaceIdType placeId)
	{
		return mPlaceObjList.getData(placeId);
	}

	//--------------------------------------------------------------------------------------
	/*CPlaceObject* CRegionManager::getTiroRegionObject()
	{
		CPlaceObject* targetTiroRegionObj = NULL;

		std::map<PlaceIdType, CPlaceObject*>* placeObjectList = mPlaceObjList.getDataSet();
		for (std::map<PlaceIdType, CPlaceObject*>::iterator iter = placeObjectList->begin(); iter != placeObjectList->end(); ++iter)
		{
			if (iter->second->getData()->getInstanceId() == InstanceListCsv::getInstance().getTiroInstanceInfo()->instanceId)
			{
				DYNAMIC_ASSERT(NULL == targetTiroRegionObj);
				targetTiroRegionObj = iter->second;
			}
		}
		return targetTiroRegionObj;
	}*/

	////--------------------------------------------------------------------------------------
	//void CWorldManagerNew::createAllArea()
	//{
	//	std::map<AreaIdType, AreaInfo*>* areaCsvList = AreaListCsv::getInstance().getList();

	//	std::map<AreaIdType, AreaInfo*>::iterator areaIter = areaCsvList->begin();

	//	for ( ; areaIter != areaCsvList->end(); ++areaIter)
	//	{
	//		AreaInfo* areaInfo = areaIter->second;
	//		DYNAMIC_ASSERT(NULL != areaInfo);

	//		//检查是否有重复的
	//		DYNAMIC_ASSERT(false == mAreaObjList.getData(areaInfo->areaId));

	//		RelationInfo* relationInfo = RelationWorldMapAreaCsv::getInstance().getRelationInfoByAreaId(areaInfo->areaId);
	//		DYNAMIC_ASSERT(NULL != relationInfo);
	//		ArtMapResCsv* ArtMapResCsv = MapListCsv::getInstance().getInfoByMapId(relationInfo->mapId);
	//		DYNAMIC_ASSERT(NULL != ArtMapResCsv);

	//		mAreaObjList.createOrRetrieve(areaInfo->areaId, areaInfo, ArtMapResCsv);
	//	}
	//}

	////--------------------------------------------------------------------------------------
	//void CWorldManagerNew::createAllPlace()
	//{
	//	std::map<PlaceIdType, PlaceInfo*>* placeCsvList = PlaceListCsv::getInstance().getList();

	//	std::map<PlaceIdType, PlaceInfo*>::iterator iter = placeCsvList->begin();

	//	for ( ; iter != placeCsvList->end(); ++iter)
	//	{
	//		PlaceInfo* placeInfo = iter->second;
	//		DYNAMIC_ASSERT(NULL != placeInfo);

	//		//检查是否有重复的
	//		DYNAMIC_ASSERT(false == mPlaceObjList.getData(placeInfo->placeId));

	//		RelationInfo* relationInfo = RelationWorldMapPlaceCsv::getInstance().getRelationInfoByPlaceId(placeInfo->placeId);
	//		DYNAMIC_ASSERT(NULL != relationInfo);
	//		ArtMapResCsv* ArtMapResCsv = MapListCsv::getInstance().getInfoByMapId(relationInfo->mapId);
	//		DYNAMIC_ASSERT(NULL != ArtMapResCsv);

	//		mPlaceObjList.createOrRetrieve(placeInfo->placeId, placeInfo, ArtMapResCsv);
	//	}
	//}

	//--------------------------------------------------------------------------------------
	std::map<PlaceIdType, CPlaceObject*>* CRegionManager::getPlaceObjectList()
	{
		return mPlaceObjList.getDataSet();
	}

	std::map<InstanceIdType, CPveObject*>* CRegionManager::getPveObjectList()
	{
		return mPveObjList.getDataSet();
	}
}