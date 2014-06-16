/******************************************************************************/
#include "stdafx.h"
#include "LoginNetPacketProcesser.h"
#include "GameNetPacket.h"
#include "ClientManager.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "LoginManager.h"
#include "SPlayer.h"
#include "PlayerCharacterNetPacket.h"
#include "PlaceNetPacket.h"
//#include "SWorldManager.h"
#include "SClan.h"

#include "PlayerCharacterData.h"
#include "SWorldManager.h"
#include "ThreadTaskManager.h"
#include "CharacterList.h"
/******************************************************************************/

namespace MG
{
    //--------------------------------------------------------------------------
    LoginNetPacketProcesser::LoginNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    LoginNetPacketProcesser::~LoginNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    Bool LoginNetPacketProcesser::processClientPacket(I32 id, NetEventRecv* packet)
    {
        if (packet->getChannel() == GNPC_LOGIN)
        {
			//FUNDETECTION(__MG_FUNC__);
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_LOGIN_C2F_ACC_LOGIN:	
				onClientLogin( id , (PT_LOGIN_C2F_LOGIN_DATA*)data->data);
				break;
            case PT_LOGIN_C2F_CREATE_CLAN:
				ThreadTaskManager::getInstance().addCreateClanTask(packet,id);
                //onClientCreateClan( id, (PT_LOGIN_C2F_CREATE_CLAN_DATA*)data->data );
                break;
            case PT_LOGIN_C2F_DELETE_CLAN:
				ThreadTaskManager::getInstance().addDeleteClanTask(id,packet,id);
                //onClientDeleteClan( id, (PT_LOGIN_C2F_DELETE_CLAN_DATA*)data->data );
                break;
            case PT_LOGIN_C2F_JOINGAME:
				ThreadTaskManager::getInstance().addJoinGameTask(packet,id);
                //onClientJoinGame( id );
                break;
            case PT_LOGIN_C2F_CREATE_GENERAL:
				ThreadTaskManager::getInstance().addCreateGeneralTask(packet,id,id);
                //onClientCreateGenreal( id, (PT_LOGIN_C2F_CREATE_GENERAL_DATA*)data->data );
                break;
            case PT_LOGIN_C2F_ACC_LOGOUT:
                onClientLogout( id );
                break;
            //case PT_LOGIN_C2F_SELECT_CLAN:
                //onClientSelectClan( id, (PT_LOGIN_C2F_SELECT_CLAN_DATA*)data->data );
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
    Bool LoginNetPacketProcesser::processLoginServerPacket(I32 id, NetEventRecv* packet)
    {
        if ( packet->getChannel() == GNPC_LOGIN )
        {   
			//FUNDETECTION(__MG_FUNC__);
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_LOGIN_L2F_CLIENT_CHECKED:
				//ThreadTaskManager::getInstance().addPrepareJoinGameTask(packet);
				onRecvClientLoginResultFromLoginServer( id , (PT_LOGIN_L2F_CLIENT_CHECKED_DATA*)data->data);
				break;
			case PT_LOGIN_L2F_CHECK_INFRONTSERVER:
				onRecvCheckClientInServerFromLs(id,(PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA*) data->data);
			}

            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------
    Bool LoginNetPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
    {
		if ( packet->getChannel() == GNPC_LOGIN )
		{   
			//FUNDETECTION(__MG_FUNC__);
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
				break;
			case PT_LOGIN_M2F_CHECK_INFRONTSERVER:
				onRecvCheckClientInServerFromMs(id,(PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA*) data->data);
			}

			return true;
		}
        return false;
    }

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientListenInfoToLoginServer( CChar* clientListenIp, I32 clientListenPort )
	{
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2L_FRONT_SERVER_LOGIN;

            // ת���߼���
            PT_LOGIN_F2L_LOGIN_DATA* sendData = (PT_LOGIN_F2L_LOGIN_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                StrnCpyS(sendData->ip,clientListenIp,MG_NET_MAX_IP_LEN);
                sendData->port = clientListenPort;

                // ��������
				ServerManager::getInstance().sendNetPacketToLoginServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2L_LOGIN_DATA_INFO::dataSize );
            }
        }
    }

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientLoginCheckToLoginServer( I32 clientID, Char16* accName, Char16* accPsw )
	{
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2L_CLIENT_LOGIN;

            // ת���߼���
            PT_LOGIN_F2L_CLIENT_LOGIN_DATA* sendData = (PT_LOGIN_F2L_CLIENT_LOGIN_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->clientNetIdInFrontServer = clientID;
                WStrnCpyS(sendData->data.accName ,accName, MAX_ACCOUNT_LONGIN_NAME_LEN);
                WStrnCpyS(sendData->data.accPsw ,accPsw, MAX_ACCOUNT_LONGIN_PSW_LEN);

                // ��������
				ServerManager::getInstance().sendNetPacketToLoginServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2L_CLIENT_LOGIN_DATA_INFO::dataSize );
            }
        }
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientLogoutToLoginServer(CChar16* accName )
	{
        // ���һ�����͡�����ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2L_CLIENT_LOGOUT;

            // ת���߼���
            PT_LOGIN_F2L_CLIENT_LOGOUT_DATA* sendData = (PT_LOGIN_F2L_CLIENT_LOGOUT_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
		        WStrnCpyS(sendData->accName ,accName, MAX_ACCOUNT_LONGIN_NAME_LEN);

                // ��������
                //dataPtr->send( GameNetPacketData_INFO::headSize + PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_INFO::dataSize, loginServerNetID );
				ServerManager::getInstance().sendNetPacketToLoginServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2L_CLIENT_LOGOUT_DATA_INFO::dataSize);
            }
        }
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendCheckClientInServerRelultToLs( I32 clientNetIdInLs,Bool result )
	{
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT;

			// ת���߼���
			PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA* sendData = (PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->clientNetIdInLoginServer = clientNetIdInLs;
				result ? sendData->result = 1 : sendData->result = 0;

				// ��������
				ServerManager::getInstance().sendNetPacketToLoginServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA_INFO::dataSize);
			}
		}
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::onRecvClientLoginResultFromLoginServer( I32 id , PT_LOGIN_L2F_CLIENT_CHECKED_DATA* data)
	{
		ClientObject* clientPtr = ClientManager::getInstance().getClientObject( data->clientNetID );
		if (clientPtr)
		{
			LoginManager::getInstance().onClientLoginSuccessedFromLoginServer( clientPtr, data->accID );
		}
		//LoginManager::getInstance().handleClientLoginCheckResult( data->clientNetID, 
		//	data->data.accName, data->data.accPsw,
		//	data->accID, data->result);
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::onRecvCheckClientInServerFromLs( I32 id,PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA* data )
	{
		LoginManager::getInstance().handleCheckClientInServerFromLs(id,data->clientNetIdInFrontServer,data->clientNetIdInLoginServer);
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientConnectFrontServerResult( I32 id, PT_LOGIN_F2C_LOGIN_RESULT_TYPE result, PlayerIdType accountId )
	{
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2C_ACC_LOGIN_RESULT;

            // ת���߼���
            PT_LOGIN_F2C_LOGIN_RESULT_DATA* sendData = (PT_LOGIN_F2C_LOGIN_RESULT_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->result = result;
				sendData->accountId = accountId;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2C_LOGIN_RESULT_DATA_INFO::dataSize,
					id );
            }
        }
    }

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::onClientLogin( I32 id, PT_LOGIN_C2F_LOGIN_DATA* data )
	{
		LoginManager::getInstance().handleClientLogin( id, data->data.accName, data->data.accPsw );
	}
        
    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendClientOpenClanCreateUI( I32 id )
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2C_OPEN_CREATECLANUI;

            // ��������
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,GameNetPacketData_INFO::headSize , id);
        }
    }

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendClientClanCreateResult( I32 id, CreateClanResult result, const ClanData& _clandata )
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2C_CREATE_CLAN_RESULT;

            // ת���߼���
            PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* sendData = (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->result = result;
				sendData->clanId = _clandata.clanId;
				sendData->regionID = _clandata.regionID;
				sendData->clanbagsize = _clandata.clanbagSize;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA_INFO::dataSize, 
					id);
            }
        }
    }

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendClientClanDeleteResult( I32 id, I32 index )
    {
#if 0
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
			packet->type    = PT_LOGIN_F2C_DELETE_CLAN_RESULT;

            // ת���߼���
            PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA* sendData = (PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->result = (DeleteClanResult)index;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA_INFO::dataSize,
					id );
            }
        }
