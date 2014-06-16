/******************************************************************************/

#include "stdafx.h"
#include "SPveNetPacketProcesser.h"
#include "ClientNetTranspondPacketProcesser.h"
#include "SPveManager.h"
#include "ServerManager.h"
#include "CenterServerMain.h"
#include "CenterServerMain.h"

/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	SPveNetPacketProcesser::SPveNetPacketProcesser()
	{
	}

	//--------------------------------------------------------------------------
	SPveNetPacketProcesser::~SPveNetPacketProcesser()
	{
	}

	//--------------------------------------------------------------------------
	Bool SPveNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_PVE )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PVE_F2T_CREATE:
				onRecvCreateFromFrontServer( id , (PT_PVE_F2T_CREATE_DATA*)data->data);
				break;
			case PT_PVE_F2T_ROOM_LIST:
				onRecvRoomListFromFrontServer( id , (PT_PVE_F2T_ROOM_LIST_DATA*)data->data);
				break;
			case PT_PVE_F2T_ENTER_ROOM:
				onRecvEnterRoomFromFrontServer( id , (PT_PVE_F2T_ENTER_ROOM_DATA*)data->data);
				break;
			case PT_PVE_F2T_LEAVE_ROOM:
				onRecvLeaveRoomFromFrontServer( id , (PT_PVE_F2T_LEAVE_ROOM_DATA*)data->data);
				break;
			case PT_PVE_F2T_START:
				onRecvStartRoomFromFrontServer( id , (PT_PVE_F2T_START_DATA*)data->data);
				break;
			case PT_PVE_M2T_START_NEW_INSTANCE:
				onRecvStartNewInstanceFromMapServer( id , (PT_PVE_M2T_START_NEW_INSTANCE_DATA*)data->data);
				break;
			case PT_PVE_F2T_DISCONNECT:
				onRecvDisconnectFromFrontServer( id , (PT_PVE_F2T_DISCONNECT_DATA*)data->data);
				break;
			case PT_PVE_F2T_KICK:
				onRecvKickFromFrontServer( id , (PT_PVE_F2T_KICK_DATA*)data->data);
				break;
			default:
				{
					DYNAMIC_ASSERT(0);
				}
				break;
			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::sendPveRoomListBeginToClient(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_ROOM_LIST_BEGIN;

		// 转换逻辑包
		PT_PVE_T2C_ROOM_LIST_BEGIN_DATA* sendData = (PT_PVE_T2C_ROOM_LIST_BEGIN_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包

		// 发送数据.
		ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr,
			GameNetPacketData_INFO::headSize + PT_PVE_T2C_ROOM_LIST_BEGIN_DATA_INFO::dataSize,
			frontserverNetId, clientNetId, accountId);
		
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::sendPveRoomListEndToClient(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr ;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_ROOM_LIST_END;

		// 转换逻辑包
		PT_PVE_T2C_ROOM_LIST_END_DATA* sendData = (PT_PVE_T2C_ROOM_LIST_END_DATA*)(packet->data);
		if ( sendData )
		{
			// 填充逻辑包

			// 发送数据.
			ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr,
				GameNetPacketData_INFO::headSize + PT_PVE_T2C_ROOM_LIST_END_DATA_INFO::dataSize,
				frontserverNetId, clientNetId, accountId);
		}
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::sendPveErrorToFrontServer(NetIdType frontserverNetId, Pve_Error error, NetIdType clientNetId, AccountIdType accountId)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr ;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();

		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_T2C_ERROR;

			// 转换逻辑包
			PT_PVE_T2C_ERROR_DATA* sendData = (PT_PVE_T2C_ERROR_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->error = error;

				// 发送数据.
				ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_PVE_T2C_ERROR_DATA_INFO::dataSize,frontserverNetId,
					clientNetId, accountId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::onRecvDisconnectFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_DISCONNECT_DATA* data )
	{
		PT_PVE_F2T_LEAVE_ROOM_DATA leaveData;
		leaveData.accountId		= data->accountId;
		leaveData.clientNetId	= 0;
		leaveData.roomId		= data->roomId;
		onRecvLeaveRoomFromFrontServer(frontServerNetId, &leaveData);
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::processFrontServerDisconnect(NetIdType frontServerNetId)
	{
		std::map<AccountIdType, SPveRoom*>* pveRoomList = SPveManager::getInstance().getPveRoomList();
		for (std::map<AccountIdType, SPveRoom*>::iterator roomIter = pveRoomList->begin(); roomIter != pveRoomList->end();++roomIter)
		{
			std::map<Pve_Position, SPveMember*>* memberList = roomIter->second->getMemberList();
			for (std::map<Pve_Position, SPveMember*>::iterator memberIter = memberList->begin(); memberIter != memberList->end();++memberIter)
			{
				SPveMember* member = memberIter->second;
				if (member->getFrontServerNetId() == frontServerNetId)
				{
					PT_PVE_F2T_LEAVE_ROOM_DATA leaveData;
					leaveData.accountId		= member->getAccountId();
					leaveData.clientNetId	= 0;
					leaveData.roomId		= roomIter->second->getRoomId();
					onRecvLeaveRoomFromFrontServer(frontServerNetId, &leaveData);
					if (pveRoomList->empty())
					{
						return;
					}
				}
			}
		}
		
	}
	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::onRecvRoomListFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_ROOM_LIST_DATA* data )
	{
		const NetIdType		clientNetId = data->clientNetId;
		const AccountIdType	accountId	= data->accountId;

		//--------------------------------------------------------------------------

		sendPveRoomListBeginToClient(frontServerNetId, clientNetId, accountId);

		//--------------------------------------------------------------------------

		ClientNetTranspondSendDataBufferPtr dataPtr;
		GameNetPacketData* packet       = NULL;
		PT_PVE_T2C_ROOM_LIST_DATA* sendData = NULL;
		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		std::map<AccountIdType, SPveRoom*>* pveRoomList = SPveManager::getInstance().getPveRoomList();
		// 遍历角色队列
		std::map<AccountIdType, SPveRoom*>::iterator iter = pveRoomList->begin();
		for(; iter != pveRoomList->end(); ++iter)
		{
			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_PVE_T2C_ROOM_LIST_DATA_INFO::netAddPveRoomInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(10) )
				{
					// 发送数据
					ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr,
						GameNetPacketData_INFO::headSize + PT_PVE_T2C_ROOM_LIST_DATA_INFO::dataSize(sendData),
						frontServerNetId, clientNetId, accountId);

					dataPtr.mDataPtr.setNull();
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE);
				packet		= (GameNetPacketData*) dataPtr.getTranspondData();

				if (NULL == packet)
				{
					DYNAMIC_ASSERT(0);
					return;
				}

				packet->channel = GNPC_PVE;
				packet->type    = PT_PVE_T2C_ROOM_LIST;

				sendData = (PT_PVE_T2C_ROOM_LIST_DATA*)(packet->data);
				sendData->addPveRoomNum = 0;

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PVE_T2C_ROOM_LIST_DATA_INFO::headSize;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------


			NetPveRoomInfo* netPveRoom = &(sendData->addPveRoomInfo[sendData->addPveRoomNum]);
			SPveRoom* tempPveRoom = iter->second;
			//填充 Begin
			netPveRoom->creatorAccountId	= tempPveRoom->getCreatorAccountId();
			netPveRoom->pveRoomId			= tempPveRoom->getRoomId();
			netPveRoom->targetRegionId		= tempPveRoom->getTargetRegionId();
			netPveRoom->memberNum			= tempPveRoom->getMemberNum();
			WStrnCpyS(netPveRoom->pveRoomName, tempPveRoom->getPveRoomName().c_str(), MAX_PVE_NAME);
			//填充 End

			sendDataSize += PT_PVE_T2C_ROOM_LIST_DATA_INFO::netAddPveRoomInfoSize;

			++sendData->addPveRoomNum;
		}

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr,
				GameNetPacketData_INFO::headSize + PT_PVE_T2C_ROOM_LIST_DATA_INFO::dataSize(sendData),
				frontServerNetId, clientNetId, accountId);

			dataPtr.mDataPtr.setNull() ;
		}

		//--------------------------------------------------------------------------

		sendPveRoomListEndToClient(frontServerNetId, clientNetId, accountId);
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::onRecvCreateFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_CREATE_DATA* data )
	{
		const AccountIdType accountId	= data->accountId;
		const NetIdType		clientNetId = data->clientNetId;

		SPveRoom* newPveRoom = SPveManager::getInstance().createPveRoom(data->accountId, data->pveRoomName);
		//初始化 newPveRoom
		newPveRoom->setTargetRegionId(data->targetRegionId);
		newPveRoom->setCreatorName(data->charName);

		//房主加进去
		SPveMember* leader = newPveRoom->addMember(accountId);
		leader->setAccountId(accountId);
		leader->setFrontServerNetId(frontServerNetId);
		leader->setClientNetId(clientNetId);
		leader->init(data->charArtIcon, data->level, data->charName);

		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();

		if(NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_CREATE;


		// 转换逻辑包
		PT_PVE_T2C_CREATE_DATA* sendData = (PT_PVE_T2C_CREATE_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		
		//填充数据包 Begin
		sendData->newPveRoomInfo.creatorAccountId	= accountId;
		sendData->newPveRoomInfo.pveRoomId			= newPveRoom->getRoomId();
		sendData->newPveRoomInfo.targetRegionId		= newPveRoom->getTargetRegionId();
		sendData->newPveRoomInfo.memberNum			= newPveRoom->getMemberNum();
		WStrnCpyS(sendData->newPveRoomInfo.pveRoomName, newPveRoom->getPveRoomName().c_str(), MAX_PVE_NAME);
		
		sendData->creatorInfo.accountId				= accountId;
		sendData->creatorInfo.position				= leader->getPosition();
		sendData->creatorInfo.charArtIcon			= data->charArtIcon;
		sendData->creatorInfo.charLevel				= data->level;
		WStrnCpyS(sendData->creatorInfo.characterName, data->charName, MAX_CHARACTER_NAME_LEN);
		//填充数据包 End

		// 发送数据.
		Int dataSize = GameNetPacketData_INFO::headSize + PT_PVE_T2C_CREATE_DATA_INFO::dataSize;
		
		//给自己发
		ServerManager::getInstance().sendNetPacketToFrontServer(frontServerNetId, dataPtr, dataSize);
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::onRecvEnterRoomFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_ENTER_ROOM_DATA* data )
	{
        //--------------------------------------------------------------------------

		const AccountIdType accountId	= data->accountId;
		const NetIdType		clientNetId = data->clientNetId;

		SPveRoom* pveRoom = SPveManager::getInstance().getPveRoom(data->roomId);
		if (NULL == pveRoom)
		{
			sendPveErrorToFrontServer(frontServerNetId, Pve_Error_Empty_Room , clientNetId, accountId);
			return ;
		}
		if (true == pveRoom->hasMember(accountId))
		{
			//已经加入
			sendPveErrorToFrontServer(frontServerNetId, Pve_Error_Has_Member , clientNetId, accountId);
			return ;
		}

		//--------------------------------------------------------------------------

		//初始化 newPveRoom
		SPveMember* newMember = pveRoom->addMember(accountId);
		newMember->setAccountId(accountId);
		newMember->setFrontServerNetId(frontServerNetId);
		newMember->setClientNetId(clientNetId);
		newMember->init(data->charArtIcon, data->charLevel, data->charName);

        //--------------------------------------------------------------------------

        std::map<Pve_Position, SPveMember*>* memberList = pveRoom->getMemberList();

        if ( memberList->size() > 1 )
        {
            ClientNetTranspondSendDataBufferPtr dataPtr;
            ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
            GameNetPacketData* packet   = (GameNetPacketData*) dataPtr.getTranspondData();
            if(NULL == packet) { DYNAMIC_ASSERT(0); return; }

            // 设置标签
            packet->channel = GNPC_PVE;
            packet->type    = PT_PVE_T2C_ENTER_ROOM;

            // 转换逻辑包
            PT_PVE_T2C_ENTER_ROOM_DATA* sendData = (PT_PVE_T2C_ENTER_ROOM_DATA*)(packet->data);
            if (NULL == sendData) {  DYNAMIC_ASSERT(0); return;  }

            // 填充逻辑包 Begin
            sendData->roomId					= data->roomId;
            sendData->memberInfo.accountId		= newMember->getAccountId();
            sendData->memberInfo.position		= newMember->getPosition();
            sendData->memberInfo.charArtIcon	= newMember->getCharIcon();
            sendData->memberInfo.charLevel		= newMember->getLevel();
            WStrnCpyS(sendData->memberInfo.characterName, data->charName, MAX_CHARACTER_NAME_LEN);
            // 填充逻辑包 End

            Int dataSize = GameNetPacketData_INFO::headSize + PT_PVE_T2C_ENTER_ROOM_DATA_INFO::dataSize;

            //开始广播
            for (std::map<Pve_Position, SPveMember*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
            {
                SPveMember* tempMemberInfo = iter->second;
                if (tempMemberInfo->getAccountId() == accountId)
                {
                    //不给自己发
                    continue;
                }

                //TODO: 要合并下转发包
                ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer( 
                    dataPtr, 
                    dataSize,
                    tempMemberInfo->getFrontServerNetId(), 
                    tempMemberInfo->getClientNetId(), 
                    tempMemberInfo->getAccountId() );

                CenterServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr.mDataPtr, dataPtr.mDataPtr, UInt(dataPtr.mDataPtr->getLogicDataSendSize()) );
            }
            if ( dataPtr.mDataPtr.isNull() == false )
            {
                dataPtr.mDataPtr.setNull();
            }
        }

		//--------------------------------------------------------------------------

		_sendMemberListToClient(memberList, newMember);
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::onRecvLeaveRoomFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_LEAVE_ROOM_DATA* data )
	{
		const AccountIdType accountId	= data->accountId;
		const NetIdType		clientNetId = data->clientNetId;

		SPveRoom* pveRoom = SPveManager::getInstance().getPveRoom(data->roomId);
		if (NULL == pveRoom)
		{
			sendPveErrorToFrontServer(frontServerNetId, Pve_Error_Empty_Room , clientNetId, accountId);
			return ;
		}

		if (pveRoom->getCreatorAccountId() == accountId)
		{
			//创建者离开， 摧毁房间
			_destroyRoom(data, pveRoom, frontServerNetId);
		}
		else
		{
			//普通玩家离开
			_leaveRoom(data, pveRoom, frontServerNetId);
		}
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::onRecvStartRoomFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_START_DATA* data )
	{
		const AccountIdType accountId	= data->accountId;
		const NetIdType		clientNetId = data->clientNetId;
		SPveRoom* pveRoom = SPveManager::getInstance().getPveRoom(data->roomId);

		//开始创建战斗对象
		if( NULL == pveRoom)
		{
			//不能发起战斗
			sendPveErrorToFrontServer(frontServerNetId, Pve_Error_Empty_Room, data->clientNetId, data->accountId);
			return ;
		}

		//不是房主
		if (pveRoom->getCreatorAccountId() != data->accountId)
		{
			sendPveErrorToFrontServer(frontServerNetId, Pve_Error_Start_No_Right, data->clientNetId, data->accountId);
			return ;
		}

		//--------------------------------------------------------------------------

		GameNetSendDataBufferPtr dataPtr;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_T2F_START;

			// 转换逻辑包
			PT_PVE_T2F_START_DATA* sendData = (PT_PVE_T2F_START_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId			= data->accountId;
				sendData->targetRegionId	= pveRoom->getTargetRegionId();
				sendData->roomId			= pveRoom->getRoomId();

				// 发送数据
				CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_PVE_T2F_START_DATA_INFO::dataSize, 
					frontServerNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::onRecvStartNewInstanceFromMapServer(NetIdType mapServerNetId, PT_PVE_M2T_START_NEW_INSTANCE_DATA* data)
	{
		SPveRoom* pveRoom = SPveManager::getInstance().getPveRoom(data->roomId);
		if (NULL == pveRoom)
		{
			DYNAMIC_ASSERT(0);
			return ;
		}

		std::map<Pve_Position, SPveMember*>* memberList = pveRoom->getMemberList();
		for (std::map<Pve_Position, SPveMember*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			_sendPveMemberJumpRegion(iter->second, data->targetRegionId, data->targetInstanceUId);
		}

		//从列表删除
		SPveManager::getInstance().delPveRoom(data->roomId);
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::onRecvKickFromFrontServer(NetIdType frontServerNetId, PT_PVE_F2T_KICK_DATA* data )
	{
		const AccountIdType accountId	= data->leaderAccountId;
		const NetIdType		clientNetId = data->leaderClientNetId;

		SPveRoom* pveRoom = SPveManager::getInstance().getPveRoom(data->roomId);
		if (NULL == pveRoom)
		{
			sendPveErrorToFrontServer(frontServerNetId, Pve_Error_Empty_Room , clientNetId, accountId);
			return ;
		}

		if (pveRoom->getCreatorAccountId() != data->leaderAccountId)
		{
			//senderrormsg
			sendPveErrorToFrontServer(frontServerNetId, Pve_Error_Kick, data->leaderClientNetId,data->leaderAccountId);
			return;
		}

		PT_PVE_F2T_LEAVE_ROOM_DATA leaveData;
		leaveData.roomId		= data->roomId;
		leaveData.accountId		= data->kickAccountId;
		leaveData.clientNetId	= data->leaderClientNetId;
		
		//普通玩家离开
		_leaveRoom(&leaveData, pveRoom, frontServerNetId);
		
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::_sendMemberListToClientBegin(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_MEMBER_LIST_BEGIN;

		// 转换逻辑包
		PT_PVE_T2C_MEMBER_LIST_BEGIN_DATA* sendData = (PT_PVE_T2C_MEMBER_LIST_BEGIN_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包

		// 发送数据.
		ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr,
			GameNetPacketData_INFO::headSize + PT_PVE_T2C_MEMBER_LIST_BEGIN_DATA_INFO::dataSize,
			frontserverNetId, clientNetId, accountId);
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::_sendMemberListToClient(std::map<Pve_Position, SPveMember*>* memberList, const SPveMember* newMember)
	{
		const AccountIdType accountId		 = newMember->getAccountId();
		const NetIdType		clientNetId		 = newMember->getClientNetId();
		const NetIdType		frontServerNetId = newMember->getFrontServerNetId();

		_sendMemberListToClientBegin(frontServerNetId, clientNetId, accountId);

		//--------------------------------------------------------------------------

		ClientNetTranspondSendDataBufferPtr dataPtr;
		GameNetPacketData* packet       = NULL;
		PT_PVE_T2C_MEMBER_LIST_DATA* sendData = NULL;

		// 当前发送数据头大小
		I32 sendDataHeadSize    = 0;
		// 当前发送数据大小
		I32 sendDataSize        = 0;
		// 准备发送数据大小
		I32 prepareSendDataSize = 0;

		// 遍历角色队列
		for(std::map<Pve_Position, SPveMember*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() == false  )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_PVE_T2C_MEMBER_LIST_DATA_INFO::netAddPveMemberInfoSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr.getTranspondDataMaxSize(10) )
				{
					// 发送数据
					ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
						dataPtr,
						GameNetPacketData_INFO::headSize + PT_PVE_T2C_MEMBER_LIST_DATA_INFO::dataSize(sendData),
						frontServerNetId, clientNetId, accountId);
					dataPtr.mDataPtr.setNull();
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.mDataPtr.isNull() )
			{
				ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE);
				packet		= (GameNetPacketData*) dataPtr.getTranspondData();

				if (NULL == packet)
				{
					DYNAMIC_ASSERT(0);
					return;
				}

				packet->channel = GNPC_PVE;
				packet->type    = PT_PVE_T2C_MEMBER_LIST;

				sendData = (PT_PVE_T2C_MEMBER_LIST_DATA*)(packet->data);
				sendData->addMemberNum = 0;

				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PVE_T2C_MEMBER_LIST_DATA_INFO::headSize;
				sendDataSize        = sendDataHeadSize;
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------

			NetPveMemberInfo* netPveMember = &(sendData->addMemberInfo[sendData->addMemberNum]);
			SPveMember* tempMember = iter->second;
			
			//填充 begin
			netPveMember->accountId		= tempMember->getAccountId();
			netPveMember->position		= tempMember->getPosition();
			netPveMember->charArtIcon	= tempMember->getCharIcon();
			netPveMember->charLevel		= tempMember->getLevel();
			WStrnCpyS(netPveMember->characterName, tempMember->getCharName().c_str(), MAX_CHARACTER_NAME_LEN);
			//填充 End

			sendDataSize += PT_PVE_T2C_MEMBER_LIST_DATA_INFO::netAddPveMemberInfoSize;

			++sendData->addMemberNum;
		}

		if ( dataPtr.mDataPtr.isNull() == false )
		{
			ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(
				dataPtr,
				GameNetPacketData_INFO::headSize + PT_PVE_T2C_MEMBER_LIST_DATA_INFO::dataSize(sendData),
				frontServerNetId, clientNetId, accountId);

			dataPtr.mDataPtr.setNull();
		}

		//--------------------------------------------------------------------------

		_sendMemberListToClientEnd(frontServerNetId, clientNetId, accountId);
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::_sendMemberListToClientEnd(NetIdType frontserverNetId, const NetIdType clientNetId,const AccountIdType accountId)
	{
		ClientNetTranspondSendDataBufferPtr dataPtr;
        ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtr );
		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_MEMBER_LIST_END;

		// 转换逻辑包
		PT_PVE_T2C_MEMBER_LIST_END_DATA* sendData = (PT_PVE_T2C_MEMBER_LIST_END_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包

		// 发送数据.
		ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer(dataPtr,
			GameNetPacketData_INFO::headSize + PT_PVE_T2C_MEMBER_LIST_END_DATA_INFO::dataSize,
			frontserverNetId, clientNetId, accountId);
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::_sendPveMemberJumpRegion(const SPveMember* pveMember, RegionIdType targetRegionId, InstanceUIdType targetInstanceUId)
	{
		GameNetSendDataBufferPtr dataPtr ;
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( NULL == packet )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2F_START_JUMP_REGION;

		// 转换逻辑包
		PT_PVE_T2F_START_JUMP_REGION_DATA* sendData = (PT_PVE_T2F_START_JUMP_REGION_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 填充逻辑包
		sendData->accountId			= pveMember->getAccountId();
		sendData->targetRegionId	= targetRegionId;
		sendData->targetInstanceUId	= targetInstanceUId;


		// 发送数据
		CenterServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
			GameNetPacketData_INFO::headSize + PT_PVE_T2F_START_JUMP_REGION_DATA_INFO::dataSize, 
			pveMember->getFrontServerNetId());
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::_destroyRoom(PT_PVE_F2T_LEAVE_ROOM_DATA* data, SPveRoom* pveRoom, NetIdType frontServerNetId)
	{
		GameNetSendDataBufferPtr dataPtr ;
		GameNetPacketData* packet = NULL;
		PT_PVE_T2C_DESTROY_ROOM_DATA* sendData = NULL;
		Int dataSize = GameNetPacketData_INFO::headSize + PT_PVE_T2C_DESTROY_ROOM_DATA_INFO::dataSize;

		//开始广播
		std::map<Pve_Position, SPveMember*>* memberList = pveRoom->getMemberList();
		for (std::map<Pve_Position, SPveMember*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			SPveMember* tempMemberInfo = iter->second;

			if ( dataPtr.isNull() )
			{
				CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );
				packet = (GameNetPacketData*) dataPtr->getLogicData();

				if(NULL == packet)
				{
					DYNAMIC_ASSERT(0);
					return;
				}

				// 设置标签
				packet->channel = GNPC_PVE;
				packet->type    = PT_PVE_T2C_DESTROY_ROOM;

				// 转换逻辑包
				sendData = (PT_PVE_T2C_DESTROY_ROOM_DATA*)(packet->data);
				if (NULL == sendData)
				{
					DYNAMIC_ASSERT(0);
					return;
				}
			}

			// 填充数据包
			sendData->accountId		= tempMemberInfo->getAccountId();
			sendData->roomId		= pveRoom->getRoomId();

			//给所有人发
			ServerManager::getInstance().sendNetPacketToFrontServer(frontServerNetId, dataPtr, dataSize);

			dataPtr.setNull();
		}
	
		//--------------------------------------------------------------------------

		//删除房间
		SPveManager::getInstance().delPveRoom(data->roomId);

	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcesser::_leaveRoom(PT_PVE_F2T_LEAVE_ROOM_DATA* data, SPveRoom* pveRoom, NetIdType frontServerNetId)
	{
		const AccountIdType accountId	= data->accountId;
		const NetIdType		clientNetId = data->clientNetId;

        //--------------------------------------------------------------------------

		if (false == pveRoom->hasMember(accountId))
		{
			//此玩家不在此房间
			return;
		}

        //--------------------------------------------------------------------------
		ClientNetTranspondSendDataBufferPtr dataPtrOther;
		GameNetSendDataBufferPtr dataPtrMe ;
		Int dataSize = GameNetPacketData_INFO::headSize + PT_PVE_T2C_LEAVE_ROOM_DATA_INFO::dataSize;

        //--------------------------------------------------------------------------
        //给自己发
        if ( dataPtrMe.isNull() == false )
        {
            CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtrMe );

            // 转换成标准包格式
            GameNetPacketData* packet = (GameNetPacketData*) dataPtrMe->getLogicData();
            if(NULL == packet) { DYNAMIC_ASSERT(0); return; }
            // 设置标签
            packet->channel = GNPC_PVE;
            packet->type    = PT_PVE_T2C_LEAVE_ROOM;
            // 转换逻辑包
            PT_PVE_T2C_LEAVE_ROOM_DATA* sendData = (PT_PVE_T2C_LEAVE_ROOM_DATA*)(packet->data);
            if (NULL == sendData) { DYNAMIC_ASSERT(0); return;  }
            // 填充数据包 Begin
            sendData->accountId		= accountId;
            sendData->roomId		= pveRoom->getRoomId();
        }

        ServerManager::getInstance().sendNetPacketToFrontServer(
            frontServerNetId, 
            dataPtrMe, 
            dataSize);

        dataPtrMe.setNull();

        //--------------------------------------------------------------------------

		//开始广播
        std::map<Pve_Position, SPveMember*>* memberList = pveRoom->getMemberList();
		for (std::map<Pve_Position, SPveMember*>::iterator iter = memberList->begin(); iter != memberList->end(); ++iter)
		{
			SPveMember* tempMemberInfo = iter->second;
			if (tempMemberInfo->getAccountId() != accountId)
			{
                if ( dataPtrOther.mDataPtr.isNull() == false )
                {
                    ClientNetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer( dataPtrOther );

                    // 转换成标准包格式
                    GameNetPacketData* packet = (GameNetPacketData*) dataPtrOther.getTranspondData();
                    if(NULL == packet) { DYNAMIC_ASSERT(0); return; }
                    // 设置标签
                    packet->channel = GNPC_PVE;
                    packet->type    = PT_PVE_T2C_LEAVE_ROOM;
                    // 转换逻辑包
                    PT_PVE_T2C_LEAVE_ROOM_DATA* sendData = (PT_PVE_T2C_LEAVE_ROOM_DATA*)(packet->data);
                    if (NULL == sendData) { DYNAMIC_ASSERT(0); return;  }
                    // 填充数据包 Begin
                    sendData->accountId		= accountId;
                    sendData->roomId		= pveRoom->getRoomId();
                }

				//其他人要转发
				ClientNetTranspondPacketProcesser::getInstance().sendClientTranspondSendDataToFrontServer( 
                    dataPtrOther, 
                    dataSize,
					tempMemberInfo->getFrontServerNetId(), 
                    tempMemberInfo->getClientNetId(), 
                    tempMemberInfo->getAccountId() );

                dataPtrOther.mDataPtr.setNull();
			}
		}
       
		//--------------------------------------------------------------------------

		//删除内存
		pveRoom->delMember(accountId);
	}
}
