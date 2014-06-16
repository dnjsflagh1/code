/******************************************************************************/
#ifndef _SERVERMANAGER_H_
#define _SERVERMANAGER_H_
/******************************************************************************/

#include "CenterServerPreqs.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //Server对象
    /******************************************************************************/
    struct ServerInfo 
    {
        I32		netId;
		U64		serverUniqueFlag;
        ServerInfo()
        {
            netId	= 0;
			serverUniqueFlag = 0;
        }
    };
    /******************************************************************************/
    //服务器管理 
    /******************************************************************************/
    class ServerManager
    {
    public:
        SINGLETON_INSTANCE(ServerManager);
        ServerManager();
        virtual ~ServerManager();

		//初始化和反初始化
		Bool			initialize(SServerSetting* setting);
		void			uninitialize();

    public:
        void			onConnected(I32 id,GameNetType type, U32 serverId,U64 serverUniqueFlag, NetAddress*address);
        void			onDisconnect(I32 id);
        Bool			processPacket(I32 id,NetEventRecv* packet);
		
		//广播数据包到FrontServer和MapServer
		void            boardcastNetPacketToServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);
		void            boardcastToFrontServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);
		void            boardcastToMapServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);

		////广播数据包到FrontServer
		//void			boardcastNetPacketToFrontServers( Byte channel,Byte type,Char8* data,I32 dataSize,U64 code );

		////广播数据包到MapServer
		void			boardcastNetPacketToMapServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);

		//发给某个MapServer
		void			sendNetPacketToMapServer(NetIdType mapServerId, GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);

		//发给某个FrontServer
		void			sendNetPacketToFrontServer(NetIdType frontServerId, GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);

	public:
       
		//增加和移除FrontServer对象
        ServerInfo*     getFrontServer(I32 netId);
        void            addFrontServer(ServerInfo* serverinfo);
        void            removeFrontServer(I32 netId);
		ServerInfo*     getFrontServerByIndex(I32 index);
		
		//增加和移除MapServer对象
		ServerInfo*     getMapServer(I32 netId);
		void            addMapServer(ServerInfo* serverinfo);
		void            removeMapServer(I32 netId);
		
		
		//同步MapServer服务器状态给所有服务器
		void			syncMapServersStateToAllServer(/*Bool toOnlyFrontServer = false*/);

		void			sendToFrontServerSyncMapServersStateStart();
		void			syncMapServersStateToAllServerNewByLinhu(/*Bool toOnlyFrontServer = false*/);

        //    得到SysLogServer网络编号
        I32             getSysLogServerNetID(){return mSysLogServerNetID;}


		std::list< ServerInfo*>*	getFrontServerList();
    protected:

        // SysLogServer网络编号
        I32                         mSysLogServerNetID;

        /*
            # FrontServer队列。
        */
		typedef std::list< ServerInfo* >	FrontServerListContainer;
        FrontServerListContainer			mFrontServerList;

        /*
            # MapServer队列。
        */
        std::vector< ServerInfo* > mMapServerList;

		//保存上次登录过的MapServer的最大数
		I32						mMaxMapServerNum;

    };
}
#endif