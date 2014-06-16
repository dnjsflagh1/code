/******************************************************************************/
#include "stdafx.h"
#include "ServerManager.h"
#include "TestNetPacketProcesser.h"
#include "PlaceNetPacket.h"
#include "MapServerMain.h"
//#include "SPlayer.h"
#include "NetTranspondPacketProcesser.h"
//#include "SWorldManager.h"
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
    Bool TestNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
    {
        if(packet->getChannel() == GNPC_TEST)
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_TEST_FM_CFM_BASE:
                onRecvCFMBaseTestFromFrontServer(id, (PT_TEST_FM_CFM_BASE_DATA*)(data->data));
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
    void TestNetPacketProcesser::onRecvCFMBaseTestFromFrontServer(I32 id, PT_TEST_FM_CFM_BASE_DATA* data)
    {
	}


}