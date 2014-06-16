//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\Game\WorldCoreLib\Include\RegionObjectData.h
//        Author: yuanlinhu
//          Date: 2012-3-16
//          Time: 16:04
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-16      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef _REGION_OBJECT_DATA_H_
#define _REGION_OBJECT_DATA_H_
/******************************************************************************/

#include "WorldCorePreqs.h"

#include "MapListCsv.h"
#include "ArtMapResCsv.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//
	/******************************************************************************/
	class RegionObjectData
	{
	public:
		RegionObjectData();
		virtual ~RegionObjectData();

		virtual InstanceIdType			getInstanceId() = 0;


		void	setMapListCsvInfoByMapId(const MapIdType mapId);


		MapIdType				getMapId();
		MapListCsvInfo*			getMapListCsvInfo();
		ArtMapResCsvInfo*		getArtMapResCsvInfo();
		

	private:
		MapListCsvInfo*			mMapListCsvInfo;
		ArtMapResCsvInfo*		mArtMapResCsvInfo;
	};
}

#endif	//_REGION_OBJECT_DATA_H_