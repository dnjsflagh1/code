//************************************************************************************************************
#ifndef _PARABOLAAREASKILLTEMPLATE_H_
#define _PARABOLAAREASKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{
	enum ParabolaType
	{
		PT_Null,
		PT_1,
		PT_2,
		PT_3,
	};

	struct ParabolaAreaSkillInfo : public InitiativeSkillBasicInfo
	{
		UInt						resetTimepieceId		;	
		UInt						resetTimepieceGroupId	;
		UInt						pointEffectId			;
		UInt						pointAudioId			;
		UInt						artEffectFlyId			;
		Flt							artEffectFlySpeed		;
		ParabolaType				parabolaType			;
		Flt							parabolaAngle			;
		Flt							skillRadius				;
		UInt						attackNum				;
		ShareType					shareType				;
		//UInt						randomState				;
		//UInt						stateId					;
		//UInt						stateNum				;
	};

	//---------------------------------------------------------------------------------------------
	class ParabolaAreaSkillTemplate
	{
	public:
		ParabolaAreaSkillTemplate();
		~ParabolaAreaSkillTemplate();
		SINGLETON_INSTANCE(ParabolaAreaSkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const ParabolaAreaSkillInfo*								getParabolaAreaSkillInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, ParabolaAreaSkillInfo*>						mParabolaAreaSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************