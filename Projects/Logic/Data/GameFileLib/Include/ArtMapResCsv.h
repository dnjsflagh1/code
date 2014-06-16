//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: ArtMapResCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-6
//          Time: 11:27
//   Description: 
//			读取 ArtMapRes.csv 表
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-6      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _ART_MAP_RES_CSV_H_
#define _ART_MAP_RES_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"
#include "MapListCsv.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//对应 CSV表的每个字段
	//*************************************************************************************************//
	enum ArtMapResCsvRow
	{
		AMR_ArtMapResId		= 0,
		AMR_ArtMapResNote,
		AMR_Name,
		AMR_AdvanceType,
		AMR_UseType,
		AMR_ResPackId,
		AMR_BaseFilePath,
		AMR_RPGCamSetID,
		AMR_RPGRadarID,
		AMR_SLGCamSetID,
		AMR_SLGRadarID,
		
		AMR_Max,
	};

	//*************************************************************************************************//
	//单个地图资源信息
	//*************************************************************************************************//
	struct ArtMapResCsvInfo
	{
		ArtMapResIdType		artMapResId;		//地图资源的调用Id
		Str16				name;				//地图资源中文名
		//...
		Str16				BaseFilePath;		//美术基础地图地图文件的路径，128个字母和符号

		MapType				mapType;			//地图类型
		U32					rpgCameraId;		//RPG摄像机ID
		U32					rpgRadarId;			//RPG摄像机ID
		U32					slgCameraId;		//SLG摄像机ID	
		U32					slgRadarId;			//SLG小地图ID
	};

	//--------------------------------------------------------------------------
	class ArtMapResCsv
	{
	public:
		ArtMapResCsv();
		~ArtMapResCsv();
		SINGLETON_INSTANCE(ArtMapResCsv);
		// MG_CN_MODIFY
		Bool	load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

		ArtMapResCsvInfo*				getArtMapResInfoById(ArtMapResIdType id);
		
		const ArtMapResCsvInfo*			getArtMapResInfoByIndex(I32 order);

	private:

		SimpleMapDataSetManager<ArtMapResIdType, ArtMapResCsvInfo>		mArtMapResList;
	};
}

#endif	//_ART_MAP_RES_CSV_H_