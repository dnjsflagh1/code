//**********************************************************************************************************************
#ifndef _H_CHARACTERMONSTERLIST_
#define _H_CHARACTERMONSTERLIST_
//**********************************************************************************************************************
#include "GameFilePreqs.h"
//**********************************************************************************************************************
namespace MG
{
	struct CharacterMonsterInfo
	{
		U32						CharacterMonsterId			;
		Str16					ListName					;
		Str16					SurName						;
		Str16					Name						;
		Byte                    nameColor                   ;
		Str16					Title						;
		Str16					Tips						;
		GENDER_TYPE				GenderType					;
		POWERFUL_TYPE			PowerfulType				;
		CHAR_FORMULA_TYPE		FormulaType					;
		U32						Level						;
		U32						LineageLevel				;
		U32						AbilityInitId1				;
		U32						AbilityInitId2				;
		U32						AbilityInitId3				;
		U32						AbilityAppendId				;
		U32						CharacterSkillId1			;
		U32						CharacterSkillId2			;
		U32						CharacterAppellationId		;
		U32						CharacterDialogId			;
		U32						InfluenceId					;
		U32						ArtIconId					;
		U32						ArtMashId					;
		U32						ItemGroupId					;
		U32						CharacterVisionEventListId	;		
		UInt					AIBaseGroupId				;
		UInt					AIFightGroupId				;

		//------------------------------------------------------------------
		U32					getCharacterAbilityAppendId(int index)const
		{
			switch (index)
			{
			case 0:
				return AbilityInitId1;
				break;
			case 1:
				return AbilityInitId2;
				break;
			case 2:
				return AbilityInitId3;
				break;
			case 3:
				return AbilityAppendId;
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}
			return 0;
		}
		//------------------------------------------------------------------
		U32					getCharacterCharacterSkillId(int index)const
		{
			switch (index)
			{
			case 0:
				return CharacterSkillId1;
				break;
			case 1:
				return CharacterSkillId2;
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}

			return 0;
		}
	};

	//=-------------------------------------------------------------------------------------------------
	class CharacterMonsterList
	{
	public:
		CharacterMonsterList(){;}
		~CharacterMonsterList();
		SINGLETON_INSTANCE(CharacterMonsterList);

	public:
		// MG_CN_MODIFY
		Bool							loadFile(Str16 filename, IMGExternalPackManager* packManager = NULL);
		const CharacterMonsterInfo*		getCharacterMonsterInfo(U32 id);

	private:
		void							clear();

	private:
		std::map<U32, CharacterMonsterInfo*>			mMapCharacterMonsterInfo;

	};
}
//**********************************************************************************************************************
#endif
//**********************************************************************************************************************