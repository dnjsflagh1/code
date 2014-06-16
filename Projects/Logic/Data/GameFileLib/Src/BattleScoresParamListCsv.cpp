
/******************************************************************************/

#include "stdafx.h"
#include "BattleScoresParamListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	BattleScoresParamListCsv::BattleScoresParamListCsv()
	{

	}
	//--------------------------------------------------------------------------
	BattleScoresParamListCsv::~BattleScoresParamListCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool BattleScoresParamListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
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

			Int paramId = 0;
			MGStrOp::toI32(csvdata->mData[BPL_ParamId].c_str(), paramId);
			if (true == mBattleScoresParamList.hasData(paramId))
			{
                DEBUG_ASSERT_LOG(false, "true == mBattleScoresParamList.hasData(paramId)");
				continue;
			}

			BattleScoresParamListCsvInfo* newParamCsvInfo = mBattleScoresParamList.createOrRetrieve(paramId, false);
			newParamCsvInfo->paramId		= paramId;
			newParamCsvInfo->paramName		= csvdata->mData[BPL_ParamName];
			MGStrOp::toI32(csvdata->mData[BPL_ParamType].c_str(), (I32&)newParamCsvInfo->paramType);
			MGStrOp::toI32(csvdata->mData[BPL_ParamValue].c_str(), newParamCsvInfo->paramValue);
		}

		return true;
	}

	//--------------------------------------------------------------------------
	std::map<Int, BattleScoresParamListCsvInfo*>* BattleScoresParamListCsv::getBattleScoresParamList()
	{
		return mBattleScoresParamList.getDataSet();
	}

	//--------------------------------------------------------------------------

}