//*****************************************************************************************************************
#ifndef _FIGHTAIGROUPTEMPLATE_H_
#define _FIGHTAIGROUPTEMPLATE_H_
//*****************************************************************************************************************
#include "GameFilePreqs.h"
#include "FightAITemplate.h"
//*****************************************************************************************************************
namespace MG
{
	//-------------------------------------------------------------------------------

	struct FightAIGroup 
	{
		UInt								aiFightGroupId;
		std::vector<FightAIInfo*>			aiFightAIInfoList;
	};

	//-------------------------------------------------------------------------------
	class FightAIGroupTemplate
	{
	public:
		FightAIGroupTemplate();
		~FightAIGroupTemplate();
		SINGLETON_INSTANCE(FightAIGroupTemplate);

	public:
		// MG_CN_MODIFY
		Bool									load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const FightAIGroup*						getFightAIGroup( UInt groupId );

	private:
		void									clear();

	private:
		std::map<UInt, FightAIGroup*>			mFightAIGroupList;
	};

}
//*****************************************************************************************************************
#endif
//*****************************************************************************************************************