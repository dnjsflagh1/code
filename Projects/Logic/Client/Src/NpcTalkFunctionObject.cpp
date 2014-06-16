/******************************************************************************/
#include "stdafx.h"
#include "NpcFuctionInfo.h"
#include "NpcFunctionObject.h"
#include "NpcTalkFunctionObject.h"
#include "QuestNetPacketProcesser.h"
/******************************************************************************/
namespace MG
{
	NpcFuctionObject* NpcTalkFunctionObject::create( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
	{
		return MG_NEW NpcTalkFunctionObject(functionInfo,npcCharTempId,characterId);
	}

	MG::Bool NpcTalkFunctionObject::execute()
	{
		if (!mNpcFunctionInfo)
		{
			return false;
		}
		if (mNpcFunctionInfo->param2 == ITEMSHOP_OPERATE_TYPE_OPEN_SHOP)
		{
			//ShopPacketProcesser::getInstance().sendOpenShop(mNpcFunctionInfo->param1);
		}
		return true;
	}

	NpcTalkFunctionObject::NpcTalkFunctionObject( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
		:NpcFuctionObject(functionInfo,npcCharTempId,characterId)
	{
		
	}

}