/******************************************************************************/
#ifndef _TESTNETPACKETPROCESSER_H_
#define _TESTNETPACKETPROCESSER_H_
/******************************************************************************/

#include "TestNetPacket.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //测试消息处理
    /******************************************************************************/
    class TestNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(TestNetPacketProcesser);
        TestNetPacketProcesser();
        ~TestNetPacketProcesser();

        Bool	processClientPacket(I32 id, NetEventRecv* packet);

    public:

        void	onRecvCFBaseFromClient( I32 netId, PT_TEST_CF_BASE_DATA* data);
        void	onRecvCFMBaseFromClient( I32 netId, PT_TEST_CF_CFM_BASE_DATA* data);

    protected:


    };

}


#endif