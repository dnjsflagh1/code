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
#ifndef _MAP_DISTRIBUTION_OBJECT_DATA_H_
#define _MAP_DISTRIBUTION_OBJECT_DATA_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "RegionObjectData.h"
#include "MapDistributionCsv.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//
	/******************************************************************************/
	class MapDistributionObjectData : public RegionObjectData
	{
	public:
		MapDistributionObjectData(MapDistributionCsvInfo* mapDistributionCsvInfo, const DistrictIdType districtId);
		virtual ~MapDistributionObjectData();

		virtual InstanceIdType			getInstanceId() { return 0; }

		MapDistributionCsvInfo*		getMapDistributionCsvInfo();
		DistrictListCsvInfo*		getDistrictListCsvInfo();

	private:
		MapDistributionCsvInfo*		mMapDistributionCsvInfo;
		DistrictListCsvInfo*		mDistrictListCsvInfo;

	private:
		MapDistributionObjectData();
	};
}

#endif	//_AREA_OBJECT_DATA_H_