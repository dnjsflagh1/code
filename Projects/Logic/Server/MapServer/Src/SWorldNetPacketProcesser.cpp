/******************************************************************************/
#include "stdafx.h"
#include "SWorldNetPacketProcesser.h"
/******************************************************************************/

namespace MG
{
    //--------------------------------------------------------------------------
    SWorldNetPacketProcesser::SWorldNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    SWorldNetPacketProcesser::~SWorldNetPacketProcesser()
    {

    }

    //--------------------------------------------------------------------------
    Bool SWorldNetPacketProcesser::processFrontServerPacket(I32 id, NetEventRecv* packet)
    {

        return false;
    }

    //--------------------------------------------------------------------------
    Bool SWorldNetPacketProcesser::processMapServerPacket(I32 id, NetEventRecv* packet)
    {

        return false;
    }

}