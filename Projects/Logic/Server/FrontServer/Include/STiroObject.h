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
#ifndef _S_TIRO_OBJECT_H_
#define _S_TIRO_OBJECT_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SRegionObjectBase.h"
#include "TiroObjectData.h"

/******************************************************************************/
namespace MG
{
	class STiroObject : public SRegionObjectBase
	{
	public:
		STiroObject(InstanceListCsvInfo* instanceInfo);
		~STiroObject();


		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();		//绑定的政区ID
		virtual DistrictRankType	getDistrictRankType();

	public:
		TiroObjectData*				getTiroData();
		InstanceListCsvInfo*		getListCsvInfo();
		InstanceTiroListCsvInfo*	getTiroCsvInfo();

	private:
		STiroObject();
		STiroObject(const STiroObject&);
		STiroObject& operator=(const STiroObject&);
	};
}

#endif	//_S_TIRO_OBJECT_H_