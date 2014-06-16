/******************************************************************************/
#ifndef _GMSERVERMAIN_H_
#define _GMSERVERMAIN_H_
/******************************************************************************/

#include "Singleton.h"
#include "ServerDllInterface.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //登入服务器管理
    /******************************************************************************/
    class GMServerMain : public IServerDllInterface
    {
    public:
        SINGLETON_INSTANCE(GMServerMain);
        GMServerMain();
        virtual ~GMServerMain();

        virtual Bool    initialize(ServerLauncherInterface* launcher);
        virtual void    update();
        virtual Bool    unInitialize();
        
        ServerLauncherInterface*    getServerLauncher(){return mServerLauncher;}

        virtual void    onClientConnected(I32 id,NetAddress*address) ;
        virtual void    onClientDisconnect(I32 id) ;
        virtual void    onClientRecvPacket(I32 id,NetEventRecv* packet) ;
		
		virtual void    onServerConnected(I32 id,GameNetType type, U32 serverId, U64 serverUniqueFlag, NetAddress*address);
        virtual void    onServerDisconnect(I32 id,NetAddress*address) ;
        virtual void    onServerRecvPacket(I32 id,NetEventRecv* packet) ;

		virtual void	freeEvent(INetEvent* netEvent);

    protected:

        ServerLauncherInterface* mServerLauncher;
    };
}

/******************************************************************************/

#endif