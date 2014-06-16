/******************************************************************************/
#ifndef _CHATINTERVALCHECKMANAGER_H_
#define _CHATINTERVALCHECKMANAGER_H_
/******************************************************************************/
#include "Lock.h"
#include "WorldCorePreqs.h"
/******************************************************************************/
namespace MG
{
	 
	 //TODO:���Ͷ��������
	  class ClientChatTickRecord
	  {
	  public:
            NetIdType	netId;
			
			//�ϴη�����ͨ����Ƶ������ʱ��
			U32         commonChatTick;
			//�ϴη���ȫ������Ƶ������ʱ��
			U32         fullServerChatTick;
            //�ϴη���ͬ��������Ƶ������ʱ��
			//U32                 oneRegionChatTick;


			ClientChatTickRecord(NetIdType _netID,U32 _commonChatTick = 0,U32 _fullServerChatTick = 0)
				:netId(_netID)
				,commonChatTick(_commonChatTick)
				,fullServerChatTick(_fullServerChatTick)
			{

			}
			void setCommonChatTick(U32 commonTick)
			{
				commonChatTick = commonTick;
			}
			//�յ�����Ƶ����������滻����ͨ����ʱ��
			void setFullServerChatTick(U32 fullServerTick)
			{
				fullServerChatTick = fullServerTick;
				commonChatTick = fullServerTick;
			}
	  };
	 
	  //////////////////////////////////////////////////////////////////////////////////

      class ChatIntervalCheckManager
      {
      public:
			ChatIntervalCheckManager()
				:mClientChatTickRecordListLock(NULL)
			{

			}
			~ChatIntervalCheckManager();
			 SINGLETON_INSTANCE(ChatIntervalCheckManager);

            
      private: 
		  ObjectPool<ClientChatTickRecord,false>			mClientChatTickRecordPool;
		  std::map< NetIdType, ClientChatTickRecord* >	    mClientChatTickRecordList;
		  Critical*								            mClientChatTickRecordListLock;

       //////////////////////////////////////////////////////////////////////////////////

	  public:
          Bool                   addClientChatTickRecord(NetIdType clientNetID);
          ClientChatTickRecord*  getClientChatTickRecordByClientNetID(NetIdType clientNetID);
          void                   removeClientChatTickRecordBytNetID(NetIdType clientNetID);

          void                   clearClientChatTickRecordList();
		  void                   destoryClientChatTickRecordList();
		  //�̼߳���
		  inline void threadLock()
		  {
			  if (mClientChatTickRecordListLock == NULL)
			  {
				  mClientChatTickRecordListLock = MG_NEW Critical();
			  }
			  mClientChatTickRecordListLock->lock();
		  }

		  //�߳̽���
		  inline void threadUnLock()
		  {
			  mClientChatTickRecordListLock->unlock();
		  }

      };

}

//
#endif