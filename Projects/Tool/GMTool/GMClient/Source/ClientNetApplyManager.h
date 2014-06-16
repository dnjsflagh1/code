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
        virtual Bool            initialize();
        /// 运行
        virtual I32             update();
        /// 反初始化
        virtual I32             unInitialize();

        /// 连接GM服务器
        Bool                    connectGMServerManager( NetAddress& addr );
		/// 断开GM服务器
        Bool                    disconnectGMServerManager();

        
        // 得到发送数据缓存
        NetSendDataBufferPtr    getSendDataBuffer( U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE );
        void                    sendPacket( NetSendDataBufferPtr& data, Int dataSize );
		void					closeNet();
    protected:

        virtual void		    onAccept(NetEventAccept* netEvent);
        virtual void		    onConnected(NetEventConnect* netEvent);
        virtual void		    onClose(NetEventClose* netEvent);
        virtual void		    onRecv(NetEventRecv* netEvent);
        virtual void		    onError(NetEventErr* netEvent);

    private:
		I32	mNetDriver;

        I32 mGMServerManagerId;
    };

}

/******************************************************************************/

#endif