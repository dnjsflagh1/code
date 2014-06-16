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
				addMessage(out_error,"state����ConnectFrontServerState�� op��onNetEvent desc����Front�Ͽ�����");
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
								addMessage(out_error,"state����ConnectFrontServerState�� op��onNetEvent desc��δ֪�ĵ�½ǰ�˷���������");
								mOwer->stateNetClose();
								break;
							case LCFT_LOGIN_SUCCESS:
								addMessage(out_info,"state����ConnectFrontServerState�� op��onNetEvent desc����½ǰ�˷������ɹ�");
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
								addMessage(out_error,"state����ConnectFrontServerState�� op��onNetEvent desc����½ǰ�˷�����ʧ��");
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
		addMessage(out_error,"state����ConnectFrontServerState��  op��connectLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��connectFrontServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��accountLoginLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::accountLoginFrontServer()
	{
		if (!hasParentState())
		{
			addMessage(out_info,"state����ConnectFrontServerState��  op��accountLoginFrontServer desc����¼Front��");
			mOwer->stateNetAccountloginFrontServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����ConnectFrontServerState��  op��accountLoginFrontServer desc��״̬������");
		}
		
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::accountLogin()
	{
		if (hasParentState() && !getParentState()->hasParentState())
		{
			addMessage(out_info,"state����ConnectFrontServerState��  op��accountLogin desc����¼Front��");
			mOwer->stateNetAccountloginFrontServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����ConnectFrontServerState��  op��accountLogin desc��״̬������");
		}
		
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��joinGame desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::autoJoinGame()
	{
		if (hasParentState() && getParentState()->hasParentState())
		{
			addMessage(out_info,"state����ConnectFrontServerState��  op��autoJoinGame desc����¼Front��");
			mOwer->stateNetAccountloginFrontServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����ConnectFrontServerState��  op��autoJoinGame desc��״̬������");
		}
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��createClan desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��createCharacter desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::closeNet()
	{
		addMessage(out_info,"state����ConnectFrontServerState��  op��closeNet desc������ر���");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��randMove desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��createTroop desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��testSendDataToLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��testSendDataToFrontServer desc:  desc�����ô���");
		
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��testSkill desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��createCampagin desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectFrontServerState::jumpMap()
	{	
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectFrontServerState��  op��jumpMap desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	std::string& ConnectFrontServerState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/
