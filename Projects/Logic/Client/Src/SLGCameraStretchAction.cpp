/******************************************************************************/
#include "stdafx.h"
#include "ClientMain.h"
#include "ISceneNodeAction.h"
#include "IActionManager.h"
#include "SLGCameraStretchAction.h"
#include "SLGCameraOpCtrl.h"
/******************************************************************************/

namespace MG
{
    
    /******************************************************************************/
    //SLGCameraStretchAction
    /******************************************************************************/
    Str SLGCameraStretchAction::STATE_NAME = "SLGCameraStretchAction";

    SLGCameraStretchAction::SLGCameraStretchAction( SLGCameraOpCtrl* owner )
        :LinedStateObject(STATE_NAME)
        ,mCamera(NULL)
        ,mTime(0)
        ,mOwner(owner)
    {

    }

    //-----------------------------------------------------------------------
    SLGCameraStretchAction::~SLGCameraStretchAction()
    {
    }

    //-----------------------------------------------------------------------
    void SLGCameraStretchAction::update( Flt delta )
    {
        IScene* scene   = ClientMain::getInstance().getScene();
        if ( !scene )
            return;

        ITerrainManager* terrain    = scene->getTerrainManager();
        if ( !terrain )
            return;

        //////////////////////////////////////////////////////////////////////////////

        Vec3 camPos;
        mCamera->getPosition(camPos);

		Vec3 camDir;
		mCamera->getDirection(camDir);

        Vec3 lastCamPos = camPos;

        Vec3 focusPos	= mOwner->getFocusPos();

        //////////////////////////////////////////////////////////////////////////////

		//计算摄像机最终移动去的目的地坐标
        Vec3 desPos  = focusPos - mDestDir;

		//计算最终目的地和当前的摄像机位置的向量距离
        Vec3 moveDir = desPos - camPos;
        Flt	 moveDis = moveDir.length();

        if ( (mTime > 0) && (delta < mTime) )
        {
			// moveDis / mTime 计算出了整个当前移动需要的速度信息， 然后乘以delta
			// 获得这一帧的移动距离
            moveDis = (moveDis / mTime) * delta;
        }

        moveDir.normalise();
        camPos += moveDir * moveDis;

        //////////////////////////////////////////////////////////////////////////////

        mCamera->setPosition(camPos);

        //if ( mOwner->checkAndLimitCameraHeight() )
        //{
        //    mTime = 0;
        //    mIsHeightLimited = true;
        //    
        //    //camPos;
        //    //mCamera->getPosition(camPos);

        //    //camPos.x = lastCamPos.x;
        //    //camPos.z = lastCamPos.z;

        //    mCamera->setPosition(lastCamPos);

        //}else
        {
            mCamera->lookAt(focusPos);

            mTime -= delta;
        }

        //////////////////////////////////////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------
    Bool SLGCameraStretchAction::isFinished()
    {
        if ( !mCamera )
            return true;

        if ( mIsHeightLimited )
            return true;

        if ( mTime <= 0 )
            return true;

        return false;
    }

    //-----------------------------------------------------------------------
    void SLGCameraStretchAction::onEnter()
    {
        if ( !mCamera )
            return;

        Vec3 camDir;
        mCamera->getDirection( camDir );
        mDestDir = mDestLod.calculateDir( camDir );

        mIsHeightLimited = false;
    }

    //-----------------------------------------------------------------------
    void SLGCameraStretchAction::onLeave()
    {
        if ( !mIsHeightLimited )
        {
            if ( mTime <= 0 )
            {
                Vec3 camPos;
				mCamera->getSceneNode()->getPosition(camPos);

                Vec3 focusPos = mOwner->getFocusPos();

                camPos.y = focusPos.y + mDestLod.mHeight;
                mCamera->getSceneNode()->setPosition(camPos);

                mOwner->checkAndLimitCameraHeight();

                mCamera->lookAt(focusPos);
            }
        }
    }

    //-----------------------------------------------------------------------
    void SLGCameraStretchAction::setCamera( ICamera* camera )
    {
        mCamera = camera;
    }   

    //-----------------------------------------------------------------------
    void SLGCameraStretchAction::setStretchLod( SLGCameraStretchLod destlod, Flt Time )
    {
        mDestLod = destlod;
        mTime = Time;
    }

    //-----------------------------------------------------------------------
    SLGCameraStretchLod& SLGCameraStretchAction::getStretchLod()
    {
        return mDestLod;
    }


}

