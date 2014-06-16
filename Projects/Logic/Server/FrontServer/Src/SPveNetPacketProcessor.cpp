
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
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2T_CREATE;

			// ת���߼���
			PT_PVE_F2T_CREATE_DATA* sendData = (PT_PVE_F2T_CREATE_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->accountId			= player->getAccountID();
				sendData->clientNetId		= player->getClientNetID();
				sendData->charArtIcon		= myChar->getData()->charArtIcon;
				sendData->level				= myChar->getData()->mLevel;
				sendData->targetRegionId	= data->targetRegionId;
				WStrnCpyS(sendData->charName, myChar->getName().c_str(), MAX_CHARACTER_NAME_LEN);
				WStrnCpyS(sendData->pveRoomName, data->pveName, MAX_PVE_NAME);

				// ��������
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
		//	//CenterServer ����
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
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_F2T_ROOM_LIST;

		// ת���߼���
		PT_PVE_F2T_ROOM_LIST_DATA* sendData = (PT_PVE_F2T_ROOM_LIST_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//����߼���
		sendData->accountId		    		= player->getAccountID();
		sendData->clientNetId				= player->getClientNetID();
		//sendData->creatorClanId	    		= data->creatorClanId;
		//sendData->creatorPlayerCharacterId	= clan->getMainPlayerCharacter()->getID();
		//sendData->targetRegionId			= data->targetRegionId;
		//WStrnCpyS(sendData->creatorClanName, clan->getData()->clanName.c_str(), MAX_CLAN_NAME);
		//WStrnCpyS(sendData->creatorPlayerCharacterName, clan->getMainPlayerCharacter()->getName().c_str(), MAX_CHARACTER_NAME_LEN);
		//WStrnCpyS(sendData->campaignName, data->campaignName, MAX_CAMPAIGN_NAME);

		// ��������
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

		//���� pve����ID
		player->setPveRoomId(data->roomId);

		///////////////////////////////////////////////////////////////////////////
		//sendCampaignCreateToCenterServer(data, clan, player);
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_F2T_ENTER_ROOM;

		// ת���߼���
		PT_PVE_F2T_ENTER_ROOM_DATA* sendData = (PT_PVE_F2T_ENTER_ROOM_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//����߼���
		sendData->accountId			= player->getAccountID();
		sendData->clientNetId		= player->getClientNetID();
		sendData->charArtIcon		= myChar->getData()->charArtIcon;
		sendData->charLevel			= myChar->getData()->mLevel;
		WStrnCpyS(sendData->charName, myChar->getName().c_str(), MAX_CHARACTER_NAME_LEN);
		sendData->roomId			= data->roomId;
		
		// ��������
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

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2T_LEAVE_ROOM;

			// ת���߼���
			PT_PVE_F2T_LEAVE_ROOM_DATA* sendData = (PT_PVE_F2T_LEAVE_ROOM_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->accountId			= player->getAccountID();
				sendData->clientNetId		= player->getClientNetID();
				sendData->roomId			= player->getPveRoomId();

				// ��������
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

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2T_START;

			// ת���߼���
			PT_PVE_F2T_START_DATA* sendData = (PT_PVE_F2T_START_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->accountId			= player->getAccountID();
				sendData->roomId			= player->getPveRoomId();

				// ��������
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

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2T_KICK;

			// ת���߼���
			PT_PVE_F2T_KICK_DATA* sendData = (PT_PVE_F2T_KICK_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->roomId			= player->getPveRoomId();
				sendData->leaderClientNetId		= player->getClientNetID();
				sendData->leaderAccountId	= data->leaderAccountId;
				sendData->kickAccountId		= data->kickAccountId;

				// ��������
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

		//���pve����id
		player->setPveRoomId(0);

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_LEAVE_ROOM;

		// ת���߼���
		PT_PVE_T2C_LEAVE_ROOM_DATA* sendData = (PT_PVE_T2C_LEAVE_ROOM_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//����߼���
		sendData->accountId			= player->getAccountID();
		sendData->roomId			= data->roomId;


		// ��������
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

		//���pve����id
		player->setPveRoomId(0);

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_DESTROY_ROOM;

		// ת���߼���
		PT_PVE_T2C_DESTROY_ROOM_DATA* sendData = (PT_PVE_T2C_DESTROY_ROOM_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//����߼���
		sendData->accountId			= player->getAccountID();
		sendData->roomId			= data->roomId;


		// ��������
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

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_PVE;
			packet->type    = PT_PVE_F2M_START;

			// ת���߼���
			PT_PVE_F2M_START_DATA* sendData = (PT_PVE_F2M_START_DATA*)(packet->data);
			if ( sendData )
			{
				//����߼���
				sendData->accountId			= data->accountId;
				sendData->targetRegionId	= data->targetRegionId;
				sendData->roomId			= data->roomId;

				// ��������
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

		//����pve����id
		player->setPveRoomId(data->newPveRoomInfo.pveRoomId);

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_T2C_CREATE;

		// ת���߼���
		PT_PVE_T2C_CREATE_DATA* sendData = (PT_PVE_T2C_CREATE_DATA*)(packet->data);
		if (NULL == sendData)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//������ݰ� Begin
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
		//������ݰ� End

		// ��������
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

		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_F2T_DISCONNECT;

		// ת���߼���
		PT_PVE_F2T_DISCONNECT_DATA* sendData = (PT_PVE_F2T_DISCONNECT_DATA*)(packet->data);
		if ( sendData )
		{
			//����߼���
			sendData->accountId		= player->getAccountID();
			sendData->roomId		= player->getPveRoomId();

			// ��������
			ServerManager::getInstance().sendNetPacketToCenterServer( dataPtr, 
				GameNetPacketData_INFO::headSize + PT_PVE_F2T_DISCONNECT_DATA_INFO::dataSize );
		}
#endif
	}


	void SPveNetPacketProcessor::sendPveStartToClient(SPlayerPtr& player)
	{
#if 0
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if (NULL == packet)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		// ���ñ�ǩ
		packet->channel = GNPC_PVE;
		packet->type    = PT_PVE_F2C_START;

		// ת���߼���
		PT_PVE_F2C_START_DATA* sendData = (PT_PVE_F2C_START_DATA*)(packet->data);
		if ( sendData )
		{
			//����߼���
			//sendData->accountId		= player->getAccountID();
			//sendData->roomId		= player->getPveRoomId();

			// ��������
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
				GameNetPacketData_INFO::headSize + PT_PVE_F2C_START_INFO::dataSize,
				player->getClientNetID());
		}
#endif
	}
}