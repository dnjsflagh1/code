/******************************************************************************/
#include "stdafx.h"
#include "GMAccountOpNetPacketProcesser.h"
#include "VersionSwitch.h"
#include "ClientNetApplyManager.h"
#include "ThreadStatusEventManager.h"
#include "GMManager.h"
#include "GMCommonData.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------
	Bool GMAccountOpNetPacketProcesser::processGMServerManagerPacket( I32 id, NetEventRecv* packet )
	{
        if ( packet->getChannel() == GNPC_GM_ACCOUNT )
        {   
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case GMPT_GMMC_ACC_LOGIN_RESULT:
				onGMLoginResultFromLoginServer(id,(GMPT_GMMC_ACC_LOGIN_RESULT_DATA*)data->data);
				break;
             break;
            }
            return true;
        }

		return false;
	}
    //-----------------------------------------------------------------------------
	void GMAccountOpNetPacketProcesser::sendLoginPacketToGMServerManager( CChar16* name, CChar16* password,Char8* clientVersion )
	{
		// ���һ�����͡�����ˡ�����
		NetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

		// ת���ɱ�׼����ʽ
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getData();
		if ( packet )
		{
			// ���ñ�ǩ
			packet->channel = GNPC_GM_ACCOUNT;
			packet->type    = GMPT_CGMM_ACC_LOGIN;

			// ת���߼���
			GMPT_CGMM_ACC_LOGIN_DATA* sendData = (GMPT_CGMM_ACC_LOGIN_DATA*)(packet->data);
			if ( sendData )
			{
				// ����߼���
				MGStrOp::sprintf(sendData->accName,MAX_ACCOUNT_LONGIN_NAME_LEN,L"%s",(Char*)name);
				MGStrOp::sprintf(sendData->accPsw,MAX_ACCOUNT_LONGIN_PSW_LEN,L"%s",(Char*)password);
				MGStrOp::sprintf(sendData->clientVersionNum,MAX_VERSION_NUM_LEN,"%s",CLIENT_VERSION_NUMBER);
				// ��������
				ClientNetApplyManager::getInstance().sendPacket( dataPtr , 
					GameNetPacketData_INFO::headSize + GMPT_CGMM_ACC_LOGIN_DATA_INFO::dataSize );
			}
		}
	}
	//-----------------------------------------------------------------------------
	void GMAccountOpNetPacketProcesser::onGMLoginResultFromLoginServer( I32 id , GMPT_GMMC_ACC_LOGIN_RESULT_DATA* data )
	{
		if (ThreadStatusEventManager::getInstance().hasDirty("GM_LOGIN",false))
		{
			GMClientInfo* clientInfo = GMManager::getInstance().mLoginData;
			clientInfo->authority = data->authority;
			clientInfo->isOnline = true;
			clientInfo->netId = id;
			clientInfo->gmId = data->gmId;
			 GMManager::getInstance().setCreateGMResult((gm_account_operate_result)data->result);
			 ThreadStatusEventManager::getInstance().clearDirty("GM_LOGIN");
		}
			
	}
}