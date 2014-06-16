/******************************************************************************/
#include "stdafx.h"
#include "CSceneEntity.h"
#include "HeadDes.h"
#include "HeadDesManage.h"
#include "CActionManager.h"
#include "CharacterSceneEntityAction.h"
#include "ClientMain.h"
#include "CSceneManager.h"
/******************************************************************************/
namespace MG
{
    CSceneEntity::CSceneEntity(IEntity* entity, GAMEOBJ_TYPE type, GAMEOBJ_QUERY_TYPE queryType, SceneObjectData* dynamicData)
        :CSceneObject(type,queryType,dynamicData)
        ,mEntity(entity)
        ,mHeadDes(NULL)
    {
       
    }

    //---------------------------------------------------------------------------------
    CSceneEntity::~CSceneEntity()
    {
    }

    //---------------------------------------------------------------------------------------
    void CSceneEntity::initialize()
    {
        //////////////////////////////////////////////////////////////////////

        UInt type		= getType();
		UInt queryType	= getQueryType();

        if ( mEntity )
        {
            ILogicBinder* logicBinder = mEntity->getLogicBinder();
            logicBinder->manager = this;
            logicBinder->type = type;

            mEntity->setQueryFlags( queryType );
            mEntity->getSceneNode()->stickTerrain();

			if ( isBattleState() )
			{
				//playAnimation("guard", false, true);
				setIdleAnimation("guard", true);
			}
			else
			{
				//playAnimation("stand", false, true);
				setIdleAnimation("stand", true);
			}

            if ( !mHeadDes ) 
                mHeadDes = HeadDesManage::getInstance().createHeadDes( this );
            if ( mHeadDes )
            {
                mHeadDes->setHeight( mEntity->getModelObject()->getHeight() );
                mHeadDes->init();
            }
        }

        //////////////////////////////////////////////////////////////////////
    }

    //---------------------------------------------------------------------------------------
    void CSceneEntity::unInitialize()
	{       
		getActionStateManager().clear();
		getAIStateManager().clear();

        if ( mEntity )
        {
            ClientMain::getInstance().getScene()->destroyEntity(mEntity->getName().c_str()); 
            mEntity = NULL;
        }

        if ( mHeadDes )
        {
            HeadDesManage::getInstance().destroyHeadDes( mHeadDes );
            mHeadDes = NULL;
        }
    }
    
    //---------------------------------------------------------------------------------
    void CSceneEntity::update( Flt delta )
    {
        if ( mHeadDes )
            mHeadDes->update();
        CSceneObject::update( delta );
    }
   
    //---------------------------------------------------------------------------------
    Vec3 CSceneEntity::getEntityBonePos( Str boneName )
    {
        return mEntity->getModelObject()->getBoneWorldPosition( boneName.c_str() );
    }

	//---------------------------------------------------------------------------------
	Bool CSceneEntity::getWorldPos( Vec3& worldPos )
	{
		if ( !mEntity )
			return false;
		
		mEntity->getSceneNode()->getPosition( worldPos );

		return true;
	}

	//---------------------------------------------------------------------------------
	Bool CSceneEntity::isInScreen()
	{
		if ( !mEntity )
			return false;

		if ( !mEntity->isRendering() )
			return false;

		return true;
	}

	//---------------------------------------------------------------------------------
	Bool CSceneEntity::getScreenPos( Vec2& screenPos, Vec3 offset )
	{
		if ( !isInScreen() )
			return false;
		
		Vec3 worldPos;
		if ( getWorldPos( worldPos ) == false )
			return false;

		worldPos += offset;

		IScene* pScene = CSceneManager::getInstance().getEngineScene();
		ICamera* pCamera = pScene->getActiveCamera();
		pCamera->worldPointToScreenPoint(worldPos, screenPos);

		return true;
	}

    //---------------------------------------------------------------------------------
    void CSceneEntity::stopAllMainAction()
    {
        stopMoveToAction();
        stopRequestInteractAction();
    }

    //---------------------------------------------------------------------------------------
    void CSceneEntity::doMoveToAction( Vec3 destination, Flt startTime, Bool isBlockCheck, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType )
    {
        Vec3 currPos;
        mEntity->getSceneNode()->getPosition( currPos );

        doMoveToAction(currPos,destination,startTime,isBlockCheck,moveToPathFindType);
    }

