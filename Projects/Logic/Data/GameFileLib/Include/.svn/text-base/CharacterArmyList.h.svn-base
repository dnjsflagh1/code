//**********************************************************************************************************************
#ifndef _H_CHARACTERARMYLIST_
#define _H_CHARACTERARMYLIST_
//**********************************************************************************************************************
#include "GameFilePreqs.h"
//**********************************************************************************************************************
namespace MG
{
	struct CharacterArmyInfo
	{
		U32					CharacterArmyId				;
		Str16				ListName					;
		Str16				SurName						;
		Str16				Title						;
		Str16				Tips						;
		TROOPTEMPLATE_TYPE	ArmyType					;
		CHAR_FORMULA_TYPE	FormulaType					;
		U32					Level						;
		U32					LineageLevel				;
		U32					AbilityInitId1				;
		U32					AbilityInitId2				;
		U32					AbilityInitId3				;
		U32					AbilityAppendId				;
		U32					CharacterSkillId			;
		U32					InfluenceId					;
		U32					ArtIconId					;
		U32					ArtMashId1					;
		U32					ArtMashId2					;
		U32					FormationNumMax				;
		U32					FormationListNum			;
		U32					FormationCharacterNum		;
		U32					ListNum						;
		Flt					ArmyX						;
		Flt					ArmyY						;
		U32					ArmyNumMax					;
		U32					ArmyLoyal					;
		U32					ArmyWeapon					;
		U32					State1						;
		U32					State2						;
		U32					State3						;
		U32					State4						;
		U32					CharacterVisionEventListId	;
		UInt				AIBaseGroupId				;
		UInt				AIFightGroupId				;	

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
				break;
			}
			return 0;
		}
		//------------------------------------------------------------------
		U32					getArmyState(int index)const
		{
			switch (index)
			{
			case 0:
				return State1;
				break;
			case 1:
				return State2;
				break;
			case 2:
				return State3;
				break;
			case 3:
				return State4;
				break;
			default:
				break;
			}
			return 0;
		}
	};

	//=-------------------------------------------------------------------------------------------------
	class CharacterArmyList
	{
	public:
		CharacterArmyList(){;}
		~CharacterArmyList();
		SINGLETON_INSTANCE(CharacterArmyList);

	public:
		// MG_CN_MODIFY
		Bool							loadFile(Str16 filename, IMGExternalPackManager* packManager = NULL);
		const CharacterArmyInfo*		getCharacterArmyInfo(U32 id);

	private:
		void							clear();

	private:
		std::map<U32, CharacterArmyInfo*>			mMapCharacterArmyInfo;

	};
}
//**********************************************************************************************************************
#endif
//**********************************************************************************************************************