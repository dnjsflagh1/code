/******************************************************************************/
#ifndef _INTIROSTATE_H_
#define _INTIROSTATE_H_
/******************************************************************************/
#include "BaseState.h"
/******************************************************************************/
namespace MG
{
	class InTiroState : public BaseState
	{
	public:
		InTiroState(CClient* ower);
		virtual ~InTiroState();

	public:
		// ÍøÂçÊÂ¼þ
		virtual void onNetEvent(INetEvent* netEvent);

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

		virtual std::string&	getClassName();

	};
};
/******************************************************************************/
#endif