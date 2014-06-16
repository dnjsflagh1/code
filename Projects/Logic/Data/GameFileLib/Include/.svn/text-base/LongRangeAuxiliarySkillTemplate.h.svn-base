//************************************************************************************************************
#ifndef _LONGRANGEAUXILIARYSKILLTEMPLATE_H_
#define _LONGRANGEAUXILIARYSKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	struct LongRangeAuxiliarySkillInfo : public InitiativeSkillBasicInfo
	{
		UInt						resetTimepieceId		;	
		UInt						resetTimepieceGroupId	;
	};

	//---------------------------------------------------------------------------------------------
	class LongRangeAuxiliarySkillTemplate
	{
	public:
		LongRangeAuxiliarySkillTemplate();
		~LongRangeAuxiliarySkillTemplate();
		SINGLETON_INSTANCE(LongRangeAuxiliarySkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const LongRangeAuxiliarySkillInfo*							getLongRangeAuxiliarySkillInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, LongRangeAuxiliarySkillInfo*>					mLongRangeAuxiliarySkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************