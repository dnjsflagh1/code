
/******************************************************************************/
#include "stdafx.h"
#include "PlayerNetPacketProcesser.h"
#include "FrontServerMain.h"
#include "PlayerNetPacket.h"
#include "ServerManager.h"
#include "SPlayerCharacter.h"
#include "SPlayer.h"
#include "NetTranspondPacketProcesser.h"
//#include "STroop.h"
//#include "STroopGroup.h"
#include "PlayerCharacterData.h"
#include "SWorldManager.h"
#include "GenrealEquip.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	PlayerNetPacketProcesser::PlayerNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	PlayerNetPacketProcesser::~PlayerNetPacketProcesser()
	{

	}

	//--------------------------------------------------------------------------
	Bool PlayerNetPacketProcesser::processClientPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_PLAYER )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PLAYER_C2F_PRINT_TEST:
				{
					//打印信息
					//SWorldManager::getInstance().printWorldObject();
					//ServerManager::getInstance().printServer();
					broadcastPrintTestToMapServer();
				}
				break;
			case PT_PLAYER_C2F_JUMP_REGION:
				onRecvPlayerJumpRegionFromClient(id, (PT_PLAYER_C2F_JUMP_REGION_DATA*)data->data);
				break;
			case PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID:
				onRecvPlayerJumpRegionByCharIdFromClient(id, (PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA*)data->data);
				break;
			case PT_PLAYER_C2F_TIRO_LIST:
				onRecvTiroListFromClient(id, (PT_PLAYER_C2F_TIRO_LIST_DATA*)data->data);
				break;
			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	Bool PlayerNetPacketProcesser::processLoginServerPacket(I32 id, NetEventRecv* packet)
	{
		return false;
	}

	//--------------------------------------------------------------------------
	Bool PlayerNetPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_PLAYER )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_PLAYER_M2F_JUMP_REGION:
				onRecvPlayerJumpRegionFromMapServer(id, (PT_PLAYER_M2F_JUMP_REGION_DATA*)data->data);
				break;
			}

			return true;
		}
		return false;
	}

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::onRecvPlayerJumpRegionFromClient( I32 netID, PT_PLAYER_C2F_JUMP_REGION_DATA* jumpData)
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(netID);
		DYNAMIC_ASSERT(!player.isNull());

		SClan* clan;// = player->getMainClan();
		if (!clan)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		const RegionIdType		regionId	= jumpData->regionId;
		const REGION_OBJ_TYPE	regionType	= (REGION_OBJ_TYPE)jumpData->regionType;
		const InstanceUIdType	instanceUid	= jumpData->instanceUid;

		SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(regionType, regionId);
		DYNAMIC_ASSERT(NULL != region);
		
		NetIdType mapServerID = region->getMapServerNetId();

		MG_LOG(out_sys, "\n mapServerid = %d\n", mapServerID);

		if(true == ServerManager::getInstance().isMapServerCrash(regionType, regionId))
		{
			//MapServer 当机
			//send error msg to client
			sendPlayerJumpRegionToClient(player, PlayerJump_ServerCrash, FORCE_MAX, NULL, NULL);
			return;
		}

		if (player->getCurrentRegionId() == regionId && 
			player->getCurrentRegionType() == regionType &&
			player->getCurrentInstanceUid() == instanceUid)
		{
			//sendPlayerJumpRegionToClient(player, PlayerJump_ServerCrash, FORCE_MAX);
			return;
		}

#if 0
		if (regionType == ROT_MAP_DISTRIBUTION || regionType == ROT_PLACE)
		{
			DYNAMIC_ASSERT(mapServerID > 0);
			player->setMapServerNetID(mapServerID);
		}
#endif
#if 0
		broadcastPlayerJumpToRegion( player, regionType, regionId, instanceUid);
