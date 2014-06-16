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
	//Server对象
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
	//服务器管理 
	/******************************************************************************/
	class ServerManager
	{
	public:
		SINGLETON_INSTANCE(ServerManager);
		ServerManager();
		virtual ~ServerManager();

		//初始化和反初始化
		Bool			initialize(SServerSetting* setting);
		void			uninitialize();

	public:
		void			onConnected(I32 id,GameNetType type,U32 serverId, U64 serverUniqueFlag, NetAddress*address);
		void			onDisconnect(I32 id);
		Bool			processPacket(I32 id,NetEventRecv* packet);

		///广播数据包到FrontServer和MapServer
		void            boardcastNetPacketToServers(GameNetSendDataBufferPtr packetPtr ,I32 dataSize);

		///广播数据包到FrontServer
		void			boardcastNetPacketToFrontServers( Byte channel,Byte type,Char8* data,I32 dataSize,U64 code );

		///广播数据包到MapServer
		void			boardcastNetPacketToMapServers( Byte channel,Byte type,Char8* data,I32 dataSize,U64 code );

		//发给某个Server
		void			sendNetPacketToServer(NetIdType serverNetId, GameNetSendDataBufferPtr packetPtr ,I32 dataSize);
	
	public:

		//增加和移除FrontServer对象
		ServerInfo*     getFrontServer(I32 netId);            
		void            addFrontServer(ServerInfo* serverinfo);
		void            removeFrontServer(I32 netId);

		//增加和移除MapServer对象
		ServerInfo*     getMapServer(I32 netId);            
		void            addMapServer(ServerInfo* serverinfo);
		void            removeMapServer(I32 netId);

		//  得到SysLogServer网络编号
		I32             getSysLogServerNetId(){return mSysLogServerNetId;}

		//  得到ChatServer网络编号
		I32             getChatServerNetId(){return mChatServerNetId;}

		//  得到CenterLogServer网络编号
		I32             getCenterServerNetId(){return mCenterServerNetId;}

	protected:

		// SysLogServer网络编号
		I32                         mSysLogServerNetId;

		// ChatServer网络编号
		I32                         mChatServerNetId;

		// CenterServer网络编号
		I32                         mCenterServerNetId;

		// LoginServer网络编号		
		I32							mLoginServerNetId;

		// GMServerManager网络编号		
		I32							mGMServerManagerId;


		/*
			# FrontServer列表。
		*/
		std::map< NetIdType, ServerInfo* >	mFrontServerList;

		/*
			# MapServer列表。
		*/
		std::map< NetIdType, ServerInfo* >	mMapServerList;

	};
}
#endif