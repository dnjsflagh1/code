/******************************************************************************/
#include "stdafx.h"
#include "CNpcEntity.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "HeadDes.h"
#include "HeadDesManage.h"
#include "CPlayer.h"
#include "NpcFuctionInfo.h"
#include "UINpc.h"
#include "NpcFunctionObject.h"
#include "NpcData.h"
#include "CCharacterSceneEntity.h"
#include "CClanQuestManager.h"
#include "DialogueVassal.h"
#include "ClanQuestInfoBase.h"
#include "QuestList.h"
#include "QuestValueChange.h"
#include "CharacterList.h"
/******************************************************************************/
namespace MG
{

    //-----------------------------------------------------------------------
    CNpcEntity::CNpcEntity( IEntity* entity )
        :CNoCharacterSceneEntity(entity, GOT_NPC,GQT_NPC,(MG_NEW NpcEntityData))
		,mPauseThinkTime(0)
    {	
    }

    //-----------------------------------------------------------------------
    CNpcEntity::~CNpcEntity()
    {
    }

    //-----------------------------------------------------------------------
    void CNpcEntity::initialize()
    {
        initializeEntity();
        CNoCharacterSceneEntity::initialize();
    }

    //-----------------------------------------------------------------------
    void CNpcEntity::unInitialize()
    {
        CNoCharacterSceneEntity::unInitialize();  
    }

    //-----------------------------------------------------------------------
    void CNpcEntity::update( Flt delta )
    {
		checkAndPlayIdleAnim(delta);
        CSceneEntity::update( delta );
        updateHeadUI();
    }
    //-----------------------------------------------------------------------
    void CNpcEntity::initializeEntity()
    {
		mPauseThinkTime = MGRandom::getInstance().rand_ab_One(10, 40);
    }

	//-----------------------------------------------------------------------
	void CNpcEntity::updateHeadUI()
	{
        Str strTemplateID = mEntity->getCustomAttr("CharID");
        Int templateID;
        if ( strTemplateID.empty() == false )
        {
            MGStrOp::toI32(strTemplateID.c_str(),templateID);
        }
        
		DialogueVassalInfo* npcDialogInfoNpc = DialogueVassal::getInstance().getDialogueVassalInfobyObjectId( templateID );
		NpcFunctionInfo* funInfo = NULL;
		CharacterTempInfo* charTemplate =  CharacterTemplate::getInstance().getCharacterTempInfo(templateID);
		if (!charTemplate)
		     return;

		//提交任务
		bool bShowFlagSub = false;
		//接受任务
		Bool bShowFlagAcp = false;
		//对话
		Bool bShowFlagTalk = false;
		//商店,
		//以后细分武器店，防具店 等等
		Bool bShowFlagItemShop =  false;
		//地图跳转点
		Bool bShowFlagJumpMap =  false;
		//武将招募
		Bool bShowFlagGeneralRecruired = false;
		
		//任务以外的其他功能标识ID
		U32 artIconId = 0;
		if (npcDialogInfoNpc)
		{
			for(Int i = 0; i < NPC_DIALOG_FUNCTION_ID_COUNT; i++)
			{
				funInfo = NpcFunctionInfos::getInstance().getNpcFuctionInfo(npcDialogInfoNpc->fuctionId[i]);
				if (funInfo)
				{
					DYNAMIC_ASSERT(funInfo);
					switch (funInfo->type)
					{
					case NPC_FUCTION_TYPE_CLAN_QUEST:
						{

							CClan* clan =CPlayer::getInstance().getActiveClan();
							if (!clan)
							{
								//DYNAMIC_ASSERT(false);
								//mHeadDes->setFlagImg(0);
								continue;
							}
							if (funInfo->param2 == QUEST_OPERATE_TYPE_SUBMIT)
							{
								if(CClanQuestManager::getInstance().canSubmit(funInfo->param1))
								{
									bShowFlagSub = true;
									//mHeadDes->setFlagImg(158);
								}
							}
							else if (funInfo->param2 == QUEST_OPERATE_TYPE_ACCEPT)
							{
								if(CClanQuestManager::getInstance().canAccept(funInfo->param1))
								{
									bShowFlagAcp = true;
									//mHeadDes->setFlagImg(159);
									//break;
								}
							}
							else if(funInfo->param2 == QUEST_OPERATE_TYPE_TALK)
							{
								
								ClanQuestObject* questObj = CClanQuestManager::getInstance().getQuest(funInfo->param1);
								if (questObj 
									&& questObj->mRecord.state == QUEST_COMPLETE_STATE_ACCEPTED)
								{
									std::vector<QuestValueChangeInfo*> changeValues;
								
									if(questObj->mInfo->questInfo->getValueChangeGroupInfo(changeValues) >= 1)
									{
										Bool haveTalk = false;
										for(std::vector<QuestValueChangeInfo*>::iterator it = changeValues.begin(); it != changeValues.end(); it++)
										{
											if ((*it)->type == CHANGE_TYPE_TALK_TO_NPC)
											{
												bShowFlagTalk = true;
												break;
											}
										}
									}
								}
							}
						}
						break;
					/*case NPC_FUCTION_TYPE_JUMPMAP:
						{

                            artIconId = charTemplate->getNpcArtEffectId();
						}
						break;
					case NPC_FUCTION_TYPE_ITEMSHOP:
						{
                             artIconId = charTemplate->getNpcArtEffectId();
						}
						break;
					case NPC_FUCTION_TYPE_GENERAL_RECRUIRED:
						{
                             artIconId = charTemplate->getNpcArtEffectId();
						}
						break;
					case NPC_FUCTION_TYPE_CHANGE_FIGHTED_GENERAL:
						{
                            artIconId = charTemplate->getNpcArtEffectId();
						}
						break;
					case NPC_FUCTION_TYPE_PVP_BATTLE:
						{
                            artIconId = charTemplate->getNpcArtEffectId();
						}
						break;
					case NPC_FUCTION_TYPE_PVE_BATTLE:
						{
                           artIconId = charTemplate->getNpcArtEffectId();
						}
						break;
						*/
					}
					
				}
			}
			//交任务，对话任务，接任务，功能npc 优先级
			if (bShowFlagSub)
			{
				mHeadDes->setFlagImg(110015);
				return;
			}
			if (bShowFlagTalk)
			{
				mHeadDes->setFlagImg(160);
				return;
			}
			if (bShowFlagAcp)
			{
				mHeadDes->setFlagImg(110007);
				return;
			}

			//不是任务功能的NPC标识
            mHeadDes->setFlagImg(charTemplate->getNpcArtEffectId());
		}

	}
	//-----------------------------------------------------------------------
	NpcEntityData* CNpcEntity::getDynamicData()
	{
		return dynamic_cast<NpcEntityData*>(getGameObjectData());
	}

	//-----------------------------------------------------------------------
	void CNpcEntity::checkAndPlayIdleAnim( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		Flt animLength = 0;

		if(getActionStateManager().isEmpty())
		{			
			if(isPlayAnimation("hi"))
			{
				mPauseThinkTime = MGRandom::getInstance().rand_ab_One(10, 40);
				return;
			}

			animLength = getAnimationLength("idle");
			playAnimation("idle", false);
		}

		mPauseThinkTime = MGRandom::getInstance().rand_ab_One(10, 40) + animLength;
	}
}