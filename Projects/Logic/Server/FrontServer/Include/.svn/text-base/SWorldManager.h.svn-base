//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\FrontServer\Include\SWorldManagerNew.h
//        Author: yuanlinhu
//          Date: 2012-3-20
//          Time: 10:52
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-20      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_WORLD_MANAGER_NEW_H_
#define _S_WORLD_MANAGER_NEW_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SRegionObjectManager.h"
#include "SGameObjectManager.h"
#include "RegionNetPacket.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//世界管理者
	/******************************************************************************/
	class SWorldManager
	{
	public:

		SWorldManager();
		~SWorldManager();
		SINGLETON_INSTANCE(SWorldManager);

	public:

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

		virtual Bool			initialize(ServerLauncherInterface* launcher);
		virtual Bool			unInitialize();
		void					update();

        //-----------------------------------------------------------------------------------
        // Debug
        //-----------------------------------------------------------------------------------

        void					printWorldObject();

        //-----------------------------------------------------------------------------------
        // HeartBeat
        //-----------------------------------------------------------------------------------

		HeartBeatManager*		getHeartBeatManager();
		

        //-----------------------------------------------------------------------------------
        // Region
        //-----------------------------------------------------------------------------------

		std::map<MapDistributionIdType,	SMapDistribution*>	*	getMapDistributionObjList();
		std::map<PlaceIdType,			SPlaceObject*>		*	getPlaceObjectList();
		std::map<InstanceIdType,		STiroObject*>		*	getTiroObjectList();

		SMapDistribution*		getMapDistributionByDistrictId(const DistrictIdType districtId);
		SRegionObjectBase*		getRegionObject(const REGION_OBJ_TYPE regionType, const RegionIdType id);
		NetIdType				getMapServerNetIdByRegion(REGION_OBJ_TYPE regionType, RegionIdType id);

        //-----------------------------------------------------------------------------------
        // Server
        //-----------------------------------------------------------------------------------


		// 广播数据包到所有客户端
		void					boardcastNetPacketToAllClient(GameNetSendDataBufferPtr dataPtr, I32 dataSize);

		//// 地图分配策略
		void					reLoadByCenterServerDevideInfoNew(I32 mapServerNum, I32 mapServerIndex, NetIdType mapServerNetId);



	private:

		SRegionObjectManager		mRegionObjectManager;
		SHeartBeatManager*			mHeartBeatManager;

	};
}

#endif	//_S_WORLD_MANAGER_NEW_H_
