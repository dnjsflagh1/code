/******************************************************************************/
#ifndef _QUESTNETPACKETPROCESSER_H_
#define _QUESTNETPACKETPROCESSER_H_
/******************************************************************************/
#include "GameNetEvent.h"
#include "QuestNetPacket.h"
/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //任务相关网络消息处理
    /******************************************************************************/
    class QuestNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(QuestNetPacketProcesser);
        QuestNetPacketProcesser();
        ~QuestNetPacketProcesser();

        Bool	processClientPacket(I32 id, NetEventRecv* packet);
        Bool	processLoginServerPacket(I32 id, NetEventRecv* packet);
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);
		Bool	processFrontServerPacket(I32 id, NetEventRecv *packet);

    public:

        //一些具体处理包方法
		void	onRecvQuestAcceptFromFrontServer(I32 id, PT_QUEST_F2C_ACCEPT_DATA* data );
		void	onRecvQuestSubmitFromFrontServer(I32 id, PT_QUEST_F2C_SUBMIT_DATA* data );
		void	onRecvDoingQuestListFromFrontServer(I32 id, PT_QUEST_F2C_DOING_QUESTLIST_DATA* data );
		void	onRecvFinishedQuestListFromFrontServer(I32 id, PT_QUEST_F2C_FINISHED_QUESTLIST_DATA* data );
		void	onRecvQuestStateFromFrontServer(I32 id, PT_QUEST_F2C_COMPLETEDSTATE_DATA* data );
		void    onRecvQuestGiveupFromFrontServer(I32 id, PT_QUEST_F2C_GIVEUP_DATA* data );
        void    onRecvQuestConditionVariableFromFrontServer(I32 id,PT_QUEST_F2C_CONDITION_VAR_DATA* data);

        //一些具体发送包方法
		void	sendAcceptQuest(Int questInfoId,PlayerCharacterIdType charId);		//接受任务
		void	sendSubmitQuest(Int questInfoId);		//提交任务
		void	sendGiveupQuest(U32 questInfoId);		//放弃任务
		void	sendTalkToNpc(U32 questInfoId, U32 npcId);

    };

}


#endif