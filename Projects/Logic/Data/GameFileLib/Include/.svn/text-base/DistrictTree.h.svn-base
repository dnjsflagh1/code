//////////////////////////////////////////////////////////////
//
// Copyright (C), 2012, YXZ Software Co., Ltd. 
//
//      FileName: SCharacterQuestCsv.h
//        Author: yuanlinhu
//          Date: 2012-2-28
//          Time: 14:40
// Description: 
//			1.读取政区列表
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-2-28      add

//////////////////////////////////////////////////////////////

//*************************************************************************************************//
#ifndef _DISTRICT_TREE_H_
#define _DISTRICT_TREE_H_
//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//

	//对应【DistrictTree.csv】里的每一列


	//根类型
	enum RootType
	{
		RT_NULL		= 0,		//0. 无定义

		RT_ROOT		= 1,		//1. 根政区
		RT_CHILD	= 2,		//2. 非根政区

		RT_MAX,
	};


	//单个政区树的信息
	struct DistrictTreeInfo
	{
		DistrictTreeIdType	districtTreeId;
		RootType			rootType;

		DistrictIdType		masterDistrictId;
		DistrictIdType		slaveDistrictId;
	};

	//*************************************************************************************************//
	class DistrictTreeCsv
	{
		enum DistrictTreeRow
		{
			districtTreeId,
			note,
			root_type,
			master_districtId,
			slaver_districtId,

			row_max
		};

	public:
		DistrictTreeCsv();
		~DistrictTreeCsv();
		// MG_CN_MODIFY
		Bool			loadCsv(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		std::map<DistrictTreeIdType, DistrictTreeInfo*>*	getDistrictTreeList();
	private:
		SimpleMapDataSetManager<DistrictTreeIdType, DistrictTreeInfo>	mDistrictTree;
	};
}

#endif	//_DISTRICT_TREE_H_
