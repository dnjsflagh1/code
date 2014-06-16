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
#ifndef _S_PVE_OBJECT_H_
#define _S_PVE_OBJECT_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SRegionObjectBase.h"
#include "PveObjectData.h"

/******************************************************************************/
namespace MG
{
	class SPveObject : public SRegionObjectBase
	{
	public:
		SPveObject(InstanceListCsvInfo* instanceInfo);
		~SPveObject();


		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();		//绑定的政区ID
		virtual DistrictRankType	getDistrictRankType();

	public:
		PveObjectData*				getPveData();
		InstanceListCsvInfo*		getListCsvInfo();
		InstancePVEListCsvInfo*		getPveCsvInfo();

	private:
		SPveObject();
		SPveObject(const SPveObject&);
		SPveObject& operator=(const SPveObject&);
	};
}

#endif	//_S_PVE_OBJECT_H_