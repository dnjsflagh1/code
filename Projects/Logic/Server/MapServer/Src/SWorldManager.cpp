
/******************************************************************************/

#include "stdafx.h"
#include "SWorldManager.h"

#include "District.h"
#include "InstanceListCsv.h"
#include "InstanceTimeListCsv.h"
#include "InstanceTiroListCsv.h"
#include "InstancePVEListCsv.h"
#include "InstanceAtkListCsv.h"
#include "InstanceAtkCampListCsv.h"
#include "InstanceAtkStrengthListCsv.h"
#include "InstanceHomeListCsv.h"
#include "GameRadarConfig.h"
#include "ArtMapResCsv.h"
#include "MapListCsv.h"
#include "PlaceListCsv.h"
#include "MapDistributionCsv.h"
#include "VassalCsv.h"

#include "SPlayerManager.h"
#include "SPlaceMapManager.h"
#include "SHomeMapManager.h"
#include "SPveMapManager.h"
#include "STiroMapManager.h"

#include "SPlaceMapObject.h"
#include "SHomeMapObject.h"
#include "STiroMapObject.h"
#include "SPveMapObject.h"

/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------------------
	SWorldManager::SWorldManager()
		:mSPlaceMapManager(NULL)
		,mSHomeMapManager(NULL)
		,mSPveMapManager(NULL)
		,mSTiroMapManager(NULL)
	{
		mSPlaceMapManager	= new SPlaceMapManager();
		//mSHomeMapManager	= new SHomeMapManager();
		//mSPveMapManager		= new SPveMapManager();
		//mSTiroMapManager	= new STiroMapManager();
	}

	//--------------------------------------------------------------------------------------
	SWorldManager::~SWorldManager()
	{

	}

    //-----------------------------------------------------------------------------------
    // Main
    //-----------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------------
	Bool SWorldManager::initialize(ServerLauncherInterface* launcher)
	{
		DYNAMIC_ASSERT(NULL != launcher);

		mDBDriver = launcher->getDBDriver();

		if (false == loadCsvAndCreateRegion())
		{
			DYNAMIC_ASSERT(0);
			return false;
		}
		return true;
	}

    //-----------------------------------------------------------------------------
    Bool SWorldManager::unInitialize()
    {
        return true;
    }

	//-----------------------------------------------------------------------------
	void SWorldManager::update(Flt delta)
	{

	}

	//--------------------------------------------------------------------------------------
	Bool SWorldManager::loadCsv()
	{
		//政区
		if(District::getInstance().load(L"Config\\Game\\World\\DistrictList.csv",L"Config\\Game\\World\\DistrictTree.csv") == false)
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

		//副本中用到的时间
		if ( InstanceTimeListCsv::getInstance().load(L"Config\\Game\\World\\InstanceTimeList.csv") == false )
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

		//PVE 副本
		if ( InstancePVEListCsv::getInstance().load(L"Config\\Game\\World\\InstancePvEList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//Atk 副本
		if ( InstanceAtkListCsv::getInstance().load(L"Config\\Game\\World\\InstanceAtkList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( InstanceAtkCampListCsv::getInstance().load(L"Config\\Game\\Fight\\InstanceAtkCampList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if ( InstanceAtkStrengthListCsv::getInstance().load(L"Config\\Game\\Fight\\InstanceAtkStrengthList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		//Home 副本
		if ( InstanceHomeListCsv::getInstance().load(L"Config\\Game\\World\\InstanceHomeList.csv") == false )
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(GameRadarConfig::getInstance().load(L"Config\\Game\\ArtRes\\RadarSetList.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(ArtMapResCsv::getInstance().load(L"Config\\Game\\ArtRes\\ArtMapRes.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(MapListCsv::getInstance().load(L"Config\\Game\\World\\MapList.csv") ==  false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}


		if(PlaceListCsv::getInstance().load(L"Config\\Game\\World\\PlaceList.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(MapDistributionCsv::getInstance().load(L"Config\\Game\\World\\MapDistrList.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		if(VassalCsv::getInstance().load(L"Config\\Game\\World\\DistrictVassal.csv") == false)
		{
			DYNAMIC_ASSERT(0);
			return false;
		}

		return true;
	}

	Bool SWorldManager::hasMapDistributionObj(MapDistributionIdType mapDistributionId)
	{
		//DYNAMIC_ASSERT(0);
		return true;
	}

	Bool SWorldManager::hasPlaceObj(PlaceIdType placeId)
	{
		DYNAMIC_ASSERT(0);
		return true;
	}

	Bool SWorldManager::hasTiroInstanceObj(InstanceIdType instanceId)
	{
		DYNAMIC_ASSERT(0);
		return true;
	}

	Bool SWorldManager::hasPveInstanceObj(InstanceIdType instanceId)
	{
		DYNAMIC_ASSERT(0);
		return true;
	}

	Bool SWorldManager::hasHomeInstanceObj(InstanceIdType instanceId)
	{
		DYNAMIC_ASSERT(0);
		return true;
	}

	//-----------------------------------------------------------------------------
    void SWorldManager::openReginObjectByDistrictId(const DistrictIdType districtId)
    {
#if 0
        //州 大地图
        {
            std::map<MapDistributionIdType, SMapDistribution*>*	mapObjList = SRegionObjectManager::getInstance().getMapDistributionObjList();
            std::map<MapDistributionIdType, SMapDistribution*>::iterator iter = mapObjList->begin();
            for (; iter != mapObjList->end(); iter++)
            {
                SMapDistribution* mapObj = iter->second;

                DYNAMIC_ASSERT(mapObj->getDistrictRankType() == DRT_ZHOU);

                if (mapObj->getDistrictId() == districtId)
                {
                    mapObj->setOpen(true);
                    //mBigRegionMapDistributionObjectManager.createBigRegionByList(ROT_MAP_DISTRIBUTION, mapObj->getRegionId());
                }
            }
        }

        // Place 开启
        {
            std::map<PlaceIdType, SPlaceObject*>*	placeObjList = SRegionObjectManager::getInstance().getPlaceObjectList();
            std::map<PlaceIdType, SPlaceObject*>::iterator iter = placeObjList->begin();
            for (; iter != placeObjList->end(); iter++)
            {
                SPlaceObject* tempObj = iter->second;

                DYNAMIC_ASSERT(tempObj->getDistrictRankType() == DRT_ZHOU ||
                    tempObj->getDistrictRankType() == DRT_JUN || 
                    tempObj->getDistrictRankType() == DRT_XIAN);

                if (tempObj->getDistrictId() == districtId)
                {
                    tempObj->setOpen(true);
                    //mBigRegionPlaceObjectManager.createBigRegionByList(ROT_PLACE, tempObj->getRegionId());
                }
            }
        }
#endif
    }

    //-----------------------------------------------------------------------------
    void SWorldManager::openReginObjectBySlaveDistrictInfo(DistrictListCsvInfo* childDistrictListCsvInfo)
    {
        std::map<DistrictIdType, DistrictListCsvInfo*>* slaveList =  childDistrictListCsvInfo->getSlaveList();

        //把自己激活
        openReginObjectByDistrictId(childDistrictListCsvInfo->getDistrictId());

        //激活儿子节点的place
        for (std::map<DistrictIdType, DistrictListCsvInfo*>::iterator iter = slaveList->begin(); iter != slaveList->end(); ++iter)
        {
            openReginObjectBySlaveDistrictInfo(iter->second);
        }

    }

    //-----------------------------------------------------------------------------
    void SWorldManager::reLoadByCenterServerDevideInfoNew(I32 mapServerNum, I32 mapServerIndex)
    {
#if 0
        DYNAMIC_ASSERT(mapServerNum >= mapServerIndex+1);
        MapDistributionType mapServerId = (MapDistributionType)(mapServerIndex+1);
        DYNAMIC_ASSERT(MDT_Null < mapServerId && MDT_Max > mapServerId);


        //初始化为 【不开放】
        SRegionObjectManager::getInstance().closeAllRegion();
        //mBigRegionMapDistributionObjectManager.destroyAll();
        //mBigRegionPlaceObjectManager.destroyAll();
        //mBigRegionTiroObjectManager.destroyAll();
        //mBigRegionPveObjectManager.destroyAll();
        //mBigRegionHomeObjectManager.destroyAll();


        //开放 全部 【新手】副本
        {
            std::map<InstanceIdType, STiroObject*>* regionList = SRegionObjectManager::getInstance().getTiroObjectList();
            std::map<InstanceIdType, STiroObject*>::iterator iter = regionList->begin();
            for (; iter != regionList->end(); iter++)
            {
                STiroObject* mapObj = iter->second;

                DYNAMIC_ASSERT(mapObj->getRegionType() == ROT_TIRO);
                //mBigRegionTiroObjectManager.createBigRegionByList(ROT_TIRO, mapObj->getRegionId());
            }
        }

        //开放 全部 【Pve】副本
        {
            std::map<InstanceIdType, SPveObject*>* regionList = SRegionObjectManager::getInstance().getPveObjectList();
            std::map<InstanceIdType, SPveObject*>::iterator iter = regionList->begin();
            for (; iter != regionList->end(); iter++)
            {
                SPveObject* mapObj = iter->second;

                DYNAMIC_ASSERT(mapObj->getRegionType() == ROT_PVE);
                //mBigRegionPveObjectManager.createBigRegionByList(ROT_PVE, mapObj->getRegionId());
            }
        }

        //开放 全部 【Home】副本
        {
            std::map<InstanceIdType, SHomeObject*>* regionList = SRegionObjectManager::getInstance().getHomeObjectList();
            std::map<InstanceIdType, SHomeObject*>::iterator iter = regionList->begin();
            for (; iter != regionList->end(); iter++)
            {
                SHomeObject* mapObj = iter->second;

                DYNAMIC_ASSERT(mapObj->getRegionType() == ROT_HOME);
                //mBigRegionHomeObjectManager.createBigRegionByList(ROT_HOME, mapObj->getRegionId());
            }
        }

        std::vector<DistrictIdType>	allRegionZhouIdVec;	//找到跟
        {
            std::map<MapDistributionIdType, SMapDistribution*>* mapList = SRegionObjectManager::getInstance().getMapDistributionObjList();
            std::map<MapDistributionIdType, SMapDistribution*>::iterator iter = mapList->begin();
            for (; iter != mapList->end(); iter++)
            {
                SMapDistribution* tempRegionObj = iter->second;
                DYNAMIC_ASSERT(tempRegionObj->getRegionType() == ROT_MAP_DISTRIBUTION);
                DYNAMIC_ASSERT(tempRegionObj->getDistrictRankType() == DRT_ZHOU);
                allRegionZhouIdVec.push_back(tempRegionObj->getDistrictId());

            }
        }

        DYNAMIC_ASSERT(false == allRegionZhouIdVec.empty());

        //找MapServer分配方式
        std::vector<DistrictIdType> myOpenDistrictId;
        for (std::vector<DistrictIdType>::iterator iter = allRegionZhouIdVec.begin(); 
            iter != allRegionZhouIdVec.end(); 
            ++iter)
        {
            SMapDistribution* mapObj = SRegionObjectManager::getInstance().getMapDistributionByDistrictId(*iter);
            if (mapObj->getMapDistributionType() == mapServerId)
            {
                myOpenDistrictId.push_back(*iter);
            }
        }

        if (myOpenDistrictId.empty())
        {
            return;
        }
        DYNAMIC_ASSERT(false == myOpenDistrictId.empty());

        //由我开启的州列表里的地图全部开启来
        for (std::vector<DistrictIdType>::iterator iter = myOpenDistrictId.begin(); 
            iter != myOpenDistrictId.end(); 
            ++iter)
        {
            DistrictListCsvInfo* districtChildNode = District::getInstance().getDistrictInfo(*iter);
            openReginObjectBySlaveDistrictInfo(districtChildNode);
        }
#endif
    }

	void SWorldManager::createMapDistributionObj(MapDistributionCsvInfo* mapDistributionCsvInfo)
	{

	}
	//--------------------------------------------------------------------------------------
	void SWorldManager::createPlaceObj(PlaceListCsvInfo* placeListCsvInfo)
	{
		DEBUG_ASSERT_LOG(NULL != placeListCsvInfo, "placeListCsvInfo == NULL");

		const PlaceIdType placeId = placeListCsvInfo->placeId;

		VassalCsvInfo* tempVassalInfo = VassalCsv::getInstance().getVassalCsvInfoByRegionId(Vassal_Place, placeId);
		if (NULL == tempVassalInfo)
		{
			//该 place 未挂接到政区， 所以不创建
			return;
		}

		SPlaceMapObject* placeMapObj = (SPlaceMapObject*)mSPlaceMapManager->createPlaceMapObject(placeListCsvInfo, tempVassalInfo->districtId);

		DYNAMIC_ASSERT(NULL != placeMapObj);
		DYNAMIC_ASSERT(placeMapObj->getRegionId() == placeId);

		//placeMapObj->init();
	}

	void SWorldManager::createTiroInstanceObj(InstanceListCsvInfo* instanceInfo)
	{

	}

	void SWorldManager::createPveInstanceObj(InstanceListCsvInfo* instanceInfo)
	{

	}

	void SWorldManager::createHomeInstanceObj(InstanceListCsvInfo* instanceInfo)
	{

	}

    //-----------------------------------------------------------------------------
    void SWorldManager::reLoadByCenterServerDevideInfo(I32 mapNum, I32 mapIdArray[])
    {
    }


    //-----------------------------------------------------------------------------
    void SWorldManager::printActiveRegionObject()
    {
        //SRegionObjectManager::getInstance().printActiveRegion();
    }

    //-----------------------------------------------------------------------------
    void SWorldManager::printWorldObject()
    {
//        return;
//
//        mGameObjectManager.print();
//
//        SRegionObjectManager::getInstance().printRegion();
//
//#if 0
//        //4. 激活的【MapObject】
//        {
//            MG_LOG(out_sys, "\n ------------------- 【MapObject激活列表信息】开始 ------------------- \n ");
//            std::map<MapIdType, SMapObjectNew*>* mapObjectList = mMapObjList.getDataSet();
//            std::map<MapIdType, SMapObjectNew*>::iterator iter = mapObjectList->begin();
//            Int count = 1;
//
//            std::string strIds;
//            for ( ; iter != mapObjectList->end(); ++iter, ++count)
//            {
//                SMapObjectNew* temp  = (SMapObjectNew*)iter->second;
//                if (true == temp->isOpen())
//                {
//                    std::string strId;
//                    MGStrOp::toString(iter->first, strId);
//                    if (strIds.empty())
//                    {
//                        strIds += strId;
//                    }
//                    else
//                    {
//                        strIds = strIds + "," + strId;
//                    }
//                }
//            }
//            MG_LOG(out_sys, "\n【MapObject[%s]】加载成功\n ", strIds.c_str());
//
//            MG_LOG(out_sys, "\n ------------------- 【MapObject激活列表信息】结束 ------------------- \n ");
//        }
//
//
//        //4. 激活的【PlaceObject】
//        {
//            MG_LOG(out_sys, "\n ------------------- 【PlaceObject激活列表信息】开始 ------------------- \n ");
//            std::map<PlaceIdType, SPlaceObjectNew*>* placeObjectList = mPlaceObjList.getDataSet();
//            std::map<PlaceIdType, SPlaceObjectNew*>::iterator iter = placeObjectList->begin();
//            Int count = 1;
//
//            std::string strIds;
//            for ( ; iter != placeObjectList->end(); ++iter, ++count)
//            {
//                SPlaceObjectNew* temp  = (SPlaceObjectNew*)iter->second;
//                if (true == temp->isOpen())
//                {
//                    std::string strId;
//                    MGStrOp::toString(iter->first, strId);
//                    if (strIds.empty())
//                    {
//                        strIds += strId;
//                    }
//                    else
//                    {
//                        strIds = strIds + "," + strId;
//                    }
//
//
//                }
//            }
//
//            MG_LOG(out_sys, "\n【PlaceObject[%s]】加载成功\n ", strIds.c_str());
//            MG_LOG(out_sys, "\n ------------------- 【PlaceObject激活列表信息】结束 ------------------- \n ");
//        }
//
//        //4. 激活的【SAreaObject】
//        {
//            MG_LOG(out_sys, "\n ------------------- 【AreaObject激活列表信息】开始 ------------------- \n ");
//            std::map<AreaIdType, SAreaObjectNew*>* areaObjectList = mAreaObjList.getDataSet();
//            std::map<AreaIdType, SAreaObjectNew*>::iterator iter = areaObjectList->begin();
//            Int count = 1;
//
//            std::string strIds;
//            for ( ; iter != areaObjectList->end(); ++iter, ++count)
//            {
//                SAreaObjectNew* temp  = (SAreaObjectNew*)iter->second;
//                if (true == temp->isOpen())
//                {
//                    std::string strId;
//                    MGStrOp::toString(iter->first, strId);
//                    if (strIds.empty())
//                    {
//                        strIds += strId;
//                    }
//                    else
//                    {
//                        strIds = strIds + "," + strId;
//                    }
//
//
//                }
//            }
//
//            MG_LOG(out_sys, "\n【AreaObject[%s]】加载成功\n ", strIds.c_str());
//            MG_LOG(out_sys, "\n ------------------- 【AreaObject激活列表信息】结束 ------------------- \n ");
//        }
//#endif
//#if 0
//        //5. 【MapObject】
//        {
//            MG_LOG(out_sys, "\n ------------------- 【MapObject列表信息】开始 ------------------- \n ");
//            std::map<MapIdType, SMapObject*>* mapObjectList = mMapObjList.getDataSet();
//            std::map<MapIdType, SMapObject*>::iterator iter = mapObjectList->begin();
//            Int count = 1;
//            for ( ; iter != mapObjectList->end(); ++iter, ++count)
//            {
//                SMapObject* temp  = iter->second;
//                //if (false == temp->getPlayerList()->empty()/* || false == temp->getPlayerCharacterList()->empty()*/)
//                {
//                    MG_LOG(out_sys, "\n【第[%d]个SMapObjectNew】开始\n ", count);
//                    iter->second->print();
//                    MG_LOG(out_sys, "\n【第[%d]个SMapObjectNew】结束\n ", count);
//                }
//            }
//            MG_LOG(out_sys, "\n ------------------- 【MapObject列表信息】结束 ------------------- \n ");
//        }
//
//
//        //6. 【PlaceObject】
//        {
//            MG_LOG(out_sys, "\n ------------------- 【PlaceObject列表信息】开始 ------------------- \n ");
//            std::map<PlaceIdType, SPlaceObject*>* placeObjectList = mPlaceObjList.getDataSet();
//            std::map<PlaceIdType, SPlaceObject*>::iterator iter = placeObjectList->begin();
//            Int count = 1;
//            for ( ; iter != placeObjectList->end(); ++iter, ++count)
//            {
//                SPlaceObject* temp  = iter->second;
//                //if (false == temp->getPlayerList()->empty()/* || false == temp->getPlayerCharacterList()->empty()*/)
//                {
//                    MG_LOG(out_sys, "\n【第[%d]个SPlaceObjectNew】开始\n ", count);
//                    iter->second->print();
//                    MG_LOG(out_sys, "\n【第[%d]个SPlaceObjectNew】结束\n ", count);
//                }
//
//            }
//            MG_LOG(out_sys, "\n ------------------- 【PlaceObject列表信息】结束 ------------------- \n ");
//        }
//
//        //6. 【SAreaObjectNew】
//        {
//            MG_LOG(out_sys, "\n ------------------- 【SAreaObjectNew列表信息】开始 ------------------- \n ");
//            std::map<AreaIdType, SAreaObject*>* placeObjectList = mAreaObjList.getDataSet();
//            std::map<AreaIdType, SAreaObject*>::iterator iter = placeObjectList->begin();
//            Int count = 1;
//            for ( ; iter != placeObjectList->end(); ++iter, ++count)
//            {
//                SAreaObject* temp  = iter->second;
//                //if (false == temp->getPlayerList()->empty()/* || false == temp->getPlayerCharacterList()->empty()*/)
//                {
//                    MG_LOG(out_sys, "\n【第[%d]个SAreaObjectNew】开始\n ", count);
//                    iter->second->print();
//                    MG_LOG(out_sys, "\n【第[%d]个SAreaObjectNew】结束\n ", count);
//                }
//
//            }
//            MG_LOG(out_sys, "\n ------------------- 【SAreaObjectNew列表信息】结束 ------------------- \n ");
//        }
//
//        MG_LOG(out_sys, "\n ------------------- 整个打印结束 ------------------- \n ");
//        MG_LOG(out_sys, "\n=============================================================================\n ");
//#endif

    }

    //-----------------------------------------------------------------------------------
    // Object In Region
    //-----------------------------------------------------------------------------------




    //-----------------------------------------------------------------------------------
    // Region
    //-----------------------------------------------------------------------------------


	Bool SWorldManager::getAtkSceneObject(SPlaceSceneObjectPtr& atkMapObjPtr, RegionIdType regionId, InstanceUIdType instanceUid)
	{
		SPlaceMapObject* atkMapObject = (SPlaceMapObject*)mSPlaceMapManager->getMapObject(regionId);
		if (instanceUid > 0)
		{
			return atkMapObject->getScene(atkMapObjPtr, instanceUid);
		}
		else if(instanceUid == 0)
		{
			return atkMapObject->getMainScene(atkMapObjPtr);
		}
		else
		{
			return false;
		}
		return false;
	}

	Bool SWorldManager::getHomeSceneObject(SHomeSceneObjectPtr& homeMapObjPtr, RegionIdType regionId, InstanceUIdType instanceUid)
	{
		SHomeMapObject* homeMapObject = (SHomeMapObject*)mSHomeMapManager->getMapObject(regionId);
		return homeMapObject->getScene(homeMapObjPtr, instanceUid);
	}

	Bool SWorldManager::getTiroSceneObject(STiroSceneObjectPtr& tiroMapObjPtr, RegionIdType regionId, InstanceUIdType instanceUid)
	{
		STiroMapObject* tiroMapObject = (STiroMapObject*)mSTiroMapManager->getMapObject(regionId);
		return tiroMapObject->getScene(tiroMapObjPtr, instanceUid);
	}

	Bool SWorldManager::getPveSceneObject(SPveSceneObjectPtr& pveMapObjPtr, RegionIdType regionId, InstanceUIdType instanceUid)
	{
		SPveMapObject* pveMapObject = (SPveMapObject*)mSPveMapManager->getMapObject(regionId);
		return pveMapObject->getScene(pveMapObjPtr, instanceUid);
	}

	//-----------------------------------------------------------------------------
	Bool SWorldManager::getSceneObject(SSceneObjectPtr& ptr, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid)
	{
		return true;
#if 0
		switch(regionType)
		{
		case ROT_PLACE:
			{
				SAtkMapObject* atkMapObject = (SAtkMapObject*)mSAtkMapManager->getMapObject(regionId);
				SAtkSceneObjectPtr atkMapObjPtr;
				if (instanceUid > 0)
				{
					atkMapObject->getScene(atkMapObjPtr, instanceUid);
				}
				else if(instanceUid == 0)
				{
					atkMapObject->getMainScene(atkMapObjPtr);
				}
				else
				{
					
				}
				return atkMapObjPtr->
			}
			break;
		case ROT_MAP_DISTRIBUTION:
			{
				//SAtkMapObject* atkMapObject = (SAtkMapObject*)mSAtkMapManager->getMapObject(regionId);
				//sceneObj = atkMapObject->getScene(instanceUid);
			}
			break;
		case ROT_TIRO:
			{
				STiroMapObject* tiroMapObject = (STiroMapObject*)mSTiroMapManager->getMapObject(regionId);
				sceneObj = tiroMapObject->getScene(instanceUid);
			}
			break;
		case ROT_PVE:
			{
				SPveSceneObject* pveMapObject = (SPveSceneObject*)mSPveMapManager->getMapObject(regionId);
				sceneObj = pveMapObject->getScene(instanceUid);
			}
			break;
		case ROT_HOME:
			{
				SHomeMapObject* homeMapObject = (SHomeMapObject*)mSHomeMapManager->getMapObject(regionId);
				sceneObj = homeMapObject->getScene(instanceUid);
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(0);
			}
			break;
		}

		return sceneObj;
#endif
	}


}