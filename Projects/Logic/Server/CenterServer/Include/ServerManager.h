/******************************************************************************/
#ifndef _SERVERMANAGER_H_
#define _SERVERMANAGER_H_
/******************************************************************************/

#include "CenterServerPreqs.h"

/******************************************************************************/
namespace MG
{

    /******************************************************************************/
    //Server����
    /******************************************************************************/
    struct ServerInfo 
    {
        I32		netId;
		U64		serverUniqueFlag;
        ServerInfo()
        {
            netId	= 0;
			serverUniqueFlag = 0;
        }
    };
    /******************************************************************************/
    //���������� 
    /******************************************************************************/
    class ServerManager
    {
    public:
        SINGLETON_INSTANCE(ServerManager);
        ServerManager();
        virtual ~ServerManager();

		//��ʼ���ͷ���ʼ��
		Bool			initialize(SServerSetting* setting);
		void			uninitialize();

    public:
        void			onConnected(I32 id,GameNetType type, U32 serverId,U64 serverUniqueFlag, NetAddress*address);
        void			onDisconnect(I32 id);
        Bool			processPacket(I32 id,NetEventRecv* packet);
		
		//�㲥���ݰ���FrontServer��MapServer
		void            boardcastNetPacketToServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);
		void            boardcastToFrontServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);
		void            boardcastToMapServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);

		////�㲥���ݰ���FrontServer
		//void			boardcastNetPacketToFrontServers( Byte channel,Byte type,Char8* data,I32 dataSize,U64 code );

		////�㲥���ݰ���MapServer
		void			boardcastNetPacketToMapServers(GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);

		//����ĳ��MapServer
		void			sendNetPacketToMapServer(NetIdType mapServerId, GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);

		//����ĳ��FrontServer
		void			sendNetPacketToFrontServer(NetIdType frontServerId, GameNetSendDataBufferPtr& packetPtr ,I32 dataSize);

	public:
       
		//���Ӻ��Ƴ�FrontServer����
        ServerInfo*     getFrontServer(I32 netId);
        void            addFrontServer(ServerInfo* serverinfo);
        void            removeFrontServer(I32 netId);
		ServerInfo*     getFrontServerByIndex(I32 index);
		
		//���Ӻ��Ƴ�MapServer����
		ServerInfo*     getMapServer(I32 netId);
		void            addMapServer(ServerInfo* serverinfo);
		void            removeMapServer(I32 netId);
		
		
		//ͬ��MapServer������״̬�����з�����
		void			syncMapServersStateToAllServer(/*Bool toOnlyFrontServer = false*/);

		void			sendToFrontServerSyncMapServersStateStart();
		void			syncMapServersStateToAllServerNewByLinhu(/*Bool toOnlyFrontServer = false*/);

        //    �õ�SysLogServer������
        I32             getSysLogServerNetID(){return mSysLogServerNetID;}


		std::list< ServerInfo*>*	getFrontServerList();
    protected:

        // SysLogServer������
        I32                         mSysLogServerNetID;

        /*
            # FrontServer���С�
        */
		typedef std::list< ServerInfo* >	FrontServerListContainer;
        FrontServerListContainer			mFrontServerList;

        /*
            # MapServer���С�
        */
        std::vector< ServerInfo* > mMapServerList;

		//�����ϴε�¼����MapServer�������
		I32						mMaxMapServerNum;

    };
}
#endif