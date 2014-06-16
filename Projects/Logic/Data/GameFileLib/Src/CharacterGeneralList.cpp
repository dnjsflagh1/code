//**********************************************************************************************************************
#include "stdafx.h"
#include "CharacterGeneralList.h"
//**********************************************************************************************************************
namespace MG
{
	CharacterGenrealList::~CharacterGenrealList()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Bool CharacterGenrealList::loadFile( Str16 filename )
	{
		CsvReader csvreader;

		if(!csvreader.create(filename))
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

			tempCharInfo->SurName		    = csvdata->mData[nCol++].c_str();
			tempCharInfo->Name				= csvdata->mData[nCol++].c_str();
			tempCharInfo->ZhiName			= csvdata->mData[nCol++].c_str();
			tempCharInfo->Title				= csvdata->mData[nCol++].c_str();
			tempCharInfo->Tips				= csvdata->mData[nCol++].c_str();

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->GenderType		  );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->PowerfulType		  );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->RaceType			  );
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->FormulaType		  );

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->Level						);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->LineageLevel				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->AbilityRandomType	);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityAppendId1			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityAppendId2			); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityAppendId3			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityAppendId4			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityAppendId5			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AbilityAppendId6			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterSkillId1			); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterSkillId2			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->Age						);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->MinLifeSpan				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->MaxLifeSpan				);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->NatureId					); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterAppellationId		);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterDialogId			); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->OfficialLevelId			);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->TitleId					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtIconId1					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtIconId2					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId1					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId2					); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->ArtMashId3					);
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->WeaponAcction				); 
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->AudioResId					);


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