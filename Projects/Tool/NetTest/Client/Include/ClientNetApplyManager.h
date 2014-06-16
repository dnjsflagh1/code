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
    //����������
    /******************************************************************************/
    class ClientNetApplyManager : public GameNetPacketManager
    {
    public:
        SINGLETON_INSTANCE(ClientNetApplyManager);
        ClientNetApplyManager();
        virtual ~ClientNetApplyManager();

        /// ��ʼ��.
        virtual Bool            initialize();
        /// ����
        virtual I32             update();
        /// ����ʼ��
        virtual I32             unInitialize();

        /// ���ӵ��������
        Bool                    connectLoginServer( NetAddress& addr );
        /// �Ͽ����������
        Bool                    disconnectLoginServer();
        /// ����ǰ�˷�����
        Bool                    connectFrontServer( NetAddress& addr );
        /// �Ͽ�ǰ�˷�����
        Bool                    disconnectFrontServer();
        /// �Ͽ����з�����
        Bool                    disconnectServers();
        
        // �õ��������ݻ���
        NetSendDataBufferPtr    getSendDataBuffer( U32 buffSize = MG_GAME_NET_PACKET_NORMAL_MAX_SIZE );
        void                    sendLoginServerPacket( NetSendDataBufferPtr& data, Int dataSize );
        void                    sendFrontServerPacket( NetSendDataBufferPtr& data, Int dataSize );
        
    protected:

        virtual void		    onAccept(NetEventAccept* netEvent);
        virtual void		    onConnected(NetEventConnect* netEvent);
        virtual void		    onClose(NetEventClose* netEvent);
        virtual void		    onRecv(NetEventRecv* netEvent);
        virtual void		    onError(NetEventErr* netEvent);

    private:
		I32	mNetDriver;

        I32 mLoginServerID;
        I32 mFrontServerID;
    };

}

/******************************************************************************/

#endif