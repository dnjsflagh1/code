/******************************************************************************/
#ifndef _FRONTSERVERMAIN_H_
#define _FRONTSERVERMAIN_H_
/******************************************************************************/
#include "Singleton.h"
#include "ServerDllInterface.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//前端服务器管理
	/******************************************************************************/
	class FrontServerMain : public IServerDllInterface
	{
	public:
		SINGLETON_INSTANCE(FrontServerMain);
		FrontServerMain();
		virtual ~FrontServerMain();

		virtual Bool                initialize(ServerLauncherInterface* launcher);
		virtual Bool                unInitialize();

		ServerLauncherInterface*    getServerLauncher(){return mServerLauncher;}
        DBDriver*                   getDBDriver();
        Bool                        createDBTable();

		virtual void                onClientConnected(I32 id,NetAddress*address, INetConnect* connect);
		virtual void                onClientDisconnect(I32 id, INetConnect* connect);
		virtual void                onClientRecvPacket(I32 id,NetEventRecv* packet, INetConnect* connect);
		
		virtual void                onServerConnected(I32 id,GameNetType type, U32 serverId, U64 serverUniqueFlag, NetAddress*address);
		virtual void                onServerDisconnect(I32 id,NetAddress*address);
		virtual void                onServerRecvPacket(I32 id,NetEventRecv* packet);
        
		virtual void	            freeEvent(INetEvent* netEvent);

	protected:

        Bool                        loadFile();
        Str16                       getSettingFilePath();
 
    private:

		ServerLauncherInterface* mServerLauncher;
        LuaManager* mLuaMgr;

	};
}

/******************************************************************************/

#endif