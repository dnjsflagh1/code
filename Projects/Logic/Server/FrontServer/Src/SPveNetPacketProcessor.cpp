
/******************************************************************************/

#include "stdafx.h"
#include "SPveNetPacketProcessor.h"
#include "SWorldManager.h"
#include "FrontServerMain.h"
#include "ServerManager.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "PlayerNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	SPveNetPacketProcessor::SPveNetPacketProcessor()
	{

	}

	//--------------------------------------------------------------------------
	SPveNetPacketProcessor::~SPveNetPacketProcessor()
	{

	}

	//--------------------------------------------------------------------------
	Bool SPveNetPacketProcessor::processCenterServerPacket(I32 id, NetEventRecv* packet)
	{
		if (packet->getChannel() == GNPC_PVE)
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case  PT_PVE_T2C_CREATE:
				onRecvCreateRoomFromCenterServer( id , (PT_PVE_T2C_CREATE_DATA*)data->data);
				break;
			case  PT_PVE_T2C_LEAVE_ROOM:
				onRecvLeaveRoomFromCenterServer( id , (PT_PVE_T2C_LEAVE_ROOM_DATA*)data->data);
				break;
			case  PT_PVE_T2C_DESTROY_ROOM:
				onRecvDestroyRoomFromCenterServer( id , (PT_PVE_T2C_DESTROY_ROOM_DATA*)data->data);
				break;
			case PT_PVE_T2F_START:
				onRecvStartRoomFromCenterServer( id , (PT_PVE_T2F_START_DATA*)data->data);
				break;
			case PT_PVE_T2F_START_JUMP_REGION:
				onRecvStartJumpRegionFromCenterServer( id , (PT_PVE_T2F_START_JUMP_REGION_DATA*)data->data);
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
	Bool SPveNetPacketProcessor::processClientPacket(I32 id, NetEventRecv* packet)
	{
		if (packet->getChannel() == GNPC_PVE)
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case  PT_PVE_C2F_CREATE:
				onRecvPveCreateFromClient( id , (PT_PVE_C2F_CREATE_DATA*)data->data);
				break;
			case PT_PVE_C2F_ROOM_LIST:
				onRecvPveRoomListFromClient( id , (PT_PVE_C2F_ROOM_LIST_DATA*)data->data);
				break;
			case PT_PVE_C2F_ENTER_ROOM:
				onRecvPveEnterRoomFromClient( id , (PT_PVE_C2F_ENTER_ROOM_DATA*)data->data);
				break;
			case PT_PVE_C2F_LEAVE_ROOM:
				onRecvPveLeaveRoomFromClient( id , (PT_PVE_C2F_LEAVE_ROOM_DATA*)data->data);
				break;
			case PT_PVE_C2F_START:
				onRecvPveStartFromClient( id , (PT_PVE_C2F_START_DATA*)data->data);
				break;
			case PT_PVE_C2F_KICK:
				onRecvPveKickFromClient( id , (PT_PVE_C2F_KICK_DATA*)data->data);
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
	void SPveNetPacketProcessor::onRecvPveCreateFromClient(I32 id, PT_PVE_C2F_CREATE_DATA* data)
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			return;
		}

		SClanPtr clan;
		player->getMainClan(clan);

		//SClan* clan = player->getMainClan();
		//if (NULL == clan)
		//{
		//	//send error msg to client
		//	return;
		//}

		SPlayerCharacterPtr myChar;
		clan->getMainPlayerCharacter(myChar);

		//SPlayerCharacter* myChar = clan->getMainPlayerCharacter();
		//if (NULL == clan)
		//{
		//	return;
		//}

		//--------------------------------------------------------------------------

		//sendCampaignCreateToCenterServer(data, clan, player);
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2T_CREATE;

			// 转换逻辑包
			PT_PVE_F2T_CREATE_DATA* sendData = (PT_PVE_F2T_CREATE_DATA*)(packet->data);
			if ( sendData )
			{
				//填充逻辑包
				sendData->accountId			= player->getAccountID();
				sendData->clientNetId		= player->getClientNetID();
				sendData->charArtIcon		= myChar->getData()->charArtIcon;
				sendData->level				= myChar->getData()->mLevel;
				sendData->targetRegionId	= data->targetRegionId;
				WStrnCpyS(sendData->charName, myChar->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				WStrnCpyS(sendData->pveRoomName, data->pveName, MAX_PVE_NAME);

				// 发送数据
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_PVE_F2T_CREATE_DATA_INFO::dataSize );
			}
		}
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvPveRoomListFromClient( I32 id, PT_PVE_C2F_ROOM_LIST_DATA* data )
	{
		//if (ServerManager::getInstance().getCenterServerNetID() < 0)
		//{
		//	//CenterServer 当机
		//	
		//	return;
		//}
		SPlayerPtr player;
		//= SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			return;
		}

		SClanPtr clan;
		player->getMainClan(clan);
		//SClan* clan = player->getMainClan();
		//if (NULL == clan)
		//{
		//	//send error msg to client
		//	return;
		//}

		//--------------------------------------------------------------------------

		//sendCampaignCreateToCenterServer(data, clan, player);
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_F2T_ROOM_LIST;

		// 转换逻辑包
		PT_PVE_F2T_ROOM_LIST_DATA* sendData = (PT_PVE_F2T_ROOM_LIST_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//填充逻辑包
		sendData->accountId		    		= player->getAccountID();
		sendData->clientNetId				= player->getClientNetID();
		//sendData->creatorClanId	    		= data->creatorClanId;
		//sendData->creatorPlayerCharacterId	= clan->getMainPlayerCharacter()->getID();
		//sendData->targetRegionId			= data->targetRegionId;
		//WStrnCpyS(sendData->creatorClanName, clan->getData()->clanName.c_str(), MAX_CLAN_NAME);
		//WStrnCpyS(sendData->creatorPlayerCharacterName, clan->getMainPlayerCharacter()->getName().c_str(), MAX_CHARACTER_NAME_LEN);
		//WStrnCpyS(sendData->campaignName, data->campaignName, MAX_CAMPAIGN_NAME);

		// 发送数据
		ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
			GameNetPacketData_INFO::headSize + PT_PVE_F2T_ROOM_LIST_DATA_INFO::dataSize );
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvPveEnterRoomFromClient(I32 id, PT_PVE_C2F_ENTER_ROOM_DATA* data)
	{
		SPlayerPtr player;
		//= SWorldManager::getInstance().getPlayerByClientNetId(id);
		//if (player.isNull())
		//{
		//	//
		//	DYNAMIC_ASSERT(0);
		//	return;
		//}

		SClanPtr clan;
		player->getMainClan(clan);
		//SClan* clan = player->getMainClan();
		//if (NULL == clan)
		//{
		//	//send error msg to client
		//	DYNAMIC_ASSERT(0);
		//	return;
		//}
#if 0
		SPlayerCharacter* myChar = clan->getMainPlayerCharacter();
		if (NULL == myChar)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//设置 pve房间ID
		player->setPveRoomId(data->roomId);

		///////////////////////////////////////////////////////////////////////////
		//sendCampaignCreateToCenterServer(data, clan, player);
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_F2T_ENTER_ROOM;

		// 转换逻辑包
		PT_PVE_F2T_ENTER_ROOM_DATA* sendData = (PT_PVE_F2T_ENTER_ROOM_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//填充逻辑包
		sendData->accountId			= player->getAccountID();
		sendData->clientNetId		= player->getClientNetID();
		sendData->charArtIcon		= myChar->getData()->charArtIcon;
		sendData->charLevel			= myChar->getData()->mLevel;
		WStrnCpyS(sendData->charName, myChar->getName().c_str(), MAX_CHARACTER_NAME_LEN);
		sendData->roomId			= data->roomId;
		
		// 发送数据
		ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
			GameNetPacketData_INFO::headSize + PT_PVE_F2T_ENTER_ROOM_DATA_INFO::dataSize );
#endif
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvPveLeaveRoomFromClient(I32 id, PT_PVE_C2F_LEAVE_ROOM_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			DYNAMIC_ASSERT(0);
			return;
		}
		if (data->accountId != player->getAccountID())
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		SClan* clan = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			DYNAMIC_ASSERT(0);
			return;
		}

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2T_LEAVE_ROOM;

			// 转换逻辑包
			PT_PVE_F2T_LEAVE_ROOM_DATA* sendData = (PT_PVE_F2T_LEAVE_ROOM_DATA*)(packet->data);
			if ( sendData )
			{
				//填充逻辑包
				sendData->accountId			= player->getAccountID();
				sendData->clientNetId		= player->getClientNetID();
				sendData->roomId			= player->getPveRoomId();

				// 发送数据
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_PVE_F2T_LEAVE_ROOM_DATA_INFO::dataSize );
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvPveStartFromClient(I32 id, PT_PVE_C2F_START_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			DYNAMIC_ASSERT(0);
			return;
		}
		if (data->accountId != player->getAccountID())
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		SClan* clan = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			DYNAMIC_ASSERT(0);
			return;
		}

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2T_START;

			// 转换逻辑包
			PT_PVE_F2T_START_DATA* sendData = (PT_PVE_F2T_START_DATA*)(packet->data);
			if ( sendData )
			{
				//填充逻辑包
				sendData->accountId			= player->getAccountID();
				sendData->roomId			= player->getPveRoomId();

				// 发送数据
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_PVE_F2T_START_DATA_INFO::dataSize );
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvPveKickFromClient(I32 id, PT_PVE_C2F_KICK_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByClientNetId(id);
		if (player.isNull())
		{
			//
			return;
		}

		SClan* clan = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			DYNAMIC_ASSERT(0);
			return;
		}

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2T_KICK;

			// 转换逻辑包
			PT_PVE_F2T_KICK_DATA* sendData = (PT_PVE_F2T_KICK_DATA*)(packet->data);
			if ( sendData )
			{
				//填充逻辑包
				sendData->roomId			= player->getPveRoomId();
				sendData->leaderClientNetId		= player->getClientNetID();
				sendData->leaderAccountId	= data->leaderAccountId;
				sendData->kickAccountId		= data->kickAccountId;

				// 发送数据
				ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_PVE_F2T_KICK_DATA_INFO::dataSize );
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvLeaveRoomFromCenterServer(I32 id, PT_PVE_T2C_LEAVE_ROOM_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByAccountId(data->accountId);
		if (player.isNull())
		{
			//
			return;
		}

		SClan* clan = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			DYNAMIC_ASSERT(0);
			return;
		}

		//清空pve房间id
		player->setPveRoomId(0);

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_LEAVE_ROOM;

		// 转换逻辑包
		PT_PVE_T2C_LEAVE_ROOM_DATA* sendData = (PT_PVE_T2C_LEAVE_ROOM_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//填充逻辑包
		sendData->accountId			= player->getAccountID();
		sendData->roomId			= data->roomId;


		// 发送数据
		FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
			GameNetPacketData_INFO::headSize + PT_PVE_T2C_LEAVE_ROOM_DATA_INFO::dataSize, 
			player->getClientNetID());
