/******************************************************************************/
#include "stdafx.h"
#include "LoginLoginServerState.h"
#include "CClientNew.h"
#include "ThreadTaskManager.h"
#include "GameNetEvent.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	LoginLoginServerState::LoginLoginServerState( CClient* ower )
		:BaseState(ower)
	{
		mClassName = "LoginLoginServerState";
	}
	//--------------------------------------------------------------------------------
	LoginLoginServerState::~LoginLoginServerState()
	{

	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::onNetEvent( INetEvent* netEvent )
	{
		if (netEvent->getType() == NET_CLOSE)
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【LoginLoginServerState】 op：onNetEvent desc：与Login断开连接");
			mOwer->setState(mOwer->getCloseState());
		}
		else
		{
			DYNAMIC_ASSERT(false);
		}
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::connectFrontServer()
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);addMessage(out_error,"state：【LoginLoginServerState】  op：connectLoginServer desc：状态不符合");
		}
		else
		{ 
			ThreadTaskManager::getInstance().lockFrontClients();
			I32 frontServerId = mOwer->stateConnectFrontServer(mOwer->getFrontServerAddr());
			if (frontServerId != INVALID_NET_ID)
			{
				addMessage(out_info,"state：【LoginLoginServerState】  op：connectFrontServer desc：连接Front成功");
				mOwer->setState(mOwer->getConnectFrontServerState());
				ThreadTaskManager::getInstance().addFrontClient(frontServerId,mOwer);
				ThreadTaskManager::getInstance().unlockFrontClients();
			}
			else
			{
				ThreadTaskManager::getInstance().unlockFrontClients();
				mOwer->setOperateFinish(true);
				addMessage(out_error,"state：【LoginLoginServerState】  op：connectFrontServer desc：登录Front中");
			}
			
		}
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：accountLoginLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：accountLoginFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::accountLogin()
	{
		
		if(hasParentState() && !getParentState()->hasParentState())
		{
			ThreadTaskManager::getInstance().lockFrontClients();
			I32 frontServerId = mOwer->stateConnectFrontServer(mOwer->getFrontServerAddr());
			if (frontServerId != INVALID_NET_ID)
			{
				addMessage(out_info,"state：【LoginLoginServerState】  op：connectFrontServer desc：连接Front成功");
				//getParentState()->setState(getParentState()->getParentState())
				ThreadTaskManager::getInstance().addFrontClient(frontServerId,mOwer);
				getParentState()->setCurrChildState(getParentState()->getConnectFrontServerState());
				ThreadTaskManager::getInstance().unlockFrontClients();
				mOwer->getCurrState()->accountLogin();
			}
			else
			{
				ThreadTaskManager::getInstance().unlockFrontClients();
				mOwer->setOperateFinish(true);
				addMessage(out_error,"state：【LoginLoginServerState】  op：connectFrontServer desc：连接Front失败");
			}

		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【LoginLoginServerState】  op：connectLoginServer desc：状态不符合");
		}
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：joinGame desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::autoJoinGame()
	{
		if (hasParentState() && getParentState()->hasParentState())
		{
			ThreadTaskManager::getInstance().lockFrontClients();
			I32 frontServerId = mOwer->stateConnectFrontServer(mOwer->getFrontServerAddr());
			if (frontServerId != INVALID_NET_ID)
			{
				addMessage(out_info,"state：【LoginLoginServerState】  op：autoJoinGame desc：连接Front成功");
				ThreadTaskManager::getInstance().addFrontClient(frontServerId,mOwer);
				getParentState()->setCurrChildState(getParentState()->getConnectFrontServerState());
				ThreadTaskManager::getInstance().unlockFrontClients();
				mOwer->getCurrState()->autoJoinGame();
			}
			else
			{
				ThreadTaskManager::getInstance().unlockFrontClients();
				mOwer->setOperateFinish(true);
				addMessage(out_error,"state：【LoginLoginServerState】  op：autoJoinGame desc：连接Front失败");
				mOwer->stateNetClose();
			}
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【LoginLoginServerState】  op：autoJoinGame desc：状态不符合");
		}
			
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：createClan desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：createCharacter desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::closeNet()
	{
		addMessage(out_info,"state：【LoginLoginServerState】  op：createCharacter desc：关闭网络中");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：randMove desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：createTroop desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::sendDataToLoginServer(U32 size)
	{
		//mOwer->setOperateFinish(true);addMessage(out_error,"state：【LoginLoginServerState】  op：testSendDataToLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：testSendDataToFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：testSkill desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：createCampagin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void LoginLoginServerState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【LoginLoginServerState】  op：jumpMap desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	std::string& LoginLoginServerState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/
