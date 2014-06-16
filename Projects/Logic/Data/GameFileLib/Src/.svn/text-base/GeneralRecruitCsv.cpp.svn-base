/******************************************************************************/

#include "stdafx.h"
#include "GeneralRecruitCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	GeneralRecruitCsv::GeneralRecruitCsv()
	{

	}

	//--------------------------------------------------------------------------
	GeneralRecruitCsv::~GeneralRecruitCsv()
	{

	}

	//--------------------------------------------------------------------------
	Bool GeneralRecruitCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == GeneralRecruitCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			
			U32		GeneralRecruitID = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRecruitCsvRow_GeneralRecruitID].c_str(), GeneralRecruitID);
			if (true == mGeneralRecruitList.hasData(GeneralRecruitID))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}

			
			U32		GeneralGroupID1 = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRecruitCsvRow_GeneralGroupID1].c_str(), GeneralGroupID1);


			U32		GeneralGroupID2 = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRecruitCsvRow_GeneralGroupID2].c_str(), GeneralGroupID2);


			U32		GeneralGroupID3 = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRecruitCsvRow_GeneralGroupID3].c_str(), GeneralGroupID3);


			U32		GeneralGroupID4 = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRecruitCsvRow_GeneralGroupID4].c_str(), GeneralGroupID4);


			U32		GeneralGroupID5 = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRecruitCsvRow_GeneralGroupID5].c_str(), GeneralGroupID5);


			U32		GeneralGroupID6 = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRecruitCsvRow_GeneralGroupID6].c_str(), GeneralGroupID6);

			GeneralRecruitCsvInfo* newInfo = mGeneralRecruitList.createOrRetrieve(GeneralRecruitID, false);
			newInfo->GeneralRecruitID		= GeneralRecruitID;
			newInfo->GeneralGroupID[0]		= GeneralGroupID1;
			newInfo->GeneralGroupID[1]		= GeneralGroupID2;
			newInfo->GeneralGroupID[2]		= GeneralGroupID3;
			newInfo->GeneralGroupID[3]		= GeneralGroupID4;
			newInfo->GeneralGroupID[4]		= GeneralGroupID5;
			//newInfo->GeneralGroupID		= GeneralGroupID6;

		}

		return true;
	}

	//--------------------------------------------------------------------------
	GeneralRecruitCsvInfo* GeneralRecruitCsv::getInfoById(U32 id)
	{
		return mGeneralRecruitList.getData(id);
	}

	//--------------------------------------------------------------------------
	std::map<U32, GeneralRecruitCsvInfo*>* GeneralRecruitCsv::getList()
	{
		return mGeneralRecruitList.getDataSet();
	}

}