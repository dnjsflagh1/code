/******************************************************************************/
#include "stdafx.h"
#include "CGoUpAndDownSkillEffect.h"
#include "CSceneManager.h"
#include "CLuaSkillSystem.h"
#include "CCharacterSceneEntity.h"
#include "CPlayer.h"
#include "SkillInfoList.h"
#include "SkillBaseInfo.h"
#include "ICollisionObject.h"
#include "IDynamicBlockObject.h"
#include "IEffectEntity.h"
/******************************************************************************/

namespace MG
{

	//--------------------------------------------------------------------------
	CGoUpAndDownSkillEffect::CGoUpAndDownSkillEffect( CSkillObject* object )
		:CSkillEffect( object )
		, mEffectComponent(NULL)
		//, mCurrTime(0)
		,mIsGoUp(true)
		,mCurrInterValTime(0)
	{

	}

	//--------------------------------------------------------------------------
	CGoUpAndDownSkillEffect::~CGoUpAndDownSkillEffect()
	{
		//end();
	}

	//--------------------------------------------------------------------------
	void CGoUpAndDownSkillEffect::start()
	{
		CSkillEffect::start();

		CCharacterSceneEntity* ownerCharacterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
		if(!ownerCharacterSceneEntity)
		{
			end();
			return;
		}

		if(ownerCharacterSceneEntity->getDynamicData()->belongPlayerID != CPlayer::getInstance().getAccountID())
		{
			end();
			return;
		}

		ownerCharacterSceneEntity->setDir(mDir);
		const SkillInfo* skillInfo = SkillInfoList::getInstance().getSkillInfo(mSkillObject->getSkillInfo()->skillId);
		if(!skillInfo)
		{
			end();
			return;
		}

		InitiativeSkillBasicInfo* initiativeSkillBasicInfo = (InitiativeSkillBasicInfo*)skillInfo->skillInfo;
		if(!initiativeSkillBasicInfo)
		{
			end();
			return;
		}
		
		// CN_MODIFY
		mEffectComponent = CSceneManager::getInstance().getEngineScene()->createEffectComponent(initiativeSkillBasicInfo->skillExpression[0].artEffectId);
		//if(!mEffectComponent)
		//{
		//	end();
		//	return;
		//}

		Str actionName;
		if(ownerCharacterSceneEntity->getIsCanMove())
		{
			MGStrOp::toString(initiativeSkillBasicInfo->skillExpression[0].action.c_str(), actionName);
			ownerCharacterSceneEntity->setIsCanMove(false);
			mIsGoUp = true;
		}
		else
		{
			MGStrOp::toString(initiativeSkillBasicInfo->skillExpression[1].action.c_str(), actionName);
			mIsGoUp = false;
		}

		if(mEffectComponent)
		{
			mEffectComponent->getSceneNode()->setPosition(mTargetPos);
		}
		
		mPlayAnimationTime = ownerCharacterSceneEntity->getEntity()->getAnimationController()->getLength(actionName.c_str()) / 1000;
		ownerCharacterSceneEntity->playAnimation(actionName.c_str());
		ownerCharacterSceneEntity->setFreezeLastFrame(actionName, true);
	}

	//--------------------------------------------------------------------------
	void CGoUpAndDownSkillEffect::end()
	{
		IDynamicBlockObject* dynamicBlockObject = NULL;
		ICollisionObject* collisionObject = NULL;

		if(mEffectComponent)
		{
			// CN_MODIFY
			CSceneManager::getInstance().getEngineScene()->destroyEffectComponent(mEffectComponent->getName().c_str());
			mEffectComponent = NULL;
		}

		CCharacterSceneEntity* ownerCharacterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
		if(!ownerCharacterSceneEntity)
		{
			return;
		}


        Bool blcokEnable = ownerCharacterSceneEntity->getEntity()->createOrRetrieveDynamicBlockObject()->getEnable();
		collisionObject = ownerCharacterSceneEntity->getEntity()->createOrRetrieveCollisionObject();
		dynamicBlockObject = ownerCharacterSceneEntity->getEntity()->createOrRetrieveDynamicBlockObject();

		if(!mIsGoUp)
		{
			ownerCharacterSceneEntity->setIsCanMove(true);
			if(collisionObject)
			{
				collisionObject->setEnable(false);
			}

			if(dynamicBlockObject)
			{
				dynamicBlockObject->setShowBlock(true);
				dynamicBlockObject->setEnable(false);
				dynamicBlockObject->setStructureMode(false);
                dynamicBlockObject->setStaticBlockEnable(true);
				dynamicBlockObject->setEnable(blcokEnable);
			}
		}
		else
		{
			if(collisionObject)
			{
				collisionObject->setEnable(true);
			}

			if(dynamicBlockObject)
			{
				dynamicBlockObject->setShowBlock(true);
				dynamicBlockObject->setEnable(false);
				dynamicBlockObject->setStructureMode(true);
                dynamicBlockObject->setStaticBlockEnable(true);
				dynamicBlockObject->setEnable(blcokEnable);
			}
		}

		CSkillEffect::end();
	}

	//--------------------------------------------------------------------------
	void CGoUpAndDownSkillEffect::update( Flt delta )
	{
		mCurrInterValTime += delta;
		if( mCurrInterValTime >= mPlayAnimationTime)
		{
			CCharacterSceneEntity* ownerCCharacterSceneEntity = CSceneManager::getInstance().getCharacterSceneEntity(mSkillObject->getOwnerType(), mSkillObject->getOwnerID(), mSkillObject->getOwnerIndex());
			if(ownerCCharacterSceneEntity)
			{
				end();
				return;
			}	

			mCurrInterValTime = 0;
		}

	}

	//-----------------------------------------------------------------------
	void CGoUpAndDownSkillEffect::setTargetPos( Vec3 pos )
	{
		mTargetPos = pos;
	}

	//-----------------------------------------------------------------------
	void CGoUpAndDownSkillEffect::setDir( Vec3 dir )
	{
		mDir = dir;
	}

}