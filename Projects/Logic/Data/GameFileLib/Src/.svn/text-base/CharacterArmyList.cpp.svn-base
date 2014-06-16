//**********************************************************************************************************************
#include "stdafx.h"
#include "CharacterArmyList.h"
//**********************************************************************************************************************
namespace MG
{
	CharacterArmyList::~CharacterArmyList()
	{
		clear();
	}
	//----------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CharacterArmyList::loadFile( Str16 filename, IMGExternalPackManager* packManager/* = NULL */)
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

			CharacterArmyInfo* tempCharInfo = new CharacterArmyInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterArmyId);
			nCol++;
			tempCharInfo->ListName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->SurName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->Title				= csvdata->mData[nCol++].c_str();
			tempCharInfo->Tips				= csvdata->mData[nCol++].c_str();

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->ArmyType		);
			DYNAMIC_ASSERT(tempCharInfo->ArmyType> TROOPTEMPLATE_TYPE_NULL  &&  tempCharInfo->ArmyType < TROOPTEMPLATE_TYPE_MAX);

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->FormulaType		);
			DYNAMIC_ASSERT(tempCharInfo->FormulaType> CHAR_FORMULA_TYPE_NULL  &&  tempCharInfo->FormulaType < CHAR_FORMULA_TYPE_MAX);


			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->Level				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->LineageLevel		);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityInitId1		);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityInitId2		); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityInitId3		);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityAppendId	);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterSkillId	);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->InfluenceId		); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtIconId			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId1			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId2			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->FormationNumMax	); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->FormationListNum	);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->FormationCharacterNum);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ListNum			); 

			MGStrOp::toFlt(csvdata->mData[nCol++].c_str(), tempCharInfo->ArmyX				);
			tempCharInfo->ArmyX /= 10;
			MGStrOp::toFlt(csvdata->mData[nCol++].c_str(), tempCharInfo->ArmyY				);
			tempCharInfo->ArmyY /= 10;
	
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArmyNumMax			); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArmyLoyal			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArmyWeapon			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->State1				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->State2				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->State3				); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->State4				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterVisionEventListId	);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIBaseGroupId			); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIFightGroupId		);


			mMapCharacterArmyInfo[tempCharInfo->CharacterArmyId] = tempCharInfo;
		}

		return true;
	}
	//----------------------------------------------------------------------------------------------------
	const CharacterArmyInfo* CharacterArmyList::getCharacterArmyInfo( U32 id )
	{
		std::map<U32, CharacterArmyInfo*>::iterator iter = mMapCharacterArmyInfo.find(id);
		if ( mMapCharacterArmyInfo.end() != iter )
			return iter->second;

		return NULL;
	}
	//----------------------------------------------------------------------------------------------------
	void CharacterArmyList::clear()
	{
		std::map<U32, CharacterArmyInfo*>::iterator front = mMapCharacterArmyInfo.begin();
		std::map<U32, CharacterArmyInfo*>::iterator back = mMapCharacterArmyInfo.end();
		while (front != back)
		{
			delete front->second;

			++front;
		}

		mMapCharacterArmyInfo.clear();
	}
}