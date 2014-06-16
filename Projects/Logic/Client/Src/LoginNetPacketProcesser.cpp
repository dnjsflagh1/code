/******************************************************************************/
#include "stdafx.h"
#include "ClientNetApplyManager.h"
#include "LoginNetPacketProcesser.h"
#include "LoginManager.h"
#include "CPlayer.h"

#include "PlayerCharacterData.h"
#include "VersionSwitch.h"
#include "GameMain.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------------
	Bool LoginNetPacketProcesser::processLoginServerPacket( I32 id, NetEventRecv* packet )
	{
        if ( packet->getChannel() == GNPC_LOGIN )
        {   
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_LOGIN_L2C_ACC_LOGIN_FAIL:
                onClientLoginFailedFromLoginServer( id , (PT_LOGIN_L2C_LOGIN_FAIL_DATA*)data->data);
                break;
            case PT_LOGIN_L2C_ACC_LOGIN_SUCCESS:	
                onClientLoginSuccessedFromLoginServer( id , (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA*)data->data);
                break;
			/*case PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO:
				onClientLoginQueueInfoFromLoginServer(id,(PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA*)data->data);
				break;*/
			case PT_SERVER_S2C_LOGIN_VERSION_ERROR:
				onRecvLoginVersionError(id,(PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA*)data->data);
            }
            return true;
        }

		return false;
	}
    
	//-----------------------------------------------------------------------------
	Bool LoginNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
	{
        if ( packet->getChannel() == GNPC_LOGIN )
        {   
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_LOGIN_F2C_ACC_LOGIN_RESULT:
                onRecvClientLoginResultFromFrontServer( id , (PT_LOGIN_F2C_LOGIN_RESULT_DATA*)data->data );
                break;
            case PT_LOGIN_F2C_OPEN_CREATECLANUI:
                onRecvClientOpenCreateClanUIFromFrontServer( id );
                break;
			case  PT_LOGIN_F2C_CLAN_DATA:
				onRecvClientClanInfoFromFrontServer(id,(PT_LOGIN_F2C_CLAN_DATA_DATA*)data->data);
				break;
            case PT_LOGIN_F2C_OPEN_CLANCONTROLUI:
                onRecvClientOpenClanControlUIFromFrontServer( id);
                break;
            case PT_LOGIN_F2C_CREATE_CLAN_RESULT:
                onRecvClientCreateClanResultFromFrontServer( id, (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA*)data->data );
                break;
            case PT_LOGIN_F2C_DELETE_CLAN_RESULT:
                onRecvClientDeleteClanResultFromFrontServer( id, (PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA*)data->data );
                break;
            case PT_LOGIN_F2C_OPENCRETEGENREALUI:
                onRecvClientOpenCreateGenrealUIFromFrontServer( id );
                break;
            case PT_LOGIN_F2C_CREATE_GENERAL_RESULT:
                onRecvClientCreateGenrealResultFromFrontServer( id, (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA*)data->data );
                break;
            /*case PT_LOGIN_F2C_SELECT_CLAN_RESULT:
                onRecvClientSelectClanResultFromFrontServer(id, (PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA*)data->data);
                break;*/
		
			/*case PT_LOGIN_F2C_ACC_LOGIN_QUEUE_INFO:
				onClientLoginQueueInfoFromFrontServer(id,(PT_LOGIN_F2C_ACC_LOGIN_QUEUE_INFO_DATA*)data->data);
				break;*/

            }
            return true;
        }
      
		return false;
	}

	//-----------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendLoginPacketToLoginServer(CChar16* name, CChar16* password,Char8* clientVersion)
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
                ClientNetApplyManager::getInstance().sendLoginServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2L_LOGIN_DATA_INFO::dataSize );
            }
        }
	}

    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onClientLoginFailedFromLoginServer( I32 id , PT_LOGIN_L2C_LOGIN_FAIL_DATA* data )
    {
		//FUNDETECTION(__MG_FUNC__);
        LoginManager::getInstance().onLoginToLoginServerFailed( data->errResult );
    }

    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onClientLoginSuccessedFromLoginServer( I32 id , PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* data )
    { 
		//FUNDETECTION(__MG_FUNC__);
        LoginManager::getInstance().onLoginToLoginServerSuccessed( data->ip, data->port );
    }

	//-----------------------------------------------------------------------------
	void LoginNetPacketProcesser::onRecvLoginVersionError( I32 id , PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA* data )
	{
		MG::MsgBox::show(data->errorInfo,"版本错误");

		GameMain::getInstance().stopAndRestore();
	}

	//-----------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendLoginPacketToFrontServer(CChar16* name, CChar16* password)
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

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_LOGIN_DATA_INFO::dataSize );
            }
        }
	}

	//-----------------------------------------------------------------------------
	void LoginNetPacketProcesser::sendSelectCharacterPacketToFrontServer(UInt id)
	{
		/*PT_ACC_C2F_SELECT_CHARACTER_DATA data;
		data.characterId = id;
		ClientNetApplyManager::getInstance().sendFrontServerPacket(GNPC_LOGIN,PT_ACC_C2F_SELECT_CHARACTER,(Char*)&data,sizeof(data));*/
	}

    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientLoginResultFromFrontServer( I32 id , PT_LOGIN_F2C_LOGIN_RESULT_DATA* data )
    {
		//FUNDETECTION(__MG_FUNC__);
        LoginManager::getInstance().onRecvLoginToFrontServerResult( data->result,id );
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendClanInfoToFrontServer(  CClan* pClan  )
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
                wcscpy_s( sendData->clanhomelandname, pClan->getClanHomeLandName().length()+1, pClan->getClanHomeLandName().c_str() );
                wcscpy_s( sendData->clanname, pClan->getName().length()+1, pClan->getName().c_str() );
                sendData->ConstellationId = 0;
                sendData->armyemblem = 0;
                sendData->armyemblemcolor = 0;
                sendData->bg = 0;
                sendData->bgcolor = 0;
				sendData->accountid = CPlayer::getInstance().getAccountID();

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_CREATE_CLAN_DATA_INFO::dataSize );
            }
        }

    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendDeleteClanToFrontServer( ClanIdType clanid )
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
				sendData->accountId		 = CPlayer::getInstance().getAccountID();

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_DELETE_CLAN_DATA_INFO::dataSize );
            }
        }
    
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientOpenCreateClanUIFromFrontServer( I32 id )
    {
		//FUNDETECTION(__MG_FUNC__);
        LoginManager::getInstance().openClanCreateUI();
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientOpenClanControlUIFromFrontServer( I32 id)
    {      
        LoginManager::getInstance().openClanControlUI();
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientCreateClanResultFromFrontServer( I32 id, PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* data )
    {
        LoginManager::getInstance().handleCreateClanResult( data->result );
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientDeleteClanResultFromFrontServer( I32 id, PT_LOGIN_F2C_DELETE_CLAN_RESULT_DATA* data )
    {
        LoginManager::getInstance().handleClanDeleteResult(data->result);
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientCreateGenrealResultFromFrontServer( I32 id, PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* data )
    {
        //LoginManager::getInstance().handleCreateGenrealResult(data->result, data->isGenreal, data->genrealID);
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendJoingameToFrontServer()
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
            ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                GameNetPacketData_INFO::headSize );
        }
        
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendCreateGenrealToFrontServer(U32 resID, PlayerCharacterData* pCharacterData )
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
				sendData->resID         = resID;
				sendData->charArtIcon   = pCharacterData->charArtIcon;
				sendData->accountId		= CPlayer::getInstance().getAccountID();
                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_CREATE_GENERAL_DATA_INFO::dataSize );
            }
        }
            
    }
    //-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::sendToFrontServerExitgame()
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
            ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                GameNetPacketData_INFO::headSize );
        }
        
    }
	//-----------------------------------------------------------------------------
	//void LoginNetPacketProcesser::onClientLoginQueueInfoFromLoginServer( I32 id , PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA* data )
	//{
	//	LoginManager::getInstance().handleClientLoginQueueInfo(data->type,data->waitCount);
	//}
	////-----------------------------------------------------------------------------
	//void LoginNetPacketProcesser::onClientLoginQueueInfoFromFrontServer( I32 id , PT_LOGIN_F2C_ACC_LOGIN_QUEUE_INFO_DATA* data )
	//{
	//	LoginManager::getInstance().handleClientLoginQueueInfo(data->type,data->waitCount);
	//}
	//-----------------------------------------------------------------------------
    void LoginNetPacketProcesser::onRecvClientOpenCreateGenrealUIFromFrontServer( I32 id )
    {
        LoginManager::getInstance().openGenrealCreateUI();
    }
    //-----------------------------------------------------------------------------
    //void LoginNetPacketProcesser::sendSelectClanToFrontServer( U64 clanid )
    //{
    //    // 获得一个发送【服务端】缓存
    //    GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

    //    // 转换成标准包格式
    //    GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
    //    if ( packet )
    //    {
    //        // 设置标签
    //        packet->channel = GNPC_LOGIN;
    //        packet->type    = PT_LOGIN_C2F_SELECT_CLAN;

    //        // 转换逻辑包
    //        PT_LOGIN_C2F_SELECT_CLAN_DATA* sendData = (PT_LOGIN_C2F_SELECT_CLAN_DATA*)(packet->data);
    //        if ( sendData )
    //        {
    //            // 填充逻辑包
    //            sendData->clandatabaseid = clanid;

    //            // 发送数据
    //            ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
    //                GameNetPacketData_INFO::headSize + PT_LOGIN_C2F_SELECT_CLAN_DATA_INFO::dataSize );
    //        }
    //    }

    //}
    //-----------------------------------------------------------------------------
