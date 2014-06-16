/******************************************************************************/
#include "stdafx.h"
#include "CAIManager.h"
/******************************************************************************/
namespace MG
{

    //--------------------------------------------------------------------------
    CAIManager::CAIManager()
        :mUpdateCurrIndex(0)
        ,mMaxUpdateLimitCount(10)
		,mUpdateLimitCount(0)
    {

    }

    //--------------------------------------------------------------------------
    CAIManager::~CAIManager()
    {

    }

	//--------------------------------------------------------------------------
	void CAIManager::addLimitCount()
	{
		mUpdateLimitCount++;
	}

	//--------------------------------------------------------------------------
	Bool CAIManager::isOverMaxLimitCount()
	{
		return mUpdateLimitCount > mMaxUpdateLimitCount;
	}

    //--------------------------------------------------------------------------
    void CAIManager::update( Flt delta )
    {
        if ( mUpdateLinedStateManagerList.empty() )
            return;

		mUpdateLimitCount = 0;
		UInt count = mUpdateLinedStateManagerList.size();
		if ( mUpdateCurrIndex >= count )
			mUpdateCurrIndex = 0;

        std::map< LinedStateManager*, Bool>::iterator iter = mUpdateLinedStateManagerList.begin();
        std::advance(iter, mUpdateCurrIndex);
        
		for ( UInt i=0; i<count; i++ )
		{
			if ( iter == mUpdateLinedStateManagerList.end() )
			{
				iter = mUpdateLinedStateManagerList.begin();
			}

			if ( iter->second )
			{
				iter->first->update( delta ); 
				iter++;
			}else
			{
				iter = mUpdateLinedStateManagerList.erase( iter );
			}

			if ( isOverMaxLimitCount() == false )
			{
				mUpdateCurrIndex++;
				if ( iter == mUpdateLinedStateManagerList.end() )
				{
					mUpdateCurrIndex = 0;
				}
			}
		}
    }

    //--------------------------------------------------------------------------
    void CAIManager::clear()
    {
        mUpdateLinedStateManagerList.clear();
        mUpdateCurrIndex = 0;
    }

    //--------------------------------------------------------------------------
    void CAIManager::addUpdateAIMgr( LinedStateManager* mgr )
    {
        mUpdateLinedStateManagerList[ mgr ] = true;
    }

    //--------------------------------------------------------------------------
    void CAIManager::removeUpdateAIMgr( LinedStateManager* mgr )
    {
        std::map< LinedStateManager*, Bool>::iterator iter = mUpdateLinedStateManagerList.find( mgr );
        if ( iter != mUpdateLinedStateManagerList.end() )
        {
            iter->second = false;
        }
    }

    //--------------------------------------------------------------------------
    CAIEntityGroupPathFindingGatherInAdvance* CAIManager::createCAIEntityGroupPathFindingGatherInAdvance()
    {
        CAIEntityGroupPathFindingGatherInAdvance* ai = MG_POOL_NEW(mCAIEntityGroupPathFindingGatherInAdvancePool, CAIEntityGroupPathFindingGatherInAdvance, ());

        ai->setManagedLifeTime( false );
        ai->addListener( this );

        return ai;
    }

    //--------------------------------------------------------------------------
    void CAIManager::destroyCAIEntityGroupPathFindingGatherInAdvance(CAIEntityGroupPathFindingGatherInAdvance* ai)
    {
        MG_POOL_DELETE(mCAIEntityGroupPathFindingGatherInAdvancePool, ai);
    }

    //--------------------------------------------------------------------------
    CAIEntityGroupPathFindingMoveInAdvance* CAIManager::createCAIEntityGroupPathFindingMoveInAdvance()
    {
        CAIEntityGroupPathFindingMoveInAdvance* ai = MG_POOL_NEW(mCAIEntityGroupPathFindingMoveInAdvancePool, CAIEntityGroupPathFindingMoveInAdvance, ());

        ai->setManagedLifeTime( false );
        ai->addListener( this );

        return ai;
    }

    //--------------------------------------------------------------------------
    void CAIManager::destroyCAIEntityGroupPathFindingMoveInAdvance(CAIEntityGroupPathFindingMoveInAdvance* ai)
    {
        MG_POOL_DELETE(mCAIEntityGroupPathFindingMoveInAdvancePool, ai);
    }

    //--------------------------------------------------------------------------
    CAIEntityGroupPathFindingPursueAttackInAdvance* CAIManager::createCAIEntityGroupPathFindingPursueAttackInAdvance()
    {
        CAIEntityGroupPathFindingPursueAttackInAdvance* ai = MG_POOL_NEW(mCAIEntityGroupPathFindingPursueAttackInAdvancePool, CAIEntityGroupPathFindingPursueAttackInAdvance, ());

        ai->setManagedLifeTime( false );
        ai->addListener( this );

        return ai;
    }

