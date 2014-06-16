/******************************************************************************/
#include "stdafx.h"
#include "SceneNodeAction.h"
#include "SceneNodeSpecialMoveAction.h"
#include "MGEngineUtility.h"
#include "ISceneNode.h"
#include "IScene.h"
#include "ITerrain.h"
#include "MGSceneNode.h"
/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //SceneNodeParabolaMoveToAction
    /******************************************************************************/
    Str SceneNodeParabolaMoveToAction::STATE_NAME = "SceneNodeParabolaMoveToAction";
    SceneNodeParabolaMoveToAction::SceneNodeParabolaMoveToAction( ISceneNode* object ): SceneNodeLineMoveToAction(object, STATE_NAME), mSpeedY(0), mGravity(0.5f)
    {
    }

    //-----------------------------------------------------------------------
    SceneNodeParabolaMoveToAction::~SceneNodeParabolaMoveToAction()
    {

    }

    //-----------------------------------------------------------------------
    void SceneNodeParabolaMoveToAction::onEnter()
    {
        SceneNodeLineMoveToAction::onEnter();
        Vector3 dir = mMoveDestination - mMoveStartPosition;
        Vector2 v(dir.x, dir.z);
        Flt length = v.length();
        v.normalise();
        /*
        0 = v1 - g * t1;	v1为发射初速度
        s1 = v1 * t1 - 1/2 * g * t1 * t1;	上升的高度
        s2 = 1/2 * g * t2 * t2 = s1 + C;	下落的高度，C为武器和地面的高度
        t = t1 + t2;	t为从发射到落地的总时间
        */
        Flt a = v.length();
        float t =  length / mMoveSpeed;
        float dis = abs(mMoveStartPosition.y - mMoveDestination.y);
        float t1 = (0.5f * mGravity * t * t + dis) / (mGravity * t);
        float v1 = mGravity * t1;
        mSpeedY = v1;
    }

    //-----------------------------------------------------------------------
    void SceneNodeParabolaMoveToAction::onLeave()
    {
        SceneNodeLineMoveToAction::onLeave();
    }

    //-----------------------------------------------------------------------
    void SceneNodeParabolaMoveToAction::update( Flt delta )
    {
        //SceneNodeMoveToAction::update( delta );

        Flt timeTick = delta * mMoveSpeed;

        Vector3 position = MGEngineUtility::getPosition( mSceneNode );
        Vector3 currentFrameMoveDis = mMoveVelocity * timeTick;
        currentFrameMoveDis.y =  mSpeedY * timeTick + 0.5f * (-mGravity) * timeTick * timeTick;
        position += currentFrameMoveDis;

        Vec3 moveToPos;
        moveToPos = MGEngineUtility::toVec3( position );
        mSceneNode->setPosition(moveToPos);

        Vector3 currDir3 = position - mMoveStartPosition;
		/*mSceneNode->setDirection(Vec3(currDir3.x, currDir3.y, currDir3.z));*/

        Vector2 currDir2(currDir3.x, currDir3.z);
        mCurrMoveLength = currDir2.length();

        if(mCurrMoveLength >= mMoveLength)
        {
			mSceneNode->setPosition( MGEngineUtility::toVec3(mMoveDestination));
			mSceneNode->stickTerrain();
        }

        mSpeedY = mSpeedY + (-mGravity) * timeTick;
    }

    //-----------------------------------------------------------------------
    Bool SceneNodeParabolaMoveToAction::isFinished()
    {
        return SceneNodeLineMoveToAction::isFinished();
    }
    //-----------------------------------------------------------------------



    /******************************************************************************/
    //SceneNodeParabolaMoveToAction
    /******************************************************************************/
    Str SceneNodeCurveMoveToAction::STATE_NAME = "SceneNodeCurveMoveToAction";
    SceneNodeCurveMoveToAction::SceneNodeCurveMoveToAction( ISceneNode* object ): SceneNodeLineMoveToAction(object), mSpeedZ(0), mGravity(1.f)
    {

    }

    //-----------------------------------------------------------------------
    SceneNodeCurveMoveToAction::~SceneNodeCurveMoveToAction()
    {

    }

    //-----------------------------------------------------------------------
    void SceneNodeCurveMoveToAction::onEnter()
    {
        SceneNodeLineMoveToAction::onEnter();
        Vector3 dir = mMoveDestination - mMoveStartPosition;
        Vector2 v(dir.x, dir.z);
        UInt length = v.length();
        v.normalise();
        /*
        0 = v1 - g * t1;	v1为发射初速度
        s1 = v1 * t1 - 1/2 * g * t1 * t1;	上升的高度
        s2 = 1/2 * g * t2 * t2 = s1 + C;	下落的高度，C为武器和地面的高度
        t = t1 + t2;	t为从发射到落地的总时间
        */
        Flt a = v.length();
        float t =  length / mMoveSpeed;
        float dis = mMoveStartPosition.z - mMoveDestination.z;
        float t1 = (0.5f * mGravity * t * t + dis) / (mGravity * t);
        float v1 =  mGravity * t1;
        mSpeedZ = v1;

        mMoveDis = mMoveStartPosition;
        mMoveDir = MGEngineUtility::getNormaliseVerticalVector(mMoveStartPosition);
    }

    //-----------------------------------------------------------------------
    void SceneNodeCurveMoveToAction::onLeave()
    {
        SceneNodeLineMoveToAction::onLeave();
    }

    //-----------------------------------------------------------------------
    void SceneNodeCurveMoveToAction::update( Flt delta )
    {
        //SceneNodeMoveToAction::update( delta );

        Flt timeTick = mMoveSpeed * delta;

        Vector3 position = MGEngineUtility::getPosition( mSceneNode );
        Vector3 currentFrameMoveDis = mMoveVelocity * timeTick ;

        //currentFrameMoveDis.z =  mSpeedZ * timeTick + 0.5f * (-mGravity) * timeTick * timeTick;
        Flt s = mSpeedZ * timeTick + 0.5f * (-mGravity) * timeTick * timeTick;

        //position += currentFrameMoveDis;
        position = (position + mMoveDir * s + currentFrameMoveDis);

        Vec3 moveToPos;
        moveToPos = MGEngineUtility::toVec3( position );
        mSceneNode->setPosition(moveToPos);

        Vector3 currDir3 = position - mMoveStartPosition;
        Vector2 currDir2(currDir3.x, currDir3.z);
        mCurrMoveLength = currDir2.length();

        mSpeedZ = mSpeedZ + (-mGravity) * timeTick;
    }

    //-----------------------------------------------------------------------
    Bool SceneNodeCurveMoveToAction::isFinished()
    {
        return SceneNodeLineMoveToAction::isFinished();
    }


}