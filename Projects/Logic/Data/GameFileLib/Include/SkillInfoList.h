//************************************************************************************************************
#ifndef _SKILLLIST_H_
#define _SKILLLIST_H_
//************************************************************************************************************
#include "GameFilePreqs.h"
#include "SkillBaseInfo.h"
//************************************************************************************************************
namespace MG
{

	enum 
	{
		SKILLID,	
		SKILLNOTES,
		SKILLTYPE,	
		SKILLLISTID,
		SKILLSHOWTYPE
	};

	//---------------------------------------------------------------------------------------------
	class SkillInfoList
	{
	public:
		SkillInfoList();
		~SkillInfoList();
		SINGLETON_INSTANCE(SkillInfoList);

	public:
		// MG_CN_MODIFY
		Bool														load( Str16 fileName, IMGExternalPackManager* packManager = NULL );

		const SkillInfo*											getSkillInfo( IdType id );
		const SkillInfo*											getSkillInfoByIndex( UInt index );

		UInt														getSkillInfoNum();

	private:
		void														clear();

	private:
		std::map<IdType, SkillInfo*>								mSkillInfoList;

	};
}
//************************************************************************************************************
#endif
//************************************************************************************************************