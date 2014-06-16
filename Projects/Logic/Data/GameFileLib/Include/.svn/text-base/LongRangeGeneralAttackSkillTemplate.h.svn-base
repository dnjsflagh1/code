//************************************************************************************************************
#ifndef _LONGRANGEGENERALATTACKSKILLTEMPLATE_H_
#define _LONGRANGEGENERALATTACKSKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	struct LongRangeGeneralAttackSkillInfo : public InitiativeSkillBasicInfo
	{
		SkillFlyType				artEffectFlyType	;
		UInt						artEffectFlyId		;
		UInt						artEffectFlySpeed	;
	};

	//---------------------------------------------------------------------------------------------
	class LongRangeGeneralAttackSkillTemplate
	{
	public:
		LongRangeGeneralAttackSkillTemplate();
		~LongRangeGeneralAttackSkillTemplate();
		SINGLETON_INSTANCE(LongRangeGeneralAttackSkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const LongRangeGeneralAttackSkillInfo*						getLongRangeGeneralAttackSkillInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, LongRangeGeneralAttackSkillInfo*>				mLongRangeGeneralAttackSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************