    //---------------------------------------------------------------------------------------
    void CSceneEntity::doMoveToAction(Vec3 startPos, Vec3 destination, Flt startTime, Bool isBlockCheck, ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType)
    {
       // stopMoveToAction();

        CCSEntityLineMoveAcion* action = CActionManager::getInstance().createCCSEntityLineMoveAcion( this, startPos, destination, startTime );

        action->setMoveSpeed( getDynamicData()->moveSpeed );
        action->setYawSpeed( getDynamicData()->yawSpeed );
		action->setBlockCheck( isBlockCheck );
		action->setMoveToPathFindType( moveToPathFindType );

		if ( isBattleState() )
			action->setAnimation("march");
		else
			action->setAnimation("move");

        getActionStateManager().push(action/*, false*/);
    }

    //---------------------------------------------------------------------------------------
    void CSceneEntity::stopMoveToAction()
    {
        getActionStateManager().removeState( CCSEntityLineMoveAcion::STATE_NAME, false );
    }

	//---------------------------------------------------------------------------------------
	void CSceneEntity::setIsWaitMoveToAction( Bool isWait )
	{
		CCSEntityLineMoveAcion* entityLineMoveAcion = (CCSEntityLineMoveAcion*)getActionStateManager().getState( CCSEntityLineMoveAcion::STATE_NAME, false );
		if(entityLineMoveAcion)
		{
			entityLineMoveAcion->setIsWait(isWait);
		}
	}

    //---------------------------------------------------------------------------------------
    CCSEntityLineMoveAcion* CSceneEntity::getActiveMoveToAction()
    {
        LinedStateObject* obj = getActionStateManager().getState( CCSEntityLineMoveAcion::STATE_NAME, false );
        if ( obj )
        {
            return static_cast<CCSEntityLineMoveAcion*>(obj);
        }
        return NULL;
    }

  
    //---------------------------------------------------------------------------------------
    void CSceneEntity::doPlayParticleEffectAction(Str effectName, Vec3 relativePos, Str bindBoneName)
    {

    }

    //---------------------------------------------------------------------------------------
    void CSceneEntity::stopPlayParticleEffectAction(Str effectName)
    {

    }

   
    //---------------------------------------------------------------------------------------
    void CSceneEntity::doRequestInteractAction(CCharacterSceneEntity* obj)
    {

    }

    //---------------------------------------------------------------------------------------
    void CSceneEntity::stopRequestInteractAction()
    {

    }

	//---------------------------------------------------------------------------------------
	void CSceneEntity::setIdleAnimation( Str animName, Bool isIdle, Bool isPlay )
	{
		//获取完整名称
		//-----------------------------------------------------------------------------------
		Str weaponActionGroup;
		Str rideActionGroup;

		getActionGroup( weaponActionGroup, rideActionGroup );

		animName = weaponActionGroup + rideActionGroup + animName;

		//-----------------------------------------------------------------------------------

		//获取动画
		if ( mEntity )
		{
			IAnimationController* animationController = mEntity->getAnimationController();
			if(!animationController)
			{
				return;
			}

			animationController->setIsIdle(isIdle, animName.c_str());
			Bool isIdlePlaying = animationController->isIdlePlaying();
			if(!isPlay && !isIdlePlaying)
			{	
				return;
			}

			mEntity->getAnimationController()->play(animName.c_str());
		}
	}
 
    //---------------------------------------------------------------------------------------
    void CSceneEntity::playAnimation(Str animName, Bool randomTimePlaye, Bool isLoop, Bool isLastFrameStop, Bool isReset)
    {
		if ( animName.empty() )
			return;

		//获取完整名称
		//-----------------------------------------------------------------------------------
		Str weaponActionGroup;
		Str rideActionGroup;

		getActionGroup( weaponActionGroup, rideActionGroup );

		animName = weaponActionGroup + rideActionGroup + animName;

		//-----------------------------------------------------------------------------------

		//获取动画
        if(!mEntity->getAnimationController()->isPlaying(animName.c_str()))
        {
            mEntity->getAnimationController()->play(animName.c_str(), isReset);
            mEntity->getAnimationController()->setLoop(animName.c_str(), isLoop);
            mEntity->getAnimationController()->setLastFrameStopEnable(animName.c_str(), isLastFrameStop);

            // random
			if(randomTimePlaye)
			{
				Flt time = mEntity->getAnimationController()->getLength(animName.c_str());
				if(time > 0)
				{
					time = time * 1000;
					time = (UInt)MGRandom::getInstance().rand_ab_One(0, (UInt)time);
					mEntity->getAnimationController()->setTimePosition(animName.c_str(), time / 1000);
				}
			}


            mEntity->getAnimationController()->setLoop(animName.c_str(), isLoop);
        }

    }

