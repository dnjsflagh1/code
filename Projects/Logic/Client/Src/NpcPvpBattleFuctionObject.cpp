/******************************************************************************/
#include "stdafx.h"
#include "NpcFuctionInfo.h"
#include "NpcPvpBattleFuctionObject.h"
#include "UICampaignSystemNew.h"
/******************************************************************************/

namespace MG
{
	//----------------------------------------------------------------------------------------
	NpcFuctionObject* NpcPvpBattleFunctionObject::create( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
	{
		return MG_NEW NpcPvpBattleFunctionObject(functionInfo,npcCharTempId,characterId);
	}
	//----------------------------------------------------------------------------------------
	MG::Bool NpcPvpBattleFunctionObject::execute()
	{    
		UICampaignSystemNew::getInstance().openGui();
		return true;
	}
	//----------------------------------------------------------------------------------------
	NpcPvpBattleFunctionObject::NpcPvpBattleFunctionObject( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
		:NpcFuctionObject(functionInfo,npcCharTempId,characterId)
	{

	}
}