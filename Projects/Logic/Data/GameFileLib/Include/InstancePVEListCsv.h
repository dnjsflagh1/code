//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Src\InstancePVEListCsv.cpp
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 18:06
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-23      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _INSTANCE_PVE_LIST_CSV_H_
#define _INSTANCE_PVE_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct InstancePVEListCsvInfo
	{
		InstanceIdType	instancePVEId;
		Int				openType;
		Int 			openTimeStart;						//开始开放时间
		Int				openTimeEnd;						//结束开放时间
		Int				timepieceId;						//时间区域ID
		Int				overdueType;						//重置间隔类型
		Int				overdueTime;						//重置间隔时间
		Int				teamId;								//队伍ID
		Int				destroyTime;						//销毁时长
		Int				outTime;							//结束时间
		Int				finishQuest;						//任务通关
		Int				finishCharacter;					//人物击杀通关
		Int				finishArmy;							//军队击杀通关
		Int				finishBuilding;						//建筑击杀通关
		Int				finishScript;						//脚本通关
		Int				itemGroupId;						//奖品分组
		Int				rewardScript;						//脚本奖励
		MapIdType		mapListId;

		InstancePVEListCsvInfo()
			:instancePVEId(0)
			,openType(0)
			,openTimeStart(0)
			,openTimeEnd(0)
			,timepieceId(0)
			,overdueType(0)
			,overdueTime(0)
			,teamId(0)
			,destroyTime(0)
			,outTime(0)
			,finishQuest(0)
			,finishCharacter(0)
			,finishArmy(0)
			,finishBuilding(0)
			,finishScript(0)
			,itemGroupId(0)
			,rewardScript(0)
			,mapListId(0)
		{
		}
	};

	//*************************************************************************************************//
	class InstancePVEListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum InstancePVEListCsvRow
		{
			InstancePVEListCsvRow_InstancePVEId		= 0,			//	副本的调用Id
			InstancePVEListCsvRow_Notes,							//
			InstancePVEListCsvRow_OpenType,							//开放时间
			InstancePVEListCsvRow_OpenTimeStart,					//开始开放时间
			InstancePVEListCsvRow_OpenTimeEnd,						//结束开放时间
			InstancePVEListCsvRow_TimepieceID,						//时间区域ID
			InstancePVEListCsvRow_OverdueType,						//重置间隔类型
			InstancePVEListCsvRow_OverdueTime,						//重置间隔时间
			InstancePVEListCsvRow_TeamID,							//队伍ID
			//InstancePVEListCsvRow_DestroyTime,						//销毁时长
			//InstancePVEListCsvRow_OutTime,							//结束时间
			InstancePVEListCsvRow_FinishQuest,						//任务通关
			InstancePVEListCsvRow_FinishCharacter,					//人物击杀通关
			InstancePVEListCsvRow_FinishArmy,						//军队击杀通关
			InstancePVEListCsvRow_FinishBuilding,					//建筑击杀通关
			InstancePVEListCsvRow_FinishScript,						//脚本通关
			InstancePVEListCsvRow_ItemGroupId,						//奖品分组
			InstancePVEListCsvRow_RewardScript,						//脚本奖励
			InstancePVEListCsvRow_MapListId,						//使用地图id
            InstancePVEListCsvRow_ClanJudgeID,                      //氏族判断编号
            InstancePVEListCsvRow_CharacterJudgeID,                 //角色判断编号
			InstancePVEListCsvRow_InstanceTimeId,					//副本时间ID

			InstancePVEListCsvRow_Max,
		};

	public:
		InstancePVEListCsv();
		~InstancePVEListCsv();
		SINGLETON_INSTANCE(InstancePVEListCsv);
		// MG_CN_MODIFY
		Bool						load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstancePVEListCsvInfo*		getInfoById(InstanceIdType id);

		std::map<InstanceIdType, InstancePVEListCsvInfo*>*			getList();

	private:
		SimpleMapDataSetManager<InstanceIdType, InstancePVEListCsvInfo>		mInstancePVEList;
	};
}

#endif	//_INSTANCE_PVE_LIST_CSV_H_