//**********************************************************************************************************************
#include "stdafx.h"
#include "CharacterObjectList.h"
//**********************************************************************************************************************
namespace MG
{
	CharacterObjectList::~CharacterObjectList()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CharacterObjectList::loadFile( Str16 filename, IMGExternalPackManager* packManager/* = NULL*/ )
	{
		CsvReader csvreader;
		// MG_CN_MODIFY
		if(!csvreader.create(filename, packManager))
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

			CharacterObjectInfo* tempCharInfo = new CharacterObjectInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterObjectId);
			nCol++;
			tempCharInfo->ListName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->SurName	     = csvdata->mData[nCol++].c_str();
			tempCharInfo->Title	     = csvdata->mData[nCol++].c_str();
			tempCharInfo->Tips	     = csvdata->mData[nCol++].c_str();

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->Level			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtIconId		);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId		);
			
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->MutualType   );
			DYNAMIC_ASSERT(tempCharInfo->MutualType < CHARACTER_OBJ_MUTUALTYPE_MAX);

			tempCharInfo->MutualAction	     = csvdata->mData[nCol++].c_str();

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->MutualTime		 );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->MutualItemGroup );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->MutualEffectId	 );

			tempCharInfo->MutualScript = csvdata->mData[nCol++].c_str();

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterVisionEventListId		); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIBaseGroupId		 ); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIFightGroupId	 );


			tempCharInfo->MutualScript	     = csvdata->mData[nCol++].c_str();

			mMapCharacterObjectInfo[tempCharInfo->CharacterObjectId] = tempCharInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------------------
	const CharacterObjectInfo* CharacterObjectList::getCharacterObjectInfo( U32 id )
	{
		std::map<U32, CharacterObjectInfo*>::iterator iter = mMapCharacterObjectInfo.find(id);
		if ( iter != mMapCharacterObjectInfo.end() )
			return iter->second;

		return NULL;
	}
	//-------------------------------------------------------------------------------------------------------
	void CharacterObjectList::clear()
	{
		std::map<U32, CharacterObjectInfo*>::iterator front = mMapCharacterObjectInfo.begin();
		std::map<U32, CharacterObjectInfo*>::iterator back = mMapCharacterObjectInfo.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}
		mMapCharacterObjectInfo.clear();
	}
}