#endif
    }

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientClanInfo( I32 id, ClanData* _pClanData )
	{
		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
		FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_LOGIN_F2C_CLAN_DATA;

			// ת���߼���
			PT_LOGIN_F2C_CLAN_DATA_DATA* sendData = (PT_LOGIN_F2C_CLAN_DATA_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->accountId		 = _pClanData->accountId;
				sendData->clandatabaseid  = _pClanData->clanId;
				sendData->status          = _pClanData->status;
				sendData->ConstellationId = _pClanData->ConstellationId;
				sendData->armyemblem      = _pClanData->armyemblem;
				sendData->armyemblemcolor = _pClanData->armyemblemcolor;
				sendData->bg              = _pClanData->bg;
				sendData->bgcolor         = _pClanData->bgcolor;
				wcscpy_s( sendData->clanhomelandname, _pClanData->clanHomeLandName.length()+1, _pClanData->clanHomeLandName.c_str() );
				wcscpy_s( sendData->clanname, _pClanData->clanName.length()+1, _pClanData->clanName.c_str() );
				sendData->mainGenrealId   = _pClanData->mainGenrealId;
				sendData->wiseGenrealId  = _pClanData->wiseGenrealId;
				sendData->commanderGenrealId = _pClanData->commanderGenrealId;
				sendData->curGenrealId	 = _pClanData->curGenrealId;
				sendData->regionID        = _pClanData->regionID;
				sendData->clanbagsize     = _pClanData->clanbagSize;
				sendData->clanLevel		 = _pClanData->clanLevel;
				memcpy((void*)sendData->clanExp, (void*)_pClanData->clanExp, sizeof(_pClanData->clanExp));
				memcpy((void*)sendData->clanMoney, (void*)_pClanData->clanMoney, sizeof(_pClanData->clanMoney));
				

				// ��������
				//FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
				//	GameNetPacketData_INFO::headSize + PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA_INFO::dataSize,
				//	id );
			}
		}
	}

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendClientOpenClanControlUI( I32 id )
    {
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );
        GameNetPacketData* packet       = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2C_OPEN_CLANCONTROLUI;
	
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
				GameNetPacketData_INFO::headSize,
				id );
        }
    }

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::onClientCreateClan( I32 id, PT_LOGIN_C2F_CREATE_CLAN_DATA* data )
    {
        //����
        ClanData clanData;
		clanData.accountId	= data->accountid;
        clanData.ConstellationId = data->ConstellationId;
        clanData.armyemblem = data->armyemblem;
        clanData.armyemblemcolor = data->armyemblemcolor;
        clanData.bg = data->bg;
        clanData.bgcolor = data->bgcolor;
        clanData.clanHomeLandName = data->clanhomelandname;
        clanData.clanName = data->clanname;
		//Debug ��ʱʹ�ù̶��ļ��������ͼ �Ժ�Ҫ�޸ĳ� ����ѡ��ĵ�ͼ ���� ������
		clanData.regionID = 273;
		clanData.regionType = ROT_PLACE;

		CreateClanResult createclanresult = LoginManager::getInstance().handleClientCreateClan(id, clanData);
		
		//sendClientClanCreateResult(id, );
    }

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::onClientDeleteClan( I32 id, PT_LOGIN_C2F_DELETE_CLAN_DATA* data )
    {
		/*SPlayerPtr player = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(mClientNetId);
		if (player.isNull())
		{
			LoginManager::getInstance().sendClientDeleteClanResult(mClientNetId,DeleteClanResult_OtherError) ;
		}
		if (player->deleteClanFromMemAndDB(((PT_LOGIN_C2F_DELETE_CLAN_DATA*)data->data)->clandatabaseid))
		{
			LoginManager::getInstance().sendClientDeleteClanResult(mClientNetId,DeleteClanResult_OtherError) ;
		}*/
    }

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::onClientJoinGame( I32 id, PT_LOGIN_C2F_JOINGAME_DATA* data )
    {
		LoginManager::getInstance().handleClientJoinGame(id, data->accountId);
    }

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::onClientCreateGenreal( I32 id, PT_LOGIN_C2F_CREATE_GENERAL_DATA* data )
    {
		const CharacterResInfo* createChar = CharacterResourceConfig::getInstance().getCharacterResourceInfo(data->resID);
		if (NULL == createChar)
		{
			DYNAMIC_ASSERT_LOG(0, "�Ҳ������ñ�CharacterResourceConfig��Դ");
			return;
		}
		const CharacterTempInfo* charGeneral = CharacterTemplate::getInstance().getCharacterTempInfo(createChar->templateid);
		if (NULL == charGeneral)
		{
			DYNAMIC_ASSERT_LOG(0, "�Ҳ������ñ�CharacterTemplate��Դ");
			return;
		}

 		PlayerCharacterData playerCharData;
 		playerCharData.mName = data->name;
 		playerCharData.charSurName = data->charSurName;
 		playerCharData.mCharacterTemplateID = createChar->templateid;
 		playerCharData.charArtIcon = data->charArtIcon;
		playerCharData.charAccountId = data->accountId;

		CreateGenrealResult creategenrealresult = LoginManager::getInstance().handleClientCreateGenreal(id, playerCharData, createChar);

		//LoginNetPacketProcesser::getInstance().sendClientCreateGenrealResult(id, creategenrealresult, &playerCharData);
    }

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendClientOpenGenrealCreateUI( I32 id )
    {
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2C_OPENCRETEGENREALUI;

            // ��������
			FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,GameNetPacketData_INFO::headSize , id);
        }
    }

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendClientCreateGenrealResult(I32 id, I32 index, Bool isGenreal, IdType genrealID)
    {
#if 0
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2C_CREATE_GENERAL_RESULT;

            // ת���߼���
            PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* sendData = (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->result = (CreateGenrealResult)index;
                sendData->genrealID = _playercharacterdata->mId;
				sendData->charTempId = _playercharacterdata->mCharacterTemplateID;
				sendData->clanId = _playercharacterdata->charClanId;
				sendData->regionId = _playercharacterdata->mRegionID;
				sendData->regionType = _playercharacterdata->mRegionType;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA_INFO::dataSize , 
					id );
            }
        }
