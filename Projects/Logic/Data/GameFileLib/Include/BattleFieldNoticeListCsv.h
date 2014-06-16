//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: BattleFieldNoticeListCsv.h
//        Author: yuanlinhu
//          Date: 2012-7-9
//          Time: 11:27
//   Description: 
//			读取 BattleFieldNoticeListCsv.csv 表
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-7-9      add
//////////////////////////////////////////////////////////////

//*************************************************************************************************//

#ifndef _BATTLE_FIELD_NOTICE_LIST_CSV_H_
#define _BATTLE_FIELD_NOTICE_LIST_CSV_H_

//*************************************************************************************************//

#include "GameFilePreqs.h"
#include "DataSetManager.h"

//*************************************************************************************************//

namespace MG
{
	//*************************************************************************************************//
	//对应 CSV表的每个字段
	//*************************************************************************************************//
	enum BattleFieldNoticeListCsvRow
	{
		BPN_RankId		= 0	,		//通告序列Id
		BPN_Notes			,
		BPN_Name			,		//通告名称
		BPN_Text			,		//显示文字
		BPN_ConditionType	,		//判断类型
		BPN_ConditionValue	,		//判断值域

		BPN_MAX
	};

	//*************************************************************************************************//
	//单个信息
	//*************************************************************************************************//
	enum BattleFieldConditionType
	{
		BFCT_NULL,

		BFCT_KillGeneral,

		BFCT_MAX
	};

	struct BattleFieldNoticeListCsvInfo
	{
		Int							rankId;
		Str16						name;
		Str16						text;
		BattleFieldConditionType	conditionType;
		Int							conditionValue;
	};

	//--------------------------------------------------------------------------
	class BattleFieldNoticeListCsv
	{
	public:
		BattleFieldNoticeListCsv();
		~BattleFieldNoticeListCsv();
		SINGLETON_INSTANCE(BattleFieldNoticeListCsv);
		// MG_CN_MODIFY
		Bool	load(const Char16* FileName, IMGExternalPackManager* packManager = NULL);
		BattleFieldNoticeListCsvInfo*		getNoticeInfoByConditionType(const BattleFieldConditionType conditionType);

	private:

		SimpleMapDataSetManager<Int, BattleFieldNoticeListCsvInfo>		mBattleFieldNoticeList;
	};
}

#endif	//_BATTLE_FIELD_NOTICE_LIST_CSV_H_