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
	//��Ϸ������
	/******************************************************************************/
	struct IocpNetUdpSectionPacket;
	class GameNetUdpPacketManager : public NetUdpManager
	{
	public:
		GameNetUdpPacketManager();
		virtual ~GameNetUdpPacketManager();

		virtual Bool        initialize(U16 sectionPacketSize);
		//handlePacketCount = ���������
		//-1,Ϊȫ������
		virtual I32         update();
		virtual I32         unInitialize();

		void				setOnceHandlePacketCountByDriver(I32 handle,I32 onceHandlePacketCount);
		Int					getOnceHandlePacketCountByDriver(I32 handle);
		void				revertOnceHandlePacketCountByDrive();

		//���������¼�
		void				handleNetEvent(INetUdpEvent* netEvent);
	protected:

		virtual	void	    addUdpAcceptEvent(I32 handle,I32 id,U32 logicId,NetAddress&address);
		virtual	void	    addUdpConnectEvent(I32 handle,I32 id,U32 logicId,NetAddress&address);
		virtual	void	    addUdpCloseEvent(I32 handle,I32 id,U32 logicId,Bool isPassivity,NetAddress&address);
		virtual	void	    addUdpRecvEvent(I32 handle,I32 id,U32 logicId,IocpNetUdpSectionPacket* packet);
		virtual	void	    addUdpErrEvent(I32 handle,I32 id,U32 logicId);

		NetUdpEventRecv*	createNetUdpEventRecv(I32 id,U16 sectionPacketSize,U32 sectionCount );
		void				destoryNetUdpEventRecv(NetUdpEventRecv* recvEvent);
		///�ͷ��¼�����
		void				freeEvent(INetUdpEvent* netEvent);

	protected:

		Bool				checkRecvPacketValid(I32 handle,I32 id, GameNetUdpPacketHeader* packet,I32 packetSize);

		virtual void		onAccept(NetUdpEventAccept* netEvent) = 0;
		virtual void		onConnected(NetUdpEventConnect* netEvent) = 0;
		virtual void		onClose(NetUdpEventClose* netEvent) = 0;
		virtual void		onRecv(NetUdpEventRecv* netEvent) =0;
		virtual void		onError(NetUdpEventErr* netEvent) = 0;
		
	private:

		// �����������ӵ����������¼����м���
		struct NetEventsSet
		{
			// �Ƿ���Ч
			Bool isValid;
			// ����
			std::map<U32,	INetUdpEvent*>  preparingEventsList;
			std::map<U32,	INetUdpEvent*>  preparedEventsList;
			NetEventsSet()
				:isValid( true )
			{

			}
		};

		//���������¼�����//�����������ӻ���
		typedef std::map<I32, NetEventsSet>	NetEventsList;

		//���������¼�����//����NetManager::Driver���໮��
		std::map<I32, NetEventsList>	        mNetEventsMap;

		//һ�δ��������
		//-1,Ϊȫ������
		//����NetManager::Driver���໮��
		std::map<I32, Int>	                    mOnceHandlePacketCount;

		// �����
		ObjectPool<NetUdpEventAccept>		mNetUdpEventAcceptPool;
		ObjectPool<NetUdpEventConnect>		mNetUdpEventConnectPool;
		ObjectPool<NetUdpEventClose>		mNetUdpEventClosePool;

		std::map<U32, ObjectPool<NetUdpEventRecv>>
											mNetEventNormalRecvPools;                     // �������ݻ���ṹ���б�
	
		ObjectPool<NetUdpEventErr>			mNetUdpEventErrPool;
		
		// �߳���
		Critical    mNetEventsPreparedListCs;
		Critical    mNetEventsPreparingListCs;

		Critical    mNetEventsPoolCs;

	};

}

/******************************************************************************/

#endif