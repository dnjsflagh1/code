/******************************************************************************/
#ifndef _CLIENTMANAGER_H_
#define _CLIENTMANAGER_H_
/******************************************************************************/
#include "ObjectPool.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//客户端对象
	/******************************************************************************/

// 断开连接之后客户端对象超时时间为10秒
// 由于网络id 不可能重复（服务器开启两个星期内）所以可以用网络id来做检测
#define MAX_CLIENT_TIMEOUT_AFTER_DISCONNECTED 5000	
// 用来检测逻辑对象的周期时间间隔
#define CHECK_DISCONNECTED_CLIENT_TIME_OFFECT 4000
// 连接超过20分钟 还未登录成功 客户端对象超时断开连接
#define MAX_CONNECT_TIME_OUT 1200000	

	class ClientObject
	{
	public:

		I32					netId;
		U32					connectTime;
		U64					addressUIN;
		Bool				isDisConnected;
		U32					disConnectTime;
		Critical			mCs;
		NetAddress			mAddr;
		//===================================
		ClientObject(I32 id, U64 uin,NetAddress& addr)
		{
			netId		= id;
			disConnectTime = 0;
			revert(uin,addr);
		}
		//===================================
		void revert(U64 uin,NetAddress& addr)
		{
			isDisConnected = false;
			addressUIN	= uin;
			disConnectTime = 0;
			connectTime = MGTimeOp::getCurrTick();
			disConnectTime = 0;
			mAddr = addr;
		}
		//===================================
		void disConnected()
		{
			isDisConnected = true;
			disConnectTime = MGTimeOp::getCurrTick();
		}
		//===================================
	};

	/******************************************************************************/
	//客户端管理
	//登入成功后断开连接
	//TODO：需要修改为UDP连接
	//TODO：需要增加同一IP连接数量
	/******************************************************************************/
	class ClientManager
	{
	public:
		SINGLETON_INSTANCE(ClientManager);
		ClientManager();
		virtual ~ClientManager();
	public:

		//初始化和反初始化
		Bool    initialize();
		void    uninitialize();

		//主进程更新
		void	update();

		//网络底层事件
		void	onConnected(I32 id,NetAddress*address);
		void	onDisconnect(I32 id);
		Bool	processPacket(I32 id, NetEventRecv* packet);

	public:
		/*Bool	removeClientObject(I32 id);*/
		ClientObject*	createClientObject(I32 netId,U64 uin,NetAddress& address);
		void			destoryClientObject(ClientObject* clientObj);

		void			addClientObjectToMap(I32 netId,ClientObject* clientObj);
		ClientObject*	getClientFromMap(I32 netId);
		// 只有在网络断开连接时候才会调用此接口
		void			removeClientObjectFromMap(I32 netId);

		void			addClientObjectToQueue(ClientObject* clientObj);
		ClientObject*	getClientObjectFromQueue();			
		
		
	protected:

		//检测客户端超时 或者 断开连接后清除逻辑对象 （没有登陆成功的客户端）
		static	void	checkTimeOutThread(Ptr ptr); 

	public:	
		ObjectPool<ClientObject,false> mClientObjectPool;

		// 已经链接的客户端对象表<netId,客户端对象>
		std::map<I32, ClientObject*>	mClientObjectList;
		Critical						mClientObjectListLock;

		// 客户端对象队列（冗余的），为了减小锁定粒度
		std::queue<ClientObject*>		mClientObjectQueue;
		Critical						mClientObjectQueueLock;

		

		OneThreadHandle	mCheckTimeOutThread;
	};
}
#endif