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

        Bool	processFrontServerPacket(I32 id,NetEventRecv* packet);

        //���ͻ�����������
        void	sendCFBaseTestToFrontServer(U64 player_id,U64 character_id,U32 size);
        //���ͻ�����������
        void	sendCFMBaseTestToFrontServer(U64 player_id,U64 character_id,U32 size);

        //���յ������������ݷ���
        void	onRecvCFTestRespondFromFrontServer( I32 id, PT_TEST_FC_BASE_DATA* data);
        //���յ������������ݷ���
        void	onRecvCFMTestRespondFromFrontServer( I32 id, PT_TEST_MC_CFM_BASE_DATA* data);
    private:

        PT_TEST_CF_BASE_DATA mData;
        U64 mSendNum;
        U64 mRecvNum;
    };
}

#endif