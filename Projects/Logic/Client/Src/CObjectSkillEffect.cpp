#include "stdafx.h"
#include "CSceneManager.h"
#include "CLuaSkillSystem.h"
#include "ICollisionSystem.h"
#include "SkillNetPacketProcesser.h"
#include "ClientMain.h"
#include "CObjectSkillEffect.h"
#include "CPlayer.h"
#include "CBuildingEntity.h"
#include "ISceneNodeAction.h"
#include "IActionManager.h"
#include "CTroopEffectEntityGroupManager.h"
#include "SkillBaseInfo.h"
#include "IEffectEntity.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	CObjectSkillEffect::CObjectSkillEffect( CSkillObject* object )
		:CSkillEffect( object )
		,mEffectComponent( NULL )
		,mIsSendCollisionPacket(false)
		,mDis(0)
		,mTargetId(0)
		,mTargetType(GOT_UNKNOWN)
		,mMoveSpeed(1)
		,mFlyEntity(NULL)
		,mPauseThinkTime(0)
		,mState(OSES_CREATEEFFECT)
	{
		mIsCheckCollsion = true;
	}

	//--------------------------------------------------------------------------
	CObjectSkillEffect::~CObjectSkillEffect()
	{
		end();
	}

	//--------------------------------------------------------------------------
	void CObjectSkillEffect::start()
	{
		CSkillEffect::start();

		Vec3 targetPos;

		CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getTargetObjectIndex());
		if(!characterSceneEntity || characterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}

		CCharacterSceneEntity* targetCharacterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
		if(!targetCharacterSceneEntity || targetCharacterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}

		targetPos = targetCharacterSceneEntity->getPos();

		if(targetCharacterSceneEntity->getType() == GOT_MONSTER && characterSceneEntity->getDynamicData()->belongPlayerID ==  CPlayer::getInstance().getAccountID())
		{
			mIsSendCollisionPacket = true;
		}
		else if(targetCharacterSceneEntity->getDynamicData()->belongPlayerID == CPlayer::getInstance().getAccountID())
		{
			mIsSendCollisionPacket = true;
		}
	}

	//--------------------------------------------------------------------------
	void CObjectSkillEffect::end()
	{
		CSkillEffect::end();

		if ( mEffectComponent )
		{
			// CN_MODIFY
			CSceneManager::getInstance().getEngineScene()->destroyEffectComponent( mEffectComponent->getName().c_str() );
			mEffectComponent = NULL;
		}

		if( mFlyEntity )
		{
			CTroopEffectEntityGroupManager::getInstance().destroyEffectComponent(mEffectFileId, mFlyEntity);
			mFlyEntity = NULL;
		}

	}

	//--------------------------------------------------------------------------
	void CObjectSkillEffect::update( Flt delta )
	{
		if(mPauseThinkTime > 0)
		{
			mPauseThinkTime -= delta;
			return;
		}

		CCharacterSceneEntity* targetCharacterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mTargetType, mTargetId, mTargetIndex);
		if(!targetCharacterSceneEntity || targetCharacterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}
	
		CCharacterSceneEntity* characterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getTargetObjectIndex());
		if(!characterSceneEntity || characterSceneEntity->getDynamicData()->isDied)
		{
			end();
			return;
		}

		CSkillEffect::update( delta );

		switch(mState)
		{
			case OSES_CREATEEFFECT:
				createEffect(characterSceneEntity, targetCharacterSceneEntity);
				break;

			case OSES_MOVETO:
				effectMoveTo(characterSceneEntity, targetCharacterSceneEntity);
				break;

			case OSES_COLLISION:
				effectCollision(characterSceneEntity, targetCharacterSceneEntity);
				break;
		}
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::setStartPos( Vec3 pos )
	{
		mPos = pos;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::setDistance( Flt dis )
	{
		mDis = dis;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::setTargetIndex( UInt index )
	{
		mTargetIndex = index;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::setTargetID( IdType id )
	{
		mTargetId = id;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::setTargetType( GAMEOBJ_TYPE type )
	{
		mTargetType = type;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::setMoveSpeed( Flt speed )
	{
		mMoveSpeed = speed;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::moveToPos( ISceneNode* sceneNode, Vec3 pos )
	{
		ISceneNodeLineMoveToAction* lineMoveToAction = sceneNode->getScene()->getActionManager()->createSceneNodeLineMoveToAction(sceneNode);
		lineMoveToAction->setMoveSpeed(mMoveSpeed);
		lineMoveToAction->setIgnoreHeight(false);
		lineMoveToAction->setStickTerrain(false);
		lineMoveToAction->setMoveToDestination(pos);
		sceneNode->getLinedStateManager()->push(lineMoveToAction);
	}

	//-----------------------------------------------------------------------
	IEntity* CObjectSkillEffect::createFlyEntity( UInt effectId, Vec3 pos, Vec3 dir, Bool isVisible )
	{
		IEntity* entity = CTroopEffectEntityGroupManager::getInstance().getEffectComponent(effectId);
		if(!entity)
		{
			return NULL;
		}

		entity->getSceneNode()->setPosition( mPos );
		entity->getSceneNode()->setDirection( mDir );
		entity->getSceneNode()->setVisible(isVisible);

		return entity;
	}

	//-----------------------------------------------------------------------
	IEffectComponent* CObjectSkillEffect::createEffectComponent( UInt effectId, Vec3 pos, Vec3 dir, Bool isAutoDestroy )
	{
		// CN_MODIFY
		IEffectComponent* effectEntity = CSceneManager::getInstance().getEngineScene()->createEffectComponent(mEffectFileId, isAutoDestroy);
		if(!effectEntity)
		{
			return NULL;
		}

		effectEntity->getSceneNode()->setPosition( mPos );
		effectEntity->getSceneNode()->setDirection( mDir );

		return effectEntity;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::stopUpdate( Flt time )
	{
		mPauseThinkTime = time;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::resumeUpdate()
	{
		mPauseThinkTime = 0;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::createEffect( CCharacterSceneEntity* owner, CCharacterSceneEntity* target )
	{
		Vec3 targetPos = target->getPos(false);
		targetPos.y += (target->getEntity()->getModelObject()->getHeight() / 2);
		Vec3 dir = targetPos - mPos;
		mPos.y += (owner->getEntity()->getModelObject()->getHeight() / 2);
		mDir = MGMath::normaliseVector(dir);

		if(owner->getType() == GOT_SOLDIER)
		{
			mFlyEntity = createFlyEntity(mEffectFileId, mPos, mDir, true);
			if ( !mFlyEntity )
			{
				end();
				return;
			}

			moveToPos(mFlyEntity->getSceneNode(), targetPos);

			Flt continueTime = dir.length() / mMoveSpeed;
			stopUpdate(continueTime);
		}
		else
		{
			mEffectComponent = createEffectComponent(mEffectFileId, mPos, mDir, false);
			if ( !mEffectComponent )
			{
				end();
				return;
			}

			moveToPos(mEffectComponent->getSceneNode(), targetPos);
			//stopUpdate(1);
		}

		mState = OSES_MOVETO;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::effectMoveTo( CCharacterSceneEntity* owner, CCharacterSceneEntity* target )
	{
		if(mEffectComponent)
		{
			Vec3 targetPos = target->getPos(false);
			targetPos.y += (target->getEntity()->getModelObject()->getHeight() / 2);

			Vec3 currEffectPos;
			mEffectComponent->getSceneNode()->getPosition(currEffectPos);
			Vec3 dir =  targetPos - currEffectPos;
			mDir = MGMath::normaliseVector(dir);

			dir.y = 0;
			Flt dis = dir.length();

			mEffectComponent->getSceneNode()->setDirection(mDir);

			moveToPos(mEffectComponent->getSceneNode(), targetPos);

			if( dis > 0.5 )
			{
				//stopUpdate(1);
				return;
			}	
		}
	
		mState = OSES_COLLISION;
	}

	//-----------------------------------------------------------------------
	void CObjectSkillEffect::effectCollision( CCharacterSceneEntity* owner, CCharacterSceneEntity* target )
	{
		if(!mIsCheckCollsion)
		{
			end();
			return;
		}

		CLuaSkillSystem::getInstance().execClientCollisionAffectScript( target, 1, mSkillObject, this );

		if(mIsSendCollisionPacket)
		{
			SkillNetPacketProcesser::getInstance().sendSkillCharacterCollisionAffectCharacter(mSkillObject->getOwnerType(), owner, mTargetType, target, 1, mSkillObject->getSkillInfo()->skillId, CPlayer::getInstance().getActiveClan()->getFocusRegionID());
		}

		end();
		mState = OSES_NULL;
	}

}


