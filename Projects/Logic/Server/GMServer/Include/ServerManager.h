/******************************************************************************/
#ifndef _SERVERMANAGER_H_
#define _SERVERMANAGER_H_
/******************************************************************************/
#include "GMServerPreqs.h"
/******************************************************************************/
class SServerSetting;
namespace MG
{
	/******************************************************************************/
	//Server����
	/******************************************************************************/
	struct ServerInfo 
	{
		I32		netId;
		U64		serverUniqueFlag;
		U32		serverId;
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
		void			onConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address);
		void			onDisconnect(I32 id);
		Bool			processPacket(I32 id,NetEventRecv* packet);

		///�㲥���ݰ���FrontServer��MapServer
		void            boardcastNetPacketToServers(GameNetSendDataBufferPtr packetPtr ,I32 dataSize);

		///�㲥���ݰ���FrontServer
		void			boardcastNetPacketToFrontServers( Byte channel,Byte type,Char8* data,I32 dataSize,U64 code );

		///�㲥���ݰ���MapServer
		void			boardcastNetPacketToMapServers( Byte channel,Byte type,Char8* data,I32 dataSize,U64 code );

		//����ĳ��Server
		void			sendNetPacketToServer(NetIdType serverNetId, GameNetSendDataBufferPtr packetPtr ,I32 dataSize);
	
	public:

		//���Ӻ��Ƴ�FrontServer����
		ServerInfo*     getFrontServer(I32 netId);            
		void            addFrontServer(ServerInfo* serverinfo);
		void            removeFrontServer(I32 netId);

		//���Ӻ��Ƴ�MapServer����
		ServerInfo*     getMapServer(I32 netId);            
		void            addMapServer(ServerInfo* serverinfo);
		void            removeMapServer(I32 netId);

		//  �õ�SysLogServer������
		I32             getSysLogServerNetId(){return mSysLogServerNetId;}

		//  �õ�ChatServer������
		I32             getChatServerNetId(){return mChatServerNetId;}

		//  �õ�CenterLogServer������
		I32             getCenterServerNetId(){return mCenterServerNetId;}

	protected:

		// SysLogServer������
		I32                         mSysLogServerNetId;

		// ChatServer������
		I32                         mChatServerNetId;

		// CenterServer������
		I32                         mCenterServerNetId;

		// LoginServer������		
		I32							mLoginServerNetId;

		// GMServerManager������		
		I32							mGMServerManagerId;


		/*
			# FrontServer�б�
		*/
		std::map< NetIdType, ServerInfo* >	mFrontServerList;

		/*
			# MapServer�б�
		*/
		std::map< NetIdType, ServerInfo* >	mMapServerList;

	};
}
#endif