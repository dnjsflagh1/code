/******************************************************************************/
#ifndef _NPCGENERALRECRUTIFUNCTIONOBJECT_H_
#define _NPCGENERALRECRUTIFUNCTIONOBJECT_H_
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
	class NpcGeneralRecruitFunctionObject : public NpcFuctionObject
	{
	public:
		static NpcFuctionObject* create(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId);
		virtual Bool			execute();	

	private:
		NpcGeneralRecruitFunctionObject(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType  characterId);
	};
}

/******************************************************************************/
#endif
