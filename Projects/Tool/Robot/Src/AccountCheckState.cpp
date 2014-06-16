/******************************************************************************/
#include "stdafx.h"
#include "AccountCheckState.h"
#include "GameNetEvent.h"
#include "CClientNew.h"
#include "LoginNetPacket.h"
#include "ThreadTaskManager.h"
#include "PlayerNetPacket.h"

#include "ConnectLoginServerState.h"
#include "LoginLoginServerState.h"
#include "ConnectFrontServerState.h"
#include "LoginFrontServerState.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	AccountCheckState::AccountCheckState( CClient* ower )
		:BaseState(ower)
	{
		mConnectLoginServerState	= MG_NEW ConnectLoginServerState(ower);
		mLoginLoginServerState		= MG_NEW LoginLoginServerState(ower);
		mConnectFrontServerState	= MG_NEW ConnectFrontServerState(ower);
		mLoginFrontServerState		= MG_NEW LoginFrontServerState(ower);
		mCurrState					= mConnectLoginServerState;

		mConnectLoginServerState->setParentState(this);
		mLoginLoginServerState->setParentState(this);
		mConnectFrontServerState->setParentState(this);
		mLoginFrontServerState->setParentState(this);
		
		mClassName =  "AccountCheckState";
	}
	//--------------------------------------------------------------------------------
	AccountCheckState::~AccountCheckState()
	{
		mCurrState = NULL;
		MG_SAFE_DELETE(mConnectLoginServerState);
		MG_SAFE_DELETE(mLoginLoginServerState);
		MG_SAFE_DELETE(mConnectFrontServerState);
		MG_SAFE_DELETE(mLoginFrontServerState);
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::onNetEvent( INetEvent* netEvent )
	{
		mCurrState->onNetEvent(netEvent);
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��connectLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��connectFrontServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��accountLoginLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��accountLoginFrontServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::accountLogin()
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����AccountCheckState��  op��accountLogin desc��״̬������");
		}
		else
		{
			addMessage(out_info,"state����AccountCheckState��  op��accountLogin desc��������״̬");
			mCurrState->accountLogin();
		}
		
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��joinGame desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::autoJoinGame()
	{
		if (hasParentState())
		{
			addMessage(out_info,"state����AccountCheckState��  op��autoJoinGame desc��������״̬");
			mCurrState->autoJoinGame();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����AccountCheckState��  op��autoJoinGame desc��״̬������");
		}
		
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��createClan desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��createCharacter desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::closeNet()
	{
		addMessage(out_info,"state����AccountCheckState��  op��closeNet desc���ر�������");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��randMove desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��createTroop desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��testSendDataToLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��testSendDataToFrontServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��testSkill desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��createCampagin desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����AccountCheckState��  op��jumpMap desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	BaseState* AccountCheckState::getConnectLoginServerState()
	{
		return mConnectLoginServerState;
	}
	//--------------------------------------------------------------------------------
	BaseState* AccountCheckState::getLoginLoginServerState()
	{
		return mLoginLoginServerState;
	}
	//--------------------------------------------------------------------------------
	BaseState* AccountCheckState::getConnectFrontServerState()
	{
		return mConnectFrontServerState;
	}
	//--------------------------------------------------------------------------------
	BaseState* AccountCheckState::getLoginFrontServerState()
	{
		return mLoginFrontServerState;
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::setCurrChildState( BaseState* state)
	{
		DYNAMIC_ASSERT(
			state == mConnectLoginServerState 
			|| state == mLoginLoginServerState 
			|| state == mConnectFrontServerState 
			|| state == mLoginFrontServerState);
		mCurrState = state;
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::reset()
	{
		mCurrState = mConnectLoginServerState;
	}
	//--------------------------------------------------------------------------------
	std::string& AccountCheckState::getClassName()
	{
		return mCurrState->getClassName();
	}
};
/******************************************************************************/
