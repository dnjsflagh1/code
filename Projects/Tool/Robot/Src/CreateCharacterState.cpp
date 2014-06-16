/******************************************************************************/
#include "stdafx.h"
#include "CreateCharacterState.h"
#include "CClientNew.h"
#include "GameNetEvent.h"
#include "RegionNetPacket.h"
#include "PlayerCharacterNetPacket.h"
#include "LoginNetPacket.h"
#include "PlayerNetPacket.h"
/******************************************************************************/
namespace MG
{
	
	//--------------------------------------------------------------------------------
	CreateCharacterState::CreateCharacterState( CClient* ower )
		:BaseState(ower)
	{
		mClassName = "CreateCharacterState";
	}
	//--------------------------------------------------------------------------------
	CreateCharacterState::~CreateCharacterState()
	{

	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::onNetEvent( INetEvent* netEvent )
	{
		if (netEvent->getType() == NET_CLOSE)
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【CreateCharacterState】 op：onNetEvent desc：与Front断开连接");
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
					case PT_LOGIN_F2C_CREATE_GENERAL_RESULT:
						{
							PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA* result = (PT_LOGIN_F2C_CREATE_GENERAL_RESULT_DATA*)data;
							if (result->result == CreateGenrealResult_Succeed)
							{
								mOwer->stateNetJoinGame();
							}
							else
							{
								mOwer->setOperateFinish(true);
								addMessage(out_error,"state：【CreateCharacterState】  op：onNetEvent desc：创建角色失败，关闭网络中");
								mOwer->stateNetClose();

							}
						}
						break;
						/*case PT_LOGIN_F2C_OPENCRETEGENREALUI:
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
						if (hasParentState())
						{
						getParentState()->setCurrChildState(getParentState()->getClanCtrlState());
						}
						else
						{
						mOwer->setState(mOwer->getClanCtrlState());
						mOwer->getCurrState()->autoJoinGame();
						}

						}
						break;*/
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
								addMessage(out_error,"state：【CreateCharacterState】  op：onNetEvent desc：跳转地图失败，关闭网络中");
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
						DYNAMIC_ASSERT(false);
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
	void CreateCharacterState::connectLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::connectFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：connectFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::accountLoginLoginServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：accountLoginLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::accountLoginFrontServer()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：accountLoginFrontServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::accountLogin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：accountLogin desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::joinGame()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：joinGame desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::autoJoinGame()
	{
		if (hasParentState())
		{
			addMessage(out_info,"state：【CreateCharacterState】  op：autoJoinGame desc：创建角色中");
			mOwer->stateNetCreateCharacter();
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【CreateCharacterState】  op：autoJoinGame desc：状态不符合");
		}
		
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::createClan()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::createCharacter()
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：状态不符合");
		}
		else
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：创建角色中");
			mOwer->stateNetCreateCharacter();
		}
		
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::closeNet()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：closeNet desc：关闭游戏中");
		//mOwer->setState(mOwer->getCloseState());
		mOwer->stateNetClose();
		
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::randMove()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::createTroop()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::sendDataToLoginServer(U32 size)
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::sendDataToFrontServer(U32 size)
	{
		if (hasParentState())
		{
			mOwer->setOperateFinish(true);
			addMessage(out_error,"state：【CreateCharacterState】  op：testSendDataToFrontServer desc：调用出错");
		}
		else
		{
			mOwer->stateTestSendDataToFrontServer(size);
			addMessage(out_info,"state：【CreateCharacterState】  op：testSendDataToFrontServer desc:  desc：发送数据到Front");
		}
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::testSkill()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::createCampagin()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	void CreateCharacterState::jumpMap()
	{
		mOwer->setOperateFinish(true);
		addMessage(out_error,"state：【CreateCharacterState】  op：connectLoginServer desc：状态不符合");
	}
	//--------------------------------------------------------------------------------
	std::string& CreateCharacterState::getClassName()
	{
		return mClassName;
	}
};
/******************************************************************************/
