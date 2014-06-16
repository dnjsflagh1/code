//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Client\Core\MGClient\Include\CNewWorldManager.h
//        Author: yuanlinhu
//          Date: 2012-3-10
//          Time: 13:32
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-10      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _C_NEW_WORLD_MANAGER_H_
#define _C_NEW_WORLD_MANAGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "DataSetManager.h"
#include "MapManager.h"

#include "RegionObjectManagerBase.h"

#include "CMapObject.h"
#include "CPlaceObject.h"
#include "CAreaObject.h"
#include "CMapDistribution.h"
#include "CTiroObject.h"
#include "CPveObject.h"
#include "CHomeObject.h"


/******************************************************************************/
namespace MG
{

	class CRegionManager : public RegionObjectManagerBase
	{
	public:
		CRegionManager();
		~CRegionManager();
		SINGLETON_INSTANCE(CRegionManager);

		Bool					initialize();

	public:
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

	public:
		CRegionObject*		    getRegionObjectById(const REGION_OBJ_TYPE regionType, const RegionIdType regionId);
		CPlaceObject*		    getPlaceObjectById(PlaceIdType placeId);

		
		std::map<PlaceIdType,		CPlaceObject*>	*		getPlaceObjectList();
		std::map<InstanceIdType,	CPveObject*>	*		getPveObjectList();


		//CPlaceObject*			getTiroRegionObject();
	
	private:
		SimpleMapDataSetManager<MapDistributionIdType,	CMapDistribution>	mMapDistributionObjList;
		SimpleMapDataSetManager<PlaceIdType,			CPlaceObject>		mPlaceObjList;
		SimpleMapDataSetManager<InstanceIdType,			CTiroObject>		mTiroObjList;
		SimpleMapDataSetManager<InstanceIdType,			CPveObject>			mPveObjList;
		SimpleMapDataSetManager<InstanceIdType,			CHomeObject>		mHomeObjList;
		
	};
}

#endif	//_C_NEW_WORLD_MANAGER_H_