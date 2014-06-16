/******************************************************************************/
#include "stdafx.h"
#include "SkillObject.h"
//#include "SkillEffectSystem.h"
#include "GameObject.h"
#include "SkillBaseInfo.h"
/******************************************************************************/

namespace MG
{

	//-----------------------------------------------------------------------
	SkillObject::SkillObject()
		:mState(SKILLSTATE_NONE)
		,mIsFinished(false)
		,mTargetObjectType(GOT_UNKNOWN)
		,mTargetObjectID(0)		
		,mTargetObjectIndex(0)
		,mOwnerType(GOT_UNKNOWN)
		,mOwnerId(0)
		,mOwnerIndex(0)
		,mUpdateTime(0)
		,mPauseUpdateTime(0)
	{
	}

    //-----------------------------------------------------------------------
    SkillObject::SkillObject( GAMEOBJ_TYPE ownerType, GameObjectIdType ownerId, UInt ownerIndex )
		:mState(SKILLSTATE_NONE)
        ,mIsFinished(false)
		,mTargetObjectType(GOT_UNKNOWN)
		,mTargetObjectID(0)		
		,mTargetObjectIndex(0)
		,mOwnerType(ownerType)
		,mOwnerId(ownerId)
		,mOwnerIndex(ownerIndex)
		,mUpdateTime(0)
		,mPauseUpdateTime(0)
    {
    }

    //-----------------------------------------------------------------------
    SkillObject::~SkillObject()
    {
    }
	
	//-----------------------------------------------------------------------
	void SkillObject::setSkillInfo( SkillInfo* skillInfo )
	{
		mSkillInfo = skillInfo;
	}

	//-----------------------------------------------------------------------
	SkillInfo* SkillObject::getSkillInfo()
	{
		return mSkillInfo;
	}

    //-----------------------------------------------------------------------
    void SkillObject::setTargetPosition(Vec3 pos)
    {
        mTargetPosition = pos;
    }

    //-----------------------------------------------------------------------
    Vec3 SkillObject::getTargetPosition()
    {
        return mTargetPosition;
    }

    //-----------------------------------------------------------------------
    void SkillObject::setTargetObject(GAMEOBJ_TYPE targetType, IdType targetId, Int targetIndex)
    {
        mTargetObjectType	= targetType;
		mTargetObjectID		= targetId;
		mTargetObjectIndex = targetIndex;
    }

    //-----------------------------------------------------------------------
    GAMEOBJ_TYPE SkillObject::getTargetObjectType()
    {
        return mTargetObjectType;
    }

    //-----------------------------------------------------------------------
    IdType SkillObject::getTargetObjectID()
    {
        return mTargetObjectID;
    }

	//-----------------------------------------------------------------------
	UInt SkillObject::getTargetObjectIndex()
	{
		return mTargetObjectIndex;
	}

    //-----------------------------------------------------------------------
    void SkillObject::stopUse()
    {
		mPhases = SKILLPHASES_END;
    }

    //-----------------------------------------------------------------------
    Bool SkillObject::isClanting()
    {
        return mState == SKILLSTATE_CLANT;
    }

    //-----------------------------------------------------------------------
    void SkillObject::startClant( Bool isUpdate  )
    {
		//stopUse();

        mState = SKILLSTATE_CLANT;
		mPhases = SKILLPHASES_START;

		mIsUpdate = isUpdate;
    }

    //-----------------------------------------------------------------------
    Bool SkillObject::isInjecting()
    {
        return mState == SKILLSTATE_INJECT;
    }

    //-----------------------------------------------------------------------
    void SkillObject::startInject( Bool isUpdate )
    {
		/*stopUse();*/

        mState = SKILLSTATE_INJECT;
		mPhases = SKILLPHASES_START;

		mIsUpdate = isUpdate;
		mIsFinished = false;

		mCurrTiming = 0;
    }

	//-----------------------------------------------------------------------
	GameObjectIdType SkillObject::getOwnerID()
	{
		return mOwnerId;
	}

	//-----------------------------------------------------------------------
	GAMEOBJ_TYPE SkillObject::getOwnerType()
	{
		return mOwnerType;
	}

	//-----------------------------------------------------------------------
	UInt SkillObject::getOwnerIndex()
	{
		return mOwnerIndex;
	}

	//-----------------------------------------------------------------------
	void SkillObject::setUpdateTime( Flt time )
	{
		mUpdateTime = time;
	}

	//-----------------------------------------------------------------------
	void SkillObject::onSkillFinished()
	{
		switch(mState)
		{
		case SKILLSTATE_CLANT:
			onSkillClantFinished();
			break;
		case SKILLSTATE_INJECT:
			onSkillInjectFinished();
			break;
		}

		mIsFinished = true;
	}

	//-----------------------------------------------------------------------
	void SkillObject::update( Flt delta ) 
	{
		if(mPauseUpdateTime > 0)
		{
			mPauseUpdateTime -= delta;
			return;
		}

		switch(mPhases)
		{
		case SKILLPHASES_START:
			onSkillStart();
			break;
		case SKILLPHASES_UPDATE: 
			onSkillUpdate( delta );
			break;
		case SKILLPHASES_END:
			onSkillEnd();
			break;
		}
	}

	//-----------------------------------------------------------------------
	void SkillObject::onSkillStart()
	{
		Flt pauseTime = 0;
		switch(mState)
		{
		case SKILLSTATE_CLANT:
			onSkillStartClant();
			pauseTime = (Flt)((InitiativeSkillBasicInfo*)mSkillInfo->skillInfo)->actionTime /*/ 1000*/;
			break;

		case SKILLSTATE_INJECT:
			onSkillStartInject();
			//mTotalTiming = (Flt)mSkillInfo->injectTime;
			break;
		}

		setUpdateTime(pauseTime);

		mPhases = SKILLPHASES_UPDATE;
	}

	//-----------------------------------------------------------------------
	void SkillObject::onSkillUpdate( Flt delta )
	{
		if (!mIsUpdate)
		{
			return;
		}

		if(mUpdateTime > 0)
		{
			mUpdateTime -= delta;

			switch(mState)
			{
			case SKILLSTATE_CLANT:
				onSkillUpdateClant( mCurrTiming );
				break;
			case SKILLSTATE_INJECT:
				onSkillUpdateInject( mCurrTiming );
				break;
			}
		}
		else
		{
			onSkillFinished();
			stopUse();
		}
	}

	//-----------------------------------------------------------------------
	void SkillObject::onSkillEnd()
	{
		switch(mState)
		{
		case SKILLSTATE_CLANT:
			onSkillEndClant();
			break;
		case SKILLSTATE_INJECT:
			onSkillEndInject();
			break;
		}

		mState = SKILLSTATE_NONE;
		mPhases = SKILLPHASES_NONE;
		mIsUpdate = false;
	}

	//-----------------------------------------------------------------------
	void SkillObject::setStopUpdateTime( Flt time )
	{
		mPauseUpdateTime = time;
	}


}