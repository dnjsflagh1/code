/******************************************************************************/
#ifndef _CLIENTMANAGER_H_
#define _CLIENTMANAGER_H_
/******************************************************************************/
#include "ObjectPool.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//�ͻ��˶���
	/******************************************************************************/

// �Ͽ�����֮��ͻ��˶���ʱʱ��Ϊ10��
// ��������id �������ظ����������������������ڣ����Կ���������id�������
#define MAX_CLIENT_TIMEOUT_AFTER_DISCONNECTED 5000	
// ��������߼����������ʱ����
#define CHECK_DISCONNECTED_CLIENT_TIME_OFFECT 4000
// ���ӳ���20���� ��δ��¼�ɹ� �ͻ��˶���ʱ�Ͽ�����
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
	//�ͻ��˹���
	//����ɹ���Ͽ�����
	//TODO����Ҫ�޸�ΪUDP����
	//TODO����Ҫ����ͬһIP��������
	/******************************************************************************/
	class ClientManager
	{
	public:
		SINGLETON_INSTANCE(ClientManager);
		ClientManager();
		virtual ~ClientManager();
	public:

		//��ʼ���ͷ���ʼ��
		Bool    initialize();
		void    uninitialize();

		//�����̸���
		void	update();

		//����ײ��¼�
		void	onConnected(I32 id,NetAddress*address);
		void	onDisconnect(I32 id);
		Bool	processPacket(I32 id, NetEventRecv* packet);

	public:
		/*Bool	removeClientObject(I32 id);*/
		ClientObject*	createClientObject(I32 netId,U64 uin,NetAddress& address);
		void			destoryClientObject(ClientObject* clientObj);

		void			addClientObjectToMap(I32 netId,ClientObject* clientObj);
		ClientObject*	getClientFromMap(I32 netId);
		// ֻ��������Ͽ�����ʱ��Ż���ô˽ӿ�
		void			removeClientObjectFromMap(I32 netId);

		void			addClientObjectToQueue(ClientObject* clientObj);
		ClientObject*	getClientObjectFromQueue();			
		
		
	protected:

		//���ͻ��˳�ʱ ���� �Ͽ����Ӻ�����߼����� ��û�е�½�ɹ��Ŀͻ��ˣ�
		static	void	checkTimeOutThread(Ptr ptr); 

	public:	
		ObjectPool<ClientObject,false> mClientObjectPool;

		// �Ѿ����ӵĿͻ��˶����<netId,�ͻ��˶���>
		std::map<I32, ClientObject*>	mClientObjectList;
		Critical						mClientObjectListLock;

		// �ͻ��˶�����У�����ģ���Ϊ�˼�С��������
		std::queue<ClientObject*>		mClientObjectQueue;
		Critical						mClientObjectQueueLock;

		

		OneThreadHandle	mCheckTimeOutThread;
	};
}
#endif