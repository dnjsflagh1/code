/******************************************************************************/
#ifndef _SERVERMANAGER_H_
#define _SERVERMANAGER_H_
/******************************************************************************/

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //Server对象
    /******************************************************************************/
    struct ServerInfo 
    {
        GameNetType type;
        I32		netId;
		U64		serverUniqueFlag;
        ServerInfo()
        {
            type = GNT_UNKOWN;
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
        void			onConnected(I32 id,GameNetType type,U32 serverId,  U64 serverUniqueFlag, NetAddress*address);
        void			onDisconnect(I32 id);
        Bool			processPacket(I32 id,NetEventRecv* packet);
		
		//广播数据包到指定类型的服务器
		void            boardcastNetPacketToServers(GameNetSendDataBufferPtr& packetPtr, I32 dataSize, GameNetType type);
	public:
       
		//增加和移除FrontServer对象
        ServerInfo*     getServerInfo(I32 netId);            
        void            addServerInfo(ServerInfo* serverinfo);
        void            removeServerInfo(I32 netId);

    protected:

        //把所有的server都写在一个队列中，
        //因为SysLogServer没有逻辑处理，不需要信息回馈。
        /*
            # Server队列。
        */
        std::list< ServerInfo* > mServerList;

    };
}
#endif