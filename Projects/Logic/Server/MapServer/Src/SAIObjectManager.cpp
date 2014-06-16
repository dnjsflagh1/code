/******************************************************************************/
#include "stdafx.h"
#include "SAIObjectManager.h"
/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	SAIObjectManager::SAIObjectManager()
		:mUpdateCurrIndex(0)
		,mMaxUpdateLimitCount(10)
		,mUpdateLimitCount(0)
	{

	}

	//--------------------------------------------------------------------------
	SAIObjectManager::~SAIObjectManager()
	{

	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::addLimitCount()
	{
		mUpdateLimitCount++;
	}

	//--------------------------------------------------------------------------
	Bool SAIObjectManager::isOverMaxLimitCount()
	{
		return mUpdateLimitCount > mMaxUpdateLimitCount;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::update( Flt delta )
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
	void SAIObjectManager::clear()
	{
		mUpdateLinedStateManagerList.clear();
		mUpdateCurrIndex = 0;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::addUpdateAIMgr( LinedStateManager* mgr )
	{
		mUpdateLinedStateManagerList[ mgr ] = true;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::removeUpdateAIMgr( LinedStateManager* mgr )
	{
		std::map< LinedStateManager*, Bool>::iterator iter = mUpdateLinedStateManagerList.find( mgr );
		if ( iter != mUpdateLinedStateManagerList.end() )
		{
			iter->second = false;
		}
	}

	//--------------------------------------------------------------------------


	//--------------------------------------------------------------------------
	SAIGuard* SAIObjectManager::createSAIGuard( SCharacter* character )
	{
		SAIGuard* ai = MG_POOL_NEW(mSAIGuardPool, SAIGuard, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAIGuard(SAIGuard* ai)
	{
		MG_POOL_DELETE(mSAIGuardPool, ai);
	}

	//--------------------------------------------------------------------------
	SAIRandomMove* SAIObjectManager::createSAIRandomMove( SCharacter* character )
	{
		SAIRandomMove* ai = MG_POOL_NEW(mSAIRandomMovePool, SAIRandomMove, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAIRandomMove(SAIRandomMove* ai)
	{
		MG_POOL_DELETE(mSAIRandomMovePool, ai);
	}

	//--------------------------------------------------------------------------
	SAIAttack* SAIObjectManager::createSAIAttack( SCharacter* character )
	{
		SAIAttack* ai = MG_POOL_NEW(mSAIAttackPool, SAIAttack, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAIAttack( SAIAttack* ai )
	{
		MG_POOL_DELETE(mSAIAttackPool, ai);
	}

	//--------------------------------------------------------------------------
	SAISeekHelp* SAIObjectManager::createSAISeekHelp( SCharacter* character )
	{	
		SAISeekHelp* ai = MG_POOL_NEW(mSAISeekHelpPool, SAISeekHelp, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAISeekHelp( SAISeekHelp* ai )
	{
		MG_POOL_DELETE(mSAISeekHelpPool, ai);
	}

	//--------------------------------------------------------------------------
	SAIEscape* SAIObjectManager::createSAIEscape( SCharacter* character )
	{
		SAIEscape* ai = MG_POOL_NEW(mSAIEscapePool, SAIEscape, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAIEscape( SAIEscape* ai )
	{
		MG_POOL_DELETE(mSAIEscapePool, ai);
	}

	//--------------------------------------------------------------------------
	SAIFightTrigger* SAIObjectManager::createSAIFightTrigger( SCharacter* character )
	{
		SAIFightTrigger* ai = MG_POOL_NEW(mSAIFightTriggerPool, SAIFightTrigger, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAIFightTrigger(SAIFightTrigger* ai)
	{
		MG_POOL_DELETE(mSAIFightTriggerPool, ai);
	}

	//--------------------------------------------------------------------------
	SAIKeepDistance*	SAIObjectManager::createSAIKeepDistance( SCharacter* character )
	{
		SAIKeepDistance* ai = MG_POOL_NEW(mSAIKeepDistancePool, SAIKeepDistance, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAIKeepDistance(SAIKeepDistance* ai)
	{
		MG_POOL_DELETE(mSAIKeepDistancePool, ai);
	}

	//--------------------------------------------------------------------------
	SAIHateDetect* SAIObjectManager::createSAIHateDetect( SCharacter* character )
	{
		SAIHateDetect* ai = MG_POOL_NEW(mSAIHateDetectPool, SAIHateDetect, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAIHateDetect( SAIHateDetect* ai )
	{
		MG_POOL_DELETE(mSAIHateDetectPool, ai);
	}

	//--------------------------------------------------------------------------
	SAIPursue* SAIObjectManager::createSAIPursue( SCharacter* character )
	{
		SAIPursue* ai = MG_POOL_NEW(mSAIPursuePool, SAIPursue, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAIPursue(SAIPursue* ai)
	{
		MG_POOL_DELETE(mSAIPursuePool, ai);
	}

	//--------------------------------------------------------------------------
	SAISelectSkill* SAIObjectManager::createSAISelectSkill( SCharacter* character )
	{
		SAISelectSkill* ai = MG_POOL_NEW(mSAISelectSkillPool, SAISelectSkill, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAISelectSkill(SAISelectSkill* ai)
	{
		MG_POOL_DELETE(mSAISelectSkillPool, ai);
	}

	//--------------------------------------------------------------------------
	SAIReturn* SAIObjectManager::createSAIReturn( SCharacter* character )
	{
		SAIReturn* ai = MG_POOL_NEW(mSAIReturnPool, SAIReturn, (character));

		ai->setManagedLifeTime( false );
		ai->addListener( this );

		return ai;
	}

	//--------------------------------------------------------------------------
	void SAIObjectManager::destroySAIReturn(SAIReturn* ai)
	{
		MG_POOL_DELETE(mSAIReturnPool, ai);
	}

	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	void SAIObjectManager::onLinedStateLifeTimeOver(LinedStateObject* obj)
	{
		if ( obj->getName() == SAIGuard::STATE_NAME )
		{
			destroySAIGuard((SAIGuard*)obj);
		}else
			if ( obj->getName() == SAIRandomMove::STATE_NAME )
			{
				destroySAIRandomMove((SAIRandomMove*)obj);
			}else
				if ( obj->getName() == SAIAttack::STATE_NAME )
				{
					destroySAIAttack((SAIAttack*)obj);
				}else
					if ( obj->getName() == SAIFightTrigger::STATE_NAME )
					{
						destroySAIFightTrigger((SAIFightTrigger*)obj);
					}else
						if ( obj->getName() == SAIKeepDistance::STATE_NAME )
						{
							destroySAIKeepDistance((SAIKeepDistance*)obj);
						}else
							if ( obj->getName() == SAIPursue::STATE_NAME )
							{
								destroySAIPursue((SAIPursue*)obj);
							}else
								if ( obj->getName() == SAISelectSkill::STATE_NAME )
								{
									destroySAISelectSkill((SAISelectSkill*)obj);
								}			
	}

}