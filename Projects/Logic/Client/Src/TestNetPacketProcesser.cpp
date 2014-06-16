/******************************************************************************/
#include "stdafx.h"
#include "TestNetPacket.h"
#include "TestNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
#include "CSceneManager.h"
#include "CPlayer.h"
/******************************************************************************/
namespace MG
{
    //--------------------------------------------------------------------------
    TestNetPacketProcesser::TestNetPacketProcesser()
    {
        mSendNum = 0;
        mRecvNum = 0;

        mData.num = 0;
    }
    //--------------------------------------------------------------------------
    TestNetPacketProcesser::~TestNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    Bool TestNetPacketProcesser::processFrontServerPacket( I32 id,NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_TEST )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_TEST_FC_BASE:
                onRecvCFTestRespondFromFrontServer( id, (PT_TEST_FC_BASE_DATA*)data->data );
                break;
            case PT_TEST_MC_CFM_BASE:
                onRecvCFMTestRespondFromFrontServer( id, (PT_TEST_MC_CFM_BASE_DATA*)data->data );
                break;
            }
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::sendCFBaseTestToFrontServer(U64 player_id,U64 character_id,U32 size)
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TEST;
            packet->type    = PT_TEST_CF_BASE;

            // 转换逻辑包
            PT_TEST_CF_BASE_DATA* sendData = (PT_TEST_CF_BASE_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->player_id = player_id;
                sendData->character_Id = character_id;
                sendData->num = mSendNum++;
				sendData->size = size;

                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_TEST_CF_BASE_DATA_INFO::dataSize(sendData) );
            }
        }

           
    }

    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::sendCFMBaseTestToFrontServer(U64 player_id,U64 character_id,U32 size)
    {
        // 获得一个发送【服务端】缓存
        GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( );

        // 转换成标准包格式
        GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
        if ( packet )
        {
            // 设置标签
            packet->channel = GNPC_TEST;
            packet->type    = PT_TEST_CF_CFM_BASE;

            // 转换逻辑包
            PT_TEST_CF_CFM_BASE_DATA* sendData = (PT_TEST_CF_CFM_BASE_DATA*)(packet->data);
            if ( sendData )
            {
                // 填充逻辑包
                sendData->data.player_id = player_id;
                sendData->data.character_Id = character_id;
                sendData->data.num = mSendNum++;
				sendData->data.size = size;
                // 发送数据
                ClientNetApplyManager::getInstance().sendFrontServerPacket( dataPtr , 
                    GameNetPacketData_INFO::headSize + PT_TEST_CF_CFM_BASE_DATA_INFO::dataSize(sendData) );
            }
        }
           
    }

    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::onRecvCFTestRespondFromFrontServer( I32 id, PT_TEST_FC_BASE_DATA* data)
    {
		//FUNDETECTION(__MG_FUNC__);
        if (data->data.player_id == mData.player_id )
        {
            mRecvNum++;
        }else
        {
            UInt i = 0;
        }
    }

    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::onRecvCFMTestRespondFromFrontServer( I32 id, PT_TEST_MC_CFM_BASE_DATA* data)
    {
        //FUNDETECTION(__MG_FUNC__);
        if (data->data.player_id == mData.player_id )
        {
            mRecvNum++;
        }else
        {
            UInt i = 0;
        }
    }
}
