/******************************************************************************/
#include "stdafx.h"
#include "CClanQuestManager.h"
#include "QuestNetPacketProcesser.h"
#include "QuestList.h"
#include "CPlayer.h"
#include "UIMessageBox.h"
#include "UINpc.h"
#include "UIQuestManager.h"
#include "ItemPacketProcesser.h"
#include "ItemGroupTemplate.h"
#include "QuestNormalList.h"
#include "QuestText.h"
#include "GameJudge.h"
/******************************************************************************/
namespace MG
{


	void CClanQuestManager::acceptClanQuest( U32 questInfoId,PlayerCharacterIdType charId)
	{
        Bool success = true;
		static Char16 str[64] = {0};
		Str16 hintStr; 
		showQuestHintStr(questInfoId, hintStr);
        
		if (!canAccept(questInfoId))
		{    
			 MGStrOp::sprintf(str,64,L"接受【%s】任务失败",hintStr.c_str());
             success = false;
		}
		if (success)
		{   
			GAMEJUDGE_TYPE gudgeType = questGameJudge(questInfoId);
            if (gudgeType != GAMEJUDGE_TYPE_SUCCESS)
            {
                 success = false;
            }
			else
			{
                if (gudgeType == GAMEJUDGE_TYPE_CLAN_COMPLETE_QUEST_ERROR)
                {
                       MGStrOp::sprintf(str,64,L"接受【%s】任务失败\n需要完成指定任务!",hintStr.c_str());
                }
				else if (gudgeType == GAMEJUDGE_TYPE_CLAN_LEVEL_ERROR)
				{
                      MGStrOp::sprintf(str,64,L"接受【%s】任务失败\n等级不够!",hintStr.c_str());
				}
				
			}
            
		}

        if (success)
        {
               QuestNetPacketProcesser::getInstance().sendAcceptQuest(questInfoId,charId);
        }
		else
		{
			  UIMessageBox::getInstance().showHint(str);
		}
		
	}

	void CClanQuestManager::submitClanQuest( U32 questInfoId )
	{
		Bool success = canSubmit(questInfoId);
		if (success)
		{
			QuestNetPacketProcesser::getInstance().sendSubmitQuest(questInfoId);
		}
		else
		{
			static Char16 str[64] = {0};
			Str16 hintStr; 
			showQuestHintStr(questInfoId, hintStr);
			
			MGStrOp::sprintf(str,64,L"提交【%s】任务失败",hintStr.c_str());
			UIMessageBox::getInstance().showHint(str);
			
		}
	}

	void CClanQuestManager::giveupClanQuest( U32 questInfoId )
	{
		Bool success = canGiveup(questInfoId);
		if (success)
		{
			QuestNetPacketProcesser::getInstance().sendGiveupQuest(questInfoId);
		}
		else
		{
			static Char16 str[64] = {0};
			Str16 hintStr; 
			showQuestHintStr(questInfoId, hintStr);
			
			MGStrOp::sprintf(str,64,L"放弃【%s】任务失败",hintStr.c_str());
			UIMessageBox::getInstance().showHint(str);
			
		}
	}

