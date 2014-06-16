//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: MapListCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-6
//          Time: 13:44
//   Description: 
//			读取 MapList.csv 表
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-6      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _MAP_LIST_CSV_H_
#define _MAP_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//对应 CSV表的每个字段
	//*************************************************************************************************//
	enum MapListCsvRow
	{
		MLC_MapId = 0,						//地图的id，由地编生成
		MLC_MapNote,
		MLC_MapGroupName,					//地图分组名
		MLC_MapName,						//地图名，16汉字内
		MLC_MapText,						//地图说明，64汉字内
		MLC_OpenType,						//"只有开放的地图才会被读取，不开放的地图暂时不使用。"
		MLC_MapType,						//地图对象的类型
		MLC_ArtMapResId,					//地图对象使用的地图资源表id
		MLC_MapFilePath,					//策划用地图信息路径
		MLC_MapFileName,					//策划用地图信息文件名称
		MLC_AudioResId,						//地图对象内播放的音频id，对应音频资源表
		
		MLC_RpgJumpPointId,					//RPG进入点Id
		MLC_RpgAlivePointId,				//RPG复活点Id
		MLC_SlgAttackJumpPointId,			//SLG攻方进入点Id
		MLC_SlgAttackAlivePointId,			//SLG攻方复活点Id
		MLC_SlgDefenseJumpPointId,			//SLG守方进入点Id
		MLC_SlgDefenseAlivePointId,			//SLG守方复活点Id

		MLC_Max,
	};

	enum MapType
	{
		MT_Null				= 0,	//无意义

		MT_Distribution		= 1,	//世界分块地图
		MT_Place			= 2,	//地点内景地图
		MT_Building			= 3,	//建筑内部地图
		MT_Direction		= 4,	//直接跳转地图
		MT_Instance			= 5,	//副本地图

		MT_Max,
	};

	enum MapOpenType
	{
		MOT_Null,
		MOT_Open = 1,
		MOT_Closed = 2,
	};

	//*************************************************************************************************//
	//单个地图实例信息
	//*************************************************************************************************//
	struct MapListCsvInfo
	{
		MapIdType			mapListId;
		//Str16				mapNotes;
		Str16				mapGroupName;
		Str16				mapName;
		Str16				mapText;
		MapOpenType			mapOpenType;
		MapType				mapType;
		ArtMapResIdType		artMapResId;
		Str16				filePath;				//策划用地图信息路径
		Str16				fileName;				//策划用地图信息文件名称
		U32                 audioResID;         	//背景音乐

		ArtPointResId		rpgJumpPointId;			//RPG进入点
		ArtPointResId		rpgAlivePointId;		//RPG复活点
		ArtPointResId		slgAttackJumpPointId;	//SLG攻方进入点
		ArtPointResId		slgAttackAlivePointId;	//SLG攻方复活点
		ArtPointResId		slgDefenseJumpPointId;	//SLG守方进入点
		ArtPointResId		slgDefenseAlivePointId;	//SLG守方复活点

		MapListCsvInfo()
			:mapListId(0)
			,mapOpenType(MOT_Null)
			,mapType(MT_Null)
			,artMapResId(0)
			,audioResID(0)
		
			,rpgJumpPointId(0)
			,rpgAlivePointId(0)
			,slgAttackJumpPointId(0)
			,slgAttackAlivePointId(0)
			,slgDefenseJumpPointId(0)
			,slgDefenseAlivePointId(0)
		{
			mapName.reserve(30);
		}
	};


	//--------------------------------------------------------------------------
	class MapListCsv
	{
	public:
		MapListCsv();
		~MapListCsv();
		SINGLETON_INSTANCE(MapListCsv);
		// MG_CN_MODIFY
		Bool				load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		MapListCsvInfo*		getInfoByMapId(MapIdType id);

		std::map<MapIdType, MapListCsvInfo*>	*	getList();

	private:
		SimpleMapDataSetManager<MapIdType, MapListCsvInfo>		mMapList;
	};
}

#endif	//_MAP_LIST_CSV_H_