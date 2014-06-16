
/******************************************************************************/

#include "stdafx.h"
#include "BattleScoresRankListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	BattleScoresRankListCsv::BattleScoresRankListCsv()
	{

	}
	//--------------------------------------------------------------------------
	BattleScoresRankListCsv::~BattleScoresRankListCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool BattleScoresRankListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			Int classId = 0;
			MGStrOp::toI32(csvdata->mData[BPR_ClassId].c_str(), classId);
			if (true == mBattleScoresRankList.hasData(classId))
			{
				DEBUG_ASSERT_LOG(false, "true == mBattleScoresRankList.hasData(classId)");
				continue;
			}

			BattleScoresRankListCsvInfo* newRankCsvInfo = mBattleScoresRankList.createOrRetrieve(classId);
			newRankCsvInfo->classId		= classId;
			newRankCsvInfo->className	= csvdata->mData[BPR_ClassName];
			newRankCsvInfo->iconId		= csvdata->mData[BPR_IconId];
			MGStrOp::toI32(csvdata->mData[BPR_ClassLevel].c_str(), newRankCsvInfo->classLevel);
			MGStrOp::toI32(csvdata->mData[BPR_RewardLevel].c_str(), newRankCsvInfo->rewardLevel);
			MGStrOp::toU64(csvdata->mData[BPR_ItemGroup].c_str(), newRankCsvInfo->itemGroup);
		}

		return true;
	}

	//--------------------------------------------------------------------------
	BattleScoresRankListCsvInfo* BattleScoresRankListCsv::getBattleScoreRankByPoint(const Int point)
	{
		std::map<Int, BattleScoresRankListCsvInfo*>* rankList = mBattleScoresRankList.getDataSet();
        DEBUG_ASSERT_LOG((false == rankList->empty()), "false == rankList->empty()");
		BattleScoresRankListCsvInfo* resultRankInfo = rankList->begin()->second;

		Bool hasFound = false;
		for (std::map<Int, BattleScoresRankListCsvInfo*>::iterator iter = rankList->begin(); iter != rankList->end(); ++iter)
		{
			if (point < iter->second->rewardLevel)
			{
				continue;
			}

			if (true == hasFound)
			{
				if (resultRankInfo->rewardLevel <= iter->second->rewardLevel)
				{
					resultRankInfo = iter->second;
				}
			}
			else
			{
				resultRankInfo = iter->second;
				hasFound = true;
			}
				
			
		}

        DEBUG_ASSERT_LOG((NULL != resultRankInfo), "NULL != resultRankInfo");
		return resultRankInfo;
	}

	//--------------------------------------------------------------------------

}