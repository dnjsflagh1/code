//************************************************************************************************************
#ifndef _GOUPANDDOWNSKILLTEMPLATE_H_
#define _GOUPANDDOWNSKILLTEMPLATE_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	struct GoUpAndDownSkillInfo : public InitiativeSkillBasicInfo
	{
	};

	//---------------------------------------------------------------------------------------------
	class GoUpAndDownSkillTemplate
	{
	public:
		GoUpAndDownSkillTemplate();
		~GoUpAndDownSkillTemplate();
		SINGLETON_INSTANCE(GoUpAndDownSkillTemplate);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const GoUpAndDownSkillInfo*									getGoUpAndDownSkillInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, GoUpAndDownSkillInfo*>						mGoUpAndDownSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************