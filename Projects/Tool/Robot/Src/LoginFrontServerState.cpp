/******************************************************************************/
#include "stdafx.h"
#include "LoginFrontServerState.h"
#include "CClientNew.h"
#include "GameNetEvent.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
/******************************************************************************/
namespace MG
{
	//--------------------------------------------------------------------------------
	LoginFrontServerState::LoginFrontServerState( CClient* ower )
		:BaseState(ower)
	{
		mClassName = "LoginFrontServerState";
	}
	//--------------------------------------------------------------------------------
	LoginFrontServerState::~LoginFrontServerState()
	{

	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::onNetEvent( INetEvent* netEvent )
	{
		if (netEvent->getType() == NET_CLOSE)
		{
			if (netEvent->getID() == mOwer->getFrontServerNetId())
			{
				mOwer->setOperateFinish(true);
				addMessage(out_error,"state����ConnectFrontServerState�� op��onNetEvent desc����Front�Ͽ�����");
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
					case PT_LOGIN_F2C_OPEN_CREATECLANUI:
						{
							if (hasParentState() && getParentState()->hasParentState())
							{
								getParentState()->getParentState()->setCurrChildState(getParentState()->getParentState()->getCreateClanState());
								mOwer->getCurrState()->autoJoinGame();
							}
							else
							{
								mOwer->setState(mOwer->getCreateClanState());
							}
						}
						break;
					case PT_LOGIN_F2C_OPEN_CLANCONTROLUI:
						{
							if (hasParentState() && getParentState()->hasParentState())
							{
								getParentState()->getParentState()->setCurrChildState(getParentState()->getParentState()->getClanCtrlState());
								mOwer->getCurrState()->autoJoinGame();
							}
							else
							{
								mOwer->setState(mOwer->getClanCtrlState());
							}
						}
						break;
					}
				}
				else if (channel == GNPC_PLAYER)
				{
					switch (type)
					{
					case PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST:
						{
							
						}
						break;
					default:
						{
							DYNAMIC_ASSERT(false);
						}
					}
				}
			}
		}
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��connectLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��connectFrontServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��accountLoginLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��connectLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::accountLogin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��accountLogin desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��joinGame desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::autoJoinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��autoJoinGame desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��createClan desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��createCharacter desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::closeNet()
	{
		addMessage(out_info,"state����LoginFrontServerState��  op��closeNet desc���ر�������");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��randMove desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��createTroop desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��testSendDataToLoginServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��testSendDataToFrontServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��testSkill desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��createCampagin desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void LoginFrontServerState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����LoginFrontServerState��  op��jumpMap desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	std::string& LoginFrontServerState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/
