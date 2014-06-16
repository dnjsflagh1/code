#include "stdafx.h"
#include "CAIManager.h"
#include "CSceneManager.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "WorldCoreDefine.h"
#include "CAIEntityEscape.h"
#include "CAIController.h"

//#include "FightManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityEscape::STATE_NAME = "CAIEntityEscape";

	//--------------------------------------------------------------------------
	CAIEntityEscape::CAIEntityEscape( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,CAI(characterSceneEntity)
		,mEscapeRadius(0)
		,mMinInterval(0)
		,mMaxInterval(0)
		,mIsStartMove(false)
		,mPauseThinkTime(0)
		,mEscapeTime(0)
		,mStartEscapeTime(0)
	{
		mAIType = AIT_ESCAPE;
	}

	//--------------------------------------------------------------------------
	CAIEntityEscape::~CAIEntityEscape()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityEscape::update( Flt delta )
	{
		if(MGTimeOp::getCurrTick() - mStartEscapeTime >= mEscapeTime)
		{
			notifyEscapeEnd();
			destroy();
			return;
		}

		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		if(!mIsStartMove && !mOwner->getAIStateManager().getState("CAIEntityPathFindingMoveInAdvance", false))
		{	
			UInt intervalTime = MGRandom::getInstance().rand_ab_One(mMinInterval, mMaxInterval);
			mPauseThinkTime = intervalTime / 1000;

			mIsStartMove = true;
		}

		if(mIsStartMove)
		{
			mDestination = getEscapeMoveToPos();
			CAIEntityPathFindingMoveInAdvance*  pathFindingMoveInAdvance = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(mOwner);
			pathFindingMoveInAdvance->setDestination(mDestination);

			mOwner->getAIStateManager().push(pathFindingMoveInAdvance, false);
			mIsStartMove = false;
		}

	}

	//-----------------------------------------------------------------------
	Bool CAIEntityEscape::isFinished()
	{
		return false;
	}

	//-----------------------------------------------------------------------
	void CAIEntityEscape::onEnter()
	{
		if(mOwner->getDynamicData()->isDied)
		{
			destroy();
			return;
		}

		mStartEscapeTime = MGTimeOp::getCurrTick();
		mCenterPos = mOwner->getPos();
	}

	//-----------------------------------------------------------------------
	void CAIEntityEscape::onLeave()
	{
		notifyEnd();
	}

	//-----------------------------------------------------------------------
	Vec3 CAIEntityEscape::getEscapeMoveToPos()
	{
		Vec3 dir(1,0,0);
		Int angle = MGRandom::getInstance().rand_ab_One(0, 360);
		Int dis = MGRandom::getInstance().rand_ab_One(1, mEscapeRadius);
		dir = MGMath::rotateVector(dir, angle * (MG_PI / 180));
		return mCenterPos + dir * dis;
	}

	//-----------------------------------------------------------------------
	void CAIEntityEscape::setAIParam( UInt escapeRadius,  Flt escapeTime , Flt minInterval, Flt maxInterval )
	{
		mEscapeRadius = escapeRadius;
		mEscapeTime = escapeTime;
		mMinInterval = minInterval;
		mMaxInterval = maxInterval;
	}

	//-----------------------------------------------------------------------
	void CAIEntityEscape::notifyEscapeEnd()
	{
		if(mAIListener)
		{
			mAIListener->onEscapeEnd();
		}
	}


}