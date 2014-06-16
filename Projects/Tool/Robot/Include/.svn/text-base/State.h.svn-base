/******************************************************************************/
#ifndef _STATE_H_
#define _STATE_H_
/******************************************************************************/
#include "OperateManager.h"
/******************************************************************************/
namespace MG
{
	//==============================================================================
	struct ClientState
	{
		ClientState();
		~ClientState();
		ClientState& operator=(ClientState& state);
		void clear();

		Bool isRecvLoginSucess;
		Bool isRecvClanList;
		Bool isRecvCreateClan;
		Bool isRecvCreateHero;
		Bool isRecvOpenClan;
		Bool isRecvHeroList;
		Bool isRecvTroopList;
		Bool isRecvJumpRegion;
		Bool isJoinGame;
	};
}
#endif //_STATE_H_