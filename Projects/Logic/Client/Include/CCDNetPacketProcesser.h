//******************************************************************************************************
#ifndef _H_CCD_PACKET_PROCESSER_
#define _H_CCD_PACKET_PROCESSER_
//******************************************************************************************************
#include "ClientPreqs.h"
#include "CDNetPacket.h"
#include "GameNetEvent.h"
//******************************************************************************************************
namespace MG
{
    class CCDNetPacketProcesser
    {
    public:
        CCDNetPacketProcesser(){;}
        ~CCDNetPacketProcesser(){;}
        SINGLETON_INSTANCE(CCDNetPacketProcesser);

    public:
        Bool	processServerPacket(I32 id, NetEventRecv* packet);
        //?

    private:
        void    recvCDList(I32 id, PT_CD_F2C_CDLIST_DATA* pData);

    protected:
    private:
    };
}
//******************************************************************************************************
#endif
//******************************************************************************************************