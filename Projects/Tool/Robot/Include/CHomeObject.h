//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\MapServer\Include\CHomeObject.h
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

#ifndef _C_HOME_OBJECT_H_
#define _C_HOME_OBJECT_H_

/******************************************************************************/

#include "ClientPreqs.h"
#include "CRegionObject.h"
#include "HomeObjectData.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//º“‘∞∂‘œÛ
	/******************************************************************************/
	class CHomeObject : public CRegionObject
	{
	public:
		explicit CHomeObject(InstanceListCsvInfo* instanceInfo);
		~CHomeObject();

	public:
		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();
		virtual DistrictRankType	getDistrictRankType();

	public:
		HomeObjectData*				getHomeData();
		InstanceListCsvInfo*		getListCsvInfo();
		InstanceHomeListCsvInfo*	getHomeCsvInfo();

	private:
		CHomeObject();
		CHomeObject(const CHomeObject&);
		CHomeObject& operator=(const CHomeObject&);
	};
}

#endif	//_C_HOME_OBJECT_H_