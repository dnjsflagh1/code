/******************************************************************************/
#ifndef _QUEST_NETPACKET_H_
#define _QUEST_NETPACKET_H_
/******************************************************************************/
#include "CommonGameDefine.h"
#include "NetDefine.h"
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//任务数据包相关类型
	/******************************************************************************/
	enum QuestNetPacket
	{
		PT_QUEST_UNKNOW = 0,

		PT_QUEST_C2F_ACCEPT,				 //接受任务
		PT_QUEST_F2C_ACCEPT,

		PT_QUEST_C2F_SUBMIT,				 //提交任务
		PT_QUEST_F2C_SUBMIT,
		
		PT_QUEST_C2F_GIVEUP,
		PT_QUEST_F2C_GIVEUP,

		PT_QUEST_F2C_DOING_QUESTLIST,
		PT_QUEST_F2C_FINISHED_QUESTLIST,
        
        PT_QUEST_F2C_CONDITION_VAR,
		PT_QUEST_F2C_COMPLETEDSTATE,
		
		PT_QUEST_C2F_TALK_TO_NPC,
	};

#pragma pack (push)
#pragma pack (1)

	/******************************************************************************/
	struct PT_QUEST_C2F_ACCEPT_DATA
	{
		U32 questInfoId;
        PlayerCharacterIdType characterId;
	};
    struct PT_QUEST_C2F_ACCEPT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_QUEST_C2F_ACCEPT_DATA);
    };

	struct PT_QUEST_F2C_ACCEPT_DATA
	{
		U32			questInfoId;
		U32			time;
		Byte		ret;
	};
    struct PT_QUEST_F2C_ACCEPT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_QUEST_F2C_ACCEPT_DATA);
    };
	enum PT_QUEST_F2C_ACCEPT_RESULT
	{
         pt_quest_f2c_accept_null,
         pt_quest_f2c_accept_success,
		 pt_quest_f2c_accept_already_done,
         pt_quest_f2c_accept_clanlevel_not_enough,
		 pt_quest_f2c_accept_characterlevel_not_enough,
		 pt_quest_f2c_accept_need_complete_quest,
		 pt_quest_f2c_accept_unknown_error

	};
	/******************************************************************************/
	struct PT_QUEST_C2F_SUBMIT_DATA
	{
		U32 questInfoId;
	};
    struct PT_QUEST_C2F_SUBMIT_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_QUEST_C2F_SUBMIT_DATA);
    };

	struct PT_QUEST_F2C_SUBMIT_DATA
	{
		U32			questInfoId;
		U32			time;
		Byte		result;
	};
	struct PT_QUEST_F2C_SUBMIT_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_QUEST_F2C_SUBMIT_DATA);
	};
	enum PT_QUEST_F2C_SUBMIT_RESULT
	{
         pt_quest_f2c_submit_null,
		 pt_quest_f2c_submit_success,
		 pt_quest_f2c_submit_clanbag_full,
		 pt_quest_f2c_submit_clanbag_not_enough,
		 pt_quest_f2c_submit_unknown_error
	};
    /******************************************************************************/
	struct PT_QUEST_C2F_GIVEUP_DATA
	{
		U32			questInfoId;
	};
    struct PT_QUEST_C2F_GIVEUP_DATA_INFO
    {
        static const Int dataSize = sizeof (PT_QUEST_C2F_GIVEUP_DATA);
    };
		
	struct PT_QUEST_F2C_GIVEUP_DATA
	{
		U32			questInfoId;
		U32			time;
		Bool		ret;
	};
	struct PT_QUEST_F2C_GIVEUP_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_QUEST_F2C_SUBMIT_DATA);
	};
	/******************************************************************************/
	struct PT_QUEST_F2C_COMPLETEDSTATE_DATA
	{
		U32		questInfoId;
		Byte	completeState;	//true finished, false failed
	};
	struct PT_QUEST_F2C_COMPLETEDSTATE_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_QUEST_F2C_COMPLETEDSTATE_DATA);
	};
    struct PT_QUEST_F2C_CONDITION_VAR_DATA
	{
        U32   questInfoId;
		Byte  varPos;
		Int   varValue;
	};
	struct PT_QUEST_F2C_CONDITION_VAR_DATA_INFO
	{
        static const Int dataSize = sizeof(PT_QUEST_F2C_CONDITION_VAR_DATA);
	};
	/******************************************************************************/
	//正在进行中的任务
	struct DOING_QUEST_DATA			
	{		
		U32		questInfoId;
		Byte	completeState;
		U32		beginTime;
		U32		endTime;
		I32		value[4];
	};
	struct PT_QUEST_F2C_DOING_QUESTLIST_DATA
	{
		U16 count;
		DOING_QUEST_DATA data[1];
	};
	struct PT_QUEST_F2C_DOING_QUESTLIST_DATA_INFO
	{
			static const Int questDataSize = sizeof(DOING_QUEST_DATA);
			static const Int headSize = sizeof(PT_QUEST_F2C_DOING_QUESTLIST_DATA) - questDataSize;
		
	};
	//已完成的任务
	struct FINISHED_QUEST_DATA			
	{		
		U32		questInfoId;
		U32		endTime;
	};
	struct PT_QUEST_F2C_FINISHED_QUESTLIST_DATA
	{
		U16 count;
		FINISHED_QUEST_DATA data[1];
	};
	struct PT_QUEST_F2C_FINISHED_QUESTLIST_DATA_INFO
	{
			static const Int questDataSize = sizeof(FINISHED_QUEST_DATA);
			static const Int headSize = sizeof(PT_QUEST_F2C_FINISHED_QUESTLIST_DATA) - questDataSize;
	};
	/******************************************************************************/
	struct PT_QUEST_C2F_TALK_TO_NPC_DATA
	{
		U32 npcId;
		U32 questInfoId;
	};
	struct PT_QUEST_C2F_TALK_TO_NPC_DATA_INFO
	{
		static const Int dataSize = sizeof (PT_QUEST_C2F_TALK_TO_NPC_DATA);
	};
	/******************************************************************************/
#pragma pack (pop)
}

/******************************************************************************/

#endif	//_QUEST_NETPACKET_H_