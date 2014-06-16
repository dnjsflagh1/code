/******************************************************************************/
#ifndef _NPCTALKFUNCTIONOBJECT_H_
#define _NPCTALKFUNCTIONOBJECT_H_
/******************************************************************************/
#include "WorldCorePreqs.h"
#include "NpcFunctionObject.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//��ϷNpc���ܶ���
	/******************************************************************************/
	class NpcTalkFunctionObject : public NpcFuctionObject
	{
	public:
		static NpcFuctionObject*	create(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId);
		virtual Bool				execute();	
	private:
		NpcTalkFunctionObject(NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType  characterId);
	};
	//-------------------------------------------------------------------------------------------------
}

/******************************************************************************/
#endif
