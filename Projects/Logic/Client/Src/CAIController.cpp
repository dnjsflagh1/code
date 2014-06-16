/******************************************************************************/
#include "stdafx.h"
#include "CAIController.h"
#include "BaseAIGroupTemplate.h"
#include "CCharacterSceneEntity.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CharacterList.h"
#include "CharacterSkillTempLate.h"
#include "CAIManager.h"
#include "SkillInfoList.h"
#include "CSceneManager.h"


/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	CAIController::CAIController( CCharacterSceneEntity* owner )
		:mOwner(owner)
		,mKeepDistance(0)
		,mCurrGuardRadius(0)
		,mPursueRadius(0)
		,mIsPause(false)
	{

	}

	//--------------------------------------------------------------------------
	CAIController::~CAIController()
	{

	}

	//--------------------------------------------------------------------------
	void CAIController::Init()
	{
		mBaseAIGroup = (BaseAIGroup*)mOwner->getBaseAIGroup();
		if ( mBaseAIGroup == NULL )
			return;

		mCenterPos = mOwner->getPos();

		std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_SELECTSKILL);
		if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
		{
			UInt characterTemplateId = 0;
			if(mOwner->getType() == GOT_SOLDIER)
			{
				characterTemplateId = ((CTroopSoldierEntity*)mOwner)->getTroopEntity()->getDynamicData()->mCharacterTemplateID;
			}
			else
			{
				characterTemplateId = mOwner->getDynamicData()->mCharacterTemplateID;
			}

			const CharacterTempInfo* characterTempInfo = CharacterTemplate::getInstance().getCharacterTempInfo(characterTemplateId);
			if(!characterTempInfo)
			{
				return;
			}

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
			//mCurrGuardRadius = mOwner->getSkillOwnManager()->getMinSkillAttackDis();
		}
		else if(mPursueRadius < mCurrGuardRadius)
		{
			mCurrGuardRadius = mPursueRadius;
		}

		setPeaceState();
	}

	//--------------------------------------------------------------------------
	void CAIController::update( Flt delta )
	{
		if(mIsPause)
		{
			return;
		}

		AIController::update(delta);
	}

	//--------------------------------------------------------------------------
	void CAIController::setPeaceState()
	{
		if ( mBaseAIGroup == NULL )
			return;

		AIController::setPeaceState();
		mOwner->getAIStateManager().clear();
		mAIFightTrigger = NULL;
		BaseAIInfo* baseAIInfo = NULL;

		mOwner->getDynamicData()->isFightState = false;

		for(std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_PEACE].begin(); it !=  mBaseAIGroup->aiBaseAIInfoList[BAH_PEACE].end(); ++it)
		{
			baseAIInfo = it->second;

			switch( baseAIInfo->aiBaseType)
			{
			case BAT_RANDOMMOVE:
				{
					CAIEntityRandomPathFindingMove* aiEntityRandomPathFindingMoveInAdvance = CAIManager::getInstance().createCAIEntityRandomPathFindingMove(mOwner);
					aiEntityRandomPathFindingMoveInAdvance->setAIParam(mCenterPos, (Flt)baseAIInfo->paramList[0], (Flt)baseAIInfo->paramList[1], (Flt)baseAIInfo->paramList[2]);
					aiEntityRandomPathFindingMoveInAdvance->addAIListener(this);

					mOwner->getAIStateManager().push(aiEntityRandomPathFindingMoveInAdvance, false);
				}
				break;

			case BAT_GUARD:
				{
					CAIEntityGuard* aiEntityGuardInAdvance = CAIManager::getInstance().createCAIEntityGuard(mOwner);
					aiEntityGuardInAdvance->setAIParam((Flt)baseAIInfo->paramList[0], mCurrGuardRadius, baseAIInfo->paramList[3], baseAIInfo->paramList[4]);
					aiEntityGuardInAdvance->addAIListener(this);

					mOwner->getAIStateManager().push(aiEntityGuardInAdvance, false);
				}
				break;
			}
		}
	}

	//--------------------------------------------------------------------------
	void CAIController::setFightState()
	{
		AIController::setFightState();
		mOwner->getDynamicData()->isFightState = true;
	}

	//--------------------------------------------------------------------------
	void CAIController::setReturnState()
	{
		AIController::setReturnState();
		mOwner->getDynamicData()->isFightState = false; 
	}

	//--------------------------------------------------------------------------
	void CAIController::setIsPause( Bool isPause )
	{
		if(isPause == false && mIsPause == true)
		{
			setPeaceState();
		}
		else if(isPause == true && mIsPause == false)
		{
			if(mOwner->getType() == GOT_TROOP)
			{
				((CTroopEntity*)mOwner)->clearAIState();
				((CTroopEntity*)mOwner)->clearActionState();
			}
			else
			{
				mOwner->getAIStateManager().clear();
				mOwner->getActionStateManager().clear();
			}

			mPauseThinkTime = 2;
		}

		mIsPause = isPause;
	}

	//--------------------------------------------------------------------------
	Bool CAIController::getIsPause()
	{
		return mIsPause;
	}

	//--------------------------------------------------------------------------
	void CAIController::updateFightState( Flt delta )
	{
		if ( mBaseAIGroup == NULL )
			return;

		switch(mFightState)
		{
		case FS_PREPAR:
			{
				mOwner->getAIStateManager().clear();
				mAIFightTrigger = NULL;

				mAIFightTrigger = CAIManager::getInstance().createCAIEntityFightTrigger(mOwner);
				mAIFightTrigger->setCurrTarget(mTargetType, mTargetId);
				mAIFightTrigger->addAIListener(this);

				mOwner->getAIStateManager().push((CAIEntityFightTrigger*)mAIFightTrigger, false);

				mFightState = FS_SELECTSKILL;

				std::map<BaseAIType, BaseAIInfo*>::iterator it = mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].find(BAT_KEEPDISTANCE);
				if(it != mBaseAIGroup->aiBaseAIInfoList[BAH_FIGHT].end())
				{
					CAIEntityKeepDistance* entityKeepDistanceInAdvance = CAIManager::getInstance().createCAIEntityKeepDistance(mOwner);

					BaseAIInfo* baseAIInfo = it->second;
					mKeepDistance = baseAIInfo->paramList[1];
					entityKeepDistanceInAdvance->setAIParam((Flt)baseAIInfo->paramList[0], mKeepDistance, (Flt)baseAIInfo->paramList[2], mTargetType, mTargetId, mTargetIndex);
					entityKeepDistanceInAdvance->addAIListener(this);

					mOwner->getAIStateManager().push(entityKeepDistanceInAdvance, false);
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

				CAIEntitySelectSkill* entitySelectSkillInAdvance = CAIManager::getInstance().createCAIEntitySelectSkill(mOwner);
				entitySelectSkillInAdvance->setSelectSkill(mSkillRatioList);
				entitySelectSkillInAdvance->addAIListener(this);

				mOwner->getAIStateManager().push(entitySelectSkillInAdvance, false);
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
				CCharacterSceneEntity* targetCharacter = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
				if(!targetCharacter || targetCharacter->getDynamicData()->isDied)
				{
					mFightState = FS_PREPAR;
					mPauseThinkTime = 1;

					return;
				}

				Vec3 currOwnerPos = mOwner->getPos();
				Vec3 currTargetPos = targetCharacter->getPos();

				Flt moveToPosDis = (currOwnerPos - mMoveToPos).length();
				Flt targetPosDis = (currOwnerPos - currTargetPos).length();

				if(moveToPosDis <= 1 || targetPosDis >= mKeepDistance)
				{
					mFightState = FS_PREPAR;
				}
				else
				{
					CAIEntityPathFindingMoveInAdvance* entityPathFindingMoveInAdvance = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(mOwner);
					entityPathFindingMoveInAdvance->setDestination(mMoveToPos);
					mOwner->getAIStateManager().push(entityPathFindingMoveInAdvance, true);
				}

				mPauseThinkTime = 1;
			}
			break;
		}
	}

	//--------------------------------------------------------------------------
	void CAIController::updateReturn( Flt delta )
	{
		if ( mBaseAIGroup == NULL )
			return;

		switch(mReturnState)
		{
		case RS_START:
			{
				mOwner->getAIStateManager().clear();
				mAIFightTrigger = NULL;

				if(mBaseAIGroup->aiBaseAIInfoList[BAH_ENDFIGHT].size())
				{
					BaseAIInfo* baseAIInfo = mBaseAIGroup->aiBaseAIInfoList[BAH_ENDFIGHT][BAT_RETURN];
					CAIEntityReturn* entityReturnInAdvance = CAIManager::getInstance().createCAIEntityReturn(mOwner);
					entityReturnInAdvance->setIsMoveTo(((BOOL)baseAIInfo->paramList[0]));
					entityReturnInAdvance->setReturnToPos(mCenterPos);
					entityReturnInAdvance->addAIListener(this);

					mOwner->getAIStateManager().push(entityReturnInAdvance, false);

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
				setPeaceState();
			break;
		}
	}

	//-------------------------------------------------------------------------
	void CAIController::updatePursue( Flt delta )
	{
		if(!mBaseAIGroup)
			return;

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

				if(!mIsContinuePursue)
				{
					setPeaceState();
					mIsContinuePursue = true;
					return;
				}

				CAIEntityPathFindingPursue* entityPathFindingPursueInAdvance = CAIManager::getInstance().createCAIEntityPathFindingPursue(mOwner);
				entityPathFindingPursueInAdvance->setTarget(mTargetType, mTargetId, mTargetIndex);
				entityPathFindingPursueInAdvance->setPursueRadius((Flt)it->second->paramList[0]);
				entityPathFindingPursueInAdvance->addAIListener(this);
				if(mUseSkillId != 0)
				{
					const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(mUseSkillId);
					if(skillInfo)
					{
						Flt stopPursueRadius = 0;
						Flt skillRange = ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->range;

						CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
						if(!targetEntity || targetEntity->getDynamicData()->isDied)
						{
							setPeaceState();
							return;
						}

						if(mTargetId != 0)
						{
							if(mOwner->getType() == GOT_TROOP)
							{
								stopPursueRadius = mOwner->getEntity()->getModelObject()->getPatherRadius() + targetEntity->getEntity()->getModelObject()->getPatherRadius() + 1.5;
								if(skillRange > stopPursueRadius)
								{
									stopPursueRadius = skillRange;
								}
							}
							else
							{
								stopPursueRadius = mOwner->getEntity()->getModelObject()->getWidth() / 2 + targetEntity->getEntity()->getModelObject()->getPatherRadius() + skillRange;
							}
						}
						else
						{
							stopPursueRadius = mOwner->getEntity()->getModelObject()->getWidth() / 2 + skillRange;
						}


						//if(mOwner->getType() == GOT_TROOP && skillInfo->skillType == SKT_SHORTRANGEGENERAL)
						//{
						//	CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
						//	if(targetEntity && !targetEntity->getDynamicData()->isDied)
						//	{
						//		stopPursueRadius = mOwner->getEntity()->getModelObject()->getPatherRadius() + targetEntity->getEntity()->getModelObject()->getPatherRadius() + 1;
						//	}
						//}
						//else
						//{
						//	stopPursueRadius = ((InitiativeSkillBasicInfo*)skillInfo->skillInfo)->range;
						//}
	
						entityPathFindingPursueInAdvance->setStopPursueRadius(stopPursueRadius);
					}
				}

				mOwner->getAIStateManager().push(entityPathFindingPursueInAdvance, false);

				mPursueState = PS_PURSUEING;
			}

			break;
		case PS_PURSUEING:

			if(!mIsContinuePursue)
			{
				setPeaceState();
				mIsContinuePursue = true;
				return;
			}

			break;
		case PS_ENDPURSUE:
			break;
		}
	}

	//-------------------------------------------------------------------------
	void CAIController::updateAttack( Flt delta )
	{
		if(!mBaseAIGroup)
			return;

		switch(mAttackState)
		{
		case AS_STARTATTACK:
			{
				CAIEntityAttack* entityAttackInAdvance  = CAIManager::getInstance().createCAIEntityAttack(mOwner);
				entityAttackInAdvance->setUseSkillId(mUseSkillId);
				entityAttackInAdvance->setTarget(mTargetType, mTargetId, mTargetIndex);
				entityAttackInAdvance->addAIListener(this);

				mOwner->getAIStateManager().push(entityAttackInAdvance, false);

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
	Bool CAIController::isDead()
	{
		return mOwner->getDynamicData()->isDied;
	}
}