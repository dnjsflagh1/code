
/******************************************************************************/
#include "stdafx.h"
#include "CPveNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "UIPveCreate.h"
#include "CPlayer.h"
#include "UIMessageBox.h"
/******************************************************************************/

namespace MG
{
	Bool CPveNetPacketProcesser::processFrontServerPacket(I32 id,NetEventRecv* packet)
	{
		if (packet->getChannel() == GNPC_PVE)
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PVE_T2C_ERROR:
				onRecvPveError( id, (PT_PVE_T2C_ERROR_DATA*)data->data );
				break;
			case PT_PVE_T2C_CREATE:
				onRecvPveCreate( id, (PT_PVE_T2C_CREATE_DATA*)data->data );
				break;
			case PT_PVE_T2C_ROOM_LIST_BEGIN:
				onRecvPveRoomListBegin( id, (PT_PVE_T2C_ROOM_LIST_BEGIN_DATA*)data->data );
				break;
			case PT_PVE_T2C_ROOM_LIST:
				onRecvPveRoomList( id, (PT_PVE_T2C_ROOM_LIST_DATA*)data->data );
				break;
			case PT_PVE_T2C_ROOM_LIST_END:
				onRecvPveRoomListEnd( id, (PT_PVE_T2C_ROOM_LIST_END_DATA*)data->data );
				break;
			case PT_PVE_T2C_ENTER_ROOM:
				onRecvEnterRoom( id, (PT_PVE_T2C_ENTER_ROOM_DATA*)data->data );
				break;
			case PT_PVE_T2C_MEMBER_LIST_BEGIN:
				onRecvMemberListBegin( id, (PT_PVE_T2C_MEMBER_LIST_BEGIN_DATA*)data->data );
				break;
			case PT_PVE_T2C_MEMBER_LIST:
				onRecvMemberList( id, (PT_PVE_T2C_MEMBER_LIST_DATA*)data->data );
				break;
			case PT_PVE_T2C_MEMBER_LIST_END:
				onRecvMemberListEnd( id, (PT_PVE_T2C_MEMBER_LIST_END_DATA*)data->data );
				break;
			case PT_PVE_T2C_LEAVE_ROOM:
				onRecvLeaveRoom( id, (PT_PVE_T2C_LEAVE_ROOM_DATA*)data->data );
				break;
			case PT_PVE_T2C_DESTROY_ROOM:
				onRecvDestroyRoom( id, (PT_PVE_T2C_DESTROY_ROOM_DATA*)data->data );
				break;
			case PT_PVE_F2C_START:
				onRecvPveStart( id, (PT_PVE_F2C_START_DATA*)data->data );
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}
			return true;
		}
		return false;
	}

	void CPveNetPacketProcesser::sendPveRoomList()
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_C2F_ROOM_LIST;

		// 转换逻辑包
		PT_PVE_C2F_ROOM_LIST_DATA* sendData = (PT_PVE_C2F_ROOM_LIST_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包
		//sendData->creatorClanId	=creatorClanId;
		//sendData->targetRegionId = targetRegionId;
		//WStrnCpyS(sendData->campaignName, campaignName, MAX_CAMPAIGN_NAME);

		// 发送数据
		ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
			GameNetPacketData_INFO::headSize + PT_PVE_C2F_ROOM_LIST_DATA_INFO::dataSize );
	}

	void CPveNetPacketProcesser::sendPveCreate(AccountIdType creatorAccountId, RegionIdType targetRegionId, const Char16* pveName)
	{
		///////////////////////////////////////////////////////////////////////////

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );


		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_C2F_CREATE;

		// 转换逻辑包
		PT_PVE_C2F_CREATE_DATA* sendData = (PT_PVE_C2F_CREATE_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包
		sendData->creatorAccountId	= creatorAccountId;
		sendData->targetRegionId	= targetRegionId;
		WStrnCpyS(sendData->pveName, pveName, MAX_PVE_NAME);

		// 发送数据
		ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
			GameNetPacketData_INFO::headSize + PT_PVE_C2F_CREATE_DATA_INFO::dataSize );
	}

	void CPveNetPacketProcesser::sendPveEnterRoom(int roomId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_C2F_ENTER_ROOM;

		// 转换逻辑包
		PT_PVE_C2F_ENTER_ROOM_DATA* sendData = (PT_PVE_C2F_ENTER_ROOM_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包
		sendData->roomId		= roomId;

		// 发送数据
		ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
			GameNetPacketData_INFO::headSize + PT_PVE_C2F_ENTER_ROOM_DATA_INFO::dataSize );
	}

	void CPveNetPacketProcesser::sendPveLeaveRoom(AccountIdType accountId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_C2F_LEAVE_ROOM;

		// 转换逻辑包
		PT_PVE_C2F_LEAVE_ROOM_DATA* sendData = (PT_PVE_C2F_LEAVE_ROOM_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包
		sendData->accountId = accountId;

		// 发送数据
		ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
			GameNetPacketData_INFO::headSize + PT_PVE_C2F_LEAVE_ROOM_DATA_INFO::dataSize );
	}

	void CPveNetPacketProcesser::sendPveStart(AccountIdType accountId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_C2F_START;

		// 转换逻辑包
		PT_PVE_C2F_START_DATA* sendData = (PT_PVE_C2F_START_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包
		sendData->accountId = accountId;

		// 发送数据
		ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
			GameNetPacketData_INFO::headSize + PT_PVE_C2F_START_DATA_INFO::dataSize );
	}

	void CPveNetPacketProcesser::sendPveKickMember(AccountIdType leaderAccountId, AccountIdType kickAccountId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_C2F_KICK;

		// 转换逻辑包
		PT_PVE_C2F_KICK_DATA* sendData = (PT_PVE_C2F_KICK_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包
		sendData->leaderAccountId	= leaderAccountId;
		sendData->kickAccountId		= kickAccountId;

		// 发送数据
		ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
			GameNetPacketData_INFO::headSize + PT_PVE_C2F_KICK_DATA_INFO::dataSize );
	}

	void CPveNetPacketProcesser::onRecvPveError(I32 id, PT_PVE_T2C_ERROR_DATA* data)
	{
		switch (data->error)
		{
		case Pve_Error_Full_Member:
			UIMessageBox::getInstance().showHint(L"房间满人");
			CPveNetPacketProcesser::getInstance().sendPveRoomList();
			break;
		case Pve_Error_Has_Member:
			UIMessageBox::getInstance().showHint(L"已经加入");
			CPveNetPacketProcesser::getInstance().sendPveRoomList();
			break;
		case Pve_Error_Start_No_Right:
			UIMessageBox::getInstance().showHint(L"无权限开始");
			break;
		case Pve_Error_Empty_Room:
		case Pve_Error_Kick:
			CPveNetPacketProcesser::getInstance().sendPveRoomList();
			break;
		default:
			DYNAMIC_ASSERT(0);
			break;
		}
	}

	void CPveNetPacketProcesser::onRecvPveCreate(I32 id, PT_PVE_T2C_CREATE_DATA* data)
	{
		UIPveCreate::getInstance().addPveRoom(1, &(data->newPveRoomInfo));

		UIPveCreate::getInstance().addPveMember(1, &(data->creatorInfo));
	
		UIPveCreate::getInstance().openGui();
	}

	void CPveNetPacketProcesser::onRecvPveRoomListBegin(I32 id, PT_PVE_T2C_ROOM_LIST_BEGIN_DATA* data)
	{
		UIPveCreate::getInstance().clearPveRoom();
	}

	void CPveNetPacketProcesser::onRecvPveRoomList(I32 id, PT_PVE_T2C_ROOM_LIST_DATA* data)
	{
		UIPveCreate::getInstance().addPveRoom(data->addPveRoomNum, data->addPveRoomInfo);
	}

	void CPveNetPacketProcesser::onRecvPveRoomListEnd(I32 id, PT_PVE_T2C_ROOM_LIST_END_DATA* data)
	{
		UIPveCreate::getInstance().openGui();
	}

	void CPveNetPacketProcesser::onRecvEnterRoom(I32 id, PT_PVE_T2C_ENTER_ROOM_DATA* data)
	{
		UIPveCreate::getInstance().addPveMember(1, &(data->memberInfo));
		UIPveCreate::getInstance().openGui();
	}

	void CPveNetPacketProcesser::onRecvLeaveRoom(I32 id, PT_PVE_T2C_LEAVE_ROOM_DATA* data)
	{
		const AccountIdType myAccountId = CPlayer::getInstance().getAccountID();
		if (myAccountId == data->accountId)
		{
			//我自己离开
			UIPveCreate::getInstance().clearPveMember();
			UIPveCreate::getInstance().openGui();
		}
		else
		{
			//别人离开
			UIPveCreate::getInstance().delPveMember(data->accountId);
			UIPveCreate::getInstance().openGui();
		}
	}

	void CPveNetPacketProcesser::onRecvDestroyRoom(I32 id, PT_PVE_T2C_DESTROY_ROOM_DATA* data)
	{
		const AccountIdType myAccountId = CPlayer::getInstance().getAccountID();

		UIPveCreate::getInstance().delPveRoom(data->roomId);
		UIPveCreate::getInstance().clearPveMember();
		UIPveCreate::getInstance().openGui();
	}

	void CPveNetPacketProcesser::onRecvPveStart(I32 id, PT_PVE_F2C_START_DATA* data)
	{
		UIPveCreate::getInstance().clearPveMember();
	}

	void CPveNetPacketProcesser::onRecvMemberListBegin(I32 id, PT_PVE_T2C_MEMBER_LIST_BEGIN_DATA* data)
	{
		UIPveCreate::getInstance().clearPveMember();
	}

	void CPveNetPacketProcesser::onRecvMemberList(I32 id, PT_PVE_T2C_MEMBER_LIST_DATA* data)
	{
		UIPveCreate::getInstance().addPveMember(data->addMemberNum, data->addMemberInfo);
	}

	void CPveNetPacketProcesser::onRecvMemberListEnd(I32 id, PT_PVE_T2C_MEMBER_LIST_END_DATA* data)
	{
		UIPveCreate::getInstance().openGui();
	}
}