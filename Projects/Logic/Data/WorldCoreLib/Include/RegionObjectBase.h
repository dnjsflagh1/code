//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\SRegionObject.h
//        Author: yuanlinhu
//          Date: 2012-3-16
//          Time: 17:45
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-16      add
//////////////////////////////////////////////////////////////


/******************************************************************************/

#ifndef _WORLDCORE_REGION_OBJECT_BASE_H_
#define _WORLDCORE_REGION_OBJECT_BASE_H_

/******************************************************************************/

#include "WorldCorePreqs.h"
#include "DistrictList.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//�������
	/******************************************************************************/
	class RegionObjectBase
	{
	public:
		RegionObjectBase(RegionObjectData* regionData);
		virtual ~RegionObjectBase();
		
		virtual RegionIdType		getRegionId()				= NULL;
		virtual	REGION_OBJ_TYPE		getRegionType() const		= NULL;
		virtual	DistrictIdType		getDistrictId()				= NULL;		//�󶨵�����ID
		virtual DistrictRankType	getDistrictRankType()		= NULL;		//����������

		RegionObjectData*	getData();


	private:
		RegionObjectData*					mRegionData;

	private:
		RegionObjectBase();
	};
}

#endif	//_WORLDCORE_REGION_OBJECT_BASE_H_