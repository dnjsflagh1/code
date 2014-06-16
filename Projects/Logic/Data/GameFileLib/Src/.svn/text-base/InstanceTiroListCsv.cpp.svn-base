/******************************************************************************/

#include "stdafx.h"
#include "InstanceTiroListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	InstanceTiroListCsv::InstanceTiroListCsv()
	{

	}

	//--------------------------------------------------------------------------
	InstanceTiroListCsv::~InstanceTiroListCsv()
	{

	}

	//--------------------------------------------------------------------------
	Bool InstanceTiroListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;

		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == InstanceTiroRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			InstanceIdType instanceTiroId;
			MGStrOp::toU32(csvdata->mData[InstanceTiroRow_InstanceTiroId].c_str(), instanceTiroId);
			if (true == mInstanceTiroList.hasData(instanceTiroId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int characterMaxNum = 0;
			MGStrOp::toI32(csvdata->mData[InstanceTiroRow_CharacterMaxNum].c_str(), characterMaxNum);

			Int newNum = 0;
			MGStrOp::toI32(csvdata->mData[InstanceTiroRow_NewNum].c_str(), newNum);

			QuestIdType questId = 0;
			MGStrOp::toI32(csvdata->mData[InstanceTiroRow_QuestId].c_str(), questId);

			MapIdType mapListId = 0;
			MGStrOp::toU32(csvdata->mData[InstanceTiroRow_mapListId].c_str(), mapListId);
			
			InstanceTiroListCsvInfo* newInstanceTiroInfo	= mInstanceTiroList.createOrRetrieve(instanceTiroId, false);
			newInstanceTiroInfo->instanceTiroId		= instanceTiroId;
			newInstanceTiroInfo->characterMaxNum	= characterMaxNum;
			newInstanceTiroInfo->newNum				= newNum;
			newInstanceTiroInfo->questId			= questId;
			newInstanceTiroInfo->mapListId			= mapListId;
			DYNAMIC_ASSERT(mapListId > 0);
			DYNAMIC_ASSERT(characterMaxNum >= newNum);
		}

		return true;
	}

	//--------------------------------------------------------------------------
	InstanceTiroListCsvInfo* InstanceTiroListCsv::getInfoById(InstanceIdType id)
	{
		return mInstanceTiroList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<InstanceIdType, InstanceTiroListCsvInfo*>* InstanceTiroListCsv::getList()
	{
		return mInstanceTiroList.getDataSet();
	}
}