/******************************************************************************/
#include "stdafx.h"
#include "SceneEntityAction.h"
#include "CSceneManager.h"
#include "CSceneEntity.h"
#include "ISceneNodeAction.h"
#include "IActionManager.h"
#include "CGameTimeSystem.h"
#include "IDynamicBlockObject.h"
#include "IBlockManager.h"
/******************************************************************************/

namespace MG
{

//#define WAITMOVETIME 300

    /******************************************************************************/
    //游戏对象直线移动行为
    /******************************************************************************/

    Str CCSEntityLineMoveAcion::STATE_NAME = "CCSEntityLineMoveAcion";

    //-----------------------------------------------------------------------
    CCSEntityLineMoveAcion::CCSEntityLineMoveAcion( CSceneEntity* entity, Vec3 startPos, Vec3 endPos, Flt startTime )
        :LinedStateObject(STATE_NAME)
        ,mEntity( entity )
        ,mStartPos(startPos)
        ,mEndPos(endPos)
        ,mDelayPushTime(startTime)
        ,mAnimName("move")
        ,mIsAutoAnimEnd(true)
        ,mMoveSpeed(1)
        ,mRealMoveSpeed(1)
        ,mYawSpeed(10)
		,mIsStartMove(false)
		,mPathRadius(0)
        ,mCMoveAcionState(MAS_NULL)
		,mBlockManager(NULL)
        ,mSceneNodeLineMoveToStartPosAction(NULL)
        ,mSceneNodeLineMoveToEndPosAction(NULL)
        ,mIsPrepareMoveEndPos(false)
        ,mIsAlreadyMoveEndPos(false)
		,mIsBlockCheck(true)
		,mMoveToPathFindType(ISceneNodeGridLineMoveToAction::PFT_DYNAMIC)
		,mWaitTime(0)
		,mIsWaitMove(false)
		,mWaitMoveTime(200)
    {

    }

