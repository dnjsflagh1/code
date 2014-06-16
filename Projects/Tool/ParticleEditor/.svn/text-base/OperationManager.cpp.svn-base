/******************************************************************************/
#include "StdAfx.h"
#include "CoreManager.h"
#include "GlobalOptions.h"
#include "OperationManager.h"
#include "IEditorSystem.h"
#include "IEditorOperation.h"
#include "IActionManager.h"
#include "GameFileDefine.h"
/******************************************************************************/


namespace ParticleEditor {

    //-----------------------------------------------------------------------
    OperationManager::OperationManager()
        :mCameraSpeed(1000.0f)
        ,mViewportLock(true)
		,mIsMouseStateCheck(false)
		,mTimeMouseHold(0)
		,mOpInterval(0.05f)
    {
        mCameraHeightSet.push_back(20);
        mCameraHeightSet.push_back(40);
        mCameraHeightSet.push_back(60);
        mCameraHeightSet.push_back(80);

        mMinPitch = (Flt)(- 1.57 * 1.0 / 2.0);
        mMaxPitch = (Flt)(- 1.57 * 1.0 / 3.0);
    }
    //-----------------------------------------------------------------------
    OperationManager::~OperationManager()
    {

    }

    //-----------------------------------------------------------------------
    void OperationManager::update( Dbl delta )
    {
        IInput* input       = CoreManager::getInstance().getEngineMain()->input();
        if ( input == NULL )
            return;

        IScene* scene       = CoreManager::getInstance().getScene();
        if ( scene == NULL )
            return;

        ITerrainManager* terrain   = scene->getTerrainManager();
        if ( terrain == NULL )
            return;

        ICamera* camera = scene->getActiveCamera();


        updateFreeCameraOp(input,terrain,camera,delta);
    }

    //-----------------------------------------------------------------------
    void OperationManager::revertCamera()
    {
        IInput* input = CoreManager::getInstance().getEngineMain()->input();
        IScene* scene = CoreManager::getInstance().getScene();

        if ( scene )
        {
            ICamera* camera = scene->getActiveCamera();
            if ( camera )
            {
                camera->setOrientation(Qua(1,0,0,0));

                Vec3 pos;
                camera->getPosition(pos);
                pos.y = 80;
                camera->setPosition(pos);
                //camera->setDirection(Vec3(0,-1,0));
                //camera->lookAt(Vec3(0,0,0));
                camera->pitch( (Flt)(- 1.57 * 1.0 / 2.0) );
            }
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateFreeCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta )
    {   
        Flt d = (Flt)delta * mCameraSpeed;

        //通过滚轮改变摄像机离地面距离
        Int	wheelRel = 0;
        if ( input->isMouseHolded(MB_Left) == false &&
			!input->isCtrlOn() && !input->isAltOn() && !input->isShiftOn() )
            wheelRel = input->getMouseWheel();
        if(wheelRel != 0)
        {
            Flt scale = 0.05f;
            Flt final_wheel = (Flt)-wheelRel * scale;

            Vec3 camera_pos;
            camera->getPosition(camera_pos);

            if ( abs(camera_pos.y)  > 1000.0f )
                final_wheel = (Flt)-wheelRel*1.0f;
            else if ( abs(camera_pos.y)  > 100.0f )
                final_wheel = (Flt)-wheelRel*0.1f;
            else if ( abs(camera_pos.y)  > 0.0f )
                final_wheel = (Flt)-wheelRel*0.01f;

            camera->translate(Vec3(0, 0, final_wheel));
        }

		//控制角度
		if( input->isMouseHolded(MB_Middle) )
		{
			Vec2 rel = input->getMouseMoveDelta();
			camera->pitch( rel.y * (-3.0f) );
			camera->yaw( rel.x * (-3.0f) );
		}

        //按键控制位置

        {
            bool camera_translate = false;
            Vec3 vec_trans;
			Flt  scale = 0.05f;

			if ( input->isKeyHolded(KC_LSHIFT) )
			{
				scale *= 2.0f;
			}

            if ( input->isKeyHolded(KC_A) )
            {
                vec_trans = Vec3(-d,0,0);
                camera_translate = true;
            }
            else if ( input->isKeyHolded(KC_D) )
            {
                vec_trans = Vec3(d,0,0);
                camera_translate = true;
            }
            else if ( input->isKeyHolded(KC_W) )
            {
                vec_trans = Vec3(0,0,-d);
                camera_translate = true;
            }
            else if ( input->isKeyHolded(KC_S) )
            {
                vec_trans = Vec3(0,0,d);
                camera_translate = true;
            }
			else if ( input->isKeyHolded(KC_E) )
			{
				Vec3 camera_pos;
				camera->getPosition(camera_pos);
				camera_pos.y += scale * d;
				camera->setPosition(camera_pos);
			}
			else if ( input->isKeyHolded(KC_Q) )
			{
				Vec3 camera_pos;
				camera->getPosition(camera_pos);
				camera_pos.y -= scale * d;
				camera->setPosition(camera_pos);
			}

            if ( camera_translate )
            {
                Vec3 camera_pos;
                camera->getPosition(camera_pos);

                //scale *= camera_pos.y;

                vec_trans.x *= scale;
                vec_trans.y *= scale;
                vec_trans.z *= scale;

                camera->translate(vec_trans);
            }
        }
           
    }


  
}

