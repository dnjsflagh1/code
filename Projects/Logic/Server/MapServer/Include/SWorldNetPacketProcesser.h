/******************************************************************************/
#ifndef _SWORLDNETPACKETPROCESSER_H_
#define _SWORLDNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //�������������Ϣ����
    /******************************************************************************/
    class SWorldNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(SWorldNetPacketProcesser);
        SWorldNetPacketProcesser();
        ~SWorldNetPacketProcesser();

        Bool	processFrontServerPacket(I32 id, NetEventRecv* packet);
        Bool	processMapServerPacket(I32 id, NetEventRecv* packet);
		
    public:

        //һЩ���崦�������

        //һЩ���巢�Ͱ�����

    };

}


#endif