/******************************************************************************/
#include "stdafx.h"
#include "TestNetPacket.h"
#include "TestNetPacketProcesser.h"
#include "ClientNetApplyManager.h"
//#include "ClientManager.h"
//#include "CSceneManager.h"
#include "CPlayer.h"
/******************************************************************************/
namespace MG
{
    //--------------------------------------------------------------------------
    TestNetPacketProcesser::TestNetPacketProcesser()
    {
        mSendNum = 0;
        mRecvNum = 0;
    }
    //--------------------------------------------------------------------------
    TestNetPacketProcesser::~TestNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    Bool TestNetPacketProcesser::processFrontServerPacket( CClient* client,NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_TEST )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
            switch (data->type)
            {
            case PT_TEST_FC_BASE:
                onRecvCFTestRespondFromFrontServer( client, (PT_TEST_FC_BASE_DATA*)data->data );
                break;
            case PT_TEST_MC_CFM_BASE:
                onRecvCFMTestRespondFromFrontServer( client, (PT_TEST_MC_CFM_BASE_DATA*)data->data );
                break;
            }
            return true;
        }
        return false;
    }

	//--------------------------------------------------------------------------
	Bool TestNetPacketProcesser::processLoginServerPacket( CClient* client,NetEventRecv* packet )
	{
		if ( packet->getChannel() == GNPC_TEST )
		{
			GameNetPacketData* data = (GameNetPacketData*)(packet->getData());
			switch (data->type)
			{
			case PT_TEST_LC_BASE:
				onRecvCLTestRespondFromLoginServer( client, (PT_TEST_LC_BASE_DATA*)data->data );
				break;
			}
			return true;
		}
		return false;
	}
    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::sendCFBaseTestToFrontServer(I32 frontServerId,U64 player_id,U64 character_id,U64& sendNum,I32 size)
    {
		// 获得一个发送【服务端】缓存
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer(size + PT_TEST_CF_BASE_DATA_INFO::headSize + 24);

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
				sendData->num = sendNum++;
				sendData->size = size;
				mSendNum++;
				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerId, dataPtr , 
					GameNetPacketData_INFO::headSize + PT_TEST_CF_BASE_DATA_INFO::dataSize(sendData) );
			}
		}
    }

    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::sendCFMBaseTestToFrontServer(I32 frontServerId,U64 player_id,U64 character_id,U64& sendNum,I32 size)
    {
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( size + 24);

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
				sendData->data.num = sendNum++;
				sendData->data.size = size;
				mSendNum++;
				// 发送数据
				ClientNetApplyManager::getInstance().sendFrontServerPacket(frontServerId, dataPtr , 
					GameNetPacketData_INFO::headSize + PT_TEST_CF_CFM_BASE_DATA_INFO::dataSize(sendData) );
			}
		}
	}
    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::onRecvCFTestRespondFromFrontServer( CClient* client, PT_TEST_FC_BASE_DATA* data)
    {
		//FUNDETECTION(__MG_FUNC__);
       /* if (data->player_id == client->getPlayerObj()->getAccountID() )
        {
            client->recvNumAdd(1);
        }else
        {
            UInt i = 0;
        }
		mRecvNum++;*/
    }

    //--------------------------------------------------------------------------
    void TestNetPacketProcesser::onRecvCFMTestRespondFromFrontServer( CClient* client, PT_TEST_MC_CFM_BASE_DATA* data)
    {
        //FUNDETECTION(__MG_FUNC__);
       /* if (data->player_id == client->getPlayerObj()->getAccountID() )
        {
            client->recvNumAdd(1);
        }else
        {
            UInt i = 0;
        }
		mRecvNum++;*/
    }

	//--------------------------------------------------------------------------
	void TestNetPacketProcesser::sendCLBaseTestToLoginServer(I32 loginServerId,I32 size)
	{
		GameNetSendDataBufferPtr dataPtr = ClientNetApplyManager::getInstance().getSendDataBuffer( size + 24);

		// 转换成标准包格式
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( packet )
		{
			// 设置标签
			packet->channel = GNPC_TEST;
			packet->type    = PT_TEST_CL_BASE;

			// 转换逻辑包
			PT_TEST_CL_BASE_DATA* sendData = (PT_TEST_CL_BASE_DATA*)(packet->data);
			if ( sendData )
			{
				// 填充逻辑包
				sendData->size = size;
				memset(sendData->data,1,size);
				std::string str;
				str += MGRandom::getInstance().rand_ab_One(1,1000);
				memcpy(sendData->data,str.c_str(),str.size());

				// 发送数据
				ClientNetApplyManager::getInstance().sendLoginServerPacket(loginServerId, dataPtr, 
					GameNetPacketData_INFO::headSize + PT_TEST_CL_BASE_DATA_INFO::dataSize(sendData));
				static U64 sendCount = 0;
				sendCount++;
				if (sendCount % 1000 == 1)
				{
					MG_LOG(out_game_logic,"发送数据次数 = %I64d------>md5 = %s\n",sendCount, MGMd5::md5Str(sendData->data,sendData->size).c_str());
				}
				
			}
		}
	}
	//--------------------------------------------------------------------------
	void TestNetPacketProcesser::onRecvCLTestRespondFromLoginServer( CClient* client, PT_TEST_LC_BASE_DATA* data )
	{
		/*static U64 recvCount = 0;
		recvCount++;
		if (recvCount % 1000 == 1)
		{
			MG_LOG(out_game_logic,"接收数据次数 = %I64d<------md5 = %s\n",recvCount,MGMd5::md5Str(data->data.data,data->data.size).c_str());
		}*/
	}
}
