/******************************************************************************/
#ifndef _TESTNETPACKETPROCESSER_H_
#define _TESTNETPACKETPROCESSER_H_
/******************************************************************************/

#include "TestNetPacket.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //������Ϣ����
    /******************************************************************************/
    class TestNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(TestNetPacketProcesser);
        TestNetPacketProcesser();
        ~TestNetPacketProcesser();

        Bool	processClientPacket(I32 id, NetEventRecv* packet);

    public:
        void	onRecvCLBaseFromClient( I32 netId, PT_TEST_CL_BASE_DATA* data);

    protected:


    };

}


#endif