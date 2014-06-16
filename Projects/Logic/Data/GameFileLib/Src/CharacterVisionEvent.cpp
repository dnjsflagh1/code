//*****************************************************************************************************************
#include "stdafx.h"
#include "CharacterVisionEvent.h"
//*****************************************************************************************************************
namespace MG
{
	enum
	{	
		EVENTID,
		NOTE,
		EVENTTYPE,
		AUDIORESID,
		EFFECTRESID,
		ACTIONNAME,
		MODESIZE,
		MODECOLOR,

		CVE_MAX
	};

	CharacterVisionEvent::CharacterVisionEvent()
	{

	}
	//-------------------------------------------------------------------------------------------------

	CharacterVisionEvent::~CharacterVisionEvent()
	{
		clear();
	}

	//-------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	Bool CharacterVisionEvent::load( Str16 fileName, IMGExternalPackManager* packManager/* = NULL*/ )
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(fileName, packManager))
		{
			return false;
		}

		DYNAMIC_ASSERT(csvreader.getColumnSize() == CVE_MAX);

		CsvData* csvdata = NULL;
		Int RowCount = csvreader.count();

		for(int i = 0; i < RowCount; ++i)
		{
			csvdata = csvreader.findValue(i);
			if(!csvdata)
			{
				continue;
			}

			CharacterVisionEventInfo* tempInfo = new CharacterVisionEventInfo;
			MGStrOp::toU32(csvdata->mData[EVENTID].c_str(), tempInfo->characterVisionEventId);
			MGStrOp::toU32(csvdata->mData[AUDIORESID].c_str(), tempInfo->audioResId);
			MGStrOp::toU32(csvdata->mData[EFFECTRESID].c_str(), tempInfo->effectResId);
			tempInfo->actionName = csvdata->mData[ACTIONNAME].c_str();
			MGStrOp::toU32(csvdata->mData[MODESIZE].c_str(), tempInfo->ModleSize);
			tempInfo->ModleColor = csvdata->mData[MODECOLOR].c_str();

			mCharacterVisionEventInfoList[tempInfo->characterVisionEventId] = tempInfo;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	const CharacterVisionEventInfo* CharacterVisionEvent::getCharacterVisionEventInfo( U32 id )
	{
		std::map<UInt, CharacterVisionEventInfo*>::iterator it = mCharacterVisionEventInfoList.find(id);
		if(it == mCharacterVisionEventInfoList.end())
		{
			return NULL;
		}

		return it->second;
	}

	//-------------------------------------------------------------------------------------------------
	void CharacterVisionEvent::clear()
	{
		for(std::map<UInt, CharacterVisionEventInfo*>::iterator it = mCharacterVisionEventInfoList.begin(); it != mCharacterVisionEventInfoList.end(); ++it)
		{
			MG_SAFE_DELETE(it->second);
		}

		mCharacterVisionEventInfoList.clear();
	}


	//*********************************************************************************************************
	MG::Bool CharacterVisionEventInfo::getModleColor( ColorI& color )
	{
		if ( ModleColor.length() != 12 )
			return false;
		else
		{
			Str16 r,g,b,a;
			r = ModleColor.substr(0, 3);
			g = ModleColor.substr(3, 3);
			b = ModleColor.substr(6, 3);
			a = ModleColor.substr(9, 3);

			UInt tempColor = 0;
			MGStrOp::toU32(r.c_str(), tempColor);
			color.r = tempColor;
			MGStrOp::toU32(g.c_str(), tempColor);
			color.g = tempColor;
			MGStrOp::toU32(b.c_str(), tempColor);
			color.b = tempColor;
			MGStrOp::toU32(a.c_str(), tempColor);
			color.a = tempColor;
		}

		return true;
	}
	//-------------------------------------------------------
	MG::Bool CharacterVisionEventInfo::getModleSize( Flt& flt )
	{
		if ( ModleSize == 0 )
			return false;
		else
			flt = ModleSize/1000.f;

		return true;
	}
}