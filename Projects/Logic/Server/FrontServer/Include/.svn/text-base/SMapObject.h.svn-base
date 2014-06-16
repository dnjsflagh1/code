//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\FrontServer\Include\SMapObjectNew.h
//        Author: yuanlinhu
//          Date: 2012-3-20
//          Time: 10:31
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-20      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _S_MAP_OBJECT_NEW_H_
#define _S_MAP_OBJECT_NEW_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SRegionObjectBase.h"

/******************************************************************************/
namespace MG
{
	class SMapObject : public SRegionObjectBase
	{
	public:
		SMapObject(MapListCsvInfo* mapCsvInfo);
		~SMapObject();

		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;



	//private:
	//	MapObjectData*		mMapData;
		
	private:
		SMapObject();
	};
}

#endif	//_S_MAP_OBJECT_NEW_H_