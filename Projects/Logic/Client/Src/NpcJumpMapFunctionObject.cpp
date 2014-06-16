/******************************************************************************/
#include "stdafx.h"
#include "NpcFuctionInfo.h"
#include "NpcFunctionObject.h"
#include "NpcJumpMapFunctionObject.h"
#include "QuestNetPacketProcesser.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "CPlayer.h"
#include "PlayerNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{
	NpcFuctionObject* NpcJumpMapFunctionObject::create( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
	{
		return MG_NEW NpcJumpMapFunctionObject(functionInfo,npcCharTempId,characterId);
	}

	MG::Bool NpcJumpMapFunctionObject::execute()
	{
		if (!mNpcFunctionInfo)
		{
			return false;
		}
		Int param4_point;
		MGStrOp::toI32(mNpcFunctionInfo->param4.c_str(),param4_point);
		PlayCharacterNetPacketProcesser::getInstance().jumpMapForUI(mPlayerCharacterId,(MapType)mNpcFunctionInfo->param1,
			(RegionIdType)mNpcFunctionInfo->param2,mNpcFunctionInfo->param3, param4_point);
		
		//Íæ¼ÒÉãÏñ»úÌøµØÍ¼
		//const AccountIdType accountId = CPlayer::getInstance().getAccountID();
		//PlayerNetPacketProcesser::getInstance().sendPlayerEnterRegionByCharId(accountId,mPlayerCharacterId);

		return true;
	}

	NpcJumpMapFunctionObject::NpcJumpMapFunctionObject( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
		:NpcFuctionObject(functionInfo,npcCharTempId,characterId)
	{
		
	}

}