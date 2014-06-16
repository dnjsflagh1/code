//******************************************************************************************
#ifndef _QUESTLIST_H_
#define _QUESTLIST_H_
//******************************************************************************************
#include "WorldCorePreqs.h"
//******************************************************************************************
namespace MG
{
	//-----------------------------------------------------------------------
	enum QUEST_TYPE
	{
		QUEST_TYPE_NULL,
		QUEST_TYPE_NORMAL,
		QUEST_TYPE_RANDOM
	};

	enum
	{
		QuestInfoid,
		QuestNote,
		QuestInfotype,
		QuestListInfoid,
	};
	//对应策划文档QuestList一条记录
	struct ClanQuestInfo
	{
		U32					id;			//任务序号
		QUEST_TYPE			type;		//任务类型
		U32					questId;	//任务列表序号
		ClanQuestInfoBase*  questInfo;   
		ClanQuestInfo()
			:id(0)
			,type(QUEST_TYPE_NULL)
			,questId(0)
		{
			
		}
	};
	//-----------------------------------------------------------------------
	//对应策划文档QuestList表
	class ClanQuestInfos                       
	{
	public:
		ClanQuestInfos();
		~ClanQuestInfos();
		SINGLETON_INSTANCE(ClanQuestInfos);

	public:
		// MG_CN_MODIFY
		///加载 QuestList.csv 
		Bool								load(Str16 fileName, IMGExternalPackManager* packManager = NULL);

		//根据ID获得  QuestInfo
		ClanQuestInfo*						getQuestInfo(U32 id);

		Bool								setQuestInfoData();
	protected:
		void								clear();

	private:
		std::map<U32, ClanQuestInfo*>			mQuestInfoMap;

	};
}
#endif