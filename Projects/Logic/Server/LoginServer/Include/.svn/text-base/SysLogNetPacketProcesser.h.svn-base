/******************************************************************************/
#ifndef _H_SYSLOGNETPACKETPROCESSER_
#define _H_SYSLOGNETPACKETPROCESSER_
/******************************************************************************/
#include "SysLogNetPacket.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //帐号登入消息处理
    /******************************************************************************/
    class SysLogNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(SysLogNetPacketProcesser);

    public:
        //发送Account操作信息到SysLogServer
        void	sendAccountInfoToSysLogServer(I32 id, I32 clientNetId, Byte type, IdType accountID, U32 ip);

    };
}
#endif