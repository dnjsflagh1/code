/******************************************************************************/
#include "stdafx.h"
#include "NpcFuctionInfo.h"
#include "NpcChangeFightedGerneralFunctionObject.h"
#include "UIChangeRecruit.h"
/******************************************************************************/

namespace MG
{
	//----------------------------------------------------------------------------------------
	NpcFuctionObject* NpcChangeFightedGeneralFuctionObject::create( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
	{
		return MG_NEW NpcChangeFightedGeneralFuctionObject(functionInfo,npcCharTempId,characterId);
	}
	//----------------------------------------------------------------------------------------
	MG::Bool NpcChangeFightedGeneralFuctionObject::execute()
	{    
		if (!UIChangeRecruit::getInstance().isOpen())
		{
			UIChangeRecruit::getInstance().openGui();
			return true;
		}
		  
	}
	//----------------------------------------------------------------------------------------
	NpcChangeFightedGeneralFuctionObject::NpcChangeFightedGeneralFuctionObject( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
		:NpcFuctionObject(functionInfo,npcCharTempId,characterId)
	{

	}
}