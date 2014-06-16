/******************************************************************************/
#ifndef _MAPSERVERMAIN_H_
#define _MAPSERVERMAIN_H_
/******************************************************************************/

#include "Singleton.h"
#include "ServerDllInterface.h"
#include "LuaManager.h"
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //登入服务器管理
    /******************************************************************************/
    class MapServerMain : public IServerDllInterface
    {
    public:
        SINGLETON_INSTANCE(MapServerMain);
        MapServerMain();
        virtual ~MapServerMain();

        virtual Bool    initialize(ServerLauncherInterface* launcher);
        virtual void    update();
        virtual Bool    unInitialize();

        ServerLauncherInterface*    getServerLauncher(){return mServerLauncher;}

        virtual void    onClientConnected(I32 id,NetAddress*address, INetConnect* connect);
        virtual void    onClientDisconnect(I32 id, INetConnect* connect);
        virtual void    onClientRecvPacket(I32 id,NetEventRecv* packet, INetConnect* connect);
        
		virtual void    onServerConnected(I32 id,GameNetType type, U32 serverId, U64 serverUniqueFlag, NetAddress*address) ;
        virtual void    onServerDisconnect(I32 id,NetAddress*address);
        virtual void    onServerRecvPacket(I32 id,NetEventRecv* packet);

	public:
		        void    freeEvent(INetEvent* netEvent);

    protected:

                Bool    loadFile();
				Str16   getSettingFilePath();

    protected:

        ServerLauncherInterface* mServerLauncher;
		LuaManager*				 mLuaMgr;

		/// 上次更新帧时间
		Dbl mLastUpdateTicks;
		/// 当前更新帧时间
		Dbl mCurrUpdateTicks;
		/// 当前更新帧时间段
		Dbl mUpdateDelta;
    };
}

/******************************************************************************/

#endif