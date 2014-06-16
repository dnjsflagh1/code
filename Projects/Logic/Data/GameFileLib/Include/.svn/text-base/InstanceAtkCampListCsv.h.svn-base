//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceAtkCampListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 18:38
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-23      add
//////////////////////////////////////////////////////////////


//*************************************************************************************************//

#ifndef _INSTANCE_ATK_CAMP_LIST_CSV_H_
#define _INSTANCE_ATK_CAMP_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//
namespace MG
{
	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct InstanceAtkCampListCsvInfo
	{
		CampIdType		campListId;
		CampIdType		camp[POSITION_MAX];

		InstanceAtkCampListCsvInfo()
			:campListId(0)
		{
			memset(camp, 0, sizeof(camp));
		}
	};

	class InstanceAtkCampListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum InstanceAtkCampListCsvRow
		{
			InstanceAtkCampListCsvRow_CampListId,			//序列Id
			InstancePVECampListCsvRow_Notes,
			InstancePVECampListCsvRow_CampId1,				//中军出兵配置Id
			InstancePVECampListCsvRow_CampId2,				//左军出兵配置Id
			InstancePVECampListCsvRow_CampId3,				//右军出兵配置Id
			InstancePVECampListCsvRow_CampId4,				//左翼出兵配置Id
			InstancePVECampListCsvRow_CampId5,				//右翼出兵配置Id

			InstancePVECampListCsvRow_Max,
		};
	public:
		InstanceAtkCampListCsv();
		~InstanceAtkCampListCsv();
		SINGLETON_INSTANCE(InstanceAtkCampListCsv);
		// MG_CN_MODIFY
		Bool							load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceAtkCampListCsvInfo*		getInfoById(CampIdType campListId);

		std::map<InstanceIdType, InstanceAtkCampListCsvInfo*>*			getList();

	private:
		SimpleMapDataSetManager<InstanceIdType, InstanceAtkCampListCsvInfo>		mInstanceAtkCampList;
	};
}

#endif	//_INSTANCE_ATK_CAMP_LIST_CSV_H_