#endif
    }

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendMapServerListToMapServer( I32 id, std::vector<MapServerInfo*>& mapVec )
	{
       
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::broadMapServerListToMapServer( std::map< I32, MapServerInfo* > &MapServerList )
	{
		//�����б�
		std::vector<MapServerInfo*> mapVec;
		for (std::map< I32, MapServerInfo* >::iterator it = MapServerList.begin(); it != MapServerList.end(); ++it)
		{
			mapVec.push_back(it->second);
		}

		//�㲥
		std::map< I32, MapServerInfo* >::iterator itMap = MapServerList.begin();
		for ( ; itMap != MapServerList.end(); ++itMap)
		{
			sendMapServerListToMapServer(itMap->first, mapVec);
		}	
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendCheckClientInServerRelultToMs( I32 mapServerNetId,I32 clientNetId,Bool result )
	{
		// ���һ�����͡�����ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT;

			// ת���߼���
			PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA* sendData = (PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				sendData->clientNetIdInFrontServer = clientNetId;
				result ? sendData->result = 1 : sendData->result = 0;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2M_CHECK_INFRONTSERVER_RESULT_DATA_INFO::dataSize,
					mapServerNetId );
			}
		}
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::onRecvCheckClientInServerFromMs( I32 id,PT_LOGIN_M2F_CHECK_INFRONTSERVER_DATA* data )
	{
		LoginManager::getInstance().handleCheckClientInServerFromMs(id,data->clientNetIdInFrontServer);
	}

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::onClientLogout( I32 id )
    {
		//ClientObject
        FrontServerMain::getInstance().getServerLauncher()->closeClient(id);
    }

    ////--------------------------------------------------------------------------
    //void LoginNetPacketProcesser::onClientSelectClan( I32 id, PT_LOGIN_C2F_SELECT_CLAN_DATA* data )
    //{
    //    SelectClanResult res = (SelectClanResult)LoginManager::getInstance().handleClanSelect(id, data->clandatabaseid);
    //    sendClientClanSelectResult(id, res);
    //}

    //--------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendClientClanSelectResult( I32 id, I32 index )
    {
#if 0
        // ���һ�����͡��ͻ��ˡ�����
        GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_F2C_SELECT_CLAN_RESULT;

            // ת���߼���
            PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA* sendData = (PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA*)(packet->data);
            if ( sendData )
            {
                // ����߼���
                sendData->result = (SelectClanResult)index;

                // ��������
				FrontServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA_INFO::dataSize , 
					id );
            }
        }