	//--------------------------------------------------------------------------
	CAIEntityGroupInteractiveInAdvance* CAIManager::createCAIEntityGroupInteractiveInAdvance()
	{
		CAIEntityGroupInteractiveInAdvance* ai = MG_POOL_NEW(mCAIEntityGroupInteractiveInAdvancePool, CAIEntityGroupInteractiveInAdvance, ());

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntityGroupInteractiveInAdvance(CAIEntityGroupInteractiveInAdvance* ai)
	{
		MG_POOL_DELETE(mCAIEntityGroupInteractiveInAdvancePool, ai);
	}

    //--------------------------------------------------------------------------
    void CAIManager::destroyCAIEntityGroupPathFindingPursueAttackInAdvance(CAIEntityGroupPathFindingPursueAttackInAdvance* ai)
    {
        MG_POOL_DELETE(mCAIEntityGroupPathFindingPursueAttackInAdvancePool, ai);
    }

    //--------------------------------------------------------------------------
    CAIEntityPathFindingMoveInAdvance* CAIManager::createCAIEntityPathFindingMoveInAdvance( CCharacterSceneEntity* characterSceneEntity )
    {
        CAIEntityPathFindingMoveInAdvance* ai = MG_POOL_NEW(mCAIEntityPathFindingMoveInAdvancePool, CAIEntityPathFindingMoveInAdvance, (characterSceneEntity));

        ai->setManagedLifeTime( false );
        ai->addListener( this );

        return ai;
    }

    //--------------------------------------------------------------------------
    void CAIManager::destroyCAIEntityPathFindingMoveInAdvance(CAIEntityPathFindingMoveInAdvance* ai)
    {
        MG_POOL_DELETE(mCAIEntityPathFindingMoveInAdvancePool, ai);
    }

    //--------------------------------------------------------------------------
    CAIEntityGuard* CAIManager::createCAIEntityGuard( CCharacterSceneEntity* characterSceneEntity )
    {
        CAIEntityGuard* ai = MG_POOL_NEW(mCAIEntityGuardInAdvancePool, CAIEntityGuard, (characterSceneEntity));

        ai->setManagedLifeTime( false );
        ai->addListener( this );

        return ai;
    }

    //--------------------------------------------------------------------------
    void CAIManager::destroyCAIEntityGuard(CAIEntityGuard* ai)
    {
        MG_POOL_DELETE(mCAIEntityGuardInAdvancePool, ai);
    }

    //--------------------------------------------------------------------------
    CAIEntityRandomPathFindingMove* CAIManager::createCAIEntityRandomPathFindingMove( CCharacterSceneEntity* characterSceneEntity )
    {
        CAIEntityRandomPathFindingMove* ai = MG_POOL_NEW(mCAIEntityRandomPathFindingMoveInAdvancePool, CAIEntityRandomPathFindingMove, (characterSceneEntity));

        ai->setManagedLifeTime( false );
        ai->addListener( this );

        return ai;
    }

    //--------------------------------------------------------------------------
    void CAIManager::destroyCAIEntityRandomPathFindingMove(CAIEntityRandomPathFindingMove* ai)
    {
        MG_POOL_DELETE(mCAIEntityRandomPathFindingMoveInAdvancePool, ai);
	}

	//--------------------------------------------------------------------------
	CAIEntityAttack* CAIManager::createCAIEntityAttack( CCharacterSceneEntity* characterSceneEntity )
	{
		CAIEntityAttack* ai = MG_POOL_NEW(mCAIEntityAttackPool, CAIEntityAttack, (characterSceneEntity));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntityAttack(CAIEntityAttack* ai)
	{
		 MG_POOL_DELETE(mCAIEntityAttackPool, ai);
	}

	//--------------------------------------------------------------------------
	CAIEntityFightTrigger* CAIManager::createCAIEntityFightTrigger( CCharacterSceneEntity* characterSceneEntity )
	{
		CAIEntityFightTrigger* ai = MG_POOL_NEW(mCAIEntityFightTriggerPool, CAIEntityFightTrigger, (characterSceneEntity));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntityFightTrigger(CAIEntityFightTrigger* ai)
	{
		 MG_POOL_DELETE(mCAIEntityFightTriggerPool, ai);
	}

	//--------------------------------------------------------------------------
	CAIEntityKeepDistance*	CAIManager::createCAIEntityKeepDistance( CCharacterSceneEntity* characterSceneEntity )
	{
		CAIEntityKeepDistance* ai = MG_POOL_NEW(mCAIEntityKeepDistanceInAdvancePool, CAIEntityKeepDistance, (characterSceneEntity));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntityKeepDistance(CAIEntityKeepDistance* ai)
	{
		 MG_POOL_DELETE(mCAIEntityKeepDistanceInAdvancePool, ai);
	}


	//--------------------------------------------------------------------------
	CAIEntityEscape* CAIManager::createCAIEntityEscape( CCharacterSceneEntity* characterSceneEntity )
	{
		CAIEntityEscape* ai = MG_POOL_NEW(mCAIEntityEscapePool, CAIEntityEscape, (characterSceneEntity));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntityEscape(CAIEntityEscape* ai)
	{
		MG_POOL_DELETE(mCAIEntityEscapePool, ai);
	}

	//--------------------------------------------------------------------------
	CAIEntityPathFindingPursue* CAIManager::createCAIEntityPathFindingPursue( CCharacterSceneEntity* characterSceneEntity )
	{
		CAIEntityPathFindingPursue* ai = MG_POOL_NEW(mCAIEntityPathFindingPursueInAdvancePool, CAIEntityPathFindingPursue, (characterSceneEntity));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntityPathFindingPursue(CAIEntityPathFindingPursue* ai)
	{
		 MG_POOL_DELETE(mCAIEntityPathFindingPursueInAdvancePool, ai);
	}

	//--------------------------------------------------------------------------
	CAIEntitySelectSkill* CAIManager::createCAIEntitySelectSkill( CCharacterSceneEntity* characterSceneEntity )
	{
		CAIEntitySelectSkill* ai = MG_POOL_NEW(mCAIEntitySelectSkillInAdvancePool, CAIEntitySelectSkill, (characterSceneEntity));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntitySelectSkill(CAIEntitySelectSkill* ai)
	{
		 MG_POOL_DELETE(mCAIEntitySelectSkillInAdvancePool, ai);
	}

	//--------------------------------------------------------------------------
	CAIEntityReturn* CAIManager::createCAIEntityReturn( CCharacterSceneEntity* characterSceneEntity )
	{
		CAIEntityReturn* ai = MG_POOL_NEW(mCAIEntityReturnPool, CAIEntityReturn, (characterSceneEntity));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntityReturn(CAIEntityReturn* ai)
	{
		MG_POOL_DELETE(mCAIEntityReturnPool, ai);
	}

    //--------------------------------------------------------------------------
    CAIEntityPathFindingMoveAndGuardInAdvance* CAIManager::createCAIEntityPathFindingMoveAndGuardInAdvance( CCharacterSceneEntity* characterSceneEntity )
    {
        CAIEntityPathFindingMoveAndGuardInAdvance* ai = MG_POOL_NEW(mCAIEntityPathFindingMoveAndGuardInAdvancePool, CAIEntityPathFindingMoveAndGuardInAdvance, (characterSceneEntity));

        ai->setManagedLifeTime( false );
        ai->addListener( this );

        return ai;
    }

    //--------------------------------------------------------------------------
    void CAIManager::destroyCAIEntityPathFindingMoveAndGuardInAdvance(CAIEntityPathFindingMoveAndGuardInAdvance* ai)
    {
        MG_POOL_DELETE(mCAIEntityPathFindingMoveAndGuardInAdvancePool, ai);
    }

    //--------------------------------------------------------------------------
    CAIEntityPathFindingPursueAttackInAdvance* CAIManager::createCAIEntityPathFindingPursueAttackInAdvance( CCharacterSceneEntity* characterSceneEntity )
    {
        CAIEntityPathFindingPursueAttackInAdvance* ai = MG_POOL_NEW(mCAIEntityPathFindingPursueAttackInAdvancePool, CAIEntityPathFindingPursueAttackInAdvance, (characterSceneEntity));

        ai->setManagedLifeTime( false );
        ai->addListener( this );

        return ai;
    }

    //--------------------------------------------------------------------------
    void CAIManager::destroyCAIEntityPathFindingPursueAttackInAdvance(CAIEntityPathFindingPursueAttackInAdvance* ai)
    {
        MG_POOL_DELETE(mCAIEntityPathFindingPursueAttackInAdvancePool, ai);
    }



    //--------------------------------------------------------------------------
    void CAIManager::onLinedStateLifeTimeOver(LinedStateObject* obj)
    {
        if ( obj->getName() == CAIEntityGroupPathFindingGatherInAdvance::STATE_NAME )
        {
            destroyCAIEntityGroupPathFindingGatherInAdvance((CAIEntityGroupPathFindingGatherInAdvance*)obj);
        }else
        if ( obj->getName() == CAIEntityGroupPathFindingMoveInAdvance::STATE_NAME )
        {
            destroyCAIEntityGroupPathFindingMoveInAdvance((CAIEntityGroupPathFindingMoveInAdvance*)obj);
        }else
        if ( obj->getName() == CAIEntityGroupPathFindingPursueAttackInAdvance::STATE_NAME )
        {
            destroyCAIEntityGroupPathFindingPursueAttackInAdvance((CAIEntityGroupPathFindingPursueAttackInAdvance*)obj);
        }else
		if ( obj->getName() == CAIEntityGroupInteractiveInAdvance::STATE_NAME )
		{
			destroyCAIEntityGroupInteractiveInAdvance((CAIEntityGroupInteractiveInAdvance*)obj);
		}else
        ////////////////////////////////////////////////////////////////////////////////////////////////
        if ( obj->getName() == CAIEntityPathFindingMoveInAdvance::STATE_NAME )
        {
            destroyCAIEntityPathFindingMoveInAdvance((CAIEntityPathFindingMoveInAdvance*)obj);
        }else
        if ( obj->getName() == CAIEntityGuard::STATE_NAME )
        {
            destroyCAIEntityGuard((CAIEntityGuard*)obj);
        }else
        if ( obj->getName() == CAIEntityRandomPathFindingMove::STATE_NAME )
        {
            destroyCAIEntityRandomPathFindingMove((CAIEntityRandomPathFindingMove*)obj);
		}else
		if ( obj->getName() == CAIEntityAttack::STATE_NAME )
		{
			destroyCAIEntityAttack((CAIEntityAttack*)obj);
		}else
		if ( obj->getName() == CAIEntityFightTrigger::STATE_NAME )
		{
			destroyCAIEntityFightTrigger((CAIEntityFightTrigger*)obj);
		}else
		if ( obj->getName() == CAIEntityKeepDistance::STATE_NAME )
		{
			destroyCAIEntityKeepDistance((CAIEntityKeepDistance*)obj);
		}else
		if ( obj->getName() == CAIEntityPathFindingPursue::STATE_NAME )
		{
			destroyCAIEntityPathFindingPursue((CAIEntityPathFindingPursue*)obj);
		}else
		if ( obj->getName() == CAIEntityEscape::STATE_NAME )
		{
			destroyCAIEntityEscape((CAIEntityEscape*)obj);
		}else
		if ( obj->getName() == CAIEntitySelectSkill::STATE_NAME )
		{
			destroyCAIEntitySelectSkill((CAIEntitySelectSkill*)obj);
		}else
        if ( obj->getName() == CAIEntityPathFindingMoveAndGuardInAdvance::STATE_NAME )
        {
            destroyCAIEntityPathFindingMoveAndGuardInAdvance((CAIEntityPathFindingMoveAndGuardInAdvance*)obj);
        }else
        if ( obj->getName() == CAIEntityPathFindingPursueAttackInAdvance::STATE_NAME )
        {
            destroyCAIEntityPathFindingPursueAttackInAdvance((CAIEntityPathFindingPursueAttackInAdvance*)obj);
        }else
		if ( obj->getName() == CAIEntityInteractiveInAdvance::STATE_NAME )
		{
			destroyCAIEntityInteractiveInAdvance((CAIEntityInteractiveInAdvance*)obj);
		}else
		if ( obj->getName() == CAIEntityDie::STATE_NAME )
		{
			destroyCAIEntityDie((CAIEntityDie*)obj);
		}
    }
	
	//--------------------------------------------------------------------------
	CAIEntityInteractiveInAdvance* CAIManager::createCAIEntityInteractiveInAdvance( CCharacterSceneEntity* characterSceneEntity )
	{
		CAIEntityInteractiveInAdvance* ai = MG_POOL_NEW(mCAIEntityInteractiveInAdvancePool, CAIEntityInteractiveInAdvance, (characterSceneEntity));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntityInteractiveInAdvance(CAIEntityInteractiveInAdvance* ai)
	{
		 MG_POOL_DELETE(mCAIEntityInteractiveInAdvancePool, ai);
	}

	//--------------------------------------------------------------------------
	CAIEntityDie* CAIManager::createCAIEntityDie( CCharacterSceneEntity* characterSceneEntity )
	{
		CAIEntityDie* ai = MG_POOL_NEW(mCAIEntityDiePool, CAIEntityDie, (characterSceneEntity));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAIEntityDie(CAIEntityDie* ai)
	{
		MG_POOL_DELETE(mCAIEntityDiePool, ai);
	}

	//--------------------------------------------------------------------------
	CAITroopObjectSendSkillPacket* CAIManager::createCAITroopObjectSendSkillPacket()
	{
		CAITroopObjectSendSkillPacket* ai = MG_POOL_NEW(mCAITroopObjectSendSkillPacketPool, CAITroopObjectSendSkillPacket, ());

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void CAIManager::destroyCAITroopObjectSendSkillPacket(CAITroopObjectSendSkillPacket* ai)
	{
		 MG_POOL_DELETE(mCAITroopObjectSendSkillPacketPool, ai);
	}

}