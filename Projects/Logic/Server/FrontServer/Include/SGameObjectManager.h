//////////////////////////////////////////////////////////////
//
// Copyright (C), 2011, MG Software Co., Ltd. 
//
//      FileName: e:\MGProgram\Trunk\Projects\Server\FrontServer\Include\SGameObjectManager.h
//        Author: yuanlinhu
//          Date: 2012-3-20
//          Time: 10:41
//   Description: 
//			
//
// modify History:
//      <author>    <time>        <descript>
//      yuanlinhu  2012-3-20      add
//////////////////////////////////////////////////////////////

/******************************************************************************/
#ifndef S_GAME_OBJECT_MANAGER_H_
#define S_GAME_OBJECT_MANAGER_H_
/******************************************************************************/

#include "FrontServerPreqs.h"
#include "SPlayer.h"
#include "SClan.h"
#include "SPlayerCharacter.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//GameObject管理者
	/******************************************************************************/
	class SGameObjectManager
	{
		friend class SPlayer;
		friend class SClan;
	public:
		SGameObjectManager();
		~SGameObjectManager();

	public:
		Bool					initialize();
		void					unInitialize();

		void					update();

	public:
		SPlayerPtr										createPlayerFromMemory(NetIdType clientID, Char16* accName, Char16* accPsw, AccountIdType accID);
		void											destroyPlayerFromMemory( SPlayer* pPlayer );
		
		SPlayerPtr										getPlayerByClientNetId(const NetIdType clientNetId);
		SPlayerPtr										getPlayerByAccountId(const AccountIdType accountId);

		void											removePlayerFromList(NetIdType clientNetId);
		void											removePlayerFromList(SPlayerPtr playerPtr);
		void											clearPlayerFromList();

		std::map<NetIdType, SPlayerPtr>*				getPlayerList() { return &mPlayerList; }
		/*void											lockPlayerList();
		void											unLockPlayerList();
		std::map<NetIdType, SPlayerPtr>*				getPlayerList();*/
		
		// 遍历playerlist(多线程版) 
		// 返回值为false表示遍历结束
		// 传入的playerIndex必须为0的左值
		// TODO:测试当另外一个线程删除对象时是否会有问题
		Bool											traversalPlayerList(I32& playerIndex,NetIdType& clientNetId,SPlayerPtr& player);								

	public:
		SClan*											createClanFromMemory( SPlayer* parentPlayer);
		SPlayerCharacter*								createPlayerCharacterFromMemory(PlayerCharacterIdType id, SClan* parentClan);

		//【删除】
		void											destroyClanFromMemory(SClan* clan);
		void											destroyPlayerCharacterFromMemory(SPlayerCharacter* playerCharacter);
		//【清空】
		void											destroyAllClanListFromMemory();
		void											destroyAllPlayerCharacterListFromMemory();

		//SPlayerPtr									getPlayerFromQueue();
		//void											addPlayerToQueue(SPlayerPtr player);

		//检测客户端断开连接
		static void										checkPlayerThread(Ptr ptr); 
	private:
		OneThreadHandle															mCheckPlayerThread;

		std::map<NetIdType, SPlayerPtr>											mPlayerList;
		Critical																mPlayerListCs;

		//std::queue<SPlayerPtr>												mPlayerQueue;
		//Critical																mPlayerQueueCs;

		ObjectPool<SPlayer,false>                                               mSPlayerPool;
		Critical																mPlayerPoolCs;
	
		ObjectPool<SClan,false>												    mSClanPool;
		Critical																mSClanPoolCs;

		ObjectPool<SPlayerCharacter,false>                                      mSPlayerCharacterPool;
		Critical																mSPlayerCharacterPoolCs;


	};
}

#endif	//S_GAME_OBJECT_MANAGER_H_