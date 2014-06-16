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
#ifndef _S_HOME_OBJECT_H_
#define _S_HOME_OBJECT_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SRegionObjectBase.h"
#include "HomeObjectData.h"

/******************************************************************************/
namespace MG
{
	class SHomeObject : public SRegionObjectBase
	{
	public:
		SHomeObject(InstanceListCsvInfo* instanceInfo);
		~SHomeObject();


		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;
		virtual	DistrictIdType		getDistrictId();		//绑定的政区ID
		virtual DistrictRankType	getDistrictRankType();

	public:
		HomeObjectData*				getHomeData();
		InstanceListCsvInfo*		getListCsvInfo();
		InstanceHomeListCsvInfo*	getHomeCsvInfo();

	private:
		SHomeObject();
		SHomeObject(const SHomeObject&);
		SHomeObject& operator=(const SHomeObject&);
	};
}

#endif	//_S_HOME_OBJECT_H_