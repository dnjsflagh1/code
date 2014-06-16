/******************************************************************************/

#include "stdafx.h"
#include "BattleScoreSystem.h"
#include "BattleScoresParamListCsv.h"
#include "BattleStatics.h"
#include "BattleScoresRankListCsv.h"

/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	BattleScoreSystem::BattleScoreSystem()
	{

	}

	//--------------------------------------------------------------------------
	BattleScoreSystem::~BattleScoreSystem()
	{

	}

	//--------------------------------------------------------------------------
	BattleScoresRankListCsvInfo* BattleScoreSystem::getBattleScoreRankListByBattleStatics(const BattleStatics* battleStatics)
	{
		//1.根据公式 计算 战功
		Int resultPoint = 0;
		std::map<Int, BattleScoresParamListCsvInfo*>* battleScoresParamList = BattleScoresParamListCsv::getInstance().getBattleScoresParamList();

		for (std::map<Int, BattleScoresParamListCsvInfo*>::iterator iter = battleScoresParamList->begin(); iter != battleScoresParamList->end(); ++iter)
		{
			resultPoint += _calcParamPoint(battleStatics, iter->second);
		}

		//2. 根据战功 查询评价等级
		BattleScoresRankListCsvInfo* rankInfo = BattleScoresRankListCsv::getInstance().getBattleScoreRankByPoint(resultPoint);
		DYNAMIC_ASSERT(NULL != rankInfo);

		return rankInfo;
	}

	//--------------------------------------------------------------------------
	Int	BattleScoreSystem::_calcParamPoint(const BattleStatics* battleStatics, const BattleScoresParamListCsvInfo* paramInfo)
	{
		DYNAMIC_ASSERT(NULL != paramInfo);
		Int point = 0;
		switch(paramInfo->paramType)
		{
		case BSPT_KillGeneral:
			{
				point = battleStatics->getKillGeneralPoint();
			}
			break;
		case BSPT_SupKillGeneralPoint:
			{
				point = battleStatics->getSupKillGeneralPoint();
			}
			break;
		case	BSPT_GeneralHurtPoint		:		//(参数2) 	对武将的伤害总量
			{
				point = battleStatics->getGeneralHurtPoint();
			}
			break;
		case	BSPT_KillArmyPoint			:		//(参数4) 	击破军队数
			{
				point = battleStatics->getKillArmyPoint();
			}
			break;
		case	BSPT_ArmyHurtPoint			:		//(参数5) 	对军队的伤害总量(千分数)
			{
				point = battleStatics->getArmyHurtPoint();
			}
			break;
		case	BSPT_SupKillArmyPoint		:		//(参数6) 	辅助击破军队数
			{
				point = battleStatics->getSupKillArmyPoint();
			}
			break;
		case	BSPT_DestoryBuildPoint		:		//(参数7) 	击破建筑数
			{
				point = battleStatics->getDestoryBuildPoint();
			}
			break;
		case	BSPT_BuildHurtPoint			:		//(参数8) 	对建筑的伤害总量(千分数)
			{
				point = battleStatics->getBuildHurtPoint();
			}
			break;
		case	BSPT_SupDestoryBuildPoint	:		//(参数9) 	辅助击破建筑数
			{
				point = battleStatics->getSupDestoryBuildPoint();
			}
			break;
		case	BSPT_DestoryForcePoint		:		//(参数10) 	击破重要据点数
			{
				point = battleStatics->getDestoryForcePoint();
			}
			break;
		case	BSPT_ForceHurtPoint			:		//(参数11) 	对重要据点的伤害总量
			{
				point = battleStatics->getForceHurtPoint();
			}
			break;
		case	BSPT_SupDestoryForcePoint	:		//(参数12) 	辅助击破重要据点数
			{
				point = battleStatics->getSupDestoryForcePoint();
			}
			break;
		case	BSPT_HealGeneralPoint		:		//(参数13) 	治疗武将总量(千分数)
			{
				point = battleStatics->getHealGeneralPoint();
			}
			break;
		case	BSPT_HealArmyPoint			:		//(参数14) 	治疗军队总量(千分数)
			{
				point = battleStatics->getHealArmyPoint();
			}
			break;
		case	BSPT_HealBuildPoint			:		//(参数15) 	修复建筑耐久总量(千分数)
			{
				point = battleStatics->getHealBuildPoint();
			}
			break;
		case	BSPT_ConstructBuild			:		//(参数16) 	建筑建造量
			{
				point = 0;
			}
			break;
		case	BSPT_DeathPoint				:		//(参数17) 	死亡次数
			{
				point = battleStatics->getDeathPoint();
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(0);
			}
			break;
		}

		return point  * paramInfo->paramValue;
	}

	//--------------------------------------------------------------------------
}