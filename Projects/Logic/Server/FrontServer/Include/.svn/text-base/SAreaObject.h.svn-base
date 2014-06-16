//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\FrontServer\Include\SAreaObject.h
//        Author: yuanlinhu
//          Date: 2012-3-20
//          Time: 9:57
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-20      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_AREA_OBJECT_H_
#define _S_AREA_OBJECT_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SRegionObjectBase.h"

/******************************************************************************/
namespace MG
{
	class SAreaObject : public SRegionObjectBase
	{
	public:
		SAreaObject(MapListCsvInfo* mapCsvInfo);
		~SAreaObject();

		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual DistrictIdType		getDistrictId();
		virtual DistrictRankType	getDistrictRankType();

	//private:
	//	AreaObjectData*		mAreaData;

	private:
		SAreaObject();
	};
}

#endif	//_S_AREA_OBJECT_H_