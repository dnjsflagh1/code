/******************************************************************************/
#ifndef _CCLIENT_H_
#define _CCLIENT_H_
/******************************************************************************/
#include "CPlayer.h"
#include "NetAddress.h"
//#include "ClientMessage.h"
#include "State.h"
#include "NetPacketPackManager.h"
#include "BaseState.h"
#include "UIOperateManager.h"

/******************************************************************************/
/* 
	作为机器人 只保留客户端最少量的属性
	测试必要的功能 比如：登录，移动，模仿技能的发送
*/
/******************************************************************************/
namespace MG
{
	enum OpType
	{
		OpType_autoJoinGame,
		OpType_close,
	};
	class CCampaign;
	class CCampaignManager;
	class CClient
	{
	public:
		CClient();
		CClient(I32 index,  Char* service,Char16* accountName,Char16* password,I32 nClan,Int threadIndex);
		~CClient();
	public:
		void				update(Flt delta);

	public:
		// 网络事件 由网络驱动
		void				onNetEvent(INetEvent* netEvent);
		
		// UI事件 由UI驱动
		void 				connectLoginServer();
		void 				connectFrontServer();
		void 				accountLoginLoginServer();
		void 				accountLoginFrontServer();
		void 				accountLogin();
		void 				joinGame();
		void 				autoJoinGame();
		void 				createClan();
		void 				createCharacter();
		void 				closeNet();
		void 				randMove();
		void 				createTroop();
		void 				sendDataToLoginServer(U32 size);
		void 				sendDataToFrontServer(U32 size);
		void 				testSkill();
		void 				createCampagin();
		void 				jumpMap();

	public:

		// 真正做事情的地方 TODO:要放到状态中
		I32					stateConnectLoginServer( NetAddress& addr );
		I32					stateConnectFrontServer( NetAddress& addr );
		void				stateDisconnectLoginServer();
		void				stateDisconnectFrontServer();
		void				stateNetCreateClan();
		void				stateNetCreateCharacter();
		void				stateNetAccountloginLoginServer();
		void				stateNetAccountloginFrontServer();
		void				stateNetJoinGame();
		void				stateNetClose();
		void				stateRandMove();
		void				stateCreateTroop();
		void				stateTestNet(U32 size);
		void				stateTestSendDataToLoginServer(U32 size);
		void				stateTestSendDataToFrontServer(U32 size);
        void                stateNetChat(U32 chatId,I32 size);

		void				stateSendClantSkillRequest();
		void				stateSendEmitterSkillRequest();
		void				stateSendCollisionAffectRequest();
		std::string&		getStateName();

	public:
		void				onLoginServerClose();
		void				onFrontServerClose();

	public:
		//	属性访问接口
		I32					getIndex();
		void				setIndex(I32 index);

		void				setIp(Char* ip);
		Char*				getIp();

		void				setPlayerName(Char16* name);
		Char16*				getPlayerName();
		void				getPlayerNameA(Char8* accountName);
		void				setPlayerPsw(Char16* psw);
		Char16*				getPlayerPsw();

		NetPacketPackManager*getPackManager();

		CPlayer*			getPlayerObj();
		CClan*				getSelectClan();
		U8					getSelectClanIndex();

		void				setFrontServerAddr(NetAddress& addr);
		NetAddress&			getFrontServerAddr();

		I32					getFrontServerNetId();
		void				setFrontServerNetId(I32 netId);
		I32					getLoginServerNetId();
		void				setLoginServerNetId(I32 netId);
		Bool				isDisconnect();



		CCampaign*			getCampaign();
		void				setCampaign(CCampaign* campaign);
		CCampaignManager*	getCampaignManger();
		void				setCampaignManger(CCampaignManager* campaignMgr);

		void				setThreadIndex(Int index);
		Int					getThreadIndex();
		void				setTaskNumber();
		Int					getTaskNumber();

	

		UiOperateManager*	getUiOperateManger();

		Bool				isOperateFinish();
		void				setOperateFinish(Bool isFinish = true);

	private:
		CPlayer						mPlayerObj;
		
		Char						mServerIp[MAX_SERVER_NAME_LEN];
		Char16						mAccountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16						mPassword[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Byte						mSelectClan;
		U8							mSelectClanIndex;
		

		CCampaign*					mCampagin;
		CCampaignManager*			mCampaignManager;


		NetPacketPackManager*		mPackManager;
		I32							mFrontServerId;
		I32							mLoginServerId;
		NetAddress					mFrontServerAddr;
		U64							mNetTestSendNum;



		// 线程索引
		Int							mThreadIndex;
		// 当前任务数
		Int							mTaskNumber;


		Bool						mIsOperateFinish;
		UiOperateManager*			mUiOperateManager;
		OpType						mCurrOp;
		I32							mUiIndex;

public:
		//	状态接口
		void				setState(BaseState* state);
		BaseState*			getCloseState();
		BaseState*			getLoginState();
		BaseState*			getAccountCheckState();
		BaseState*			getConnectLoginServerState();
		BaseState*			getLoginLoginServerState();
		BaseState*			getConnectFrontServerState();
		BaseState*			getLoginFrontServerState();
		BaseState*			getCreateClanState();
		BaseState*			getClanCtrlState();
		BaseState*			getCreateCharacterState();
		BaseState*			getInTiroState();
		BaseState*			getCreateCampaginState();
		BaseState*			getInCampaginState();
		BaseState*			getCurrState();

private:
		// 状态
		BaseState*					mCurrState;
		BaseState*					mCloseState;
		BaseState*					mLoginState;
		BaseState*					mAccountCheckState;
		BaseState*					mConnectLoginServerState;
		BaseState*					mLoginLoginServerState;
		BaseState*					mConnectFrontServerState;	
		BaseState*					mLoginFrontServerState;
		BaseState*					mCreateClanState;
		BaseState*					mClanCtrlState;
		BaseState*					mCreateCharacterState;	
		BaseState*					mInTiroState;
		BaseState*					mCreateCampaginState;
		BaseState*					mInCampaginState;
		


	};
}
#endif //_CCLIENT_H_