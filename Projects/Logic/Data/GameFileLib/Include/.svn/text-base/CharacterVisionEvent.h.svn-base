//*****************************************************************************************************************
#ifndef _CHARACTEREVENT_H_
#define _CHARACTEREVENT_H_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
	//-------------------------------------------------------------------------------

	struct CharacterVisionEventInfo 
	{
		friend CharacterVisionEvent;

	public:
		UInt	characterVisionEventId;
		UInt	audioResId;
		UInt	effectResId;
		Str16	actionName;		
		Bool	getModleColor(ColorI& color);
		Bool	getModleSize(Flt& flt);

	protected:
		UInt	ModleSize;
		Str16	ModleColor;

	};

	//-------------------------------------------------------------------------------
	class CharacterVisionEvent
	{
	public:
		CharacterVisionEvent();
		~CharacterVisionEvent();
		SINGLETON_INSTANCE(CharacterVisionEvent);

	public:
		// MG_CN_MODIFY
		Bool									load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const CharacterVisionEventInfo*			getCharacterVisionEventInfo( UInt id );

	private:
		void									clear();

	private:
		std::map<UInt, CharacterVisionEventInfo*> mCharacterVisionEventInfoList;
	};

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************