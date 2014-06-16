//**********************************************************************************************************
#include "stdafx.h"
#include "ClanQuestManager.h"
#include "ClanQuestObject.h"
#include "QuestList.h"
#include "ClanQuestInfoBase.h"
#include "QuestNormalList.h"
//**********************************************************************************************************
namespace MG
{
    
	//--------------------------------------------------------------------------
	ClanQuestObject* ClanQuestManager::createQuest(U32 questInfoId)
	{
		ClanQuestObject* obj = MG_POOL_NEW(mQuestPool,ClanQuestObject,());
		DYNAMIC_ASSERT(obj);
		obj->clear();
		obj->mInfo = ClanQuestInfos::getInstance().getQuestInfo(questInfoId);
		if (!obj->mInfo)
		{
			DYNAMIC_ASSERT(false);
			MG_POOL_DELETE(mQuestPool,obj);
			return NULL;
		}
		return obj;
	}
	//--------------------------------------------------------------------------
	void ClanQuestManager::addQuest( ClanQuestObject* quest )
	{
		
		switch(quest->mRecord.state)
		{
		case QUEST_COMPLETE_STATE_ACCEPTED:
			mAllDoingQuests[quest->mInfo->id] = quest;
			mAcceptedQuests[quest->mInfo->id] = quest;
			break;
		case QUEST_COMPLETE_STATE_FINISHED:
			{   
				//存在则一定是循环任务类型 只需要把结束时间替换
				if (isExistInFinishedQuests(quest->mInfo->id))
				{   
                    mFinishedQuests[quest->mInfo->id]->endTime = quest->mRecord.endTime;  
				}
				else
				{
					FinishedClanQuestObject* questObj = createFinishedQuest();
					questObj->endTime = quest->mRecord.endTime;
					questObj->questInfoId = quest->mInfo->id;
					mFinishedQuests[quest->mInfo->id] = questObj;
				}
				//放入废置任务表 用于释放。
				mIdleQuestObjects[quest->mInfo->id] = quest;
				
			}
			break;
		case QUEST_COMPLETE_STATE_SUBMITED:
			mAllDoingQuests[quest->mInfo->id] = quest;
			mSubmitedQuests[quest->mInfo->id] = quest;
			break;
		case QUEST_COMPLETE_STATE_FAILED:
			mAllDoingQuests[quest->mInfo->id] = quest;
			mFailQuests[quest->mInfo->id] = quest;
			break;
		case QUEST_COMPLETE_STATE_TIMEOUT:
			mAllDoingQuests[quest->mInfo->id] = quest;
			mTimeOutQuests[quest->mInfo->id] = quest;
			break;
		}
	}
	//--------------------------------------------------------------------------
	ClanQuestObject* ClanQuestManager::getQuest( U32 questInfoId )
	{
		std::map< U32 , ClanQuestObject*>::iterator it = mAllDoingQuests.find(questInfoId);
		if (it != mAllDoingQuests.end())
		{
			return it->second;
		}
		return NULL;
	}
	//--------------------------------------------------------------------------
	ClanQuestObject* ClanQuestManager::removeQuest( U32 questInfoId )
	{
		ClanQuestObject* quest = NULL;
		std::map< U32 , ClanQuestObject*>::iterator it = mAllDoingQuests.find(questInfoId);
		if (it != mAllDoingQuests.end())
		{
			quest = it->second;
			mAllDoingQuests.erase(it);
		}
		if (quest)
		{
			switch(quest->mRecord.state)
			{
			case QUEST_COMPLETE_STATE_ACCEPTED:
				{
					it = mAcceptedQuests.find(questInfoId);
					if (it != mAcceptedQuests.end())
					{
						mAcceptedQuests.erase(it);
					}
				}

				break;
			case QUEST_COMPLETE_STATE_SUBMITED:
				{
					it = mSubmitedQuests.find(questInfoId);
					if (it != mSubmitedQuests.end())
					{
						mSubmitedQuests.erase(it);
					}
				}
				break;
			case QUEST_COMPLETE_STATE_FAILED:
				{
					it = mFailQuests.find(questInfoId);
					if (it != mFailQuests.end())
					{
						mFailQuests.erase(it);
					}
				}
				break;
			case QUEST_COMPLETE_STATE_TIMEOUT:
				{
					it = mTimeOutQuests.find(questInfoId);
					if (it != mTimeOutQuests.end())
					{
						mTimeOutQuests.erase(it);
					}
				}
				break;
			case QUEST_COMPLETE_STATE_FINISHED:
				{
					std::map< U32 , FinishedClanQuestObject*>::iterator finishedIt = mFinishedQuests.find(questInfoId);
					if (finishedIt != mFinishedQuests.end())
			         {
				         mFinishedQuests.erase(finishedIt);
			         }
				}
				break;
			}
		}
		return quest;
	}
	//--------------------------------------------------------------------------
	void ClanQuestManager::destory( U32 questInfoId )
	{
		ClanQuestObject* obj = getQuest(questInfoId);
		if (obj)
		{
			removeQuest(questInfoId);
			MG_POOL_DELETE(mQuestPool,obj);
		}	
	}
	//--------------------------------------------------------------------------
	void ClanQuestManager::destory( ClanQuestObject* clanQuestObj )
	{
		if (clanQuestObj)
		{
			MG_POOL_DELETE(mQuestPool,clanQuestObj);
		}
	}
	//--------------------------------------------------------------------------
	Bool ClanQuestManager::canAccept( U32 questInfoId )
	{
		Bool isContinue = true;
		//已经完成过的任务
		if (isExistInFinishedQuests(questInfoId))
		{  
			ClanQuestInfo* questInfo = ClanQuestInfos::getInstance().getQuestInfo(questInfoId);
			if (questInfo->questInfo->getQuestCycleType() == CYCLE_TYPE_PER_HOUR)
			{
				if(MGTimeOp::inSameHour(mFinishedQuests[questInfoId]->endTime))
				{
					isContinue = false;
				}
				else
				{
					isContinue = true;
				}

			}
			else if (questInfo->questInfo->getQuestCycleType() == CYCLE_TYPE_PER_DAY)
			{
				if(MGTimeOp::inSameDay(mFinishedQuests[questInfoId]->endTime))
				{
					isContinue = false;
				}
				else
				{
					isContinue = true;
				}
			}
			else if (questInfo->questInfo->getQuestCycleType() == CYCLE_TYPE_PER_WEEK)
			{
				if(MGTimeOp::inSameWeek(mFinishedQuests[questInfoId]->endTime))
				{
					isContinue = false;
				}
				else
				{
					isContinue = true;
				}
			}
			else
			{
				isContinue = false;
			}
			
		}
		//已经接收的任务
		ClanQuestObject* questObj = getQuest(questInfoId);
		if (questObj)
		{
			isContinue = false;
		}	
		if (isContinue)
		{
			//已达到最大任务数
			if (mAllDoingQuests.size() >= mQuestMaxCount)
			{
                 return false;
			}
			//TODO:
			// 角色判断
			// 氏族判断
			return true;
		}
		else
		{
			return false;
		}
	}
	//--------------------------------------------------------------------------
	Bool ClanQuestManager::canSubmit( U32 questInfoId )
	{
		Bool isContinue = true;
		ClanQuestObject* questObj = getQuest(questInfoId);
		if (questObj)
		{
			if(questObj->mRecord.state == QUEST_COMPLETE_STATE_SUBMITED)
			{
				return true;
			}
		}

		return false;
	}
	//--------------------------------------------------------------------------
	Bool ClanQuestManager::canGiveup( U32 questInfoId )
	{
		return true;
	}
	//--------------------------------------------------------------------------
	ClanQuestManager::~ClanQuestManager()
	{

	}
	//--------------------------------------------------------------------------	
	Clan* ClanQuestManager::getClan()
	{
		return mClan;
	}
    //--------------------------------------------------------------------------
    void ClanQuestManager::clear()
    {
        mFinishedQuests.clear();
        mSubmitedQuests.clear();
        mFailQuests.clear();
        mTimeOutQuests.clear();

        mQuestPool.releaseAllObject( true );
        mFinishedQuestPool.releaseAllObject(true);
        mAllDoingQuests.clear();
		mIdleQuestObjects.clear();
        mAcceptedQuests.clear();
    }

	//--------------------------------------------------------------------------
	MG::Bool ClanQuestManager::isExistInFinishedQuests( U32 questInfoId )
	{
		std::map< U32,FinishedClanQuestObject*>::iterator it = mFinishedQuests.find(questInfoId);
		if (it != mFinishedQuests.end())
		{
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------
	void ClanQuestManager::setQuestMaxCount( U32 count )
	{
       mQuestMaxCount = count;
	}
	//--------------------------------------------------------------------------
	MG::U32 ClanQuestManager::getQuestMaxCount() const
	{
		return mQuestMaxCount;

	}
	//--------------------------------------------------------------------------
	FinishedClanQuestObject* ClanQuestManager::createFinishedQuest()
	{
		FinishedClanQuestObject* obj = MG_POOL_NEW(mFinishedQuestPool,FinishedClanQuestObject,());
		DYNAMIC_ASSERT(obj);
		return obj;
	}
	//--------------------------------------------------------------------------
	MG::Bool ClanQuestManager::isExistInSubmitQuests( U32 questInfoId )
	{
		std::map< U32 , ClanQuestObject*>::iterator iter = mSubmitedQuests.find(questInfoId);
		if ( iter != mSubmitedQuests.end() )
			return true;

		return false;
	}
}