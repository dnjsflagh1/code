#include "stdafx.h"
#include "State.h"
/******************************************************************************/

namespace MG
{
	//--------------------------------------------------------------------------
	ClientState::ClientState()
		:isRecvLoginSucess(false)
		,isRecvClanList(false)
		,isRecvCreateClan(false)
		,isRecvCreateHero(false)
		,isRecvOpenClan(false)
		,isRecvHeroList(false)
		,isRecvJumpRegion(false)
		,isRecvTroopList(false)
		,isJoinGame(false)
	{

	}
	//--------------------------------------------------------------------------
	ClientState::~ClientState()
	{

	}
	//--------------------------------------------------------------------------
	ClientState& ClientState::operator=(ClientState& state)
	{
		isRecvLoginSucess = state.isRecvLoginSucess;
		isRecvClanList = state.isRecvClanList;
		isRecvCreateClan = state.isRecvCreateClan;
		isRecvCreateHero = state.isRecvCreateHero;
		isRecvOpenClan = state.isRecvOpenClan;
		isRecvHeroList = state.isRecvHeroList;
		isRecvJumpRegion = state.isRecvJumpRegion;
		isRecvTroopList = state.isRecvTroopList;
		isJoinGame = state.isJoinGame;
		return *this;
	}
	//--------------------------------------------------------------------------
	void ClientState::clear()
	{
		isRecvLoginSucess = false;
		isRecvClanList = false;
		isRecvCreateClan = false;
		isRecvCreateHero = false;
		isRecvOpenClan = false;
		isRecvHeroList = false;
		isRecvTroopList = false;
		isRecvJumpRegion = false;
		isJoinGame = false;
	}

	//--------------------------------------------------------------------------

}