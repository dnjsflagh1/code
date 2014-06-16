/******************************************************************************/
#include "stdafx.h"
#include "SAIController.h"
#include "BaseAIGroupTemplate.h"
#include "SCharacter.h"
#include "CharacterList.h"
#include "CharacterSkillTempLate.h"
#include "SAIObjectManager.h"
#include "SkillInfoList.h"
#include "STroop.h"
#include "SAIManager.h"
#include "SSkillOwnManager.h"
#include "SWorldManager.h"

/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	SAIController::SAIController( SCharacter* owner )
		:mOwner(owner)
		,mLastUpdateTime(0)
		,mKeepDistance(0)
		,mCurrGuardRadius(0)
		,mPursueRadius(0)
	{

	}

	//--------------------------------------------------------------------------
	SAIController::~SAIController()
	{

	}

	//--------------------------------------------------------------------------
	void SAIController::Init()
	{
		mBaseAIGroup = (BaseAIGroup*)mOwner->getBaseAIGroup();

		if(!mBaseAIGroup)
		{
			return;
		}

		UInt characterTemplateId = 0;

		if(mOwner->getType() == GOT_SOLDIER)
		{
			characterTemplateId = 0;//((STroopSoldier*)mOwner)->getOwnerTroop()->getCharacterData()->mCharacterTemplateID;
		}
		else
		{
			characterTemplateId = mOwner->getCharacterData()->mCharacterTemplateID;
		}

		const CharacterTempInfo* characterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(characterTemplateId);
		if(!characterTempInfo)
		{
			return;
		}

		//mFightAIGroup = FightAIGroupTemplate::getInstance().getFightAIGroup(characterTempInfo->getAIFightGroupId());

		mCenterPos = mOwner->getPos();

		std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_SELECTSKILL);
		if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
		{
			CharSkillInfo* charSkillInfo = (CharSkillInfo*)CharacterSkillTemplate::getInstance().getCharSkillInfo(characterTempInfo->getCharacterCharacterSkillId(0));
			if(charSkillInfo)
			{
				SkillInfo* skillInfo = NULL;
				SkillRatio skillRatio;

				for(UInt i = 0; i < CHAR_SKILL_NUM; ++i)
				{
					skillRatio.skillId = charSkillInfo->CharSkillList[i];
					skillRatio.ratioVal = it->second->paramList[i];
					mSkillRatioList.push_back(skillRatio);
				}
			}
		}

		it = mBaseAIGroup->aiBaseAIInfoList[BAH_PEACE].find(BAT_GUARD);
		if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_PEACE].end() )
		{
			mCurrGuardRadius = it->second->paramList[1];
		}

		it = mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_PURSUE);
		if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
		{
			mPursueRadius = it->second->paramList[0];
		}

		if(mPursueRadius == 0)
		{
			mCurrGuardRadius = mOwner->getSkillOwnManager()->getMinSkillAttackDis();
		}
		else if(mPursueRadius < mCurrGuardRadius)
		{
			mCurrGuardRadius = mPursueRadius;
		}

		SFightManager* fightManager = mOwner->getFightManager();
		if(fightManager)
		{
			fightManager->addListener(this);
		}

		setBirthState();
	}

	//--------------------------------------------------------------------------
	void SAIController::update()
	{
		Flt delta = 0;
		Flt currTick = MGTimeOp::getCurrTick();

		if(mLastUpdateTime != 0)
		{
			delta = (currTick - mLastUpdateTime) / 1000;
		}

		AIController::update(delta);

		mLastUpdateTime = currTick;
	}

	//--------------------------------------------------------------------------
	void SAIController::setPeaceState()
	{
		AIController::setPeaceState();
		mOwner->getAIManager()->clear();
		mAIFightTrigger = NULL;
		BaseAIInfo* baseAIInfo = NULL;

		for(std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_PEACE].begin(); it !=  mBaseAIGroup->aiBaseAIInfoList[BAH_PEACE].end(); ++it)
		{
			baseAIInfo = it->second;

			switch( baseAIInfo->aiBaseType)
			{
			case BAT_RANDOMMOVE:
				{
					SAIRandomMove* aiRandomMove = SAIObjectManager::getInstance().createSAIRandomMove(mOwner);
					aiRandomMove->setAIParam(mCenterPos, (Flt)baseAIInfo->paramList[0], (Flt)baseAIInfo->paramList[1], (Flt)baseAIInfo->paramList[2], (Flt)baseAIInfo->paramList[3]);
					aiRandomMove->addAIListener(this);

					mOwner->getAIManager()->push(aiRandomMove, false);
				}
				break;

			case BAT_GUARD:
				{
					SAIGuard* aiGuard = SAIObjectManager::getInstance().createSAIGuard(mOwner);
					aiGuard->setAIParam((Flt)baseAIInfo->paramList[0], mCurrGuardRadius, baseAIInfo->paramList[3], baseAIInfo->paramList[4]);
					aiGuard->addAIListener(this);

					mOwner->getAIManager()->push(aiGuard, false);
				}
				break;
			}
		}
	}

	//--------------------------------------------------------------------------
	void SAIController::updateFightState( Flt delta )
	{
		switch(mFightState)
		{
		case FS_PREPAR:
			{
				mOwner->getAIManager()->clear();
				mAIFightTrigger = NULL;

				mAIFightTrigger = SAIObjectManager::getInstance().createSAIFightTrigger(mOwner);
				mAIFightTrigger->setCurrTarget(mTargetType, mTargetId);
				mAIFightTrigger->addAIListener(this);

				mOwner->getAIManager()->push((SAIFightTrigger*)mAIFightTrigger, false);

				mFightState = FS_SELECTSKILL;

				{
					std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_HATEDETECT);
					if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
					{
						SAIHateDetect* aiHateDetect = SAIObjectManager::getInstance().createSAIHateDetect(mOwner);

						BaseAIInfo* baseAIInfo = it->second;
						aiHateDetect->setCurrTarget(mTargetType, mTargetId, mTargetIndex);
						aiHateDetect->setHateRatio(baseAIInfo->paramList[0]);
						aiHateDetect->addAIListener(this);

						mOwner->getAIManager()->push(aiHateDetect, false);
					}
				}


				{
					std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_KEEPDISTANCE);
					if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
					{
						SAIKeepDistance* aiKeepDistance = SAIObjectManager::getInstance().createSAIKeepDistance(mOwner);

						BaseAIInfo* baseAIInfo = it->second;
						mKeepDistance = baseAIInfo->paramList[1];
						aiKeepDistance->setAIParam((Flt)baseAIInfo->paramList[0], mKeepDistance, (Flt)baseAIInfo->paramList[2], mTargetType, mTargetId, mTargetIndex);
						aiKeepDistance->addAIListener(this);

						mOwner->getAIManager()->push(aiKeepDistance, false);
					}
				}


			}

			break;

		case FS_SELECTSKILL:
			{
				mUseSkillId = 0;

				std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_SELECTSKILL);
				if(it == mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
				{
					mFightState = FS_PURSUE;
					mPursueState = PS_STARTPURSUE;
					return;
				}

				SAISelectSkill* aiSelectSkillInAdvance = SAIObjectManager::getInstance().createSAISelectSkill(mOwner);
				aiSelectSkillInAdvance->setSelectSkill(mSkillRatioList);
				aiSelectSkillInAdvance->addAIListener(this);

				mOwner->getAIManager()->push(aiSelectSkillInAdvance, false);
			}
			break;

		case FS_PURSUE:
			updatePursue(delta);
			break;

		case FS_ATTACK:
			{
				if(mUseSkillId == 0)
				{
					mFightState = FS_SELECTSKILL;
					return;
				}

				updateAttack(delta);

			}
			break;

		case FS_MOVETOKEEPDISPOS:
			{
				SCharacter* targetCharacter = 0;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), mTargetType, mTargetId, mTargetIndex);
				if(!targetCharacter || targetCharacter->isDead())
				{
					mFightState = FS_PREPAR;
					mPauseThinkTime = 1;

					return;
				}

				Vec3 currOwnerPos = mOwner->getPos();
				currOwnerPos.y = 0;

				Vec3 currTargetPos = targetCharacter->getPos();
				currTargetPos.y = 0;

				Flt moveToPosDis = (currOwnerPos - mMoveToPos).length();
				Flt targetPosDis = (currOwnerPos - currTargetPos).length();

				if(moveToPosDis < 1 || targetPosDis >= mKeepDistance)
				{
					mFightState = FS_PREPAR;
				}
				else
				{
					mOwner->moveToPos(mOwner->getPos(), mMoveToPos);
				}

				mPauseThinkTime = 1;
			}
			break;

		case FS_HELPMOVETO:
			{
				SCharacter* targetCharacter = 0;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), mTargetType, mTargetId, mTargetIndex);
				if(!targetCharacter || targetCharacter->isDead())
				{
					setPeaceState();
					mPauseThinkTime = 1;

					return;
				}

				Vec3 currOwnerPos = mOwner->getPos();
				currOwnerPos.y = 0;

				Vec3 currTargetPos = targetCharacter->getPos();
				currTargetPos.y = 0;
				Flt targetPosDis = (currOwnerPos - currTargetPos).length();

				if(targetPosDis < mPursueRadius)
				{
					mFightState = FS_PREPAR;
				}
				else
				{
					mOwner->moveToPos(mOwner->getPos(), mMoveToPos);
				}

				mPauseThinkTime = 1;
			}
			break;
		}
	}

	//--------------------------------------------------------------------------
	void SAIController::updateReturn( Flt delta )
	{
		switch(mReturnState)
		{
		case RS_START:
			{
				mOwner->getAIManager()->clear();
				mAIFightTrigger = NULL;

				if(mBaseAIGroup->aiBaseAIInfoList[BAH_ENDFIGHT].size())
				{
					BaseAIInfo* baseAIInfo = mBaseAIGroup->aiBaseAIInfoList[BAH_ENDFIGHT][BAT_RETURN];
					SAIReturn* aiReturn = SAIObjectManager::getInstance().createSAIReturn(mOwner);
					aiReturn->setReturnType(((SAIReturn::ReturnType)((UInt)baseAIInfo->paramList[0])));
					Vec3 returnPos = mOwner->getFightManager()->getEnterFightPos();
					aiReturn->setReturnToPos(returnPos);
					aiReturn->addAIListener(this);

					mOwner->getAIManager()->push(aiReturn, false);

					mReturnState = RS_RETURNING;
				}
				else
				{
					setPeaceState();
				}

			}
			break;
		case RS_RETURNING:
			break;
		case RS_END:
			mPauseThinkTime = 2;
			setPeaceState();
			break;
		}
	}

	//-------------------------------------------------------------------------
	void SAIController::onEnterFight( GameObject* fightObject )
	{
		{
			std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_STARTFIGHT].find(BAT_SEEKHELP);
			if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_STARTFIGHT].end())
			{
				SAISeekHelp* aiSeekHelp = SAIObjectManager::getInstance().createSAISeekHelp(mOwner);
				aiSeekHelp->setSeekHelpRadius(it->second->paramList[0]);

				vector<UInt> helpTemplateList;
				helpTemplateList.push_back(it->second->paramList[1]);
				helpTemplateList.push_back(it->second->paramList[2]);
				helpTemplateList.push_back(it->second->paramList[3]);
				helpTemplateList.push_back(it->second->paramList[4]);

				aiSeekHelp->setSeekHelpTemplate(helpTemplateList);
				aiSeekHelp->setTarget(mTargetType, mTargetId, mTargetIndex);
				aiSeekHelp->addAIListener(this);

				mOwner->getAIManager()->push(aiSeekHelp, false);
			}
		}

		{
			std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_STARTFIGHT].find(BAT_ESCAPE);
			if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_STARTFIGHT].end())
			{
				SAIEscape* aiEscape = SAIObjectManager::getInstance().createSAIEscape(mOwner);
				aiEscape->setAIParam(it->second->paramList[0], it->second->paramList[1], it->second->paramList[2], it->second->paramList[3]);
				aiEscape->addAIListener(this);

				mOwner->getAIManager()->push(aiEscape, false);
			}
		}

		{
			std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_HATEDETECT);
			if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
			{
				SAIHateDetect* aiHateDetect = SAIObjectManager::getInstance().createSAIHateDetect(mOwner);
				
				BaseAIInfo* baseAIInfo = it->second;

				mTargetType = GOT_UNKNOWN;
				mTargetId = 0;
				mTargetIndex = 0;

				aiHateDetect->setCurrTarget(mTargetType, mTargetId, mTargetIndex);
				aiHateDetect->setHateRatio(baseAIInfo->paramList[0]);
				aiHateDetect->addAIListener(this);

				mOwner->getAIManager()->push(aiHateDetect, false);
			}
		}
	}

	//-------------------------------------------------------------------------
	void  SAIController::onEndFight( GameObject* fightObject )
	{
		mTargetType = GOT_UNKNOWN;
		mTargetId = 0;
		mTargetIndex = 0;

		setReturnState();
		mOwner->clearFightAITriggerCount();
	}

	//-------------------------------------------------------------------------
	void SAIController::updatePursue( Flt delta )
	{
		switch(mPursueState)
		{
		case PS_STARTPURSUE:
			{
				std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_PURSUE);
				if(it == mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
				{
					mFightState = FS_ATTACK;
					mAttackState = AS_STARTATTACK;
					return;
				}

				//if(!mIsContinuePursue)
				//{
				//	setPeaceState();
				//	mIsContinuePursue = true;
				//	return;
				//}

				SAIPursue* aiPursue = SAIObjectManager::getInstance().createSAIPursue(mOwner);

				aiPursue->setTarget(mTargetType, mTargetId, mTargetIndex);
				aiPursue->setPursueRadius(mPursueRadius);
				aiPursue->addAIListener(this);
				if(mUseSkillId != 0)
				{
					const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(mUseSkillId);
					if(skillInfo)
					{
						aiPursue->setStopPursueRadius(((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->range);
					}
				}

				mOwner->getAIManager()->push(aiPursue, false);

				mPursueState = PS_PURSUEING;
			}

			break;
		case PS_PURSUEING:
			break;
		case PS_ENDPURSUE:
			break;
		}
	}

	//-------------------------------------------------------------------------
	void SAIController::updateAttack( Flt delta )
	{
		switch(mAttackState)
		{
		case AS_STARTATTACK:
			{
				SAIAttack* aiAttackInAdvance  = SAIObjectManager::getInstance().createSAIAttack(mOwner);
				aiAttackInAdvance->setUseSkillId(mUseSkillId);
				aiAttackInAdvance->setTarget(mTargetType, mTargetId, mTargetIndex);
				aiAttackInAdvance->addAIListener(this);

				mOwner->getAIManager()->push(aiAttackInAdvance, false);

				mAttackState = AS_ATTACKING;
			}

			break;
		case AS_ATTACKING:
			break;
		case AS_ENDATTACK:
			break;
		}
	}

	//-------------------------------------------------------------------------
	Bool SAIController::isDead()
	{
		return mOwner->isDead();	
	}

}