/******************************************************************************/
#ifndef _ServerNetApplyManager_H_
#define _ServerNetApplyManager_H_
/******************************************************************************/

#include "Singleton.h"
#include "NetManager.h"
#include "GameNetPacketManager.h"
#include "Lock.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //����������
    /******************************************************************************/
    class ServerNetApplyManager : public GameNetPacketManager
    {
    public:
        SINGLETON_INSTANCE(ServerNetApplyManager);
        ServerNetApplyManager();
        virtual ~ServerNetApplyManager();

        /// ��ʼ��.
        virtual Bool        initialize();

        /// ����
        virtual I32         update();

        /// ����ʼ��
        virtual I32         unInitialize();

        ///���������
		void                loginServer( I32 id , U64 serverUniqueFlag );
        ///���ܵ�����������������Ϣ��
        void                onRecvServerConncectLogin( I32 id, Char16* name, GameNetType type, U64 serverUniqueFlag, U32 serverId, U32 code, Char8* serverVersion);
		
		I32					connect(I32 handle,NetAddress* addr,Bool reConnect);

    protected:

        /// ����ײ��¼�
        virtual void		onAccept(NetEventAccept* netEvent);
        virtual void		onConnected(NetEventConnect* netEvent);
        virtual void		onClose(NetEventClose* netEvent) ;
        virtual void		onRecv(NetEventRecv* netEvent) ;
        virtual void		onError(NetEventErr* netEvent) ;

	public:

        /// ������Ϣ
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

	protected:
		//�����������߳�
		static void			reConnectThread(Ptr ptr); 
						
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

		std::vector<ServerDeclare>	mReConnectServerMap;
		Critical					mReConnectLock;
		OneThreadHandle				mReConnectThread;
		U64							mUniqueFlag;
		
    };

}

/******************************************************************************/

#endif