/******************************************************************************/
#include "stdafx.h"
#include "SAIKeepDistance.h"
#include "SWorldManager.h"
#include "SCharacter.h"
#include "CharacterList.h"
#include "SAIController.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str SAIKeepDistance::STATE_NAME = "SAIKeepDistance";

	//--------------------------------------------------------------------------
	SAIKeepDistance::SAIKeepDistance( SCharacter* owner )
		:LinedStateObject(STATE_NAME)
		,SAI(owner)
		,mCheckInterval(0)
		,mCheckRatio(0)
		,mKeepDistance(0)
		,mPauseThinkTime(0)
		,mTargetType(GOT_UNKNOWN)
		,mTargetId(0)
		,mTargetIndex(0)
	{
		mAIType = AIT_KEEPDISTANCE;
	}

	//--------------------------------------------------------------------------
	SAIKeepDistance::~SAIKeepDistance()
	{
	}

	//-----------------------------------------------------------------------
	void SAIKeepDistance::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		mPauseThinkTime = mCheckInterval; 

		UInt ratio = MGRandom::getInstance().rand_ab_One(0,1000);
		if(ratio > mCheckRatio)
		{
			return;
		}

		Vec3 keepDisPos; 

		if(isKeepDistance(keepDisPos))
		{
			notifyKeepDistance(keepDisPos);

			destroy();
			return;
		}
	}				 

	//-----------------------------------------------------------------------
	Bool SAIKeepDistance::isFinished()
	{
		return false;
	}

	//-----------------------------------------------------------------------
	void SAIKeepDistance::onEnter()
	{

	}

	//-----------------------------------------------------------------------
	void SAIKeepDistance::onLeave()
	{
		notifyEnd();
	}

	//-----------------------------------------------------------------------
	void SAIKeepDistance::notifyKeepDistance ( Vec3 keepDisPos )
	{
		if(mAIListener)
		{
			mAIListener->onKeepDistance(keepDisPos);
		}
	}

	//-----------------------------------------------------------------------
	Bool SAIKeepDistance::isKeepDistance( Vec3& pos )
	{
		SCharacter* targetCharacter = 0;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), mTargetType, mTargetId, mTargetIndex);
		if(!targetCharacter || targetCharacter->isDead())
		{
			return false;
		}

		Vec3 currPos = mOwner->getPos();
		Vec3 dir = currPos - targetCharacter->getPos();

		Flt dis = dir.length();
		if(dis < mKeepDistance)
		{
			dir.normalise();
			pos = currPos + dir * mKeepDistance;

			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------
	void SAIKeepDistance::setAIParam( Flt checkInterval, UInt checkRatio, Flt keepDistance, GAMEOBJ_TYPE	targetType, GameObjectIdType targetId, UInt	targetIndex )
	{
		mCheckInterval = checkInterval;
		mCheckRatio = checkRatio;
		mKeepDistance = keepDistance;
		mTargetType = targetType;
		mTargetId = targetId;
		mTargetIndex = targetIndex;
	}
}