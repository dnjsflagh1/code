/******************************************************************************/
#ifndef _NPCPVPBATTLEFUNCTIONOBJECT_H_
#define _NPCPVPBATTLEFUNCTIONOBJECT_H_
/******************************************************************************/
#include "WorldCorePreqs.h"
#include "NpcFunctionObject.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//游戏Npc功能对象
	/******************************************************************************/
	// NCP家族任务
	class NpcPvpBattleFunctionObject : public NpcFuctionObject
	{
	public:
		static NpcFuctionObject* create(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId);
		virtual Bool			execute();	

	private:
		NpcPvpBattleFunctionObject(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType  characterId);
	};
}

/******************************************************************************/
#endif
