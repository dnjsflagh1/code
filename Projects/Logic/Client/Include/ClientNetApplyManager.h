/******************************************************************************/
#ifndef _CLIENTNETAPPLYMANAGER_H_
#define _CLIENTNETAPPLYMANAGER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "Singleton.h"
#include "NetManager.h"
#include "GameNetPacketManager.h"
/******************************************************************************/
namespace MG
{
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
        virtual Bool				initialize();
        /// 运行
        virtual I32					update();
        /// 反初始化
        virtual I32					unInitialize();

        /// 连接登入服务器
        Bool						connectLoginServer( NetAddress& addr );
        /// 断开登入服务器
        Bool						disconnectLoginServer();
        /// 连接前端服务器
        Bool						connectFrontServer( NetAddress& addr );
        /// 断开前端服务器
        Bool						disconnectFrontServer();
        /// 断开所有服务器
        Bool						disconnectServers();
        
        // 得到发送数据缓存
        GameNetSendDataBufferPtr	getSendDataBuffer( U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE );
        void						sendLoginServerPacket( GameNetSendDataBufferPtr& data, Int dataSize );
        void						sendFrontServerPacket( GameNetSendDataBufferPtr& data, Int dataSize );
        
    protected:

        virtual void				onAccept(NetEventAccept* netEvent);
        virtual void				onConnected(NetEventConnect* netEvent);
        virtual void				onClose(NetEventClose* netEvent);
        virtual void				onRecv(NetEventRecv* netEvent);
        virtual void				onError(NetEventErr* netEvent);

    private:
		I32	mNetDriver;

        I32 mLoginServerID;
        I32 mFrontServerID;
    };

}

/******************************************************************************/

#endif