#endif
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvDestroyRoomFromCenterServer(I32 id, PT_PVE_T2C_DESTROY_ROOM_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByAccountId(data->accountId);
		if (player.isNull())
		{
			//
			return;
		}

		SClan* clan = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			DYNAMIC_ASSERT(0);
			return;
		}

		//清空pve房间id
		player->setPveRoomId(0);

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_DESTROY_ROOM;

		// 转换逻辑包
		PT_PVE_T2C_DESTROY_ROOM_DATA* sendData = (PT_PVE_T2C_DESTROY_ROOM_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//填充逻辑包
		sendData->accountId			= player->getAccountID();
		sendData->roomId			= data->roomId;


		// 发送数据
		FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
			GameNetPacketData_INFO::headSize + PT_PVE_T2C_DESTROY_ROOM_DATA_INFO::dataSize, 
			player->getClientNetID());
#endif
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvStartRoomFromCenterServer(I32 id, PT_PVE_T2F_START_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByAccountId(data->accountId);
		if (player.isNull())
		{
			//
			DYNAMIC_ASSERT(0);
			return;
		}

		SClan* clan = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			DYNAMIC_ASSERT(0);
			return;
		}

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2M_START;

			// 转换逻辑包
			PT_PVE_F2M_START_DATA* sendData = (PT_PVE_F2M_START_DATA*)(packet->data);
			if ( sendData )
			{
				//填充逻辑包
				sendData->accountId			= data->accountId;
				sendData->targetRegionId	= data->targetRegionId;
				sendData->roomId			= data->roomId;

				// 发送数据
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					GameNetPacketData_INFO::headSize + PT_PVE_F2M_START_DATA_INFO::dataSize,
					player->getMapServerNetID());
			}
		}
