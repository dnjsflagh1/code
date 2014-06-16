/******************************************************************************/
#include "stdafx.h"
#include "TestNetPacketProcesser.h"
#include "PlaceNetPacket.h"
#include "SPlayer.h"
#include "ServerManager.h"
#include "FrontServerMain.h"
#include "ClientManager.h"
#include "SWorldManager.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------
    TestNetPacketProcesser::TestNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    TestNetPacketProcesser::~TestNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    Bool TestNetPacketProcesser::processClientPacket( I32 id, NetEventRecv* packet )
    {
        if(packet->getChannel() == GNPC_TEST)
        {
			//FUNDETECTION(__MG_FUNC__);
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_TEST_CF_BASE:
                onRecvCFBaseFromClient(id, (PT_TEST_CF_BASE_DATA*)(data->data));
                break;
            case PT_TEST_CF_CFM_BASE:
                onRecvCFMBaseFromClient(id, (PT_TEST_CF_CFM_BASE_DATA*)(data->data));
                break;
            default:
                DYNAMIC_ASSERT(false);
                break;
            }
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::onRecvCFBaseFromClient( I32 netId, PT_TEST_CF_BASE_DATA* data)
    {
        // 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        FrontServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer( dataPtr, PT_TEST_CF_BASE_DATA_INFO::dataSize(data) + 24);


        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TEST;
            packet->type    = PT_TEST_FC_BASE;
			
		
			PT_TEST_FC_BASE_DATA* sendData = (PT_TEST_FC_BASE_DATA*)packet->data;
			if (sendData)
			{
				// 填充逻辑包
				sendData->data.character_Id = data->character_Id;
				sendData->data.num			= data->num;
				sendData->data.size			= data->size;
				sendData->data.player_id	= data->player_id;
				memcpy( sendData->data.data,data->data, data->size );

				// 发送数据
				SWorldManager::getInstance().boardcastNetPacketToAllClient( dataPtr,
					GameNetPacketData_INFO::headSize + PT_TEST_FC_BASE_DATA_INFO::dataSize(sendData) );
			}
           
        }
    }

    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::onRecvCFMBaseFromClient( I32 netId, PT_TEST_CF_CFM_BASE_DATA* data)
    {

		SPlayerPtr playerPtr;// = SWorldManager::getInstance().getGameObjectManager()->getPlayerByClientNetId(netId);
		if (playerPtr.isNull())
		{
			return;
		}
        SPlayerCharacter* playerCharacter;// = playerPtr->getPlayerCharacter(data->data.character_Id);
        if ( playerCharacter )
        {
            // 获得一个发送【服务端】缓存
			GameNetSendDataBufferPtr dataPtr;
            FrontServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer(dataPtr,PT_TEST_CF_CFM_BASE_DATA_INFO::dataSize(data) + 24 );

            // 转换成标准包格式
            GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
            if ( packet )
            {
                // 设置标签
                packet->channel = GNPC_TEST;
                packet->type    = PT_TEST_FM_CFM_BASE;

				PT_TEST_FM_CFM_BASE_DATA* sendData = (PT_TEST_FM_CFM_BASE_DATA*)packet->data;
			
				if (sendData)
				{
					// 填充数据
					sendData->data.character_Id = data->data.character_Id;
					sendData->data.num			= data->data.num;
					sendData->data.player_id	= data->data.player_id;
					sendData->data.size			= data->data.size;
					memcpy( sendData->data.data,data->data.data, data->data.size ); 

					// 发送数据
					ServerManager::getInstance().sendNetPacketToActiveMapServerByNetId( dataPtr,
						GameNetPacketData_INFO::headSize + PT_TEST_FM_CFM_BASE_DATA_INFO::dataSize(sendData) ,
						playerCharacter->getRegionId() );
				}
            }
        }
    }

}