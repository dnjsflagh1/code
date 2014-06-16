/******************************************************************************/
#ifndef _NPCJUMPMAPFUNCTIONOBJECT_H_
#define _NPCJUMPMAPFUNCTIONOBJECT_H_
/******************************************************************************/
#include "WorldCorePreqs.h"
#include "NpcFunctionObject.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//游戏Npc功能对象
	/******************************************************************************/
	class NpcJumpMapFunctionObject : public NpcFuctionObject
	{
	public:
		static NpcFuctionObject*	create(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId);
		virtual Bool				execute();	
	private:
		NpcJumpMapFunctionObject(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType  characterId);
	};
	//-------------------------------------------------------------------------------------------------
}

/******************************************************************************/
#endif
