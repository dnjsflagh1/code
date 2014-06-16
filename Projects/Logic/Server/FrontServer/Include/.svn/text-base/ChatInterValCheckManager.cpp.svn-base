/******************************************************************************/
#include "stdafx.h"
#include "CommonGameDefine.h"
#include "ChatInterValCheckManager.h"
/******************************************************************************/
namespace MG
{

        //-----------------------------------------------------------------------------
		ChatIntervalCheckManager::~ChatIntervalCheckManager()
		{
			if (mClientChatTickRecordListLock != NULL)
			{
                 MG_SAFE_DELETE(mClientChatTickRecordListLock);
				 mClientChatTickRecordListLock = NULL;
			}

			//
			destoryClientChatTickRecordList();
		}

		//-----------------------------------------------------------------------------
		Bool ChatIntervalCheckManager::addClientChatTickRecord( NetIdType clientNetID )
		{
			   
               ClientChatTickRecord* clientRecordPtr = getClientChatTickRecordByClientNetID(clientNetID);
			   if (clientRecordPtr == NULL)
			   {
				    //对象池内部锁
                    mClientChatTickRecordPool.threadLock();
					{
						clientRecordPtr = MG_POOL_NEW(mClientChatTickRecordPool,ClientChatTickRecord,(clientNetID));
					
					}
					mClientChatTickRecordPool.threadUnLock();
					if (clientRecordPtr)
					{
						 //外部逻辑数据链表锁
                         threadLock();
						 {
							mClientChatTickRecordList[clientNetID] = clientRecordPtr;
						 }
						 threadUnLock();
						 return true;
					}
					else
					{
                           return false;
					}
			   }
			   else
			   {
				   return false;
				  
			   }

		}

		//-----------------------------------------------------------------------------
		MG::ClientChatTickRecord* ChatIntervalCheckManager::getClientChatTickRecordByClientNetID( NetIdType clientNetID )
		{
              ClientChatTickRecord* clientRecordPtr = NULL;
			  threadLock();
			  {
				  std::map< NetIdType, ClientChatTickRecord* >::iterator it = mClientChatTickRecordList.find(clientNetID);
				  if (it != mClientChatTickRecordList.end())
				  {
					  clientRecordPtr = it->second;
				  }
			  }
			  threadUnLock();
			  return clientRecordPtr;
			  
		}
		//-----------------------------------------------------------------------------
		void ChatIntervalCheckManager::clearClientChatTickRecordList()
		{
			if (mClientChatTickRecordList.size() >= 0)
			{
				mClientChatTickRecordList.clear();
			}
			
			
		}
		//-----------------------------------------------------------------------------
		void ChatIntervalCheckManager::removeClientChatTickRecordBytNetID( NetIdType clientNetID )
		{
			threadLock();
			{
				std::map<NetIdType, ClientChatTickRecord*>::iterator it = mClientChatTickRecordList.find(clientNetID);
				if (it != mClientChatTickRecordList.end())
				{
					MG_POOL_DELETE( mClientChatTickRecordPool, it->second);
					mClientChatTickRecordList.erase(it);
				}

			}
			threadUnLock();
			
		}
		//-----------------------------------------------------------------------------
		void ChatIntervalCheckManager::destoryClientChatTickRecordList()
		{
			std::map<NetIdType, ClientChatTickRecord*>::iterator front = mClientChatTickRecordList.begin();
			std::map<NetIdType, ClientChatTickRecord*>::iterator back = mClientChatTickRecordList.end();
			while(front != back)
			{
				MG_POOL_DELETE( mClientChatTickRecordPool, front->second);
				front++;
			}
			clearClientChatTickRecordList();

		}
		//-----------------------------------------------------------------------------

	
}
