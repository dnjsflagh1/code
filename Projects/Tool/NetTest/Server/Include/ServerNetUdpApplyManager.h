/******************************************************************************/
#ifndef _SERVERNETUDPAPPLYMANAGER_H_
#define _SERVERNETUDPAPPLYMANAGER_H_
/******************************************************************************/

#include "Singleton.h"
//#include "NetUdpManager.h"
//#include "GameNetUdpPacketManager.h"
#include "Lock.h"
#include <map>
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //服务器管理
    /******************************************************************************/
    class ServerNetUdpApplyManager : public GameNetUdpPacketManager
    {
    public:
        SINGLETON_INSTANCE(ServerNetUdpApplyManager);
        ServerNetUdpApplyManager();
        virtual ~ServerNetUdpApplyManager();

        /// 初始化.
        virtual Bool        initialize(U16 sectionPacketSize);

        /// 运行
        virtual I32         update();

        /// 反初始化
        virtual I32         unInitialize();

		void				connect(I32 handle,NetAddress* addr,Bool reConnect);
    protected:

        /// 网络底层事件
		virtual void		onAccept(NetUdpEventAccept* netEvent);
		virtual void		onConnected(NetUdpEventConnect* netEvent);
		virtual void		onClose(NetUdpEventClose* netEvent);
		virtual void		onRecv(NetUdpEventRecv* netEvent);
		virtual void		onError(NetUdpEventErr* netEvent);

	public:

        /// 网络信息
		I32					getServerHandle();	
		I32					getClientHandle();

        void				closeAllClient();
		void				closeClient(I32 id);
		void				closeServer(I32 id);

		U64					getClientUid(I32 id);
		U64					getServerUid(I32 id);

		NetConnectInfo*		getClientNetInfo();
		NetConnectInfo*		getServerNetInfo();
		NetConnectInfo*		getClientConnectInfo(I32 id);
		NetConnectInfo*		getServerConnectInfo(I32 id);

		I32					getServerCurrConnectionCount();
		I32					getClientCurrConnectionCount();

		Bool				isAllowedConnect(CChar16* ip);
		Bool				isAllowedConnect(CChar8* ip);
		void				setConnectServerLoginState(U64 uin,I32 netId,Bool isConnected,Bool isLogined);
		U64					getUniqueFlag();
						
	private:

		I32 mClientDriver;
		I32 mServerDriver;

		struct ServerDeclare
		{
			Bool		isConnected;
			Bool		isLogined;
			NetAddress	address;
			I32			handle;
			I32			netId;
			U64			lastConnectTimeTick;
			I32			connectTimes;
			I32			loginTimes;
			ServerDeclare()
			{
				isConnected = false;
				isLogined = false;
				handle = -1;
				netId = -1;
				lastConnectTimeTick = 0;
				connectTimes = 0;
				loginTimes = 0;
			}
		};

		U64							mUniqueFlag;
		std::map<I32,Bool>			mRemoteConnects;
    };
	
}

/******************************************************************************/

#endif