/******************************************************************************/
#include "stdafx.h"
#include "SAIController.h"
#include "SAIManager.h"
#include "SAIPursue.h"
#include "SWorldManager.h"
#include "SCharacter.h"
#include "CharacterList.h"
#include "SFightManager.h"

/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str SAIPursue::STATE_NAME = "SAIPursue";

	//--------------------------------------------------------------------------
	SAIPursue::SAIPursue( SCharacter* owner )
		:LinedStateObject(STATE_NAME)
		,SAI(owner)
		,mTargetId(0)
		,mTargetIndex(0)
		,mTargetType(GOT_UNKNOWN)
		/*,mPathFindingMoveAI(NULL)*/
		,mIsFinished(false)
		,mPauseThinkTime(0)
		,mPursueRadius(0)
		,mStopPursueRadius(0)
	{
		mAIType = AIT_PURSUE;
	}

	//--------------------------------------------------------------------------
	SAIPursue::~SAIPursue()
	{
	}

	//-----------------------------------------------------------------------
	void SAIPursue::update( Flt delta )
	{
		updatePursue(delta);
	}				 

	//-----------------------------------------------------------------------
	Bool SAIPursue::isFinished()
	{
		return mIsFinished;
	}

	//-----------------------------------------------------------------------
	void SAIPursue::onEnter()
	{
		if(mOwner->isDead())
		{
			destroy();
			return;
		}

		//如果目标是object
		if(mTargetId != 0)
		{
			SCharacter* targetEntity = 0;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), mTargetType, mTargetId, mTargetIndex);
			if(!targetEntity)
			{
				notifyEnd();
				destroy();
				return;
			}

			if(targetEntity->isDead())
			{
				notifyTargetDied();
				destroy();
				return;
			}

			mTargetPos = targetEntity->getPos();
		}


		mMoveToPos = mTargetPos;
		mMoveToPos.y = 0;

		mPoint = mOwner->getFightManager()->getEnterFightPos();
	}

	//-----------------------------------------------------------------------
	void SAIPursue::onLeave()
	{
		if(!mIsFinished)
		{
			mOwner->stopMove();
		}
	}

	//-----------------------------------------------------------------------
	void SAIPursue::setTarget(GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index)
	{
		mTargetType = gameType;
		mTargetId = id;
		mTargetIndex = index;
	}

	//-----------------------------------------------------------------------
	void SAIPursue::setTarget(Vec3 pos)
	{
		mTargetPos = pos;
	}


	//-----------------------------------------------------------------------
	void SAIPursue::updatePursue( Flt delta )
	{
		if(mTargetId != 0)
		{
			SCharacter* targetEntity = 0;//SWorldManager::getInstance().getCharacterFromSceneObject(mOwner->getRegionType(), mOwner->getRegionID(), mOwner->getCurrentRealRegionObject()->getInstanceUId(), mTargetType, mTargetId, mTargetIndex);
			if(!targetEntity)
			{
				notifyEnd();
				destroy();
				return;
			}

			if(targetEntity->isDead())
			{
				notifyTargetDied();
				destroy();
				return;
			}

			mTargetPos = targetEntity->getPos();
			mTargetPos.y = 0;

			// 这是有用的。还会回来的。
			//if(mCharacterSceneEntity->getEntity()->getSceneNode()->getScene()->getBlockManager()->isDynamicBlockByRadius(mMoveToPos, mBlockDiameter/*, IBlockManager::VERTEX_LEFTDOWN*/))
			//{
			//	Vec3 dir = mCharacterSceneEntity->getPos() - mMoveToPos /*mTargetPos*/;
			//	dir.normalise();
			//	mCharacterSceneEntity->getEntity()->getSceneNode()->getScene()->getBlockManager()->getPosNearestAccessiblePos(mTargetPos, dir, mBlockDiameter, mMoveToPos);
			//}		//if(mCharacterSceneEntity->getEntity()->getSceneNode()->getScene()->getBlockManager()->isDynamicBlockByRadius(mMoveToPos, mBlockDiameter/*, IBlockManager::VERTEX_LEFTDOWN*/))
			//{
			//	Vec3 dir = mCharacterSceneEntity->getPos() - mMoveToPos /*mTargetPos*/;
			//	dir.normalise();
			//	mCharacterSceneEntity->getEntity()->getSceneNode()->getScene()->getBlockManager()->getPosNearestAccessiblePos(mTargetPos, dir, mBlockDiameter, mMoveToPos);
			//}
		}

		//判断是否进入技能发射范围
		Flt dis = (mPoint -  mTargetPos).length();
		if(dis > mPursueRadius)
		{
			//if(mPathFindingMoveAI)
			//{
			//	mPathFindingMoveAI->destroy();
			//}

			mOwner->stopMove();

			notifyPursueResult(false);
			destroy();
			return;
		}

		Vec3 dir = mTargetPos - mOwner->getPos();
		dis = dir.length();
		if(mStopPursueRadius == 0 || dis <= mStopPursueRadius || mPursueRadius == 0)
		{
			//if(mPathFindingMoveAI)
			//{
			//	mPathFindingMoveAI->destroy();
			//}

			mOwner->stopMove();

			notifyPursueResult(true);
			destroy();
			return;

		}

		if(mTargetPos == mLastTargetPos)
		{
			return;
		}

		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		Vec3 ownerPos = mOwner->getPos();
		Vec3 newDir = ownerPos - mTargetPos;
		newDir.normalise();

		Int angle = MGRandom::getInstance().rand_ab_One(0, 360);
		newDir = MGMath::rotateVector(newDir, angle * (MG_PI / 180));

		Vec3 newTargetPos = mTargetPos + newDir * (mStopPursueRadius - 0.1);

		mOwner->moveToPos(ownerPos/*mOwner->getPos()*/, newTargetPos/*mTargetPos*/);

		mLastTargetPos = mTargetPos;

		stopThink(1);
	}

	//-----------------------------------------------------------------------
	void SAIPursue::stopThink( Flt time )
	{
		mPauseThinkTime = time;
	}

	//-----------------------------------------------------------------------
	void SAIPursue::resumeThink()
	{
		mPauseThinkTime = 0;
	}

	//-----------------------------------------------------------------------
	void SAIPursue::notifyPursueResult( Bool isFinish )
	{
		if(mAIListener)
		{
			mAIListener->onPursueResult(isFinish);
		}
	}

	//-----------------------------------------------------------------------
	void SAIPursue::notifyTargetDied()
	{
		if(mAIListener)
		{
			mAIListener->onTargetDied();
		}
	}

	//-----------------------------------------------------------------------
	void SAIPursue::setPursueRadius( Flt pursueRadius )
	{
		mPursueRadius = pursueRadius;
	}

	//-----------------------------------------------------------------------
	void SAIPursue::setStopPursueRadius( Flt stopPursueRadius )
	{
		mStopPursueRadius = stopPursueRadius;
	}
}