#endif
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvStartJumpRegionFromCenterServer(I32 id, PT_PVE_T2F_START_JUMP_REGION_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByAccountId(data->accountId);
		if (player.isNull())
		{
			return;
		}

		const RegionIdType		regionId	= data->targetRegionId;
		const InstanceUIdType	instanceUId = data->targetInstanceUId;
		DYNAMIC_ASSERT(regionId > 0 && instanceUId > 0);

		SPlayerCharacter* myPlayerCharacter = player->getMainClan()->getMainPlayerCharacter();

		PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpToRegionNewVer(myPlayerCharacter, 
																							ROT_PVE, regionId, instanceUId);

		sendPveStartToClient(player);
#endif
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::onRecvCreateRoomFromCenterServer(I32 id, PT_PVE_T2C_CREATE_DATA* data)
	{
#if 0
		SPlayerPtr player = SWorldManager::getInstance().getPlayerByAccountId(data->creatorInfo.accountId);
		if (player.isNull())
		{
			//
			DYNAMIC_ASSERT(0);
			return;
		}

		SClan* clan = player->getMainClan();
		if (NULL == clan)
		{
			//send error msg to client
			DYNAMIC_ASSERT(0);
			return;
		}

		//设置pve房间id
		player->setPveRoomId(data->newPveRoomInfo.pveRoomId);

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
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
		sendData->newPveRoomInfo.creatorAccountId	= data->newPveRoomInfo.creatorAccountId;
		sendData->newPveRoomInfo.pveRoomId			= data->newPveRoomInfo.pveRoomId;
		sendData->newPveRoomInfo.targetRegionId		= data->newPveRoomInfo.targetRegionId;
		sendData->newPveRoomInfo.memberNum			=  data->newPveRoomInfo.memberNum;
		WStrnCpyS(sendData->newPveRoomInfo.pveRoomName, data->newPveRoomInfo.pveRoomName, MAX_PVE_NAME);

		sendData->creatorInfo.accountId				= data->creatorInfo.accountId;
		sendData->creatorInfo.position				= data->creatorInfo.position;
		sendData->creatorInfo.charArtIcon			= data->creatorInfo.charArtIcon;
		sendData->creatorInfo.charLevel				= data->creatorInfo.charLevel;
		WStrnCpyS(sendData->creatorInfo.characterName, data->creatorInfo.characterName, MAX_CHARACTER_NAME_LEN);
		//填充数据包 End

		// 发送数据
		FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
			GameNetPacketData_INFO::headSize + PT_PVE_T2C_CREATE_DATA_INFO::dataSize, 
			player->getClientNetID());
#endif
	}

	//--------------------------------------------------------------------------
	void SPveNetPacketProcessor::sendPveDisconnectToCenterServer(SPlayerPtr player)
	{
#if 0
		DYNAMIC_ASSERT(!player.isNull());

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_F2T_DISCONNECT;

		// 转换逻辑包
		PT_PVE_F2T_DISCONNECT_DATA* sendData = (PT_PVE_F2T_DISCONNECT_DATA*)(packet->data);
		if ( sendData )
		{
			//填充逻辑包
			sendData->accountId		= player->getAccountID();
			sendData->roomId		= player->getPveRoomId();

			// 发送数据
			ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
				GameNetPacketData_INFO::headSize + PT_PVE_F2T_DISCONNECT_DATA_INFO::dataSize );
		}
#endif
	}


	void SPveNetPacketProcessor::sendPveStartToClient(SPlayerPtr& player)
	{
#if 0
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// 设置标签
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_F2C_START;

		// 转换逻辑包
		PT_PVE_F2C_START_DATA* sendData = (PT_PVE_F2C_START_DATA*)(packet->data);
		if ( sendData )
		{
			//填充逻辑包
			//sendData->accountId		= player->getAccountID();
			//sendData->roomId		= player->getPveRoomId();

			// 发送数据
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
				GameNetPacketData_INFO::headSize + PT_PVE_F2C_START_INFO::dataSize,
				player->getClientNetID());
		}
#endif
	}
}