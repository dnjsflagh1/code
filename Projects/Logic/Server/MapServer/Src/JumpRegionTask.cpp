
//***********************************************************************************************************
#include "stdafx.h"
#include "JumpRegionTask.h"
#include "PlayerNetPacket.h"
#include "SPlayerNetPacketProcesser.h"
#include "PlayerCharacterNetPacket.h"
#include "SPlayerCharacterNetPacketProcesser.h"
#include "MapServerMain.h"
#include "ItemNetPacket.h"
#include "SItemPacketProcesser.h"
#include "ThreadTaskManager.h"
//***********************************************************************************************************

namespace MG
{
    //-----------------------------------------------------------------------
	JumpRegionTask::JumpRegionTask(NetEventRecv* netEvent, I32 netId, U32 key/* = 0*/)
		: ModeTask( U32( TTT_JUMPREGION ),key)
		,mNetEvent(netEvent)
		,mNetId(netId)
	{
	}

    //-----------------------------------------------------------------------
	JumpRegionTask::~JumpRegionTask()
	{

	}

    //-----------------------------------------------------------------------
	I32 JumpRegionTask::getNetId() const
	{
		return mNetId;
	}

    //-----------------------------------------------------------------------
	void JumpRegionTask::process()
	{
		GameNetPacketData* data = (GameNetPacketData*)(mNetEvent->getData());

		if (mNetEvent->getChannel() == GNPC_PLAYER)
		{
			processPlayerPackage(getNetId(), data);
		}
		else if(mNetEvent->getChannel() == GNPC_PLAYER_CHARACTER)
		{
			processPlayerCharacterPackage(getNetId(), data);
		}
		else if( mNetEvent->getChannel() == GNPC_ITEM)
		{
			processItemPackage(getNetId(), data);
		}
	}

    //-----------------------------------------------------------------------
	void JumpRegionTask::free()
	{
        ThreadTaskManager::getInstance().freeJumpRegionTask(this);
	}

    //-----------------------------------------------------------------------
	void JumpRegionTask::processPlayerPackage(I32 id, GameNetPacketData* data)
	{
		switch (data->type)
		{
		case PT_PLAYER_F2M_LOGIN:
			{
				SPlayerNetPacketProcesser::getInstance().onRecvPlayerLogin(getNetId() , (PT_PLAYER_F2M_LOGIN_DATA*)data->data);
			}
			break;
		case PT_PLAYER_F2M_LOGOUT:
			{
				SPlayerNetPacketProcesser::getInstance().onRecvPlayerLogout(getNetId() , (PT_PLAYER_F2M_LOGOUT_DATA*)data->data);
			}
			break;
		case PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST:
			{
				SPlayerNetPacketProcesser::getInstance().onRecvPlayerCharacterList(getNetId(), (PT_PLAYER_F2M_PLAYERCHARACTER_INFO_LIST_DATA*)data->data);
			}
			break;
		case PT_PLAYER_F2M_JUMP_REGION:
			{
				SPlayerNetPacketProcesser::getInstance().onRecvPlayerJumpToRegion(getNetId(), (PT_PLAYER_F2M_JUMP_REGION_DATA*)data->data);
			}
			break;
		case PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID:
			{
				SPlayerNetPacketProcesser::getInstance().onRecvPlayerJumpToRegionByCharId(getNetId(), (PT_PLAYER_F2M_JUMP_REGION_BY_CHAR_ID_DATA*)data->data);
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(0);
			}
			break;
		}
	}

    //-----------------------------------------------------------------------
	void JumpRegionTask::processPlayerCharacterPackage(I32 id, GameNetPacketData* data)
	{
		switch (data->type)
		{
		case PT_PLAYERCHARACTER_F2M_JUMP_REGION:
			{
				SPlayerCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterJumpFromFrontServer(getNetId(), (PT_PLAYERCHARACTER_F2M_JUMP_REGION_DATA*)data->data);
			}
			break;
		case PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION:
			{
				SPlayerCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterJumpCampaignRegionFormFrontServer(getNetId(), (PT_PLAYERCHARACTER_F2M_JUMP_CAMPAIGN_REGION_DATA*)data->data);
			}
			break;
		case PT_PLAYERCHARACTER_F2M_SKILL_INFO:
			{
				SPlayerCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterSkillList(getNetId(), (PT_PLAYERCHARACTER_F2M_SKILL_INFO_DATA*)data->data);
			}
			break;
		case PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION:
			{
				SPlayerCharacterNetPacketProcesser::getInstance().onRecvPlayerCharacterJumpEmptyRegionFromFrontServer(getNetId(), (PT_PLAYERCHARACTER_F2M_JUMP_EMPTY_REGION_DATA*)data->data);
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(0);
			}
			break;
		}
	}

    //-----------------------------------------------------------------------
	void JumpRegionTask::processItemPackage(I32 id, GameNetPacketData* data)
	{
		switch (data->type)
		{
		case PT_ITEM_F2M_EQUIP_LIST:
			{
				SItemPacketProcesser::getInstance().recvEquipList(id, (PT_ITEM_F2M_EQUIP_LIST_DATA*)(data->data));
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(0);
			}
			break;
		}
	}
}
