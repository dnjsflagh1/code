//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\FrontServer\Include\SPlaceObject.h
//        Author: yuanlinhu
//          Date: 2012-3-20
//          Time: 10:01
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-20      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _S_PLACE_OBJECT_H_
#define _S_PLACE_OBJECT_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SRegionObjectBase.h"

/******************************************************************************/
namespace MG
{
	class SPlaceObject : public SRegionObjectBase
	{
	public:
		SPlaceObject(PlaceListCsvInfo* placeInfo, DistrictIdType districtId);
		~SPlaceObject();


		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();		//绑定的政区ID
		virtual DistrictRankType	getDistrictRankType();

	public:
		PlaceObjectData*			getPlaceData();
		PlaceListCsvInfo*			getPlaceListCsvInfo();
		DistrictListCsvInfo*		getDistrictListCsvInfo();

	private:
		SPlaceObject();
		SPlaceObject(const SPlaceObject&);
		SPlaceObject& operator=(const SPlaceObject&);
	};
}

#endif	//_S_PLACE_OBJECT_H_