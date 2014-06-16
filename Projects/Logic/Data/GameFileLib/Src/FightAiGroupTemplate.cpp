//*****************************************************************************************************************
#include "stdafx.h"
#include "FightAiGroupTemplate.h"
//*****************************************************************************************************************
namespace MG
{
	enum
	{	
		AIFIGHTGROUPID,
		NOTES,
		AIFIGHTID1,
		AIFIGHTID2,
		AIFIGHTID3,
		AIFIGHTID4,
		AIFIGHTID5,
		AIFIGHTID6,
		AIFIGHTID7,
		AIFIGHTID8,
		AIFIGHTID9,
		AIFIGHTID10,
		AIFIGHTID11,
		AIFIGHTID12,
		AIFIGHTID13,
		AIFIGHTID14,
		AIFIGHTID15,
		AIFIGHTID16,
	};

	FightAIGroupTemplate::FightAIGroupTemplate()
	{

	}
	//-------------------------------------------------------------------------------------------------

	FightAIGroupTemplate::~FightAIGroupTemplate()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool FightAIGroupTemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			FightAIGroup* tempGroup = new FightAIGroup;

			MGStrOp::toU32(csvdata->mData[AIFIGHTGROUPID].c_str(), tempGroup->aiFightGroupId);

			UInt aiId = 0;
			const FightAIInfo* fightAIInfo = NULL;

			for(UInt i = AIFIGHTID1; i < AIFIGHTID16 + 1; ++i)
			{
				MGStrOp::toU32(csvdata->mData[i].c_str(), aiId);
				if(aiId == 0)
				{
					continue;
				}

				fightAIInfo = FightAITemplate::getInstance().getFightTriggerInfo(aiId);
				if(!fightAIInfo)
				{
					continue;
				}

				tempGroup->aiFightAIInfoList.push_back((FightAIInfo*)fightAIInfo);
			}
			

			mFightAIGroupList[tempGroup->aiFightGroupId] = tempGroup;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	void FightAIGroupTemplate::clear()
	{
		for(std::map<UInt, FightAIGroup*>::iterator it = mFightAIGroupList.begin(); it != mFightAIGroupList.end(); ++it)
		{
			MG_SAFE_DELETE(it->second);
		}

		mFightAIGroupList.clear();
	}

	//-------------------------------------------------------------------------------------------------
	const FightAIGroup* FightAIGroupTemplate::getFightAIGroup( UInt groupId )
	{
		std::map<UInt, FightAIGroup*>::iterator it = mFightAIGroupList.find(groupId);
		if(it == mFightAIGroupList.end())
		{
			return NULL;
		}

		return it->second;
	}


	//*********************************************************************************************************

}