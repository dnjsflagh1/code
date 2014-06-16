/******************************************************************************/
#ifndef _ACCOUNTCHECKSTATE_H_
#define _ACCOUNTCHECKSTATE_H_
/******************************************************************************/
#include "BaseState.h"
/******************************************************************************/
namespace MG
{
	class AccountCheckState :public BaseState
	{
	public:
		AccountCheckState(CClient* ower);
		virtual ~AccountCheckState();

	public:
		// 网络事件
		virtual void onNetEvent(INetEvent* netEvent);


		// 操作方法
		virtual void connectLoginServer();
		virtual	void connectFrontServer();
		virtual void accountLoginLoginServer();
		virtual void accountLoginFrontServer();
		virtual void accountLogin();
		virtual void joinGame();
		virtual void autoJoinGame();
		virtual void createClan();
		virtual void createCharacter();
		virtual	void closeNet();
		virtual void randMove();
		virtual void createTroop();
		virtual void sendDataToLoginServer(U32 size);
		virtual void sendDataToFrontServer(U32 size);
		virtual	void testSkill();
		virtual	void createCampagin();
		virtual	void jumpMap();
		virtual void reset();
		// 获取子状态
		virtual	BaseState*		getConnectLoginServerState();
		virtual	BaseState*		getLoginLoginServerState();
		virtual	BaseState*		getConnectFrontServerState();
		virtual	BaseState*		getLoginFrontServerState();
	
		// 设置子状态
		virtual	void			setCurrChildState(BaseState* state);

		virtual std::string&	getClassName();
	private:
		BaseState*					mCurrState;
		BaseState*					mConnectLoginServerState;
		BaseState*					mLoginLoginServerState;
		BaseState*					mConnectFrontServerState;	
		BaseState*					mLoginFrontServerState;
	};
};
/******************************************************************************/
#endif