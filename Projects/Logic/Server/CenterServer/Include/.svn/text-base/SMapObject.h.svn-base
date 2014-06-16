//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\CenterServer\Include\SMapObject.h
//        Author: yuanlinhu
//          Date: 2012-3-21
//          Time: 15:12
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-21      add
//////////////////////////////////////////////////////////////


/******************************************************************************/
#ifndef _S_MAP_OBJECT_NEW_H_
#define _S_MAP_OBJECT_NEW_H_
/******************************************************************************/

#include "CenterServerPreqs.h"
#include "SRegionObject.h"

/******************************************************************************/
namespace MG
{
	class SMapObject : public SRegionObject
	{
	public:
		SMapObject(MapListCsvInfo* mapCsvInfo);
		~SMapObject();

		virtual RegionIdType		getRegionId();
		virtual	REGION_OBJ_TYPE		getRegionType() const;

		void			setMapServerNetId(NetIdType mapServerNetId);
		NetIdType		getMapServerNetId() const;

	private:
		MapObjectData*		mMapData;
		NetIdType			mMapServerNetId;

	private:
		SMapObject();
	};
}

#endif	//_S_MAP_OBJECT_NEW_H_