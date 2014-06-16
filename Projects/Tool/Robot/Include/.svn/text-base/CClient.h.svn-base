/******************************************************************************/
#ifndef _CCLIENT_H_
#define _CCLIENT_H_
/******************************************************************************/
#include "CPlayer.h"
#include "NetAddress.h"
#include "ClientMessage.h"
#include "State.h"
#include "NetPacketPackManager.h"
/******************************************************************************/
/* 作为机器人 只保留客户端最少量的属性
测试必要的功能 比如：登录，移动，模仿技能的发送
*/
/******************************************************************************/
namespace MG
{
	class CCampaign;
	class CClient
	{
	public:
		CClient();
		CClient(I32 index,  Char* service,Char16* accountName,Char16* password,I32 nClan,Int threadIndex);
		~CClient();
	public:
		void				update(Flt delta);

	public:
		I32					connectLoginServer( NetAddress& addr );
		I32					connectFrontServer( NetAddress& addr );
		void				disconnectLoginServer();
		void				disconnectFrontServer();
		void				netCreateClan();
		void				netCreateCharacter();
		void				netAccountloginLoginServer();
		void				netAccountloginFrontServer();
		void				netJoinGame();
		void				netClose();
		void				randMove();
		void				createTroop();
		void				testNet();
		void				testSendDataToLoginServer(U32 size);
        void                netChat(U32 chatId,I32 size);

		void				sendClantSkillRequest();
		void				sendEmitterSkillRequest();
		void				sendCollisionAffectRequest();

	public:
		void				onLoginServerClose();
		void				onFrontServerClose();

	public:
		void				setPlayerName(Char16* name);
		Char16*				getPlayerName();
		void				setPlayerPsw(Char16* psw);
		Char16*				getPlayerPsw();
		void				setIp(Char* ip);
		Char*				getIp();

		CClientMessage*		getClientMessage();
		CPlayer*			getPlayerObj();
		CClan*				getSelectClan();
		U8					getSelectClanIndex();
		ClientState&		getState();
		OperateManager*		getOperateManager();
		NetPacketPackManager*getPackManager();

		I32					getFrontServerNetId();
		void				setFrontServerNetId(I32 netId);
		I32					getLoginServerNetId();
		void				setLoginServerNetId(I32 netId);
		Bool				isDisconnect();

		I32					getIndex();
		void				setIndex(I32 index);

		CCampaign*			getCampaign();
		void				setCampaign(CCampaign* campaign);

		void				setThreadIndex(Int index);
		Int					getThreadIndex();

		// for test
		void				setTaskNumber();
		Int					getTaskNumber();

	private:
		CPlayer						mPlayerObj;
		OperateManager*				mManager;
		CClientMessage*				mMessage;
		ClientState					mState;
		CCampaign*					mCampagin;
		NetPacketPackManager*		mPackManager;

		Critical					mOperateLock;
		U8							mSelectClanIndex;
		I32							mUiIndex;

		I32							mFrontServerId;
		I32							mLoginServerId;

		Char						mServerIp[MAX_SERVER_NAME_LEN];
		Char16						mAccountName[MAX_ACCOUNT_LONGIN_NAME_LEN];
		Char16						mPassword[MAX_ACCOUNT_LONGIN_PSW_LEN];
		Byte						mSelectClan;
		U64							mNetTestSendNum;

		Int							mThreadIndex;
		Int							mTaskNumber;
	};
}
#endif //_CCLIENT_H_