/******************************************************************************/
#ifndef _LOGINNETPACKETPROCESSER_H_
#define _LOGINNETPACKETPROCESSER_H_
/******************************************************************************/

#include "NetAddress.h"
#include "GameNetPacket.h"
#include "LoginNetPacket.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //服务器登入消息处理
    /******************************************************************************/
    class LoginNetPacketProcesser
    {
    public:
        SINGLETON_INSTANCE(LoginNetPacketProcesser);

        Bool	processClientPacket(I32 id,NetEventRecv* packet);
        Bool	processServerPacket(I32 id,NetEventRecv* packet);

        //************************************************************

        //@{ Server
    public:
        //发送Server登入结果消息
        void	sendS2SLoginPacket(I32 id,Char16* name, U8 serverType,U64 serverUniqueFlag,U32 serverId, U32 code,Char8* serverVersion);
		void	sendLoginVersionErrorInfo(I32 id,Char16* name, Byte type,Char8* errorInfo,I32 errorInfoSize);
    protected:
        //当Server登入事件
        void	onRecvS2SLoginPacket(I32 id, PT_LOGIN_S2S_LOGIN_DATA* data);
		void	onRecvLoginErrorVersionInfo(I32 id,PT_SERVER_S2S_LOGIN_VERSION_ERROR_DATA* data);
        //@ }

        //************************************************************

        //@{ Client
    public:

    protected:
		void	printServerLoginLog(I32 id, Char16* name, U8 serverType, U64 serverUniqueFlag, U32 serverId,U32 code,Char8* serverVersion);

    };
}
#endif