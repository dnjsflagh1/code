/******************************************************************************/
#include "stdafx.h"
#include "CPointSkillEffect.h"
#include "CSceneManager.h"
#include "CLuaSkillSystem.h"
#include "CPlayer.h"
#include "SkillNetPacketProcesser.h"
#include "CBuildingEntity.h"
#include "SkillBaseInfo.h"
#include "ICollisionSystem.h"
#include "ClientMain.h"
#include "IActionManager.h"
#include "IEffectEntity.h"
/******************************************************************************/

namespace MG
{

    //--------------------------------------------------------------------------
    CPointSkillEffect::CPointSkillEffect( CSkillObject* object )
        : CSkillEffect( object )
		,mEffectComponent(NULL) 
		,mMapId(0)
		,mAffectNum(1) 
		,mCurrAffectNum(0)
		,mRadius(0) 
		,mAffectIntervalTime(0)
		,mAttackNum(0)
		,mCurrAttackNum(0)
		,mFlyEffectComponent(NULL)
		,mMoveSpeed(1)
		,mFlyEffectID(0)
		,mState(PSES_NULL)
		,mPauseThinkTime(0)
    {

    }

    //--------------------------------------------------------------------------
    CPointSkillEffect::~CPointSkillEffect()
    {
		end();
    }

	//--------------------------------------------------------------------------
	void CPointSkillEffect::setStartPos( Vec3 pos )
	{
		mStartPos = pos;
	}
	
	//--------------------------------------------------------------------------
	void CPointSkillEffect::setFlyEffectId( UInt flyEffectID )
	{
		mFlyEffectID = flyEffectID;
	}

    //--------------------------------------------------------------------------
    void CPointSkillEffect::start()
    {
        CSkillEffect::start();

		CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
		if(!characterSceneEntity || characterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}

		SkillInfo* skillInfo = mSkillObject->getSkillInfo();
		if(!skillInfo)
		{
			end();
			return;
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)(skillInfo->skillInfo);
		if(!initiativeSkillBasicInfo)
		{
			end();
			return;
		}


		mMapId = CSceneManager::getInstance().getRegionId();

		mState = PSES_CREATEEFFECT;
    }

    //--------------------------------------------------------------------------
    void CPointSkillEffect::end()
    {
		if(mFlyEffectID == 0 && mEffectComponent)
		{
			// CN_MODIFY
			CSceneManager::getInstance().getEngineScene()->destroyEffectComponent(mEffectComponent->getName().c_str());
			mEffectComponent = NULL;
		}

		 CSkillEffect::end();
    }

    //--------------------------------------------------------------------------
    void CPointSkillEffect::update( Flt delta )
    {
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		CSkillEffect::update(delta);

		CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
		if(!characterSceneEntity || characterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}

		switch(mState)
		{
		case PSES_CREATEEFFECT:
			createEffect();
			break;

		case PSES_MOVETO:
			effectMoveTo();
			break;

		case PSES_CHECKCOLLISION:
			checkCollision(characterSceneEntity);
			break;
		}

    }
	//-----------------------------------------------------------------------
	void  CPointSkillEffect::setPos( Vec3 pos )
    {
        mPos = pos;
    }
	//-----------------------------------------------------------------------
	void  CPointSkillEffect::setRadius( UInt radius )
	{
		mRadius = radius;
	}
	//-----------------------------------------------------------------------
	void  CPointSkillEffect::setAffectIntervalTime(Flt time)
	{
		mAffectIntervalTime = time;
	}
	//-----------------------------------------------------------------------
	void CPointSkillEffect::setAffectNum(UInt num)
	{
		mAffectNum = num;
	}
	//-----------------------------------------------------------------------
	void CPointSkillEffect::setAttackNum(UInt num)
	{
		mAttackNum = num;
	}
	//-----------------------------------------------------------------------
	void CPointSkillEffect::getCanAttackNum(ISceneObjectCollisionCallback* callback, CCharacterSceneEntity* ownerCharacterSceneEntity)
	{
		if(!ownerCharacterSceneEntity)
		{
			mCanAttackNum = 0;
		}

		ILogicBinder* logicBinder = NULL;
		ISceneObject* sceneObject = NULL;
		CCharacterSceneEntity* targetCharacterSceneEntity = NULL;

		for(UInt i = 0; i < callback->collisionList.size(); ++i)
		{
			sceneObject = callback->collisionList[i].second;
			if(!sceneObject)
			{
				continue;
			}

			logicBinder = sceneObject->getLogicBinder();

			if(!logicBinder || !logicBinder->manager)
			{
				continue;
			}

			targetCharacterSceneEntity = (CCharacterSceneEntity*)logicBinder->manager;

			if(targetCharacterSceneEntity == ownerCharacterSceneEntity || targetCharacterSceneEntity->getDynamicData()->force == ownerCharacterSceneEntity->getDynamicData()->force || targetCharacterSceneEntity->getDynamicData()->isDied)
			{
				continue;
			}

			mCanAttackNum++;
		}
	}

	//-----------------------------------------------------------------------
	void CPointSkillEffect::setMoveSpeed( Flt moveSpeed )
	{
		mMoveSpeed = moveSpeed;
	}

