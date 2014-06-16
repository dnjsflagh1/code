//**********************************************************************************************************************
#include "stdafx.h"
#include "CharacterBuildList.h"
//**********************************************************************************************************************
namespace MG
{
	CharacterBuildList::~CharacterBuildList()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CharacterBuildList::loadFile( Str16 filename , IMGExternalPackManager* packManager/* = NULL*/)
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

			CharacterBuildInfo* tempCharInfo = new CharacterBuildInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterBuildId);
			nCol++;
			tempCharInfo->ListName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->SurName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->Title				= csvdata->mData[nCol++].c_str();
			tempCharInfo->Tips				= csvdata->mData[nCol++].c_str();
            
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->BuildType	);
			DYNAMIC_ASSERT(tempCharInfo->BuildType> CHAR_BUILD_TYPE_NULL  &&  tempCharInfo->BuildType < CHAR_BUILD_TYPE_MAX);

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
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->MapListId			);
			tempCharInfo->DestroyScript				= csvdata->mData[nCol++].c_str();

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterVisionEventListId			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIBaseGroupId		); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AIFightGroupId		);

			mMapCharacterBuildInfo[tempCharInfo->CharacterBuildId] = tempCharInfo;
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------------------
	const CharacterBuildInfo* CharacterBuildList::getCharacterBuildInfo( U32 id )
	{
		std::map<U32, CharacterBuildInfo*>::iterator iter = mMapCharacterBuildInfo.find(id);
		if ( iter != mMapCharacterBuildInfo.end() )
			return iter->second;

		return NULL;
	}
	//-------------------------------------------------------------------------------------------------------
	void CharacterBuildList::clear()
	{
		std::map<U32, CharacterBuildInfo*>::iterator front = mMapCharacterBuildInfo.begin();
		std::map<U32, CharacterBuildInfo*>::iterator back = mMapCharacterBuildInfo.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}
		mMapCharacterBuildInfo.clear();
	}
}