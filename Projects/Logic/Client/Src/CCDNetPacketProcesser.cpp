//******************************************************************************************************
#include "stdafx.h"
#include "CCDNetPacketProcesser.h"      
#include "CCDManager.h"
//******************************************************************************************************
namespace MG
{
    MG::Bool CCDNetPacketProcesser::processServerPacket( I32 id, NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_CD )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_CD_F2C_CDLIST:
                recvCDList( id, (PT_CD_F2C_CDLIST_DATA*)data->data );
                break;
            }
            return true;
        }
        return false;
    }
    //-------------------------------------------------------------------------------------------
    void CCDNetPacketProcesser::recvCDList( I32 id, PT_CD_F2C_CDLIST_DATA* pData )
    {
        for (U32 i=0; i<pData->cdNum; i++)
        {
            CCDManager::getInstance().addCD(
				(CD_MASTER_TYPE)pData->masterType, 
				pData->masterID, 
				pData->cddata[i].cdId, 
				pData->cddata[i].cdLiveTime, 
				pData->cddata[i].cdTotalTime
				);
        }
    }
}