/******************************************************************************/
#include "stdafx.h"
#include "ClientManager.h"

/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------
	ClientManager::ClientManager()
	{

	}
	//--------------------------------------------------------------------------
	ClientManager::~ClientManager()
	{

	}
	//--------------------------------------------------------------------------
	MG::Bool ClientManager::initialize()
	{
		return true;
	}
	//--------------------------------------------------------------------------
	void ClientManager::uninitialize()
	{

	}
	//--------------------------------------------------------------------------
	Bool ClientManager::addClientObject( Str16 clanName,I32 netIdInFrontServer,I32 frontServerNetId,U64 accountId )
	{
		// 先查找客户端对象
		ClientObject* clientObj = getClientObject(clanName);
		if (clientObj)
		//存在时修改数据
		{
			//DYNAMIC_ASSERT(false);
			clientObj->frontServerNetId = frontServerNetId;
			clientObj->netIdInFrontServer = netIdInFrontServer;
			clientObj->accountId = accountId;
			return false;
		}
		// 不存在 
		// 添加数据到hash表
		clientObj = MG_POOL_NEW(mClientObjectPool,ClientObject,(netIdInFrontServer, frontServerNetId,accountId));
		mClientObjectHashMap.element[clanName] = clientObj;

		// 添加数据到分类表
		if (mClientObjectClassSet.element.empty())
		{
			ClientHashMap tempSet;
			tempSet.element[clanName] = clientObj;
			mClientObjectClassSet.element[clientObj->frontServerNetId] = tempSet;
		}
		else
		{
			ClientClassMapIt classit = mClientObjectClassSet.element.find(clientObj->frontServerNetId);
			if (classit != mClientObjectClassSet.element.end())
			{
				classit->second.element[clanName] = clientObj;	
			}
			else
			{
				ClientHashMap tempSet;
				tempSet.element[clanName] = clientObj;
				mClientObjectClassSet.element[clientObj->frontServerNetId] = tempSet;
			}
			
		}
		return true;
	}
	//--------------------------------------------------------------------------
	MG::Bool ClientManager::removeClientObject( Str16 clanName )
	{
		ClientHashMapIt it = mClientObjectHashMap.element.find(clanName);
		if (it != mClientObjectHashMap.element.end())
		{
			// 先移除mClientObjectClassSet中客户端
			Bool error = true;
			ClientClassMapIt classSetit = mClientObjectClassSet.element.begin();
			for (; classSetit != mClientObjectClassSet.element.end();)
			{
				ClientHashMap& clienMap = classSetit->second;
				if (clienMap.element.empty())
				{
					classSetit = mClientObjectClassSet.element.erase(classSetit);
				}
				else
				{
					ClientHashMapIt clientIt = clienMap.element.find(clanName);
					if (clientIt != clienMap.element.end())
					{
						clienMap.element.erase(clientIt);
						error = false;
						break;
					}
					classSetit++;
				}
				
			}
			// 再移除mClientObjectHashMap中客户端
			MG_POOL_DELETE(mClientObjectPool,it->second);
			mClientObjectHashMap.element.erase(it);

			if (error)
			{
				DYNAMIC_ASSERT(false);
				return false;
			}
			return true;

		}
		return false;
	}
	//--------------------------------------------------------------------------
	ClientObject* ClientManager::getClientObject( Str16 clanName )
	{
		ClientHashMapIt it = mClientObjectHashMap.element.find(clanName);
		if (it != mClientObjectHashMap.element.end())
		{
			return it->second;
		}
		return NULL;
	}
	//--------------------------------------------------------------------------
	/*stdext::hash_map< Str16,ClientObject* >* ClientManager::getClients()
	{
		return (stdext::hash_map< Str16,ClientObject* >*)(&mClientObjectHashMap);
	}*/
	//--------------------------------------------------------------------------
	ClientHashMap& ClientManager::getClients()
	{
		return mClientObjectHashMap;
	}
	//--------------------------------------------------------------------------
	MG::Bool ClientManager::removeClientByFrontServerNetId( I32 frontServerNetId )
	{
		Bool isSuccess = true;
		ClientClassMapIt classSetit = mClientObjectClassSet.element.find(frontServerNetId);
		if (classSetit != mClientObjectClassSet.element.end())
		{
			ClientHashMap& clienMap = classSetit->second;
			if (clienMap.element.empty())
			{
				DYNAMIC_ASSERT(false);
				isSuccess = false;
				mClientObjectClassSet.element.erase(classSetit);	
				return isSuccess;
			}

			ClientHashMapIt clientObjIt = clienMap.element.begin();
			for (; clientObjIt != clienMap.element.end(); clientObjIt++)
			{
				
				ClientObject* clientObj = clientObjIt->second;
				if (clientObj)
				{
					// 先移除mClientObjectHashMap中对应项
					ClientHashMapIt clientObjIt2 = mClientObjectHashMap.element.find(clientObjIt->first);
					if (clientObjIt2 != mClientObjectHashMap.element.end())
					{
						mClientObjectHashMap.element.erase(clientObjIt2);	
					}
					else
					{
						isSuccess = false;
						DYNAMIC_ASSERT(false);
					}
					// 再删除内存
					MG_POOL_DELETE(mClientObjectPool,clientObj);
				}
				else
				{
					DYNAMIC_ASSERT(false);
					isSuccess = false;
				}
			}
			// 最后清空mClientObjectClassSet中对应项
			mClientObjectClassSet.element.erase(classSetit);
			
		}
		return isSuccess;
	}
	//--------------------------------------------------------------------------
}
