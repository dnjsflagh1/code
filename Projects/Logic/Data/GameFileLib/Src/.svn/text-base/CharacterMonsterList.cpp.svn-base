//**********************************************************************************************************************
#include "stdafx.h"
#include "CharacterMonsterList.h"
//**********************************************************************************************************************
namespace MG
{
	CharacterMonsterList::~CharacterMonsterList()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CharacterMonsterList::loadFile( Str16 filename, IMGExternalPackManager* packManager/* = NULL*/ )
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

			CharacterMonsterInfo* tempCharInfo = new CharacterMonsterInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterMonsterId);
			nCol++;
			tempCharInfo->ListName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->SurName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->Name				= csvdata->mData[nCol++].c_str();
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(),(U32&)tempCharInfo->nameColor);
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

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityInitId1			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityInitId2			); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityInitId3			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityAppendId			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterSkillId1			); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterSkillId2			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterAppellationId		);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterDialogId			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->InfluenceId				); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtIconId					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ItemGroupId				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterVisionEventListId					); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIBaseGroupId				); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIFightGroupId				);

			mMapCharacterMonsterInfo[tempCharInfo->CharacterMonsterId] = tempCharInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------------------
	const CharacterMonsterInfo* CharacterMonsterList::getCharacterMonsterInfo( U32 id )
	{
		std::map<U32, CharacterMonsterInfo*>::iterator iter = mMapCharacterMonsterInfo.find(id);
		if ( mMapCharacterMonsterInfo.end() != iter )
			return iter->second;

		return NULL;
	}
	//-------------------------------------------------------------------------------------------------------
	void CharacterMonsterList::clear()
	{
		std::map<U32, CharacterMonsterInfo*>::iterator front = mMapCharacterMonsterInfo.begin();
		std::map<U32, CharacterMonsterInfo*>::iterator back = mMapCharacterMonsterInfo.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}
		mMapCharacterMonsterInfo.clear();
	}
}