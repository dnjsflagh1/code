/******************************************************************************/
#ifndef _MAP_SERVER_SERVERMANAGER_H_
#define _MAP_SERVER_SERVERMANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "NetDefine.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//Server����
	/******************************************************************************/

    class ServerConnectInfo 
    {
    public:

        I32		mNetId;

        ServerConnectInfo();
        ~ServerConnectInfo();

        void    onConnected(I32 id);
        void    onDisConnected();
        Bool    isConnected();
        void    disConnected();
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

    public:

        //-----------------------------------------------------------------------------------------

        Bool                initialize();
        void                update();
        Bool                unInitialize();

        //-----------------------------------------------------------------------------------------

        // From MapServerMain
        void			    onConnected(I32 id,GameNetType type,U32 serverId,NetAddress*address);
        void			    onDisconnect(I32 id);   
        Bool			    processPacket(I32 id,NetEventRecv* packet);

        void                onConnectFrontServer(I32 id);
        void                onConnectCenterServer(I32 id);
        void                onConnectChatServer(I32 id);
        void                onConnectSysLogServer(I32 id);

        void                onDisconnectFrontServer(I32 id);
        void                onDisconnectCenterServer(I32 id);
        void                onDisconnectChatServer(I32 id);
        void                onDisconnectSysLogServer(I32 id);

        //-----------------------------------------------------------------------------------------

        //��FrontServer�㲥
        void			    boardcastNetPacketToAllFrontServer( GameNetSendDataBufferPtr& dataPtr,I32 dataSize );
        //����Ϣ�� CenterServer
        void			    sendNetPacketToCenterServer(GameNetSendDataBufferPtr& dataPtr,I32 dataSize);
        //����Ϣ�� SysLogServer
        void			    sendNetPacketToSysServer(GameNetSendDataBufferPtr& dataPtr,I32 dataSize);
        //����Ϣ�� ChatServer
        void			    sendNetPacketToChatServer(GameNetSendDataBufferPtr& dataPtr,I32 dataSize);

        //-----------------------------------------------------------------------------------------

    public:

        void                getFrontServerList(std::vector<NetIdType>& netList);

    protected:

        //���Ӻ��Ƴ�FrontServer����
        Bool                hasFrontServer(NetIdType netId);
        void                addFrontServer(NetIdType netId);
        void                removeFrontServer(NetIdType netId);
        void                removeAllFrontServer();

    protected:

        /*
            # FrontServer���С�
        */
        std::map<NetIdType, ServerConnectInfo> mFrontServerList;
        RWLocker mFrontServerListCs;

        // CenterServer������
		ServerConnectInfo           mCenterServerConnect;
        // SysLogServer������
        ServerConnectInfo           mSysLogServerConnect;
		// ChatServer������
		ServerConnectInfo           mChatServerConnect;

    };
}
#endif	//_MAP_SERVER_SERVERMANAGER_H_