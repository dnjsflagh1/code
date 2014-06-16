
/******************************************************************************/
#include "stdafx.h"
#include "SSkillObject.h"
#include "SLuaSkillSystem.h"
#include "SkillNetPacketProcesser.h"
#include "SkillBaseInfo.h"
#include "SWorldManager.h"
//#include "STroopSoldier.h"
//#include "STroopNew.h"
////#include "Character.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
	SSkillObject::SSkillObject( SCharacter* owner )
		:mLastTime(0)
    {
		mOwnerType = owner->getType();
		if(mOwnerType != GOT_SOLDIER)
		{
			mOwnerId = owner->getID();
			mOwnerIndex = 0;
		}
		else
		{
			//mOwnerId = ((STroopSoldier*)owner)->getTroop()->getID();
			mOwnerIndex = owner->getID();
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
	void SSkillObject::onSkillStartClant()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillUpdateClant( Flt delta )
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillEndClant()
	{
	
	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillClantFinished()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillStartInject()
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillUpdateInject( Flt delta )
	{

	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillEndInject()
	{
 
	}

	//-----------------------------------------------------------------------
	void SSkillObject::onSkillInjectFinished()
	{

	}

}