/******************************************************************************/

#include "stdafx.h"
#include "InstanceTimeListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	InstanceTimeListCsv::InstanceTimeListCsv()
	{

	}

	//--------------------------------------------------------------------------
	InstanceTimeListCsv::~InstanceTimeListCsv()
	{

	}

	//--------------------------------------------------------------------------

	Bool InstanceTimeListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;

		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == InstanceTimeListCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			U32 instanceTimeId;
			MGStrOp::toU32(csvdata->mData[InstanceTimeListCsvRow_InstanceTimeId].c_str(), instanceTimeId);
			if (true == mInstanceTimeList.hasData(instanceTimeId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			
			I32 instanceType = 0;
			MGStrOp::toI32(csvdata->mData[InstanceTimeListCsvRow_InstanceType].c_str(), instanceType);

			U32 time1 = 0;
			MGStrOp::toU32(csvdata->mData[InstanceTimeListCsvRow_Time1].c_str(), time1);

			U32 time2 = 0;
			MGStrOp::toU32(csvdata->mData[InstanceTimeListCsvRow_Time2].c_str(), time2);

			U32 time3 = 0;
			MGStrOp::toU32(csvdata->mData[InstanceTimeListCsvRow_Time3].c_str(), time3);

			U32 time4 = 0;
			MGStrOp::toU32(csvdata->mData[InstanceTimeListCsvRow_Time4].c_str(), time4);

			U32 time5 = 0;
			MGStrOp::toU32(csvdata->mData[InstanceTimeListCsvRow_Time5].c_str(), time5);

			U32 time6 = 0;
			MGStrOp::toU32(csvdata->mData[InstanceTimeListCsvRow_Time6].c_str(), time6);

			InstanceTimeListCsvInfo* newInstanceTimeInfo	= mInstanceTimeList.createOrRetrieve(instanceTimeId, false);
			newInstanceTimeInfo->instanceTimeId	= instanceTimeId;
			newInstanceTimeInfo->instanceType	= (InstanceType)instanceType;
			newInstanceTimeInfo->time1			= time1 / 10;
			newInstanceTimeInfo->time2			= time2 / 10;
			newInstanceTimeInfo->time3			= time3 / 10;
			newInstanceTimeInfo->time4			= time4 / 10;
			newInstanceTimeInfo->time5			= time5 / 10;
			newInstanceTimeInfo->time6			= time6 / 10;
		}

		return true;
	}

	//--------------------------------------------------------------------------
	InstanceTimeListCsvInfo* InstanceTimeListCsv::getInfoById(U32 instanceTimeId)
	{
		return mInstanceTimeList.getData(instanceTimeId);
	}

	//--------------------------------------------------------------------------
	std::map<U32, InstanceTimeListCsvInfo*>* InstanceTimeListCsv::getList()
	{
		return mInstanceTimeList.getDataSet();
	}
}