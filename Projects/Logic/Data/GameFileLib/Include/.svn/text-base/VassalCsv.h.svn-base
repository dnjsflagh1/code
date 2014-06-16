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

#ifndef _VASSAL_CSV_H_
#define _VASSAL_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//公共枚举
	//*************************************************************************************************//


	//--------------------------------------------------------------------------
	enum VassalType
	{
		Vassal_Null				 = 0,			//0. 无意义
		
		Vassal_Place			 = 1,			//1. 地点
		Vassal_Area				 = 2,			//2. 网格 （未实现）
		Vassal_MapDistribution	 = 3,			//3. 地图分块（州地图）
		

		Vassal_Max				,
	};




	//*************************************************************************************************//
	//单个地点实例信息
	//*************************************************************************************************//
	struct VassalCsvInfo
	{
		Int		districtVassalId;			//顺序编号

		VassalType		type;
		RegionIdType	vassalId;
		DistrictIdType	districtId;

		VassalCsvInfo()
			:districtVassalId(0)
			,type(Vassal_Null)
			,vassalId(0)
			,districtId(0)
		{
		}
	};

	//--------------------------------------------------------------------------
	class VassalCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum VassalCsvRow
		{
			Vassal_Row_DistrictVassalid	= 0	,					//地点id
			Vassal_Row_Note					,	
			Vassal_Row_Type					,
			Vassal_Row_VassalId				,
			Vassal_Row_DistrictId			,

			PLC_Max,
		};
	public:
		VassalCsv();
		~VassalCsv();
		SINGLETON_INSTANCE(VassalCsv);

		bool load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		std::map<Int, VassalCsvInfo*>*		getList();
		VassalCsvInfo*						getVassalCsvInfoByRegionId(const VassalType vassalType, const RegionIdType regionId);

	private:
		SimpleMapDataSetManager<Int/*排序编号，对程序无意义*/, VassalCsvInfo>		mVassalCsvList;
	};
}

#endif	//_PLACE_LIST_CSV_