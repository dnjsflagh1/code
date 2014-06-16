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
    //�������������Ϣ����
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

        //һЩ���崦�������
		void	onRecvQuestAcceptFromFrontServer(I32 id, PT_QUEST_F2C_ACCEPT_DATA* data );
		void	onRecvQuestSubmitFromFrontServer(I32 id, PT_QUEST_F2C_SUBMIT_DATA* data );
		void	onRecvDoingQuestListFromFrontServer(I32 id, PT_QUEST_F2C_DOING_QUESTLIST_DATA* data );
		void	onRecvFinishedQuestListFromFrontServer(I32 id, PT_QUEST_F2C_FINISHED_QUESTLIST_DATA* data );
		void	onRecvQuestStateFromFrontServer(I32 id, PT_QUEST_F2C_COMPLETEDSTATE_DATA* data );
		void    onRecvQuestGiveupFromFrontServer(I32 id, PT_QUEST_F2C_GIVEUP_DATA* data );
        void    onRecvQuestConditionVariableFromFrontServer(I32 id,PT_QUEST_F2C_CONDITION_VAR_DATA* data);

        //һЩ���巢�Ͱ�����
		void	sendAcceptQuest(Int questInfoId,PlayerCharacterIdType charId);		//��������
		void	sendSubmitQuest(Int questInfoId);		//�ύ����
		void	sendGiveupQuest(U32 questInfoId);		//��������
		void	sendTalkToNpc(U32 questInfoId, U32 npcId);

    };

}


#endif