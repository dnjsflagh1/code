
/******************************************************************************/

#include "stdafx.h"
#include "BattleFieldNoticeListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	BattleFieldNoticeListCsv::BattleFieldNoticeListCsv()
	{

	}
	//--------------------------------------------------------------------------
	BattleFieldNoticeListCsv::~BattleFieldNoticeListCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool BattleFieldNoticeListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			Int rankId = 0;
			MGStrOp::toI32(csvdata->mData[BPN_RankId].c_str(), rankId);
			if (true == mBattleFieldNoticeList.hasData(rankId))
			{
                DEBUG_ASSERT_LOG(false, "true == mBattleFieldNoticeList.hasData(rankId)");
				continue;
			}

			BattleFieldNoticeListCsvInfo* newNoticeCsvInfo = mBattleFieldNoticeList.createOrRetrieve(rankId, false);
			newNoticeCsvInfo->rankId	= rankId;
			newNoticeCsvInfo->name		= csvdata->mData[BPN_Name];
			newNoticeCsvInfo->text		= csvdata->mData[BPN_Text];
			MGStrOp::toI32(csvdata->mData[BPN_ConditionType].c_str(), (I32&)newNoticeCsvInfo->conditionType);
			MGStrOp::toI32(csvdata->mData[BPN_ConditionValue].c_str(), newNoticeCsvInfo->conditionValue);

		}

		return true;
	}

	//--------------------------------------------------------------------------
	BattleFieldNoticeListCsvInfo* BattleFieldNoticeListCsv::getNoticeInfoByConditionType(const BattleFieldConditionType conditionType)
	{
		BattleFieldNoticeListCsvInfo* retNoticeInfo = NULL;
		std::map<Int, BattleFieldNoticeListCsvInfo*>* noticeList = mBattleFieldNoticeList.getDataSet();

		for (std::map<Int, BattleFieldNoticeListCsvInfo*>::iterator iter = noticeList->begin(); iter != noticeList->end(); ++iter)
		{
			if (conditionType == iter->second->conditionType)
			{
				retNoticeInfo = iter->second;
			}
		}

		return retNoticeInfo;
	}

}