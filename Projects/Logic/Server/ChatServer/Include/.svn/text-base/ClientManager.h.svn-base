/******************************************************************************/
#ifndef _CLIENTMANAGER_H_
#define _CLIENTMANAGER_H_
/******************************************************************************/

#include "LoginNetPacket.h"

/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//客户端对象
	/******************************************************************************/
	class ClientObject
	{
	public:
		I32					netIdInFrontServer;
		I32					frontServerNetId;
		U64					accountId;
		ClientObject(I32 netIdInFrontServer, I32 frontServerNetId,U64 accountId)

		{
			this->netIdInFrontServer = netIdInFrontServer;
			this->frontServerNetId = frontServerNetId;
			this->accountId = accountId;
		}
	};

	
	/******************************************************************************/
	// 解决C4503警告
	/******************************************************************************/
	struct  ClientHashMap
	{
		stdext::hash_map< Str16,ClientObject* > element;
	};
	struct ClientClassMap
	{
		stdext::hash_map< I32, ClientHashMap > element;
	};

    /******************************************************************************/
    //客户端管理
	//# 负责管理还未登入的客户端对象，主要职责为检测客户端登入超时。
    /******************************************************************************/
    class ClientManager
    {
    public:
        SINGLETON_INSTANCE(ClientManager);
        ClientManager();
        virtual ~ClientManager();
    public:
		// 初始化和反初始化
        Bool    initialize();
        void    uninitialize();
	protected:
		//typedef stdext::hash_map< Str16,ClientObject* > ClientHashMap;
		typedef stdext::hash_map< Str16,ClientObject* >::iterator ClientHashMapIt;
		//typedef stdext::hash_map< I32, ClientHashMap >	ClientClassMap;
		typedef stdext::hash_map< I32, ClientHashMap >::iterator ClientClassMapIt;
	public:
		// 获得客户端对象表 以便外部操作
		//stdext::hash_map< Str16,ClientObject* >* getClients();
		ClientHashMap& getClients();

		// 添加 移除 获得 客户端对象
		Bool			addClientObject(Str16 clanName,I32 netIdInFrontServer,I32 frontServerNetId,U64 accountId);
		Bool			removeClientObject(Str16 clanName);
		Bool			removeClientByFrontServerNetId(I32 frontServerNetId);
		ClientObject*	getClientObject(Str16 clanName);
		
		// 设置客户端对象属性 比如 组队，势力


	private:
		ObjectPool<ClientObject>											mClientObjectPool;
		// <clanName，Client>
		//stdext::hash_map< Str16, ClientObject* >							mClientObjectHashMap;
		// <FrontServerNetId, clientMap> 按照前台服务器网络ID分类的客户端集合 
		//stdext::hash_map< I32, stdext::hash_map< Str16,ClientObject* > >	mClientObjectClassSet;

		ClientHashMap										mClientObjectHashMap;	
		ClientClassMap										mClientObjectClassSet;
    };
}
#endif