//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SWorldManagerNew.h
//        Author: yuanlinhu
//          Date: 2012-3-12
//          Time: 13:48
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-12      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _S_WORLD_MANAGER_NEW_H_
#define _S_WORLD_MANAGER_NEW_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "DataSetManager.h"
#include "RegionObjectManagerBase.h"
#include "NetTranspondPacketProcesser.h"
#include "SMapObject.h"
#include "SPlayer.h"
#include "SPlayerCharacter.h"
#include "SBuilding.h"
#include "PlayerNetPacket.h"
#include "RegionNetPacket.h"
#include "BuildingData.h"
#include "PlayerCharacterNetPacket.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//世界管理者
	/******************************************************************************/
    class SWorldManager : public RegionObjectManagerBase
	{
	public:

		SWorldManager();
		~SWorldManager();
		SINGLETON_INSTANCE(SWorldManager);

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

    public:

		Bool					    initialize(ServerLauncherInterface* launcher);
		Bool					    unInitialize();
		void					    update(Flt delta);


		//-----------------------------------------------------------------------------------
		// createRegionObj
		//-----------------------------------------------------------------------------------
		virtual		Bool	loadCsv();

		virtual		Bool	hasMapDistributionObj(MapDistributionIdType mapDistributionId);
		virtual		Bool	hasPlaceObj(PlaceIdType placeId);
		virtual		Bool	hasTiroInstanceObj(InstanceIdType instanceId);
		virtual		Bool	hasPveInstanceObj(InstanceIdType instanceId);
		virtual		Bool	hasHomeInstanceObj(InstanceIdType instanceId);

		virtual		void	createMapDistributionObj(MapDistributionCsvInfo* mapDistributionCsvInfo);
		virtual		void	createPlaceObj(PlaceListCsvInfo* placeListCsvInfo);
		virtual		void	createTiroInstanceObj(InstanceListCsvInfo* instanceInfo);
		virtual		void	createPveInstanceObj(InstanceListCsvInfo* instanceInfo);
		virtual		void	createHomeInstanceObj(InstanceListCsvInfo* instanceInfo);



        //-----------------------------------------------------------------------------------
        // Region
        //-----------------------------------------------------------------------------------

    public:

        void					    reLoadByCenterServerDevideInfo(I32 mapNum, I32 mapIdArray[]);
        void					    reLoadByCenterServerDevideInfoNew(I32 mapServerNum, I32 mapServerIndex);

        void					    openReginObjectBySlaveDistrictInfo(DistrictListCsvInfo* childDistrictListCsvInfo);
        void					    openReginObjectByDistrictId(const DistrictIdType districtId);



        //-----------------------------------------------------------------------------------
        // Scene
        //-----------------------------------------------------------------------------------

    public:

		Bool                        getSceneObject( SSceneObjectPtr& ptr, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid);

		Bool		                getAtkSceneObject( SPlaceSceneObjectPtr& atkMapObjPtr, RegionIdType regionId, InstanceUIdType instanceUid );
		Bool		                getHomeSceneObject( SHomeSceneObjectPtr& homeMapObjPtr, RegionIdType regionId, InstanceUIdType instanceUid );
		Bool		                getTiroSceneObject( STiroSceneObjectPtr& tiroMapObjPtr, RegionIdType regionId, InstanceUIdType instanceUid );
		Bool		                getPveSceneObject( SPveSceneObjectPtr& pveMapObjPtr, RegionIdType regionId, InstanceUIdType instanceUid );
		

		//-----------------------------------------------------------------------------------
		// Debug
		//-----------------------------------------------------------------------------------

	public:

		void					    printWorldObject();			//打印所有
		void					    printActiveRegionObject();


    private:

		DBDriver*               mDBDriver;

		SPlaceMapManager*       mSPlaceMapManager;
		SHomeMapManager*        mSHomeMapManager;
		SPveMapManager*         mSPveMapManager;
		STiroMapManager*        mSTiroMapManager;

	};
}

#endif	//_S_WORLD_MANAGER_NEW_H_