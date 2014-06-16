/******************************************************************************/
#ifndef _LOGINSTATE_H_
#define _LOGINSTATE_H_
/******************************************************************************/
#include "BaseState.h"
/******************************************************************************/
namespace MG
{
	class LoginState : public BaseState
	{
	public:
		LoginState(CClient* ower);
		virtual ~LoginState();

	public:
		// 网络事件
		virtual void onNetEvent(INetEvent* netEvent);
		
		/******************************************************************************/
		// 操作方法
		virtual void 			connectLoginServer();
		virtual	void 			connectFrontServer();
		virtual void 			accountLoginLoginServer();
		virtual void 			accountLoginFrontServer();
		virtual void 			accountLogin();
		virtual void 			joinGame();
		virtual void 			autoJoinGame();
		virtual void 			createClan();
		virtual void 			createCharacter();
		virtual	void 			closeNet();
		virtual void 			randMove();
		virtual void 			createTroop();
		virtual void 			sendDataToLoginServer(U32 size);
		virtual void 			sendDataToFrontServer(U32 size);
		virtual	void 			testSkill();
		virtual	void 			createCampagin();
		virtual	void 			jumpMap();

		virtual void			reset();
		/******************************************************************************/
		// 子状态
		virtual	BaseState*		getAccountCheckState();
		virtual	BaseState*		getCreateClanState();
		virtual	BaseState*		getClanCtrlState();
		virtual	BaseState*		getCreateCharacterState();
	
		virtual	void			setCurrChildState(BaseState* state);
		/******************************************************************************/
		virtual std::string&	getClassName();
	private:	
		// 当前子状态
		BaseState*		mCurrState;
		
		// 子状态
		BaseState*		mAccountCheckState;
		BaseState*		mCreateClanState;
		BaseState*		mClanCtrlState;
		BaseState*		mCreateCharacterState;

	};
};
/******************************************************************************/
#endif