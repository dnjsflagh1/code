//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: BattleScoresParamListCsv.h
//        Author: yuanlinhu
//          Date: 2012-7-9
//          Time: 11:27
//   Description: 
//			��ȡ BattleScoresParamList.csv ��
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
	//��Ӧ CSV���ÿ���ֶ�
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
	//������Ϣ
	//*************************************************************************************************//

	enum BattleScoresParamType
	{
		BSPT_NULL = 0,

		BSPT_KillGeneral			,		//(����1) 	���Ƶн�
		BSPT_SupKillGeneralPoint	,		//(����2) 	�������Ƶн���
		BSPT_GeneralHurtPoint		,		//(����3) 	���佫���˺�����
		BSPT_KillArmyPoint			,		//(����4) 	���ƾ�����
		BSPT_ArmyHurtPoint			,		//(����5) 	�Ծ��ӵ��˺�����(ǧ����)
		BSPT_SupKillArmyPoint		,		//(����6) 	�������ƾ�����
		BSPT_DestoryBuildPoint		,		//(����7) 	���ƽ�����
		BSPT_BuildHurtPoint			,		//(����8) 	�Խ������˺�����(ǧ����)
		BSPT_SupDestoryBuildPoint	,		//(����9) 	�������ƽ�����
		BSPT_DestoryForcePoint		,		//(����10) 	������Ҫ�ݵ���
		BSPT_ForceHurtPoint			,		//(����11) 	����Ҫ�ݵ���˺�����
		BSPT_SupDestoryForcePoint	,		//(����12) 	����������Ҫ�ݵ���
		BSPT_HealGeneralPoint		,		//(����13) 	�����佫����(ǧ����)
		BSPT_HealArmyPoint			,		//(����14) 	���ƾ�������(ǧ����)
		BSPT_HealBuildPoint			,		//(����15) 	�޸������;�����(ǧ����)
		BSPT_ConstructBuild,				//(����16)			����������			��New��
		BSPT_DeathPoint				,		//(����17) 	��������
		
		BSPT_MAX,
	};

	struct BattleScoresParamListCsvInfo
	{
		Int						paramId;		//����Id
		Str16					paramName;		//��������
		BattleScoresParamType	paramType;		//��������
		Int						paramValue;		//����ֵ
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