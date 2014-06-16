/******************************************************************************/
#ifndef _NPCITEMSHOPFUNCTIONOBJECT_H_
#define _NPCITEMSHOPFUNCTIONOBJECT_H_
/******************************************************************************/
#include "WorldCorePreqs.h"
#include "NpcFunctionObject.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//��ϷNpc���ܶ���
	/******************************************************************************/
	// NCP�̵�
	class NpcItemShopFunctionObject : public NpcFuctionObject
	{
	public:
		static NpcFuctionObject* create(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId);
		virtual Bool	execute();
	private:
		NpcItemShopFunctionObject(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType  characterId);
	};
	//-------------------------------------------------------------------------------------------------
}

/******************************************************************************/
#endif
