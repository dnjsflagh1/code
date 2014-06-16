/******************************************************************************/

#include "stdafx.h"
#include "GeneralRandomCsv.h"

/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	GeneralRandomCsv::GeneralRandomCsv()
	{

	}

	//--------------------------------------------------------------------------
	GeneralRandomCsv::~GeneralRandomCsv()
	{

	}

	//--------------------------------------------------------------------------
	Bool GeneralRandomCsv::load(const Char16* FileName, IMGExternalPackManager* packManager/* = NULL*/)
	{
		CsvReader csvreader;
		if(!csvreader.create(FileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == GeneralRandomCsvRow_Max);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(Int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}


			U32		GeneralRandomId = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRandomCsvRow_GeneralRandomId].c_str(), GeneralRandomId);
			if (true == mGeneralRandomList.hasData(GeneralRandomId))
			{
				DYNAMIC_ASSERT(0);
				continue;
			}


			U32		GeneralGroupID = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRandomCsvRow_GeneralGroupID].c_str(), GeneralGroupID);


			U32		CharacterId = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRandomCsvRow_CharacterTemplateId].c_str(), CharacterId);

			U32		GeneralRandomNum = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRandomCsvRow_GeneralRandomNum].c_str(), GeneralRandomNum);

			U32		AbilityInit1 = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRandomCsvRow_AbilityInit1].c_str(), AbilityInit1);

			U32		AbilityInit2 = 0;
			MGStrOp::toU32(csvdata->mData[GeneralRandomCsvRow_AbilityInit2].c_str(), AbilityInit2);

			Int		LifeSpanRandom = 0;
			MGStrOp::toI32(csvdata->mData[GeneralRandomCsvRow_LifeSpanRandom].c_str(), LifeSpanRandom);


			GeneralRandomCsvInfo* newInfo = mGeneralRandomList.createOrRetrieve(GeneralRandomId, false);
			newInfo->GeneralRandomId	= GeneralRandomId;
			newInfo->GeneralGroupID		= GeneralGroupID;
			newInfo->CharacterTemplateId		= CharacterId;
			newInfo->GeneralRandomNum	= GeneralRandomNum;
			newInfo->AbilityInit1		= AbilityInit1;
			newInfo->AbilityInit2		= AbilityInit2;
			newInfo->LifeSpanRandom		= LifeSpanRandom;
			std::vector<const GeneralRandomCsvInfo*>* groupList = & (mGeneralRandomByGroupId[GeneralGroupID]);
			groupList->push_back(newInfo);
		}

		return true;
	}

	//--------------------------------------------------------------------------
	GeneralRandomCsvInfo* GeneralRandomCsv::getInfoById(U32 id)
	{
		return mGeneralRandomList.getData(id);
	}

	std::vector<const GeneralRandomCsvInfo*>* GeneralRandomCsv::getRandomListByGeneralGroupId(U32 GeneralGroupId)
	{
		std::map<U32, std::vector<const GeneralRandomCsvInfo*> >::iterator iter = mGeneralRandomByGroupId.find(GeneralGroupId);
		if (iter != mGeneralRandomByGroupId.end())
		{
			return &(iter->second);
		}
		
		return NULL;
	}
	//--------------------------------------------------------------------------
	std::map<U32, GeneralRandomCsvInfo*>* GeneralRandomCsv::getList()
	{
		return mGeneralRandomList.getDataSet();
	}

}