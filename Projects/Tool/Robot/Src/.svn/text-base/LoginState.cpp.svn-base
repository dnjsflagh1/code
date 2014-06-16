/******************************************************************************/
#include "stdafx.h"
#include "LoginState.h"
#include "AccountCheckState.h"
#include "CreateClanState.h"
#include "ClanCtrlState.h"
#include "CreateCharacterState.h"
#include "CClientNew.h"
/******************************************************************************/
namespace MG
{
	
	//--------------------------------------------------------------------------------
	LoginState::LoginState( CClient* ower )
		:BaseState(ower)
	{
		mAccountCheckState		= MG_NEW AccountCheckState(ower);
		mCreateClanState		= MG_NEW CreateClanState(ower);
		mClanCtrlState			= MG_NEW ClanCtrlState(ower);
		mCreateCharacterState	= MG_NEW CreateCharacterState(ower);
		mCurrState				= mAccountCheckState;
		mAccountCheckState->setParentState(this);			
		mCreateClanState->setParentState(this);		
		mClanCtrlState->setParentState(this);			
		mCreateCharacterState->setParentState(this);	
		mClassName = "LoginState";
		
	}
	//--------------------------------------------------------------------------------
	LoginState::~LoginState()
	{
		mCurrState = NULL;
		MG_SAFE_DELETE(mAccountCheckState	);
		MG_SAFE_DELETE(mCreateClanState	);
		MG_SAFE_DELETE(mClanCtrlState		);
		MG_SAFE_DELETE(mCreateCharacterState);
	}
	//--------------------------------------------------------------------------------
	void LoginState::onNetEvent( INetEvent* netEvent )
	{
		mCurrState->onNetEvent(netEvent);
	}
	//--------------------------------------------------------------------------------
	void LoginState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：connectFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：accountLoginLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：accountLoginFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::accountLogin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：accountLogin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：joinGame desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::autoJoinGame()
	{
		addMessage(out_info,"state：【LoginState】  op：autoJoinGame desc：进入子状态");
		mCurrState->autoJoinGame();
		
	}
	//--------------------------------------------------------------------------------
	void LoginState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：createClan desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：createCharacter desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::closeNet()
	{
		addMessage(out_info,"state：【LoginState】  op：closeNet desc：关闭网络中");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void LoginState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：randMove desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：createTroop desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：testSendDataToLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：testSendDataToFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：testSkill desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：createCampagin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginState】  op：jumpMap desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	BaseState* LoginState::getAccountCheckState()
	{
		return mAccountCheckState;
	}
	//--------------------------------------------------------------------------------
	BaseState* LoginState::getCreateClanState()
	{
		return mCreateClanState;
	}
	//--------------------------------------------------------------------------------
	BaseState* LoginState::getClanCtrlState()
	{
		return mClanCtrlState;
	}
	//--------------------------------------------------------------------------------
	BaseState* LoginState::getCreateCharacterState()
	{
		return mCreateCharacterState;
	}
	//--------------------------------------------------------------------------------
	void LoginState::setCurrChildState( BaseState* state )
	{
		DYNAMIC_ASSERT(
			state == mAccountCheckState
			|| state == mCreateClanState
			|| state == mClanCtrlState
			|| mCreateCharacterState);
		mCurrState = state;
	}

	void LoginState::reset()
	{
		mAccountCheckState->reset();
		mCurrState = mAccountCheckState;
	}
	//--------------------------------------------------------------------------------
	std::string& LoginState::getClassName()
	{
		return mCurrState->getClassName();
	}
};						
/******************************************************************************/
