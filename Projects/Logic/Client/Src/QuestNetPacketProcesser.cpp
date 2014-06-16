/******************************************************************************/
#include "stdafx.h"
#include "QuestNetPacketProcesser.h"
#include "GameNetPacket.h"
#include "ClientNetApplyManager.h"
#include "UIMessageBox.h"
#include "CClan.h"
#include "CPlayer.h"
#include "CClanQuestManager.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	QuestNetPacketProcesser::QuestNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	QuestNetPacketProcesser::~QuestNetPacketProcesser()
	{

	}

    //--------------------------------------------------------------------------
    Bool QuestNetPacketProcesser::processClientPacket(I32 id, NetEventRecv* packet)
    {

        return false;
    }

    //--------------------------------------------------------------------------
    Bool QuestNetPacketProcesser::processLoginServerPacket(I32 id, NetEventRecv* packet)
    {

        return false;
    }

    //--------------------------------------------------------------------------
    Bool QuestNetPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
    {

        return false;
    }

	//--------------------------------------------------------------------------
	Bool QuestNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv *packet)
	{
		if ( packet->getChannel() == GNPC_QUEST )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_QUEST_F2C_ACCEPT:
				onRecvQuestAcceptFromFrontServer( id, (PT_QUEST_F2C_ACCEPT_DATA*)data->data );
				break;
			case PT_QUEST_F2C_SUBMIT:
				onRecvQuestSubmitFromFrontServer( id, (PT_QUEST_F2C_SUBMIT_DATA*)data->data );
				break;
			case PT_QUEST_F2C_DOING_QUESTLIST:
				onRecvDoingQuestListFromFrontServer(id, (PT_QUEST_F2C_DOING_QUESTLIST_DATA*)data->data);
				break;
			case PT_QUEST_F2C_FINISHED_QUESTLIST:
				onRecvFinishedQuestListFromFrontServer(id, (PT_QUEST_F2C_FINISHED_QUESTLIST_DATA*)data->data);
				break;
			case PT_QUEST_F2C_COMPLETEDSTATE:
				onRecvQuestStateFromFrontServer(id,(PT_QUEST_F2C_COMPLETEDSTATE_DATA*)data->data);
				break;
			case PT_QUEST_F2C_GIVEUP:
				onRecvQuestGiveupFromFrontServer(id,(PT_QUEST_F2C_GIVEUP_DATA*)data->data);
				break;
			case PT_QUEST_F2C_CONDITION_VAR:
				onRecvQuestConditionVariableFromFrontServer(id,(PT_QUEST_F2C_CONDITION_VAR_DATA*)data->data);
				break;
			}
			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::onRecvQuestAcceptFromFrontServer(I32 id, PT_QUEST_F2C_ACCEPT_DATA* data )
	{
		CClanQuestManager::getInstance().handleAcceptQuestResult(data->questInfoId,(PT_QUEST_F2C_ACCEPT_RESULT)data->ret);
	}

	void QuestNetPacketProcesser::onRecvQuestSubmitFromFrontServer(I32 id, PT_QUEST_F2C_SUBMIT_DATA* data )
	{
		//FUNDETECTION(__MG_FUNC__);
		CClanQuestManager::getInstance().handleSubmitQuestResult(data->questInfoId,data->result);

	}

	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendAcceptQuest(Int questInfoId,PlayerCharacterIdType charId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_QUEST;
            packet->type    = PT_QUEST_C2F_ACCEPT;

            // 转换逻辑包
            PT_QUEST_C2F_ACCEPT_DATA* sendData = (PT_QUEST_C2F_ACCEPT_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->questInfoId = questInfoId;
                sendData->characterId = charId;
                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_QUEST_C2F_ACCEPT_DATA_INFO::dataSize );
            }
        }

	}


	void QuestNetPacketProcesser::sendSubmitQuest(Int questId)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_QUEST;
            packet->type    = PT_QUEST_C2F_SUBMIT;

            // 转换逻辑包
            PT_QUEST_C2F_SUBMIT_DATA* sendData = (PT_QUEST_C2F_SUBMIT_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->questInfoId = questId;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_QUEST_C2F_SUBMIT_DATA_INFO::dataSize );
            }
        }

	}
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendTalkToNpc(U32 questInfoId, U32 npcId )
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_C2F_TALK_TO_NPC;

			// 转换逻辑包
			PT_QUEST_C2F_TALK_TO_NPC_DATA* sendData = (PT_QUEST_C2F_TALK_TO_NPC_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->npcId = npcId;
				sendData->questInfoId = questInfoId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_QUEST_C2F_TALK_TO_NPC_DATA_INFO::dataSize );
			}
		}

	}
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendGiveupQuest( U32 questId )
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_C2F_GIVEUP;

			// 转换逻辑包
			PT_QUEST_C2F_GIVEUP_DATA* sendData = (PT_QUEST_C2F_GIVEUP_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->questInfoId = questId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_QUEST_C2F_GIVEUP_DATA_INFO::dataSize );
			}
		}
	}
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::onRecvQuestStateFromFrontServer( I32 id, PT_QUEST_F2C_COMPLETEDSTATE_DATA* data )
	{
		CClanQuestManager::getInstance().setQuestState(data->questInfoId,data->completeState);
	}

	void QuestNetPacketProcesser::onRecvQuestGiveupFromFrontServer( I32 id, PT_QUEST_F2C_GIVEUP_DATA* data )
	{
         CClanQuestManager::getInstance().handleGiveupQuestResult(data->questInfoId,data->ret);
	}
   
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::onRecvDoingQuestListFromFrontServer( I32 id, PT_QUEST_F2C_DOING_QUESTLIST_DATA* data )
	{
           CClanQuestManager::getInstance().handleRecvDoingQuestList(data->data,data->count);

	}
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::onRecvFinishedQuestListFromFrontServer( I32 id, PT_QUEST_F2C_FINISHED_QUESTLIST_DATA* data )
	{
       CClanQuestManager::getInstance().handleRecvFinishedQuestList(data->data,data->count);

	}
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::onRecvQuestConditionVariableFromFrontServer( I32 id,PT_QUEST_F2C_CONDITION_VAR_DATA* data )
	{
		CClanQuestManager::getInstance().handleRecvConditionVariable(data->questInfoId,data->varPos,data->varValue);
	}
	//--------------------------------------------------------------------------
}

