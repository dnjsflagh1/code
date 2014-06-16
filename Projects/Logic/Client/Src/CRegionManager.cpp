
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

#include "InstanceAtkListCsv.h"
#include "InstanceTimeListCsv.h"
// MG_CN_MODIFY
#include "ClientMain.h"
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
		// MG_CN_MODIFY
		IEngineMain* engineMain = ClientMain::getInstance().getEngine();
		IMGExternalPackManager* packManager = ClientMain::getInstance().getMGPackManager();
		
		//政区
		if(!District::getInstance().load(L"Config\\Game\\World\\DistrictList.csv",
										 L"Config\\Game\\World\\DistrictTree.csv", packManager))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//副本
		if ( InstanceListCsv::getInstance().load(L"Config\\Game\\World\\InstanceList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//新手副本
		if ( InstanceTiroListCsv::getInstance().load(L"Config\\Game\\World\\InstanceTiroList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//PVE副本
		if ( InstancePVEListCsv::getInstance().load(L"Config\\Game\\World\\InstancePvEList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( InstanceHomeListCsv::getInstance().load(L"Config\\Game\\World\\InstanceHomeList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(!ArtMapResCsv::getInstance().load(L"Config\\Game\\ArtRes\\ArtMapRes.csv", packManager))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(!MapListCsv::getInstance().load(L"Config\\Game\\World\\MapList.csv", packManager))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//1. 读csv表

		if(!PlaceListCsv::getInstance().load(L"Config\\Game\\World\\PlaceList.csv", packManager))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(!MapDistributionCsv::getInstance().load(L"Config\\Game\\World\\MapDistrList.csv", packManager))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(!VassalCsv::getInstance().load(L"Config\\Game\\World\\DistrictVassal.csv", packManager))
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//副本中用到的时间
		if ( InstanceTimeListCsv::getInstance().load(L"Config\\Game\\World\\InstanceTimeList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}


		//Atk 副本
		if ( InstanceAtkListCsv::getInstance().load(L"Config\\Game\\World\\InstanceAtkList.csv", packManager) == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}


		return true;
	}

	//--------------------------------------------------------------------------------------
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
	CRegionObject* CRegionManager::getRegionObjectById(REGION_OBJ_TYPE regionType, RegionIdType regionId)
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

	//--------------------------------------------------------------------------------------
	std::map<MapDistributionIdType,	CMapDistribution*>* CRegionManager::getMapDistributionObjList()
	{
		return mMapDistributionObjList.getDataSet();
	}

	//--------------------------------------------------------------------------------------
	std::map<PlaceIdType, CPlaceObject*>* CRegionManager::getPlaceObjList()
	{
		return mPlaceObjList.getDataSet();
	}

	//--------------------------------------------------------------------------------------
	std::map<InstanceIdType, CTiroObject*>* CRegionManager::getTiroObjList()
	{
		return mTiroObjList.getDataSet();
	}

	//--------------------------------------------------------------------------------------
	std::map<InstanceIdType, CPveObject*>* CRegionManager::getPveObjList()
	{
		return mPveObjList.getDataSet();
	}

	//--------------------------------------------------------------------------------------
	std::map<InstanceIdType, CHomeObject*>* CRegionManager::getHomeObjList()
	{
		return mHomeObjList.getDataSet();
	}

	//--------------------------------------------------------------------------------------
}