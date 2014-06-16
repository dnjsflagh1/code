/******************************************************************************/

#ifndef _GENERAL_RECRUIT_SYSTEM_H_
#define _GENERAL_RECRUIT_SYSTEM_H_

/******************************************************************************/

#include "FrontServerPreqs.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//
	struct CharAttrInfo
	{
		U32					charTemplateId;
		CharacterTempInfo*	charTempInfo;
		Str16				name;					//姓名
		Str16				name_xing;				//姓
		Str16				name_ming;				//名
		Int					age;					//登场年龄
		Int					lifeSpanBase;			//
		UInt				charAttrAppendId		;
		UInt				charAttrAppendLvlAddId	;

		Flt					charAttrRand[DB_RECORD_ATTR_NUM];   	//角色的随机天赋属性
		Flt					charAttrRandAdd[DB_RECORD_ATTR_NUM];	//角色的随机天赋属性等级附加
		
		CharAttrInfo()
			:charTemplateId(0)
			,charTempInfo(NULL)
		{
			for (Int i=0; i<DB_RECORD_ATTR_NUM; ++i)
			{
				charAttrRand[i] = 0.0f;
				charAttrRandAdd[i] = 0.0f;
			}
		}
	};


	/******************************************************************************/

	class GeneralRecruitSystem
	{
	public:
		GeneralRecruitSystem();
		~GeneralRecruitSystem();
		SINGLETON_INSTANCE(GeneralRecruitSystem);

		void	            reFresh(U32 GeneralRecruitId);
		
		U32		            getLastGeneralRecruitId() const;
		void	            setLastGeneralRecruitId(U32 id);

		CharAttrInfo*		getCharAttrInfoByIndex(RECRUIT_POSITION index);
		std::map<RECRUIT_POSITION, CharAttrInfo*>*		getCharAttrList();

	private:
    
		void	            setRandomAttr(RECRUIT_POSITION index, const GeneralRandomCsvInfo* generalRandomInfo);
		void	            setRandomGeneral(RECRUIT_POSITION index, U32 GeneralGroupId);
		U32		            setGenrealAge( const CalendarInfo* pCalendarInfo, U32 age );
		
	private:

		U32			mLastGeneralRecruitId;
		std::map<RECRUIT_POSITION, CharAttrInfo*>		mCharAttrList;

	};

}

#endif	//_GENERAL_RECRUIT_SYSTEM_H_