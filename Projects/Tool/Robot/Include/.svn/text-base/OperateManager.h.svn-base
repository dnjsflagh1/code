/******************************************************************************/
#ifndef _OPERATEMANAGER_H_
#define _OPERATEMANAGER_H_
/******************************************************************************/
#include "Operate.h"
#include "ObjectPool.h"
#include "AccountLoginOperate.h"
#include "UseSkillOperate.h"
#include "RandMoveOperate.h"
#include "CreateClanOperate.h"
#include "DeleteClanOperate.h"
#include "JoinGameOperate.h"
#include "AutoJoinGameOperate.h"
#include "CloseOperate.h"
#include "NetTestOperate.h"
#include "CampaignOperate.h"
#include "ChatOperate.h"

/******************************************************************************/
namespace MG
{
	class CClient;
	class OperateManager
	{
	public:
		OperateManager(CClient* client);
		~OperateManager();
		
		void					update();
		CClient*				getClient();
		BaseOperate*			getCurrentOperate();
		void					setCurrentOperate();

		BaseOperate*			createOperate( OperateType optype);
		void					freeOperate(BaseOperate* operate);

		void					setCreateMode(Bool isCreate);
		Bool					getCreateMode();

		void					onNetEvent(Byte channel,Byte type,void* data);
		void					onCloseByLoginServer();
		void					onCloseByFrontServer();

		void					pushOperate(BaseOperate* operate);

		void					clear();

		//get
		CampaignOperate*        getcreateCampaignOperateObject();
		
	private:
		BaseOperate*			mCurrOperate;
		
		CClient*				mClient;
		Critical				mLock;
		std::list<BaseOperate*> mOperates;

		AccountLoginOperate*	mAccountLoginOperate;
		CreateClanOperate*		mCreateClanOperate;
		DeleteClanOperate*		mDeleteClanOperate;
		JoinGameOperate*		mJoinGameOperate;
		CloseOperate*			mCloseOperate;
		AutoJoinGameOperate*	mAutoJoinGameOperate;
		UseSkillOperate*		mUseSkillOperate;
		RandMoveOperate*		mRandMoveOperate;
		NetTestOperate*			mNetTestOperate;
		CreateTroopOperate*		mCreateTroopOperate;
		CampaignOperate*		mCampaignOperate;
		NetTestLoginOperate*	mNetTestLoginOperate;
		ConnectLoginOperate*	mConnectLoginOperate;
		ChatOperate*            mChatOperate;


		Bool					mIsCreateOperate;	

		static ObjectPool<AccountLoginOperate>		mAccountLoginOperatePool;
		static ObjectPool<CreateClanOperate>		mCreateClanOperatePool;
		static ObjectPool<DeleteClanOperate>		mDeleteClanOperatePool;
		static ObjectPool<JoinGameOperate>			mJoinGameOperatePool;
		static ObjectPool<CloseOperate>				mCloseOperatePool;
		static ObjectPool<AutoJoinGameOperate>		mAutoJoinGameOperatePool;
		static ObjectPool<UseSkillOperate>			mUseSkillOperatePool;
		static ObjectPool<RandMoveOperate>			mRandMoveOperatePool;
		static ObjectPool<NetTestOperate>			mNetTestOperatePool;
		static ObjectPool<CreateTroopOperate>		mCreateTroopOperatePool;
		static ObjectPool<CampaignOperate>			mCampaignOperatePool;
		static ObjectPool<NetTestLoginOperate>		mNetTestLoginOperatePool;
		static ObjectPool<ConnectLoginOperate>		mConnectLoginOperatePool;


								
	private:
		/*顺序操作控制变量*/
		MG::Int					    mCurrOperateIndex;
		/*****************/
	};
}
#endif //_OPERATEMANAGER_H_