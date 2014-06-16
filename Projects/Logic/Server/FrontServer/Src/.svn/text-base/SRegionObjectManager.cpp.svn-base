

/******************************************************************************/

#include "stdafx.h"
#include "SRegionObjectManager.h"

#include "AreaListCsv.h"
#include "MapListCsv.h"
#include "PlaceListCsv.h"
#include "ArtMapResCsv.h"
#include "VassalCsv.h"
#include "District.h"

#include "RelationWorldMapAreaCsv.h"
#include "RelationWorldMapPlaceCsv.h"

#include "InstanceHomeListCsv.h"
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
		//1. 读csv表
		if (District::getInstance().load(L"Config\\Game\\World\\DistrictList.csv",L"Config\\Game\\World\\DistrictTree.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//副本总表
		if ( InstanceListCsv::getInstance().load(L"Config\\Game\\World\\InstanceList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//新手副本
		if ( InstanceTiroListCsv::getInstance().load(L"Config\\Game\\World\\InstanceTiroList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//Pve副本
		if ( InstancePVEListCsv::getInstance().load(L"Config\\Game\\World\\InstancePvEList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//Home副本
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

	Bool SRegionObjectManager::hasMapDistributionObj(MapDistributionIdType mapDistributionId)
	{
		return mMapDistributionObjList.hasData(mapDistributionId);
	}

	Bool SRegionObjectManager::hasPlaceObj(PlaceIdType placeId)
	{
		return mPlaceObjList.hasData(placeId);
	}

	Bool SRegionObjectManager::hasTiroInstanceObj(InstanceIdType instanceId)
	{
		return mTiroObjList.hasData(instanceId);
	}

	Bool SRegionObjectManager::hasPveInstanceObj(InstanceIdType instanceId)
	{
		return mPveObjList.hasData(instanceId);
	}

	Bool SRegionObjectManager::hasHomeInstanceObj(InstanceIdType instanceId)
	{
		return mHomeObjList.hasData(instanceId);
	}

	void SRegionObjectManager::createMapDistributionObj(MapDistributionCsvInfo* mapDistributionCsvInfo)
	{
		const MapDistributionIdType	mapDistributionId = mapDistributionCsvInfo->mapDistributionId;

		VassalCsvInfo* tempVassalInfo = VassalCsv::getInstance().getVassalCsvInfoByRegionId(Vassal_MapDistribution, mapDistributionId);
		if (NULL == tempVassalInfo)
		{
			//该 MapDistriction 未挂接到政区， 所以不创建
			return;
		}

		SMapDistribution* newMapDistribution = mMapDistributionObjList.createOrRetrieve<MapDistributionCsvInfo*, DistrictIdType>
								(mapDistributionId, mapDistributionCsvInfo, tempVassalInfo->districtId);
		
		DYNAMIC_ASSERT(NULL != newMapDistribution);
		DYNAMIC_ASSERT(newMapDistribution->getRegionId() == mapDistributionId);
	}

	void SRegionObjectManager::createPlaceObj(PlaceListCsvInfo* placeInfo)
	{
		const PlaceIdType placeId = placeInfo->placeId;

		VassalCsvInfo* tempVassalInfo = VassalCsv::getInstance().getVassalCsvInfoByRegionId(Vassal_Place, placeId);
		if (NULL == tempVassalInfo)
		{
			//该 place 未挂接到政区， 所以不创建
			return;
		}

		SPlaceObject* place = mPlaceObjList.createOrRetrieve<PlaceListCsvInfo*, DistrictIdType>(placeId, placeInfo, tempVassalInfo->districtId);
		DYNAMIC_ASSERT(NULL != place);
		DYNAMIC_ASSERT(place->getRegionId() == placeId);
	}

	void SRegionObjectManager::createTiroInstanceObj(InstanceListCsvInfo* instanceInfo)
	{
		const InstanceIdType instanceId = instanceInfo->instanceId;

		STiroObject* newTiro = mTiroObjList.createOrRetrieve<InstanceListCsvInfo*>(instanceId, instanceInfo);
		DYNAMIC_ASSERT(NULL != newTiro);
		DYNAMIC_ASSERT(newTiro->getRegionId() == instanceInfo->instanceId);
	}

	void SRegionObjectManager::createPveInstanceObj(InstanceListCsvInfo* instanceInfo)
	{
		const InstanceIdType instanceId = instanceInfo->instanceId;

		SPveObject* newPve = mPveObjList.createOrRetrieve<InstanceListCsvInfo*>(instanceId, instanceInfo);
		DYNAMIC_ASSERT(NULL != newPve);
		DYNAMIC_ASSERT(newPve->getRegionId() == instanceInfo->instanceId);
	}

	void SRegionObjectManager::createHomeInstanceObj(InstanceListCsvInfo* instanceInfo)
	{
		const InstanceIdType instanceId = instanceInfo->instanceId;

		SHomeObject* newHome = mHomeObjList.createOrRetrieve<InstanceListCsvInfo*>(instanceId, instanceInfo);
		DYNAMIC_ASSERT(NULL != newHome);
		DYNAMIC_ASSERT(newHome->getRegionId() == instanceInfo->instanceId);
	}

	////--------------------------------------------------------------------------------------
	//std::map<MapIdType,SMapObject*>* SRegionObjectManager::getMapObjectList()
	//{
	//	return mMapObjList.getDataSet();
	//}

	std::map<MapDistributionIdType,	SMapDistribution*>* SRegionObjectManager::getMapDistributionObjList()
	{
		return mMapDistributionObjList.getDataSet();
	}

	//--------------------------------------------------------------------------------------
	std::map<PlaceIdType,SPlaceObject*>* SRegionObjectManager::getPlaceObjectList()
	{
		return mPlaceObjList.getDataSet();
	}

	std::map<InstanceIdType,STiroObject*>* SRegionObjectManager::getTiroObjectList()
	{
		return mTiroObjList.getDataSet();
	}

	std::map<InstanceIdType,SPveObject*>* SRegionObjectManager::getPveObjectList()
	{
		return mPveObjList.getDataSet();
	}

	std::map<InstanceIdType,SHomeObject*>* SRegionObjectManager::getHomeObjectList()
	{
		return mHomeObjList.getDataSet();
	}
	////--------------------------------------------------------------------------------------
	//std::map<AreaIdType,SAreaObject*>* SRegionObjectManager::getAreaObjectList()
	//{
	//	return mAreaObjList.getDataSet();
	//}


	////--------------------------------------------------------------------------------------
	//SRegionObjectBase* SRegionObjectManager::getMapObject( MapIdType id )
	//{
	//	return mMapObjList.getData(id);
	//}

	////--------------------------------------------------------------------------------------
	//SRegionObjectBase* SRegionObjectManager::getPlaceObject( PlaceIdType id )
	//{
	//	return mPlaceObjList.getData(id);
	//}

	////--------------------------------------------------------------------------------------
	//SRegionObjectBase* SRegionObjectManager::getAreaObject( AreaIdType id )
	//{
	//	return mAreaObjList.getData(id);
	//}

#if 0
	//--------------------------------------------------------------------------------------
	SRegionObjectBase* SRegionObjectManager::getRegionObject( RegionIdType id, REGION_OBJ_TYPE type )
	{
		SRegionObjectBase* regionObject = NULL;
		switch(type)
		{
		case ROT_MAP:
			{
				regionObject = getMapObject(id);
			}break;
		case ROT_PLACE:
			{
				regionObject = getPlaceObject(id);
			}break;
		case ROT_AREA:
			{
				regionObject = getAreaObject(id);
			}break;
		default:
			{
				DYNAMIC_ASSERT(0);
			}break;
		}

		return regionObject;
	}
#endif


	SMapDistribution* SRegionObjectManager::getMapDistributionByDistrictId(const DistrictIdType districtId)
	{
		std::map<MapDistributionIdType, SMapDistribution*>* mapObjList = getMapDistributionObjList();
		std::map<MapDistributionIdType, SMapDistribution*>::iterator iter = mapObjList->begin();
		for ( ; iter != mapObjList->end(); ++iter)
		{
			SMapDistribution* tempMapObj = iter->second;
			if (tempMapObj->getDistrictId() == districtId)
			{
				return tempMapObj;
			}
		}

		return NULL;
	}

	//--------------------------------------------------------------------------------------
	SRegionObjectBase* SRegionObjectManager::getRegionObject(const REGION_OBJ_TYPE regionType, const RegionIdType regionId)
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
	void SRegionObjectManager::printRegionObjectMapServerId()
	{
		MG_LOG(out_sys, "\n ////////////////////////////////////////////////////////////////////////// n ");
		MG_LOG(out_sys, "\n -------------------RegionObject 的 MapServerNetId信息 打印 开始------------------- \n ");
		



		//3. 激活的【SPlaceObject】打印 MapServer的 ID
		{
			string mapDistributionIds;

			std::map<MapDistributionIdType, SMapDistribution*>* mapDistributionObjList = getMapDistributionObjList();
			std::map<MapDistributionIdType, SMapDistribution*>::iterator iter = mapDistributionObjList->begin();
			for ( ; iter != mapDistributionObjList->end(); iter++)
			{
				std::string id;
				std::string temp;
				temp += "[";
				MGStrOp::toString(iter->first, id);
				temp = temp + id + ",";
				MGStrOp::toString(iter->second->getMapServerNetId(), id);
				if (iter->second->getMapServerNetId() <= 0)
				{
					continue;
				}
				temp = temp + id + "]";
				if (mapDistributionIds.empty())
				{
					mapDistributionIds = mapDistributionIds + temp;
				}
				else
				{
					mapDistributionIds = mapDistributionIds + " , " + temp;
				}
			}

			if (mapDistributionIds.empty())
			{
				mapDistributionIds = "空";
			}

			MG_LOG(out_sys, "\n【SMapDistribution[%s]】加载成功\n ", mapDistributionIds.c_str());
		}

		//3. 激活的【SPlaceObject】打印 MapServer的 ID
		{
			string placeObjIds;
			std::map<MapIdType, SPlaceObject*>* placeObjectList = getPlaceObjectList();
			std::map<MapIdType, SPlaceObject*>::iterator iter = placeObjectList->begin();
			for ( ; iter != placeObjectList->end(); iter++)
			{
				std::string id;
				std::string temp;
				temp += "[";
				MGStrOp::toString(iter->first, id);
				temp = temp + id + ",";
				MGStrOp::toString(iter->second->getMapServerNetId(), id);
				if (iter->second->getMapServerNetId() <= 0)
				{
					continue;
				}
				temp = temp + id + "]";
				if (placeObjIds.empty())
				{
					placeObjIds = placeObjIds + temp;
				}
				else
				{
					placeObjIds = placeObjIds + " , " + temp;
				}
			}

			if (placeObjIds.empty())
			{
				placeObjIds = "空";
			}

			MG_LOG(out_sys, "\n【SPlaceObject[%s]】加载成功\n ", placeObjIds.c_str());
		}

		//3. 激活的【SPveObject】打印 MapServer的 ID
		{
			string tiroObjIds;
			std::map<InstanceIdType, SPveObject*>* tiroObjectList = getPveObjectList();
			std::map<InstanceIdType, SPveObject*>::iterator iter = tiroObjectList->begin();
			for ( ; iter != tiroObjectList->end(); iter++)
			{
				std::string id;
				std::string temp;
				temp += "[";
				MGStrOp::toString(iter->first, id);
				temp = temp + id + ",";
				MGStrOp::toString(iter->second->getMapServerNetId(), id);
				if (iter->second->getMapServerNetId() <= 0)
				{
					continue;
				}
				temp = temp + id + "]";
				if (tiroObjIds.empty())
				{
					tiroObjIds = tiroObjIds + temp;
				}
				else
				{
					tiroObjIds = tiroObjIds + " , " + temp;
				}
			}

			if (tiroObjIds.empty())
			{
				tiroObjIds = "空";
			}

			MG_LOG(out_sys, "\n【SPveObject[%s]】加载成功\n ", tiroObjIds.c_str());
		}

		//3. 激活的【STiroObject】打印 MapServer的 ID
		{
			string tiroObjIds;
			std::map<InstanceIdType, STiroObject*>* tiroObjectList = getTiroObjectList();
			std::map<InstanceIdType, STiroObject*>::iterator iter = tiroObjectList->begin();
			for ( ; iter != tiroObjectList->end(); iter++)
			{
				std::string id;
				std::string temp;
				temp += "[";
				MGStrOp::toString(iter->first, id);
				temp = temp + id + ",";
				MGStrOp::toString(iter->second->getMapServerNetId(), id);
				if (iter->second->getMapServerNetId() <= 0)
				{
					continue;
				}
				temp = temp + id + "]";
				if (tiroObjIds.empty())
				{
					tiroObjIds = tiroObjIds + temp;
				}
				else
				{
					tiroObjIds = tiroObjIds + " , " + temp;
				}
			}

			if (tiroObjIds.empty())
			{
				tiroObjIds = "空";
			}

			MG_LOG(out_sys, "\n【STiroObject[%s]】加载成功\n ", tiroObjIds.c_str());
		}

		//3. 激活的【SHomeObject】打印 MapServer的 ID
		{
			string tiroObjIds;
			std::map<InstanceIdType, SHomeObject*>* tiroObjectList = getHomeObjectList();
			std::map<InstanceIdType, SHomeObject*>::iterator iter = tiroObjectList->begin();
			for ( ; iter != tiroObjectList->end(); iter++)
			{
				std::string id;
				std::string temp;
				temp += "[";
				MGStrOp::toString(iter->first, id);
				temp = temp + id + ",";
				MGStrOp::toString(iter->second->getMapServerNetId(), id);
				if (iter->second->getMapServerNetId() <= 0)
				{
					continue;
				}
				temp = temp + id + "]";
				if (tiroObjIds.empty())
				{
					tiroObjIds = tiroObjIds + temp;
				}
				else
				{
					tiroObjIds = tiroObjIds + " , " + temp;
				}
			}

			if (tiroObjIds.empty())
			{
				tiroObjIds = "空";
			}

			MG_LOG(out_sys, "\n【SHomeObject[%s]】加载成功\n ", tiroObjIds.c_str());
		}

		MG_LOG(out_sys, "\n -------------------RegionObject 的 MapServerNetId信息 打印 结束------------------- \n ");
		MG_LOG(out_sys, "\n ////////////////////////////////////////////////////////////////////////// n ");
	}
	//--------------------------------------------------------------------------------------
}
