//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\Game\WorldCoreLib\Include\PlaceObjectData.h
//        Author: yuanlinhu
//          Date: 2012-3-16
//          Time: 16:14
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-16      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _AREA_OBJECT_DATA_H_
#define _AREA_OBJECT_DATA_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "RegionObjectData.h"
#include "PlaceListCsv.h"
#include "DistrictList.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//
	/******************************************************************************/
	class PlaceObjectData : public RegionObjectData
	{
	public:
		PlaceObjectData(PlaceListCsvInfo* placeListCsvInfo, const DistrictIdType districtId);
		virtual ~PlaceObjectData();

		virtual InstanceIdType		getInstanceId();

		PlaceIdType					getPlaceId();

		PlaceListCsvInfo*			getPlaceListCsvInfo();
		DistrictListCsvInfo*		getDistrictListCsvInfo();
	
	private:
		PlaceListCsvInfo*			mPlaceListCsvInfo;
		DistrictListCsvInfo*		mDistrictListCsvInfo;

	private:
		PlaceObjectData();
	};
}

#endif	//_AREA_OBJECT_DATA_H_