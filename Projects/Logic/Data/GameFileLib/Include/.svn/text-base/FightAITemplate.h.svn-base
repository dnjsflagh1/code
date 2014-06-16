//*****************************************************************************************************************
#ifndef _FIGHTAITEMPLATE_H_
#define _FIGHTAITEMPLATE_H_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
//*****************************************************************************************************************
namespace MG
{
	//-------------------------------------------------------------------------------
	
	struct FightAIInfo 
	{
		UInt								aiFightId;
		UInt								priority;
		ContactType							contactType;
		ContactCharacterType				contactParam1;
		Flt									contactParam2;
		Flt									contactParam3;
		Flt									contactParam4;
		UInt								randomNum;
		UInt								contactNum;
		EventType							eventType;
		EventCharacterType					eventParam1;
		UInt								eventParam2;
		UInt								eventParam3;
		UInt								eventParam4;
	};

	//-------------------------------------------------------------------------------
	class FightAITemplate
	{
	public:
		FightAITemplate();
		~FightAITemplate();
		SINGLETON_INSTANCE(FightAITemplate);

	public:
		// MG_CN_MODIFY
		Bool									load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const FightAIInfo*						getFightTriggerInfo( UInt id );

	private:
		void									clear();

	private:
		std::map<UInt, FightAIInfo*>			mFightAIInfoList;
	};

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************