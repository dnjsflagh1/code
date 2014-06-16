//**********************************************************************************************************************
#include "stdafx.h"
#include "CharacterList.h"
#include "CharacterArmyList.h"
#include "CharacterBuildList.h"
#include "CharacterGenrealList.h"
#include "CharacterNpcList.h"
#include "CharacterObjectList.h"
#include "CharacterMonsterList.h"
#include "DialogueVassal.h"
//**********************************************************************************************************************
namespace MG
{
	CharacterTemplate::~CharacterTemplate()
	{
		clear();
	}
	//-------------------------------------------------------------------------------------------------------
	// MG_CN_MODIFY
	MG::Bool CharacterTemplate::loadFile( Str16 filename, IMGExternalPackManager* packManager/* = NULL*/ )
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

			CharacterTempInfo* tempCharInfo = new CharacterTempInfo;
			UInt nCol = 0;

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterId);
			nCol++;
			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), (U32&)tempCharInfo->CharacterType			);

			MGStrOp::toU32(csvdata->mData[nCol++].c_str(), tempCharInfo->CharacterListId			);


			mMapCharacterTempInfoNew[tempCharInfo->CharacterId] = tempCharInfo;

			setTempInfo(tempCharInfo);
		}

		return true;
	}
	//-------------------------------------------------------------------------------------------------------
	CharacterTempInfo* CharacterTemplate::getCharacterTempInfo(U32 id)
	{
		std::map<U32, CharacterTempInfo*>::iterator iter = mMapCharacterTempInfoNew.find(id);
		if (mMapCharacterTempInfoNew.end() != iter)
			return iter->second;

		return NULL;
	}
	//-------------------------------------------------------------------------------------------------------
	void CharacterTemplate::clear()
	{
		std::map<U32, CharacterTempInfo*>::iterator front = mMapCharacterTempInfoNew.begin();
		std::map<U32, CharacterTempInfo*>::iterator back = mMapCharacterTempInfoNew.end();
		while (front != back)
		{
			delete front->second;
			++front;
		}
		mMapCharacterTempInfoNew.clear();
	}
	//-------------------------------------------------------------------------------------------------------
	void CharacterTemplate::setTempInfo( CharacterTempInfo* info )
	{
		switch (info->CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			info->mCharacterArmyInfo = CharacterArmyList::getInstance().getCharacterArmyInfo(info->CharacterListId);
			break;
		case CHARACTER_TYPE_BUILD:
			info->mCharacterBuildInfo = CharacterBuildList::getInstance().getCharacterBuildInfo(info->CharacterListId);
			break;
		case CHARACTER_TYPE_GENREAL:
			info->mCharacterGenrealInfo = CharacterGenrealList::getInstance().getCharacterGenrealInfo(info->CharacterListId);
			break;
		case CHARACTER_TYPE_MONSTER:
			info->mCharacterMonsterInfo = CharacterMonsterList::getInstance().getCharacterMonsterInfo(info->CharacterListId);
			break;
		case CHARACTER_TYPE_NPC:
			{
				
				info->mCharacterNpcInfo = CharacterNpcList::getInstance().getCharacterNpcInfo(info->CharacterListId);
				DialogueVassalInfo* dialogueVasInfo = DialogueVassal::getInstance().getDialogueVassalInfobyObjectId(info->CharacterId);
				if (NULL != dialogueVasInfo)
				{     
					  //0-7
				      const_cast<CharacterNpcInfo*>(info->mCharacterNpcInfo)->FunctionListId1 =  dialogueVasInfo->fuctionId[0];
					  const_cast<CharacterNpcInfo*>(info->mCharacterNpcInfo)->FunctionListId2 =  dialogueVasInfo->fuctionId[1];
					  const_cast<CharacterNpcInfo*>(info->mCharacterNpcInfo)->FunctionListId3 =  dialogueVasInfo->fuctionId[2];
					  const_cast<CharacterNpcInfo*>(info->mCharacterNpcInfo)->FunctionListId4 =  dialogueVasInfo->fuctionId[3];
					  const_cast<CharacterNpcInfo*>(info->mCharacterNpcInfo)->FunctionListId5 =  dialogueVasInfo->fuctionId[4];
					  const_cast<CharacterNpcInfo*>(info->mCharacterNpcInfo)->FunctionListId6 =  dialogueVasInfo->fuctionId[5];
					  const_cast<CharacterNpcInfo*>(info->mCharacterNpcInfo)->FunctionListId7 =  dialogueVasInfo->fuctionId[6];
					  const_cast<CharacterNpcInfo*>(info->mCharacterNpcInfo)->FunctionListId8 =  dialogueVasInfo->fuctionId[7];
				}
			}
			break;
		case CHARACTER_TYPE_OBJ:
			info->mCharacterObjectInfo = CharacterObjectList::getInstance().getCharacterObjectInfo(info->CharacterListId);
			break;
		default:
			break;
		}
	}

    std::map<U32, CharacterTempInfo*>& CharacterTemplate::getCharacterTempInfoList()
	{
             return mMapCharacterTempInfoNew;
	}
	//**********************************************************************************************************************
	CharacterTempInfo::CharacterTempInfo()
		:mCharacterGenrealInfo(NULL)	
		,mCharacterArmyInfo(NULL)	
		,mCharacterBuildInfo(NULL)		
		,mCharacterMonsterInfo(NULL)	
		,mCharacterNpcInfo(NULL)		
		,mCharacterObjectInfo(NULL)	
	{
		
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getCharacterArtIconId(  )const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->ArtIconId;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->ArtIconId;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->ArtIconId;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->ArtIconId;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->ArtIconId;
			break;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->ArtIconId;
			break;
		default:
			break;
		}

		return 0;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getCharacterArtMashId( int index /*= 0*/ )const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->ArtMashId1;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->ArtMashId1;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->getCharacterArtMashId(index);
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->ArtMashId;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->ArtMashId;
			break;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->ArtMashId;
			break;
		default:
			break;
		}

		return 0;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getCharacterTitle()const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->Title;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->Title;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->Title;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->Title;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->Title;
			break;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->Title;
			break;
		default:
			break;
		}

		return L"";
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getCharacterTips()const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->Tips;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->Tips;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->Tips;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->Tips;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->Tips;
			break;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->Tips;
			break;
		default:
			break;
		}

		return L"";
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getCharacterSurName()const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->SurName;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->SurName;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->SurName;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->SurName;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->SurName;
			break;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->SurName;
			break;
		default:
			break;
		}

		return L"";
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getCharacterListName()const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->ListName;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->ListName;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->ListName;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->ListName;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->ListName;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->ListName;
		default:
			break;
		}

		return L"";
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getCharacterLevel()const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->Level;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->Level;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->Level;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->Level;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->Level;
			break;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->Level;
			break;
		default:
			break;
		}

		return 0;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getCharacterAbilityAppendId( int index )const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->getCharacterAbilityAppendId(index);
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->getCharacterAbilityAppendId(index);
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->getCharacterAbilityAppendId(index);
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->getCharacterAbilityAppendId(index);
			break;
		default:
			break;
		}

		return 0;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getCharacterCharacterSkillId( int index )const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->CharacterSkillId;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->CharacterSkillId;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->getCharacterCharacterSkillId(index);
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->getCharacterCharacterSkillId(index);
			break;
		default:
			break;
		}

		return 0;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getCharacterLineageLevel()const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->LineageLevel;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->LineageLevel;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->LineageLevel;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->LineageLevel;
			break;
		default:
			break;
		}

		return 0;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::CHAR_FORMULA_TYPE CharacterTempInfo::getCharacterFormulaType()const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->FormulaType;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->FormulaType;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->FormulaType;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->FormulaType;
			break;
		default:
			break;
		}

		return CHAR_FORMULA_TYPE_NULL;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getCharacterInfluenceId()const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->InfluenceId;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->InfluenceId;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->InfluenceId;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->InfluenceId;
			break;
		default:
			break;
		}

		return 0;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Bool CharacterTempInfo::isValid() const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo != NULL;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo != NULL;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo != NULL;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo != NULL;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo != NULL;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo != NULL;
		default:
			break;
		}

		return false;
	}

	//-------------------------------------------------------------------------------------------------------
	UInt CharacterTempInfo::getAIBaseGroupId() const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->AIBaseGroupId;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->AIBaseGroupId;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->AIBaseGroupId;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->AIBaseGroupId;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->AIBaseGroupId;
			break;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->AIBaseGroupId;
			break;
		default:
			break;
		}

		return 0;
	}

	//-------------------------------------------------------------------------------------------------------
	UInt CharacterTempInfo::getAIFightGroupId() const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->AIFightGroupId;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->AIFightGroupId;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->AIFightGroupId;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->AIFightGroupId;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->AIFightGroupId;
			break;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->AIFightGroupId;
			break;
		default:
			break;
		}

		return 0;
	}

	U32	 CharacterTempInfo::getCharacterVisionEventListId() const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->CharacterVisionEventListId;
			break;
		case CHARACTER_TYPE_BUILD:
			return mCharacterBuildInfo->CharacterVisionEventListId;
			break;
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->CharacterVisionEventListId;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->CharacterVisionEventListId;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->CharacterVisionEventListId;
			break;
		case CHARACTER_TYPE_OBJ:
			return mCharacterObjectInfo->CharacterVisionEventListId;
			break;
		default:
			break;
		}

		return 0;
	}

	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getGenrealName()const
	{
		return mCharacterGenrealInfo->Name;	
	}
	//-------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------
	MG::GENDER_TYPE CharacterTempInfo::getGenrealGenderType()const
	{
		return mCharacterGenrealInfo->GenderType;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::POWERFUL_TYPE CharacterTempInfo::getGenrealPowerfulType()const
	{
		return mCharacterGenrealInfo->PowerfulType;
	}
	//-------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getGenrealAge()const
	{
		return mCharacterGenrealInfo->Age;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getGenrealMinLifeSpan()const
	{
		return mCharacterGenrealInfo->MinLifeSpan;
	}
	//-------------------------------------------------------------------------------------------------------
	/*MG::U32 CharacterTempInfo::getGenrealMaxLifeSpan()const
	{
		return mCharacterGenrealInfo->MaxLifeSpan;
	}*/
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getGenrealNatureId()const
	{
		return mCharacterGenrealInfo->NatureId; 
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getGenrealCharacterAppellationId()const
	{
		return mCharacterGenrealInfo->CharacterAppellationId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getGenrealCharacterDialogId()const
	{
		return mCharacterGenrealInfo->CharacterDialogId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getGenrealWeaponAcction()const
	{
		return mCharacterGenrealInfo->WeaponAcction;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getGenrealAudioResId()const
	{
		return mCharacterGenrealInfo->CharacterVisionEventListId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::TROOPTEMPLATE_TYPE CharacterTempInfo::getArmyArmyType()const
	{
		return mCharacterArmyInfo->ArmyType;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getFormationNumMax()const
	{
		return mCharacterArmyInfo->FormationNumMax;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getArmyArmyNumMax()const
	{
		return mCharacterArmyInfo->ArmyNumMax;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getFormationListNum()const
	{
		return mCharacterArmyInfo->FormationListNum;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getFormationCharacterNum()const
	{
		return mCharacterArmyInfo->FormationCharacterNum;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getArmyArmyX()const
	{
		return mCharacterArmyInfo->ArmyX;
	}		
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getArmyArmyY()const
	{
		return mCharacterArmyInfo->ArmyY;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getArmyListNum()const
	{
		return mCharacterArmyInfo->ListNum;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getArmyArmyLoyal()const
	{
		return mCharacterArmyInfo->ArmyLoyal;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getArmyArmyWeapon()const
	{
		return mCharacterArmyInfo->ArmyWeapon;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getArmyState( int index )const
	{
		return mCharacterArmyInfo->getArmyState(index);
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32	 CharacterTempInfo::getArmyCollisionMeshId()const
	{
		return mCharacterArmyInfo->ArtMashId2;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getBuildAudioResId()const
	{
		return mCharacterBuildInfo->CharacterVisionEventListId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getBuildArtMashId2()const
	{
		return mCharacterBuildInfo->ArtMashId2;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getBuildMapListId()const
	{
		return mCharacterBuildInfo->MapListId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getBuildDestroyScript()const
	{
		return mCharacterBuildInfo->DestroyScript;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getMonsterName()const
	{
		return mCharacterMonsterInfo->Name;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getMonsterSuiName() const
	{
         return mCharacterMonsterInfo->SurName;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::GENDER_TYPE CharacterTempInfo::getMonsterGenderType()const
	{
		return mCharacterMonsterInfo->GenderType;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::POWERFUL_TYPE CharacterTempInfo::getMonsterPowerfulType()const
	{
		return mCharacterMonsterInfo->PowerfulType;
	}
	//-------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getMonsterCharacterAppellationId()const
	{
		return mCharacterMonsterInfo->CharacterAppellationId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getMonsterCharacterDialogId()const
	{
		return mCharacterMonsterInfo->CharacterDialogId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getMonsterAudioResId()const
	{
		return mCharacterMonsterInfo->CharacterVisionEventListId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getMonsterItemGroupId()const
	{
		return mCharacterMonsterInfo->ItemGroupId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Byte CharacterTempInfo::getMonsterNameColorType() const
	{
       return mCharacterMonsterInfo->nameColor;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getNpcName()const
	{
		return mCharacterNpcInfo->Name;
	}
	//-------------------------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------------
	MG::GENDER_TYPE CharacterTempInfo::getNpcGenderType()const
	{
		return mCharacterNpcInfo->GenderType;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getNpcCharacterAppellationId()const
	{
		return mCharacterNpcInfo->CharacterAppellationId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getNpcCharacterDialogId()const
	{
		return mCharacterNpcInfo->CharacterDialogId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getNpcArtEffectId()const
	{
		return mCharacterNpcInfo->ArtEffectId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getNpcAudioResId()const
	{
		return mCharacterNpcInfo->CharacterVisionEventListId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getNpcFunctionListId( int index )const
	{
		return mCharacterNpcInfo->getNpcFunctionListId(index);
	}		
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getObjectAudioResId()const
	{
		return mCharacterObjectInfo->CharacterVisionEventListId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::CHARACTER_OBJ_MUTUALTYPE CharacterTempInfo::getObjectMutualType()const
	{
		return mCharacterObjectInfo->MutualType;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getObjectMutualAction()const
	{
		return mCharacterObjectInfo->MutualAction;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getObjectMutualTime()const
	{
		return mCharacterObjectInfo->MutualTime;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getObjectMutualItemGroup()const
	{
		return mCharacterObjectInfo->MutualItemGroup;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::U32 CharacterTempInfo::getObjectMutualEffectId()const
	{
		return mCharacterObjectInfo->MutualEffectId;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getObjectMutualScript()const
	{
		return mCharacterObjectInfo->MutualScript;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::CHAR_BUILD_TYPE CharacterTempInfo::getBuildType() const
	{
		return mCharacterBuildInfo->BuildType;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::Str16 CharacterTempInfo::getNpcSuiName() const
	{
        return mCharacterNpcInfo->SurName;
	}
	//-------------------------------------------------------------------------------------------------------
	MG::GENDER_TYPE CharacterTempInfo::getCharacterGenderType() const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_GENREAL:
			return mCharacterGenrealInfo->GenderType;
			break;
		case CHARACTER_TYPE_MONSTER:
			return mCharacterMonsterInfo->GenderType;
			break;
		case CHARACTER_TYPE_NPC:
			return mCharacterNpcInfo->GenderType;
			break;
		default:
			return GENDER_TYPE_NONE_SEX;
			break;
		}
	}
	//-------------------------------------------------------------------------------------------------------
	MG::TROOPTEMPLATE_TYPE CharacterTempInfo::getCharacterArmyType() const
	{
		switch (CharacterType)
		{
		case CHARACTER_TYPE_ARMY:
			return mCharacterArmyInfo->ArmyType;
			break;
		default:
			return TROOPTEMPLATE_TYPE_OTHER;
			break;
		}
	}

}