//     void LoginNetPacketProcesser::onRecvClientSelectClanResultFromFrontServer( I32 id, PT_LOGIN_F2C_SELECT_CLAN_RESULT_DATA* data )
//     {
//         LoginManager::getInstance().handleSelectClanResult(data->result);
//     }

	void LoginNetPacketProcesser::onRecvClientClanInfoFromFrontServer( I32 id, PT_LOGIN_F2C_CLAN_DATA_DATA* data )
	{
		ClanData clanData;

		clanData.clanId            = data->clandatabaseid;
		clanData.accountId         = data->accountId;
		//clanData.status            = data->status;
		clanData.clanHomeLandName  = data->clanhomelandname;
		clanData.clanName          = data->clanname;
		//clanData.ancestry          = data->ConstellationId;
		clanData.armyemblem        = data->armyemblem;
		clanData.armyemblemcolor   = data->armyemblemcolor;
		clanData.bg                = data->bg;
		clanData.bgcolor           = data->bgcolor;
		clanData.mainGenrealId     = data->mainGenrealId;
		clanData.wiseGenrealId	   = data->wiseGenrealId;
		clanData.commanderGenrealId= data->commanderGenrealId;
		clanData.curGenrealId	   = data->curGenrealId;
		clanData.clanbagSize       = data->clanbagsize;
		clanData.regionID          = data->regionID;
		clanData.clanLevel		   = data->clanLevel;
		memcpy((void*)clanData.clanExp, (void*)data->clanExp, sizeof(data->clanExp));
		memcpy((void*)clanData.clanMoney, (void*)data->clanMoney, sizeof(data->clanMoney));

		CPlayer::getInstance().setAccountID(data->accountId);
		CPlayer::getInstance().addClan(&clanData);
		CPlayer::getInstance().setActive(clanData.clanId);
	}
}