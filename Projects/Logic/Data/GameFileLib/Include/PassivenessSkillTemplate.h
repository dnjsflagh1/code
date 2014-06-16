//************************************************************************************************************
#ifndef _PASSIVENESSSKILLTEMPLATE_H_
#define _PASSIVENESSSKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	struct PassivenessSkillInfo : public PassivenessSkillBasicInfo
	{
	};

	//---------------------------------------------------------------------------------------------
	class PassivenessSkillTemplate
	{
	public:
		PassivenessSkillTemplate();
		~PassivenessSkillTemplate();
		SINGLETON_INSTANCE(PassivenessSkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const PassivenessSkillInfo*									getPassivenessSkillInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, PassivenessSkillInfo*>						mPassivenessSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************