	void CClanQuestManager::handleAcceptQuestResult( U32 questInfoId ,PT_QUEST_F2C_ACCEPT_RESULT result)
	{
		
		Str16 hintStr; 
		showQuestHintStr(questInfoId, hintStr);
		static Char16 str[64] = {0};
		switch (result)
		{
		case pt_quest_f2c_accept_success:
			{
				ClanQuestObject* quest = removeQuest(questInfoId);
				if (quest)
				{
					quest->mRecord.state = QUEST_COMPLETE_STATE_ACCEPTED;
					quest->mRecord.beginTime = MGTimeOp::getCurrTimestamp();
				}
				else
				{
					quest = createQuest(questInfoId);
					DYNAMIC_ASSERT(quest);
					quest->mRecord.state = QUEST_COMPLETE_STATE_ACCEPTED;
					quest->mRecord.beginTime = MGTimeOp::getCurrTimestamp();

				}
				addQuest(quest);
				UIQuestManager::getInstance().addQuest(quest);
				UINpc::getInstance().destoryFunctionObj();

				MGStrOp::sprintf(str,64,L"接受【%s】任务成功",hintStr.c_str());
				UIMessageBox::getInstance().showHint(str);
				
				//直接返回对话上级
				UINpc::getInstance().returnTalkDialog();
			}
			break;
		case pt_quest_f2c_accept_already_done:
			{	
				MGStrOp::sprintf(str,64,L"接受【%s】任务失败",hintStr.c_str());
				UIMessageBox::getInstance().showHint(str);		
			}
			break;
		case pt_quest_f2c_accept_clanlevel_not_enough:
			{	
				MGStrOp::sprintf(str,64,L"接受【%s】任务失败",hintStr.c_str());
				UIMessageBox::getInstance().showHint(str);	
			}
			break;
		case pt_quest_f2c_accept_characterlevel_not_enough:
			{	
				MGStrOp::sprintf(str,64,L"接受【%s】任务失败",hintStr.c_str());
				UIMessageBox::getInstance().showHint(str);		
			}
			break;
		case pt_quest_f2c_accept_need_complete_quest:
			{
				MGStrOp::sprintf(str,64,L"接受【%s】任务失败\n需要完成指定任务!",hintStr.c_str());
				UIMessageBox::getInstance().showHint(str);		
			}
			break;
		case pt_quest_f2c_accept_unknown_error:
			{ 	
				MGStrOp::sprintf(str,64,L"接受【%s】任务失败",hintStr.c_str());
				UIMessageBox::getInstance().showHint(str);	
			}
			break;
		}
		
	}

	void CClanQuestManager::handleSubmitQuestResult( U32 questInfoId ,Byte result)
	{
		Str16 hintStr; 
		showQuestHintStr(questInfoId, hintStr);
		static Char16 str[64] = {0};

		switch(result)
		{
		case pt_quest_f2c_submit_success:
			{
				ClanQuestObject* quest = removeQuest(questInfoId);
				if (quest)
				{
					quest->mRecord.endTime = MGTimeOp::getCurrTimestamp();
					quest->mRecord.state = QUEST_COMPLETE_STATE_FINISHED;
				}
				else
				{
					DYNAMIC_ASSERT(false);
				}
				addQuest(quest);

				UINpc::getInstance().destoryFunctionObj();

				
				MGStrOp::sprintf(str,64,L"提交【%s】任务成功",hintStr.c_str());
				UIMessageBox::getInstance().showHint(str);
				

				//删除任务日志列表相关记录
				UIQuestManager::getInstance().removeQuest(questInfoId);
				destory(quest);


				//向服务器获取奖励物品(如果有)  
				CClan* pClan = dynamic_cast<CClan*>(mClan);
				DYNAMIC_ASSERT(pClan);
				pClan->getMainGenreal()->getID();

				ClanQuestInfo* missionInfo = ClanQuestInfos::getInstance().getQuestInfo(questInfoId);
				DYNAMIC_ASSERT(missionInfo);
				U32 rewardItemGroupId = missionInfo->questInfo->getItemGroupId();
				if (rewardItemGroupId != 0)
				{
					ItemPacketProcesser::getInstance().sendRewardItemAssociateQuest(rewardItemGroupId,pClan->getMainGenreal()->getID());
				}

				//删除任务相关道具(如果有);
               /* U32 deleteItemGroup = missionInfo->questInfo->getItemDelGroupId();
				if (deleteItemGroup != 0)
				{
						ItemPacketProcesser::getInstance().sendr
				}
				*/
				//
				UINpc::getInstance().returnTalkDialog();
				//删除任务日志列表相关记录
				UIQuestManager::getInstance().removeQuest(questInfoId);
			}
			break;
		case pt_quest_f2c_submit_clanbag_full:
			{
				MGStrOp::sprintf(str,64,L"提交【%s】任务失败,无法获取奖励物品,背包已满!",hintStr.c_str());
				UIMessageBox::getInstance().showHint(str);
				
			}
			break;
		}

	}

	void CClanQuestManager::handleGiveupQuestResult( U32 questInfoId ,Bool success)
	{
		Str16 hintStr; 
		showQuestHintStr(questInfoId, hintStr);
		static Char16 str[64] = {0};

		if (success)
		{
			ClanQuestObject* quest = removeQuest(questInfoId);
			if (quest)
			{
				destory(quest);
			}
			else
			{
				DYNAMIC_ASSERT(false);
			}
			UINpc::getInstance().destoryFunctionObj();
			//删除任务日志列表相关记录
			UIQuestManager::getInstance().removeQuest(questInfoId);

			MGStrOp::sprintf(str,64,L"放弃【%s】任务成功",hintStr.c_str());
			UIMessageBox::getInstance().showHint(str);
		}
		else
		{
			//放弃任务失败
			
			MGStrOp::sprintf(str,64,L"放弃【%s】任务失败",hintStr.c_str());
			UIMessageBox::getInstance().showHint(str);
		}

	}

