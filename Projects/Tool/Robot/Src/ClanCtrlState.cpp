/******************************************************************************/
#include "stdafx.h"
#include "ClanCtrlState.h"
#include "CClientNew.h"
#include "GameNetEvent.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
#include "RegionNetPacket.h"
/******************************************************************************/
namespace MG
{
	
	//--------------------------------------------------------------------------------
	ClanCtrlState::ClanCtrlState( CClient* ower )
		:BaseState(ower)
	{
		mClassName =  "ClanCtrlState";
	}
	//--------------------------------------------------------------------------------
	ClanCtrlState::~ClanCtrlState()
	{

	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::onNetEvent( INetEvent* netEvent )
	{
		if (netEvent->getType() == NET_CLOSE)
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ClanCtrlState】 op：onNetEvent desc：与Front断开连接");
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
					case PT_LOGIN_F2C_OPENCRETEGENREALUI:
						{
							if (hasParentState())
							{
								getParentState()->setCurrChildState(getParentState()->getCreateCharacterState());
								mOwer->getCurrState()->autoJoinGame();
							}
							else
							{
								mOwer->setState(mOwer->getCreateCharacterState());
							}
						}
						break;
					}

				}
				else if (channel == GNPC_REGION)
				{
					switch (type)
					{
					case PT_REGION_M2C_ADD_PLAYER_CHARACTER:
						{
							/*PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA* tempData = (PT_REGION_M2C_ADD_PLAYER_CHARACTER_DATA*)data;
							for(Int i = 0; i < tempData->addPlayerNum; ++i)
							{
								CPlayerCharacter* character = mOwer->getPlayerObj()->getPlayerCharacter(tempData->addPlayerInfo[i].character_id);
								if (character)
								{
									mOwer->setState(mOwer->getInTiroState());
								}
							}*/
						}
						break;
					default:
						DYNAMIC_ASSERT(false);
					}
				}
				else if (channel == GNPC_PLAYER_CHARACTER)
				{
					switch(type)
					{
					case PT_PLAYERCHARACTER_F2C_JUMP_REGION:
						{
							PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA* jumpData = (PT_PLAYERCHARACTER_F2C_JUMP_REGION_DATA*)data;
							if (jumpData->jumpResult == ChatarcterJumpRegionResult_Succeed)
							{
								addMessage(out_info,"state：【CreateCharacterState】  op：onNetEvent desc：跳转地图成功，进入新手村");
								mOwer->setState(mOwer->getInTiroState());
							}
							else
							{
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【CreateCharacterState】  op：onNetEvent desc：跳转地图失败,关闭网络中");
								mOwer->stateNetClose();

							}

						}
					}

				}
				else if (channel == GNPC_PLAYER)
				{
					switch(type)
					{
					case PT_PLAYER_F2C_PLAYERCHARACTER_INFO_LIST:
						break;
					default:
						{
							DYNAMIC_ASSERT(false);
						}

					}
				}
				else if (channel == GNPC_LINE_UP)
				{
				}
				else if (channel == GNPC_TEST)
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
	void ClanCtrlState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：accountLoginLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：accountLoginFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::accountLogin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：accountLogin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::joinGame()
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ClanCtrlState】  op：joinGame desc：状态不符合");
		}
		else
		{
			addMessage(out_info,"state：【ClanCtrlState】  op：joinGame desc：进入游戏中");
			mOwer->stateNetJoinGame();
		}
		
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::autoJoinGame()
	{
		if (hasParentState())
		{
			addMessage(out_info,"state：【ClanCtrlState】  op：joinGame desc：进入游戏中");
			mOwer->stateNetJoinGame();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
		}
		
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::createCharacter()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::closeNet()
	{
		addMessage(out_info,"state：【ClanCtrlState】  op：connectLoginServer desc：关闭网络中");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::sendDataToFrontServer(U32 size)
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【ClanCtrlState】  op：testSendDataToFrontServer desc：调用出错");
		}
		else
		{
			mOwer->stateTestSendDataToFrontServer(size);
			addMessage(out_error,"state：【ClanCtrlState】  op：testSendDataToFrontServer desc:  desc：发送数据到Front");
		}
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void ClanCtrlState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【ClanCtrlState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	std::string& ClanCtrlState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/