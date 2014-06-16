/******************************************************************************/
#include "stdafx.h"
#include "QuestNetPacketProcesser.h"
#include "QuestNetPacket.h"
//#include "SWorldManager.h"
#include "FrontServerMain.h"
#include "SWorldManager.h"
#include "SClanQuestManager.h"
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
		if ( packet->getChannel() == GNPC_QUEST )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_QUEST_C2F_ACCEPT:
				onRecvQuestAcceptFromClient( id , (PT_QUEST_C2F_ACCEPT_DATA*)data->data);
				break;
			case PT_QUEST_C2F_SUBMIT:
				onRecvQuestSubmitFromClient( id , (PT_QUEST_C2F_SUBMIT_DATA*)data->data);
				break;
			case PT_QUEST_C2F_GIVEUP:
				onRecvQuestGiveupFromClient(id,(PT_QUEST_C2F_GIVEUP_DATA*)data->data);
				break;
			case PT_QUEST_C2F_TALK_TO_NPC:
				onRecvTalkToNpc(id,(PT_QUEST_C2F_TALK_TO_NPC_DATA*)data->data);
				break;
			}

			return true;
		}
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
	void QuestNetPacketProcesser::onRecvQuestAcceptFromClient( I32 id , PT_QUEST_C2F_ACCEPT_DATA* data )
	{
		Int questId = data->questInfoId;
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}
		
		SClanQuestManager* questManager;// = player->getQuestManager();
		if (NULL == questManager)
		{
			return;
		}
		questManager->handleAcceptQuest(data->questInfoId,data->characterId);
	}

	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::onRecvQuestSubmitFromClient(I32 id , PT_QUEST_C2F_SUBMIT_DATA* data)
	{
		Int questId = data->questInfoId;
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SClanQuestManager* questManager;// = player->getQuestManager();
		if (NULL == questManager)
		{
			return;
		}

		if(questManager->canSubmit(data->questInfoId))
		{
			questManager->handleSubmitQuest(data->questInfoId);
		}

	}
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::onRecvQuestGiveupFromClient( I32 id , PT_QUEST_C2F_GIVEUP_DATA* data )
	{
		Int questId = data->questInfoId;
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if(player.isNull())
		{
			return;
		}

		SClanQuestManager* questManager;// = player->getQuestManager();
		if (NULL == questManager)
		{
			return;
		}

		if(questManager->canGiveup(data->questInfoId))
		{
			questManager->handleGiveupQuest(data->questInfoId);
		}
	}
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::onRecvTalkToNpc( I32 id , PT_QUEST_C2F_TALK_TO_NPC_DATA* data )
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if( player.isNull())
		{
			return;
		}

		SClanQuestManager* questManager;// = player->getQuestManager();
		if (NULL == questManager)
		{
			return;
		}

		questManager->notifyTalktoNpc(data->questInfoId,data->npcId);
	}

    //--------------------------------------------------------------------------
    void QuestNetPacketProcesser::sendAllQuestInfoToClient( I32 id, SPlayerPtr& playerPtr )
    {
#if 0
        NetIdType netId = ((SClan*)getClan())->getParentPlayer()->getClientNetID();
        if (mAllDoingQuests.size() >0 )
        {   
            QuestNetPacketProcesser::getInstance().sendDoingQuestInfoToClient(netId,&mAllDoingQuests);
        }
        if (mFinishedQuests.size() >0 )
        {
            QuestNetPacketProcesser::getInstance().sendFinishedQuestInfoToClient(netId,&mFinishedQuests);
        }
#endif

    }

	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendQuestAcceptResult( I32 id, U32 questInfoId, PT_QUEST_F2C_ACCEPT_RESULT result )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_ACCEPT;

			// ת���߼���
			PT_QUEST_F2C_ACCEPT_DATA* sendData = (PT_QUEST_F2C_ACCEPT_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->questInfoId = questInfoId;
				sendData->ret = (Byte)result;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,GameNetPacketData_INFO::headSize + PT_QUEST_F2C_ACCEPT_DATA_INFO::dataSize, id);

			}
		}
	}
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendQuestSubmitResult( I32 id, U32 questInfoId, Byte result )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_SUBMIT;

			// ת���߼���
			PT_QUEST_F2C_SUBMIT_DATA* sendData = (PT_QUEST_F2C_SUBMIT_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->questInfoId = questInfoId;
				sendData->result = result;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_QUEST_F2C_SUBMIT_DATA_INFO::dataSize, id );

			}
		}
	}

	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendQuestGiveupResult( I32 id, U32 questInfoId, Bool result )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_GIVEUP;

			// ת���߼���
			PT_QUEST_F2C_GIVEUP_DATA* sendData = (PT_QUEST_F2C_GIVEUP_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->questInfoId = questInfoId;
				sendData->ret = result;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_QUEST_F2C_GIVEUP_DATA_INFO::dataSize, id);
			}
		}
	}

	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendQuestCompletedState( I32 id, U32 questInfoId ,Byte completeState)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_COMPLETEDSTATE;

			// ת���߼���
			PT_QUEST_F2C_COMPLETEDSTATE_DATA* sendData = (PT_QUEST_F2C_COMPLETEDSTATE_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->questInfoId = questInfoId;
				sendData->completeState = completeState;

				// ��������

				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_QUEST_F2C_COMPLETEDSTATE_DATA_INFO::dataSize, id);
			}
		}
	}

	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendDoingQuestInfoToClient( I32 id,std::map< U32 , ClanQuestObject*>* doingQuestInfo )
	{
		DYNAMIC_ASSERT(doingQuestInfo);
		
		//--------------------------------------------------------------------------

		// �õ�һ�����ͷ��ͻ���
		GameNetSendDataBufferPtr dataPtr;
		GameNetPacketData* packet = NULL;
		PT_QUEST_F2C_DOING_QUESTLIST_DATA* sendData = NULL;

		// ��ǰ��������ͷ��С
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_QUEST_F2C_DOING_QUESTLIST_DATA_INFO::headSize;
		// ��ǰ�������ݴ�С
		I32 sendDataSize        = sendDataHeadSize;
		// ׼���������ݴ�С
		I32 prepareSendDataSize = sendDataHeadSize;

		// �����������
		std::map< U32 , ClanQuestObject*>::iterator front     = doingQuestInfo->begin();
		std::map< U32 , ClanQuestObject*>::iterator back      = doingQuestInfo->end();
		while (front != back)
		{
			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// ����һ����Ʒ���ݴ�С���������ݻ����С
				prepareSendDataSize = sendDataSize + PT_QUEST_F2C_DOING_QUESTLIST_DATA_INFO::questDataSize;

				// ������ڻ�������С����
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					//if(dataPtr->send( sendDataSize, id ) == false)
					FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr, sendDataSize, id );
					
					dataPtr.setNull();
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// �õ�һ�����ͷ��ͻ���
				FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				packet->channel = GNPC_QUEST;
				packet->type    = PT_QUEST_F2C_DOING_QUESTLIST;
				sendData = (PT_QUEST_F2C_DOING_QUESTLIST_DATA*)(packet->data);
				// ���
				sendData->count = 0;

				// ��ǰ��������ͷ��С
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_QUEST_F2C_DOING_QUESTLIST_DATA_INFO::headSize;
				// ��ǰ�������ݴ�С
				sendDataSize        = sendDataHeadSize;
				// ׼���������ݴ�С
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------

			// ���������¼
			DOING_QUEST_DATA& doingQuestData = sendData->data[sendData->count];
			doingQuestData.questInfoId = front->second->mInfo->id;
            doingQuestData.beginTime   = front->second->mRecord.beginTime;
			doingQuestData.endTime     = front->second->mRecord.endTime;
			doingQuestData.completeState = Byte(front->second->mRecord.state);
			doingQuestData.value[0]      = front->second->mRecord.value[0];
			doingQuestData.value[1]      = front->second->mRecord.value[1];
			doingQuestData.value[2]      = front->second->mRecord.value[2];
			doingQuestData.value[3]      = front->second->mRecord.value[3];
			
			// ��������
			sendDataSize += PT_QUEST_F2C_DOING_QUESTLIST_DATA_INFO::questDataSize;
			++sendData->count;
			++front;   
		}

		//--------------------------------------------------------------------------
		// �����ʣ������
		if ( dataPtr.isNull() == false )
		{
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr, sendDataSize, id );
			dataPtr.setNull();
		}
	}
	
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendFinishedQuestInfoToClient( I32 id,std::map<U32,FinishedClanQuestObject*>* finishedQuestInfo )
	{
		DYNAMIC_ASSERT(finishedQuestInfo);
		
		// �õ�һ�����ͷ��ͻ���
		GameNetSendDataBufferPtr dataPtr ;
		GameNetPacketData* packet       =  NULL;
		PT_QUEST_F2C_FINISHED_QUESTLIST_DATA* sendData = NULL;

		// ��ǰ��������ͷ��С
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_QUEST_F2C_FINISHED_QUESTLIST_DATA_INFO::headSize;
		// ��ǰ�������ݴ�С
		I32 sendDataSize        = sendDataHeadSize;
		// ׼���������ݴ�С
		I32 prepareSendDataSize = sendDataHeadSize;

		// �����������
		std::map<U32,FinishedClanQuestObject*>::iterator front     = finishedQuestInfo->begin();
		std::map<U32,FinishedClanQuestObject*>::iterator back      = finishedQuestInfo->end();
		while (front != back)
		{
			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// ����һ����Ʒ���ݴ�С���������ݻ����С
				prepareSendDataSize = sendDataSize + PT_QUEST_F2C_FINISHED_QUESTLIST_DATA_INFO::questDataSize;

				// ������ڻ�������С����
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr, sendDataSize, id );
					dataPtr.setNull();
				}	
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// �õ�һ�����ͷ��ͻ���
				FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				packet->channel = GNPC_QUEST;
				packet->type    = PT_QUEST_F2C_FINISHED_QUESTLIST;
				sendData = (PT_QUEST_F2C_FINISHED_QUESTLIST_DATA*)(packet->data);
				// ���
				sendData->count = 0;

				// ��ǰ��������ͷ��С
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_QUEST_F2C_FINISHED_QUESTLIST_DATA_INFO::headSize;
				// ��ǰ�������ݴ�С
				sendDataSize        = sendDataHeadSize;
				// ׼���������ݴ�С
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------
			

			// ���������¼
			FINISHED_QUEST_DATA& finishedQuestData = sendData->data[sendData->count];
			finishedQuestData.questInfoId = front->second->questInfoId;
			finishedQuestData.endTime     = front->second->endTime;

			// ��������
			sendDataSize += PT_QUEST_F2C_FINISHED_QUESTLIST_DATA_INFO::questDataSize;
			++sendData->count;
			++front;   
		}

		//--------------------------------------------------------------------------
		// �����ʣ������
		if ( dataPtr.isNull() == false)
		{
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, id);
			dataPtr.setNull();
		}
	}
	
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendQuestConditionVariable( I32 id,U32 questInfoId,Byte varPos,Int varValue )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_CONDITION_VAR;

			// ת���߼���
			PT_QUEST_F2C_CONDITION_VAR_DATA* sendData = (PT_QUEST_F2C_CONDITION_VAR_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->questInfoId = questInfoId;
				sendData->varValue = varValue;
				sendData->varPos = varPos;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_QUEST_F2C_CONDITION_VAR_DATA_INFO::dataSize, 
					id );
			}
		}
	}
}

