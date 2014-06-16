//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: SRegionObjectManager.h
//        Author: yuanlinhu
//          Date: 2012-3-20
//          Time: 10:13
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-20      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _S_REGION_OBJECT_MANAGER_H_
#define _S_REGION_OBJECT_MANAGER_H_
/******************************************************************************/

#include "FrontServerPreqs.h"

#include "RegionObjectManagerBase.h"
#include "DataSetManager.h"
#include "MapManager.h"

#include "SMapObject.h"
#include "SPlaceObject.h"
#include "SAreaObject.h"
#include "SRegionObjectBase.h"
#include "SMapDistribution.h"
#include "STiroObject.h"
#include "SPveObject.h"
#include "SHomeObject.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//地图管理者
	/******************************************************************************/
	class SRegionObjectManager : public RegionObjectManagerBase
	{
	public:
		SRegionObjectManager();
		~SRegionObjectManager();

	public:
		virtual		Bool	loadCsv();

		virtual		Bool	hasMapDistributionObj(MapDistributionIdType mapDistributionId);
		virtual		Bool	hasPlaceObj(PlaceIdType placeId);
		virtual		Bool	hasTiroInstanceObj(InstanceIdType instanceId);
		virtual		Bool	hasPveInstanceObj(InstanceIdType instanceId);
		virtual		Bool	hasHomeInstanceObj(InstanceIdType instanceId);

		virtual		void	createMapDistributionObj(MapDistributionCsvInfo* mapDistributionCsvInfo);
		virtual		void	createPlaceObj(PlaceListCsvInfo* placeInfo);
		virtual		void	createTiroInstanceObj(InstanceListCsvInfo* instanceTiroInfo);
		virtual		void	createPveInstanceObj(InstanceListCsvInfo* instanceInfo);
		virtual		void	createHomeInstanceObj(InstanceListCsvInfo* instanceInfo);

		std::map<MapDistributionIdType,	SMapDistribution*>	*			getMapDistributionObjList();
		std::map<PlaceIdType,			SPlaceObject*>		*			getPlaceObjectList();
		std::map<InstanceIdType,		STiroObject*>		*			getTiroObjectList();
		std::map<InstanceIdType,		SPveObject*>		*			getPveObjectList();
		std::map<InstanceIdType,		SHomeObject*>		*			getHomeObjectList();
		

		SMapDistribution*		getMapDistributionByDistrictId(const DistrictIdType districtId);
		SRegionObjectBase*		getRegionObject(const REGION_OBJ_TYPE regionType, const RegionIdType id);


		void	printRegionObjectMapServerId();
	
	private:
		SimpleMapDataSetManager<MapDistributionIdType,	SMapDistribution>		mMapDistributionObjList;
		SimpleMapDataSetManager<PlaceIdType,			SPlaceObject>			mPlaceObjList;
		SimpleMapDataSetManager<InstanceIdType,			STiroObject>			mTiroObjList;
		SimpleMapDataSetManager<InstanceIdType,			SPveObject>				mPveObjList;
		SimpleMapDataSetManager<InstanceIdType,			SHomeObject>			mHomeObjList;
	};

}

#endif	//_S_REGION_OBJECT_MANAGER_H_