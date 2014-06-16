//******************************************************************************************************
#ifndef _H_SCD_PACKET_PROCESSER_
#define _H_SCD_PACKET_PROCESSER_
//******************************************************************************************************
#include "FrontServerPreqs.h"
#include "CDNetPacket.h"
//******************************************************************************************************
namespace MG
{
    class SCDNetPacketProcesser
    {
    public:
        SCDNetPacketProcesser(){;}
        ~SCDNetPacketProcesser(){;}
        SINGLETON_INSTANCE(SCDNetPacketProcesser);

    public:
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);
        //?

    public:
        void    sendClientCDList(I32 id, IdType masterId, CD_MASTER_TYPE masterType, CDTimer* pCDTimer);

    protected:
    private:
    };
}
//******************************************************************************************************
#endif
//******************************************************************************************************