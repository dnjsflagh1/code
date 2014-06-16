/******************************************************************************/
#ifndef _ClientNetUdpApplyManager_H_
#define _ClientNetUdpApplyManager_H_
/******************************************************************************/
#include "Singleton.h"
#include "NetUdpManager.h"
#include "GameNetUdpPacketManager.h"
/******************************************************************************/
#define MAX_SOCKET 100
namespace MG
{
    /******************************************************************************/
    //服务器管理
    /******************************************************************************/
    class ClientNetUdpApplyManager : public GameNetUdpPacketManager
    {
    public:
        SINGLETON_INSTANCE(ClientNetUdpApplyManager);
        ClientNetUdpApplyManager();
        virtual ~ClientNetUdpApplyManager();

        /// 初始化.
        virtual Bool            initialize();
        /// 运行
        virtual I32             update();
        /// 反初始化
        virtual I32             unInitialize();

        /// 连接登入服务器
        Bool                    connectLoginServer( NetAddress& addr );
        /// 断开登入服务器
        Bool                    disconnectLoginServer();
        /// 连接前端服务器
        Bool                    connectFrontServer( NetAddress& addr );
        /// 断开前端服务器
        Bool                    disconnectFrontServer();
        /// 断开所有服务器
        Bool                    disconnectServers();  
        /// 得到发送数据缓存
		LogicSendPacket*		getLogicSendPacket(I32 handle,Byte channel,Byte type, U32 logicDataSize,Char8* data);
		
		I32					mNetDriver;
		I32					mSocketIndex[MAX_SOCKET];  
	protected:

		virtual void		onAccept(NetUdpEventAccept* netEvent);
		virtual void		onConnected(NetUdpEventConnect* netEvent);
		virtual void		onClose(NetUdpEventClose* netEvent);
		virtual void		onRecv(NetUdpEventRecv* netEvent);
		virtual void		onError(NetUdpEventErr* netEvent);

    private:
		

    };

}

/******************************************************************************/

#endif