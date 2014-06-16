
/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "CGeneralRecruitNetPacketProcessor.h"
#include "CPlayer.h"
#include "UIRecruitGeneral.h"
#include "MessageManager.h"
#include "UIClanInfo.h"
#include "UIChangeRecruit.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	Bool CGeneralRecruitNetPacketProcessor::processFrontServerPacket(I32 id, NetEventRecv *packet)
	{
		if ( packet->getChannel() == GNPC_GENERAL_RECRUIT )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN:
				onRecvRandomGeneralListBeginFromFrontServer( id, (PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_DATA*)data->data );
				break;
			case PT_GR_F2C_RANDOM_GENERAL_LIST:
				onRecvRandomGeneralListFromFrontServer( id, (PT_GR_F2C_RANDOM_GENERAL_LIST_DATA*)data->data );
				break;
			case PT_GR_F2C_RANDOM_GENERAL_LIST_END:
				onRecvRandomGeneralListEndFromFrontServer( id, (PT_GR_F2C_RANDOM_GENERAL_LIST_END_DATA*)data->data );
				break;
			case PT_GR_F2C_GENERAL_RECRUIT_RESUILT:
				onRecvRecruitResultFromFrontServer( id, (PT_GR_F2C_GENERAL_RECRUIT_RESUILT_DATA*)data->data );
				break;
			case PT_GR_F2C_GENERAL_RECRUIT_CONFIRM:
				onRecvRecruitConfirmFromFrontServer( id, (PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_DATA*)data->data );
				break;
			//case PT_GR_F2C_CLEAR_CLAN:
			//	onRecvClientGenrealInfoFromFrontServer( id, (PT_GR_F2C_CLEAR_CLAN_DATA*)data->data );
			//	break;
			case PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN:
				onRecvRecruitGeneralListBeginFromFrontServer( id, (PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_DATA*)data->data );
				break;
			case PT_GR_F2C_RECRUIT_GENERAL_LIST:
				onRecvRecruitGeneralListFromFrontServer( id, (PT_GR_F2C_RECRUIT_GENERAL_LIST_DATA*)data->data );
				break;
			case PT_GR_F2C_RECRUIT_GENERAL_LIST_END:
				onRecvRecruitGeneralListEndFromFrontServer( id, (PT_GR_F2C_RECRUIT_GENERAL_LIST_END_DATA*)data->data );
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}
			return true;
		}
		return false;
	}

	void CGeneralRecruitNetPacketProcessor::onRecvRandomGeneralListBeginFromFrontServer( I32 id, PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_DATA* data )
	{
		UIRecruitGeneral::getInstance().clearRecruitGeneralList();
	}

	void CGeneralRecruitNetPacketProcessor::onRecvRandomGeneralListFromFrontServer( I32 id, PT_GR_F2C_RANDOM_GENERAL_LIST_DATA* data )
	{
		DYNAMIC_ASSERT(data->addGeneralNum > 0 && data->addGeneralNum <= RECRUIT_POSITION_MAX);
		for (Int i=0; i<(Int)data->addGeneralNum; ++i)
		{
			UIRecruitGeneral::getInstance().loadGeneralInfos(&(data->addGeneralInfo[i]));
		}
	}	

	void CGeneralRecruitNetPacketProcessor::onRecvRandomGeneralListEndFromFrontServer( I32 id, PT_GR_F2C_RANDOM_GENERAL_LIST_END_DATA* data )
	{
		if (UIRecruitGeneral::getInstance().isOpen())
		{
			UIRecruitGeneral::getInstance().UIFresh();
		} 
		else
		{
			UIRecruitGeneral::getInstance().openGui();
		}
		
	}

	//-----------------------------------------------------------------------------
	void CGeneralRecruitNetPacketProcessor::onRecvClientGenrealInfoFromFrontServer( I32 id, PT_GR_F2C_CLEAR_CLAN_DATA* data )
	{
		CPlayer::getInstance().deleteAllClan();
	}

	void CGeneralRecruitNetPacketProcessor::onRecvRecruitConfirmFromFrontServer( I32 id, PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_DATA* data )
	{
		RecruitGeneralInfo* generalInfo = UIRecruitGeneral::getInstance().getGeneralInfoByIndex(data->index);
		generalInfo->hasRecruit = true;

		UIRecruitGeneral::getInstance().UIFresh();
	}

	void CGeneralRecruitNetPacketProcessor::onRecvRecruitResultFromFrontServer( I32 id, PT_GR_F2C_GENERAL_RECRUIT_RESUILT_DATA* data )
	{
		const Recruit_Result result = (Recruit_Result)data->result;
		if (result == Recruit_Result_Success)
		{
			//UIRecruitGeneral::getInstance().closeGui();
			MessageManager::getInstance().addChatMsgForTest(L"招募成功");
		}
		else
		{
			if (Recruit_Result_Full == result)
			{
				MessageManager::getInstance().addChatMsgForTest(L"超出武将招募数");
			}
			else
			{
				MessageManager::getInstance().addChatMsgForTest(L"招募失败");
			}
		}
	}

	void CGeneralRecruitNetPacketProcessor::onRecvRecruitGeneralListBeginFromFrontServer( I32 id, PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_DATA* data )
	{
		CClan* activeClan = CPlayer::getInstance().getActiveClan();
		if (NULL == activeClan)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		UIChangeRecruit::getInstance().clearRecruitGeneralList();
	}

	void CGeneralRecruitNetPacketProcessor::onRecvRecruitGeneralListFromFrontServer( I32 id, PT_GR_F2C_RECRUIT_GENERAL_LIST_DATA* data )
	{
		//CClan* activeClan = CPlayer::getInstance().getActiveClan();
		//if (NULL == activeClan)
		//{
		//	DYNAMIC_ASSERT(0);
		//	return;
		//}

		DYNAMIC_ASSERT(data->addGeneralNum >= 0 && data->addGeneralNum <= 10);
		for (Int i=0; i<data->addGeneralNum; ++i)
		{
			UIChangeRecruit::getInstance().loadRecruitGeneralInfo(&(data->addGeneralInfo[i]));
		}
	}

	void CGeneralRecruitNetPacketProcessor::onRecvRecruitGeneralListEndFromFrontServer( I32 id, PT_GR_F2C_RECRUIT_GENERAL_LIST_END_DATA* data )
	{
		if (UIChangeRecruit::getInstance().isOpen())
		{
			UIChangeRecruit::getInstance().UIFresh();
		}
	}

	//-----------------------------------------------------------------------------
	void CGeneralRecruitNetPacketProcessor::sendFreshRandomGeneral(U32 GeneralRecruitId)
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_C2F_FRESH_RANDOM_GENERAL;

			// 转换逻辑包
			PT_GR_C2F_FRESH_RANDOM_GENERAL_DATA* sendData = (PT_GR_C2F_FRESH_RANDOM_GENERAL_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->GeneralRecruitId = GeneralRecruitId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_GR_C2F_FRESH_RANDOM_GENERAL_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------------
	void CGeneralRecruitNetPacketProcessor::sendGetRandomGeneralList(U32 GeneralRecruitId)
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_C2F_RANDOM_GENERAL_LIST;

			// 转换逻辑包
			PT_GR_C2F_RANDOM_GENERAL_LIST_DATA* sendData = (PT_GR_C2F_RANDOM_GENERAL_LIST_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->GeneralRecruitId	= GeneralRecruitId;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_GR_C2F_RANDOM_GENERAL_LIST_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------------
	void CGeneralRecruitNetPacketProcessor::sendGeneralRecruit(RECRUIT_POSITION index)
	{
		DYNAMIC_ASSERT(index >= RECRUIT_POSITION_1 && index < RECRUIT_POSITION_MAX);

		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_C2F_GENERAL_RECRUIT_CONFIRM;

			// 转换逻辑包
			PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_DATA* sendData = (PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->index	= index;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------------
	void CGeneralRecruitNetPacketProcessor::sendChangeGeneral(PlayerCharacterIdType charId)
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_C2F_CHANGE_GENERAL;

			// 转换逻辑包
			PT_GR_C2F_CHANGE_GENERAL_DATA* sendData = (PT_GR_C2F_CHANGE_GENERAL_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->charId	= charId;
				//sendData->regionType = regionType;

				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + PT_GR_C2F_CHANGE_GENERAL_INFO::dataSize );
			}
		}
	}

	//-----------------------------------------------------------------------------
}	//namespace MG