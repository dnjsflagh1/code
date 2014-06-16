//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: PlaceListCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-9
//          Time: 14:39
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-9      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _PLACE_LIST_CSV_
#define _PLACE_LIST_CSV_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//公共枚举
	//*************************************************************************************************//
	enum PlaceOpenType
	{
		POT_Null,			//0. 无意义
		
		POT_Open,			//1. 开放
		POT_Closed,			//2. 不开放

		POT_Max,
	};

	//--------------------------------------------------------------------------
	enum PlaceType
	{
		PlaceType_Null,				//0. 无意义
		
		PlaceType_Create,			//1. 要生成对应内存地图的place
		PlaceType_Not_Create,		//2. 不生成对应内存地图的place(仅通过地点的对话窗口实现功能)
		
		PlaceType_Max,
	};

	//--------------------------------------------------------------------------
	enum PlaceRankType
	{
		PlaceRankType_Null,			//0. 无意义

		PlaceRankType_MainCity,		//1. 主城
		PlaceRankType_Normal,		//2. 普通
		PlaceRankType_Other,		//3. 其他

		PlaceRankType_Max,
	};





	//*************************************************************************************************//
	//单个地点实例信息
	//*************************************************************************************************//
	struct PlaceListCsvInfo
	{
		PlaceIdType				placeId;				//唯一ID
		Str16					placeNote;
		Str16					placeListName;
		Str16					placeName;
		Str16					placeText;
		Str16					placeTitle;
		PlaceOpenType			placeOpen;
		PlaceRankType			placeRank;
		PlaceType				placeType;
		MapIdType				mapListId;
		InstanceIdType			instanceId;
		U32						artIconResId;
		U32						artMashResId;
		MapDistributionIdType	mapDistrListId;
		ArtPointResId			artPointResId;

		PlaceListCsvInfo()
			:placeId(0)
			,placeOpen(POT_Null)
			,placeRank(PlaceRankType_Null)
			,placeType(PlaceType_Null)
			,mapListId(0)
			,instanceId(0)
			,artIconResId(0)
			,artMashResId(0)
			,mapDistrListId(0)
			,artPointResId(0)
		{

		}
	};
	
	//--------------------------------------------------------------------------
	class PlaceListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum PlaceListCsvRow
		{
			PLC_PlaceId = 0,					//地点id
			PLC_Note,							//策划维护表格的备注，128汉字内
			PLC_ListName,						//用于GameMapEditor的类别字段，16汉字内
			PLC_Name,							//地点名，如“长安”等，16汉字内
			PLC_Text,							//地点说明，64汉字内
			PLC_Title,							//地点头衔，如“关、城、所”等，4汉字内
			PLC_OpenType,						//不开放的地点无法进入
			PLC_PlaceRank,						//地点在政区中的级别类型，越小越高
			PLC_PlaceType,						//地点的功能类型
			PLC_MapListId,						//地点内部的地图id
			PLC_InstanceId,						//副本ID
			PLC_ArtIconResId,					//地点的图标id
			PLC_ArtMashResId,					//地点的外观模型id
			PLC_MapDistrListId,					//用于从城市中跳出到具体世界分块地图。ID从(MapDistrList.csv)中取
			PLC_ArtPointResId,					//用于从城市中跳出到具体世界分块地图中坐标点。ID取自ArtPointRes.csv，跳出点由地图编辑者添加
			
			PLC_Max,
		};

	public:
		PlaceListCsv();
		~PlaceListCsv();
		SINGLETON_INSTANCE(PlaceListCsv);
		// MG_CN_MODIFY
		bool load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
	
		std::map<PlaceIdType, PlaceListCsvInfo*>*			getList();

		PlaceListCsvInfo*								getPlaceListInfo(const PlaceIdType id);



	private:

		SimpleMapDataSetManager<PlaceIdType, PlaceListCsvInfo>		mPlaceList;
	};
}

#endif	//_PLACE_LIST_CSV_