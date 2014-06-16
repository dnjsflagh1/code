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
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_ACCEPT;

			// 转换逻辑包
			PT_QUEST_F2C_ACCEPT_DATA* sendData = (PT_QUEST_F2C_ACCEPT_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->questInfoId = questInfoId;
				sendData->ret = (Byte)result;

				// 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,GameNetPacketData_INFO::headSize + PT_QUEST_F2C_ACCEPT_DATA_INFO::dataSize, id);

			}
		}
	}
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendQuestSubmitResult( I32 id, U32 questInfoId, Byte result )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_SUBMIT;

			// 转换逻辑包
			PT_QUEST_F2C_SUBMIT_DATA* sendData = (PT_QUEST_F2C_SUBMIT_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->questInfoId = questInfoId;
				sendData->result = result;

				// 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_QUEST_F2C_SUBMIT_DATA_INFO::dataSize, id );

			}
		}
	}

	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendQuestGiveupResult( I32 id, U32 questInfoId, Bool result )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_GIVEUP;

			// 转换逻辑包
			PT_QUEST_F2C_GIVEUP_DATA* sendData = (PT_QUEST_F2C_GIVEUP_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->questInfoId = questInfoId;
				sendData->ret = result;

				// 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_QUEST_F2C_GIVEUP_DATA_INFO::dataSize, id);
			}
		}
	}

	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendQuestCompletedState( I32 id, U32 questInfoId ,Byte completeState)
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_COMPLETEDSTATE;

			// 转换逻辑包
			PT_QUEST_F2C_COMPLETEDSTATE_DATA* sendData = (PT_QUEST_F2C_COMPLETEDSTATE_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->questInfoId = questInfoId;
				sendData->completeState = completeState;

				// 发送数据

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

		// 得到一个大型发送缓存
		GameNetSendDataBufferPtr dataPtr;
		GameNetPacketData* packet = NULL;
		PT_QUEST_F2C_DOING_QUESTLIST_DATA* sendData = NULL;

		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_QUEST_F2C_DOING_QUESTLIST_DATA_INFO::headSize;
		// 当前发送数据大小
		I32 sendDataSize        = sendDataHeadSize;
		// 准备发送数据大小
		I32 prepareSendDataSize = sendDataHeadSize;

		// 遍历任务队列
		std::map< U32 , ClanQuestObject*>::iterator front     = doingQuestInfo->begin();
		std::map< U32 , ClanQuestObject*>::iterator back      = doingQuestInfo->end();
		while (front != back)
		{
			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// 递增一个物品数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_QUEST_F2C_DOING_QUESTLIST_DATA_INFO::questDataSize;

				// 如果大于缓存最大大小则发送
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
				// 得到一个大型发送缓存
				FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				packet->channel = GNPC_QUEST;
				packet->type    = PT_QUEST_F2C_DOING_QUESTLIST;
				sendData = (PT_QUEST_F2C_DOING_QUESTLIST_DATA*)(packet->data);
				// 清空
				sendData->count = 0;

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_QUEST_F2C_DOING_QUESTLIST_DATA_INFO::headSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------

			// 增加任务记录
			DOING_QUEST_DATA& doingQuestData = sendData->data[sendData->count];
			doingQuestData.questInfoId = front->second->mInfo->id;
            doingQuestData.beginTime   = front->second->mRecord.beginTime;
			doingQuestData.endTime     = front->second->mRecord.endTime;
			doingQuestData.completeState = Byte(front->second->mRecord.state);
			doingQuestData.value[0]      = front->second->mRecord.value[0];
			doingQuestData.value[1]      = front->second->mRecord.value[1];
			doingQuestData.value[2]      = front->second->mRecord.value[2];
			doingQuestData.value[3]      = front->second->mRecord.value[3];
			
			// 递增参数
			sendDataSize += PT_QUEST_F2C_DOING_QUESTLIST_DATA_INFO::questDataSize;
			++sendData->count;
			++front;   
		}

		//--------------------------------------------------------------------------
		// 如果有剩余则发送
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
		
		// 得到一个大型发送缓存
		GameNetSendDataBufferPtr dataPtr ;
		GameNetPacketData* packet       =  NULL;
		PT_QUEST_F2C_FINISHED_QUESTLIST_DATA* sendData = NULL;

		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_QUEST_F2C_FINISHED_QUESTLIST_DATA_INFO::headSize;
		// 当前发送数据大小
		I32 sendDataSize        = sendDataHeadSize;
		// 准备发送数据大小
		I32 prepareSendDataSize = sendDataHeadSize;

		// 遍历任务队列
		std::map<U32,FinishedClanQuestObject*>::iterator front     = finishedQuestInfo->begin();
		std::map<U32,FinishedClanQuestObject*>::iterator back      = finishedQuestInfo->end();
		while (front != back)
		{
			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// 递增一个物品数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_QUEST_F2C_FINISHED_QUESTLIST_DATA_INFO::questDataSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr, sendDataSize, id );
					dataPtr.setNull();
				}	
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// 得到一个大型发送缓存
				FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				packet->channel = GNPC_QUEST;
				packet->type    = PT_QUEST_F2C_FINISHED_QUESTLIST;
				sendData = (PT_QUEST_F2C_FINISHED_QUESTLIST_DATA*)(packet->data);
				// 清空
				sendData->count = 0;

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_QUEST_F2C_FINISHED_QUESTLIST_DATA_INFO::headSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------
			

			// 增加任务记录
			FINISHED_QUEST_DATA& finishedQuestData = sendData->data[sendData->count];
			finishedQuestData.questInfoId = front->second->questInfoId;
			finishedQuestData.endTime     = front->second->endTime;

			// 递增参数
			sendDataSize += PT_QUEST_F2C_FINISHED_QUESTLIST_DATA_INFO::questDataSize;
			++sendData->count;
			++front;   
		}

		//--------------------------------------------------------------------------
		// 如果有剩余则发送
		if ( dataPtr.isNull() == false)
		{
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, id);
			dataPtr.setNull();
		}
	}
	
	//--------------------------------------------------------------------------
	void QuestNetPacketProcesser::sendQuestConditionVariable( I32 id,U32 questInfoId,Byte varPos,Int varValue )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_QUEST;
			packet->type    = PT_QUEST_F2C_CONDITION_VAR;

			// 转换逻辑包
			PT_QUEST_F2C_CONDITION_VAR_DATA* sendData = (PT_QUEST_F2C_CONDITION_VAR_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->questInfoId = questInfoId;
				sendData->varValue = varValue;
				sendData->varPos = varPos;

				// 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_QUEST_F2C_CONDITION_VAR_DATA_INFO::dataSize, 
					id );
			}
		}
	}
}

