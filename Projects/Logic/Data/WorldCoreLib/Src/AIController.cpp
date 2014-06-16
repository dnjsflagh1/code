/******************************************************************************/
#include "stdafx.h"
#include "AIController.h"
#include "BaseAIGroupTemplate.h"
#include "CharacterList.h"
#include "CharacterSkillTempLate.h"
#include "SkillInfoList.h"

/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	AIController::AIController()
		:mState(ACS_NULL)
		,mBaseAIGroup(NULL)
		,mFightState(FS_NULL)
		,mPursueState(PS_NULLVALUE)
		,mAttackState(AS_NULLVALUE)
		,mReturnState(RS_NULL)
		,mUseSkillId(0)
		,mAIFightTrigger(NULL)
		,mTargetType(GOT_UNKNOWN)
		,mTargetId(0)
		,mTargetIndex(0)
		,mIsContinuePursue(true)
		,mPauseThinkTime(0)
	{
	}

	//--------------------------------------------------------------------------
	AIController::~AIController()
	{

	}

	//--------------------------------------------------------------------------
	void AIController::Init()
	{

	}

	//--------------------------------------------------------------------------
	void AIController::update( Flt delta )
	{
		if(!mBaseAIGroup)
			return;

		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		if(isDead())
		{
			return;
		}

		switch(mState)
		{
		case ACS_BIRTH:
			setPeaceState();
			break;

		case ACS_PEACE:
			break;

		case ACS_STARTFIGHT:
			break;

		case ACS_FIGHT:
			updateFightState(delta);
			break;

		case ACS_ENDFIGHT:
			break;

		case ACS_RETURN:
			updateReturn(delta);
			break;
		}
	}

	//--------------------------------------------------------------------------
	Flt AIController::getAIPauseTime()
	{
		Flt pauseTime = MGRandom::getInstance().rand_ab_One(0, 600);
		pauseTime /= 1000;

		return pauseTime;
	}

	//--------------------------------------------------------------------------
	void AIController::setPeaceState()
	{
		mState = ACS_PEACE;
	}

	//--------------------------------------------------------------------------
	void AIController::setFightState()
	{
		mState = ACS_FIGHT;
		//mPauseThinkTime = getAIPauseTime();
	}

	//--------------------------------------------------------------------------
	void AIController::setHelpMoveToState()
	{
		mState = ACS_FIGHT;
		mFightState = FS_HELPMOVETO;
	}

	//--------------------------------------------------------------------------
	void AIController::setReturnState()
	{
		mState = ACS_RETURN;
		mReturnState = RS_START;
	}

	//--------------------------------------------------------------------------
	void AIController::setBirthState()
	{
		mState = ACS_BIRTH;
		mPauseThinkTime = 2;
	}

	//--------------------------------------------------------------------------
	void AIController::updateFightState( Flt delta )
	{

	}

	//--------------------------------------------------------------------------
	void AIController::updatePursue( Flt delta )
	{

	}

	//--------------------------------------------------------------------------
	void AIController::updateReturn( Flt delta )
	{
	}

	//--------------------------------------------------------------------------
	void AIController::onSearchTarget( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		mTargetType = targetType;
		mTargetId = targetId;
		mTargetIndex = targetIndex;

		setFightState();
		mFightState = FS_PREPAR;
	}

	//--------------------------------------------------------------------------
	void AIController::onFightTrigger( FightTriggerEvent& fightTriggerEvent )
	{
		switch(fightTriggerEvent.fightTriggerEventType)
		{
		case FTET_BUFF:
			break;

		case FTET_SKILL:
			mFightState = FS_PURSUE;
			mPursueState = PS_STARTPURSUE;
			mUseSkillId = fightTriggerEvent.eventParam1;
			break;
		}
	}

	//--------------------------------------------------------------------------
	void AIController::onPursueResult( Bool isFinish )
	{
		if(!isFinish)
		{
			setReturnState();
			mIsContinuePursue = false;
			return;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
		}

		mFightState = FS_ATTACK;
		mAttackState = AS_STARTATTACK;
	}

	//--------------------------------------------------------------------------
	void AIController::onSelectSkillResult( UInt skillId )
	{
		mFightState = FS_PURSUE;
		mPursueState = PS_STARTPURSUE;
		mUseSkillId = skillId;

		//mPauseThinkTime = getAIPauseTime();
	}

	//--------------------------------------------------------------------------
	void AIController::onChangeTargetForHate( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex )
	{
		mFightState = FS_PURSUE;
		mPursueState = PS_STARTPURSUE;
		mTargetType = targetType;
		mTargetId = targetId;
		mTargetIndex = targetIndex;

		//mPauseThinkTime = getAIPauseTime();
	}

	//--------------------------------------------------------------------------
	void AIController::onKeepDistance( Vec3 keepDisPos )
	{
		mMoveToPos = keepDisPos;
		mFightState = FS_MOVETOKEEPDISPOS;
	}

	//-------------------------------------------------------------------------
	void AIController::onReturnFinish()
	{
		mReturnState = RS_END;
	}

	//--------------------------------------------------------------------------
	void AIController::onAttackEnd()
	{
		mFightState = FS_SELECTSKILL;

		//if(mUseSkillId != 0)
		//{
		//	const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(mUseSkillId);
		//	if(skillInfo)
		//	{
		//		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)(skillInfo->skillInfo);
		//		mPauseThinkTime = (Flt)(initiativeSkillBasicInfo->actionTime + initiativeSkillBasicInfo->attackFrontTime + initiativeSkillBasicInfo->attackBehindTime) /*/ 1000*/;
		//	}
		//}
	}

	//--------------------------------------------------------------------------
	void AIController::onEscapeEnd()
	{
		setFightState();
	}

	//-------------------------------------------------------------------------
	void AIController::onTargetDied()
	{
		setReturnState();
	}

	//-------------------------------------------------------------------------
	void AIController::onEnd( AI* ai )
	{
		switch(ai->getAIType())
		{
		case AIT_ATTACK:
			mFightState = FS_SELECTSKILL;
			break;

		case AIT_RANDOMMOVE:
			break;

		case AIT_GUARD:
			break;

		case AIT_PURSUE:
			mFightState = FS_ATTACK;
			mAttackState = AS_STARTATTACK;
			break;

		case AIT_KEEPDISTANCE:
			break;

		case AIT_SELECTSKILL:
			mFightState = FS_PURSUE;
			mPursueState = PS_STARTPURSUE;
			break;

		case AIT_RETURN:
			break;
		}
	}

	//-------------------------------------------------------------------------
	AIControllerState AIController::getAIControllerState()
	{
		return mState;
	}

	//-------------------------------------------------------------------------

}