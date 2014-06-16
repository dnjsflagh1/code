/******************************************************************************/
#include "stdafx.h"
#include "Camera.h"
#include "EngineMain.h"
#include "EditorCameraOpCtrl.h"
#include "Scene.h"
#include "InputManager.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    EditorCameraOpCtrl::EditorCameraOpCtrl()
        :mCamera(NULL)
		,mCameraSpeed(1000)
    {

    }
    //-----------------------------------------------------------------------
    EditorCameraOpCtrl::~EditorCameraOpCtrl()
    {
        
    }
    //-----------------------------------------------------------------------
    void EditorCameraOpCtrl::update( Flt delta )
    {
		if ( mCamera )
		{
			if ( InputManager::getSingletonPtr()->isKeyHolded(KC_MINUS) )
			{
				mCameraSpeed -= 100;
				if ( mCameraSpeed < 0 )
					mCameraSpeed = 100;
			}else
			if ( InputManager::getSingletonPtr()->isKeyHolded(KC_EQUALS) )
			{
				mCameraSpeed += 100;
				if ( mCameraSpeed >2000 )
					mCameraSpeed = 2000;
			}
			Flt d = delta * mCameraSpeed;

			if ( InputManager::getSingletonPtr()->isMouseHolded(MB_Right) )
			{
				if ( InputManager::getSingletonPtr()->isKeyHolded(KC_A) )
				{
					mCamera->translate(Vec3(-d,0,0));
				}else
				if ( InputManager::getSingletonPtr()->isKeyHolded(KC_D) )
				{
					mCamera->translate(Vec3(d,0,0));
				}else
				if ( InputManager::getSingletonPtr()->isKeyHolded(KC_W) )
				{
					mCamera->translate(Vec3(0,0,-d));
				}else
				if ( InputManager::getSingletonPtr()->isKeyHolded(KC_S) )
				{
					mCamera->translate(Vec3(0,0,d));
				}
				
				Vec2 rel =  InputManager::getSingletonPtr()->getMouseMoveDelta();
				rel.x *= -2.0f;
				rel.y *= -2.0f;
				mCamera->yaw( rel.x );
				mCamera->pitch( rel.y );
			}
		}
    }
    //-----------------------------------------------------------------------
    void EditorCameraOpCtrl::setCamera(Camera* cam)
    {
        mCamera = cam;
    }

}

