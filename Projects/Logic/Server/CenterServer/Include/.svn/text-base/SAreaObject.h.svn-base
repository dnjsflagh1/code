//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\CenterServer\Include\SAreaObject.h
//        Author: yuanlinhu
//          Date: 2012-3-21
//          Time: 15:13
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-21      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_AREA_OBJECT_H_
#define _S_AREA_OBJECT_H_
/******************************************************************************/

#include "CenterServerPreqs.h"
#include "SRegionObject.h"

/******************************************************************************/
namespace MG
{
	class SAreaObject : public SRegionObject
	{
	public:
		SAreaObject(MapListCsvInfo* mapCsvInfo);
		~SAreaObject();

		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;

	private:
		AreaObjectData*		mAreaData;

	private:
		SAreaObject();
	};
}

#endif	//_S_AREA_OBJECT_H_
