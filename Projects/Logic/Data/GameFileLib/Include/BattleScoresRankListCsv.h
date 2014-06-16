//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: BattleScoresRankListCsv.h
//        Author: yuanlinhu
//          Date: 2012-7-9
//          Time: 11:27
//   Description: 
//			读取 BattleScoresRankListCsv.csv 表
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-7-9      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _BATTLE_SCORES_RANK_LIST_CSV_H_
#define _BATTLE_SCORES_RANK_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//对应 CSV表的每个字段
	//*************************************************************************************************//
	enum BattleScoresRankListCsvRow
	{
		BPR_ClassId		= 0	,	//评价Id
		BPR_Notes			,
		BPR_ClassName		,	//评价名称
		BPR_IconId			,	//对应图标
		BPR_ClassLevel		,	//评价等级
		BPR_RewardLevel		,	//对应战功点数
		BPR_ItemGroup		,	//奖励物品分组

		BPR_Max,
	};

	//*************************************************************************************************//
	//单个信息
	//*************************************************************************************************//

	struct BattleScoresRankListCsvInfo
	{
		Int						classId;
		Str16					className;
		Str16					iconId;
		Int						classLevel;
		Int						rewardLevel;
		ItemIdType				itemGroup;
	};

	//--------------------------------------------------------------------------
	class BattleScoresRankListCsv
	{
	public:
		BattleScoresRankListCsv();
		~BattleScoresRankListCsv();
		SINGLETON_INSTANCE(BattleScoresRankListCsv);
		// MG_CN_MODIFY
		Bool	load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);

		//根据战功查询最符合条件的
		BattleScoresRankListCsvInfo* getBattleScoreRankByPoint(const Int point);

	private:

		SimpleMapDataSetManager<Int, BattleScoresRankListCsvInfo>		mBattleScoresRankList;
	};
}

#endif	//_BATTLE_SCORES_RANK_LIST_CSV_H_