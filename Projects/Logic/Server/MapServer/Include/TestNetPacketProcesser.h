/******************************************************************************/
#ifndef _TESTNETPACKETPROCESSER_H_
#define _TESTNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "GameNetPacket.h"
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

        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);

        void	onRecvCFMBaseTestFromFrontServer(I32 id, PT_TEST_FM_CFM_BASE_DATA* data);

    protected:

    };

}


#endif