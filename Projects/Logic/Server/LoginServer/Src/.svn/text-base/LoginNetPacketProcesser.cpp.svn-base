/******************************************************************************/
#include "stdafx.h"
#include "GameNetEvent.h"
#include "LoginServerMain.h"
#include "LoginNetPacketProcesser.h"
#include "LineUpNetPacketProcesser.h"
#include "VersionSwitch.h"
/******************************************************************************/
namespace MG
{

	//-----------------------------------------------------------------------
	Bool LoginNetPacketProcesser::processClientPacket(I32 id,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_LOGIN )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case PT_LOGIN_C2L_ACC_LOGIN:	
				onClientLogin(id,(PT_LOGIN_C2L_LOGIN_DATA*)data->data);
				break;
			}

			return true;
		}   
		return false;
	}

	//-----------------------------------------------------------------------
	Bool LoginNetPacketProcesser::processFrontServerPacket(I32 id,NetEventRecv* packet)
	{
		if ( packet->getChannel() == GNPC_LOGIN )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
				case PT_LOGIN_F2L_FRONT_SERVER_LOGIN:	
					onFrontServerLogin(id,(PT_LOGIN_F2L_LOGIN_DATA*)(data->data));
					break;
				case PT_LOGIN_F2L_CLIENT_LOGIN: 
					onClientLoginFrontServer(id,(PT_LOGIN_F2L_CLIENT_LOGIN_DATA*)data->data);
					break;
				case PT_LOGIN_F2L_CLIENT_LOGOUT: 
					onClientLogoutFrontServer((PT_LOGIN_F2L_CLIENT_LOGOUT_DATA*)data->data);
					break;
				case PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT:
					onCheckClientInFrontServerResult((PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA*)data->data);
			}
		
			return true;
		}
		return false;
	}
                                                                      
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::sendFrontServerLoginResult(I32 id, I8 result)
	{

        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr;
        LoginServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_L2F_LOGIN_FRONT_SERVER_RESULT;

            // 转换逻辑包
            PT_LOGIN_L2F_LOGIN_RESULT_DATA* sendData = (PT_LOGIN_L2F_LOGIN_RESULT_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
		        sendData->result = result;

                // 发送数据
                //dataPtr->send( GameNetPacketData_INFO::headSize + PT_LOGIN_L2F_LOGIN_RESULT_DATA_INFO::dataSize, id );
				LoginServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_L2F_LOGIN_RESULT_DATA_INFO::dataSize,
					id);
            }
        }
	}
		
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientLoginFrontServerResult(I32 id, I32 clientNetID, Char16* accName, Char16* accPsw, U64 accID, I8 result)
	{
        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr;
        LoginServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_L2F_CLIENT_CHECKED;

            // 转换逻辑包
            PT_LOGIN_L2F_CLIENT_CHECKED_DATA* sendData = (PT_LOGIN_L2F_CLIENT_CHECKED_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->result        = result;
                sendData->clientNetID   = clientNetID;
                sendData->accID	        = accID;
				MG_LOG(out_game_logic," sendClientLoginFrontServerResult accountid = %I64d\n", accID);
                WStrnCpyS(sendData->data.accName,accName,MAX_ACCOUNT_LONGIN_NAME_LEN);
                WStrnCpyS(sendData->data.accPsw,accPsw,MAX_ACCOUNT_LONGIN_PSW_LEN);

                // 发送数据
				LoginServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_L2F_CLIENT_CHECKED_DATA_INFO::dataSize,
					id );
            }
        }
	}

	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::onFrontServerLogin(I32 id, PT_LOGIN_F2L_LOGIN_DATA* data)
	{
		ServerManager::getInstance().addFrontServer(id,data->ip,data->port);

		//直接发回FrontServer
		sendFrontServerLoginResult(id);
	}
	
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::onClientLoginFrontServer(I32 id, PT_LOGIN_F2L_CLIENT_LOGIN_DATA* data)
	{
		LoginManager::getInstance().handleClientLoginFrontServer(id,data->clientNetIdInFrontServer, data->data.accName,data->data.accPsw);
	}

	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::onClientLogoutFrontServer(PT_LOGIN_F2L_CLIENT_LOGOUT_DATA* data)
	{
		LoginManager::getInstance().handleClientLogoutFrontServer(data->accName);
	}
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::onCheckClientInFrontServerResult( PT_LOGIN_F2L_CHECK_INFRONTSERVER_RESULT_DATA* data )
	{
		LoginManager::getInstance().handleCheckClientInFrontServerResult(data->clientNetIdInLoginServer,data->result);
	}
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::sendLoginErrorPacketToClient(I32 id, I8 errorResult)
	{
        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr ;
        LoginServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_L2C_ACC_LOGIN_FAIL;

            // 转换逻辑包
            PT_LOGIN_L2C_LOGIN_FAIL_DATA* sendData = (PT_LOGIN_L2C_LOGIN_FAIL_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
		        sendData->errResult = errorResult;

                // 发送数据
                //dataPtr->send( GameNetPacketData_INFO::headSize + PT_LOGIN_L2C_LOGIN_FAIL_DATA_INFO::dataSize, id );
				LoginServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_L2C_LOGIN_FAIL_DATA_INFO::dataSize,
					id );
            }
        }
	}

	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::sendLoginSuccessPacketToClient(I32 id, CChar* ip, I32 port)
	{
        // 获得一个发送【客户端】缓存
        GameNetSendDataBufferPtr dataPtr ;
        LoginServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_LOGIN;
            packet->type    = PT_LOGIN_L2C_ACC_LOGIN_SUCCESS;

            // 转换逻辑包
            PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* sendData = (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                StrnCpyS(sendData->ip,ip,MG_NET_MAX_IP_LEN);
                sendData->port = port;

                // 发送数据
				LoginServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_L2C_LOGIN_SUCCESS_DATA_INFO::dataSize,
					id);
            }
        }
	}

	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::onClientLogin(I32 id, PT_LOGIN_C2L_LOGIN_DATA* data)
	{
		MG_LOG(out_info,"当客户端登录\n");
		// 客户端版本检测
		if (StrCmp(data->clientVersionNum,CLIENT_VERSION_NUMBER))
		{
			//版本检测失败
			Char8 desc[256] = {0};
			MGStrOp::sprintf(desc,256,"版本验证错误，当前客户端版本为%s，最新版本为%s",data->clientVersionNum,CLIENT_VERSION_NUMBER);
			sendClientLoginErrVersionInfo(id,desc,StrLen(desc));
			return;

		}
		LoginManager::getInstance().handleClientLogin(id, data->accName, data->accPsw);
	}
	
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::sendCheckClientInFrontServer(I32 frontServerId, I32 clientNetIdInFs, I32 clientNetIdInLs)
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        LoginServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_LOGIN_L2F_CHECK_INFRONTSERVER;

			// 转换逻辑包
			PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA* sendData = (PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->clientNetIdInFrontServer = clientNetIdInFs;
				sendData->clientNetIdInLoginServer = clientNetIdInLs;
				// 发送数据
				//dataPtr->send( GameNetPacketData_INFO::headSize + PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO::dataSize, frontServerId );
				LoginServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO::dataSize,
					frontServerId );
			}
		}
	}
    //-----------------------------------------------------------------------
	/*void LoginNetPacketProcesser::sendFrontServerKickoutClient( I32 frontServerId,I32 clientNetIdInFs )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr = LoginServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT;

			// 转换逻辑包
			PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA* sendData = (PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->clientNetIdInFs = clientNetIdInFs;
				// 发送数据
				//dataPtr->send( GameNetPacketData_INFO::headSize + PT_LOGIN_L2F_CHECK_INFRONTSERVER_DATA_INFO::dataSize, frontServerId );
				LoginServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_LOGIN_L2F_LOGIN_FRONT_KICKOUT_CLIENT_DATA_INFO::dataSize,
					frontServerId );
			}
		}
	}
*/
	//-----------------------------------------------------------------------
	void LoginNetPacketProcesser::sendClientLoginErrVersionInfo( I32 id,Char8* errorInfo,I32 errorInfoSize )
	{
		// 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr ;
        LoginServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr );

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_LOGIN;
			packet->type    = PT_SERVER_S2C_LOGIN_VERSION_ERROR;

			// 转换逻辑包
			PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA* sendData = (PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA*)(packet->data);
			if ( sendData )
			{
				sendData->dataSize = errorInfoSize + 1;
				sendData->errorInfo[errorInfoSize] = 0;
				MGStrOp::sprintf(sendData->errorInfo,errorInfoSize,errorInfo);
				// 发送数据
				LoginServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + PT_SERVER_S2C_LOGIN_VERSION_ERROR_DATA_INFO::dataSize(sendData),
					id);
			}
		}
	}

	

}
