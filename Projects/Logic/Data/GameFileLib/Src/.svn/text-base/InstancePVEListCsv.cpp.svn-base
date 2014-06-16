/******************************************************************************/

#include "stdafx.h"
#include "InstancePVEListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	InstancePVEListCsv::InstancePVEListCsv()
	{

	}
	//--------------------------------------------------------------------------
	InstancePVEListCsv::~InstancePVEListCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool InstancePVEListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		DYNAMIC_ASSERT(csvreader.getColumnSize() == InstancePVEListCsvRow_Max);
		
		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			InstanceIdType instancePVEId;
			MGStrOp::toU32(csvdata->mData[InstancePVEListCsvRow_InstancePVEId].c_str(), instancePVEId);
			if (true == mInstancePVEList.hasData(instancePVEId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int finishCharacter = 0;
			MGStrOp::toI32(csvdata->mData[InstancePVEListCsvRow_FinishCharacter].c_str(), finishCharacter);

			Int itemGroupId = 0;
			MGStrOp::toI32(csvdata->mData[InstancePVEListCsvRow_ItemGroupId].c_str(), itemGroupId);

			MapIdType mapListId = 0;
			MGStrOp::toU32(csvdata->mData[InstancePVEListCsvRow_MapListId].c_str(), mapListId);

			InstancePVEListCsvInfo* newInstancePVEInfo	= mInstancePVEList.createOrRetrieve(instancePVEId, false);
			newInstancePVEInfo->instancePVEId		= instancePVEId;
			newInstancePVEInfo->finishCharacter		= finishCharacter;
			newInstancePVEInfo->itemGroupId			= itemGroupId;
			newInstancePVEInfo->mapListId			= mapListId;

		}

		return true;
	}

	//--------------------------------------------------------------------------
	InstancePVEListCsvInfo* InstancePVEListCsv::getInfoById(InstanceIdType id)
	{
		return mInstancePVEList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<InstanceIdType, InstancePVEListCsvInfo*>* InstancePVEListCsv::getList()
	{
		return mInstancePVEList.getDataSet();
	}
}