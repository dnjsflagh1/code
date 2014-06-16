/******************************************************************************/
#ifndef _CLIENTNETAPPLYMANAGER_H_
#define _CLIENTNETAPPLYMANAGER_H_
/******************************************************************************/
#include "Singleton.h"
#include "NetManager.h"
#include "GameNetPacketManager.h"
/******************************************************************************/
namespace MG
{
	/*extern InterLocked netId[MAX_CONNECT];
	extern Critical connectLock;
	extern std::map<I32,Int> connectIndexs;*/
	enum
	{
		unknownServerPacket = 0,
		frontServerPacket = 1,
		loginServerPacket = 2,
	};
    /******************************************************************************/
    //服务器管理
    /******************************************************************************/
    class ClientNetApplyManager : public GameNetPacketManager
    {
    public:
        SINGLETON_INSTANCE(ClientNetApplyManager);
        ClientNetApplyManager();
        virtual ~ClientNetApplyManager();

        /// 初始化.
        virtual Bool        initialize();
        /// 运行
        virtual I32         update();
        /// 反初始化
        virtual I32         unInitialize();

        /// 连接登入服务器
        I32					connectLoginServer( NetAddress& addr);
        /// 断开登入服务器
        Bool                disconnectLoginServer(I32 loginServerNetId);
        /// 连接前端服务器
        I32					connectFrontServer( NetAddress& addr);
        /// 断开前端服务器
        Bool                disconnectFrontServer(I32 frontServerNetId);
        /// 断开所有服务器
        Bool                disconnectServers();
        
		// 得到发送数据缓存
		GameNetSendDataBufferPtr	getSendDataBuffer( U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE );
		void					sendFrontServerPacket(I32 frontServerNetId, GameNetSendDataBufferPtr& data, Int dataSize );
		void					sendLoginServerPacket(I32 loginServerNetId, GameNetSendDataBufferPtr& data, Int dataSize );
          protected:

        virtual void		onAccept(NetEventAccept* netEvent);
        virtual void		onConnected(NetEventConnect* netEvent);
        virtual void		onClose(NetEventClose* netEvent);
        virtual void		onRecv(NetEventRecv* netEvent);
        virtual void		onError(NetEventErr* netEvent);

    public:
		I32	mNetDriver;
		//Critical			sendLock;
    };

}

/******************************************************************************/

#endif