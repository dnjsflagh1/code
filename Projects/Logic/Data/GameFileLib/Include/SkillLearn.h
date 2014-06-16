//************************************************************************************************************
#ifndef _SKILLLEARN_H_
#define _SKILLLEARN_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	enum 
	{
		SKILLLEARNID,
		//NOTES,
		CLANJUDGEID	,		
		CHARACTERJUDGEID,
		SKILLFRONTID,		
		ITEMID,			
		ITEMNUM,			
		DELITEMID,		
		ARTACTION,	
		ARTEFFECTRESID,
		AUDIORESID,	
	};

	//---------------------------------------------------------------------------------------------
	class SkillLearn
	{
	public:
		SkillLearn();
		~SkillLearn();
		SINGLETON_INSTANCE(SkillLearn);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );
		const SkillLearnInfo*										getSkillLearnInfo( UInt id );

	private:
		void														clear();

	private:
		std::map<U32, SkillLearnInfo*>								mSkillLearnInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************