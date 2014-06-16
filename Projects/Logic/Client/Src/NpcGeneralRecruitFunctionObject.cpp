/******************************************************************************/
#include "stdafx.h"
#include "NpcFuctionInfo.h"
#include "CGeneralRecruitNetPacketProcessor.h"
#include "NpcGeneralRecruitFunctionObject.h"
#include "UIRecruitGeneral.h"
/******************************************************************************/

namespace MG
{
	//----------------------------------------------------------------------------------------
	NpcFuctionObject* NpcGeneralRecruitFunctionObject::create( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
	{
		return MG_NEW NpcGeneralRecruitFunctionObject(functionInfo,npcCharTempId,characterId);
	}
	//----------------------------------------------------------------------------------------
	MG::Bool NpcGeneralRecruitFunctionObject::execute()
	{
		if ((mNpcFunctionInfo != NULL) && (mNpcFunctionInfo->param1 != 0))
		{
			UIRecruitGeneral::getInstance().setGeneralRecruitId(mNpcFunctionInfo->param1);
			//CGeneralRecruitNetPacketProcessor::getInstance().sendGetRandomGeneralList(mNpcFunctionInfo->param1);
			return true;
		}
		return false;
		
	}
	//----------------------------------------------------------------------------------------
	NpcGeneralRecruitFunctionObject::NpcGeneralRecruitFunctionObject( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
		:NpcFuctionObject(functionInfo,npcCharTempId,characterId)
	{

	}
}