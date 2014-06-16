//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: BattleScoreSystem.h
//        Author: yuanlinhu
//          Date: 2012-4-23
//          Time: 10:18
//   Description: 
//			战斗统计数据 （内存）
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-7-9      add
//////////////////////////////////////////////////////////////

#ifndef _BATTLE_SCORE_SYSTEM_H_
#define _BATTLE_SCORE_SYSTEM_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "BattleScoresRankListCsv.h"

/******************************************************************************/

namespace MG
{
	class BattleScoreSystem
	{
	public:
		BattleScoreSystem();
		~BattleScoreSystem();
		SINGLETON_INSTANCE(BattleScoreSystem);

		BattleScoresRankListCsvInfo* getBattleScoreRankListByBattleStatics(const BattleStatics* battleStatics);

	private:
		Int	_calcParamPoint(const BattleStatics* battleStatics, const BattleScoresParamListCsvInfo* paramInfo);
	};
}

#endif	//_BATTLE_SCORE_SYSTEM_H_