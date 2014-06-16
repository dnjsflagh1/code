//**********************************************************************************************************************
#include "stdafx.h"
#include "CharacterGenrealList.h"
//**********************************************************************************************************************
namespace MG
{
	CharacterGenrealList::~CharacterGenrealList()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CharacterGenrealList::loadFile( Str16 filename, IMGExternalPackManager* packManager/* = NULL*/ )
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

			CharacterGenrealInfo* tempCharInfo = new CharacterGenrealInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterGeneralId);
			nCol++;
			tempCharInfo->ListName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->SurName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->Name				= csvdata->mData[nCol++].c_str();
			tempCharInfo->Title				= csvdata->mData[nCol++].c_str();
			tempCharInfo->Tips				= csvdata->mData[nCol++].c_str();

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->GenderType		);
			DYNAMIC_ASSERT(tempCharInfo->GenderType> GENDER_TYPE_NULL  &&  tempCharInfo->GenderType < GENDER_TYPE_MAX);

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->PowerfulType		);
			DYNAMIC_ASSERT(tempCharInfo->PowerfulType> POWERFUL_TYPE_NULL  &&  tempCharInfo->PowerfulType < POWERFUL_TYPE_MAX);

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->FormulaType		);
			DYNAMIC_ASSERT(tempCharInfo->FormulaType> CHAR_FORMULA_TYPE_NULL  &&  tempCharInfo->FormulaType < CHAR_FORMULA_TYPE_MAX);


			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->Level						);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->LineageLevel				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityInitId1				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityInitId2				); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityInitId3				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityAppendId			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterSkillId1			); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterSkillId2			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->Age						);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->MinLifeSpan				);
			//MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->MaxLifeSpan				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->NatureId					); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterAppellationId		);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterDialogId			); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtIconId					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId1					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId2					); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId3					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->WeaponAcction				); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterVisionEventListId	);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIBaseGroupId				); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIFightGroupId				);


			mMapCharacterGenrealInfo[tempCharInfo->CharacterGeneralId] = tempCharInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------------------
	const CharacterGenrealInfo* CharacterGenrealList::getCharacterGenrealInfo( U32 id )
	{
		std::map<U32, CharacterGenrealInfo*>::iterator iter = mMapCharacterGenrealInfo.find(id);
		if ( mMapCharacterGenrealInfo.end() != iter )
			return iter->second;

		return NULL;
	}
	//-------------------------------------------------------------------------------------------------------
	void CharacterGenrealList::clear()
	{
		std::map<U32, CharacterGenrealInfo*>::iterator front = mMapCharacterGenrealInfo.begin();
		std::map<U32, CharacterGenrealInfo*>::iterator back = mMapCharacterGenrealInfo.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}

		mMapCharacterGenrealInfo.clear();
	}
}