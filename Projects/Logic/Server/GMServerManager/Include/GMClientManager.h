/******************************************************************************/
#ifndef _GMCLIENTMANAGER_H_
#define _GMCLIENTMANAGER_H_
/******************************************************************************/
#include "GMCommonData.h"
/******************************************************************************/
namespace MG
{

	/******************************************************************************/
	//GMClient管理 
	/******************************************************************************/
	class GMClientManager
	{
	public:
		SINGLETON_INSTANCE(GMClientManager);
		GMClientManager();
		~GMClientManager();

		//初始化和反初始化
		Bool			initialize();
		void			uninitialize();

		void			processPacket(I32 id,NetEventRecv* packet);
	public:
		Bool			loadFromDb(DBDriver* dbDriver);
		
		void			onGMClientLoginIn( I32 id, Char16* name,Char16* psw );
		void			onGMClientLoginOut(I32 netId);
		void			removeGMDataByGMId(U32 gmId);
		void			clearGMDataSet();

		GMClientInfo*	getGMDataByNetId(U32 netId);
		GMClientInfo*	getGMDataByGMId(U32 gmId);
		GMClientInfo*	getGMDataByGMName(Char16* name);

		
		


		///广播数据
		void            boardcastNetPacketToGMClient(GameNetSendDataBufferPtr packetPtr ,I32 dataSize);

	public:
		std::map<U32,GMClientInfo*> mGMDataSet;

	};
}
#endif