/******************************************************************************/
#include "stdafx.h"
#include "GMServerManagerMain.h"
#include "GMAccountNetPacketProcesser.h"
#include "GMClientManager.h"
#include "VersionSwitch.h"
/******************************************************************************/

namespace MG
{
    //--------------------------------------------------------------------------
    GMAccountNetPacketProcesser::GMAccountNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    GMAccountNetPacketProcesser::~GMAccountNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    Bool GMAccountNetPacketProcesser::processGMClientPacket(I32 id, NetEventRecv* packet)
    {
        if (packet->getChannel() == GNPC_GM_ACCOUNT)
        {
			//FUNDETECTION(__MG_FUNC__);
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

			switch (data->type)
			{
			case GMPT_CGMM_ACC_LOGIN:	
				onGMClientLogin( id , (GMPT_CGMM_ACC_LOGIN_DATA*)data->data);
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
	void GMAccountNetPacketProcesser::sendGMClientLoginResult( I32 id, Byte result,Int authority)
	{
        ///////////////////////////////////////////////////////////////////////////

        // 获得一个发送【服务端】缓存
        
        GameNetSendDataBufferPtr dataPtr;
		GMServerManagerMain::getInstance().getServerLauncher()->getClientSendDataBuffer(dataPtr);

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_GM_ACCOUNT;
            packet->type    = GMPT_GMMC_ACC_LOGIN_RESULT;

            // 转换逻辑包
            GMPT_GMMC_ACC_LOGIN_RESULT_DATA* sendData = (GMPT_GMMC_ACC_LOGIN_RESULT_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->authority = authority;
				sendData->result = result;

                // 发送数据
				GMServerManagerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
					GameNetPacketData_INFO::headSize + GMPT_GMMC_ACC_LOGIN_RESULT_DATA_INFO::dataSize,id);
            }
        }

        ///////////////////////////////////////////////////////////////////////////
    
    }
	//--------------------------------------------------------------------------
	void GMAccountNetPacketProcesser::onGMClientLogin( I32 id, GMPT_CGMM_ACC_LOGIN_DATA* data )
	{
		if (StrCmp(data->clientVersionNum,CLIENT_VERSION_NUMBER))
		{
			sendGMClientLoginResult(id,gaor_err_version,0);
		}
		GMClientManager::getInstance().onGMClientLoginIn(id,data->accName,data->accPsw);
	}

}