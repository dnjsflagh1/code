/******************************************************************************/
#include "stdafx.h"
#include "SAIRandomMove.h"
#include "SCharacter.h"
#include "SAIManager.h"
#include "SActionManager.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------

    Str SAIRandomMove::STATE_NAME = "SAIRandomMove";

    //--------------------------------------------------------------------------
    SAIRandomMove::SAIRandomMove( SCharacter* owner )
        :LinedStateObject(STATE_NAME)
		,SAI(owner)
		,mMinMoveRadius(0)
		,mMaxMoveRadius(0)
		,mMinInterval(0)
		,mMaxInterval(0)
		,mIsStartMove(false)
		,mPauseThinkTime(0)
    {
		mAIType = AIT_RANDOMMOVE;
    }

    //--------------------------------------------------------------------------
    SAIRandomMove::~SAIRandomMove()
    {
    }

    //-----------------------------------------------------------------------
    void SAIRandomMove::update( Flt delta )
    {
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		if(!mIsStartMove && !mOwner->getActionManager()->getState("SCharacterMoveToAction", false))
		{	
			UInt intervalTime = MGRandom::getInstance().rand_ab_One(mMinInterval, mMaxInterval);
			mPauseThinkTime = intervalTime;

			mIsStartMove = true;
		}

		if(mIsStartMove)
		{
			mDestination = getRandomMoveToPos();
			mOwner->moveToPos(mOwner->getPos(), mDestination);

			mIsStartMove = false;
		}

    }

    //-----------------------------------------------------------------------
    Bool SAIRandomMove::isFinished()
    {
        return false;
    }

    //-----------------------------------------------------------------------
    void SAIRandomMove::onEnter()
    {
		if(mOwner->isDead())
		{
			destroy();
			return;
		}
    }

    //-----------------------------------------------------------------------
    void SAIRandomMove::onLeave()
    {
		mOwner->stopMove();
		notifyEnd();
    }

	//-----------------------------------------------------------------------
	Vec3 SAIRandomMove::getRandomMoveToPos()
	{
		Vec3 dir(1,0,0);
		Int angle = MGRandom::getInstance().rand_ab_One(0, 360);
		Int dis = MGRandom::getInstance().rand_ab_One(mMinMoveRadius, mMaxMoveRadius);
		dir = MGMath::rotateVector(dir, angle * (MG_PI / 180));
		return mCenterPos + dir * dis;
	}

	//-----------------------------------------------------------------------
	void SAIRandomMove::setAIParam( Vec3 centerPos, Flt minInterval, Flt maxInterval, Flt minMoveRadius, Flt maxMoveRadius  )
	{
		mCenterPos = centerPos;
		mMinInterval = minInterval;
		mMaxInterval = maxInterval;
		mMinMoveRadius = minMoveRadius;
		mMaxMoveRadius = maxMoveRadius;

		if(mMaxMoveRadius < mMinMoveRadius)
		{
			mMaxMoveRadius = mMinMoveRadius + 1;
		}
	}


}