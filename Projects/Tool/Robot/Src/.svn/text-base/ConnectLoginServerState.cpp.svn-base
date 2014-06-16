/******************************************************************************/
#include "stdafx.h"
#include "ConnectLoginServerState.h"
#include "CClientNew.h"
#include "GameNetEvent.h"
#include "LoginNetPacket.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	ConnectLoginServerState::ConnectLoginServerState( CClient* ower )
		:BaseState(ower)
	{
		mClassName = "ConnectLoginServerState";
	}
	//--------------------------------------------------------------------------------
	ConnectLoginServerState::~ConnectLoginServerState()
	{

	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::onNetEvent( INetEvent* netEvent )
	{
		if (netEvent->getType() == NET_CLOSE)
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ConnectLoginServerState】 op：onNetEvent desc：与Login断开连接");
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
					switch(type)
					{
					case PT_LOGIN_L2C_ACC_LOGIN_FAIL:
						{
							PT_LOGIN_L2C_LOGIN_FAIL_DATA* tempData = (PT_LOGIN_L2C_LOGIN_FAIL_DATA*)data;
							switch(tempData->errResult)
							{
							case LFFT_LOGIN_UNKNOW:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【ConnectLoginServerState】 op：onNetEvent desc：未知的登陆错误");
								break;
							case LCFT_LOGIN_REDUPLICATE:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【ConnectLoginServerState】 op：onNetEvent desc：重复登陆");
								break;
							case LCFT_LOGIN_NONE_FRONTSERVER:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【ConnectLoginServerState】 op：onNetEvent desc：前端服务器未开启");
								break;
							case LCFT_LOGIN_IDENTITY_ERROR:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【ConnectLoginServerState】 op：onNetEvent desc：账号或密码错误");
								break;
							case LCFT_LOGIN_IDENTITY_ERROR_MAX:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【ConnectLoginServerState】 op：onNetEvent desc：账号或密码错误次数太多");
								break;
							case LCFT_LOGIN_LOCK:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【ConnectLoginServerState】 op：onNetEvent desc：账号被锁定");
								break;
							default:
								DYNAMIC_ASSERT(false);
								break;
							}
							mOwer->stateNetClose();
						}
						break;

					case PT_LOGIN_L2C_ACC_LOGIN_SUCCESS:	
						{
							PT_LOGIN_L2C_LOGIN_SUCCESS_DATA* tempData = (PT_LOGIN_L2C_LOGIN_SUCCESS_DATA*)data;
							NetAddress addr(tempData->ip,tempData->port);
							addMessage(out_info,"state：【ConnectLoginServerState】 op：onNetEvent desc：登录Login成功");
							mOwer->setFrontServerAddr(addr);
							if (hasParentState())
							{
								getParentState()->setCurrChildState(getParentState()->getLoginLoginServerState());
								if (getParentState()->hasParentState())
								{
									mOwer->getCurrState()->autoJoinGame();
								}
								else
								{
									
									getParentState()->accountLogin();
								}
									
							}
							else
							{
								mOwer->setState(mOwer->getLoginLoginServerState());
							}
							
							
						}
						break;
					/*case PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO:
						{
							PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA* tempData = (PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO_DATA*)data;
							mOwer->setOperateFinish(true);addMessage(out_error,"state：【ConnectLoginServerState】 op：onNetEvent desc：前面还有%d个人在等待",tempData->waitCount);
						}
						break*/;
					case PT_SERVER_S2C_LOGIN_VERSION_ERROR:
						// 版本不匹配
						DYNAMIC_ASSERT(false);
					default:
						DYNAMIC_ASSERT(false);
						break;
					}
				}
				else if (channel == GNPC_TEST)
				{
					
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
	void ConnectLoginServerState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】 op：connectLoginServer desc：已经连接LoginServer");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：connectFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::accountLoginLoginServer()
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ConnectLoginServerState】  op：accountLoginLoginServer desc：调用错误");
		}
		else
		{
			addMessage(out_info,"state：【ConnectLoginServerState】  op：accountLoginLoginServer desc：登录Login中");
			mOwer->stateNetAccountloginLoginServer();
			//mOwer->setState(mOwer->getAccountCheckState());
		}
	
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：accountLoginFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::accountLogin()
	{
		if (hasParentState() && 
			!getParentState()->hasParentState() )
		{
			addMessage(out_info,"state：【ConnectLoginServerState】  op：accountLogin desc：登录Login中");
			mOwer->stateNetAccountloginLoginServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ConnectLoginServerState】  op：accountLogin desc：状态不符合");
		}
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：joinGame desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::autoJoinGame()
	{
		if (hasParentState() && 
			getParentState()->hasParentState() )
		{
			addMessage(out_info,"state：【ConnectLoginServerState】  op：autoJoinGame desc： 登录Login中");
			mOwer->stateNetAccountloginLoginServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ConnectLoginServerState】  op：autoJoinGame desc： 状态不符合");
		}
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：createClan desc： 状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：createCharacter desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::closeNet()
	{
		addMessage(out_info,"state：【ConnectLoginServerState】  op：closeNet desc：网络关闭中 ");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：randMove desc： 状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：createTroop desc： 状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::sendDataToLoginServer(U32 size)
	{
		if (!hasParentState())
		{
			addMessage(out_info,"state：【ConnectLoginServerState】  op：testSendDataToLoginServer desc：发送数据到Login");
			mOwer->stateTestSendDataToLoginServer(size);
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ConnectLoginServerState】  op：testSendDataToLoginServer desc:  desc：调用错误");
		}
			
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：testSendDataToFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：testSkill desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：createCampagin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ConnectLoginServerState】  op：jumpMap desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	std::string& ConnectLoginServerState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/
