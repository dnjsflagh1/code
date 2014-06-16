//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: AreaListCsv.h
//        Author: yuanlinhu
//          Date: 2012-3-9
//          Time: 14:38
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-9      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _MAP_DISTRIBUTION_CSV_H_
#define _MAP_DISTRIBUTION_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{

	//*************************************************************************************************//
	//公共枚举
	//*************************************************************************************************//
	enum MapDistributionOpenType
	{
		MDOT_Null,			//0. 无意义

		MDOT_Open,			//1. 开放
		MDOT_Closed,		//2. 不开放

		MDOT_Max,
	};

	enum MapDistributionType
	{
		MDT_Null,			//0. 无意义

		MDT_MapServer1,
		MDT_MapServer2,
		MDT_MapServer3,
		MDT_MapServer4,
		MDT_MapServer5,
		MDT_MapServer6,
		MDT_MapServer7,
		MDT_MapServer8,
		

		MDT_Max,
	};



	//*************************************************************************************************//
	//单个（大）地图分布实例信息
	//*************************************************************************************************//
	struct MapDistributionCsvInfo
	{
		MapDistributionIdType	mapDistributionId;		//唯一ID
		//Str16					listName;
		Str16					name;
		Str16					text;
		MapDistributionOpenType	openType;
		MapDistributionType		mapDistrictType;
		MapIdType				mapId;

		MapDistributionCsvInfo()
			:mapDistributionId(0)
			,openType(MDOT_Null)
			,mapDistrictType(MDT_Null)
			,mapId(0)
		{
		}
	};

	//--------------------------------------------------------------------------
	class MapDistributionCsv
	{
	private:
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum MapDistributionCsvRow
		{
			MapDistributionId	,
			Notes				,
			Name				,
			Text				,
			OpenType			,
			mapDistributionType	,
			MapId				,

			Max					,
		};
	public:
		MapDistributionCsv();
		~MapDistributionCsv();
		SINGLETON_INSTANCE(MapDistributionCsv);
		
		bool load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

		std::map<MapDistributionIdType, MapDistributionCsvInfo*>*		getList();

	private:
		SimpleMapDataSetManager<MapDistributionIdType, MapDistributionCsvInfo>		mMapDistributionCsvList;

	};
}

#endif	//_MAP_DISTRIBUTION_CSV_H_