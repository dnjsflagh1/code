
/******************************************************************************/
#include "stdafx.h"
#include "SSkillObject.h"
#include "SLuaSkillSystem.h"
#include "SSkillNetPacketProcesser.h"
#include "SkillBaseInfo.h"
#include "SWorldManager.h"
#include "SCDManager.h"
#include "STroop.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
	SSkillObject::SSkillObject( SCharacter* owner )
		:mLastTime(0)
		,mOwner(owner)
		,mIsExecScript(true)
    {
		mOwnerType = owner->getType();
		if(mOwnerType != GOT_SOLDIER)
		{
			mOwnerId = owner->getID();
			mOwnerIndex = 0;
		}
		else
		{
			//mOwnerId = ((STroopSoldier*)owner)->getOwnerTroop()->getID();
			//mOwnerIndex = owner->getID();
		}
    }

    //-----------------------------------------------------------------------
    SSkillObject::~SSkillObject()
    {
        
    }

	//-----------------------------------------------------------------------
	void SSkillObject::update( Flt delta )
	{
		Flt currTime = MGTimeOp::getCurrTick();
		SkillObject::update((currTime - mLastTime));
		mLastTime = currTime;
	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillStartClantLogic()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillClantUpdateLogic()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillEndClantLogic()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillStartClantScript()
	{
	
	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillClantUpdateScript()
	{
	
	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillEndClantScript()
	{
		
	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillStartInjectLogic()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillInjectUpdateLogic()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillEndInjectLogic()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillStartInjectScript()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillInjectUpdateScript()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::execServerSkillEndInjectScript()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillStartClant()
	{
		if(mIsExecScript)
		{
			execServerSkillStartClantScript();
		}
		else
		{
			execServerSkillStartClantLogic();
		}
	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillUpdateClant( Flt delta )
	{
		if(mIsExecScript)
		{
			execServerSkillClantUpdateScript();
		}
		else
		{
			execServerSkillClantUpdateLogic();
		}
	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillEndClant()
	{
		if(mIsExecScript)
		{
			execServerSkillEndClantScript();
		}
		else
		{
			execServerSkillEndClantLogic();
		}
	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillClantFinished()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillStartInject()
	{
		if(mIsExecScript)
		{
			execServerSkillStartInjectScript();
		}
		else
		{
			execServerSkillStartInjectLogic();
		} 
	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillUpdateInject( Flt delta )
	{
		if(mIsExecScript)
		{
			execServerSkillInjectUpdateScript();
		}
		else
		{
			execServerSkillInjectUpdateLogic();
		}
	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillEndInject()
	{
		if(mIsExecScript)
		{
			execServerSkillEndInjectScript();
		}
		else
		{
			execServerSkillEndInjectLogic();
		} 
	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillInjectFinished()
	{

	}




}