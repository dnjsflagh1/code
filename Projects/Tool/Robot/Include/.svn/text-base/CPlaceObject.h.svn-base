//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: CNewPlace.h
//        Author: yuanlinhu
//          Date: 2012-3-12
//          Time: 10:30
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-12      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _C_NEW_PLACE_H_
#define _C_NEW_PLACE_H_
/******************************************************************************/

#include "ClientPreqs.h"

#include "CRegionObject.h"
#include "PlaceObjectData.h"
/******************************************************************************/
namespace MG
{
	class CPlaceObject : public CRegionObject
	{
	public:
		CPlaceObject(PlaceListCsvInfo* placeInfo, DistrictIdType districtId);
		~CPlaceObject();

		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();				//绑定的政区ID
		virtual DistrictRankType	getDistrictRankType();		    //政区的类型

		PlaceObjectData*			getPlaceData();

		PlaceListCsvInfo*			getPlaceListCsvInfo();

	private:
		CPlaceObject();
	};

}


#endif	//_C_NEW_PLACE_H_