	//-----------------------------------------------------------------------
	void CPointSkillEffect::createEffect()
	{
		if(mFlyEffectID != 0)
		{
			// CN_MODIFY
			mFlyEffectComponent = CSceneManager::getInstance().getEngineScene()->createEffectComponent(mFlyEffectID, false);
			if(mFlyEffectComponent)
			{
				Vec3 dir = mPos - mStartPos;
				dir.y = 0;
				dir.normalise();
				mFlyEffectComponent->getSceneNode()->setPosition(mStartPos);
				mFlyEffectComponent->getSceneNode()->setDirection(dir);
				mFlyEffectComponent->getSceneNode()->stickTerrain();
			}
		}
		else if(mEffectFileId != 0)
		{
			// CN_MODIFY
			mEffectComponent = CSceneManager::getInstance().getEngineScene()->createEffectComponent(mEffectFileId, false);
			if(mEffectComponent)
			{
				mEffectComponent->getSceneNode()->setPosition(mPos);
				mEffectComponent->getSceneNode()->stickTerrain();
			}
		}

		if(mFlyEffectComponent)
		{
			ISceneNodeLineMoveToAction* lineMoveToAction = mFlyEffectComponent->getSceneNode()->getScene()->getActionManager()->createSceneNodeParabolaMoveToAction(mFlyEffectComponent->getSceneNode());
			lineMoveToAction->setMoveSpeed(mMoveSpeed);
			lineMoveToAction->setIgnoreHeight(false);
			lineMoveToAction->setStickTerrain(false);
			lineMoveToAction->setMoveToDestination(mPos);
			mFlyEffectComponent->getSceneNode()->getLinedStateManager()->push(lineMoveToAction);
		}


		mState = PSES_MOVETO;
	}

	//-----------------------------------------------------------------------
	void CPointSkillEffect::effectMoveTo()
	{
		if(mFlyEffectComponent)
		{
			if(!mFlyEffectComponent->getSceneNode()->getLinedStateManager()->getState("SceneNodeParabolaMoveToAction", false))
			{
				// CN_MODIFY 
				CSceneManager::getInstance().getEngineScene()->destroyEffectComponent(mFlyEffectComponent->getName().c_str());
				mFlyEffectComponent = NULL;

				if(mEffectFileId != 0)
				{
					// CN_MODIFY
					mEffectComponent = CSceneManager::getInstance().getEngineScene()->createEffectComponent(mEffectFileId, true);
					if(mEffectComponent)
					{
						mEffectComponent->getSceneNode()->setPosition(mPos);
						mEffectComponent->getSceneNode()->stickTerrain();
					}
				}

				mState = PSES_CHECKCOLLISION;
			}
		}
		else
		{
			mState = PSES_CHECKCOLLISION;
		}

		stopUpdate(mAffectIntervalTime);
	}

	//-----------------------------------------------------------------------
	void CPointSkillEffect::checkCollision( CCharacterSceneEntity* owner )
	{
		if(mCurrAffectNum >=  mAffectNum)
		{
			this->end();
		}
		else
		{
			ISceneObjectCollisionCallback callback;
			callback.isCheckQueryFlagsMask = true;
			callback.isCheckSingle = false;
			callback.queryFlagsMask = GQT_BUILDING | GQT_TROOP | GQT_SOLDIER | GQT_PLAYERCHARACTER | GQT_MONSTER;

			ClientMain::getInstance().getScene()->getCollisionSystem()->checkCircleCollision(mPos, mRadius, &callback);

			getCanAttackNum(&callback, owner);

			ILogicBinder* logicBinder = NULL;
			ISceneObject* sceneObject = NULL;
			CCharacterSceneEntity* targetCharacterSceneEntity = NULL;

			for(UInt i = 0; i < callback.collisionList.size(); ++i)
			{
				sceneObject = callback.collisionList[i].second;
				if(!sceneObject)
				{
					continue;
				}

				logicBinder = sceneObject->getLogicBinder();

				if(!logicBinder || !logicBinder->manager)
				{
					continue;
				}

				targetCharacterSceneEntity = (CCharacterSceneEntity*)logicBinder->manager;

				if(targetCharacterSceneEntity == owner || targetCharacterSceneEntity->getDynamicData()->force == owner->getDynamicData()->force || targetCharacterSceneEntity->getDynamicData()->isDied)
				{
					continue;
				}

				if(mCurrAttackNum < mAttackNum)
				{
					if(mAttackNum < mCanAttackNum)
					{	
						mCanAttackNum = mAttackNum;
					}

					CLuaSkillSystem::getInstance().execClientCollisionAffectScript(targetCharacterSceneEntity, mCanAttackNum, mSkillObject, this);

					if(targetCharacterSceneEntity->getType() == GOT_MONSTER && owner->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
					{
						SkillNetPacketProcesser::getInstance().sendSkillCharacterCollisionAffectCharacter(owner->getType(), owner, targetCharacterSceneEntity->getType(), targetCharacterSceneEntity, mCanAttackNum, mSkillObject->getSkillInfo()->skillId, mMapId, mSkillObject->getTargetPosition());
					}
					else if(targetCharacterSceneEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
					{
						SkillNetPacketProcesser::getInstance().sendSkillCharacterCollisionAffectCharacter(owner->getType(), owner, targetCharacterSceneEntity->getType(), targetCharacterSceneEntity, mCanAttackNum, mSkillObject->getSkillInfo()->skillId, mMapId);
					}
				}
			}

			mCurrAttackNum = 0;
			mCurrAffectNum++;

			stopUpdate(mAffectIntervalTime);
		}
	}

	//-----------------------------------------------------------------------
	void CPointSkillEffect::stopUpdate( Flt time )
	{
		mPauseThinkTime = time;
	}

	//-----------------------------------------------------------------------
	void CPointSkillEffect::resumeUpdate()
	{
		mPauseThinkTime = 0;
	}


}