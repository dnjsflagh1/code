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

#ifndef _AREA_LIST_CSV_
#define _AREA_LIST_CSV_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{

	//*************************************************************************************************//
	//公共枚举
	//*************************************************************************************************//
	enum AreaOpenType
	{
		AOT_Null,			//0. 无意义

		AOT_Open,			//1. 开放
		AOT_Closed,			//2. 不开放

		AOT_Max,
	};

	enum AreaType
	{
		AT_Null,			//0. 无意义

		AT_MapType,			//1. 世界分块区域
		AT_PlaceType,		//2. 地点内景区域
		AT_BuildingType,	//3. 建筑内部区域

		AT_Max,
	};

	//*************************************************************************************************//
	//对应 CSV表的每个字段
	//*************************************************************************************************//
	enum AreaListCsvRow
	{
		ALC_AreaId = 0,					//区域id，由编辑器根据实际地图生成
		//ALC_Note	= 1,				//策划备注，16汉字内
		ALC_Name	= 2,				//区域名，16汉字内
		ALC_OpenType,					//"只有开放的区域才会被读取，不开放的区域暂时不使用。"
		ALC_AreaType,					//"区域的用途类型，只有世界分块地图需要指定对应的美术区域"

		ALC_Max,
	};

	//*************************************************************************************************//
	//单个地点实例信息
	//*************************************************************************************************//
	struct AreaListCsvInfo
	{
		AreaIdType			areaId;
		Str16				areaName;
		AreaOpenType		areaOpen;
		AreaType			areaType;

		AreaListCsvInfo()
			:areaId(0)
			,areaOpen(AOT_Null)
			,areaType(AT_Null)
		{
			//areaName.resize(30);
		}
	};

	//--------------------------------------------------------------------------
	class AreaListCsv
	{
	public:
		AreaListCsv();
		~AreaListCsv();
		SINGLETON_INSTANCE(AreaListCsv);
		// MG_CN_MODIFY
		bool load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

		std::map<AreaIdType, AreaListCsvInfo*>*		getList();

	private:
		SimpleMapDataSetManager<AreaIdType, AreaListCsvInfo>		mAreaList;

	};
}

#endif	//_AREA_LIST_CSV_