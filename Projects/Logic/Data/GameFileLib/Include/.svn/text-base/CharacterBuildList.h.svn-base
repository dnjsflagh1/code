//**********************************************************************************************************************
#ifndef _H_CHARACTERBUILDLIST_
#define _H_CHARACTERBUILDLIST_
//**********************************************************************************************************************
#include "GameFilePreqs.h"
//**********************************************************************************************************************
namespace MG
{
	struct CharacterBuildInfo
	{
		U32				CharacterBuildId	;
		Str16			ListName			;
		Str16			SurName				;
		Str16			Title				;
		Str16			Tips				;
		CHAR_BUILD_TYPE	BuildType			;
		CHAR_FORMULA_TYPE	FormulaType		;
		U32				Level				;
		U32				LineageLevel		;
		U32				AbilityInitId1		;
		U32				AbilityInitId2		;
		U32				AbilityInitId3		;
		U32				AbilityAppendId		;
		U32				CharacterSkillId	;
		U32				InfluenceId			;
		U32				ArtIconId			;
		U32				ArtMashId1			;
		U32				ArtMashId2			;
		U32				MapListId			;
		Str16			DestroyScript		;
		U32				CharacterVisionEventListId			;
		UInt			AIBaseGroupId		;
		UInt			AIFightGroupId		;

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
	};

	//=-------------------------------------------------------------------------------------------------
	class CharacterBuildList
	{
	public:
		CharacterBuildList(){;}
		~CharacterBuildList();
		SINGLETON_INSTANCE(CharacterBuildList);

	public:
		// MG_CN_MODIFY
		Bool							loadFile(Str16 filename, IMGExternalPackManager* packManager = NULL);
		const CharacterBuildInfo*		getCharacterBuildInfo(U32 id);

	private:
		void							clear();

	private:
		std::map<U32, CharacterBuildInfo*>			mMapCharacterBuildInfo;

	};
}
//**********************************************************************************************************************
#endif
//**********************************************************************************************************************