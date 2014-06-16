//*****************************************************************************************************************
#ifndef _CHARACTERVISIONEVENTLIST_H_
#define _CHARACTERVISIONEVENTLIST_H_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
	//-------------------------------------------------------------------------------

	struct CharacterVisionEventListInfo 
	{
		UInt characterVisionEventListId;
		UInt upgradeId;
		UInt reincarnationId;
		UInt diedId;
		UInt rebirthId;
	};

	//-------------------------------------------------------------------------------
	class CharacterVisionEventList
	{
	public:
		CharacterVisionEventList();
		~CharacterVisionEventList();
		SINGLETON_INSTANCE(CharacterVisionEventList);

	public:
		// MG_CN_MODIFY
		Bool									load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const CharacterVisionEventListInfo*		getCharacterVisionEventListInfo( UInt id );

	private:
		void									clear();

	private:
		std::map<UInt, CharacterVisionEventListInfo*>	mCharacterEventListInfoList;
	};

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************