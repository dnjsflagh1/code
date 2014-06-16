//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\CenterServer\Include\SPlaceObject.h
//        Author: yuanlinhu
//          Date: 2012-3-21
//          Time: 15:11
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-21      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _S_PLACE_OBJECT_H_
#define _S_PLACE_OBJECT_H_
/******************************************************************************/

#include "CenterServerPreqs.h"
#include "SRegionObject.h"

/******************************************************************************/
namespace MG
{
	class SPlaceObject : public SRegionObject
	{
	public:
		SPlaceObject(PlaceListCsvInfo* placeInfo, MapListCsvInfo* mapCsvInfo);
		~SPlaceObject();


		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;

	private:
		PlaceObjectData*		mPlaceData;

	private:
		SPlaceObject();
	};
}

#endif	//_S_PLACE_OBJECT_H_