/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityRandomPathFindingMove.h"
#include "CAIEntityPathFindingMoveAndGuardInAdvance.h"
#include "CCharacterSceneEntity.h"
#include "CAIManager.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------

    Str CAIEntityRandomPathFindingMove::STATE_NAME = "CAIEntityRandomPathFindingMoveInAdvance";

    //--------------------------------------------------------------------------
    CAIEntityRandomPathFindingMove::CAIEntityRandomPathFindingMove( CCharacterSceneEntity* characterSceneEntity )
        :LinedStateObject(STATE_NAME)
		,CAI(characterSceneEntity)
		,mMoveRadius(0)
		,mMinInterval(0)
		,mMaxInterval(0)
		,mIsStartMove(false)
		,mPauseThinkTime(0)
    {
		mAIType = AIT_RANDOMMOVE;
    }

    //--------------------------------------------------------------------------
    CAIEntityRandomPathFindingMove::~CAIEntityRandomPathFindingMove()
    {

    }

    //-----------------------------------------------------------------------
    void CAIEntityRandomPathFindingMove::update( Flt delta )
    {
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
			mDestination = getRandomMoveToPos();
			CAIEntityPathFindingMoveInAdvance*  pathFindingMoveInAdvance = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(mOwner);
			pathFindingMoveInAdvance->setDestination(mDestination);

			mOwner->getAIStateManager().push(pathFindingMoveInAdvance, false);
			mIsStartMove = false;
		}

    }

    //-----------------------------------------------------------------------
    Bool CAIEntityRandomPathFindingMove::isFinished()
    {
        return false;
    }

    //-----------------------------------------------------------------------
    void CAIEntityRandomPathFindingMove::onEnter()
    {
		if(mOwner->getDynamicData()->isDied)
		{
			destroy();
			return;
		}
    }

    //-----------------------------------------------------------------------
    void CAIEntityRandomPathFindingMove::onLeave()
    {
		notifyEnd();
    }

	//-----------------------------------------------------------------------
	Vec3 CAIEntityRandomPathFindingMove::getRandomMoveToPos()
	{
		Vec3 dir(1,0,0);
		Int angle = MGRandom::getInstance().rand_ab_One(0, 360);
		Int dis = MGRandom::getInstance().rand_ab_One(0, mMoveRadius);
		dir = MGMath::rotateVector(dir, angle * (MG_PI / 180));
		return mCenterPos + dir * dis;
	}

	//-----------------------------------------------------------------------
	void CAIEntityRandomPathFindingMove::setAIParam( Vec3 centerPos, Flt minInterval, Flt maxInterval, Flt moveRadius )
	{
		mCenterPos = centerPos;
		mMinInterval = minInterval;
		mMaxInterval = maxInterval;
		mMoveRadius = moveRadius;
	}


}