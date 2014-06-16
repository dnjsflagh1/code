/******************************************************************************/
#ifndef _CLIENTMANAGER_H_
#define _CLIENTMANAGER_H_
/******************************************************************************/
#include "ClientPreqs.h"
#include "DataSetManager.h"
#include "Singleton.h"
#include "CClient.h"
#include "Operate.h"
/******************************************************************************/
namespace MG
{

	class ClientManager
	{
		typedef I32 loginNetId;
		typedef I32 frontNetId;
		typedef I32	indexType;
	public:
		SINGLETON_INSTANCE(ClientManager);
		ClientManager();
		~ClientManager();

	public:
		Bool									initialize();
		Bool									isInit();	

		CClient*								createOrRetrieve(I32 index,  Char* service,Char16* accountName,Char16* password,I32 nClan);
		CClient*								getNextClient();
		
		void									pushOperate(OperateType optype);
		
		void									addClientToLoginMap(loginNetId netId,CClient* client);
		void									addClientToFrontMap(frontNetId netId,CClient* client);
		Bool									removeClientFormLoginMap(loginNetId netId);
		Bool									removeClientFormFrontMap(frontNetId netId);

		CClient*								getClientbyLoginServerId(I32 netId);
		CClient*								getClientbyFrontServerId(I32 netId);

		map<I32,CClient*>*						getDataSet();
		SimpleMapDataSetManager<I32, CClient>*	getClients();
		map<frontNetId,CClient*>*				getFrontClients();
		void									closeAll();
		
		void									lockClients();
		void									unLockClients();


		//
		Bool									isAllCreatCampaignFinish();

	public:
		void									update(Flt delta);

	private:
		//I32 表示 Index
		SimpleMapDataSetManager<indexType, CClient>		mClients;
		Bool											mInited;
		Critical										mClientsLock;

		//I32 表示 网络Id
		std::map<loginNetId,CClient*>					mClientLoginMap;
		std::map<frontNetId,CClient*>					mClientFrontMap;

		U32												mLastTick;


	};
}
#endif