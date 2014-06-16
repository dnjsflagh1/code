//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SMapObjectNew.h
//        Author: yuanlinhu
//          Date: 2012-3-12
//          Time: 14:01
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-12      add
//////////////////////////////////////////////////////////////

/******************************************************************************/

#ifndef _C_MAP_DISTRIBUTION_H_
#define _C_MAP_DISTRIBUTION_H_

/******************************************************************************/

#include "ClientPreqs.h"
#include "CRegionObject.h"
#include "MapDistributionObjectData.h"
#include "District.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//分块地图对象
	/******************************************************************************/
	class CMapDistribution : public CRegionObject
	{
	public:
		CMapDistribution(MapDistributionCsvInfo* mapDistributionCsvInfo, DistrictIdType districtId);
		~CMapDistribution();

		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();			//绑定的政区ID
		virtual DistrictRankType	getDistrictRankType();		//政区的类型

	public:
		MapDistributionObjectData*		getMapDistributionData();
		MapDistributionCsvInfo*			getMapDistributionCsvInfo();
		DistrictListCsvInfo*			getDistrictListCsvInfo();

	public:
		MapDistributionType				getMapDistributionType();

	private:
		CMapDistribution();
		CMapDistribution(const CMapDistribution&);
		CMapDistribution operator=(const CMapDistribution&);
	};
}

#endif	//_SMAPOBJECT_NEW_H_
