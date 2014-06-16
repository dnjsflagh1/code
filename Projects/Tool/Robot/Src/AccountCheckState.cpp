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
		addMessage(out_error,"state：【AccountCheckState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：connectFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：accountLoginLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：accountLoginFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::accountLogin()
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【AccountCheckState】  op：accountLogin desc：状态不符合");
		}
		else
		{
			addMessage(out_info,"state：【AccountCheckState】  op：accountLogin desc：进入子状态");
			mCurrState->accountLogin();
		}
		
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：joinGame desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::autoJoinGame()
	{
		if (hasParentState())
		{
			addMessage(out_info,"state：【AccountCheckState】  op：autoJoinGame desc：进入子状态");
			mCurrState->autoJoinGame();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【AccountCheckState】  op：autoJoinGame desc：状态不符合");
		}
		
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：createClan desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：createCharacter desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::closeNet()
	{
		addMessage(out_info,"state：【AccountCheckState】  op：closeNet desc：关闭网络中");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：randMove desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：createTroop desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：testSendDataToLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：testSendDataToFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：testSkill desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：createCampagin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void AccountCheckState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【AccountCheckState】  op：jumpMap desc：状态不符合");
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
