/******************************************************************************/
#ifndef _SWORLDNETPACKETPROCESSER_H_
#define _SWORLDNETPACKETPROCESSER_H_
/******************************************************************************/

#include "MapServerPreqs.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //世界相关网络消息处理
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

        //一些具体处理包方法

        //一些具体发送包方法

    };

}


#endif