/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "LoginNetPacketProcesser.h"
#include "CPlayer.h"
#include "PlayerCharacterData.h"
#include "CClientNew.h"
#include "VersionSwitch.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------------
	Bool LoginNetPacketProcesser::processLoginServerPacket( CClient* client, NetEventRecv* packet )
	{
        if ( packet->getChannel() == GNPC_LOGIN )
        {   
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_LOGIN_L2C_ACC_LOGIN_FAIL:
                onClientLoginFailedFromLoginServer( client , (PT_LOGIN_L2C_LOGIN_FAIL_DATA*)data->data);
                break;
            case PT_LOGIN_L2C_ACC_LOGIN_SUCCESS:	
                onClientLoginSuccessedFromLoginServer( client , (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA*)data->data);
                break;
			//case PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO:
			//	onClientLoginQueueInfoFromLoginServer(client,(PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA*)data->data);
				break;
            }
            return true;
        }

		return false;
	}
    
	//-----------------------------------------------------------------------------
	Bool LoginNetPacketProcesser::processFrontServerPacket( CClient* client,NetEventRecv* packet )
	{
        if ( packet->getChannel() == GNPC_LOGIN )
        {   
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_LOGIN_F2C_ACC_LOGIN_RESULT:
                onRecvClientLoginResultFromFrontServer( client, (PT_LOGIN_F2C_LOGIN_RESULT_DATA*)data->data );
                break;
            case PT_LOGIN_F2C_OPEN_CREATECLANUI:
                onRecvClientOpenCreateClanUIFromFrontServer( client );
                break;
			case PT_LOGIN_F2C_CLAN_LIST:
				onRecvClientClanInfoFromFrontServer( client, (PT_LOGIN_F2C_CLAN_LIST_DATA*) data->data );
				break;
            case PT_LOGIN_F2C_OPEN_CLANCONTROLUI:
                onRecvClientOpenClanControlUIFromFrontServer( client);
                break;
            case PT_LOGIN_F2C_CREATE_CLAN_RESULT:
                onRecvClientCreateClanResultFromFrontServer( client, (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA*)data->data );
                break;
            case PT_LOGIN_F2C_DELETE_CLAN_RESULT:
                onRecvClientDeleteClanResultFromFrontServer( client, (PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA*)data->data );
                break;
            case PT_LOGIN_F2C_OPENCRETEGENREALUI:
                onRecvClientOpenCreateGenrealUIFromFrontServer( client );
                break;
            case PT_LOGIN_F2C_CREATE_GENERAL_RESULT:
                onRecvClientCreateGenrealResultFromFrontServer( client, (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA*)data->data );
                break;
            case PT_LOGIN_F2C_SELECT_CLAN_RESULT:
                onRecvClientSelectClanResultFromFrontServer(client, (PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA*)data->data);
                break;
            }
            return true;
        }
		else if (packet->getChannel() == GNPC_MONSTER)
		{
			return true;
		}
      
		return false;
	}

	//-----------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendLoginPacketToLoginServer(I32 netId,CChar16* name, CChar16* password)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_C2L_ACC_LOGIN;

            // 转换逻辑包
            PT_LOGIN_C2L_LOGIN_DATA* sendData = (PT_LOGIN_C2L_LOGIN_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                MGStrOp::sprintf(sendData->accName,MAX_ACCOUNT_LONGIN_NAME_LEN,L"%s",(Char*)name);
                MGStrOp::sprintf(sendData->accPsw,MAX_ACCOUNT_LONGIN_PSW_LEN,L"%s",(Char*)password);
				MGStrOp::sprintf(sendData->clientVersionNum,MAX_VERSION_NUM_LEN,"%s",CLIENT_VERSION_NUMBER);

                // 发送数据
                ClientNetApplyManager::getInstance().sendLoginServerPacket(netId, dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2L_LOGIN_DATA_INFO::dataSize );
            }
        }
	}

    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onClientLoginFailedFromLoginServer( CClient* client , PT_LOGIN_L2C_LOGIN_FAIL_DATA* data )
    {
		//FUNDETECTION(__MG_FUNC__);
       // LoginManager::getInstance().onLoginToLoginServerFailed( data->errResult );
    }

    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onClientLoginSuccessedFromLoginServer( CClient* client, PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* data )
    { 
		//FUNDETECTION(__MG_FUNC__);
        //LoginManager::getInstance().onLoginToLoginServerSuccessed( data->ip, data->port );
    }
    
	//-----------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendLoginPacketToFrontServer(I32 netId,CChar16* name, CChar16* password)
	{
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_C2F_ACC_LOGIN;

            // 转换逻辑包
            PT_LOGIN_C2F_LOGIN_DATA* sendData = (PT_LOGIN_C2F_LOGIN_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                MGStrOp::sprintf(sendData->data.accName,MAX_ACCOUNT_LONGIN_NAME_LEN,L"%s",(Char*)name);
                MGStrOp::sprintf(sendData->data.accPsw,MAX_ACCOUNT_LONGIN_PSW_LEN,L"%s",(Char*)password);
				MGStrOp::sprintf(sendData->data.clientVersionNum,MAX_VERSION_NUM_LEN,"%s",CLIENT_VERSION_NUMBER);

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket(netId, dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_LOGIN_DATA_INFO::dataSize );
            }
        }
	}

	//-----------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendSelectCharacterPacketToFrontServer(I32 netId,UInt id)
	{
		/*PT_ACC_C2F_SELECT_CHARACTER_DATA data;
		data.characterId = id;
		ClientNetApplyManager::getInstance().sendFrontServerPacket(GNPC_LOGIN,PT_ACC_C2F_SELECT_CHARACTER,(Char*)&data,sizeof(data));*/
	}

    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientLoginResultFromFrontServer(CClient* client , PT_LOGIN_F2C_LOGIN_RESULT_DATA* data )
    {
		//FUNDETECTION(__MG_FUNC__);
        //LoginManager::getInstance().onRecvLoginToFrontServerResult( data->result );
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendClanInfoToFrontServer( I32 netId, CClan* pClan  )
    {
        assert(pClan);

        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_C2F_CREATE_CLAN;

            // 转换逻辑包
            PT_LOGIN_C2F_CREATE_CLAN_DATA* sendData = (PT_LOGIN_C2F_CREATE_CLAN_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                wcscpy_s( sendData->clanDatabase.clanhomelandname, pClan->getClanHomeLandName().length()+1, pClan->getClanHomeLandName().c_str() );
                wcscpy_s( sendData->clanDatabase.clanname, pClan->getName().length()+1, pClan->getName().c_str() );
                sendData->clanDatabase.clandatabaseid = 0;
                sendData->clanDatabase.status = 0;
                sendData->clanDatabase.ancestry = 0;
                sendData->clanDatabase.armyemblem = 0;
                sendData->clanDatabase.armyemblemcolor = 0;
                sendData->clanDatabase.bg = 0;
                sendData->clanDatabase.bgcolor = 0;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket(netId, dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_CREATE_CLAN_DATA_INFO::dataSize );
            }
        }

    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendDeleteClanToFrontServer(I32 netId, U64 clanid )
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_C2F_DELETE_CLAN;

            // 转换逻辑包
            PT_LOGIN_C2F_DELETE_CLAN_DATA* sendData = (PT_LOGIN_C2F_DELETE_CLAN_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->clandatabaseid = clanid;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( netId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_DELETE_CLAN_DATA_INFO::dataSize );
            }
        }
    
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientOpenCreateClanUIFromFrontServer( CClient* client )
    {
		//FUNDETECTION(__MG_FUNC__);
        //LoginManager::getInstance().openClanCreateUI();
    }
	void LoginNetPacketProcesser::onRecvClientClanInfoFromFrontServer( CClient* client, PT_LOGIN_F2C_CLAN_LIST_DATA* data )
	{
		ClanData clanData;
		client->getPlayerObj()->setAccountID(data->clanDatabase[0].accountid);
		for (U32 i=0; i<data->nCount; i++)
		{
			clanData.clanId            = data->clanDatabase[i].clandatabaseid;
			clanData.accountId         = data->clanDatabase[i].accountid;
			clanData.status            = data->clanDatabase[i].status;
			clanData.clanHomeLandName  = data->clanDatabase[i].clanhomelandname;
			clanData.clanName          = data->clanDatabase[i].clanname;
			clanData.ancestry          = data->clanDatabase[i].ancestry;
			clanData.armyemblem        = data->clanDatabase[i].armyemblem;
			clanData.armyemblemcolor   = data->clanDatabase[i].armyemblemcolor;
			clanData.bg                = data->clanDatabase[i].bg;
			clanData.bgcolor           = data->clanDatabase[i].bgcolor;
			clanData.mainGenrealId     = data->clanDatabase[i].mainGenrealId;
			clanData.clanbagSize       = data->clanDatabase[i].clanbagsize;
			clanData.regionID          = data->clanDatabase[i].regionID;
			clanData.regionType        = (REGION_OBJ_TYPE)data->clanDatabase[i].regionType;

			//
			Int clanSize = client->getPlayerObj()->getClanList()->size();

			if (clanSize>0)
			{
				return;
			}
			client->getPlayerObj()->addClan(&clanData);
			//暂时写在这。
			if (i == 0)
				client->getPlayerObj()->setActive(clanData.clanId);
		}
	}
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientOpenClanControlUIFromFrontServer( CClient* client)
    {      
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientCreateClanResultFromFrontServer( CClient* client, PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* data )
    {
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientDeleteClanResultFromFrontServer( CClient* client, PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA* data )
    {
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientCreateGenrealResultFromFrontServer( CClient* client, PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* data )
    {
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendJoingameToFrontServer(I32 netId)
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_C2F_JOINGAME;

            // 发送数据
            ClientNetApplyManager::getInstance().sendFrontServerPacket( netId,dataPtr , 
                GameNetPacketData_INFO::headSize );
        }
        
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendCreateGenrealToFrontServer(I32 netId, PlayerCharacterData* pCharacterData )
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_C2F_CREATE_GENERAL;

            // 转换逻辑包
            PT_LOGIN_C2F_CREATE_GENERAL_DATA* sendData = (PT_LOGIN_C2F_CREATE_GENERAL_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
				wcscpy_s( sendData->name, pCharacterData->mName.length()+1, pCharacterData->mName.c_str() );
				wcscpy_s( sendData->charSurName, pCharacterData->charSurName.length()+1, pCharacterData->charSurName.c_str() );
				sendData->resID               = 1;
				sendData->charArtIcon         = pCharacterData->charArtIcon;

                // 发送数据
				sendData->resID = 1;
                ClientNetApplyManager::getInstance().sendFrontServerPacket( netId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_CREATE_GENERAL_DATA_INFO::dataSize );
            }
        }
            
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendToFrontServerExitgame(I32 netId)
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_C2F_ACC_LOGOUT;

            // 发送数据
            ClientNetApplyManager::getInstance().sendFrontServerPacket( netId,dataPtr , 
                GameNetPacketData_INFO::headSize );
        }
        
    }

    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientOpenCreateGenrealUIFromFrontServer( CClient* client )
    {
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendSelectClanToFrontServer(I32 netId, U64 clanid )
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_C2F_SELECT_CLAN;

            // 转换逻辑包
            PT_LOGIN_C2F_SELECT_CLAN_DATA* sendData = (PT_LOGIN_C2F_SELECT_CLAN_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->clandatabaseid = clanid;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( netId,dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_SELECT_CLAN_DATA_INFO::dataSize );
            }
        }

    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientSelectClanResultFromFrontServer( CClient* client, PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA* data )
    {
    }
}