/******************************************************************************/
#ifndef _SERVERNETAPPLYMANAGER_H_
#define _SERVERNETAPPLYMANAGER_H_
/******************************************************************************/

#include "Singleton.h"
#include "NetManager.h"
#include "GameNetPacketManager.h"
#include "Lock.h"
#include <map>
/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //服务器管理
    /******************************************************************************/
    class ServerNetApplyManager : public GameNetPacketManager
    {
    public:
        SINGLETON_INSTANCE(ServerNetApplyManager);
        ServerNetApplyManager();
        virtual ~ServerNetApplyManager();

        /// 初始化.
        virtual Bool        initialize();

        /// 运行
        virtual I32         update();

        /// 反初始化
        virtual I32         unInitialize();

        ///登入服务器
		I32					connect(I32 handle,NetAddress* addr,Bool reConnect);
    protected:

        /// 网络底层事件
        virtual void		onAccept(NetEventAccept* netEvent);
        virtual void		onConnected(NetEventConnect* netEvent);
        virtual void		onClose(NetEventClose* netEvent) ;
        virtual void		onRecv(NetEventRecv* netEvent) ;
        virtual void		onError(NetEventErr* netEvent) ;

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
		U64					getUniqueFlag();

	protected:

						
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