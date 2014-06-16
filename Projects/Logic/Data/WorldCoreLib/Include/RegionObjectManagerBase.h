//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\Game\WorldCoreLib\Include\WorldManagerNew.h
//        Author: yuanlinhu
//          Date: 2012-3-12
//          Time: 13:46
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-12      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _WORLD_MANAGER_NEW_H_
#define _WORLD_MANAGER_NEW_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//区域管理对象,可以派生
	/******************************************************************************/
	class RegionObjectManagerBase
	{
	public:
		RegionObjectManagerBase(){};
		virtual ~RegionObjectManagerBase(){};

		Bool				loadCsvAndCreateRegion();


		virtual		Bool	loadCsv()																	= NULL;

		virtual		Bool	hasMapDistributionObj(MapDistributionIdType mapDistributionId)				= NULL;
		virtual		Bool	hasPlaceObj(PlaceIdType placeId)											= NULL;
		virtual		Bool	hasTiroInstanceObj(InstanceIdType instanceId)								= NULL;
		virtual		Bool	hasPveInstanceObj(InstanceIdType instanceId)								= NULL;
		virtual		Bool	hasHomeInstanceObj(InstanceIdType instanceId)								= NULL;

		virtual		void	createMapDistributionObj(MapDistributionCsvInfo* mapDistributionCsvInfo)	= NULL;
		virtual		void	createPlaceObj(PlaceListCsvInfo* placeInfo)									= NULL;
		virtual		void	createTiroInstanceObj(InstanceListCsvInfo* instanceInfo)					= NULL;
		virtual		void	createPveInstanceObj(InstanceListCsvInfo* instanceInfo)						= NULL;
		virtual		void	createHomeInstanceObj(InstanceListCsvInfo* instanceInfo)					= NULL;
		
		
	private:
		void				createAllMapDistribution();	//创建（州）, 通过 MapDistributionCsv 表创建  
		void				createAllPlace();			//通过 PlaceListCsv 表创建
		void				createAllTiroInstance();	//创建 新手(InstanceNewList.csv 表)等副本
		void				createAllPVEInstance();		//创建 pve(InstancePvEList.csv 表) 等副本
		void				createAllHomeInstance();	//创建 pve(InstanceHomeList.csv 表) 等副本
	};
}

#endif	//_WORLD_MANAGER_NEW_H_	