#endif
    }

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientJoinGameToChatServer(I32 clientNetId,U64 accountId,CChar16* clanName )
	{
        I32 chatServerId = ServerManager::getInstance().getChatServerNetId();
        if ( chatServerId < 0 )
            return;

        //--------------------------------------------------------------------------

		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_LOGIN_F2A_JOINGAME;

			// ת���߼���
			PT_LOGIN_F2A_JOINGAME_DATA* sendData = (PT_LOGIN_F2A_JOINGAME_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				WStrnCpyS(sendData->clanName,clanName,MAX_CLAN_NAME);
				sendData->clientNetId = clientNetId;
				sendData->accountId = accountId;

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2A_JOINGAME_DATA_INFO::dataSize,
					chatServerId );
			}
		}
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientExitGameToChatServer( CChar16* clanName )
	{
        

        I32 chatServerId = ServerManager::getInstance().getChatServerNetId();
        if ( chatServerId < 0 )
            return;

        //--------------------------------------------------------------------------

		// ���һ�����͡��ͻ��ˡ�����
		GameNetSendDataBufferPtr dataPtr ;
        FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_LOGIN_F2A_EXITGAME;

			// ת���߼���
			PT_LOGIN_F2A_EXITGAME_DATA* sendData = (PT_LOGIN_F2A_EXITGAME_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				WStrnCpyS(sendData->clanName,clanName,MAX_CLAN_NAME);

				// ��������
				FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, 
					GameNetPacketData_INFO::headSize + PT_LOGIN_F2A_JOINGAME_DATA_INFO::dataSize,
					chatServerId);
			}
		}
	}

	//--------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientListInGameToChatServer()
	{
        I32 chatServerId = ServerManager::getInstance().getChatServerNetId();
        if ( chatServerId < 0 )
            return;

        //--------------------------------------------------------------------------

		// �õ�һ�����ͷ��ͻ���
		GameNetSendDataBufferPtr dataPtr ;
		GameNetPacketData* packet       = NULL;
		PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA* sendData = NULL;

		// ��ǰ��������ͷ��С
		I32 sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO::headSize;
		// ��ǰ�������ݴ�С
		I32 sendDataSize        = sendDataHeadSize;
		// ׼���������ݴ�С
		I32 prepareSendDataSize = sendDataHeadSize;

		// ��ʱ��������
		const ClanData* tempClanData = NULL;

		//--------------------------------------------------------------------------

		// ����playerList
		SPlayerPtr player;
		I32 currPlayerIndex = 0;
		NetIdType clientId = -1;
		Bool isContinue = true;

		while(isContinue)
		{

			//--------------------------------------------------------------------------

			//isContinue = SWorldManager::getInstance().getGameObjectManager()->traversalPlayerList(currPlayerIndex,clientId,player);

			if (!isContinue)
			{
				break;
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() == false )
			{
				// ����һ���������ݴ�С���������ݻ����С
				prepareSendDataSize = sendDataSize + PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO::elmentSize;

				// ������ڻ�������С����
				if ( prepareSendDataSize >= dataPtr->getLogicDataMaxSize() )
				{
					FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,sendDataSize, chatServerId );
					dataPtr.setNull();
				}
			}

			//--------------------------------------------------------------------------

			if ( dataPtr.isNull() )
			{
				// �õ�һ�����ͷ��ͻ���
				FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr, MG_GAME_NET_PACKET_BIG_MAX_SIZE );
				packet       = (GameNetPacketData*) dataPtr->getLogicData();
				if ( !packet )
					return;
				
				packet->channel = GNPC_LOGIN;
				packet->type    = PT_LOGIN_F2A_CLIENTLIST_INGAME;
				//PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA* sendData = (PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA*)(packet->data);
                sendData = (PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA*)(packet->data);

				// ���
				sendData->count = 0;

				// ��ǰ��������ͷ��С
				sendDataHeadSize    = GameNetPacketData_INFO::headSize + PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO::headSize;
				// ��ǰ�������ݴ�С
				sendDataSize        = sendDataHeadSize;
				// ׼���������ݴ�С
				prepareSendDataSize = sendDataHeadSize;
			}

			//--------------------------------------------------------------------------

			// ���Ӽ����¼
			SClanPtr clan;
			player->getMainClan(clan);
			//Clan* clan = player->getMainClan();
			//if (!clan)
			//{
			//	DYNAMIC_ASSERT(false);
			//	// ���ش���
			//}

			//
			Str16 tempName = clan->getClanHomeLandName() + clan->getName() + Str16(L"��");

			PT_LOGIN_F2A_JOINGAME_DATA& newClanData = sendData->data[sendData->count];
			newClanData.accountId = player->getAccountID();
			memcpy(newClanData.clanName,tempName.c_str(),MAX_CLAN_NAME * sizeof(tempName.c_str()[0]));
			newClanData.clientNetId = clientId;

			// ��������
			sendDataSize += PT_LOGIN_F2A_CLIENTLIST_INGAME_DATA_INFO::elmentSize;
			++sendData->count;
		}


		//--------------------------------------------------------------------------
		// �����ʣ������
		if ( dataPtr.isNull() == false )
		{
			FrontServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,sendDataSize, chatServerId );
			dataPtr.setNull();
		}
		
	}

}