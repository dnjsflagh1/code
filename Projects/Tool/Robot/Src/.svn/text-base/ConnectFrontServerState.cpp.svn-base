/******************************************************************************/
#include "stdafx.h"
#include "ConnectFrontServerState.h"
#include "CClientNew.h"
#include "GameNetEvent.h"
#include "LoginNetPacket.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	ConnectFrontServerState::ConnectFrontServerState( CClient* ower )
		:BaseState(ower)
	{
		mClassName = "ConnectFrontServerState";
	}
	//--------------------------------------------------------------------------------
	ConnectFrontServerState::~ConnectFrontServerState()
	{

	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::onNetEvent( INetEvent* netEvent )
	{
		if (netEvent->getType() == NET_CLOSE)
		{	
			if (netEvent->getID() == mOwer->getFrontServerNetId())
			{
				addMessage(out_error,"state：【ConnectFrontServerState】 op：onNetEvent desc：与Front断开连接");
				mOwer->setState(mOwer->getCloseState());
				mOwer->setOperateFinish(true);
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
					case PT_LOGIN_F2C_ACC_LOGIN_RESULT:
						{
							PT_LOGIN_F2C_LOGIN_RESULT_DATA* tempData = (PT_LOGIN_F2C_LOGIN_RESULT_DATA*)data;
							switch(tempData->result)
							{
							case LCFT_LOGIN_UNKNOW:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【ConnectFrontServerState】 op：onNetEvent desc：未知的登陆前端服务器错误");
								mOwer->stateNetClose();
								break;
							case LCFT_LOGIN_SUCCESS:
								addMessage(out_info,"state：【ConnectFrontServerState】 op：onNetEvent desc：登陆前端服务器成功");
								if (hasParentState())
								{
									getParentState()->setCurrChildState(getParentState()->getLoginFrontServerState());
								}
								else
								{
									mOwer->setState(mOwer->getLoginFrontServerState());
								}
								break;
							case LCFT_LOGIN_FAIL:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【ConnectFrontServerState】 op：onNetEvent desc：登陆前端服务器失败");
								mOwer->stateNetClose();
								break;
							}

						}
						break;
					/*case PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO:
						break;*/
					default:
						DYNAMIC_ASSERT(false);
					}
				}
				else if ( channel == GNPC_LINE_UP )
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
	void ConnectFrontServerState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：connectFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：accountLoginLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::accountLoginFrontServer()
	{
		if (!hasParentState())
		{
			addMessage(out_info,"state：【ConnectFrontServerState】  op：accountLoginFrontServer desc：登录Front中");
			mOwer->stateNetAccountloginFrontServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ConnectFrontServerState】  op：accountLoginFrontServer desc：状态不符合");
		}
		
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::accountLogin()
	{
		if (hasParentState() && !getParentState()->hasParentState())
		{
			addMessage(out_info,"state：【ConnectFrontServerState】  op：accountLogin desc：登录Front中");
			mOwer->stateNetAccountloginFrontServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ConnectFrontServerState】  op：accountLogin desc：状态不符合");
		}
		
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：joinGame desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::autoJoinGame()
	{
		if (hasParentState() && getParentState()->hasParentState())
		{
			addMessage(out_info,"state：【ConnectFrontServerState】  op：autoJoinGame desc：登录Front中");
			mOwer->stateNetAccountloginFrontServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ConnectFrontServerState】  op：autoJoinGame desc：状态不符合");
		}
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：createClan desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：createCharacter desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::closeNet()
	{
		addMessage(out_info,"state：【ConnectFrontServerState】  op：closeNet desc：网络关闭中");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：randMove desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：createTroop desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：testSendDataToLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：testSendDataToFrontServer desc:  desc：调用错误");
		
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：testSkill desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：createCampagin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::jumpMap()
	{	
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectFrontServerState】  op：jumpMap desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	std::string& ConnectFrontServerState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/
