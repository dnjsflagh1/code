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

#ifndef _C_TIRO_OBJECT_H_
#define _C_TIRO_OBJECT_H_

/******************************************************************************/

#include "ClientPreqs.h"
#include "CRegionObject.h"
#include "TiroObjectData.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//新手村对象
	/******************************************************************************/
	class CTiroObject : public CRegionObject
	{
	public:
		explicit CTiroObject(InstanceListCsvInfo* instanceInfo);
		~CTiroObject();

	public:
		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();			//新手副本 不需要填充
		virtual DistrictRankType	getDistrictRankType();		//新手副本 不需要填充

	public:
		TiroObjectData*				getTiroData();
		InstanceListCsvInfo*		getListCsvInfo();
		InstanceTiroListCsvInfo*	getTiroCsvInfo();

	private:
		CTiroObject();
		CTiroObject(const CTiroObject&);
		CTiroObject& operator=(const CTiroObject&);
	};
}

#endif	//_C_TIRO_OBJECT_H_