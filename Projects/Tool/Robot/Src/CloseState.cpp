/******************************************************************************/
#include "stdafx.h"
#include "CloseState.h"
#include "CClientNew.h"
#include "ThreadTaskManager.h"
#include "GameNetEvent.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
/******************************************************************************/
namespace MG
{
	
	//--------------------------------------------------------------------------------
	CloseState::CloseState( CClient* ower )
		:BaseState(ower)
	{
		DYNAMIC_ASSERT(ower);
		mClassName =  "CloseState";
	}
	//--------------------------------------------------------------------------------
	CloseState::~CloseState()
	{

	}
	//--------------------------------------------------------------------------------
	void CloseState::onNetEvent( INetEvent* netEvent )
	{
		if (netEvent->getType() == NET_CLOSE)
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����CloseState�� op��onNetEvent desc����Login�Ͽ�����");
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
					/*case PT_LOGIN_L2C_ACC_LOGIN_QUEUE_INFO:
						break;*/
					default:
						DYNAMIC_ASSERT(false);
					}
				}
				else if (channel == GNPC_PLAYER_CHARACTER)
				{
					// Ϊʲô���������Ϣ��
					// TODO
					switch(type)
					{
						
					case PT_PLAYERCHARACTER_F2C_SKILL_INFO:
						break;
					case PT_PLAYERCHARACTER_F2C_JUMP_REGION:
							break;
					default:
						DYNAMIC_ASSERT(false);
					}
				}
				else if (channel == GNPC_PLAYER)
				{
					switch(type)
					{
					case PT_PLAYER_F2C_JUMP_REGION:
						break;
					default:
						DYNAMIC_ASSERT(false);
					}
				}
				else if (channel == GNPC_REGION)
				{

				}
				else
				{
					//DYNAMIC_ASSERT(false);
				}
			}
		}
	}
	//--------------------------------------------------------------------------------
	void CloseState::connectLoginServer()
	{
		addMessage(out_info,"state����CloseState�� op��connectLoginServer desc������Login��");
		NetAddress addr(mOwer->getIp(),LOGINSERVER_PORT);
		ThreadTaskManager::getInstance().lockLoginClients();
		I32 loginServerId = mOwer->stateConnectLoginServer(addr);
		if (loginServerId != INVALID_NET_ID)
		{
			addMessage(out_info,"state����CloseState�� op��connectLoginServer desc������Login�ɹ�");
			ThreadTaskManager::getInstance().addLoginClient(loginServerId,mOwer);
			mOwer->setState(mOwer->getConnectLoginServerState());
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����CloseState�� op��connectLoginServer desc������Loginʧ��");
		}
		ThreadTaskManager::getInstance().unlockLoginClients();	
	}
	//--------------------------------------------------------------------------------
	void CloseState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��connectFrontServer desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��accountLoginLoginServer desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��accountLoginFrontServer desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::accountLogin()
	{
		addMessage(out_info,"state����CloseState�� op��accountLogin desc������Login��");
		NetAddress addr(mOwer->getIp(),LOGINSERVER_PORT);
		ThreadTaskManager::getInstance().lockLoginClients();
		I32 loginServerId = mOwer->stateConnectLoginServer(addr);
		if (loginServerId != INVALID_NET_ID)
		{
			addMessage(out_info,"state����CloseState�� op��accountLogin desc������Login�ɹ�");
			ThreadTaskManager::getInstance().addLoginClient(loginServerId,mOwer);
			mOwer->setState(mOwer->getAccountCheckState());
			ThreadTaskManager::getInstance().unlockLoginClients();
			mOwer->getCurrState()->accountLogin();
		}
		else
		{
			ThreadTaskManager::getInstance().unlockLoginClients();
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����CloseState�� op��accountLogin desc������Login��");
		}
		
	}

	//--------------------------------------------------------------------------------
	void CloseState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��joinGame desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::autoJoinGame()
	{
		addMessage(out_info,"state����CloseState�� op��autoJoinGame desc������Login��");
		NetAddress addr(mOwer->getIp(),LOGINSERVER_PORT);
		ThreadTaskManager::getInstance().lockLoginClients();
		I32 loginServerId = mOwer->stateConnectLoginServer(addr);
		if (loginServerId != INVALID_NET_ID)
		{
			addMessage(out_info,"state����CloseState�� op��autoJoinGame desc������Login�ɹ�");
			ThreadTaskManager::getInstance().addLoginClient(loginServerId,mOwer);
			mOwer->setState(mOwer->getLoginState());
			ThreadTaskManager::getInstance().unlockLoginClients();
			mOwer->getCurrState()->autoJoinGame();
		}
		else
		{
			ThreadTaskManager::getInstance().unlockLoginClients();
		}
	}
	//--------------------------------------------------------------------------------
	void CloseState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��createClan desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��createCharacter desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::closeNet()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��closeNet desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��randMove desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��createTroop desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��testSendDataToLoginServer desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��testSendDataToFrontServer desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��testSkill desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��createCampagin desc����ǰ״̬������");
	}
	//--------------------------------------------------------------------------------
	void CloseState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����CloseState�� op��jumpMap desc����ǰ״̬������");
	}

	std::string& CloseState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/
