//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceTiroListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 11:43
//   Description: 
//			新手副本设置表
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-13      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _INSTANCE_TIRO_LIST_CSV_H_
#define _INSTANCE_TIRO_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct InstanceTiroListCsvInfo
	{
		InstanceIdType	instanceTiroId;
		Int				characterMaxNum;
		Int				newNum;
		QuestIdType		questId;
		MapIdType		mapListId;

		InstanceTiroListCsvInfo()
			:instanceTiroId(0)
			,characterMaxNum(0)
			,newNum(0)
			,questId(0)
			,mapListId(0)
		{
		}
	};

	//*************************************************************************************************//
	class InstanceTiroListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum InstanceTiroListCsvRow
		{
			InstanceTiroRow_InstanceTiroId		= 0,			//	副本的调用Id
			InstanceTiroRow_Note,
			InstanceTiroRow_CharacterMaxNum,				//	副本能够容纳的最多角色数量
			InstanceTiroRow_NewNum,							//	副本新开的人数闸值，超过此数量后，系统会自动新开副本，此数字必然小于副本能够容纳的最多角色数量"
			InstanceTiroRow_QuestId,						//	完成任务的id，完成此任务的角色无法再回到这个副本
			InstanceTiroRow_mapListId,						//冒险副本使用的地图ID
			InstanceTiroRow_InstanceTimeId,
			
			InstanceTiroRow_Max
		};
	public:
		InstanceTiroListCsv();
		~InstanceTiroListCsv();
		SINGLETON_INSTANCE(InstanceTiroListCsv);
		// MG_CN_MODIFY
		Bool				load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceTiroListCsvInfo*	getInfoById(InstanceIdType id);

		std::map<InstanceIdType, InstanceTiroListCsvInfo*>	*	getList();

	private:
		SimpleMapDataSetManager<InstanceIdType, InstanceTiroListCsvInfo>		mInstanceTiroList;
	};
}

#endif	//_INSTANCE_TIRO_LIST_CSV_H_