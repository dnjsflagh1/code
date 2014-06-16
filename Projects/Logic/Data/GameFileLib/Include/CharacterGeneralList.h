//**********************************************************************************************************************
#ifndef _H_CHARACTERGENERALLIST_
#define _H_CHARACTERGENERALLIST_
//**********************************************************************************************************************
#include "GameFilePreqs.h"
//**********************************************************************************************************************
namespace MG
{
	struct CharacterGenrealInfo
	{
		U32					CharacterGeneralId			;
		Str16				SurName						;
		Str16				Name						;
		Str16				ZhiName						;
		Str16				Title						;
		Str16				Tips						;
		GENDER_TYPE			GenderType					;
		POWERFUL_TYPE		PowerfulType				;
		CHAR_RACE_TYPE		RaceType					;
		CHAR_FORMULA_TYPE	FormulaType					;
		U32					Level						;
		U32					LineageLevel				;
		CHAR_ATTRRAND_TYPE	AbilityRandomType			;
		U32					AbilityAppendId1			;
		U32					AbilityAppendId2			;
		U32					AbilityAppendId3			;
		U32					AbilityAppendId4			;
		U32					AbilityAppendId5			;
		U32					AbilityAppendId6			;
		U32					CharacterSkillId1			;
		U32					CharacterSkillId2			;
		U32					Age							;
		U32					MinLifeSpan					;
		U32					MaxLifeSpan					;
		U32					NatureId					;
		U32					CharacterAppellationId		;
		U32					CharacterDialogId			;
		U32					OfficialLevelId				;
		U32					TitleId						;
		U32					ArtIconId1					;
		U32					ArtIconId2					;
		U32					ArtMashId1					;
		U32					ArtMashId2					;
		U32					ArtMashId3					;
		U32					WeaponAcction				;
		U32					AudioResId					;
		//---------------------------------------------------------------------------
		U32					getCharacterArtIconId(int index)const
		{
			switch (index)
			{
			case 0:
				return ArtIconId1;
				break;
			case 1:
				return ArtIconId2;
				break;
			default:
				break;
			}

			return 0;
		}
		//------------------------------------------------------------------
		U32					getCharacterAbilityAppendId(int index)const
		{
			switch (index)
			{
			case 0:
				return AbilityAppendId1;
				break;
			case 1:
				return AbilityAppendId2;
				break;
			case 2:
				return AbilityAppendId3;
				break;
			case 3:
				return AbilityAppendId4;
				break;
			case 4:
				return AbilityAppendId5;
				break;
			case 5:
				return AbilityAppendId6;
				break;
			default:
				break;
			}
			return 0;
		}
		//------------------------------------------------------------------
		U32					getCharacterArtMashId(int index)const
		{
			switch (index)
			{
			case 0:
				return ArtMashId1;
				break;
			case 1:
				return ArtMashId2;
				break;
			case 2:
				return ArtMashId3;
				break;
			default:
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
				break;
			}

			return 0;
		}
	};

	//=-------------------------------------------------------------------------------------------------
	class CharacterGenrealList
	{
	public:
		CharacterGenrealList(){;}
		~CharacterGenrealList();
		SINGLETON_INSTANCE(CharacterGenrealList);

	public:
		Bool						loadFile(Str16 filename);
		const CharacterGenrealInfo*	getCharacterGenrealInfo(U32 id);

	private:
		void						clear();

	private:
		std::map<U32, CharacterGenrealInfo*>			mMapCharacterGenrealInfo;

	};
}
//**********************************************************************************************************************
#endif
//**********************************************************************************************************************