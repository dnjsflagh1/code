//*****************************************************************************************************************
#include "stdafx.h"
#include "FightAITemplate.h"
//*****************************************************************************************************************
namespace MG
{
	enum
	{	
		AIFIGHTID,
		NOTES,
		PRIORITY,
		CONTACTTYPE,
		CONTACTPARAM1,
		CONTACTPARAM2,
		CONTACTPARAM3,
		CONTACTPARAM4,
		RANDOMNUM,
		CONTACTNUM,
		EVENTTYPE,
		EVENTPARAM1,
		EVENTPARAM2,
		EVENTPARAM3,
		EVENTPARAM4,
	};

	FightAITemplate::FightAITemplate()
	{

	}
	//-------------------------------------------------------------------------------------------------

	FightAITemplate::~FightAITemplate()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool FightAITemplate::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
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

			FightAIInfo* tempInfo = new FightAIInfo;

			MGStrOp::toU32(csvdata->mData[AIFIGHTID].c_str(), tempInfo->aiFightId);
			MGStrOp::toU32(csvdata->mData[PRIORITY].c_str(), tempInfo->priority);

			UInt tempContactType = 0;
			MGStrOp::toU32(csvdata->mData[CONTACTTYPE].c_str(), tempContactType);
			tempInfo->contactType = (ContactType)tempContactType;

			UInt tempContactCharacterType = 0;
			MGStrOp::toU32(csvdata->mData[CONTACTPARAM1].c_str(), tempContactCharacterType);
			tempInfo->contactParam1 = (ContactCharacterType)tempContactCharacterType;

			MGStrOp::toFlt(csvdata->mData[CONTACTPARAM2].c_str(), tempInfo->contactParam2);
			MGStrOp::toFlt(csvdata->mData[CONTACTPARAM3].c_str(), tempInfo->contactParam3);
			MGStrOp::toFlt(csvdata->mData[CONTACTPARAM4].c_str(), tempInfo->contactParam4);

			switch(tempInfo->contactType)
			{
			case CT_ContactType1:
			case CT_ContactType7:
			case CT_ContactType8:
				tempInfo->contactParam2 /= 10;
				break;
			}

			MGStrOp::toU32(csvdata->mData[RANDOMNUM].c_str(), tempInfo->randomNum);
			MGStrOp::toU32(csvdata->mData[CONTACTNUM].c_str(), tempInfo->contactNum);

			UInt tempEventType = 0;
			MGStrOp::toU32(csvdata->mData[EVENTTYPE].c_str(), tempEventType);
			tempInfo->eventType = (EventType)tempEventType;
			UInt tempEventCharacterType = 0;
			MGStrOp::toU32(csvdata->mData[EVENTPARAM1].c_str(), tempEventCharacterType);
			tempInfo->eventParam1 = (EventCharacterType)tempEventCharacterType;
			MGStrOp::toU32(csvdata->mData[EVENTPARAM2].c_str(), tempInfo->eventParam2);
			MGStrOp::toU32(csvdata->mData[EVENTPARAM3].c_str(), tempInfo->eventParam3);
			MGStrOp::toU32(csvdata->mData[EVENTPARAM4].c_str(), tempInfo->eventParam4);

			mFightAIInfoList[tempInfo->aiFightId] = tempInfo;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	const FightAIInfo* FightAITemplate::getFightTriggerInfo( U32 id )
	{
		std::map<UInt, FightAIInfo*>::iterator it = mFightAIInfoList.find(id);
		if(it == mFightAIInfoList.end())
		{
			return NULL;
		}

		return it->second;
	}

	//-------------------------------------------------------------------------------------------------
	void FightAITemplate::clear()
	{
		for(std::map<UInt, FightAIInfo*>::iterator it = mFightAIInfoList.begin(); it != mFightAIInfoList.end(); ++it)
		{
			MG_SAFE_DELETE(it->second);
		}

		mFightAIInfoList.clear();
	}


	//*********************************************************************************************************

}