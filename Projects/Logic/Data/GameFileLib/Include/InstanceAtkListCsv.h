//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceAtrListCsv.h
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

#ifndef _INSTANCE_ATK_LIST_CSV_H_
#define _INSTANCE_ATK_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{


	enum AtkOpenType
	{
		AtkOpenType_Unlimited,		//无限制
		AtkOpenType_EveryHour,		//每小时
		AtkOpenType_EveryDay,		//每天
		AtkOpenType_EveryWeek,		//每周
		
		AtkOpenType_Max
	};

	enum AtkOverdueType
	{
		AtkOverdueType_Unlimited,		//无限制
		AtkOverdueType_EveryHour,		//每小时
		AtkOverdueType_EveryDay,		//每天
		AtkOverdueType_EveryWeek,		//每周
	};
	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct InstanceAtkListCsvInfo
	{
		InstanceIdType		instanceAtkId;
		AtkOpenType			openType;
		U64 				openTimeStart;
		U64 				openTimeEnd;
		I32					timepieceID;
		AtkOverdueType		overdueType;
		U64					overdueTime;
		CampIdType			campListId1;
		CampIdType			campListId2;
		CampIdType			campListId3;
		CampIdType			campListId4;
		QuestIdType			finishQuest;
		GameObjectIdType	finishCharacter;
		ArmyIdType			finishArmy;
		BuildingIdType		finishBuilding;
		Str16				finishScript;
		I32					itemGroupId1;		//胜利奖励，使用物品分组外表的id
		I32					itemGroupId2;		//失败奖励，使用物品分组外表的id
		I32					itemGroupId3;		//平手奖励，使用物品分组外表的id
		Str16				rewardScript;
		U32					intanceTimeId;		//外表id，从副本时间设置表获取

		InstanceAtkListCsvInfo()
			:instanceAtkId(0)
			,openType(AtkOpenType_Unlimited)
			,openTimeStart(0)
			,openTimeEnd(0)
			,timepieceID(0)
			,overdueType(AtkOverdueType_Unlimited)
			,overdueTime(0)
			,campListId1(0)
			,campListId2(0)
			,campListId3(0)
			,campListId4(0)
			,finishQuest(0)
			,finishCharacter(0)
			,finishArmy(0)
			,finishBuilding(0)
			,itemGroupId1(0)
			,itemGroupId2(0)
			,itemGroupId3(0)
			,intanceTimeId(0)
		{
		}
	};

	//*************************************************************************************************//
	class InstanceAtkListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum InstanceAtkListCsvRow
		{
			InstanceAtkListCsvRow_InstanceAtkId	,			//	副本的调用Id
			InstanceAtkListCsvRow_Notes			,
			InstanceAtkListCsvRow_OpenType		,					//开放时间 1~无限制，2~每小时, 3~每天，4~每周
			InstanceAtkListCsvRow_OpenTimeStart,					//开始开放时间
			InstanceAtkListCsvRow_OpenTimeEnd,						//结束开放时间
			InstanceAtkListCsvRow_TimepieceID,						//时间区域ID
			InstanceAtkListCsvRow_OverdueType,						//重置间隔类型	1~无限制，2~每小时,3~每天，4~每周
			InstanceAtkListCsvRow_OverdueTime,						//重置间隔时间
			InstanceAtkListCsvRow_CampListId1,						//攻方配置ID
			InstanceAtkListCsvRow_CampListId2,						//攻方援军配置ID
			InstanceAtkListCsvRow_CampListId3,						//守方配置ID
			InstanceAtkListCsvRow_CampListId4,						//守方援军配置ID
			InstanceAtkListCsvRow_FinishQuest,						//任务通关
			InstanceAtkListCsvRow_FinishCharacter,					//人物击杀通关
			InstanceAtkListCsvRow_FinishArmy,						//军队击杀通关
			InstanceAtkListCsvRow_FinishBuilding,					//建筑击杀通关
			InstanceAtkListCsvRow_FinishScript,						//脚本通关
			InstanceAtkListCsvRow_ItemGroupId1,						//胜利奖励，使用物品分组外表的id
			InstanceAtkListCsvRow_ItemGroupId2,						//失败奖励，使用物品分组外表的id
			InstanceAtkListCsvRow_ItemGroupId3,						//平手奖励，使用物品分组外表的id
			InstanceAtkListCsvRow_RewardScript,						//脚本奖励
			InstanceAtkListCsvRow_IntanceTimeId,					//副本时间ID

			InstanceAtkListCsvRow_Max,
		};
	public:
		InstanceAtkListCsv();
		~InstanceAtkListCsv();
		SINGLETON_INSTANCE(InstanceAtkListCsv);
		// MG_CN_MODIFY
		Bool							load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceAtkListCsvInfo*			getInfoById(InstanceIdType id);

		std::map<InstanceIdType, InstanceAtkListCsvInfo*>*			getList();

	private:
		SimpleMapDataSetManager<InstanceIdType, InstanceAtkListCsvInfo>		mInstanceAtkList;
	};
}

#endif	//_INSTANCE_ATK_LIST_CSV_H_