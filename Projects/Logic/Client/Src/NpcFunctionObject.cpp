/******************************************************************************/
#include "stdafx.h"
#include "NpcFuctionInfo.h"
#include "NpcFunctionObject.h"
/******************************************************************************/
namespace MG
{
	NpcFuctionObject::NpcFuctionObject( NpcFunctionInfo* functionInfo,U32 npcCharTempId, IdType characterId )
	{
		mNpcFunctionInfo = functionInfo;
		mPlayerCharacterId = characterId;
		mNpcCharTempId = npcCharTempId;
	}
}