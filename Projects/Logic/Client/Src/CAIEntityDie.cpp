/******************************************************************************/
#include "stdafx.h"
#include "CAIEntityDie.h"
#include "CCharacterSceneEntity.h"
#include "IDynamicBlockObject.h"
#include "ICollisionObject.h"
#include "CharacterList.h"
#include "CBuildingEntity.h"
#include "CTroopSoldierEntity.h"
#include "CTroopEntity.h"
#include "CFightMainManager.h"
#include "CharacterVisionEventList.h"
#include "CharacterVisionEvent.h"
#include "GameSoundManager.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------

	Str CAIEntityDie::STATE_NAME = "CAIEntityDie";

	//--------------------------------------------------------------------------
	CAIEntityDie::CAIEntityDie( CCharacterSceneEntity* characterSceneEntity )
		:LinedStateObject(STATE_NAME)
		,mCharacterSceneEntity(characterSceneEntity)
		,mPauseThinkTime(0)
		,mState(DAS_NULL)
		,mIsFinished(false)
		,mCharacterVisionEventInfo(NULL)
	{
	}

	//--------------------------------------------------------------------------
	CAIEntityDie::~CAIEntityDie()
	{

	}

	//-----------------------------------------------------------------------
	void CAIEntityDie::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}
		
		switch(mState)
		{
		case DAS_STARTPLAYDIEANIM:
			startPlayAnim();
			break;

		case DAS_ENDPLAYDIEANIM:
			endPlayAnim();
			break;
		}
	}

	//-----------------------------------------------------------------------
	Bool CAIEntityDie::isFinished()
	{
		return mIsFinished;
	}

	//-----------------------------------------------------------------------
	void CAIEntityDie::onEnter()
	{
		if(mCharacterSceneEntity->getType() == GOT_BUILDING && ((CBuildingEntity*)mCharacterSceneEntity)->isWall())
		{
			IEntity* entity = mCharacterSceneEntity->getEntity();
			if(!entity)
			{
				destroy();
				return;
			}

			setEntityBlockEnable(entity, false);

			setEntityCollisionEnable(entity, false);

			U32 meshId = mCharacterSceneEntity->getCharacterTempInfo()->getBuildArtMashId2();
			if(meshId == 0)
			{
				destroy();
				return;	
			}

			changeMesh(entity, meshId);

			setEntityCollisionEnable(entity, true);
			
			destroy();
			return;
		}

		if(mCharacterSceneEntity->getType() == GOT_MONSTER)
		{
			mCharacterSceneEntity->getEntity()->setQueryFlags(GQT_UNKNOWN);
		}

		mCharacterSceneEntity->stopAllAnimation();
		mCharacterSceneEntity->getActionStateManager().setIsPush(false);
		mCharacterSceneEntity->getAIStateManager().setIsPush(false);

		U32 characterVisionEventListId = mCharacterSceneEntity->getCharacterTempInfo()->getCharacterVisionEventListId();
		const CharacterVisionEventListInfo* characterVisionEventListInfo = CharacterVisionEventList::getInstance().getCharacterVisionEventListInfo(characterVisionEventListId);
		if(!characterVisionEventListInfo)
		{
			destroy();
			return;
		}

		mCharacterVisionEventInfo = CharacterVisionEvent::getInstance().getCharacterVisionEventInfo(characterVisionEventListInfo->diedId);
		if(!mCharacterVisionEventInfo)
		{
			destroy();
			return;
		}

		mCharacterSceneEntity->addEffect(mCharacterVisionEventInfo->effectResId);
		GameSoundManager::getInstance().play(mCharacterVisionEventInfo->audioResId);

		mState = DAS_STARTPLAYDIEANIM;
	}

	//-----------------------------------------------------------------------
	void CAIEntityDie::onLeave()
	{
		if(mCharacterSceneEntity->getType() != GOT_BUILDING || (!((CBuildingEntity*)mCharacterSceneEntity)->isWall()))
		{
			if(mCharacterSceneEntity->getType() != GOT_PLAYERCHARACTER)
			{
				mCharacterSceneEntity->getDynamicData()->isDestroy = true;
			}
		}

		//dellFightInfo();
	}

	//-----------------------------------------------------------------------
	void CAIEntityDie::stopThink( Flt time )
	{
		mPauseThinkTime = time;
	}

	//-----------------------------------------------------------------------
	void CAIEntityDie::resumeThink()
	{
		mPauseThinkTime = 0;
	}

	//------------------------------------------------------------------------
	void CAIEntityDie::setEntityBlockEnable( IEntity* entity, Bool isEnable )
	{
		IDynamicBlockObject* dynamicBlockObject = entity->createOrRetrieveDynamicBlockObject();
		if(dynamicBlockObject)
		{
			dynamicBlockObject->setEnable(isEnable);
		}
	}

	//------------------------------------------------------------------------
	void CAIEntityDie::setEntityCollisionEnable( IEntity* entity, Bool isEnable )
	{
		ICollisionObject* collisionObject = entity->createOrRetrieveCollisionObject();
		if(collisionObject)
		{
			collisionObject->setEnable(isEnable);
		}
	}

	//------------------------------------------------------------------------
	void CAIEntityDie::changeMesh( IEntity* entity, UInt meshId )
	{
		entity = mCharacterSceneEntity->reloadEntity(meshId);
		if(!entity)
		{
			destroy();
			return;	
		}
	}

	//------------------------------------------------------------------------
	void CAIEntityDie::startPlayAnim()
	{
		Str actionName;
		MGStrOp::toString(mCharacterVisionEventInfo->actionName.c_str(), actionName);

		mCharacterSceneEntity->playAnimation(actionName, false, false, true);
		Flt animTime = mCharacterSceneEntity->getAnimationLength(actionName) + 0.5;

		stopThink(animTime);

		mState = DAS_ENDPLAYDIEANIM;
	}

	//------------------------------------------------------------------------
	void CAIEntityDie::endPlayAnim()
	{
		mIsFinished = true;
	}

	//------------------------------------------------------------------------
	//void CAIEntityDie::dellFightInfo()
	//{
	//	if(mCharacterSceneEntity->getType() == GOT_SOLDIER)
	//	{
	//		CTroopObject* troopObject = ((CTroopSoldierEntity*)mCharacterSceneEntity)->getTroopEntity();
	//		if(!troopObject || troopObject->getSoldierEntitysNum() != 0)
	//		{
	//			return;
	//		}

	//		CFightMainManager::getInstance().delAllFightInfo(troopObject->getType(), troopObject->getID());
	//	}
	//	else
	//	{
	//		CFightMainManager::getInstance().delAllFightInfo(mCharacterSceneEntity->getType(), mCharacterSceneEntity->getID());
	//	}
	//}

}