	//---------------------------------------------------------------------------------------
	//void CSceneEntity::playAnimation(PLAY_ANIMATION_TYPE type, Bool isLoop, Bool isLastFrameStop)
	//{
	//	Str animatonName = getAnimationName(type, getType());

	//	playAnimation(animatonName, "0", isLoop, isLastFrameStop);
	//}

	void CSceneEntity::setFreezeLastFrame( Str animName, Bool isFreeze )
	{
		//获取完整名称
		//-----------------------------------------------------------------------------------

		Str weaponActionGroup;
		Str rideActionGroup;

		getActionGroup( weaponActionGroup, rideActionGroup );

		animName = weaponActionGroup + rideActionGroup + animName;

		//-----------------------------------------------------------------------------------
		
		if ( mEntity->getAnimationController() )
		{
			mEntity->getAnimationController()->setLastFrameStopEnable(animName.c_str(), isFreeze);
		}

	}
    //---------------------------------------------------------------------------------------
    void CSceneEntity::stopAnimation(Str animName)
    {
		//获取完整名称
		//-----------------------------------------------------------------------------------
		Str weaponActionGroup;
		Str rideActionGroup;

		getActionGroup( weaponActionGroup, rideActionGroup );

		animName = weaponActionGroup + rideActionGroup + animName;

		//-----------------------------------------------------------------------------------

		if ( mEntity->getAnimationController() )
		{
			mEntity->getAnimationController()->stop(animName.c_str());
		}
		else
		{
			DYNAMIC_ASSERT(false);
		}
    }

    //---------------------------------------------------------------------------------------
    void CSceneEntity::stopAllAnimation()
    {
		if (  mEntity->getAnimationController() )
		{
			mEntity->getAnimationController()->stopAll();
		}else
		{
			DYNAMIC_ASSERT(false);
		}
    }

    //---------------------------------------------------------------------------------------
    Bool CSceneEntity::isPlayAnimation(Str animName)
    {
		//获取完整名称
		//-----------------------------------------------------------------------------------
		Str weaponActionGroup;
		Str rideActionGroup;

		getActionGroup( weaponActionGroup, rideActionGroup );

		animName = weaponActionGroup + rideActionGroup + animName;

		//-----------------------------------------------------------------------------------

		if (  mEntity->getAnimationController() )
		{
			return mEntity->getAnimationController()->isPlaying(animName.c_str());
		}else
		{
			DYNAMIC_ASSERT(false);
		}
		return false;
    }

	//---------------------------------------------------------------------------------------

	Flt CSceneEntity::getAnimationLength(Str animName)
	{
		//获取完整名称
		//-----------------------------------------------------------------------------------
		Str weaponActionGroup;
		Str rideActionGroup;

		getActionGroup( weaponActionGroup, rideActionGroup );

		animName = weaponActionGroup + rideActionGroup + animName;

		//-----------------------------------------------------------------------------------

		if (  mEntity->getAnimationController() )
		{
			return mEntity->getAnimationController()->getLength(animName.c_str());
		}

		return 0;
	}

	//---------------------------------------------------------------------------------------
	IEntity* CSceneEntity::reloadEntity(U32 modelID)
	{
		IScene* scene = ClientMain::getInstance().getScene();
		if ( !scene )
			return NULL;

		if ( mEntity )
		{
			Vec3 pos;
			mEntity->getSceneNode()->getPosition(pos);
			Vec3 dir;
			mEntity->getSceneNode()->getDirection(dir);

			Str name = mEntity->getName();
			mEntity = NULL;

			scene->destroyEntity(name.c_str());

			if ( !name.empty() )
			{
				mEntity = scene->createEntity(name.c_str(), modelID);
				mEntity->getSceneNode()->setPosition(pos);
				mEntity->getSceneNode()->setDirection(dir);
				mEntity->getSceneNode()->stickTerrain();
			}
		}

		return mEntity;
	}

	//---------------------------------------------------------------------------------------
	void CSceneEntity::getActionGroup( Str& weaponAction, Str& rideAction )
	{
		weaponAction = "none_";
		rideAction = "none_";
	}

	//---------------------------------------------------------------------------------------
	void CSceneEntity::setActionGroup( U32 actionGroup, Bool isRide )
	{
		return;
	}

	//---------------------------------------------------------------------------------------
	void CSceneEntity::setHeadDesVisible( bool visible )
	{
		if ( mHeadDes )
			mHeadDes->setVisible( visible );
	}
}