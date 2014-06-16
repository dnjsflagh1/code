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

#ifndef _S_MAP_DISTRIBUTION_H_
#define _S_MAP_DISTRIBUTION_H_

/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SRegionObjectBase.h"
#include "MapDistributionObjectData.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//分块地图对象
	/******************************************************************************/
	class SMapDistribution : public SRegionObjectBase
	{
	public:
		SMapDistribution(MapDistributionCsvInfo* mapDistributionCsvInfo, DistrictIdType districtId);
		~SMapDistribution();

		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();			//绑定的政区ID
		virtual DistrictRankType	getDistrictRankType();	//政区的类型

	public:
		MapDistributionObjectData*		getMapDistributionData();
		MapDistributionCsvInfo*			getMapDistributionCsvInfo();
		DistrictListCsvInfo*			getDistrictListCsvInfo();

	public:
		MapDistributionType				getMapDistributionType();

	private:
		SMapDistribution();
		SMapDistribution(const SMapDistribution&);
		SMapDistribution operator=(const SMapDistribution&);
	};
}

#endif	//_SMAPOBJECT_NEW_H_
