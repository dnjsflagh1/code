//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Common\DataSource\GameFileLib\Include\InstanceListCsv.h
//        Author: yuanlinhu
//          Date: 2012-4-13
//          Time: 10:45
//   Description: 
//			2.1	副本列表(InstanceList)的数据需求
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-4-13      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _INSTANCE_LIST_CSV_H_
#define _INSTANCE_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//部分需要的枚举
	//*************************************************************************************************//
	enum InstanceType	//	副本用途，单选
	{
		InstanceType_Null		= 0,

		InstanceType_HomeLand	= 1,			//1	氏族家园副本（InstanceHome)：氏族家园只有单一玩家可进入(RPG)
		InstanceType_Tiro,						//2	将领新手副本（InstanceTiro）：用于玩家将领的登录压力分流(RPG)
		InstanceType_PVP,						//3	将领对战副本（InstancePvP）：玩家控制将领进行相互pk战斗(RPG)
		InstanceType_PVE,						//4	将领冒险副本（InstancePvE）：玩家将领和电脑怪物进行冒险(RPG)
		InstanceType_Growup,					//5	将领成长副本（InstanceGrowup）：将领通过小玩法来成长的副本(RPG)
		InstanceType_Atk,						//6	军队攻城副本（InstanceAtk）：玩家控制军队攻击城市(SLG)
		InstanceType_History,					//7	军队历史副本(InstanceHistory)：玩家控制军队经历历史战役(SLG)
		InstanceType_Sport,						//8	军队竞技副本（InstanceSport）：玩家军队相互对练的副本(SLG)
		InstanceType_Fight,						//9	军队战斗副本（InstanceFight）：玩家控制军队和电脑军队战斗(SLG)
		InstanceType_Train,						//10 军队训练副本（InstanceTrain）：军队通过小玩法来成长的副本(Slg)
	
		InstanceType_Max
	};


	//*************************************************************************************************//
	//单个副本实例信息
	//*************************************************************************************************//
	struct InstanceListCsvInfo
	{
		InstanceIdType			instanceId;
		Int						useType;
		InstanceType			instanceType;
		InstanceIdType			instanceListId;

		InstanceListCsvInfo()
			:instanceId(0)
			,useType(0)
			,instanceType(InstanceType_Null)
			,instanceListId(0)
		{
		}
	};

	//*************************************************************************************************//
	class InstanceListCsv
	{
		//*************************************************************************************************//
		//对应 CSV表的每个字段
		//*************************************************************************************************//
		enum InstanceListCsvRow
		{
			InstanceRow_InstanceId = 0,					//	副本的调用Id
			InstanceRow_Notes,
			InstanceRow_UseType,						//"副本支持的功能，二进制多选：1=离线重登陆,之后可陆续添加"
			InstanceRow_InstanceType,					//	副本用途，单选
			InstanceRow_InstanceListId,					//	以上副本的对应副本数据id，

			InstanceRow_Max
		};

	public:
		InstanceListCsv();
		~InstanceListCsv();
		SINGLETON_INSTANCE(InstanceListCsv);
		
		Bool					load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		InstanceListCsvInfo*	getInfoById(InstanceIdType id);
		std::map<InstanceIdType, InstanceListCsvInfo*>	*	getList();

	private:
		SimpleMapDataSetManager<InstanceIdType, InstanceListCsvInfo>		mInstanceList;
	};
}

#endif	//_INSTANCE_LIST_CSV_H_
