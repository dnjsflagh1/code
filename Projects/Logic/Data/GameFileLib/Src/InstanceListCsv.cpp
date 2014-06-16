/******************************************************************************/

#include "stdafx.h"
#include "InstanceListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	InstanceListCsv::InstanceListCsv()
	{

	}

	//--------------------------------------------------------------------------
	InstanceListCsv::~InstanceListCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool InstanceListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == InstanceRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			InstanceIdType instanceId;
			MGStrOp::toU32(csvdata->mData[InstanceRow_InstanceId].c_str(), instanceId);
			if (true == mInstanceList.hasData(instanceId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			Int useType = -1;
			MGStrOp::toI32(csvdata->mData[InstanceRow_UseType].c_str(), useType);

			Int instanceType = -1;
			MGStrOp::toI32(csvdata->mData[InstanceRow_InstanceType].c_str(), instanceType);

			InstanceIdType instanceListId;
			MGStrOp::toU32(csvdata->mData[InstanceRow_InstanceListId].c_str(), instanceListId);

			InstanceListCsvInfo* newInstanceInfo = mInstanceList.createOrRetrieve(instanceId, false);
			newInstanceInfo->instanceId			= instanceId;
			newInstanceInfo->useType			= useType;
			newInstanceInfo->instanceType		= (InstanceType)instanceType;
			newInstanceInfo->instanceListId		= instanceListId;
		}

		return true;
	}

	//--------------------------------------------------------------------------
	InstanceListCsvInfo* InstanceListCsv::getInfoById(InstanceIdType id)
	{
		return mInstanceList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<InstanceIdType, InstanceListCsvInfo*>* InstanceListCsv::getList()
	{
		return mInstanceList.getDataSet();
	}

}