	CClanQuestManager& CClanQuestManager::getInstance()
	{
		static  CClanQuestManager ins;
        ins.setClan( CPlayer::getInstance().getActiveClan() );
		return ins;
	}

	void CClanQuestManager::setQuestState( U32 questInfoId, Byte completeState )
	{
		ClanQuestObject* questObj = removeQuest(questInfoId);
		if (!questObj)
		{
			return;
		}
		
		questObj->mRecord.state = (QUEST_COMPLETE_STATE)completeState;
		addQuest(questObj);
		UIQuestManager::getInstance().addQuest(questObj);
	}

	void CClanQuestManager::handleRecvDoingQuestList( DOING_QUEST_DATA* questData, Int count )
	{
		for (Int i = 0; i < count; i++)
		{
			ClanQuestObject* quest = createQuest(questData->questInfoId);
			DYNAMIC_ASSERT(quest);
			quest->mRecord.state = (QUEST_COMPLETE_STATE)questData->completeState;
			quest->mRecord.beginTime = questData->beginTime;
			quest->mRecord.endTime = questData->endTime;
			quest->mRecord.value[0] = questData->value[0];
			quest->mRecord.value[1] = questData->value[1];
			quest->mRecord.value[2] = questData->value[2];
			quest->mRecord.value[3] = questData->value[3];
			addQuest(quest);
			UIQuestManager::getInstance().addQuest(quest);
            
			questData++;
 		}
	}

	void CClanQuestManager::handleRecvFinishedQuestList( FINISHED_QUEST_DATA* questData, Int count )
	{
		for (Int i = 0; i < count; i++)
		{
			FinishedClanQuestObject* quest = createFinishedQuest();
			DYNAMIC_ASSERT(quest);
			quest->questInfoId = questData->questInfoId;
			quest->endTime = questData->endTime;
            mFinishedQuests[quest->questInfoId] = quest;
			questData++;
		}
	}
	void CClanQuestManager::showQuestHintStr(U32 questInfoId, Str16& outStr)
	{
		ClanQuestInfo* questInfo =ClanQuestInfos::getInstance().getQuestInfo(questInfoId);
		if (questInfo)
		{
			QuestTextInfo* textInfo = questInfo->questInfo->getTextInfo();

			if (textInfo)
			{
				if (!textInfo->nameAdd.empty())
				{
					outStr = textInfo->name;
				}
				else
				{
					Str16 tempText = textInfo->name + L"(" + textInfo->nameAdd + L")";
					outStr = tempText;
				}

			}	
		}
	}

	void CClanQuestManager::handleRecvConditionVariable( U32 questInfoId,Byte varPos,Int varValue )
	{
        ClanQuestObject* questObj = getQuest(questInfoId);
		if (!questObj)
		{
			return;
		}
        questObj->mRecord.value[varPos] = varValue;
		UIQuestManager::getInstance().addQuest(questObj);
	}

	GAMEJUDGE_TYPE CClanQuestManager::questGameJudge( U32 questInfoId )
	{
		ClanQuestInfo* questInfo = ClanQuestInfos::getInstance().getQuestInfo(questInfoId);
		DYNAMIC_ASSERT_LOG(questInfo,"error : questInfo == NULL!");
		if (!questInfo)
			return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
		
		U32 clanJudgeId = questInfo->questInfo->getclanJudgeId();
		U32 charJudgeId = questInfo->questInfo->getcharacterJudgeId();
		CClan* tempClan = CPlayer::getInstance().getActiveClan();
		if (!tempClan)
           return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
		CPlayerCharacter* tempChar = tempClan->getMainGenreal();
		if (!tempChar)
		   return GAMEJUDGE_TYPE_UNKNOWN_ERROR;

		return GameJudge::getInstance().checkGameJudge(tempClan,NULL,(CCharacter*)tempChar,clanJudgeId,charJudgeId);
	}
}