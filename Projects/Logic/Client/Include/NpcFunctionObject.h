/******************************************************************************/
#ifndef _NPCFUCTIONOBJECT_H_
#define _NPCFUCTIONOBJECT_H_
/******************************************************************************/
#include "WorldCorePreqs.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//��ϷNpc���ܶ���
	/******************************************************************************/
	struct NpcFunctionInfo;
	class NpcFuctionObject
	{
	public:
		NpcFuctionObject(NpcFunctionInfo* functionInfo,U32 npcCharTempId, IdType characterId);
		virtual Bool			execute() = NULL;
		NpcFunctionInfo*		mNpcFunctionInfo;
		IdType					mPlayerCharacterId;
		U32						mNpcCharTempId;
	};

	/******************************************************************************/
	//��ϷNpc���������ܶ���
	/******************************************************************************/
	enum QUEST_OPERATE_TYPE
	{
		QUEST_OPERATE_TYPE_NULL = 0,
		QUEST_OPERATE_TYPE_ACCEPT,
		QUEST_OPERATE_TYPE_SUBMIT,
		QUEST_OPERATE_TYPE_FAILED_REACCEPT,
		QUEST_OPERATE_TYPE_TALK,
	};
	//-------------------------------------------------------------------------------------------------
	enum ITEMSHOP_OPERATE_TYPE
	{
		ITEMSHOP_OPERATE_TYPE_NULL = 0,
		ITEMSHOP_OPERATE_TYPE_OPEN_SHOP,
	};
    
}

/******************************************************************************/
#endif
