//**********************************************************************************************************
#ifndef _CLANQUEST_H_
#define _CLANQUEST_H_
//**********************************************************************************************************
#include "WorldCorePreqs.h"
//**********************************************************************************************************
namespace MG
{
	enum QUEST_COMPLETE_STATE
	{
	    QUEST_COMPLETE_STATE_IDLE,
		QUEST_COMPLETE_STATE_ACCEPTED = 1,
		QUEST_COMPLETE_STATE_FINISHED,
		QUEST_COMPLETE_STATE_FAILED,
		QUEST_COMPLETE_STATE_TIMEOUT,
		QUEST_COMPLETE_STATE_SUBMITED,


	};
    struct ClanQuestRecord 
    {
		QUEST_COMPLETE_STATE state;
		U32 beginTime;
		U32 endTime;
		I32 value[4];

		ClanQuestRecord()
		{
			clear();
		}
        
		void clear()
		{
			state = QUEST_COMPLETE_STATE_ACCEPTED;
			beginTime = 0;
			endTime = 0;
			value[0] = 0;
			value[1] = 0;
			value[2] = 0;
			value[3] = 0;

		}
    };
	//----------------------------------------------------------------------------------------
	//
	//读取正在进行中任务DB数据使用的数据类型
	//
	struct dbDoingClanQuestObject
	{
	public:
		dbDoingClanQuestObject():questInfoId(0){;}
		~dbDoingClanQuestObject()
		{
			clear();
		}

		void clear()
		{
			mRecord.clear();

		}

	public:
        U32                         questInfoId;
		ClanQuestRecord             mRecord;		

	};

	//
	//已完成任务DB数据使用的类型
	//
	struct FinishedClanQuestObject
	{   
		U32                         questInfoId;
		U32                         endTime;
		FinishedClanQuestObject()
		{
			questInfoId = 0;
			endTime = 0;
		}
	};
    //----------------------------------------------------------------------------------------
    struct ClanQuestObject
    {
    public:
        ClanQuestObject();
        ~ClanQuestObject();

		void clear();

    public:

        ClanQuestRecord             mRecord;
		ClanQuestInfo*				mInfo;


    };
}
//**********************************************************************************************************
#endif
//**********************************************************************************************************