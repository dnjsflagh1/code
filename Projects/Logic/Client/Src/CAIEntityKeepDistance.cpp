/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityKeepDistance.h"
#include "CSceneManager.h"
#include "CCharacterSceneEntity.h"
#include "CAIManager.h"
#include "ClientMain.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CPlayer.h"
#include "CharacterList.h"
#include "CAIController.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityKeepDistance::STATE_NAME = "CAIEntityKeepDistanceInAdvance";

	//--------------------------------------------------------------------------
	CAIEntityKeepDistance::CAIEntityKeepDistance( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,CAI(characterSceneEntity)
		,mCheckInterval(0)
		,mCheckRatio(0)
		,mKeepDistance(0)
		,mPauseThinkTime(0)
	{
		mAIType = AIT_KEEPDISTANCE;
	}

	//--------------------------------------------------------------------------
	CAIEntityKeepDistance::~CAIEntityKeepDistance()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityKeepDistance::update( Flt delta )
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
	Bool CAIEntityKeepDistance::isFinished()
	{
		return false;
	}

	//-----------------------------------------------------------------------
	void CAIEntityKeepDistance::onEnter()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityKeepDistance::onLeave()
	{
		notifyEnd();
	}

	//-----------------------------------------------------------------------
	void CAIEntityKeepDistance::notifyKeepDistance ( Vec3 keepDisPos )
	{
		if(mAIListener)
		{
			mAIListener->onKeepDistance(keepDisPos);
		}
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityKeepDistance::isKeepDistance( Vec3& pos )
	{
		CCharacterSceneEntity* targetCharacter = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
		if(!targetCharacter || targetCharacter->getDynamicData()->isDied)
		{
			return false;
		}

		Vec3 currPos = mOwner->getPos();
		Vec3 dir = currPos - targetCharacter->getPos();

		Flt dis = dir.length();
		if(dis >= mKeepDistance)
		{
			dir.normalise();
			pos = currPos + dir * mKeepDistance;

			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------
	void CAIEntityKeepDistance::setAIParam( Flt checkInterval, UInt checkRatio, Flt keepDistance, GAMEOBJ_TYPE	targetType, GameObjectIdType targetId, UInt	targetIndex )
	{
		mCheckInterval = checkInterval;
		mCheckRatio = checkRatio;
		mKeepDistance = keepDistance;
		mTargetType = targetType;
		mTargetId = targetId;
		mTargetIndex = targetIndex;
	}
}