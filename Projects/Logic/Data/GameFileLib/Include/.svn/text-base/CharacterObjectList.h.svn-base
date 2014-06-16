//**********************************************************************************************************************
#ifndef _H_CHARACTEROBJECTLIST_
#define _H_CHARACTEROBJECTLIST_
//**********************************************************************************************************************
#include "GameFilePreqs.h"
//**********************************************************************************************************************
namespace MG
{
	struct CharacterObjectInfo
	{
		U32							CharacterObjectId	;
		Str16						ListName			;
		Str16						SurName				;
		Str16						Title				;
		Str16						Tips				;
		U32							Level				;
		U32							ArtIconId			;
		U32							ArtMashId			;
		CHARACTER_OBJ_MUTUALTYPE	MutualType			;
		Str16						MutualAction		;
		U32							MutualTime			;
		U32							MutualItemGroup		;
		U32							MutualEffectId		;
		Str16						MutualScript		;
		U32							CharacterVisionEventListId			;
		UInt						AIBaseGroupId		;
		UInt						AIFightGroupId		;
		
		//---------------------------------------------------------------------------


	};
	//=-------------------------------------------------------------------------------------------------
	class CharacterObjectList
	{
	public:
		CharacterObjectList(){;}
		~CharacterObjectList();
		SINGLETON_INSTANCE(CharacterObjectList);

	public:
		// MG_CN_MODIFY
		Bool						loadFile(Str16 filename, IMGExternalPackManager* packManager = NULL);
		const CharacterObjectInfo*	getCharacterObjectInfo(U32 id);

	private:
		void						clear();

	private:
		std::map<U32, CharacterObjectInfo*>			mMapCharacterObjectInfo;

	};
}
//**********************************************************************************************************************
#endif
//**********************************************************************************************************************