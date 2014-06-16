/******************************************************************************/
#include "stdafx.h"
#include "SActionObjectManager.h"
#include "SCharacterMoveToAction.h"
/******************************************************************************/
namespace MG
{

	//--------------------------------------------------------------------------
	SActionObjectManager::SActionObjectManager()
	{

	}

	//--------------------------------------------------------------------------

	SActionObjectManager::~SActionObjectManager()
	{

	}

	//--------------------------------------------------------------------------
	void SActionObjectManager::revert()
	{

	}

	//--------------------------------------------------------------------------
	SCharacterMoveToAction* SActionObjectManager::createSCharacterMoveToAction( SCharacter* character, Vec3 startMovePos, Vec3 moveToPos )
	{
		startMovePos.y = 0;
		moveToPos.y = 0;
		SCharacterMoveToAction* action = MG_POOL_NEW(mSCharacterMoveToActionPool, SCharacterMoveToAction, (character, startMovePos, moveToPos));

		action->setManagedLifeTime( false );
		action->addListener( this );

		return action;
	}

	//--------------------------------------------------------------------------
	void SActionObjectManager::destroySCharacterMoveToAction(SCharacterMoveToAction* action)
	{
		MG_POOL_DELETE(mSCharacterMoveToActionPool, action);
	}

	//--------------------------------------------------------------------------
	void SActionObjectManager::onLinedStateLifeTimeOver(LinedStateObject* obj)
	{
		if ( obj->getName() == STATE_NAME )
		{
			destroySCharacterMoveToAction((SCharacterMoveToAction*)obj);
		}
	}


}