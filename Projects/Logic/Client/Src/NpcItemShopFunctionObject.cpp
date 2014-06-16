/******************************************************************************/
#include "stdafx.h"
#include "NpcFuctionInfo.h"
#include "NpcItemShopFunctionObject.h"
#include "ShopPacketProcesser.h"
/******************************************************************************/
namespace MG
{
	//----------------------------------------------------------------------------------------
	NpcFuctionObject* NpcItemShopFunctionObject::create( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
	{
		return MG_NEW NpcItemShopFunctionObject(functionInfo,npcCharTempId,characterId);
	}
	//----------------------------------------------------------------------------------------
	MG::Bool NpcItemShopFunctionObject::execute()
	{
		if (!mNpcFunctionInfo)
		{
			return false;
		}
	//	if (mNpcFunctionInfo->param2 == ITEMSHOP_OPERATE_TYPE_OPEN_SHOP)
		//{
			ShopPacketProcesser::getInstance().sendOpenShop(mNpcFunctionInfo->param1);
		//}
		return true;
	}
	//----------------------------------------------------------------------------------------
	NpcItemShopFunctionObject::NpcItemShopFunctionObject( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
		:NpcFuctionObject(functionInfo,npcCharTempId,characterId)
	{
		
	}
	//----------------------------------------------------------------------------------------
}