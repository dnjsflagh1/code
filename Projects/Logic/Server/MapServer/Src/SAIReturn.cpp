/******************************************************************************/
#include "stdafx.h"
#include "SAIController.h"
#include "SAIReturn.h"
#include "SCharacter.h"
#include "WorldCoreDefine.h"

//#include "FightManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str SAIReturn::STATE_NAME = "SAIReturn";

	//--------------------------------------------------------------------------
	SAIReturn::SAIReturn( SCharacter* owner )
		:LinedStateObject(STATE_NAME)
		,SAI(owner)
		,mReturnType(RT_MOVETO)
		,mPauseThinkTime(0)
	{
		mAIType = AIT_RETURN;
	}

	//--------------------------------------------------------------------------
	SAIReturn::~SAIReturn()
	{
	}	

	//-----------------------------------------------------------------------
	void SAIReturn::onEnter()
	{
		if(mOwner->isDead())
		{
			destroy();
			return;
		}
		
		switch(mReturnType)
		{
		case RT_INSTANT:
			mOwner->instantMoveToPos(mReturnPos);
			break;
		case RT_MOVETO:
			mOwner->moveToPos(mOwner->getPos(), mReturnPos);
			break;
		}

		
	}

	//-----------------------------------------------------------------------
	void SAIReturn::update( Flt delta )
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
			destroy();
			return;
		}

		mPauseThinkTime = 1;
	}

	//-----------------------------------------------------------------------
	void SAIReturn::onLeave()
	{
		notifyEnd();
	}

	//-----------------------------------------------------------------------
	Bool SAIReturn::isFinished()
	{
		return false;
	}
	
	//-----------------------------------------------------------------------
	void SAIReturn::notifyReturnFinish()
	{
		if(mAIListener)
		{
			mAIListener->onReturnFinish();
		}
	}

	//-----------------------------------------------------------------------

	void SAIReturn::setReturnType(  ReturnType returnType  )
	{
		mReturnType = returnType;
	}

	//-----------------------------------------------------------------------
	void SAIReturn::setReturnToPos( Vec3 pos )
	{
		mReturnPos = pos;
	}

}