/******************************************************************************/
#include "stdafx.h"
#include "CreateClanState.h"
#include "CClientNew.h"
#include "GameNetEvent.h"
#include "LoginNetPacket.h"
/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------------
	CreateClanState::CreateClanState( CClient* ower )
		:BaseState(ower)
	{
		mClassName = "CreateClanState";
	}
	//--------------------------------------------------------------------------------
	CreateClanState::~CreateClanState()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateClanState::onNetEvent( INetEvent* netEvent )
	{
		if (netEvent->getType() == NET_CLOSE)
		{	
			if (netEvent->getID() == mOwer->getFrontServerNetId())
			{
				mOwer->setOperateFinish(true);
				addMessage(out_error,"state：【CreateClanState】 op：onNetEvent desc：与Front断开连接");
				mOwer->setState(mOwer->getCloseState());
			}	
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
					switch(type)
					{
					case PT_LOGIN_F2C_OPEN_CLANCONTROLUI:
						if (hasParentState())
						{
							getParentState()->setCurrChildState(getParentState()->getClanCtrlState());
							mOwer->getCurrState()->autoJoinGame();
						}
						else
						{
							mOwer->setState(mOwer->getClanCtrlState());
						}
						break;
					case PT_LOGIN_F2C_CREATE_CLAN_RESULT:
						{
							PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA* tempData = (PT_LOGIN_F2C_CREATE_CLAN_RESULT_DATA*)data;
							if(tempData->result == CreateClanResult_Succeed)
							{
								addMessage(out_info,"state：【CreateClanState】  op：onNetEvent desc：创建家族成功");
							}
							else
							{
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【CreateClanState】  op：onNetEvent desc：创建家族失败");
								mOwer->stateNetClose();
							}
						}
						break;
					}
				}
				else if (channel == GNPC_LINE_UP)
				{
				}
				else
				{
					DYNAMIC_ASSERT(false);
				}
			}
		}
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：connectFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：accountLoginLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：accountLoginFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::accountLogin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：accountLogin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：joinGame desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::autoJoinGame()
	{
		
		if (hasParentState())
		{
			addMessage(out_info,"state：【CreateClanState】  op：autoJoinGame desc：创建家族中");
			mOwer->stateNetCreateClan();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【CreateClanState】  op：autoJoinGame desc：状态不符合");
		}
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::createClan()
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【CreateClanState】  op：createClan desc：状态不符合");
		}
		else
		{
			addMessage(out_info,"state：【CreateClanState】  op：createClan desc：创建家族中");
			mOwer->stateNetCreateClan();
		}
		
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：createCharacter desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::closeNet()
	{
		addMessage(out_info,"state：【CreateClanState】  op：closeNet desc：关闭网络中");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：randMove desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：createTroop desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：testSendDataToLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::sendDataToFrontServer(U32 size)
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【CreateClanState】  op：testSendDataToFrontServer desc：调用出错");
		}
		else
		{
			mOwer->stateTestSendDataToFrontServer(size);
			addMessage(out_info,"state：【CreateClanState】  op：testSendDataToLoginServer desc:  desc：发送数据到Front");
		}
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：testSkill desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：createCampagin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateClanState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateClanState】  op：jumpMap desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	std::string& CreateClanState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/
