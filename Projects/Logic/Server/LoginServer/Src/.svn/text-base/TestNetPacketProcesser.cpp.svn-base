/******************************************************************************/
#include "stdafx.h"
#include "TestNetPacketProcesser.h"
#include "LoginServerMain.h"
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
            case PT_TEST_CL_BASE:
                onRecvCLBaseFromClient(id, (PT_TEST_CL_BASE_DATA*)(data->data));
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
    void TestNetPacketProcesser::onRecvCLBaseFromClient( I32 netId, PT_TEST_CL_BASE_DATA* data)
    {

        ///////////////////////////////////////////////////////////////////////////

        // 获得一个发送【客户端】缓存
		GameNetSendDataBufferPtr dataPtr;
        LoginServerMain::getInstance().getServerLauncher()->getClientSendDataBuffer(dataPtr,PT_TEST_CL_BASE_DATA_INFO::dataSize(data) + 24 );


        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TEST;
            packet->type    = PT_TEST_LC_BASE;
			PT_TEST_LC_BASE_DATA* sendData = (PT_TEST_LC_BASE_DATA*)packet->data;

			if (sendData)
			{
				// 填充逻辑包
				sendData->data.size = data->size;
				memcpy( sendData->data.data, data->data, data->size );
			}
			

            // 发送数据
			//dataPtr->send( GameNetPacketData_INFO::headSize + PT_TEST_LC_BASE_DATA_INFO::dataSize(sendData) , netId );
			LoginServerMain::getInstance().getServerLauncher()->sendClient(dataPtr,
				GameNetPacketData_INFO::headSize + PT_TEST_LC_BASE_DATA_INFO::dataSize(sendData) ,
				netId);
        }

        ///////////////////////////////////////////////////////////////////////////

    }

}