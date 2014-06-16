//*************************************************************************************
#ifndef _TESTNETPACKETPROCESSER_H_
#define _TESTNETPACKETPROCESSER_H_
//*************************************************************************************
#include "ClientPreqs.h"
#include "TestNetPacket.h"
#include "GameNetEvent.h"
//*************************************************************************************
namespace MG
{
    class TestNetPacketProcesser
    {
    public:
        TestNetPacketProcesser();
        ~TestNetPacketProcesser();
        SINGLETON_INSTANCE(TestNetPacketProcesser)

        Bool	processFrontServerPacket(CClient* client,NetEventRecv* packet);
		Bool	processLoginServerPacket(CClient* client,NetEventRecv* packet);
        //发送基础测试数据
        void	sendCFBaseTestToFrontServer(I32 frontServerId, U64 player_id,U64 character_id,U64& sendNum,I32 size);
        //发送基础测试数据
        void	sendCFMBaseTestToFrontServer(I32 frontServerId,U64 player_id,U64 character_id,U64& sendNum,I32 size);

        //当收到基础测试数据反馈
        void	onRecvCFTestRespondFromFrontServer(CClient* client, PT_TEST_FC_BASE_DATA* data);
        //当收到基础测试数据反馈
        void	onRecvCFMTestRespondFromFrontServer( CClient* client, PT_TEST_MC_CFM_BASE_DATA* data);


		void	sendCLBaseTestToLoginServer(I32 loginServerId,I32 size);
		void	onRecvCLTestRespondFromLoginServer(CClient* client, PT_TEST_LC_BASE_DATA* data);
    private:

       /* PT_TEST_BASE_DATA mData;*/
        U64 mSendNum;
        U64 mRecvNum;
    };
}

#endif