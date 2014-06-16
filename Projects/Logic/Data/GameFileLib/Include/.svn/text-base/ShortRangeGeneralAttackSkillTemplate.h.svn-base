//************************************************************************************************************
#ifndef _SHORTRANGEGENERALATTACKSKILLTEMPLATE_H_
#define _SHORTRANGEGENERALATTACKSKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	struct ShortRangeGeneralAttackSkillInfo : public InitiativeSkillBasicInfo
	{
	};

	//---------------------------------------------------------------------------------------------
	class ShortRangeGeneralAttackSkillTemplate
	{
	public:
		ShortRangeGeneralAttackSkillTemplate();
		~ShortRangeGeneralAttackSkillTemplate();
		SINGLETON_INSTANCE(ShortRangeGeneralAttackSkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const ShortRangeGeneralAttackSkillInfo*						getShortRangeGeneralAttackSkillInfo( UInt id );

		const ShortRangeGeneralAttackSkillInfo*						getShortRangeGeneralAttackSkillInfoByIndex( UInt index );
		UInt														getShortRangeGeneralAttackSkillInfoNum();

	private:
		void														clear();

	private:
		std::map<U32, ShortRangeGeneralAttackSkillInfo*>			mShortRangeGeneralAttackSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************