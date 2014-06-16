/******************************************************************************/
#include "stdafx.h"
#include "SClanQuestManager.h"
#include "SLuaClanQuestSystem.h"
#include "ClanQuestInfoBase.h"
#include "ClanQuestObject.h"
#include "QuestList.h"
#include "SClan.h"
#include "SPlayer.h"
#include "QuestNetPacketProcesser.h"
#include "QuestValueChange.h"
#include "SItemManager.h"
#include "SClan.h"
#include "PlayerItem.h"
#include "ClanDataBase.h"
#include "FrontServerMain.h"
#include "GameJudge.h"
/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	SClanQuestManager::SClanQuestManager()
	{
           setQuestMaxCount(16);
	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::handleAcceptQuest( U32 questInfoId,U64 generalId)
	{
        Bool isContinue = true;
        PT_QUEST_F2C_ACCEPT_RESULT result = pt_quest_f2c_accept_success;
		ClanQuestObject* questObj = NULL;
        if (!canAccept(questInfoId))
        {   
            result = pt_quest_f2c_accept_unknown_error;
			isContinue = false;
        }

		if (isContinue)
		{  
           GAMEJUDGE_TYPE judge_type = questGameJudge(questInfoId,generalId);
		   if (judge_type != GAMEJUDGE_TYPE_SUCCESS)
		   {
                isContinue = false;
				if (judge_type == GAMEJUDGE_TYPE_CLAN_COMPLETE_QUEST_ERROR)
				{
					result = pt_quest_f2c_accept_need_complete_quest;
				}
				else if (judge_type == GAMEJUDGE_TYPE_CLAN_COMPLETE_QUEST_ERROR) 
				{
					result = pt_quest_f2c_accept_need_complete_quest;
				}
				else if (judge_type == GAMEJUDGE_TYPE_CLAN_LEVEL_ERROR)
				{
					result = pt_quest_f2c_accept_clanlevel_not_enough;
				}
				else if (judge_type == GAMEJUDGE_TYPE_CHARACTER_LEVEL_ERROR)
				{
					result = pt_quest_f2c_accept_characterlevel_not_enough;
				}
				else
				{
                   result = pt_quest_f2c_accept_unknown_error;
				} 
		   }

		}
		if (isContinue)
		{
			// 内存操作
			questObj = processAcceptClanQuestMemory(questInfoId);
			if (!questObj)
			{
				DYNAMIC_ASSERT_LOG(questObj,"error : can not create ClanQuestObject from memory!");
			    isContinue = false;
                result = pt_quest_f2c_accept_unknown_error;

			}
		}
	
		// 调用脚本
		//if (!SLuaClanQuestSystem::getInstance().execAcceptQuestScript((SClan*)getClan(),questObj))
		{
			//DYNAMIC_ASSERT(false);
			//return;
		}
		
		// 数据库操作
        
		// 通知客户端
		NetIdType netId = ((SClan*)getClan())->getParentPlayer()->getClientNetID();
		QuestNetPacketProcesser::getInstance().sendQuestAcceptResult(netId,questInfoId,result);
		
		//需要预处理类型:如获取某一物品先判断是否已有该物品及数量
        if (isContinue)
        { 
            preProcessAcceptQuest(questObj);
        }
	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::handleSubmitQuest( U32 questInfoId )
	{
        PT_QUEST_F2C_SUBMIT_RESULT result = pt_quest_f2c_submit_success;

		ClanQuestObject* questObj = getQuest(questInfoId);
		if (!questObj)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		ClanQuestInfo* questInfo = questObj->mInfo;
		U32 rewardItemGroupId = questInfo->questInfo->getItemGroupId();
		U32 delItemGroupId =     questInfo->questInfo->getItemDelGroupId();
		if (rewardItemGroupId != 0)
		{
			if (false == getSItemManager()->handleCheckCanAddToClanBag(rewardItemGroupId))
			{
                  result = pt_quest_f2c_submit_clanbag_full;
			}
		}
        if (delItemGroupId !=0)
        {
			//判断有任务物品删除
			if (false == getSItemManager()->handleCheckItemExistInClanBag(delItemGroupId))
			{
                  result = pt_quest_f2c_submit_clanbag_not_enough;
			}
			else
			{
				//删除任务物品
				getSItemManager()->handlDeductQuestItem(delItemGroupId);
			}
        }
		
		if (result == pt_quest_f2c_submit_success)
		{  
			// 内存操作
            processSubmitClanQuestMemory(questInfoId);
		}
		// 调用脚本
		//if (!SLuaClanQuestSystem::getInstance().execSubbmitQuestScript((SClan*)getClan(),questObj))
		{
			//DYNAMIC_ASSERT(false);
			//return;
		}
		// 数据库操作

		// 通知客户端
		NetIdType netId = ((SClan*)getClan())->getParentPlayer()->getClientNetID();
		QuestNetPacketProcesser::getInstance().sendQuestSubmitResult(netId,questInfoId,result);

	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::handleGiveupQuest( U32 questInfoId )
	{

		// 内存操作
		processGiveupClanQuestMemory(questInfoId);

		// 数据库操作

		// 通知客户端
		NetIdType netId = ((SClan*)getClan())->getParentPlayer()->getClientNetID();
		QuestNetPacketProcesser::getInstance().sendQuestGiveupResult(netId,questInfoId,true);
	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::handleFinishQuest( U32 questInfoId )
	{
		// 内存操作
		ClanQuestObject* questObj = processQuestFinishedMemory(questInfoId);
		if (!questObj)
		{
			DYNAMIC_ASSERT(false);
			return;
		}
		// 数据库操作

		// 通知客户端
		NetIdType netId = ((SClan*)getClan())->getParentPlayer()->getClientNetID();
		QuestNetPacketProcesser::getInstance().sendQuestCompletedState(netId,questInfoId,true);
	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::handleFailQuest( U32 questInfoId )
	{
		// 内存操作
		processQuestFailedMemory(questInfoId);

		// 数据库操作

		// 通知客户端
		NetIdType netId = ((SClan*)getClan())->getParentPlayer()->getClientNetID();
		QuestNetPacketProcesser::getInstance().sendQuestCompletedState(netId,questInfoId,false);
	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::processQuestFailedMemory( U32 questInfoId )
	{
		destory(questInfoId);
	}

	//--------------------------------------------------------------------------
	ClanQuestObject* SClanQuestManager::processQuestFinishedMemory( U32 questInfoId )
	{
		ClanQuestObject* questObj = removeQuest(questInfoId);
		if (questObj)
		{
			questObj->mRecord.state = QUEST_COMPLETE_STATE_FINISHED;
			addQuest(questObj);
		}
		return questObj;
	}

	//--------------------------------------------------------------------------
	ClanQuestObject* SClanQuestManager::processAcceptClanQuestMemory( U32 questInfoId )
	{
		ClanQuestObject* questObj = removeQuest(questInfoId);
		if (!questObj)
		{
			questObj = createQuest(questInfoId);
			if (!questObj)
			{
				destory(questObj);
				return NULL;
			}
		}
		questObj->mRecord.state = QUEST_COMPLETE_STATE_ACCEPTED;
		questObj->mRecord.beginTime = MGTimeOp::getCurrTimestamp();
		addQuest(questObj);
		return questObj;
	}

	//--------------------------------------------------------------------------
	ClanQuestObject* SClanQuestManager::processSubmitClanQuestMemory( U32 questInfoId )
	{
		ClanQuestObject* questObj = removeQuest(questInfoId);
		if (!questObj)
		{
			return NULL;
		}
		questObj->mRecord.state = QUEST_COMPLETE_STATE_FINISHED;
		questObj->mRecord.endTime = MGTimeOp::getCurrTimestamp();
		addQuest(questObj);
		return questObj;
	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::processGiveupClanQuestMemory( U32 questInfoId )
	{
		destory(questInfoId);
	}

	//--------------------------------------------------------------------------
	MG::QUEST_COMPLETE_STATE SClanQuestManager::checkClanQuestState( ClanQuestObject* clanQuestObj )
	{
		QUEST_COMPLETE_STATE state;
		state = QUEST_COMPLETE_STATE_IDLE;
		Bool successFlag[MAX_CLAN_QUEST_VALUE_COUNT];
		Bool failedFlag[MAX_CLAN_QUEST_VALUE_COUNT];

		for (Int i = 0; i < MAX_CLAN_QUEST_VALUE_COUNT; i++)
		{
	
			if (clanQuestObj->mRecord.value[i] <= clanQuestObj->mInfo->questInfo->getValue(false,i))
			{
				failedFlag[i] = true;
			}
			else
			{
				failedFlag[i] = false;
			}
			if(clanQuestObj->mRecord.value[i] >= clanQuestObj->mInfo->questInfo->getValue(true,i))
			{
				successFlag[i] = true;
			}
			else
			{
				successFlag[i] = false;
			}
		}
        
		if (successFlag[0] && successFlag[1] && successFlag[2] && successFlag[3])
		{
           state = QUEST_COMPLETE_STATE_SUBMITED;
		}
		else if (failedFlag[0] || failedFlag[1] || failedFlag[2] || failedFlag[3])
		{
			state = QUEST_COMPLETE_STATE_FAILED;
		}
		else
		{
			state = QUEST_COMPLETE_STATE_ACCEPTED;
		}

		return state;
	}

	//--------------------------------------------------------------------------
	MG::Bool SClanQuestManager::isClanQuestTimeOut( ClanQuestObject* clanQuestObj )
	{
		return false;
	}

	// 外部调用接口
	//--------------------------------------------------------------------------
	void SClanQuestManager::notifyTalktoNpc( U32 questInfoId,U32 npcId )
	{
		if (mAcceptedQuests.empty())
		{
			return;
		}
		std::vector<QuestValueChangeInfo*> changeValues;
		std::vector<QuestValueChangeInfo*>::iterator valueIt;

		ClanQuestObject* questObj = removeQuest(questInfoId);
		if (!questObj)
		{
			return;
		}

		if(questObj->mInfo->questInfo->getValueChangeGroupInfo(changeValues) > 0)
		{
			for (valueIt = changeValues.begin(); valueIt != changeValues.end(); valueIt++)
			{
				if((*valueIt)->type == CHANGE_TYPE_TALK_TO_NPC && (*valueIt)->param1 == npcId)
				{
					
					questObj->mRecord.value[(*valueIt)->valueChangeType] += (*valueIt)->valueChangeNum;
					QuestNetPacketProcesser::getInstance().sendQuestConditionVariable(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,(*valueIt)->valueChangeType,
						questObj->mRecord.value[(*valueIt)->valueChangeType]);
				}
			}
			QUEST_COMPLETE_STATE tempState = checkClanQuestState(questObj);
			
			if (tempState != questObj->mRecord.state && tempState != QUEST_COMPLETE_STATE_IDLE)
			{
				questObj->mRecord.state = tempState;
				addQuest(questObj);
				QuestNetPacketProcesser::getInstance().sendQuestCompletedState(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,Byte(tempState));
			}
			else
			{
				addQuest(questObj);
			}
			
		}
	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::notifyKillMonster( U32 mosterId )
	{
		if (mAcceptedQuests.empty())
		{
			return;
		}
		
		std::vector<QuestValueChangeInfo*> changeValues;
		std::vector<QuestValueChangeInfo*>::iterator valueIt;

		std::map< U32 , ClanQuestObject*>::iterator questIt = mAcceptedQuests.begin();
		while (questIt != mAcceptedQuests.end())
		{
			ClanQuestObject* questObj = questIt->second;
			if (!questObj)
			{
				DYNAMIC_ASSERT(false);
				return;
			}
			//
			changeValues.clear();
			//此任务对象有没有被触发
			Bool isTriggered = false;
			//触发其他外部方法
			Bool isTriggeredExternal = false;
			if(questObj->mInfo->questInfo->getValueChangeGroupInfo(changeValues) > 0)
			{	
				for (valueIt = changeValues.begin(); valueIt != changeValues.end(); valueIt++)
				{
					
					if((*valueIt)->type == CHANGE_TYPE_KILL_MONSTER && (*valueIt)->param1 == mosterId)
					{
						// 当前任务被触发
						isTriggered = true;
						// 改变任务相关属性
						questObj->mRecord.value[(*valueIt)->valueChangeType] += (*valueIt)->valueChangeNum;	
						QuestNetPacketProcesser::getInstance().sendQuestConditionVariable(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,(*valueIt)->valueChangeType,
							questObj->mRecord.value[(*valueIt)->valueChangeType]);
							
					}
					else if ((*valueIt)->type == CHANGE_TYPE_KILLMONSTER_AND_GETITEM && (*valueIt)->param1 == mosterId)
					{   
						DYNAMIC_ASSERT_LOG(isTriggered != true,"ValueChangeGroupInfo logic error!");
						U32 itemTemplateId = (*valueIt)->param3;
						U32 randomValue = (*valueIt)->param2;
						U32 itemCount = (*valueIt)->param4;
						    // 杀死怪物，并且背包有位置,概率获得任务物品,
							if (MGRandom::getInstance().rand_ab_One(1,1000)<= randomValue)
							{
								SItemManager* itemManager = getSItemManager();
								DYNAMIC_ASSERT(itemManager);
								if (itemManager->handleCheckCanAddToClanBag(itemTemplateId,itemCount))
								{
									SItemManager* itemManager = getSItemManager();
									DYNAMIC_ASSERT(itemManager);
									/**/
									questIt++;
									/**/
									itemManager->handlAddItem(itemTemplateId,itemCount);
									isTriggeredExternal = true;
									
								}
							}
						
					}
					else
					{
						//调用出错 或者 当前任务的当前目标与此外部事件无关	
					}
				}
				// 如果当前任务被触发
				if (isTriggered)
				{
					// 从内存取出任务 
					//questIt = mAcceptedQuests.erase(questIt);
					std::map< U32 , ClanQuestObject*>::iterator questItTemp;
					questItTemp = questIt;
					questIt++;
					mAcceptedQuests.erase(questItTemp);
					removeQuest(questObj->mInfo->id);

					// 检测任务状态

					QUEST_COMPLETE_STATE tempState = checkClanQuestState(questObj);
					
					if (tempState != questObj->mRecord.state && tempState != QUEST_COMPLETE_STATE_IDLE)
					// 状态发生改变并 重新加入内存 通知客户端 
					{
						questObj->mRecord.state = tempState;
						addQuest(questObj);
						QuestNetPacketProcesser::getInstance().sendQuestCompletedState(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,Byte(tempState));
					}
					else
					// 状态未发生改变 加入内存
					{
						addQuest(questObj);
					}
					
				}
				else
				{
                    if (isTriggeredExternal == false)
                    {
						questIt++;
                    }
				}
			}
			else
			{
				questIt++;
			}
		}
	}

	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	void SClanQuestManager::notifyGetOrDropItem( U64 itemId,Bool isGet )
	{
		if (mAllDoingQuests.empty())
		{
			return;
		}
		std::vector<QuestValueChangeInfo*> changeValues;
		std::vector<QuestValueChangeInfo*>::iterator valueIt;

		std::map< U32 , ClanQuestObject*>::iterator questIt = mAllDoingQuests.begin();
		while (questIt != mAllDoingQuests.end())
		{

			ClanQuestObject* questObj = questIt->second;
			if (!questObj)
			{
				DYNAMIC_ASSERT(false);
				return;
			}
			changeValues.clear();
			// 此任务对象有没有被触发
			Bool isTriggered = false;
			if(questObj->mInfo->questInfo->getValueChangeGroupInfo(changeValues) > 0)
			{	
				for (valueIt = changeValues.begin(); valueIt != changeValues.end(); valueIt++)
				{

					if(
						((*valueIt)->type == CHANGE_TYPE_GET_ITEM && (*valueIt)->param1 == itemId) || 
						((*valueIt)->type == CHANGE_TYPE_KILLMONSTER_AND_GETITEM && (*valueIt)->param3 == itemId)
						)
					{
						// 当前任务被触发
						isTriggered = true;
						// 改变任务相关属性
						if (isGet)
						{
                              questObj->mRecord.value[(*valueIt)->valueChangeType] += (*valueIt)->valueChangeNum;	
						}
						else
						{
							  if (questObj->mRecord.value[(*valueIt)->valueChangeType] != 0)
							  { 
								  questObj->mRecord.value[(*valueIt)->valueChangeType] -= (*valueIt)->valueChangeNum;
							  }
							  
						}
						
						QuestNetPacketProcesser::getInstance().sendQuestConditionVariable(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,(*valueIt)->valueChangeType,
							questObj->mRecord.value[(*valueIt)->valueChangeType]);

				    	}
					
					else
					{
						//调用出错 或者 当前任务的当前目标与此外部事件无关	
					}
				}
				// 如果当前任务被触发
				if (isTriggered)
				{
					// 从内存取出任务 
					std::map< U32 , ClanQuestObject*>::iterator questItTemp;
					questItTemp = questIt;
					questIt++;
					//mAcceptedQuests.erase(questItTemp);
					//mAllDoingQuests.erase()
					removeQuest(questObj->mInfo->id);

					// 检测任务状态
					QUEST_COMPLETE_STATE tempState = checkClanQuestState(questObj);

					if (tempState != questObj->mRecord.state && tempState != QUEST_COMPLETE_STATE_IDLE)
						// 状态发生改变并 重新加入内存 通知客户端 
					{
						questObj->mRecord.state = tempState;
						addQuest(questObj);
						
					    QuestNetPacketProcesser::getInstance().sendQuestCompletedState(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,Byte(tempState));

					}
					else
						// 状态未发生改变 加入内存
					{
						addQuest(questObj);
					}
				}
				else
				{
					questIt++;
				}
			}
			else
			{
				questIt++;
			}
		}
	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::notifyGetGeneral( U64 generalId )
	{
		if (mAcceptedQuests.empty())
		{
			return;
		}
		std::vector<QuestValueChangeInfo*> changeValues;
		std::vector<QuestValueChangeInfo*>::iterator valueIt;

		std::map< U32 , ClanQuestObject*>::iterator questIt = mAcceptedQuests.begin();
		while (questIt != mAcceptedQuests.end())
		{
			ClanQuestObject* questObj = questIt->second;
			if (!questObj)
			{
				DYNAMIC_ASSERT(false);
				return;
			}
			changeValues.clear();
			// 此任务对象有没有被触发
			Bool isTriggered = false;
			if(questObj->mInfo->questInfo->getValueChangeGroupInfo(changeValues) > 0)
			{	
				for (valueIt = changeValues.begin(); valueIt != changeValues.end(); valueIt++)
				{

					if((*valueIt)->type == CHANGE_TYPE_GET_GENERAL && (*valueIt)->param1 == generalId)
					{
						// 当前任务被触发
						isTriggered = true;
						// 改变任务相关属性
						questObj->mRecord.value[(*valueIt)->valueChangeType] += (*valueIt)->valueChangeNum;	
						QuestNetPacketProcesser::getInstance().sendQuestConditionVariable(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,(*valueIt)->valueChangeType,
							questObj->mRecord.value[(*valueIt)->valueChangeType]);

					}
					else
					{
						//调用出错 或者 当前任务的当前目标与此外部事件无关	
					}
				}
				// 如果当前任务被触发
				if (isTriggered)
				{
					// 从内存取出任务 
					//questIt = mAcceptedQuests.erase(questIt);
					std::map< U32 , ClanQuestObject*>::iterator questItTemp;
					questItTemp = questIt;
					questIt++;
					mAcceptedQuests.erase(questItTemp);
					removeQuest(questObj->mInfo->id);

					// 检测任务状态
					QUEST_COMPLETE_STATE tempState = checkClanQuestState(questObj);

					if (tempState != questObj->mRecord.state && tempState != QUEST_COMPLETE_STATE_IDLE)
						// 状态发生改变并 重新加入内存 通知客户端 
					{
						questObj->mRecord.state = tempState;
						addQuest(questObj);
						QuestNetPacketProcesser::getInstance().sendQuestCompletedState(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,Byte(tempState));
					}
					else
						// 状态未发生改变 加入内存
					{
						addQuest(questObj);
					}
				}
				else
				{
					questIt++;
				}
			}
			else
			{
				questIt++;
			}
		}
	}

    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
	
    //--------------------------------------------------------------------------
    //--------------------------------------------------------------------------
	void SClanQuestManager::notifyLeaveMap()
	{
		if (mAllDoingQuests.empty())
		{
			return;
		}
		std::vector<QuestValueChangeInfo*> changeValues;
		std::vector<QuestValueChangeInfo*>::iterator valueIt;

		std::map< U32 , ClanQuestObject*>::iterator questIt = mAllDoingQuests.begin();
		while (questIt != mAllDoingQuests.end())
		{

			ClanQuestObject* questObj = questIt->second;
			if (!questObj)
			{
				DYNAMIC_ASSERT(false);
				return;
			}

			if (questObj->mRecord.state == QUEST_COMPLETE_STATE_FINISHED || questObj->mRecord.state == QUEST_COMPLETE_STATE_FAILED)
			{ 
				return;
			}
			changeValues.clear();
			// 此任务对象有没有被触发
			Bool isTriggered = false;
			if(questObj->mInfo->questInfo->getValueChangeGroupInfo(changeValues) > 0)
			{	
				for (valueIt = changeValues.begin(); valueIt != changeValues.end(); valueIt++)
				{

					if((*valueIt)->type == CHANGE_TYPE_LEAVE_MAP)
					{
						// 当前任务被触发
						isTriggered = true;
						// 改变任务相关属性
						questObj->mRecord.value[(*valueIt)->valueChangeType] += (*valueIt)->valueChangeNum;	
						QuestNetPacketProcesser::getInstance().sendQuestConditionVariable(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,(*valueIt)->valueChangeType,
							questObj->mRecord.value[(*valueIt)->valueChangeType]);

					}
					else
					{
						//调用出错 或者 当前任务的当前目标与此外部事件无关	
					}
				}
				// 如果当前任务被触发
				if (isTriggered)
				{
					// 从内存取出任务 
					//questIt = mAcceptedQuests.erase(questIt);
					std::map< U32 , ClanQuestObject*>::iterator questItTemp;
					questItTemp = questIt;
					questIt++;
					removeQuest(questObj->mInfo->id);

					// 检测任务状态
					QUEST_COMPLETE_STATE tempState = checkClanQuestState(questObj);

					if (tempState != questObj->mRecord.state && tempState != QUEST_COMPLETE_STATE_IDLE)
						// 状态发生改变并 重新加入内存 通知客户端 
					{
						questObj->mRecord.state = tempState;
						addQuest(questObj);
						QuestNetPacketProcesser::getInstance().sendQuestCompletedState(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,Byte(tempState));
					}
					else
						// 状态未发生改变 加入内存
					{
						addQuest(questObj);
					}
				}
				else
				{
                        questIt++; 
				}
			}
			else
			{
                   questIt++;
			}
		}
	}

    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
	void SClanQuestManager::notifyInGameTime()
	{
		if (mAcceptedQuests.empty())
		{
			return;
		}

		std::vector<QuestValueChangeInfo*> changeValues;
		std::vector<QuestValueChangeInfo*>::iterator valueIt;

		std::map< U32 , ClanQuestObject*>::iterator questIt = mAcceptedQuests.begin();
		while (questIt != mAcceptedQuests.end())
		{
			ClanQuestObject* questObj = questIt->second;
			if (!questObj)
			{
				DYNAMIC_ASSERT(false);
				return;
			}
			changeValues.clear();
			// 此任务对象有没有被触发
			Bool isTriggered = false;
			if(questObj->mInfo->questInfo->getValueChangeGroupInfo(changeValues) > 0)
			{	
				for (valueIt = changeValues.begin(); valueIt != changeValues.end(); valueIt++)
				{

					if((*valueIt)->type == CHANGE_TYPE_PLAY_TIME )
					{   

						if (MGTimeOp::getCurrTimestamp() - questObj->mRecord.beginTime >= ((*valueIt)->param1)/10)  //单位 百毫秒
						{   
							// 当前任务被触发
							isTriggered = true;
							// 改变任务相关属性
							questObj->mRecord.value[(*valueIt)->valueChangeType] += (*valueIt)->valueChangeNum;	
							QuestNetPacketProcesser::getInstance().sendQuestConditionVariable(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,(*valueIt)->valueChangeType,
								questObj->mRecord.value[(*valueIt)->valueChangeType]);
						}
						

					}
					else
					{
						//调用出错 或者 当前任务的当前目标与此外部事件无关	
					}
				}
				// 如果当前任务被触发
				if (isTriggered)
				{
					// 从内存取出任务 
					questIt = mAcceptedQuests.erase(questIt);
					removeQuest(questObj->mInfo->id);

					// 检测任务状态

					QUEST_COMPLETE_STATE tempState = checkClanQuestState(questObj);

					if (tempState != questObj->mRecord.state && tempState != QUEST_COMPLETE_STATE_IDLE)
						// 状态发生改变并 重新加入内存 通知客户端 
					{
						questObj->mRecord.state = tempState;
						addQuest(questObj);
						QuestNetPacketProcesser::getInstance().sendQuestCompletedState(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,Byte(tempState));
					}
					else
						// 状态未发生改变 加入内存
					{
						addQuest(questObj);
					}

				}
				else
				{
					questIt++;
				}
			}
			else
			{
				 questIt++;
			}
		}
	}
	//--------------------------------------------------------------------------
	SItemManager* SClanQuestManager::getSItemManager()
	{	
		SItemManager* itemManager = NULL;
		SClan* clanPtr = dynamic_cast<SClan*>(getClan());
		DYNAMIC_ASSERT(clanPtr);
		itemManager = (clanPtr->getItemManager());
		return itemManager;
	}

	//--------------------------------------------------------------------------
	void SClanQuestManager::preProcessAcceptQuest(ClanQuestObject* questObj)
	{
		if (mAcceptedQuests.empty())
		{
			return;
		}
		std::vector<QuestValueChangeInfo*> changeValues;
		std::vector<QuestValueChangeInfo*>::iterator valueIt;
		// 此任务对象有没有被触发
		Bool isTriggered = false;
		if(questObj->mInfo->questInfo->getValueChangeGroupInfo(changeValues) > 0)
		{	
			for (valueIt = changeValues.begin(); valueIt != changeValues.end(); valueIt++)
			{
                //
				if((*valueIt)->type == CHANGE_TYPE_GET_ITEM || 
					(*valueIt)->type == CHANGE_TYPE_KILLMONSTER_AND_GETITEM)
				{
                    U32 templateId = 0;
					if ((*valueIt)->type == CHANGE_TYPE_GET_ITEM)
					{
                             templateId = (*valueIt)->param1;
					}
					else if ((*valueIt)->type == CHANGE_TYPE_KILLMONSTER_AND_GETITEM)
					{
                             templateId = (*valueIt)->param3;
					} 
					SItemManager* itemManager = getSItemManager();
					DYNAMIC_ASSERT(itemManager);
                    U32 itemCount = itemManager->findItemCountByTemplateId(templateId,ITEM_SITE_TYPE_CLAN);
					if (itemCount == 0)
					{
						return;
					}
					// 当前任务被触发
					isTriggered = true;
				   // 改变任务相关属性
				    questObj->mRecord.value[(*valueIt)->valueChangeType] += ((*valueIt)->valueChangeNum)*itemCount;	
					QuestNetPacketProcesser::getInstance().sendQuestConditionVariable(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,(*valueIt)->valueChangeType,
						questObj->mRecord.value[(*valueIt)->valueChangeType]);
					
				}
				//接受任务后即完成
				if ((*valueIt)->type == CHANGE_TYPE_RECIVE_THEN_FINISHED)
				{  
					// 当前任务被触发
					isTriggered = true;
					// 改变任务相关属性
					questObj->mRecord.value[(*valueIt)->valueChangeType] += (*valueIt)->valueChangeNum;
					QuestNetPacketProcesser::getInstance().sendQuestConditionVariable(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,(*valueIt)->valueChangeType,
						questObj->mRecord.value[(*valueIt)->valueChangeType]);
				}


			}
			// 如果当前任务被触发
			if (isTriggered)
			{
				// 从内存取出任务
				removeQuest(questObj->mInfo->id);

				// 检测任务状态
				QUEST_COMPLETE_STATE tempState = checkClanQuestState(questObj);

				if (tempState != questObj->mRecord.state && tempState != QUEST_COMPLETE_STATE_IDLE)
					// 状态发生改变并 重新加入内存 通知客户端 
				{
					questObj->mRecord.state = tempState;
					addQuest(questObj);
					QuestNetPacketProcesser::getInstance().sendQuestCompletedState(((SClan*)getClan())->getParentPlayer()->getClientNetID(),questObj->mInfo->id,Byte(tempState));
				}
				else
					// 状态未发生改变 加入内存
				{
					addQuest(questObj);
				}

			}
		}

	}
	//--------------------------------------------------------------------------
	void SClanQuestManager::loadClanQuest( std::vector<dbDoingClanQuestObject>& doingQuestData,std::vector<FinishedClanQuestObject>& finishedQuestData )
	{
		//填充finished quest
     
		FinishedClanQuestObject* finishedQuestobj = NULL;
		std::vector<FinishedClanQuestObject>::iterator finishedFrontIt = finishedQuestData.begin();
		std::vector<FinishedClanQuestObject>::iterator finishedbackIt = finishedQuestData.end();;
        while( finishedFrontIt != finishedbackIt)
		{      
               finishedQuestobj = createFinishedQuest();
			   finishedQuestobj->endTime = (*finishedFrontIt).endTime;
			   finishedQuestobj->questInfoId = (*finishedFrontIt).questInfoId;
			   mFinishedQuests[(*finishedFrontIt).questInfoId] = finishedQuestobj;

			  finishedFrontIt++;
		}

		//填充doing    quest
		U32 questId = 0;
		ClanQuestObject*  questObj = NULL;
		std::vector<dbDoingClanQuestObject>::iterator front = doingQuestData.begin();
		std::vector<dbDoingClanQuestObject>::iterator back = doingQuestData.end();
		while (front != back)
		{
           questId = (*front).questInfoId;
		   questObj = createQuest(questId);
		   if (questObj == NULL)
		   {
			   DYNAMIC_ASSERT(0);
		   }
		   
		   //更加DB设置任务信息
           questObj->mRecord.beginTime = (*front).mRecord.beginTime;
		   questObj->mRecord.endTime = (*front).mRecord.endTime;
		   questObj->mRecord.state = (*front).mRecord.state;
		   questObj->mRecord.value[0] = (*front).mRecord.value[0];
		   questObj->mRecord.value[1] = (*front).mRecord.value[1];
		   questObj->mRecord.value[2] = (*front).mRecord.value[2];
		   questObj->mRecord.value[3] = (*front).mRecord.value[3];
           
		   //add
		   addQuest(questObj);
		   front++;

		}

	}
	//--------------------------------------------------------------------------
	void SClanQuestManager::saveQuestDataToDataBase()
	{
		// 保存氏族任务 时需要判断氏族是否存在
		if (mClan)
		{	
			ClanDataBaseDBOp::updateQuest(*( FrontServerMain::getInstance().getDBDriver() ),mClan->getClanID(),&mAllDoingQuests,&mFinishedQuests);
		}
	}

	//--------------------------------------------------------------------------
	GAMEJUDGE_TYPE SClanQuestManager::questGameJudge( U32 questInfoId,U64 generalId )
	{
          ClanQuestInfo* questInfo = ClanQuestInfos::getInstance().getQuestInfo(questInfoId);
		  if (!questInfo)
		  {   
			  DYNAMIC_ASSERT_LOG(questInfo,"error: ClanQuestInfo == NULL!");
			  return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
		  }

          SClan* tempClan = static_cast<SClan*>(mClan);
		  SPlayerCharacterPtr char_ptr;
          tempClan->getPlayerCharacter(char_ptr, generalId);
		  //if (!pChar)
		  //{
			 // DYNAMIC_ASSERT_LOG(pChar,"error: SPlayerCharacter == NULL!");
			 // return GAMEJUDGE_TYPE_UNKNOWN_ERROR;
		  //}
		  return GameJudge::getInstance().checkGameJudge(tempClan,(SCharacter*)char_ptr.getPointer(),questInfo->questInfo->getclanJudgeId(),
			  questInfo->questInfo->getcharacterJudgeId());
	}
	//--------------------------------------------------------------------------

}