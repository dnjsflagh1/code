/******************************************************************************/

#include "stdafx.h"
#include "InstanceAtkCampListCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	InstanceAtkCampListCsv::InstanceAtkCampListCsv()
	{

	}

	//--------------------------------------------------------------------------
	InstanceAtkCampListCsv::~InstanceAtkCampListCsv()
	{

	}

	//--------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool InstanceAtkCampListCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == InstancePVECampListCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			CampIdType campListId;
			MGStrOp::toU64(csvdata->mData[InstanceAtkCampListCsvRow_CampListId].c_str(), campListId);
			if (true == mInstanceAtkCampList.hasData(campListId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}


			CampIdType camp01;
			MGStrOp::toU64(csvdata->mData[InstancePVECampListCsvRow_CampId1].c_str(), camp01);

			CampIdType camp02;
			MGStrOp::toU64(csvdata->mData[InstancePVECampListCsvRow_CampId2].c_str(), camp02);

			CampIdType camp03;
			MGStrOp::toU64(csvdata->mData[InstancePVECampListCsvRow_CampId3].c_str(), camp03);

			CampIdType camp04;
			MGStrOp::toU64(csvdata->mData[InstancePVECampListCsvRow_CampId4].c_str(), camp04);

			CampIdType camp05;
			MGStrOp::toU64(csvdata->mData[InstancePVECampListCsvRow_CampId5].c_str(), camp05);



			InstanceAtkCampListCsvInfo* newInstanceAtkCampInfo	= mInstanceAtkCampList.createOrRetrieve(campListId, false);
			newInstanceAtkCampInfo->campListId	= campListId;
			newInstanceAtkCampInfo->camp[0]		= camp01;
			newInstanceAtkCampInfo->camp[1]		= camp02;
			newInstanceAtkCampInfo->camp[2]		= camp03;
			newInstanceAtkCampInfo->camp[3]		= camp04;
			newInstanceAtkCampInfo->camp[4]		= camp05;

		}

		return true;
	}

	//--------------------------------------------------------------------------
	InstanceAtkCampListCsvInfo* InstanceAtkCampListCsv::getInfoById(CampIdType campListId)
	{
		return mInstanceAtkCampList.getData(campListId);
	}

	//--------------------------------------------------------------------------
	std::map<InstanceIdType, InstanceAtkCampListCsvInfo*>* InstanceAtkCampListCsv::getList()
	{
		return mInstanceAtkCampList.getDataSet();
	}
}