#endif
	}

	void PlayerNetPacketProcesser::onRecvPlayerJumpRegionByCharIdFromClient(I32 netID, PT_PLAYER_C2F_JUMP_REGION_BY_CHAR_ID_DATA* jumpData)
	{
		SPlayerCharacter* playerChar;// = SWorldManager::getInstance().getPlayerCharacter(jumpData->accountId, jumpData->playerCharacterId);
		DYNAMIC_ASSERT(NULL != playerChar);
		DYNAMIC_ASSERT(playerChar->getMapServerNetId() > 0);

		sendPlayerJumpToRegionByCharId(playerChar->getMapServerNetId(), jumpData->accountId, jumpData->playerCharacterId);
	}

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::onRecvTiroListFromClient(I32 netID, PT_PLAYER_C2F_TIRO_LIST_DATA* data)
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(netID);
		DYNAMIC_ASSERT( !player.isNull());

		SClan* clan;// = player->getMainClan();
		if (!clan)
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		//REGION_OBJ_TYPE	regionType	= (REGION_OBJ_TYPE)data->regionType;
		//RegionIdType	regionId	= data->regionId;

		//SRegionObjectBase* region = SWorldManager::getInstance().getRegionObject(ROT_PLACE, regionId);
		//DYNAMIC_ASSERT(NULL != region);
		

		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_F2M_TIRO_LIST;

			// 转换逻辑包
			PT_PLAYER_F2M_TIRO_LIST_DATA* sendData = (PT_PLAYER_F2M_TIRO_LIST_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId	    = player->getAccountID();
			
				const Int dataSize = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_TIRO_LIST_INFO::dataSize;
				// 发送数据
				std::map<ServerUniqueFlagIdType, MapServerConnectInfo*>* mapServerList;// = ServerManager::getInstance().getActiveMapServerList();
				for (std::map<ServerUniqueFlagIdType, MapServerConnectInfo*>::iterator iter = mapServerList->begin(); iter != mapServerList->end(); ++iter)
				{
					NetIdType mapServerNetId;// = iter->second->netId;
					DYNAMIC_ASSERT(mapServerNetId > 0);

					sendData->accountId			= player->getAccountID();
					sendData->mapServerNetId	= mapServerNetId;
					
					ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId(dataPtr, dataSize, mapServerNetId);

					FrontServerMain::getInstance().getServerLauncher()->cloneSendDataBuffer( dataPtr, dataPtr, UInt(dataSize) );
					packet = (GameNetPacketData*) dataPtr->getLogicData();
					sendData = (PT_PLAYER_F2M_TIRO_LIST_DATA*)(packet->data);
				}
			}
		}
	}

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::onRecvPlayerJumpRegionFromMapServer(I32 id, PT_PLAYER_M2F_JUMP_REGION_DATA* data)
	{
		SPlayerPtr player;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(data->client_net_id);
		if (player.isNull())
		{
			//error 
			//KickPlayer()
			//DYNAMIC_ASSERT(0);
			return;
		}

		if (data->jumpResult == PlayerJump_Success)
		{
			player->setCurrentRegion((REGION_OBJ_TYPE)data->regionType, data->regionId,data->instanceUid);
			player->setMapServerNetID(id);
		}

		sendPlayerJumpRegionToClient(player, data->jumpResult, (FORCE)data->force, &(data->pos), &(data->dir));
	}

    //--------------------------------------------------------------------------
    void PlayerNetPacketProcesser::sendPlayerCharacterListToClient(I32 netID, SPlayer* player)
    {
		//--------------------------------------------------------------------------

        //检查
		//player->lockClanList();
        SClan* pClan;// = player->getMainClan();
        assert(pClan);
        std::map<U64, SPlayerCharacter*>* pPlayerCharacterList;// = pClan->getPlayerCharacterList();
        assert(pPlayerCharacterList);

        Int nCount = pPlayerCharacterList->size();
        if (nCount <= 0)
            return;

        //设置已发送
        //pClan->setIsGenrealSend(true);

        //--------------------------------------------------------------------------

        // 得到一个大型发送缓存
        GameNetSendDataBufferPtr dataPtr ;
        GameNetPacketData* packet       = NULL;
        PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA* sendData = NULL;

        // 当前发送数据头大小
        I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA_INFO::headSize;
        // 当前发送数据大小
        I32 sendDataSize        = sendDataHeadSize;
        // 准备发送数据大小
        I32 prepareSendDataSize = sendDataHeadSize;

        // 遍历角色队列
        std::map<U64, SPlayerCharacter*>::iterator iter = pPlayerCharacterList->begin();
        while( pPlayerCharacterList->end() != iter )
        {

			//--------------------------------------------------------------------------
			
			if ( dataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA_INFO::elementSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, netID);
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

				packet->channel = GNPC_PLAYER;
				packet->type    = PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST;
				sendData = (PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA*)(packet->data);
				// 清空
				sendData->remainPlayerCharacterNum = 0;

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA_INFO::headSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------
            
            // 增加角色记录
            SPlayerCharacter* playerCharacter                   = iter->second;
            DYNAMIC_ASSERT(playerCharacter);
            PlayerCharacterData* playerCharacterData            = playerCharacter->getData();
            DYNAMIC_ASSERT(playerCharacterData);
            NetPlayerCharacterInfo& newNetPlayerCharacterData   = sendData->remainPlayerCharacter[sendData->remainPlayerCharacterNum];

            //填充角色记录
            wcscpy_s(newNetPlayerCharacterData.name, _countof(newNetPlayerCharacterData.name), playerCharacterData->mName.c_str());
			wcscpy_s(newNetPlayerCharacterData.surName, _countof(newNetPlayerCharacterData.surName), playerCharacterData->charSurName.c_str());

            newNetPlayerCharacterData.Id			            = playerCharacterData->mId;
            newNetPlayerCharacterData.charClanId	            = playerCharacterData->charClanId;
            newNetPlayerCharacterData.genrealPos	            = ((NetVec2)playerCharacterData->mPos).getData();
            newNetPlayerCharacterData.regionType	            = (REGION_OBJ_TYPE)playerCharacterData->mRegionType;
            newNetPlayerCharacterData.regionId		            = playerCharacterData->mRegionID;
            newNetPlayerCharacterData.characterTemplateID       = playerCharacterData->mCharacterTemplateID;
            newNetPlayerCharacterData.charCurAge			    = playerCharacterData->charCurAge;
			newNetPlayerCharacterData.charLifeSpan				= playerCharacterData->charLifeSpan;
            newNetPlayerCharacterData.charLvl	                = playerCharacterData->mLevel;
            newNetPlayerCharacterData.charExp1	                = playerCharacterData->charExp1;
            newNetPlayerCharacterData.charExp2		            = playerCharacterData->charExp2;
            newNetPlayerCharacterData.charExp3                  = playerCharacterData->charExp3;
            newNetPlayerCharacterData.charHP			        = playerCharacterData->mHp;
            newNetPlayerCharacterData.charMP	                = playerCharacterData->mMp;
            newNetPlayerCharacterData.charLineageNum	        = playerCharacterData->mLineageNum;
            newNetPlayerCharacterData.charArtMashID1			= playerCharacterData->charArtMashID1;
            newNetPlayerCharacterData.charArtMashID2			= playerCharacterData->charArtMashID2;
            newNetPlayerCharacterData.charArtIcon			    = playerCharacterData->charArtIcon;
            newNetPlayerCharacterData.charInfluenceID		    = playerCharacterData->charInfluenceID;
            newNetPlayerCharacterData.charSkillPointAll         = playerCharacterData->charSkillPointAll;
            newNetPlayerCharacterData.charNoAssignSkillPoint    = playerCharacterData->charNoAssignSkillPoint;
            newNetPlayerCharacterData.charState         	    = playerCharacterData->charState;
            newNetPlayerCharacterData.charLifeState	            = playerCharacterData->charLifeState;
            newNetPlayerCharacterData.charDir		            = ((NetVec2)playerCharacterData->mDir).getData();
			newNetPlayerCharacterData.charAttrAppendId			= playerCharacterData->charAttrAppendId;
			newNetPlayerCharacterData.charAttrAppendLvlAddId	= playerCharacterData->charAttrAppendLvlAddId;

            for (Int i=0; i<DB_RECORD_ATTR_NUM; i++)
            {
                newNetPlayerCharacterData.attrRand[i]       = playerCharacterData->charAttrRand[i];
                newNetPlayerCharacterData.attrRandAdd[i]    = playerCharacterData->charAttrRandAdd[i];
            }

            // 递增参数
            sendDataSize += PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA_INFO::elementSize;
            ++sendData->remainPlayerCharacterNum;

            ++iter;
        }

		//--------------------------------------------------------------------------

        // 如果有剩余则发送
        if ( dataPtr.isNull() == false )
        {
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,sendDataSize, netID);
			dataPtr.setNull();
        }
    }
        
    //--------------------------------------------------------------------------
    void PlayerNetPacketProcesser::sendPlayerJumpRegionToClient(SPlayerPtr player, PlayerJumpResult jumpResult, FORCE force, NetVec2Data* pos, NetVec2Data* dir)
    {
        SClan* pClan;// = player->getMainClan();
        DYNAMIC_ASSERT(pClan);

        
        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER;
            packet->type    = PT_PLAYER_F2C_JUMP_REGION;

            // 转换逻辑包
            PT_PLAYER_F2C_JUMP_REGION_DATA* sendData = (PT_PLAYER_F2C_JUMP_REGION_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->regionId      = player->getCurrentRegionId();
                sendData->regionType    = player->getCurrentRegionType();
				sendData->instanceUid	= player->getCurrentInstanceUid();
				sendData->jumpResult	= jumpResult;
				sendData->force			= force;
				if (NULL != pos)
				{
					sendData->pos		= *pos;
				}
				if (NULL != dir)
				{
					sendData->dir		= *dir;
				}

                // 发送数据
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_PLAYER_F2C_JUMP_REGION_INFO::dataSize, player->getClientNetID());
            }
        }
    }

    //--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::broadcastPrintTestToMapServer()
	{
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( NULL == packet )
		{
			return;
		}

		// 设置标签
		packet->channel = GNPC_PLAYER;
		packet->type    = PT_PLAYER_F2M_PRINT_TEST;
	
		// 发送数据
		//ServerManager::getInstance().broadOrSendNetPacketToActiveMapServer( 
		//	dataPtr, GameNetPacketData_INFO::headSize);
	}

	//--------------------------------------------------------------------------
    void PlayerNetPacketProcesser::broadcastPlayerLoginToMapServer(SPlayerPtr player, NetIdType mapServerId)
    {
        SClan* clan;// = player->getMainClan();
        if (NULL == clan)
        {
            DYNAMIC_ASSERT(0);
            return;
        }

        //--------------------------------------------------------------------------

        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER;
            packet->type    = PT_PLAYER_F2M_LOGIN;

            // 转换逻辑包
            PT_PLAYER_F2M_LOGIN_DATA* sendData = (PT_PLAYER_F2M_LOGIN_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->accountId	    = player->getAccountID();
                sendData->clientId	    = player->getClientNetID();
				sendData->clanId		= clan->getClanID();
                sendData->regionType    = (Byte)clan->getFocusRegionType();
                sendData->regionID	    = clan->getFocusRegionID();
                

                // 发送数据
     //           ServerManager::getInstance().broadOrSendNetPacketToActiveMapServer( dataPtr, 
     //               GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_LOGIN_DATA_INFO::dataSize,
					//mapServerId);
            }
        }
    }

    //--------------------------------------------------------------------------
    void PlayerNetPacketProcesser::broadcastPlayerLogoutToMapServer(SPlayerPtr player)
    {
       
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER;
            packet->type    = PT_PLAYER_F2M_LOGOUT;

            // 转换逻辑包
            PT_PLAYER_F2M_LOGOUT_DATA* sendData = (PT_PLAYER_F2M_LOGOUT_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
		        sendData->accountId	= player->getAccountID();
				
                // 发送数据
                ServerManager::getInstance().boardcastNetPacketToAcitveMapServer( dataPtr, 
                    GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_LOGOUT_DATA_INFO::dataSize);
            }
        }
    }

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendRecruitPlayerCharacterToMapServer(SPlayerPtr player, 
		SPlayerCharacter* newPlayerCharacter, NetIdType mapServerNetId)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA_INFO::headSize;
		// 当前发送数据大小
		I32 sendDataSize        = sendDataHeadSize;
		sendDataSize += PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA_INFO::elementSize;

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST;

			// 转换逻辑包
			PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA* sendData = (PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA*)(packet->data);
			sendData->playerCharacterNum = 1;
			
			PlayerCharacterData* playerCharacterData = newPlayerCharacter->getData();

			if ( sendData )
			{
				NetPlayerCharacterInfo *playerCharacter = &(sendData->playerCharacter[0]);
				// 填充逻辑包
				wcscpy_s(playerCharacter->name, _countof(playerCharacter->name), playerCharacterData->mName.c_str());
				// wcscpy_s(newNetPlayerChar.charZiName, _countof(newNetPlayerChar.charZiName), playerCharacterData->charZiName.c_str());
				wcscpy_s(playerCharacter->surName, _countof(playerCharacter->surName), playerCharacterData->charSurName.c_str());

				playerCharacter->Id			            = playerCharacterData->mId;
				playerCharacter->charClanId			    = playerCharacterData->charClanId;
				playerCharacter->accountId              = player->getAccountID();
				playerCharacter->regionType	            = playerCharacterData->mRegionType;
				playerCharacter->regionId               = playerCharacterData->mRegionID;
				playerCharacter->characterTemplateID    = playerCharacterData->mCharacterTemplateID;
				playerCharacter->charCurAge			    = playerCharacterData->charCurAge;
				playerCharacter->charLifeSpan			= playerCharacterData->charLifeSpan;
				playerCharacter->charLvl                = playerCharacterData->mLevel;
				playerCharacter->charExp1               = playerCharacterData->charExp1;
				playerCharacter->charExp2               = playerCharacterData->charExp2;
				playerCharacter->charExp3               = playerCharacterData->charExp3;
				playerCharacter->charHP			        = playerCharacterData->mHp;
				playerCharacter->charMP	                = playerCharacterData->mMp;
				playerCharacter->charLineageNum	        = playerCharacterData->mLineageNum;
				playerCharacter->charArtMashID1			= playerCharacterData->charArtMashID1;
				playerCharacter->charArtMashID2			= playerCharacterData->charArtMashID2;
				playerCharacter->charArtIcon            	= playerCharacterData->charArtIcon;
				playerCharacter->charInfluenceID        	= playerCharacterData->charInfluenceID;
				playerCharacter->charSkillPointAll      	= playerCharacterData->charSkillPointAll;
				playerCharacter->charNoAssignSkillPoint	= playerCharacterData->charNoAssignSkillPoint;
				playerCharacter->charState              	= playerCharacterData->charState;
				playerCharacter->charLifeState          	= playerCharacterData->charLifeState;
				playerCharacter->charDir                	= ((NetVec2)playerCharacterData->mDir).getData();
				playerCharacter->genrealPos	           = ((NetVec2)playerCharacterData->mPos).getData();
				playerCharacter->charAttrAppendId		= playerCharacterData->charAttrAppendId;
				playerCharacter->charAttrAppendLvlAddId = playerCharacterData->charAttrAppendLvlAddId;

				for (Int i=0; i<DB_RECORD_ATTR_NUM; i++)
				{
					playerCharacter->attrRand[i]       = playerCharacterData->charAttrRand[i];
					playerCharacter->attrRandAdd[i]    = playerCharacterData->charAttrRandAdd[i];
				}

				// 发送数据
				//ServerManager::getInstance().broadOrSendNetPacketToActiveMapServer(dataPtr,sendDataSize, 
				//	mapServerNetId);
			}
		}
	}

    //--------------------------------------------------------------------------
    void PlayerNetPacketProcesser::broadcastPlayerCharacterListToMapServer(SPlayerPtr player, NetIdType mapServerId)
    {
		//player->lockClanList();
        SClan* clan;// = player->getMainClan();
        DYNAMIC_ASSERT(clan);
        std::map<U64, SPlayerCharacter*>* playerCharacterList;// = clan->getPlayerCharacterList();
        DYNAMIC_ASSERT(playerCharacterList);

        //--------------------------------------------------------------------------

        // 得到一个大型发送缓存
        GameNetSendDataBufferPtr dataPtr ;
        GameNetPacketData* packet       = NULL;
        PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA* sendData = NULL;

        // 当前发送数据头大小
        I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA_INFO::headSize;
        // 当前发送数据大小
        I32 sendDataSize        = sendDataHeadSize;
        // 准备发送数据大小
        I32 prepareSendDataSize = sendDataHeadSize;

        // 遍历角色队列
        std::map<IdType, SPlayerCharacter*>::iterator iter = playerCharacterList->begin();
	
		// 是否下层进行了克隆
        for ( ; iter != playerCharacterList->end(); iter++)
        {

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA_INFO::elementSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					// 广播到地图服务器
					//ServerManager::getInstance().broadOrSendNetPacketToActiveMapServer(dataPtr,sendDataSize,mapServerId);
					//dataPtr.setNull();
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				packet->channel = GNPC_PLAYER;
				packet->type    = PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST;
				sendData = (PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA*)(packet->data);
				// 清空
				sendData->playerCharacterNum = 0;

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA_INFO::headSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------
            
            // 检测
            SPlayerCharacter* playerCharacter = iter->second;
            DYNAMIC_ASSERT(playerCharacter);
            PlayerCharacterData* playerCharacterData = playerCharacter->getData();
            DYNAMIC_ASSERT(playerCharacterData);

            // 增加角色记录
            NetPlayerCharacterInfo & newNetPlayerChar = sendData->playerCharacter[sendData->playerCharacterNum];

            //填充包
            wcscpy_s(newNetPlayerChar.name, _countof(newNetPlayerChar.name), playerCharacterData->mName.c_str());
			wcscpy_s(newNetPlayerChar.surName, _countof(newNetPlayerChar.surName), playerCharacterData->charSurName.c_str());

            newNetPlayerChar.Id			            = playerCharacterData->mId;
            newNetPlayerChar.charClanId			    = playerCharacterData->charClanId;
            newNetPlayerChar.accountId              = player->getAccountID();
            newNetPlayerChar.regionType	            = playerCharacterData->mRegionType;
            newNetPlayerChar.regionId               = playerCharacterData->mRegionID;
            newNetPlayerChar.characterTemplateID    = playerCharacterData->mCharacterTemplateID;
            newNetPlayerChar.charCurAge			    = playerCharacterData->charCurAge;
			newNetPlayerChar.charLifeSpan			= playerCharacterData->charLifeSpan;
            newNetPlayerChar.charLvl                = playerCharacterData->mLevel;
            newNetPlayerChar.charExp1               = playerCharacterData->charExp1;
            newNetPlayerChar.charExp2               = playerCharacterData->charExp2;
            newNetPlayerChar.charExp3               = playerCharacterData->charExp3;
            newNetPlayerChar.charHP			        = playerCharacterData->mHp;
            newNetPlayerChar.charMP	                = playerCharacterData->mMp;
            newNetPlayerChar.charLineageNum	        = playerCharacterData->mLineageNum;
            newNetPlayerChar.charArtMashID1			= playerCharacterData->charArtMashID1;
            newNetPlayerChar.charArtMashID2			= playerCharacterData->charArtMashID2;
            newNetPlayerChar.charArtIcon            = playerCharacterData->charArtIcon;
            newNetPlayerChar.charInfluenceID        = playerCharacterData->charInfluenceID;
            newNetPlayerChar.charSkillPointAll      = playerCharacterData->charSkillPointAll;
            newNetPlayerChar.charNoAssignSkillPoint	= playerCharacterData->charNoAssignSkillPoint;
            newNetPlayerChar.charState              = playerCharacterData->charState;
            newNetPlayerChar.charLifeState          = playerCharacterData->charLifeState;
            newNetPlayerChar.charDir                = ((NetVec2)playerCharacterData->mDir).getData();
			newNetPlayerChar.genrealPos	            = ((NetVec2)playerCharacterData->mPos).getData();
			newNetPlayerChar.charAttrAppendId		= playerCharacterData->charAttrAppendId;
			newNetPlayerChar.charAttrAppendLvlAddId	= playerCharacterData->charAttrAppendLvlAddId;

			for (Int i=0; i<DB_RECORD_ATTR_NUM; i++)
			{
				newNetPlayerChar.attrRand[i]       = playerCharacterData->charAttrRand[i];
				newNetPlayerChar.attrRandAdd[i]    = playerCharacterData->charAttrRandAdd[i];
			}
            // 递增参数
            sendDataSize += PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA_INFO::elementSize;

            ++sendData->playerCharacterNum;
        }

		//--------------------------------------------------------------------------

        // 如果有剩余则发送
        if ( dataPtr.isNull() == false )
        {
            // 广播到地图服务器
			//ServerManager::getInstance().broadOrSendNetPacketToActiveMapServer(
			//	dataPtr,sendDataSize,mapServerId);
        }
    }

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::broadcastAllListEndToMapServer(NetIdType mapServerId)
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_S2S_SYNC_ALL_LIST_END;

			// 转换逻辑包
			PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA* sendData = (PT_PLAYER_S2S_SYNC_ALL_LIST_END_DATA*)(packet->data);
			if ( sendData )
			{
				// 发送数据
				I32 sendDataSize = GameNetPacketData_INFO::headSize + PT_PLAYER_S2S_SYNC_ALL_LIST_END_INFO::dataSize;
				//ServerManager::getInstance().broadOrSendNetPacketToActiveMapServer(dataPtr, 
				//	sendDataSize, mapServerId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::broadcastTroopGroupListToMapServer(SPlayerPtr player, NetIdType mapServerId)
	{
	}

    //--------------------------------------------------------------------------
    void PlayerNetPacketProcesser::sendTroopListToClient( SPlayerPtr player )
    {
    }

	void PlayerNetPacketProcesser::sendPlayerJumpToRegionNewVer(SPlayerPtr player, NetIdType mapServerNetId, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_F2M_JUMP_REGION;

			// 转换逻辑包
			PT_PLAYER_F2M_JUMP_REGION_DATA* sendData = (PT_PLAYER_F2M_JUMP_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId	    = player->getAccountID();
				sendData->regionId	    = regionId;
				sendData->regionType    = regionType;
				sendData->instanceUid   = instanceUid;

				const Int dataSize = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_JUMP_REGION_INFO::dataSize;
				// 发送数据
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, dataSize, mapServerNetId);
			}
		}
	}


    //--------------------------------------------------------------------------
    void PlayerNetPacketProcesser::broadcastPlayerJumpToRegion(SPlayerPtr player, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid)
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER;
            packet->type    = PT_PLAYER_F2M_JUMP_REGION;

            // 转换逻辑包
            PT_PLAYER_F2M_JUMP_REGION_DATA* sendData = (PT_PLAYER_F2M_JUMP_REGION_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->accountId	    = player->getAccountID();
                sendData->regionId	    = regionId;
				sendData->regionType    = regionType;
				sendData->instanceUid   = instanceUid;
				
				const Int dataSize = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_JUMP_REGION_INFO::dataSize;
                // 发送数据
                ServerManager::getInstance().boardcastNetPacketToAcitveMapServer( dataPtr, dataSize);
            }
        }
    }

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendPlayerJumpToRegionByCharId(NetIdType mapServerNetId, AccountIdType accountId, PlayerCharacterIdType playerCharacterId)
		{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID;

			// 转换逻辑包
			PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA* sendData = (PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId				= accountId;
				sendData->playerCharacterId	    = playerCharacterId;

				const Int dataSize = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_INFO::dataSize;
				
				// 发送数据
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					dataSize, mapServerNetId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendPlayerJumpToMapServer(NetIdType mapServerNetId, SPlayerPtr player, REGION_OBJ_TYPE regionType, RegionIdType regionId, InstanceUIdType instanceUid)
	{
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_F2M_JUMP_REGION;

			// 转换逻辑包
			PT_PLAYER_F2M_JUMP_REGION_DATA* sendData = (PT_PLAYER_F2M_JUMP_REGION_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->accountId	    = player->getAccountID();
				sendData->regionId	    = regionId;
				sendData->regionType    = regionType;
				sendData->instanceUid   = instanceUid;

				const Int dataSize = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_JUMP_REGION_INFO::dataSize;
				// 发送数据
				ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr, 
					dataSize, mapServerNetId);
			}
		}
	}

    //--------------------------------------------------------------------------
    void PlayerNetPacketProcesser::sendPlayerCharacterToClient( I32 netID, SPlayerCharacter* pChar )
    {
        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_PLAYER;
            packet->type    = PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST;

            // 转换逻辑包
            PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA* sendData = (PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包

                // 检测
                PlayerCharacterData* playerCharacterData = pChar->getData();
                DYNAMIC_ASSERT(playerCharacterData);

                // 增加角色记录
                sendData->remainPlayerCharacterNum = 1;
                NetPlayerCharacterInfo & newPlayerCharacterData = sendData->remainPlayerCharacter[0];

				//填充角色记录
				wcscpy_s(newPlayerCharacterData.name, _countof(newPlayerCharacterData.name), playerCharacterData->mName.c_str());
				//wcscpy_s(newPlayerCharacterData.charZiName, _countof(newPlayerCharacterData.charZiName), playerCharacterData->charZiName.c_str());
				wcscpy_s(newPlayerCharacterData.surName, _countof(newPlayerCharacterData.surName), playerCharacterData->charSurName.c_str());

				newPlayerCharacterData.Id			            = playerCharacterData->mId;
				newPlayerCharacterData.charClanId	            = playerCharacterData->charClanId;
				newPlayerCharacterData.genrealPos	            = ((NetVec2)playerCharacterData->mPos).getData();
				newPlayerCharacterData.regionType	            = (REGION_OBJ_TYPE)playerCharacterData->mRegionType;
				newPlayerCharacterData.regionId		            = playerCharacterData->mRegionID;
				newPlayerCharacterData.characterTemplateID       = playerCharacterData->mCharacterTemplateID;
				newPlayerCharacterData.charCurAge			    = playerCharacterData->charCurAge;
				newPlayerCharacterData.charLifeSpan				= playerCharacterData->charLifeSpan;
				newPlayerCharacterData.charLvl	                = playerCharacterData->mLevel;
				newPlayerCharacterData.charExp1	                = playerCharacterData->charExp1;
				newPlayerCharacterData.charExp2		            = playerCharacterData->charExp2;
				newPlayerCharacterData.charExp3                  = playerCharacterData->charExp3;
				newPlayerCharacterData.charHP			        = playerCharacterData->mHp;
				newPlayerCharacterData.charMP	                = playerCharacterData->mMp;
				newPlayerCharacterData.charLineageNum	        = playerCharacterData->mLineageNum;
				newPlayerCharacterData.charArtMashID1			= playerCharacterData->charArtMashID1;
				newPlayerCharacterData.charArtMashID2			= playerCharacterData->charArtMashID2;
				newPlayerCharacterData.charArtIcon			    = playerCharacterData->charArtIcon;
				newPlayerCharacterData.charInfluenceID		    = playerCharacterData->charInfluenceID;
				newPlayerCharacterData.charSkillPointAll         = playerCharacterData->charSkillPointAll;
				newPlayerCharacterData.charNoAssignSkillPoint    = playerCharacterData->charNoAssignSkillPoint;
				newPlayerCharacterData.charState         	    = playerCharacterData->charState;
				newPlayerCharacterData.charLifeState	            = playerCharacterData->charLifeState;
				newPlayerCharacterData.charDir		            = ((NetVec2)playerCharacterData->mDir).getData();
				newPlayerCharacterData.charAttrAppendId			= playerCharacterData->charAttrAppendId;
				newPlayerCharacterData.charAttrAppendLvlAddId	= playerCharacterData->charAttrAppendLvlAddId;

				for (Int i=0; i<DB_RECORD_ATTR_NUM; i++)
				{
					newPlayerCharacterData.attrRand[i]       = playerCharacterData->charAttrRand[i];
					newPlayerCharacterData.attrRandAdd[i]    = playerCharacterData->charAttrRandAdd[i];
				}

                // 发送客户端
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST_DATA_INFO::dataSize,
					netID);
            }
        }
    }

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::sendMainPlayerCharacterToClient( I32 netID, SPlayerCharacter* pChar )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_PLAYER;
			packet->type    = PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO;

			// 转换逻辑包
			PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO_DATA* sendData = (PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包

				// 检测
				PlayerCharacterData* playerCharacterData = pChar->getData();
				DYNAMIC_ASSERT(playerCharacterData);
				sendData->generalId = playerCharacterData->mId;

				// 发送客户端
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_PLAYER_F2C_MAIN_PLAYERCHARACTER_INFO_DATA_INFO::dataSize,
					netID );
			}
		}
	}

	//--------------------------------------------------------------------------
	void PlayerNetPacketProcesser::broadcastPlayerCharacterEquipListToMapServer( SPlayerPtr player,NetIdType mapServerId /*= 0*/ )
	{
		//将玩家氏族下的所有角色的装备信息发送给MapServer
		SClan* clan;// = player->getMainClan();
		DYNAMIC_ASSERT(clan);
		SItemManager* itemManager = clan->getItemManager();
		DYNAMIC_ASSERT(itemManager);
        
		std::map<PlayerCharacterIdType, GenrealEquip*>* tempGenrealEquipMap = itemManager->getGenrealEquipMap();
		
		//--------------------------------------------------------------------------

		// 得到一个大型发送缓存
		GameNetSendDataBufferPtr dataPtr;
		GameNetPacketData* packet       = NULL;
		PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA* sendData = NULL;
        
		// 当前发送数据头大小
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA_INFO::headSize;
		// 当前发送数据大小
		I32 sendDataSize        = sendDataHeadSize;
		// 准备发送数据大小
		I32 prepareSendDataSize = sendDataHeadSize;

		// 遍历角色装备队列
		std::map<PlayerCharacterIdType, GenrealEquip*>::iterator frontGenrealEquip = tempGenrealEquipMap->begin();
		std::map<PlayerCharacterIdType, GenrealEquip*>::iterator backGenrealEquip = tempGenrealEquipMap->end();

        while (frontGenrealEquip != backGenrealEquip)
        {

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// 递增一个角色数据大小到发送数据缓存大小
				prepareSendDataSize = sendDataSize + PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA_INFO::elementSize;

				// 如果大于缓存最大大小则发送
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					// 广播到地图服务器
					//ServerManager::getInstance().broadOrSendNetPacketToActiveMapServer(dataPtr,
					//	sendDataSize,mapServerId);
					
					dataPtr.setNull();
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// 得到一个大型发送缓存
				FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;

				packet->channel = GNPC_PLAYER;
				packet->type    = PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST;
				sendData = (PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA*)(packet->data);
				// 清空
				sendData->playerCharacterNum = 0;

				// 当前发送数据头大小
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA_INFO::headSize;
				// 当前发送数据大小
				sendDataSize        = sendDataHeadSize;
				// 准备发送数据大小
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------
		
			//每一个角色的装备
			PlayerItem** tempItemArr = frontGenrealEquip->second->getEquipItemArray();
			//增加角色记录
            netPlayerCharacterEquip& newEquipInfo = sendData->playerCharacterEquip[sendData->playerCharacterNum];
			
			//填充包
            newEquipInfo.charid = frontGenrealEquip->first;
			for (Int i=1; i<ITEM_EQUIP_SLOT_TYPE_MAX; i++)
			{   
				if ( tempItemArr[i] )
				{
					newEquipInfo.equipAttr[i].equipId = tempItemArr[i]->getItemTempID();
					newEquipInfo.equipAttr[i].curStrengthenLv = tempItemArr[i]->getItemRecord()->curStrengthenLv;
					newEquipInfo.equipAttr[i].randAppendID = tempItemArr[i]->getItemRecord()->randAppendID;
					newEquipInfo.equipAttr[i].strengthenAppendID = tempItemArr[i]->getItemRecord()->strengthenAppendID;
				}
				else
				{
					newEquipInfo.equipAttr[i].equipId = 0;
					newEquipInfo.equipAttr[i].curStrengthenLv = 0;
					newEquipInfo.equipAttr[i].randAppendID = 0;
					newEquipInfo.equipAttr[i].strengthenAppendID = 0;
				}	
			}
			
			//递增参数
			sendDataSize += PT_PLAYER_F2M_PLAYERCHARACTER_EQUIP_INFO_LIST_DATA_INFO::elementSize;
			++sendData->playerCharacterNum;
			//
			frontGenrealEquip++;
        }
        
		//--------------------------------------------------------------------------
		//剩余发送
		if ( dataPtr.isNull() == false )
		{
			// 广播到地图服务器
			//ServerManager::getInstance().broadOrSendNetPacketToActiveMapServer(dataPtr,
			//	sendDataSize, mapServerId);
			dataPtr.setNull();
		}
	}
}