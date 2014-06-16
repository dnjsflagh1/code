/******************************************************************************/
#include "stdafx.h"
#include "CAIController.h"
#include "CAIEntityReturn.h"
#include "ICollisionSystem.h"
#include "CCharacterSceneEntity.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "WorldCoreDefine.h"

//#include "FightManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityReturn::STATE_NAME = "CAIEntityReturn";

	//--------------------------------------------------------------------------
	CAIEntityReturn::CAIEntityReturn( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,CAI(characterSceneEntity)
		,mIsMoveTo(true)
		,mPauseThinkTime(0)
	{
		mAIType = AIT_RETURN;
	}

	//--------------------------------------------------------------------------
	CAIEntityReturn::~CAIEntityReturn()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityReturn::onEnter()
	{
		if(mOwner->getDynamicData()->isDied)
		{
			destroy();
			return;
		}

		CAIEntityPathFindingMoveInAdvance* pathFindingMoveAI = CAIManager::getInstance().createCAIEntityPathFindingMoveInAdvance(mOwner);
		pathFindingMoveAI->setDestination(mReturnPos);
		mOwner->getAIStateManager().push(pathFindingMoveAI, false);
	}

	//-----------------------------------------------------------------------
	void CAIEntityReturn::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		Vec3 currPos = mOwner->getPos();
		Flt dis = (currPos - mReturnPos).length();

		if(dis < 1)
		{
			notifyReturnFinish();
		}

		mPauseThinkTime = 1;
	}

	//-----------------------------------------------------------------------
	void CAIEntityReturn::onLeave()
	{
		notifyEnd();
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityReturn::isFinished()
	{
		return false;
	}
	
	//-----------------------------------------------------------------------
	void CAIEntityReturn::notifyReturnFinish()
	{
		if(mAIListener)
		{
			mAIListener->onReturnFinish();
		}
	}

	//-----------------------------------------------------------------------

	void CAIEntityReturn::setIsMoveTo( Bool isMoveTo )
	{
		mIsMoveTo = isMoveTo;
	}

	//-----------------------------------------------------------------------
	void CAIEntityReturn::setReturnToPos( Vec3 pos )
	{
		mReturnPos = pos;
	}

}