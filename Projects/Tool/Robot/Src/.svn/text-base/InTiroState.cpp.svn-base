/******************************************************************************/
#include "stdafx.h"
#include "InTiroState.h"
#include "GameNetEvent.h"
#include "LoginNetPacket.h"
#include "CClientNew.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	InTiroState::InTiroState( CClient* ower )
		:BaseState(ower)
	{
		mClassName = "InTiroState";
	}
	//--------------------------------------------------------------------------------
	InTiroState::~InTiroState()
	{

	}
	//--------------------------------------------------------------------------------
	void InTiroState::onNetEvent( INetEvent* netEvent )
	{
		if (netEvent->getType() == NET_CLOSE)
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【InTiroState】 op：onNetEvent desc：与Front断开连接");
			mOwer->setState(mOwer->getCloseState());
		}
		else
		{
			NetEventRecv* recvEvent = (NetEventRecv*)netEvent;
			if (recvEvent)
			{
				Byte channel = recvEvent->getChannel();
				GameNetPacketData* packetData = (GameNetPacketData*)(recvEvent->getData());
				Byte type = packetData->type;
				void* data = packetData->data;
				if ( channel == GNPC_LOGIN )
				{

				}
			}
				
		}
	}

	//--------------------------------------------------------------------------------
	void InTiroState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：connectLoginServer desc：当前状态不符合");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：connectFrontServer desc：当前状态不符合");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：accountLoginLoginServer desc：当前状态不符合");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：accountLoginFrontServer desc：当前状态不符合");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::accountLogin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：accountLogin desc：当前状态不符合");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：joinGame desc：当前状态不符合");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::autoJoinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：autoJoinGame desc：当前状态不符合");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：createClan desc：当前状态不符合");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：createCharacter desc：当前状态不符合");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::closeNet()
	{
		addMessage(out_info,"state：【InTiroState】  op：closeNet desc：关闭网络中");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void InTiroState::randMove()
	{
		addMessage(out_info,"state：【InTiroState】  op：randMove desc：移动中");
		mOwer->stateRandMove();
	}
	//--------------------------------------------------------------------------------
	void InTiroState::createTroop()
	{
		addMessage(out_info,"state：【InTiroState】  op：createTroop desc：未处理");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：sendDataToLoginServer desc：未处理");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::sendDataToFrontServer(U32 size)
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【InTiroState】  op：testSendDataToFrontServer desc：调用出错");
		}
		else
		{
			mOwer->stateTestSendDataToFrontServer(size);
			addMessage(out_info,"state：【InTiroState】  op：testSendDataToLoginServer desc:  desc：发送数据到Front");
		}
	}
	//--------------------------------------------------------------------------------
	void InTiroState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：testSkill desc：未处理");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：createCampagin desc：未处理");
	}
	//--------------------------------------------------------------------------------
	void InTiroState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【InTiroState】  op：jumpMap desc：未处理");
	}
	//--------------------------------------------------------------------------------
	std::string& InTiroState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/