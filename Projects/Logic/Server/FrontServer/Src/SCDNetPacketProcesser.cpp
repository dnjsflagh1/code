//******************************************************************************************************
#include "stdafx.h"
#include "SCDNetPacketProcesser.h"
#include "FrontServerMain.h"
//******************************************************************************************************
namespace MG
{
	//------------------------------------------------------------------------------------------
    MG::Bool SCDNetPacketProcesser::processMapServerPacket( I32 id, NetEventRecv* packet )
    {
        return false;
    }

    //------------------------------------------------------------------------------------------
    void SCDNetPacketProcesser::sendClientCDList( I32 id, IdType masterId, CD_MASTER_TYPE masterType, CDTimer* pCDTimer )
    {
    }
}
