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
        
        // ���һ�����͡�������������
        GameNetSendDataBufferPtr dataPtr ;
        LoginServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        // ת���ɱ�׼����ʽ
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // ���ñ�ǩ
            packet->channel = GNPC_SYSLOG;
            packet->type    = PT_SYSLOG_PLAYER_LOGIN;

            // ת���߼���
            PT_SYSLOG_PLAYER_LOGIN_Data* sendData = (PT_SYSLOG_PLAYER_LOGIN_Data*)(packet->data);
            if ( sendData )
            {
                // ����߼���
				sendData->type = type;
                sendData->playerId = accountID;
				sendData->logTime = MGTimeOp::getCurrTimestamp();
				sendData->ipAddress = ip;

                // ��������
                //dataPtr->send( GameNetPacketData_INFO::headSize + PT_SYSLOG_ACCOUNT_OPERATE_DATA_INFO::dataSize , id );
				LoginServerMain::getInstance().getServerLauncher()->sendServer(dataPtr,
					GameNetPacketData_INFO::headSize + PT_SYSLOG_PLAYER_LOGIN_DATA_INFO::dataSize ,
					id );
            }
        }
    }

}