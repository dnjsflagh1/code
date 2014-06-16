//************************************************************************************************************
#ifndef _TARGETPOSAREASKILLTEMPLATE_H_
#define _TARGETPOSAREASKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	struct TargetPosAreaSkillInfo : public InitiativeSkillBasicInfo
	{
		UInt						resetTimepieceId		;	
		UInt						resetTimepieceGroupId	;
		UInt						pointEffectId			;
		UInt						pointSkillEffectId		;
		UInt						pointAudioId			;
		Flt							skillRadius				;
		UInt						attackNum				;
		ShareType					shareType				;
		UInt						skillCastNum			;
		Flt							skillCastInterval		;
		//UInt						randomState				;
		//UInt						stateId					;
		//UInt						stateNum				;
	};

	//---------------------------------------------------------------------------------------------
	class TargetPosAreaSkillTemplate
	{
	public:
		TargetPosAreaSkillTemplate();
		~TargetPosAreaSkillTemplate();
		SINGLETON_INSTANCE(TargetPosAreaSkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const TargetPosAreaSkillInfo*								getTargetPosAreaSkillInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, TargetPosAreaSkillInfo*>						mTargetPosAreaSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************