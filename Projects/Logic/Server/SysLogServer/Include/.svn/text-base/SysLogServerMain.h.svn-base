
/******************************************************************************/
#ifndef _CENTERSERVERMAIN_H_
#define _CENTERSERVERMAIN_H_
/******************************************************************************/


#include "Singleton.h"
#include "ServerDllInterface.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//登入服务器管理
	/******************************************************************************/
	class SysLogServerMain : public IServerDllInterface
	{
	public:
		SINGLETON_INSTANCE(SysLogServerMain);
		SysLogServerMain();
		virtual ~SysLogServerMain();

		virtual Bool    initialize(ServerLauncherInterface* launcher);
		virtual void    update();
		virtual Bool    unInitialize();

		ServerLauncherInterface*    getServerLauncher(){return mServerLauncher;}

		virtual void    onClientConnected(I32 id,NetAddress*address, INetConnect* connect);
		virtual void    onClientDisconnect(I32 id, INetConnect* connect);
		virtual void    onClientRecvPacket(I32 id, NetEventRecv* packet,INetConnect* connect);

		virtual void    onServerConnected(I32 id,GameNetType type, U32 serverId, U64 serverUniqueFlag, NetAddress*address);
		virtual void    onServerDisconnect(I32 id,NetAddress*address);
		virtual void    onServerRecvPacket(I32 id,NetEventRecv* packet);

	protected:

		ServerLauncherInterface* mServerLauncher;
	};
}

/******************************************************************************/

#endif	//_CENTERSERVERMAIN_H_