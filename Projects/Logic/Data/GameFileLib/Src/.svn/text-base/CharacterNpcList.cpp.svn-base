//**********************************************************************************************************************
#include "stdafx.h"
#include "CharacterNpcList.h"
//**********************************************************************************************************************
namespace MG
{
	CharacterNpcList::~CharacterNpcList()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CharacterNpcList::loadFile( Str16 filename, IMGExternalPackManager* packManager/* = NULL*/ )
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

			CharacterNpcInfo* tempCharInfo = new CharacterNpcInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterNpcId);
			nCol++;
			tempCharInfo->ListName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->SurName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->Name				= csvdata->mData[nCol++].c_str();
			tempCharInfo->Title				= csvdata->mData[nCol++].c_str();
			tempCharInfo->Tips				= csvdata->mData[nCol++].c_str();

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->GenderType   );
			DYNAMIC_ASSERT(tempCharInfo->GenderType < GENDER_TYPE_MAX  &&  tempCharInfo->GenderType > GENDER_TYPE_NULL);

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->Level						);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterAppellationId		);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterDialogId			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIId						);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->InfluenceId				); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtIconId					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtEffectId				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterVisionEventListId	); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIBaseGroupId				); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIFightGroupId				);

			mMapCharacterNpcInfo[tempCharInfo->CharacterNpcId] = tempCharInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------------------
	const CharacterNpcInfo* CharacterNpcList::getCharacterNpcInfo( U32 id )
	{
		std::map<U32, CharacterNpcInfo*>::iterator iter = mMapCharacterNpcInfo.find(id);
		if (iter != mMapCharacterNpcInfo.end())
			return iter->second;

		return NULL;
	}
	//-------------------------------------------------------------------------------------------------------
	void CharacterNpcList::clear()
	{
		std::map<U32, CharacterNpcInfo*>::iterator front = mMapCharacterNpcInfo.begin();
		std::map<U32, CharacterNpcInfo*>::iterator back = mMapCharacterNpcInfo.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}
		mMapCharacterNpcInfo.clear();
	}
}