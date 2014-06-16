//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: BattleScoresParamListCsv.h
//        Author: yuanlinhu
//          Date: 2012-7-9
//          Time: 11:27
//   Description: 
//			读取 BattleScoresParamList.csv 表
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-7-9      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _BATTLE_SCORES_PARAM_LIST_CSV_H_
#define _BATTLE_SCORES_PARAM_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//对应 CSV表的每个字段
	//*************************************************************************************************//
	enum BattleScoresParamListCsvRow
	{
		BPL_ParamId		= 0	,
		BPL_Notes			,
		BPL_ParamName		,
		BPL_ParamType		,
		BPL_ParamValue		,
		

		BPL_Max,
	};

	//*************************************************************************************************//
	//单个信息
	//*************************************************************************************************//

	enum BattleScoresParamType
	{
		BSPT_NULL = 0,

		BSPT_KillGeneral			,		//(参数1) 	击破敌将
		BSPT_SupKillGeneralPoint	,		//(参数2) 	辅助击破敌将数
		BSPT_GeneralHurtPoint		,		//(参数3) 	对武将的伤害总量
		BSPT_KillArmyPoint			,		//(参数4) 	击破军队数
		BSPT_ArmyHurtPoint			,		//(参数5) 	对军队的伤害总量(千分数)
		BSPT_SupKillArmyPoint		,		//(参数6) 	辅助击破军队数
		BSPT_DestoryBuildPoint		,		//(参数7) 	击破建筑数
		BSPT_BuildHurtPoint			,		//(参数8) 	对建筑的伤害总量(千分数)
		BSPT_SupDestoryBuildPoint	,		//(参数9) 	辅助击破建筑数
		BSPT_DestoryForcePoint		,		//(参数10) 	击破重要据点数
		BSPT_ForceHurtPoint			,		//(参数11) 	对重要据点的伤害总量
		BSPT_SupDestoryForcePoint	,		//(参数12) 	辅助击破重要据点数
		BSPT_HealGeneralPoint		,		//(参数13) 	治疗武将总量(千分数)
		BSPT_HealArmyPoint			,		//(参数14) 	治疗军队总量(千分数)
		BSPT_HealBuildPoint			,		//(参数15) 	修复建筑耐久总量(千分数)
		BSPT_ConstructBuild,				//(参数16)			建筑建造量			【New】
		BSPT_DeathPoint				,		//(参数17) 	死亡次数
		
		BSPT_MAX,
	};

	struct BattleScoresParamListCsvInfo
	{
		Int						paramId;		//参数Id
		Str16					paramName;		//参数名称
		BattleScoresParamType	paramType;		//参数类型
		Int						paramValue;		//参数值
	};

	//--------------------------------------------------------------------------
	class BattleScoresParamListCsv
	{
	public:
		BattleScoresParamListCsv();
		~BattleScoresParamListCsv();
		SINGLETON_INSTANCE(BattleScoresParamListCsv);
		// MG_CN_MODIFY
		Bool	load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		std::map<Int, BattleScoresParamListCsvInfo*>* getBattleScoresParamList();

	private:

		SimpleMapDataSetManager<Int, BattleScoresParamListCsvInfo>		mBattleScoresParamList;
	};
}

#endif	//_BATTLE_SCORES_PARAM_LIST_CSV_H_