/******************************************************************************/
#ifndef _BASESTATE_H_
#define _BASESTATE_H_
/******************************************************************************/

/******************************************************************************/
namespace MG
{
	class INetEvent;
	class CClient;
	class BaseState
	{
	public:
		BaseState(CClient* ower);
		virtual ~BaseState();

	public:
		// 网络事件
		virtual void			onNetEvent(INetEvent* netEvent) = 0;
		

		// 操作方法
		virtual void 			connectLoginServer() = 0;
		virtual	void 			connectFrontServer() = 0;
		virtual void 			accountLoginLoginServer() = 0;
		virtual void 			accountLoginFrontServer() = 0;
		virtual void 			accountLogin() = 0;
		virtual void 			joinGame() = 0;
		virtual void 			autoJoinGame() = 0;
		virtual void 			createClan() = 0;
		virtual void 			createCharacter() = 0;
		virtual	void 			closeNet() = 0;
		virtual void 			randMove() = 0;
		virtual void 			createTroop() = 0;
		virtual void 			sendDataToLoginServer(U32 size) = 0;
		virtual void 			sendDataToFrontServer(U32 size) = 0;
		virtual	void 			testSkill() = 0;
		virtual	void 			createCampagin() = 0;
		virtual	void 			jumpMap() = 0;
		
		// 设置父状态
		void					setParentState(BaseState* state);
		BaseState*				getParentState();
		Bool					hasParentState();

		virtual		void		reset(){;}
		virtual		std::string&getClassName() = 0;	
		// 获得子状态
		virtual	BaseState*		getCloseState();
		virtual	BaseState*		getLoginState();
		virtual	BaseState*		getAccountCheckState();
		virtual	BaseState*		getConnectLoginServerState();
		virtual	BaseState*		getLoginLoginServerState();
		virtual	BaseState*		getConnectFrontServerState();
		virtual	BaseState*		getLoginFrontServerState();
		virtual	BaseState*		getCreateClanState();
		virtual	BaseState*		getClanCtrlState();
		virtual	BaseState*		getCreateCharacterState();
		virtual	BaseState*		getInTiroState();
		virtual	BaseState*		getCreateCampaginState();
		virtual	BaseState*		getInCampaginState();

		virtual	void			setCurrChildState(BaseState*);

		virtual	void			addMessage(LOG_TYPE outType, CChar* fmt, ...);


	protected:
		// 状态的拥有者
		CClient*		mOwer;
		BaseState*		mParentState;
		std::string		mClassName;

	};
}
/******************************************************************************/
#endif