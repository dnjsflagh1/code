/******************************************************************************/
#ifndef _DBSERVERMAIN_H_
#define _DBSERVERMAIN_H_
/******************************************************************************/
#include "Singleton.h"
#include "ServerDllInterface.h"
#include "LuaManager.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//前端服务器管理
	/******************************************************************************/
	class DbServerMain : public IServerDllInterface
	{
	public:
		SINGLETON_INSTANCE(DbServerMain);
		DbServerMain();
		virtual ~DbServerMain();

		virtual Bool    initialize(ServerLauncherInterface* launcher);
		virtual void    update();
		virtual Bool    unInitialize();

		ServerLauncherInterface*    getServerLauncher(){return mServerLauncher;}
        DBDriver*                   getDBDriver();

		virtual void    onClientConnected(I32 id,NetAddress*address);
		virtual void    onClientDisconnect(I32 id);
		virtual void    onClientRecvPacket(I32 id,NetEventRecv* packet);
		
		virtual void    onServerConnected(I32 id,GameNetType type, U32 serverId, U64 serverUniqueFlag, NetAddress*address);
		virtual void    onServerDisconnect(I32 id,NetAddress*address);
		virtual void    onServerRecvPacket(I32 id,NetEventRecv* packet);
        
	protected:
        //加载通用资源
        Bool            LoadFile();
        Bool            CreateTable();

        //管理相连服务器，比如MapServer LoginServer

    private:

		ServerLauncherInterface* mServerLauncher;
        LuaManager* mLuaMgr;
	};
}

/******************************************************************************/

#endif