/******************************************************************************/
#ifndef _CHATINTERVALCHECKMANAGER_H_
#define _CHATINTERVALCHECKMANAGER_H_
/******************************************************************************/
#include "Lock.h"
#include "WorldCorePreqs.h"
/******************************************************************************/
namespace MG
{
	 
	 //TODO:类型多独立出来
	  class ClientChatTickRecord
	  {
	  public:
            NetIdType	netId;
			
			//上次发送普通聊天频道包的时间
			U32         commonChatTick;
			//上次发送全服聊天频道包的时间
			U32         fullServerChatTick;
            //上次发送同地区聊天频道包的时间
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
			//收到特殊频道聊天包将替换到普通包的时间
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
		  //线程加锁
		  inline void threadLock()
		  {
			  if (mClientChatTickRecordListLock == NULL)
			  {
				  mClientChatTickRecordListLock = MG_NEW Critical();
			  }
			  mClientChatTickRecordListLock->lock();
		  }

		  //线程解锁
		  inline void threadUnLock()
		  {
			  mClientChatTickRecordListLock->unlock();
		  }

      };

}

//
#endif