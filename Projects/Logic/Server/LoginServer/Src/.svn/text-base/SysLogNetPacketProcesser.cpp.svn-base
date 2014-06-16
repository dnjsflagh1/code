/******************************************************************************/
#include "stdafx.h"
#include "SysLogNetPacketProcesser.h"
#include "LoginServerMain.h"
#include "ClientManager.h"
/******************************************************************************/
namespace MG
{
	//-----------------------------------------------------------------------------
    void SysLogNetPacketProcesser::sendAccountInfoToSysLogServer( I32 id, I32 clientNetId, Byte type, IdType accountID, U32 ip )
    {
		if (-1 == id) 
			return;
        
        // 获得一个发送【服务器】缓存
        GameNetSendDataBufferPtr dataPtr ;
        LoginServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_SYSLOG;
            packet->type    = PT_SYSLOG_PLAYER_LOGIN;

            // 转换逻辑包
            PT_SYSLOG_PLAYER_LOGIN_Data* sendData = (PT_SYSLOG_PLAYER_LOGIN_Data*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
				sendData->type = type;
                sendData->playerId = accountID;
				sendData->logTime = MGTimeOp::getCurrTimestamp();
				sendData->ipAddress = ip;

                // 发送数据
                //dataPtr->send( GameNetPacketData_INFO::headSize + PT_SYSLOG_ACCOUNT_OPERATE_DATA_INFO::dataSize , id );
				LoginServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_SYSLOG_PLAYER_LOGIN_DATA_INFO::dataSize ,
					id );
            }
        }
    }

}