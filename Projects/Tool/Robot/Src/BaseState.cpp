/******************************************************************************/
#include "stdafx.h"
#include "BaseState.h"
#include "CClientNew.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	BaseState::BaseState( CClient* ower )
	{
		DYNAMIC_ASSERT(mOwer);
		mOwer = ower;
		mParentState = NULL;
		mClassName = "BaseState";
	}
	//--------------------------------------------------------------------------------
	void BaseState::setParentState( BaseState* state )
	{
		DYNAMIC_ASSERT(state);
		mParentState = state;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getParentState()
	{
		return mParentState;
	}
	//--------------------------------------------------------------------------------
	BaseState::~BaseState()
	{
		mParentState = NULL;
		mOwer = NULL;
	}
	//--------------------------------------------------------------------------------
	void BaseState::addMessage( LOG_TYPE outType, CChar* fmt, ... )
	{
		va_list vl;
		Char msg[2048];
		msg[2047] = 0;
		va_start( vl, fmt );
		vsprintf_s( msg, fmt, vl );
		va_end( vl );
		Char8 playerName[64] = {0};
		mOwer->getPlayerNameA(playerName);
		//MG_LOG(outType,"Íæ¼Ò:¡¾%s¡¿%s\n",playerName,msg);
	}
	//--------------------------------------------------------------------------------
	Bool BaseState::hasParentState()
	{
		return mParentState != NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getCloseState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getLoginState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getAccountCheckState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getConnectLoginServerState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getLoginLoginServerState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getConnectFrontServerState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getLoginFrontServerState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getCreateClanState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getClanCtrlState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getCreateCharacterState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getInTiroState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getCreateCampaginState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	BaseState* BaseState::getInCampaginState()
	{
		return NULL;
	}
	//--------------------------------------------------------------------------------
	void BaseState::setCurrChildState( BaseState* )
	{

	}
	//--------------------------------------------------------------------------------
}