    //-----------------------------------------------------------------------
    CCSEntityLineMoveAcion::~CCSEntityLineMoveAcion()
    {

    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::update( Flt delta )
    {
		if(MGTimeOp::getCurrTick() >= mWaitTime && mIsWaitMove)
		{
			mIsWaitMove = false;
			setIsWait(mIsWaitMove);
		}

        if ( mIsPrepareMoveEndPos )
        {
            moveToEndPos();
            mIsPrepareMoveEndPos = false;
        }
    }

    //---------------------------------------------------------
    Bool CCSEntityLineMoveAcion::isFinished()
    {
        // 检测2个引擎Action是否结束

        // 需要根据Action的对象指针和UsedCount判断
		if( !mEntity )
		{
			return true;
		}

        if( !mEntity->getEntity() )
        {
            return true;
        }

		ISceneNode* sceneNode = mEntity->getEntity()->getSceneNode();
		if( !sceneNode )
		{
			return true;
		}

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if ( mIsAlreadyMoveEndPos == true )
        {
            if( !mEntity->getEntity()->getSceneNode()->getLinedStateManager()->getState("SceneNodeLineMoveToAction", false) &&
                !mEntity->getEntity()->getSceneNode()->getLinedStateManager()->getState("SceneNodeGridLineMoveToAction", false) )
            {
                return true;
            }
        }

		//是否移动结束
		return false;
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::onEnter()
    {
        //calculateRealMoveSpeed();

		if(!mEntity)
		{
			return;
		}

        mIsPrepareMoveEndPos = false;
        mIsAlreadyMoveEndPos = false;
        mAnimPlaying = false;

		mPathRadius = mEntity->getEntity()->getModelObject()->getPatherRadius();

		ISceneNode* sceneNode = mEntity->getEntity()->getSceneNode();
		if(!sceneNode)
		{
			return;
		}
 
		mEntity->playAnimation(mAnimName.c_str(), true, true, false, false );
		
		mBlockManager = sceneNode->getScene()->getBlockManager();

		//calculateRealMoveSpeed();

        /////////////////////////////////////////////////////////////////////////////////////////////

        setMoveAcionState( MAS_MOVING );

        /////////////////////////////////////////////////////////////////////////////////////////////

        if ( isNeedMoveToStartPos() )
        {
            moveToStartPos();
        }else
        {
            moveToEndPos();
        }
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::onMoveAcionStateChanged( CMoveAcionState state )
    {
        if(state == MAS_MOVING)
        {
            mEntity->playAnimation(mAnimName.c_str(),false,true,false);
            mAnimPlaying = true;
        }
        else
        {
            mEntity->stopAnimation(mAnimName.c_str());
            mAnimPlaying = false;
        }
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::onLeave()
    {
        /*  动画
        @ 根据是否自动关闭动画开关控制动画的关闭
        */

        /*  停止灰尘特效
        */

		//停止播放动作
		if(!mEntity)
		{
			return;
		}

        if ( mSceneNodeLineMoveToStartPosAction ||  mSceneNodeLineMoveToEndPosAction )
        {
            if ( mSceneNodeLineMoveToStartPosAction )
                mSceneNodeLineMoveToStartPosAction->removeListener( this );
            if ( mSceneNodeLineMoveToEndPosAction )
                mSceneNodeLineMoveToEndPosAction->removeListener( this );
		    mEntity->getEntity()->getSceneNode()->getLinedStateManager()->removeState(mSceneNodeLineMoveToActionName, false);
        }

		mEntity->stopAnimation(mAnimName.c_str());

        setMoveAcionState( MAS_NULL );
    }

    //-----------------------------------------------------------------------
    Bool CCSEntityLineMoveAcion::isNeedMoveToStartPos()
    {
        if ( !mEntity )
            return false;

        if ( !mEntity->getEntity() )
            return false ;

        ISceneNode* sceneNode = mEntity->getEntity()->getSceneNode();
        if( !sceneNode )
        {
            return false ;
        }

        Vec3 currPos;
        sceneNode->getPosition(currPos);

        Vec3 ec = mEndPos - currPos;
        Vec3 es = mEndPos - mStartPos;

        ec.y = 0;
        es.y = 0;

        Flt currDis = ec.length();
        Flt dis     = es.length();

        if ( currDis > dis  )
            return true;

        return false;
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::moveToStartPos()
    {
        if ( !mEntity )
            return;

        if ( !mEntity->getEntity() )
            return;

        ISceneNode* sceneNode = mEntity->getEntity()->getSceneNode();
        if( !sceneNode )
        {
            return;
        }

		IDynamicBlockObject* dynamicBlockObject = mEntity->getEntity()->getDynamicBlockObject();

        mSceneNodeLineMoveToStartPosAction = sceneNode->getScene()->getActionManager()->createSceneNodeGridLineMoveToAction(sceneNode, dynamicBlockObject);

        mSceneNodeLineMoveToActionName = mSceneNodeLineMoveToStartPosAction->getName();
        mSceneNodeLineMoveToStartPosAction->addListener( this );
        mSceneNodeLineMoveToStartPosAction->setMoveSpeed(mMoveSpeed);
        mSceneNodeLineMoveToStartPosAction->setMoveToDestination(mStartPos);
        mSceneNodeLineMoveToStartPosAction->setBlockCheck( false );
		mSceneNodeLineMoveToStartPosAction->setMoveToPathFindType(mMoveToPathFindType);

		if (dynamicBlockObject != NULL)
		{
			Flt perturbRadiu = dynamicBlockObject->getObjectRadius()*2;
			mSceneNodeLineMoveToStartPosAction->setPerturbRadiu(perturbRadiu);
			
			//mSceneNodeLineMoveToStartPosAction->setPerturbEnable(true);
		}

		CCSEntityLineMoveAcion* entityLineMoveAcion = NULL;
		ISceneNodeGridLineMoveToAction* sceneNodeGridLineMoveToAction = NULL;
		for(UInt i = 0; i < mMoveAcionListenerList.size(); ++i)
		{
			entityLineMoveAcion = mMoveAcionListenerList[i];
			sceneNodeGridLineMoveToAction = entityLineMoveAcion->getCurrSceneNodeGridLineMoveToAction();
			if(!sceneNodeGridLineMoveToAction)
			{
				continue;
			}

			mSceneNodeLineMoveToStartPosAction->addListener(sceneNodeGridLineMoveToAction);
		}

        sceneNode->getLinedStateManager()->push(mSceneNodeLineMoveToStartPosAction, false);

        /////////////////////////////////////////////////////////////////////////////////////////////

        ISceneNodeYawToAction* yawToAction = sceneNode->getScene()->getActionManager()->createSceneNodeYawToAction(sceneNode);
        yawToAction->setYawSpeed(mYawSpeed);
        yawToAction->setYawToPosition(mStartPos);
        yawToAction->setIsImmediately(false);
        sceneNode->getLinedStateManager()->push(yawToAction, false);

        /////////////////////////////////////////////////////////////////////////////////////////////

        sceneNode->stickTerrain();
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::moveToEndPos()
    {
        mIsAlreadyMoveEndPos = true;

        if ( !mEntity )
            return;

        if ( !mEntity->getEntity() )
            return;

        ISceneNode* sceneNode = mEntity->getEntity()->getSceneNode();
        if( !sceneNode )
        {
            return;
        }

		IDynamicBlockObject* dynamicBlockObject = mEntity->getEntity()->getDynamicBlockObject();
	
        mSceneNodeLineMoveToEndPosAction = sceneNode->getScene()->getActionManager()->createSceneNodeGridLineMoveToAction(sceneNode, dynamicBlockObject);

        mSceneNodeLineMoveToActionName = mSceneNodeLineMoveToEndPosAction->getName();
        mSceneNodeLineMoveToEndPosAction->addListener( this );
        mSceneNodeLineMoveToEndPosAction->setMoveSpeed(mMoveSpeed);
        mSceneNodeLineMoveToEndPosAction->setMoveToDestination(mEndPos);
        mSceneNodeLineMoveToEndPosAction->setBlockCheck( mIsBlockCheck );
		mSceneNodeLineMoveToEndPosAction->setMoveToPathFindType(mMoveToPathFindType);

		if (dynamicBlockObject != NULL)
		{
			Flt perturbRadiu = dynamicBlockObject->getObjectRadius()*2;
			mSceneNodeLineMoveToEndPosAction->setPerturbRadiu(perturbRadiu);

			//mSceneNodeLineMoveToEndPosAction->setPerturbEnable(true);
		}

		CCSEntityLineMoveAcion* entityLineMoveAcion = NULL;
		ISceneNodeGridLineMoveToAction* sceneNodeGridLineMoveToAction = NULL;
		for(UInt i = 0; i < mMoveAcionListenerList.size(); ++i)
		{
			entityLineMoveAcion = mMoveAcionListenerList[i];
			sceneNodeGridLineMoveToAction = entityLineMoveAcion->getCurrSceneNodeGridLineMoveToAction();
			if(!sceneNodeGridLineMoveToAction)
			{
				continue;
			}

			mSceneNodeLineMoveToEndPosAction->addListener(sceneNodeGridLineMoveToAction);
		}

        sceneNode->getLinedStateManager()->push(mSceneNodeLineMoveToEndPosAction, false);

        /////////////////////////////////////////////////////////////////////////////////////////////

        ISceneNodeYawToAction* yawToAction = sceneNode->getScene()->getActionManager()->createSceneNodeYawToAction(sceneNode);
        yawToAction->setYawSpeed(mYawSpeed);

        //Vec3 currPos;
        //sceneNode->getPosition(currPos);

        yawToAction->setYawToPosition(mEndPos);
        yawToAction->setIsImmediately(false);
        sceneNode->getLinedStateManager()->push(yawToAction, false);

        /////////////////////////////////////////////////////////////////////////////////////////////

        sceneNode->stickTerrain();
    }

    //-----------------------------------------------------------------------
    CMoveAcionState CCSEntityLineMoveAcion::getMoveAcionState()
    {
        return mCMoveAcionState;
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::setMoveAcionState( CMoveAcionState state )
    {
        mCMoveAcionState = state;
        onMoveAcionStateChanged( mCMoveAcionState );
    }
    
    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::onLinedStateEnter(LinedStateObject* obj)
    {
        if ( mSceneNodeLineMoveToStartPosAction == obj )
        {
            setMoveAcionState( MAS_MOVING );
        }else
        if ( mSceneNodeLineMoveToEndPosAction == obj )
        {
            setMoveAcionState( MAS_MOVING );
        }else
        {
            DYNAMIC_ASSERT(false);
        }
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::onLinedStateLeave(LinedStateObject* obj)
    {
        if ( mSceneNodeLineMoveToStartPosAction == obj )
        {
            mSceneNodeLineMoveToStartPosAction = NULL;

            mIsPrepareMoveEndPos = true;
        }else
        if ( mSceneNodeLineMoveToEndPosAction == obj )
        {
            mSceneNodeLineMoveToEndPosAction = NULL;

            setMoveAcionState( MAS_NULL );
        }else
        {
            DYNAMIC_ASSERT(false);
        }
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::onLinedStateChanged(LinedStateObject* obj)
    {
        if ( mSceneNodeLineMoveToEndPosAction == obj )
        {
            CMoveAcionState state = MAS_MOVING;

            IDynamicBlockObject* selfBlockOBj   =  mEntity->getEntity()->createOrRetrieveDynamicBlockObject();
            if ( !selfBlockOBj )
                return;

			//UInt collideBlockIndex              =  selfBlockOBj->getCollideBlockIndex();
            IDynamicBlockObject* colBlockOBj    =  selfBlockOBj->getCollideBlockObject()/*mBlockManager->getDynamicBlockObjectFromGridBlock(collideBlockIndex)*/;

            if ( colBlockOBj )
            {
                state =  MAS_MOVESTOP;

                //UInt oppositeCollideBlockIndex              =  colBlockOBj->getCollideBlockIndex();
                IDynamicBlockObject* oppositeColBlockOBj    =  colBlockOBj->getCollideBlockObject();//mBlockManager->getDynamicBlockObjectFromGridBlock(oppositeCollideBlockIndex);

                if ( selfBlockOBj != oppositeColBlockOBj )
                {
                    ISceneObject* sceneObj = colBlockOBj->getSceneObject();
                    if ( sceneObj )
                    {
                        ILogicBinder* logicBinder = sceneObj->getLogicBinder();
                        if ( logicBinder )
                        {
                            CSceneEntity* entity = static_cast<CSceneEntity*>( logicBinder->manager );
                            if ( entity )
                            {
                                LinedStateObject* stateObj = entity->getActionStateManager().getState( getName(), true );
                                if ( stateObj )
                                {
                                    CCSEntityLineMoveAcion* moveAction = static_cast<CCSEntityLineMoveAcion*>(stateObj);
                                    if ( moveAction )
                                    {
                                        CMoveAcionState blockState = moveAction->getMoveAcionState();
                                        if ( ( blockState == MAS_MOVING ) || ( blockState == MAS_MOVEWAIT ) )
                                        {
                                            state =  MAS_MOVEWAIT;

											mWaitTime = MGTimeOp::getCurrTick() + mWaitMoveTime;
											mIsWaitMove = true;
											mWaitMoveTime += 100;

											setIsWait(mIsWaitMove);
                                        }
                                    }
                                }

                            }
                        }
                    }
                }
            }

            setMoveAcionState( state );

			selfBlockOBj->setCollideBlockObject(NULL);

            ////////////////////////////////////////////////////////////////////

            //if ( state != MAS_MOVING )
            //{
            //    if ( collideBlockIndex == 0 )
            //    {
            //        DYNAMIC_ASSERT( false );
            //    }
            //}

        }else
        if ( mSceneNodeLineMoveToStartPosAction == obj )
        {

        }else
        {
            DYNAMIC_ASSERT( false );
        }
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::setAnimation( Str animName, Bool isAutoAnimEnd )
    {
        mAnimName = animName;
        mIsAutoAnimEnd = isAutoAnimEnd;
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::setMoveSpeed(Flt speed)
    {
        mMoveSpeed = speed;
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::setYawSpeed(Flt speed)
    {
        // 暂时程序定制
        //mYawSpeed = speed;
    }

    //-----------------------------------------------------------------------
    void CCSEntityLineMoveAcion::calculateRealMoveSpeed()
    {
        if ( mMoveSpeed <= 0 )
        {
            mMoveSpeed = 1;
            return;
        }

        Vec3 currPos;
        mEntity->getEntity()->getSceneNode()->getPosition(currPos);
        Flt dis = (mStartPos - currPos).length() + (mEndPos - currPos).length();
        Flt tempTime = dis / mMoveSpeed;

        Flt currTime = CGameTimeSystem::getInstance().getCurrActualTime();
        Flt diffTime = currTime - mDelayPushTime;
        tempTime = tempTime + diffTime;

        if ( tempTime == 0 )
        {
            mMoveSpeed = dis;
        }
        else
        {
            mMoveSpeed = dis / tempTime;
        }
    }

	//-----------------------------------------------------------------------
	void CCSEntityLineMoveAcion::setBlockCheck( Bool isBlockCheck )
	{
		mIsBlockCheck = isBlockCheck;
	}

	//-----------------------------------------------------------------------
	void CCSEntityLineMoveAcion::setMoveToPathFindType( ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType )
	{
		mMoveToPathFindType = moveToPathFindType;
	}

	//-----------------------------------------------------------------------
	ISceneNodeGridLineMoveToAction* CCSEntityLineMoveAcion::getCurrSceneNodeGridLineMoveToAction()
	{
		if(mSceneNodeLineMoveToStartPosAction)
		{
			return mSceneNodeLineMoveToStartPosAction;
		}
		else
		{
			return mSceneNodeLineMoveToEndPosAction;
		}

		return NULL;
	}

	//-----------------------------------------------------------------------
	void CCSEntityLineMoveAcion::setIsWait( Bool isWait )
	{
		if ( !mEntity )
			return;

		if ( !mEntity->getEntity() )
			return;

		ISceneNode* sceneNode = mEntity->getEntity()->getSceneNode();
		if( !sceneNode )
		{
			return;
		}

		ISceneNodeGridLineMoveToAction* sceneNodeGridLineMoveToAction = (ISceneNodeGridLineMoveToAction*)sceneNode->getLinedStateManager()->getState("SceneNodeGridLineMoveToAction", false);
		if(sceneNodeGridLineMoveToAction)
		{
			sceneNodeGridLineMoveToAction->setIsWait(isWait);
		}
	}

	//-----------------------------------------------------------------------
	Vec3 CCSEntityLineMoveAcion::getDestination()
	{
		return mEndPos;
	}

	//-----------------------------------------------------------------------
	void CCSEntityLineMoveAcion::addEntityLineMoveAcionListener( CCSEntityLineMoveAcion* moveAcion )
	{
		mMoveAcionListenerList.push_back(moveAcion);
	}

    /******************************************************************************/
    //请求交互行为
    /******************************************************************************/

    Str CCSEntityRequestInteractAcion::STATE_NAME = "CCSEntityRequestInteractAcion";

    //-----------------------------------------------------------------------

    CCSEntityRequestInteractAcion::CCSEntityRequestInteractAcion( CSceneEntity* requestEntity, CSceneEntity* desEntity )
        :LinedStateObject(STATE_NAME)
        ,mRequestEntity(requestEntity)
        ,mDesEntity(desEntity)
    {

    }

    //-----------------------------------------------------------------------
    CCSEntityRequestInteractAcion::~CCSEntityRequestInteractAcion()
    {

    }

    //-----------------------------------------------------------------------
    void CCSEntityRequestInteractAcion::update( Flt delta )
    {

    }

    //-----------------------------------------------------------------------
    Bool CCSEntityRequestInteractAcion::isFinished()
    {

        return false;
    }

    //-----------------------------------------------------------------------
    void CCSEntityRequestInteractAcion::onEnter()
    {



    }

    //-----------------------------------------------------------------------
    void CCSEntityRequestInteractAcion::onLeave()
    {

    }

    //-----------------------------------------------------------------------
    Vec3 CCSEntityRequestInteractAcion::getSuitableInteractPosition()
    {

        return Vec3(0,0,0);
    }

}