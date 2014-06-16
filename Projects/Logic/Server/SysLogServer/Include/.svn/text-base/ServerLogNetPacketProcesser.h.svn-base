/******************************************************************************/
#ifndef _H_SERVERLOG_NETPACKETPROCESSER_
#define _H_SERVERLOG_NETPACKETPROCESSER_
/******************************************************************************/
#include "SysLogServerPreqs.h"
#include "SysLogNetPacket.h"
/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//服务器状态相关网络消息处理
	/******************************************************************************/
	class ServerLogNetPacketProcesser
	{
	public:
		SINGLETON_INSTANCE(ServerLogNetPacketProcesser);

		Bool	processSysLogServerPacket(I32 id,NetEventRecv* packet);

    private:
        void    recvPlayerLoginFromLoginS(I32, PT_SYSLOG_PLAYER_LOGIN_Data* pData);
		void    recvCharacterLoginFromFrontS(I32, PT_SYSLOG_CHARACTER_LOGIN_Data* pData);

	};
}
/******************************************************************************/
#endif
/******************************************************************************/