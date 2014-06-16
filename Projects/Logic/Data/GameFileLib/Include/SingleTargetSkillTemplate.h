//************************************************************************************************************
#ifndef _SINGLETARGETSKILLTEMPLATE_H_
#define _SINGLETARGETSKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	struct SingleTargetSkillInfo : public InitiativeSkillBasicInfo
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
	class SingleTargetSkillTemplate
	{
	public:
		SingleTargetSkillTemplate();
		~SingleTargetSkillTemplate();
		SINGLETON_INSTANCE(SingleTargetSkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const SingleTargetSkillInfo*								getSingleTargetSkillInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, SingleTargetSkillInfo*>						mSingleTargetSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************