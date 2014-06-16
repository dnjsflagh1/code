//************************************************************************************************************
#ifndef _SELFAREASKILLTEMPLATE_H_
#define _SELFAREASKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	struct SelfAreaSkillInfo : public InitiativeSkillBasicInfo
	{
		UInt						resetTimepieceId		;	
		UInt						resetTimepieceGroupId	;
		Flt							skillRadius				;
		UInt						attackNum				;
		ShareType					shareType				;
		//UInt						randomState				;
		//UInt						stateId					;
		//UInt						stateNum				;
	};

	//---------------------------------------------------------------------------------------------
	class SelfAreaSkillTemplate
	{
	public:
		SelfAreaSkillTemplate();
		~SelfAreaSkillTemplate();
		SINGLETON_INSTANCE(SelfAreaSkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const SelfAreaSkillInfo*									getSelfAreaSkillInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, SelfAreaSkillInfo*>							mSelfAreaSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************