//*****************************************************************************************************************
#include "stdafx.h"
#include "CharacterVisionEventList.h"
//*****************************************************************************************************************
namespace MG
{
	enum
	{	
		CHARACTEREVENTLISTID,
		NOTE,
		UPGRADEID,
		REINCARNATIONID,
		DIEDID,
		REBIRTHID,
	};

	CharacterVisionEventList::CharacterVisionEventList()
	{

	}
	//-------------------------------------------------------------------------------------------------

	CharacterVisionEventList::~CharacterVisionEventList()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool CharacterVisionEventList::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
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

			CharacterVisionEventListInfo* tempInfo = new CharacterVisionEventListInfo;

			MGStrOp::toU32(csvdata->mData[CHARACTEREVENTLISTID].c_str(), tempInfo->characterVisionEventListId);
			MGStrOp::toU32(csvdata->mData[UPGRADEID].c_str(), tempInfo->upgradeId);
			MGStrOp::toU32(csvdata->mData[REINCARNATIONID].c_str(), tempInfo->reincarnationId);
			MGStrOp::toU32(csvdata->mData[DIEDID].c_str(), tempInfo->diedId);
			MGStrOp::toU32(csvdata->mData[REBIRTHID].c_str(), tempInfo->rebirthId);

			mCharacterEventListInfoList[tempInfo->characterVisionEventListId] = tempInfo;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	const CharacterVisionEventListInfo* CharacterVisionEventList::getCharacterVisionEventListInfo( U32 id )
	{
		std::map<UInt, CharacterVisionEventListInfo*>::iterator it = mCharacterEventListInfoList.find(id);
		if(it == mCharacterEventListInfoList.end())
		{
			return NULL;
		}

		return it->second;
	}

	//-------------------------------------------------------------------------------------------------
	void CharacterVisionEventList::clear()
	{
		for(std::map<UInt, CharacterVisionEventListInfo*>::iterator it = mCharacterEventListInfoList.begin(); it != mCharacterEventListInfoList.end(); ++it)
		{
			MG_SAFE_DELETE(it->second);
		}

		mCharacterEventListInfoList.clear();
	}


	//*********************************************************************************************************

}