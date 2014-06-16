/******************************************************************************/
#include "stdafx.h"
#include "NpcFuctionInfo.h"
#include "CPlayer.h"
#include "QuestNetPacketProcesser.h"
#include "UINpc.h"
#include "CClanQuestManager.h"
#include "NpcClanQuestFunctionObject.h"
#include "ClanQuestInfoBase.h"
#include "QuestList.h"
#include "QuestValueChange.h"
#include "UIMessageBox.h"
/******************************************************************************/
namespace MG
{

	NpcClanQuestFunctionObject::NpcClanQuestFunctionObject( NpcFunctionInfo* functionInfo,U32 npcCharTempId, IdType characterId )
		:NpcFuctionObject(functionInfo,npcCharTempId,characterId)
	{
		
	}
	//----------------------------------------------------------------------------------------
	MG::Bool NpcClanQuestFunctionObject::execute()
	{
		CClan* clan = CPlayer::getInstance().getActiveClan();
		if (!clan || !mNpcFunctionInfo)
		{
			return false;
		}
		if (mNpcFunctionInfo->param2 == QUEST_OPERATE_TYPE_ACCEPT)
		{
			UINpc::getInstance().openNpcQuestDialog(mNpcFunctionInfo->param1,NPC_QUEST_STATE_ACCEPT);
			return true;
		}
		else if (mNpcFunctionInfo->param2 == QUEST_OPERATE_TYPE_SUBMIT)
		{
			if(!CClanQuestManager::getInstance().canSubmit(mNpcFunctionInfo->param1))
			{
				UINpc::getInstance().openNpcQuestDialog(mNpcFunctionInfo->param1,NPC_QUEST_STATE_UNCOMMIT);	
			}
			else
			{
				UINpc::getInstance().openNpcQuestDialog(mNpcFunctionInfo->param1,NPC_QUEST_STATE_COMMIT);	
			}
				
			return true;
		}
		/*
		else if(mNpcFunctionInfo->param2 == QUEST_OPERATE_TYPE_SUBMIT_AND_ACCEPT)
		{
			
			if(CClanQuestManager::getInstance().canAccept(mNpcFunctionInfo->param1))	
			{
				UINpc::getInstance().openNpcQuestDialog(mNpcFunctionInfo->param1,NPC_QUEST_STATE_ACCEPT);
				return true;
			}
			else if (CClanQuestManager::getInstance().canSubmit(mNpcFunctionInfo->param1))
			{
				UINpc::getInstance().openNpcQuestDialog(mNpcFunctionInfo->param1,NPC_QUEST_STATE_COMMIT);
				return true;
			}
			else
			{
				UINpc::getInstance().openNpcQuestDialog(mNpcFunctionInfo->param1,NPC_QUEST_STATE_UNCOMMIT);
				return true;
			}
		}
		*/
		else if(mNpcFunctionInfo->param2 == QUEST_OPERATE_TYPE_TALK)
		{
			ClanQuestObject* questObj = CClanQuestManager::getInstance().getQuest(mNpcFunctionInfo->param1);
			if (questObj && questObj->mRecord.state == QUEST_COMPLETE_STATE_ACCEPTED)
			{
				UINpc::getInstance().openNpcQuestDialog(mNpcFunctionInfo->param1,NPC_QUEST_STATE_TALK);
			}
			else
			{
				UIMessageBox::getInstance().showHint(L"无法完成和Npc对话");
				return false;
			}
		}
		else
		{
			return false;
		}

	}

	//----------------------------------------------------------------------------------------
	NpcFuctionObject* NpcClanQuestFunctionObject::create( NpcFunctionInfo* functionInfo,U32 npcCharTempId,IdType characterId )
	{
		if (functionInfo == NULL 
			|| functionInfo->type != NPC_FUCTION_TYPE_CLAN_QUEST
			|| characterId == 0)
		{
			return NULL;
		}

		CClan* clan = CPlayer::getInstance().getActiveClan();
		if (!clan)
		{
			DYNAMIC_ASSERT(false);
			return NULL;
		}
		//只显示能够接受 或者 已经接受的任务 
		if (functionInfo->param2 == QUEST_OPERATE_TYPE_ACCEPT)
		{
			if(!CClanQuestManager::getInstance().canAccept(functionInfo->param1))
			{
				return NULL;
			}
		}
		else if (functionInfo->param2 == QUEST_OPERATE_TYPE_SUBMIT)
		{
			ClanQuestObject* questObj = CClanQuestManager::getInstance().getQuest(functionInfo->param1);
			if (questObj)
			{
			}
			else
			{
				return NULL;
			}
		}
		/*
		else if(functionInfo->param2 == QUEST_OPERATE_TYPE_SUBMIT_AND_ACCEPT)
		{
			if(!CClanQuestManager::getInstance().canAccept(functionInfo->param1))
			{
				return NULL;
			}
			
		}
		*/
		else if (functionInfo->param2 == QUEST_OPERATE_TYPE_TALK)
		{
			ClanQuestObject* questObj = CClanQuestManager::getInstance().getQuest(functionInfo->param1);
			if (!questObj 
				|| questObj->mRecord.state != QUEST_COMPLETE_STATE_ACCEPTED)
			{
				return NULL;
			}
			std::vector<QuestValueChangeInfo*> changeValues;
			if(questObj->mInfo->questInfo->getValueChangeGroupInfo(changeValues) < 1)
			{
				return NULL;
			}
			Bool haveTalk = false;
			for(std::vector<QuestValueChangeInfo*>::iterator it = changeValues.begin(); it != changeValues.end(); it++)
			{
				if ((*it)->type == CHANGE_TYPE_TALK_TO_NPC)
				{
					haveTalk = true;
					break;
				}
			}
			if (!haveTalk)
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
		
		return MG_NEW NpcClanQuestFunctionObject(functionInfo,npcCharTempId,characterId);
	}

}