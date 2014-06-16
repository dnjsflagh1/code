/******************************************************************************/
#ifndef _SERVERMANAGER_H_
#define _SERVERMANAGER_H_
/******************************************************************************/
#include "GMServerManagerPreqs.h"
/******************************************************************************/
class SServerSetting;
namespace MG
{
	/******************************************************************************/
	//Server对象
	/******************************************************************************/
	struct GMServerInfo 
	{
		I32		netId;
		U64		serverUniqueFlag;
		U32		serverId;
		Str		serverName;
		GMServerInfo()
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

		///广播数据
		void            boardcastNetPacketToServers(GameNetSendDataBufferPtr packetPtr ,I32 dataSize);

	public:
		/*
			# GMServer映射表。<网络id，GMServer信息>
		*/
		std::map< NetIdType, GMServerInfo* >			mGMServerMap;


	};
}
#endif