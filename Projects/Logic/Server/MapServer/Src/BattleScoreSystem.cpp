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
		//1.���ݹ�ʽ ���� ս��
		Int resultPoint = 0;
		std::map<Int, BattleScoresParamListCsvInfo*>* battleScoresParamList = BattleScoresParamListCsv::getInstance().getBattleScoresParamList();

		for (std::map<Int, BattleScoresParamListCsvInfo*>::iterator iter = battleScoresParamList->begin(); iter != battleScoresParamList->end(); ++iter)
		{
			resultPoint += _calcParamPoint(battleStatics, iter->second);
		}

		//2. ����ս�� ��ѯ���۵ȼ�
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
		case	BSPT_GeneralHurtPoint		:		//(����2) 	���佫���˺�����
			{
				point = battleStatics->getGeneralHurtPoint();
			}
			break;
		case	BSPT_KillArmyPoint			:		//(����4) 	���ƾ�����
			{
				point = battleStatics->getKillArmyPoint();
			}
			break;
		case	BSPT_ArmyHurtPoint			:		//(����5) 	�Ծ��ӵ��˺�����(ǧ����)
			{
				point = battleStatics->getArmyHurtPoint();
			}
			break;
		case	BSPT_SupKillArmyPoint		:		//(����6) 	�������ƾ�����
			{
				point = battleStatics->getSupKillArmyPoint();
			}
			break;
		case	BSPT_DestoryBuildPoint		:		//(����7) 	���ƽ�����
			{
				point = battleStatics->getDestoryBuildPoint();
			}
			break;
		case	BSPT_BuildHurtPoint			:		//(����8) 	�Խ������˺�����(ǧ����)
			{
				point = battleStatics->getBuildHurtPoint();
			}
			break;
		case	BSPT_SupDestoryBuildPoint	:		//(����9) 	�������ƽ�����
			{
				point = battleStatics->getSupDestoryBuildPoint();
			}
			break;
		case	BSPT_DestoryForcePoint		:		//(����10) 	������Ҫ�ݵ���
			{
				point = battleStatics->getDestoryForcePoint();
			}
			break;
		case	BSPT_ForceHurtPoint			:		//(����11) 	����Ҫ�ݵ���˺�����
			{
				point = battleStatics->getForceHurtPoint();
			}
			break;
		case	BSPT_SupDestoryForcePoint	:		//(����12) 	����������Ҫ�ݵ���
			{
				point = battleStatics->getSupDestoryForcePoint();
			}
			break;
		case	BSPT_HealGeneralPoint		:		//(����13) 	�����佫����(ǧ����)
			{
				point = battleStatics->getHealGeneralPoint();
			}
			break;
		case	BSPT_HealArmyPoint			:		//(����14) 	���ƾ�������(ǧ����)
			{
				point = battleStatics->getHealArmyPoint();
			}
			break;
		case	BSPT_HealBuildPoint			:		//(����15) 	�޸������;�����(ǧ����)
			{
				point = battleStatics->getHealBuildPoint();
			}
			break;
		case	BSPT_ConstructBuild			:		//(����16) 	����������
			{
				point = 0;
			}
			break;
		case	BSPT_DeathPoint				:		//(����17) 	��������
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