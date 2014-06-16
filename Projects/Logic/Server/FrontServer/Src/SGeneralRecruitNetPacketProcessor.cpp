//*******************************************************************************************************
#include "stdafx.h"
#include "SGeneralRecruitNetPacketProcessor.h"
#include "GameNetPacket.h"

#include "FrontServerMain.h"
#include "SWorldManager.h"
#include "SGameObjectManager.h"
#include "PlayerCharacterDB.h"
#include "PlayerNetPacketProcesser.h"
#include "CampaignNetPacketProcesser.h"
#include "LoginNetPacketProcesser.h"
#include "SPveNetPacketProcessor.h"
#include "CampaignNetPacketProcesser.h"
#include "ServerManager.h"
#include "PlayerCharacterNetPacketProcesser.h"
#include "CharacterList.h"

//*******************************************************************************************************
namespace MG
{
	//--------------------------------------------------------------------------
	Bool SGeneralRecruitNetPacketProcessor::processClientPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_GENERAL_RECRUIT )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case  PT_GR_C2F_FRESH_RANDOM_GENERAL:
				onRecvFreshFromClient( id , (PT_GR_C2F_FRESH_RANDOM_GENERAL_DATA*)data->data);
				break;
			case  PT_GR_C2F_RANDOM_GENERAL_LIST:	
				onRecvGetListFromClient( id , (PT_GR_C2F_RANDOM_GENERAL_LIST_DATA*)data->data);
				break;
			case PT_GR_C2F_GENERAL_RECRUIT_CONFIRM:
				onRecvGeneralRecruitFromClientNewVer( id , (PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_DATA*)data->data);
				break;
			case PT_GR_C2F_CHANGE_GENERAL:
				onRecvChangeGeneralFromClientNewVersion( id , (PT_GR_C2F_CHANGE_GENERAL_DATA*)data->data);
				break;
			default:
				DYNAMIC_ASSERT(0);
				break;
			}


			return true;
		}

		return false;
	}

	//--------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::onRecvFreshFromClient(NetIdType clientNetId, PT_GR_C2F_FRESH_RANDOM_GENERAL_DATA*data)
	{
		SPlayerPtr playerPtr;// = SWorldManager::getInstance().getPlayerByClientNetId(clientNetId);
		if ( playerPtr.isNull())
		{
			//�쳣,�账��.
			DYNAMIC_ASSERT(0);
			return;
		}

		GeneralRecruitSystem* generalRecruitSystem;// = playerPtr->getGeneralRecruitSystem();
		generalRecruitSystem->reFresh(data->GeneralRecruitId);
		
		sendRandomGeneralListToClient(clientNetId, generalRecruitSystem);
	}

	//--------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::onRecvGetListFromClient(NetIdType clientNetId, PT_GR_C2F_RANDOM_GENERAL_LIST_DATA* data)
	{
		SPlayerPtr playerPtr;// = SWorldManager::getInstance().getPlayerByClientNetId(clientNetId);
		if ( playerPtr.isNull())
		{
			//�쳣,�账��.
			DYNAMIC_ASSERT(0);
			return;
		}

		GeneralRecruitSystem* generalRecruitSystem;// = playerPtr->getGeneralRecruitSystem();
		if (generalRecruitSystem->getLastGeneralRecruitId() != data->GeneralRecruitId)
		{
			//��Ҫ����ˢ��һ��
			generalRecruitSystem->reFresh(data->GeneralRecruitId);
		}

		sendRandomGeneralListToClient(clientNetId, generalRecruitSystem);
	}

	void SGeneralRecruitNetPacketProcessor::onRecvGeneralRecruitFromClientNewVer(NetIdType clientNetId, PT_GR_C2F_GENERAL_RECRUIT_CONFIRM_DATA*data)
	{
		RECRUIT_POSITION index = (RECRUIT_POSITION)data->index;
		DYNAMIC_ASSERT(index >= RECRUIT_POSITION_1 && index < RECRUIT_POSITION_MAX);

		SPlayerPtr playerPtr;// = SWorldManager::getInstance().getPlayerByClientNetId(clientNetId);
		if ( playerPtr.isNull())
		{
			//�쳣,�账��.
			DYNAMIC_ASSERT(0);
			return;
		}

		SClan* pClan;// = playerPtr->getMainClan();
		if ( !pClan )
		{
			//�쳣,�账��.
			DYNAMIC_ASSERT(0);
			sendGeneralRecruitResultToClient(clientNetId, Recruit_Result_Error_Index);
			return;
		}

		//if (pClan->getPlayerCharacterList()->size() >= 5)
		//{
		//	sendGeneralRecruitResultToClient(clientNetId, Recruit_Result_Full);
		//	return;
		//}


		GeneralRecruitSystem* generalRecruitSystem;// = playerPtr->getGeneralRecruitSystem();

		CharAttrInfo* charAttrInfo = generalRecruitSystem->getCharAttrInfoByIndex(index);
		if (NULL == charAttrInfo)
		{
			sendGeneralRecruitResultToClient(clientNetId, Recruit_Result_Error_Index);
			return;
		}

		PlayerCharacterData playerCharData;
		playerCharData.mName					= charAttrInfo->name_ming;
		playerCharData.charSurName				= charAttrInfo->name_xing;
		playerCharData.mCharacterTemplateID 	= charAttrInfo->charTemplateId;
		playerCharData.charArtIcon 				= charAttrInfo->charTempInfo->getCharacterArtIconId();
		playerCharData.mRegionType 				= ROT_TIRO;
		playerCharData.mRegionID				= 20001;
		playerCharData.charClanId				= pClan->getClanID();
		playerCharData.charAttrAppendId			= charAttrInfo->charAttrAppendId;
		playerCharData.charAttrAppendLvlAddId	= charAttrInfo->charAttrAppendLvlAddId;
		playerCharData.charCurAge				= charAttrInfo->age;
		playerCharData.charLifeSpan				= charAttrInfo->lifeSpanBase;


		for (Int i=0; i<DB_RECORD_ATTR_NUM; ++i)
		{
			playerCharData.charAttrRand[i] = charAttrInfo->charAttrRand[i];
			playerCharData.charAttrRandAdd[i] = charAttrInfo->charAttrRandAdd[i];
		}

		//���浽DB
		U64 tempId = 0;
		if ( PlayerCharacterDBOp::createPlayerCharacter(  *( FrontServerMain::getInstance().getDBDriver() ), &playerCharData, tempId ) == false )
		{
			//�쳣,�账��.
			DYNAMIC_ASSERT(0);
			sendGeneralRecruitResultToClient(clientNetId, Recruit_Result_Error_DB);
			return;
		}

		SPlayerCharacter* newPlayerCharacter;// =  SWorldManager::getInstance().getGameObjectManager()->createPlayerCharacterFromMemory(tempId, pClan);

		DYNAMIC_ASSERT(NULL != newPlayerCharacter);


		SGameObjectManager* gameObjManagerTest1;// = (SWorldManager::getInstance().getGameObjectManager());
		//��Ҫ��ʼ�������ݡ�
		//�ͻ�����Ϣ��
		playerCharData.mId = tempId;
		//newPlayerCharacter->init(&playerCharData, true);

		//pClan->_addPlayerCharacterToList(newPlayerCharacter);

		SGameObjectManager* gameObjManagerTest2;// = (SWorldManager::getInstance().getGameObjectManager());

		//SPlayerCharacter newPlayerCharacter(NULL, 0);
		//playerCharData.mId = tempId;
		//newPlayerCharacter.init(&playerCharData, true);
		//������ļ�ɹ���Ϣ
		sendGeneralRecruitConfirmToClient(clientNetId, data->index);
		sendGeneralRecruitResultToClient(clientNetId, Recruit_Result_Success);


		//�½�ɫ��Ϣ���͸��ͻ���
		PlayerNetPacketProcesser::getInstance().sendPlayerCharacterToClient(clientNetId, newPlayerCharacter);
		//newPlayerCharacter->sendDataInfoBeforeJoinGame(true);
		PlayerNetPacketProcesser::getInstance().sendRecruitPlayerCharacterToMapServer(playerPtr, newPlayerCharacter);
		//loadDbAndSendRecruitGeneralListToClient(clientNetId, pClan);
	}

	void SGeneralRecruitNetPacketProcessor::onRecvChangeGeneralFromClientNewVersion(NetIdType clientNetId, PT_GR_C2F_CHANGE_GENERAL_DATA* data)
	{
		// ��Ҫ���õ��������� ����ͬ��������
		//�鿴�Ƿ������佫
		SPlayerPtr player;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(clientNetId);

		if ( player.isNull() )
		{
			//�쳣,�账��.
			DYNAMIC_ASSERT(0);
			return;
		}
		SClan* clan;// = player->getMainClan();
		if (clan == NULL)
		{
			//�쳣,�账��.
			DYNAMIC_ASSERT(0);
			return;
		}

		if (clan->getMainGenrealID() == data->charId)
		{
			sendGeneralRecruitResultToClient(clientNetId, Recruit_Result_Change_myself);
			return;
		}

		//��� MapServer �� region���ָ��
		SPlayerCharacter* mainGeneral;// = clan->getPlayerCharacterFromList(clan->getMainGenrealID());
		PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpToEmptyRegionNewVer(player->getAccountID(), 
			mainGeneral->getID(), mainGeneral->getMapServerNetId());

		//���Ŀ��MapServer�Ƿ�����
		SPlayerCharacter* changeGeneral;// = clan->getPlayerCharacterFromList(data->charId);
		DYNAMIC_ASSERT(NULL != changeGeneral);
		clan->setMainGenrealID(data->charId);
		const REGION_OBJ_TYPE	regionType	= changeGeneral->getData()->mRegionType;
		const RegionIdType		regionId	= changeGeneral->getData()->mRegionID;
		const InstanceUIdType	instanceUId = changeGeneral->getData()->mInstanceUId;

		PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpToRegionNewVer(changeGeneral, regionType,  regionId, instanceUId);
#if 0
		DYNAMIC_ASSERT(NULL != pChar);
		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(regionType, regionId);
		DYNAMIC_ASSERT(NULL != region);

		NetIdType mapServerID = region->getMapServerNetId();

		if((region->getRegionType() != ROT_TIRO) && 
			(region->getRegionType() != ROT_PVE) &&
			(mapServerID <= 0) )
		{
			//MapServer ����

			PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpRegionToClient(
				pChar->getBelongPlayer()->getClientNetID(), 
				ChatarcterJumpRegionResult_Fail_Crash, 
				pChar->getID(), regionId, regionType, instanceUId);
			//ֱ�ӶϿ����� for test
			//FrontServerMain::getInstance().getServerLauncher()->closeClient(player->getClientNetID());
			return;
		}


		if((region->getRegionType() == ROT_MAP_DISTRIBUTION) || 
			(region->getRegionType() == ROT_PLACE))
		{
			player->setMapServerNetID(mapServerID);
		}

		


		if (ROT_TIRO == regionType)
		{
			const NetIdType mapServerNetId = ServerManager::getInstance().getRandMapServerNetId();
			player->setMapServerNetID(mapServerNetId);

			//��ɫ����ͼ
			PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpToTiroRegion(mapServerNetId, pChar->getID(), regionType,  regionId, instanceUId);

			//�������ָ����� �������MapServer
			PlayerNetPacketProcesser::getInstance().sendPlayerJumpToMapServer(mapServerNetId, player, 
				player->getCurrentRegionType(),
				player->getCurrentRegionId(),
				player->getCurrentInstanceUid());
		}
		else if(ROT_MAP_DISTRIBUTION == regionType || 
			ROT_PLACE == regionType )
		{
			//��ɫ����ͼ
			PlayerCharacterNetPacketProcesser::getInstance().broadcastPlayerCharacterJumpToRegion(pChar->getID(), regionType,  regionId, instanceUId);

			// �㲥����ͼ������
			PlayerNetPacketProcesser::getInstance().broadcastPlayerJumpToRegion(player, 
				player->getCurrentRegionType(),
				player->getCurrentRegionId(),
				player->getCurrentInstanceUid());
		}
		else if(ROT_PVE == regionType || ROT_HOME == regionType)
		{
			const NetIdType mapServerNetId = ServerManager::getInstance().getRandMapServerNetId();
			player->setMapServerNetID(mapServerNetId);

			//��ɫ����ͼ
			PlayerCharacterNetPacketProcesser::getInstance().sendPlayerCharacterJumpToTiroRegion(mapServerNetId, pChar->getID(), regionType,  regionId, instanceUId);

			//�������ָ����� �������MapServer
			PlayerNetPacketProcesser::getInstance().sendPlayerJumpToMapServer(mapServerNetId, player, 
				player->getCurrentRegionType(),
				player->getCurrentRegionId(),
				player->getCurrentInstanceUid());
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

#endif


		//��ɫװ����Ϣ��
		//��ɫ������Ϣ
		//��ɫ״̬��Ϣ
		//��������������
		//���Լ���
		//���������Ϣ��
		//player->getMainClan()->sendInfo(false);  
		//player->getMainClan()->sendDataInfoOnJoinGame();
	}

	void SGeneralRecruitNetPacketProcessor::sendRandomGeneralListBeginToClient(NetIdType clientNetID)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN;

			// ת���߼���
			PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_DATA* sendData = (PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				//sendData->error = error;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_GR_F2C_RANDOM_GENERAL_LIST_BEGIN_INFO::dataSize,
					clientNetID);
			}
		}
	}

	//----------------------------------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::sendRandomGeneralListToClient(NetIdType clientNetID, GeneralRecruitSystem* generalRecruitSystem)
	{
		sendRandomGeneralListBeginToClient(clientNetID);

		//----------------------------------------------------------------------------------------------------

		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_F2C_RANDOM_GENERAL_LIST;

			PT_GR_F2C_RANDOM_GENERAL_LIST_DATA* sendData = (PT_GR_F2C_RANDOM_GENERAL_LIST_DATA*)(packet->data);
			sendData->addGeneralNum = 0;

			// ��ǰ��������ͷ��С
			I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_GR_F2C_RANDOM_GENERAL_LIST_INFO::headSize;
			// ��ǰ�������ݴ�С
			I32 sendDataSize        = sendDataHeadSize;
			// ׼���������ݴ�С
			I32 prepareSendDataSize = sendDataHeadSize;

			Int index = 0;
			std::map<RECRUIT_POSITION, CharAttrInfo*>* charAttrList = generalRecruitSystem->getCharAttrList();
			for (std::map<RECRUIT_POSITION, CharAttrInfo*>::iterator iter = charAttrList->begin(); iter != charAttrList->end(); ++iter)
			{
				CharAttrInfo* tempCharAttr = iter->second;
				NetRandomGeneralInfo* tempInfo = &(sendData->addGeneralInfo[index]);

				tempInfo->charTemplateId	= tempCharAttr->charTemplateId;
				WStrnCpyS(tempInfo->name, tempCharAttr->name.c_str(), MAX_CHARACTER_NAME_LEN);

				for (Int i=0; i<DB_RECORD_ATTR_NUM; ++i)
				{
					tempInfo->charAttrRand[i] = tempCharAttr->charAttrRand[i];
					tempInfo->charAttrRandAdd[i] = tempCharAttr->charAttrRandAdd[i];
				}
				tempInfo->charAttrAppendId		= tempCharAttr->charAttrAppendId;
				tempInfo->charAttrAppendLvlId	= tempCharAttr->charAttrAppendLvlAddId;
				tempInfo->index					= index;
				tempInfo->age					= tempCharAttr->age;
				tempInfo->lifeSpan				= tempCharAttr->lifeSpanBase;

				index++;
				sendData->addGeneralNum++;
			}

			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
				GameNetPacketData_INFO::headSize + PT_GR_F2C_RANDOM_GENERAL_LIST_INFO::dataSize(sendData), 
				clientNetID);

			dataPtr.setNull();
		}

		//----------------------------------------------------------------------------------------------------

		sendRandomGeneralListEndToClient(clientNetID);
	}

	//----------------------------------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::sendRandomGeneralListEndToClient(NetIdType clientNetID)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_F2C_RANDOM_GENERAL_LIST_END;

			// ת���߼���
			PT_GR_F2C_RANDOM_GENERAL_LIST_END_DATA* sendData = (PT_GR_F2C_RANDOM_GENERAL_LIST_END_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				//sendData->error = error;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_GR_F2C_RANDOM_GENERAL_LIST_END_INFO::dataSize,
					clientNetID);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::loadDbAndSendRecruitGeneralListToClient(NetIdType clientNetID, SClan* clan)
	{
		//��DB��ý�ɫlist��Ϣ
		std::vector<PlayerCharacterData>  playerCharacterList;
		std::vector<ItemRecord>           playerCharacterItemList;
		std::map<IdType, std::map<UInt, BuffData>>&	mapPlayerCharBuff = clan->getSBuffManager()->getMapCharacterBuff();
		if ( PlayerCharacterDBOp::getPlayerCharactersNameMap( *( FrontServerMain::getInstance().getDBDriver() ), 
			clan->getClanID(), 0, 
			playerCharacterList,
			playerCharacterItemList, 
			mapPlayerCharBuff) == false )
		{  
			DYNAMIC_ASSERT(0);
			return;
		}

		//��ʼ����
		sendRecruitGeneralListBeginToClient(clientNetID);
		sendRecruitGeneralListToClient(clientNetID, &playerCharacterList);
		sendRecruitGeneralListEndToClient(clientNetID);
	}

	void SGeneralRecruitNetPacketProcessor::sendRecruitGeneralListBeginToClient(NetIdType clientNetID)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN;

			// ת���߼���
			PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_DATA* sendData = (PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				//sendData->error = error;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_GR_F2C_RECRUIT_GENERAL_LIST_BEGIN_INFO::dataSize, 
					clientNetID);
			}
		}
	}

	//----------------------------------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::sendRecruitGeneralListToClient(NetIdType clientNetID, std::vector<PlayerCharacterData>* playerCharacterList)
	{
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


			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_F2C_RECRUIT_GENERAL_LIST;

			PT_GR_F2C_RECRUIT_GENERAL_LIST_DATA* sendData = (PT_GR_F2C_RECRUIT_GENERAL_LIST_DATA*)(packet->data);
			sendData->addGeneralNum = 0;

			// ��ǰ��������ͷ��С
			I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_GR_F2C_RECRUIT_GENERAL_LIST_INFO::headSize;
			// ��ǰ�������ݴ�С
			I32 sendDataSize        = sendDataHeadSize;
			// ׼���������ݴ�С
			I32 prepareSendDataSize = sendDataHeadSize;

			Int index = 0;
			for (std::vector<PlayerCharacterData>::iterator iter = playerCharacterList->begin(); iter != playerCharacterList->end(); ++iter)
			{
				PlayerCharacterData* charData = &(*iter);
				NetRecuitGeneralInfo* tempInfo = &(sendData->addGeneralInfo[index]);

				//������� begin
				tempInfo->uin				= charData->mId;
				tempInfo->charTemplateId	= charData->mCharacterTemplateID;
				//������� end

				sendData->addGeneralNum++;
				index++;
			}

			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
				GameNetPacketData_INFO::headSize + PT_GR_F2C_RECRUIT_GENERAL_LIST_INFO::dataSize(sendData), 
				clientNetID);
	}

	//--------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::sendRecruitGeneralListEndToClient(NetIdType clientNetID)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_F2C_RECRUIT_GENERAL_LIST_END;

			// ת���߼���
			PT_GR_F2C_RECRUIT_GENERAL_LIST_END_DATA* sendData = (PT_GR_F2C_RECRUIT_GENERAL_LIST_END_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				//sendData->error = error;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_GR_F2C_RECRUIT_GENERAL_LIST_END_INFO::dataSize,
					clientNetID);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::sendGeneralRecruitResultToClient(NetIdType clientNetID, Recruit_Result result)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_F2C_GENERAL_RECRUIT_RESUILT;

			// ת���߼���
			PT_GR_F2C_GENERAL_RECRUIT_RESUILT_DATA* sendData = (PT_GR_F2C_GENERAL_RECRUIT_RESUILT_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->result = result;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_GR_F2C_GENERAL_RECRUIT_RESUILT_INFO::dataSize,
					clientNetID);
			}
		}
	}

	//--------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::sendGeneralRecruitConfirmToClient(NetIdType clientNetID, U32 index)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_F2C_GENERAL_RECRUIT_CONFIRM;

			// ת���߼���
			PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_DATA* sendData = (PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->index = index;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_GR_F2C_GENERAL_RECRUIT_CONFIRM_INFO::dataSize, 
					clientNetID);
			}
		}
	}


	//--------------------------------------------------------------------------
	void SGeneralRecruitNetPacketProcessor::sendClearClanToClient(NetIdType clientNetID)
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_GENERAL_RECRUIT;
			packet->type    = PT_GR_F2C_CLEAR_CLAN;

			// ת���߼���
			PT_GR_F2C_CLEAR_CLAN_DATA* sendData = (PT_GR_F2C_CLEAR_CLAN_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				//sendData->error = error;
	
				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_CAMPAIGN_T2C_ERROR_INFO::dataSize,
					clientNetID);
			}
		}
	}

	//--------------------------------------------------------------------------

}	//namespace MG