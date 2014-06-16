/******************************************************************************/
#ifndef _GAMENETUDPPACKETMANAGER_H_
#define _GAMENETUDPPACKETMANAGER_H_
/******************************************************************************/
#include "GameNetUdpPacket.h"
#include "NetUdpManager.h"
#include "GameNetUdpEvent.h"
#include "Lock.h"
#include "ObjectPool.h"
/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//游戏包管理
	/******************************************************************************/
	struct IocpNetUdpSectionPacket;
	class GameNetUdpPacketManager : public NetUdpManager
	{
	public:
		GameNetUdpPacketManager();
		virtual ~GameNetUdpPacketManager();

		virtual Bool        initialize(U16 sectionPacketSize);
		//handlePacketCount = 处理包数量
		//-1,为全部处理
		virtual I32         update();
		virtual I32         unInitialize();

		void				setOnceHandlePacketCountByDriver(I32 handle,I32 onceHandlePacketCount);
		Int					getOnceHandlePacketCountByDriver(I32 handle);
		void				revertOnceHandlePacketCountByDrive();

		//处理网络事件
		void				handleNetEvent(INetUdpEvent* netEvent);
	protected:

		virtual	void	    addUdpAcceptEvent(I32 handle,I32 id,U32 logicId,NetAddress&address);
		virtual	void	    addUdpConnectEvent(I32 handle,I32 id,U32 logicId,NetAddress&address);
		virtual	void	    addUdpCloseEvent(I32 handle,I32 id,U32 logicId,Bool isPassivity,NetAddress&address);
		virtual	void	    addUdpRecvEvent(I32 handle,I32 id,U32 logicId,IocpNetUdpSectionPacket* packet);
		virtual	void	    addUdpErrEvent(I32 handle,I32 id,U32 logicId);

		NetUdpEventRecv*	createNetUdpEventRecv(I32 id,U16 sectionPacketSize,U32 sectionCount );
		void				destoryNetUdpEventRecv(NetUdpEventRecv* recvEvent);
		///释放事件对象
		void				freeEvent(INetUdpEvent* netEvent);

	protected:

		Bool				checkRecvPacketValid(I32 handle,I32 id, GameNetUdpPacketHeader* packet,I32 packetSize);

		virtual void		onAccept(NetUdpEventAccept* netEvent) = 0;
		virtual void		onConnected(NetUdpEventConnect* netEvent) = 0;
		virtual void		onClose(NetUdpEventClose* netEvent) = 0;
		virtual void		onRecv(NetUdpEventRecv* netEvent) =0;
		virtual void		onError(NetUdpEventErr* netEvent) = 0;
		
	private:

		// 单个网络连接的网络连接事件队列集合
		struct NetEventsSet
		{
			// 是否有效
			Bool isValid;
			// 队列
			std::map<U32,	INetUdpEvent*>  preparingEventsList;
			std::map<U32,	INetUdpEvent*>  preparedEventsList;
			NetEventsSet()
				:isValid( true )
			{

			}
		};

		//网络连接事件队列//根据网络连接划分
		typedef std::map<I32, NetEventsSet>	NetEventsList;

		//网络连接事件队列//根据NetManager::Driver分类划分
		std::map<I32, NetEventsList>	        mNetEventsMap;

		//一次处理包数量
		//-1,为全部处理
		//根据NetManager::Driver分类划分
		std::map<I32, Int>	                    mOnceHandlePacketCount;

		// 对象池
		ObjectPool<NetUdpEventAccept>		mNetUdpEventAcceptPool;
		ObjectPool<NetUdpEventConnect>		mNetUdpEventConnectPool;
		ObjectPool<NetUdpEventClose>		mNetUdpEventClosePool;

		std::map<U32, ObjectPool<NetUdpEventRecv>>
											mNetEventNormalRecvPools;                     // 发送数据缓存结构池列表
	
		ObjectPool<NetUdpEventErr>			mNetUdpEventErrPool;
		
		// 线程锁
		Critical    mNetEventsPreparedListCs;
		Critical    mNetEventsPreparingListCs;

		Critical    mNetEventsPoolCs;

	};

}

/******************************************************************************/

#endif