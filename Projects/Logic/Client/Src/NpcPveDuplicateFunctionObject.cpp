/******************************************************************************/
#include "stdafx.h"
#include "NpcFuctionInfo.h"
#include "NpcPveDuplicateFunctionObject.h"
#include "UIPveCreate.h"
/******************************************************************************/

namespace MG
{
	//----------------------------------------------------------------------------------------
	NpcFuctionObject* NpcPveDuplicteFunctionObject::create( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
	{
		return MG_NEW NpcPveDuplicteFunctionObject(functionInfo,npcCharTempId,characterId);
	}
	//----------------------------------------------------------------------------------------
	MG::Bool NpcPveDuplicteFunctionObject::execute()
	{    
		if (!UIPveCreate::getInstance().isOpen())
		{
            UIPveCreate::getInstance().openGui();
			return true;
		}
	}
	//----------------------------------------------------------------------------------------
	NpcPveDuplicteFunctionObject::NpcPveDuplicteFunctionObject( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
		:NpcFuctionObject(functionInfo,npcCharTempId,characterId)
	{

	}
}