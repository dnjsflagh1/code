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
			addMessage(out_error,"state����ConnectLoginServerState�� op��onNetEvent desc����Login�Ͽ�����");
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
								addMessage(out_error,"state����ConnectLoginServerState�� op��onNetEvent desc��δ֪�ĵ�½����");
								break;
							case LCFT_LOGIN_REDUPLICATE:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state����ConnectLoginServerState�� op��onNetEvent desc���ظ���½");
								break;
							case LCFT_LOGIN_NONE_FRONTSERVER:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state����ConnectLoginServerState�� op��onNetEvent desc��ǰ�˷�����δ����");
								break;
							case LCFT_LOGIN_IDENTITY_ERROR:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state����ConnectLoginServerState�� op��onNetEvent desc���˺Ż��������");
								break;
							case LCFT_LOGIN_IDENTITY_ERROR_MAX:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state����ConnectLoginServerState�� op��onNetEvent desc���˺Ż�����������̫��");
								break;
							case LCFT_LOGIN_LOCK:
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state����ConnectLoginServerState�� op��onNetEvent desc���˺ű�����");
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
							addMessage(out_info,"state����ConnectLoginServerState�� op��onNetEvent desc����¼Login�ɹ�");
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
							mOwer->setOperateFinish(true);addMessage(out_error,"state����ConnectLoginServerState�� op��onNetEvent desc��ǰ�滹��%d�����ڵȴ�",tempData->waitCount);
						}
						break*/;
					case PT_SERVER_S2C_LOGIN_VERSION_ERROR:
						// �汾��ƥ��
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
		addMessage(out_error,"state����ConnectLoginServerState�� op��connectLoginServer desc���Ѿ�����LoginServer");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��connectFrontServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::accountLoginLoginServer()
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����ConnectLoginServerState��  op��accountLoginLoginServer desc�����ô���");
		}
		else
		{
			addMessage(out_info,"state����ConnectLoginServerState��  op��accountLoginLoginServer desc����¼Login��");
			mOwer->stateNetAccountloginLoginServer();
			//mOwer->setState(mOwer->getAccountCheckState());
		}
	
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��accountLoginFrontServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::accountLogin()
	{
		if (hasParentState() && 
			!getParentState()->hasParentState() )
		{
			addMessage(out_info,"state����ConnectLoginServerState��  op��accountLogin desc����¼Login��");
			mOwer->stateNetAccountloginLoginServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����ConnectLoginServerState��  op��accountLogin desc��״̬������");
		}
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��joinGame desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::autoJoinGame()
	{
		if (hasParentState() && 
			getParentState()->hasParentState() )
		{
			addMessage(out_info,"state����ConnectLoginServerState��  op��autoJoinGame desc�� ��¼Login��");
			mOwer->stateNetAccountloginLoginServer();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����ConnectLoginServerState��  op��autoJoinGame desc�� ״̬������");
		}
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��createClan desc�� ״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��createCharacter desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::closeNet()
	{
		addMessage(out_info,"state����ConnectLoginServerState��  op��closeNet desc������ر��� ");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��randMove desc�� ״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��createTroop desc�� ״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::sendDataToLoginServer(U32 size)
	{
		if (!hasParentState())
		{
			addMessage(out_info,"state����ConnectLoginServerState��  op��testSendDataToLoginServer desc���������ݵ�Login");
			mOwer->stateTestSendDataToLoginServer(size);
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state����ConnectLoginServerState��  op��testSendDataToLoginServer desc:  desc�����ô���");
		}
			
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::sendDataToFrontServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��testSendDataToFrontServer desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��testSkill desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��createCampagin desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	void ConnectLoginServerState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state����ConnectLoginServerState��  op��jumpMap desc��״̬������");
	}
	//--------------------------------------------------------------------------------
	std::string& ConnectLoginServerState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/
