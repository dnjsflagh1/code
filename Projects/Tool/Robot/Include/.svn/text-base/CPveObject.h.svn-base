//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SPlaceObjectNew.h
//        Author: yuanlinhu
//          Date: 2012-3-12
//          Time: 14:03
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-12      add
//////////////////////////////////////////////////////////////


/******************************************************************************/

#ifndef _C_PVE_OBJECT_H_
#define _C_PVE_OBJECT_H_

/******************************************************************************/

#include "ClientPreqs.h"
#include "CRegionObject.h"
#include "PveObjectData.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//Pve对象
	/******************************************************************************/
	class CPveObject : public CRegionObject
	{
	public:
		CPveObject(InstanceListCsvInfo* instanceInfo);
		~CPveObject();

	public:
		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();			//新手副本 不需要填充
		virtual DistrictRankType	getDistrictRankType();		//新手副本 不需要填充

	public:
		PveObjectData*				getPveData();
		InstanceListCsvInfo*		getListCsvInfo();
		InstancePVEListCsvInfo*		getPveCsvInfo();

	private:
		//CPveObject();
		CPveObject(const CPveObject&);
		CPveObject& operator=(const CPveObject&);
	};
}

#endif	//_C_TIRO_OBJECT_H_