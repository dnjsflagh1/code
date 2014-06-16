//************************************************************************************************************
#ifndef _SINGLEEMITTERSKILLTEMPLATE_H_
#define _SINGLEEMITTERSKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	struct SingleEmitterSkillInfo : public InitiativeSkillBasicInfo
	{
		SkillFlyType				artEffectFlyType		;
		UInt						artEffectFlyId			;
		Flt							artEffectFlySpeed		;
		UInt						resetTimepieceId		;	
		UInt						resetTimepieceGroupId	;
		//UInt						randomState				;
		//UInt						stateId					;
		//UInt						stateNum				;
	};

	//---------------------------------------------------------------------------------------------
	class SingleEmitterSkillTemplate
	{
	public:
		SingleEmitterSkillTemplate();
		~SingleEmitterSkillTemplate();
		SINGLETON_INSTANCE(SingleEmitterSkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const SingleEmitterSkillInfo*								getSingleEmitterSkillInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, SingleEmitterSkillInfo*>						mSingleEmitterSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************