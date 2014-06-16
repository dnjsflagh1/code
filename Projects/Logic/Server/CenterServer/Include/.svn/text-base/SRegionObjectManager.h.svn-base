//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\CenterServer\Include\SRegionObjectManager.h
//        Author: yuanlinhu
//          Date: 2012-3-21
//          Time: 15:14
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-21      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_REGION_OBJECT_MANAGER_H_
#define _S_REGION_OBJECT_MANAGER_H_
/******************************************************************************/

#include "CenterServerPreqs.h"

#include "RegionObjectManagerBase.h"
#include "DataSetManager.h"
#include "MapManager.h"

#include "SMapObject.h"
#include "SPlaceObject.h"
#include "SAreaObject.h"

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

		virtual		Bool	hasAreaObj(AreaIdType areaId);
		virtual		Bool	hasPlaceObj(PlaceIdType placeId);

		virtual		void	createPlaceObj(PlaceListCsvInfo* placeInfo, MapListCsvInfo* mapCsvInfo);
		virtual		void	createAreaObj(MapListCsvInfo* mapCsvInfo);

		std::map<MapIdType,			SMapObject*>			*			getMapObjectList();
		std::map<PlaceIdType,		SPlaceObject*>			*			getPlaceObjectList();
		std::map<AreaIdType,		SAreaObject*>			*			getAreaObjectList();
		std::map<RegionIdType,		SRegionObject*>			*			getAllObjcetList();


		SRegionObject*							getMapObject(MapIdType id);
		SRegionObject*							getPlaceObject(PlaceIdType id);
		SRegionObject*							getAreaObject(AreaIdType id);
		SRegionObject*							getRegionObject(RegionIdType id, REGION_OBJ_TYPE type);

	private:
		SimpleMapDataSetManager<MapIdType,		SMapObject>			mMapObjList;
		SimpleMapDataSetManager<PlaceIdType,	SPlaceObject>		mPlaceObjList;
		SimpleMapDataSetManager<AreaIdType,		SAreaObject>		mAreaObjList;

		MapManager<RegionIdType, SRegionObject*>					mAllObjectList;
	};

}

#endif	//_S_REGION_OBJECT_MANAGER_H_