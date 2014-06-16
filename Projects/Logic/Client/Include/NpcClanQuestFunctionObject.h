/******************************************************************************/
#ifndef _NPCCLANQUESTFUNCTIONOBJECT_H_
#define _NPCCLANQUESTFUNCTIONOBJECT_H_
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
	class NpcClanQuestFunctionObject : public NpcFuctionObject
	{
	public:
		static NpcFuctionObject* create(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId);
		virtual Bool			execute();	
	
	private:
		NpcClanQuestFunctionObject(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType  characterId);
	};
}

/******************************************************************************/
#endif
