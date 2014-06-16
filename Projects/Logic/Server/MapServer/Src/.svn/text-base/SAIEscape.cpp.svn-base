#include "stdafx.h"
#include "SAIManager.h"
#include "WorldCoreDefine.h"
#include "SAIEscape.h"
#include "SAIController.h"
#include "SCharacter.h"
#include "SActionManager.h"

//#include "FightManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str SAIEscape::STATE_NAME = "SAIEscape";

	//--------------------------------------------------------------------------
	SAIEscape::SAIEscape( SCharacter* owner )
		:LinedStateObject(STATE_NAME)
		,SAI(owner)
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
	SAIEscape::~SAIEscape()
	{
	}

	//-----------------------------------------------------------------------
	void SAIEscape::update( Flt delta )
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

		if(!mIsStartMove && !mOwner->getActionManager()->getState("SCharacterMoveToAction" ,false))
		{	
			UInt intervalTime = MGRandom::getInstance().rand_ab_One(mMinInterval, mMaxInterval);
			mPauseThinkTime = intervalTime;

			mIsStartMove = true;
		}

		if(mIsStartMove)
		{
			mDestination = getEscapeMoveToPos();
			mOwner->moveToPos(mOwner->getPos(), mDestination);

			mIsStartMove = false;
		}

	}

	//-----------------------------------------------------------------------
	Bool SAIEscape::isFinished()
	{
		return false;
	}

	//-----------------------------------------------------------------------
	void SAIEscape::onEnter()
	{
		if(mOwner->isDead())
		{
			destroy();
			return;
		}

		mStartEscapeTime = MGTimeOp::getCurrTick();
		mCenterPos = mOwner->getPos();
	}

	//-----------------------------------------------------------------------
	void SAIEscape::onLeave()
	{
		notifyEnd();
	}

	//-----------------------------------------------------------------------
	Vec3 SAIEscape::getEscapeMoveToPos()
	{
		Vec3 dir(1,0,0);
		Int angle = MGRandom::getInstance().rand_ab_One(0, 360);
		Int dis = MGRandom::getInstance().rand_ab_One(1, mEscapeRadius);
		dir = MGMath::rotateVector(dir, angle * (MG_PI / 180));
		return mCenterPos + dir * dis;
	}

	//-----------------------------------------------------------------------
	void SAIEscape::setAIParam( UInt escapeRadius,  Flt escapeTime , Flt minInterval, Flt maxInterval )
	{
		mEscapeRadius = escapeRadius;
		mEscapeTime = escapeTime * 1000;
		mMinInterval = minInterval;
		mMaxInterval = maxInterval;
	}

	//-----------------------------------------------------------------------
	void SAIEscape::notifyEscapeEnd()
	{
		if(mAIListener)
		{
			mAIListener->onEscapeEnd();
		}
	}


}