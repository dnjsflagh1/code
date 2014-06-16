/******************************************************************************/
#include "stdafx.h"
#include "CAIController.h"
#include "CAIManager.h"
#include "CAIEntityPathFindingPursue.h"
#include "CSceneManager.h"
#include "CCharacterSceneEntity.h"
#include "IBlockManager.h"
#include "ClientMain.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CPlayer.h"
#include "CharacterList.h"
#include "CAIEntityPathFindingMoveInAdvance.h"
#include "PlayCharacterNetPacketProcesser.h"
#include "TroopNetPacketProcesser.h"

/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityPathFindingPursue::STATE_NAME = "CAIEntityPathFindingPursue";

	//--------------------------------------------------------------------------
	CAIEntityPathFindingPursue::CAIEntityPathFindingPursue( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,CAI(characterSceneEntity)
		,mTargetId(0)
		,mTargetIndex(0)
		,mTargetType(GOT_UNKNOWN)
		,mPathFindingMoveAI(0)
		,mIsFinished(false)
		,mPauseThinkTime(0)
		,mPursueRadius(0)
		,mStopPursueRadius(0)
	{
		mAIType = AIT_PURSUE;
	}

	//--------------------------------------------------------------------------
	CAIEntityPathFindingPursue::~CAIEntityPathFindingPursue()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::update( Flt delta )
	{
		updatePursue(delta);
	}				 

	//-----------------------------------------------------------------------
	Bool CAIEntityPathFindingPursue::isFinished()
	{
		return mIsFinished;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::onEnter()
	{
		if(mOwner->getDynamicData()->isDied)
		{
			destroy();
			return;
		}

		Flt targetPatherRadius = 0;

		//如果目标是object
		if(mTargetId != 0)
		{
			CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
			if(!targetEntity)
			{
				notifyEnd();
				destroy();
				return;
			}

			if(targetEntity->getDynamicData()->isDied)
			{
				notifyTargetDied();
				destroy();
				return;
			}

			targetEntity->getEntity()->getSceneNode()->getPosition(mTargetPos);
		}


		mMoveToPos = mTargetPos;
		mMoveToPos.y = 0;

		Flt patherRadius = mOwner->getEntity()->getModelObject()->getPatherRadius();
		// 通过半径计算出所占用网格大小
		mBlockDiameter = patherRadius * 2 / ClientMain::getInstance().getScene()->getBlockManager()->getDynamicBlockGridSize();

		mPursueRadius = patherRadius * 2 + mPursueRadius;

		mPoint = mOwner->getPos();

	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::onLeave()
	{
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::setTarget(GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index)
	{
		mTargetType = gameType;
		mTargetId = id;
		mTargetIndex = index;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::setTarget(Vec3 pos)
	{
		mTargetPos = pos;
	}


	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::updatePursue( Flt delta )
	{
		if(mTargetId != 0)
		{
			CCharacterSceneEntity* targetEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
			if(!targetEntity)
			{
				notifyEnd();
				destroy();
				return;
			}

			if(targetEntity->getDynamicData()->isDied)
			{
				notifyTargetDied();
				destroy();
				return;
			}

			targetEntity->getEntity()->getSceneNode()->getPosition(mTargetPos);
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
		Flt dis = (mPoint -  mOwner->getPos()).length();
		if(dis > mPursueRadius)
		{
			if(mPathFindingMoveAI)
			{
				mPathFindingMoveAI->destroy();
			}

			if(mOwner->getType() == GOT_PLAYERCHARACTER)
			{
				PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterStopMoveToPackBuffer(mOwner->getID());
			}
			else if(mOwner->getType() == GOT_TROOP)
			{
				//TroopNetPacketProcesser::getInstance().sendTroopEntityStopMoveToPackBuffer(CPlayer::getInstance().getActiveClan()->getData()->regionType, CPlayer::getInstance().getActiveClan()->getData()->regionID, CPlayer::getInstance().getInstanceUid(), mOwner->getID());
			}

			notifyPursueResult(false);
			destroy();
			return;
		}

		dis = (mTargetPos - mOwner->getPos()).length();
		if(mStopPursueRadius == 0 || dis <= mStopPursueRadius || mPursueRadius == 0)
		{
			if(mPathFindingMoveAI)
			{
				mPathFindingMoveAI->destroy();
			}

			if(mOwner->getType() == GOT_PLAYERCHARACTER)
			{
				PlayCharacterNetPacketProcesser::getInstance().sendPlayerCharacterStopMoveToPackBuffer(mOwner->getID());
			}
			else if(mOwner->getType() == GOT_TROOP)
			{
				//TroopNetPacketProcesser::getInstance().sendTroopEntityStopMoveToPackBuffer(CPlayer::getInstance().getActiveClan()->getData()->regionType, CPlayer::getInstance().getActiveClan()->getData()->regionID, CPlayer::getInstance().getInstanceUid(), mOwner->getID());
			}

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

		mPathFindingMoveAI = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(mOwner);
		mPathFindingMoveAI->setDestination(mTargetPos);
		mOwner->getAIStateManager().push(mPathFindingMoveAI, false);
		mLastTargetPos = mTargetPos;

		stopThink(1);
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::stopThink( Flt time )
	{
		mPauseThinkTime = time;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::resumeThink()
	{
		mPauseThinkTime = 0;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::notifyPursueResult( Bool isFinish )
	{
		if(mAIListener)
		{
			mAIListener->onPursueResult(isFinish);
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::notifyTargetDied()
	{
		if(mAIListener)
		{
			mAIListener->onTargetDied();
		}
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::setPursueRadius( Flt pursueRadius )
	{
		mPursueRadius = pursueRadius;
	}

	//-----------------------------------------------------------------------
	void CAIEntityPathFindingPursue::setStopPursueRadius( Flt stopPursueRadius )
	{
		mStopPursueRadius = stopPursueRadius;
	}
}