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
    //����������
    /******************************************************************************/
    class ClientNetApplyManager : public GameNetPacketManager
    {
    public:
        SINGLETON_INSTANCE(ClientNetApplyManager);
        ClientNetApplyManager();
        virtual ~ClientNetApplyManager();

        /// ��ʼ��.
        virtual Bool        initialize();
        /// ����
        virtual I32         update();
        /// ����ʼ��
        virtual I32         unInitialize();

        /// ���ӵ��������
        I32					connectLoginServer( NetAddress& addr);
        /// �Ͽ����������
        Bool                disconnectLoginServer(I32 loginServerNetId);
        /// ����ǰ�˷�����
        I32					connectFrontServer( NetAddress& addr);
        /// �Ͽ�ǰ�˷�����
        Bool                disconnectFrontServer(I32 frontServerNetId);
        /// �Ͽ����з�����
        Bool                disconnectServers();
        
		// �õ��������ݻ���
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