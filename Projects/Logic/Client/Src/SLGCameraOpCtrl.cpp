/******************************************************************************/
#include "stdafx.h"
#include "IScene.h"
#include "IInput.h"
#include "SLGCameraOpCtrl.h"
#include "ClientMain.h"
#include "ISceneNodeAction.h"
#include "CSceneManager.h"
#include "IActionManager.h"
#include "ICollisionSystem.h"
#include "CPlayer.h"
#include "CPlayerCharacterEntity.h"
#include "SLGCameraStretchAction.h"
/******************************************************************************/

namespace MG
{

    //-----------------------------------------------------------------------
    SLGCameraOpCtrl::SLGCameraOpCtrl()
        :mCamera(NULL),  
		mIsTrackMode(true), 
		mCameraSpeed(2000), 
		mAutoMoveSize(10), 
		mViewportLock(true),
		mSyncFocus2DPosDirDirty(false),
		mSLGCameraStretchAction(NULL)
    {
		mAutoMoveSize = 2;

		mCamMaxBoard = Vec3( 1600.0f, 120.0f, 100.0f);
		mCamMinBoard = Vec3( 0, -120.0f, -1600.0f);

		mCamGameRollSpeed = 10.0f;
		mCamGameMoveSpeed = 100.0f;

        mSLGCameraStretchAction = MG_NEW SLGCameraStretchAction( this );
        mSLGCameraStretchAction->setManagedLifeTime( false );

        clearCameraStretchLods();

        addCameraStretchLod( SLGCameraStretchLod(20, 40, 0.3, 0.3) );
        addCameraStretchLod( SLGCameraStretchLod(40, 50, 0.3, 0.3) );
        addCameraStretchLod( SLGCameraStretchLod(60, 60, 0.3, 0.3) );
        addCameraStretchLod( SLGCameraStretchLod(80, 70, 0.3, 0.3) );

		mCamMinPitch = 30.0f / 180.0f * 3.14f;
		mCamMaxPitch = 80.0f / 180.0f * 3.14f;
		mCamDefaultPitch = 60.0f / 180.0f * 3.14f;
        mCamMinHeight = 20;

		mCamDefaultPos = ( mCamMaxBoard + mCamMinBoard ) * 0.5f;

        mCamDefaultHeight = 50;
    }

    //-----------------------------------------------------------------------
    SLGCameraOpCtrl::~SLGCameraOpCtrl()
    {
        MG_SAFE_DELETE(mSLGCameraStretchAction);
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::update( Flt delta )
    {
		if ( mCamera )
		{
            IEngineMain* engineMain = ClientMain::getInstance().getEngine();
            if ( engineMain == NULL )
                return;

            IInput* input           = engineMain->input();
            if ( input == NULL )
                return;

            IScene* scene           = ClientMain::getInstance().getScene();
            if ( scene == NULL )
                return;

            ITerrainManager* terrain       = scene->getTerrainManager();
            if ( terrain == NULL )
                return;


			//�л����Ʒ�ʽ
#ifdef _DEBUG
			if ( input->isKeyPressed(KC_F10) )
			{
				switchViewportLock();
			}
#endif
			if ( input->isKeyPressed(KC_F1) )
			{
				CPlayer* myPlayer = &(CPlayer::getInstance());
				{
                    IdType id = 0;
                    if ( CPlayer::getInstance().getActiveClan() )
					    id = CPlayer::getInstance().getActiveClan()->getMainGenrealID();
					focusPos( id );
				}
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////

			if ( mViewportLock && !mIsTrackMode && mSyncFocus2DPosDirDirty )
			{
				// �ⲿǿ�Ƹ���λ��
				focusPos( mSyncFocus2DPos );
				focusDir( mSyncFocus2DDir );
				mSyncFocus2DPosDirDirty = false;
			}

			if ( mViewportLock )
			{
				if ( !mIsTrackMode )
				{
					updateGameSLGCameraOp(input,terrain,mCamera,delta);
				}
				else
				{
					updateGameTrackCameraOp(input,terrain,mCamera,delta);
					//updateGameTrackCameraCollision(input, terrain, mCamera, delta);
				}

			}else
			{
				updateFreeCameraOp(input,terrain,mCamera,delta);
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////
         
		}
    }
    
    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::setCamera(ICamera* cam)
    {
        mCamera = cam;
        mSLGCameraStretchAction->setCamera( mCamera );
        revertCamera();
    }
    
    //-----------------------------------------------------------------------
	void SLGCameraOpCtrl::setAutoMoveSize(UInt size)
	{
		mAutoMoveSize = size;
	}

    //-----------------------------------------------------------------------
    Vec3 SLGCameraOpCtrl::getFocusPos()
    {
        return mFocusPos;
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::setFocusPos(Vec3 pos)
    {
        mFocusPos = pos;
    }

    //-----------------------------------------------------------------------
	void SLGCameraOpCtrl::syncFocusPosDirFromServer(Vec2 world2DPos, Vec2 world2DDir)
	{
		mSyncFocus2DPos = world2DPos;
		mSyncFocus2DDir = world2DDir;
		mSyncFocus2DPosDirDirty = true;
	}
	//-----------------------------------------------------------------------
    void SLGCameraOpCtrl::focusPos(Vec2 world2DPos)
    {
		Vec3 FocusPos;

		FocusPos.x = world2DPos.x;
		FocusPos.z = world2DPos.y;
		FocusPos.y = 0.0f;

		ITerrainManager* terrainMgr = ClientMain::getInstance().getScene()->getTerrainManager();
		if  ( terrainMgr )
		{
			terrainMgr->getStickHeight( world2DPos, FocusPos.y );
		}

		setFocusPos( FocusPos );
		focusPos(FocusPos);
    }

    //-----------------------------------------------------------------------
	void SLGCameraOpCtrl::focusPos(IdType id)
	{
		CPlayerCharacterEntity* playerEntity = CSceneManager::getInstance().getPlayerCharacterEntity( id );
		if ( playerEntity )
		{
			Vec3 act_pos;

			if ( playerEntity->getEntity() && playerEntity->getEntity()->getSceneNode() )
			{
				playerEntity->getEntity()->getSceneNode()->getPosition(act_pos);
				focusPos(act_pos);
			}
		}
		else
		{
			revertCamera();
		}
	}

	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::focusPos(Vec3 pos)
	{
		IInput* input = ClientMain::getInstance().getEngine()->input();
		IScene* scene = ClientMain::getInstance().getScene();

		if ( scene )
		{
			ICamera* camera = scene->getActiveCamera();
			if ( camera )
			{
				//���þ۽�λ��
                setFocusPos( pos );

				//��ȡ�۽���ͷλ��
				camera->focusPosition(pos);
			}
		}
	}

	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::focusDir(Vec2 dir)
	{
		IScene* scene = ClientMain::getInstance().getScene();

		if ( scene )
		{
			ICamera* camera = scene->getActiveCamera();

			if ( camera )
			{
				Vec3 camPos;
				camera->getSceneNode()->getPosition(camPos);

				// ��ȡԭ������������λ�õ�������xz���ϵľ���
				Flt dist2D = (Vec2(mFocusPos.x,mFocusPos.z) - Vec2(camPos.x, camPos.z)).length();
			
				// ��ȡ��ǰ����������λ�õ�����
				Vec3 newlookDir2D = Vec3(dir.x,0.0f,dir.y);
				newlookDir2D.normalise();
				newlookDir2D *= dist2D;

				// ��ȡԭ��������ͽ�����yzƽ���ϵľ���
				Vec3 lookDirAxisY = Vec3(0.0f,-1.0f,0.0f) * fabs(mFocusPos.y - camPos.y);
				// ��ȡԭ��������ͽ�����yzƽ���ϵ�����
				Vec3 newLookDir = lookDirAxisY + newlookDir2D;

				Vec3 newCamPos = mFocusPos - newLookDir;
				Vec3 newCamDir = mFocusPos - newCamPos;
				newCamDir.normalise();

				camera->getSceneNode()->setPosition(newCamPos);
				camera->getSceneNode()->setDirection(newCamDir);
				
				focusPos(mFocusPos);
			}
		}
	}

	//-----------------------------------------------------------------------
    void SLGCameraOpCtrl::revertCamera()
    {
		IInput* input = ClientMain::getInstance().getEngine()->input();
		IScene* scene = ClientMain::getInstance().getScene();

		if ( scene )
		{
			ICamera* camera = scene->getActiveCamera();
			if ( camera )
			{
                Vec3 pos;
                pos = mCamDefaultPos;
                pos.y = mCamDefaultHeight;

                camera->setPosition(pos);
                camera->setOrientation(Qua(1,0,0,0));
                camera->pitch(mCamDefaultPitch);
			}
		}
    }

    //-----------------------------------------------------------------------
    Flt SLGCameraOpCtrl::getHeightByFocusPos()
    {
        if ( !mCamera )
            return 20;

        Vec3 camPos;
        mCamera->getSceneNode()->getPosition(camPos);
        return camPos.y - getFocusPos().y;
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::updateFocusPos()
    {
        if ( !mCamera )
            return;

        IScene* scene   = ClientMain::getInstance().getScene();
        if ( scene == NULL )
            return;

        if ( !mIsTrackMode )
        {
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// ��ѯ�ر�λ��
            
            Vec3 camPos;
            mCamera->getSceneNode()->getPosition(camPos);
            Vec3 camDir;
            mCamera->getSceneNode()->getDirection(camDir);

            //////////////////////////////////////////////////////////////////////////////

            Vec3 currFocusPos = getFocusPos();
            scene->getCollisionSystem()->getRayIntersection(camPos,camDir,currFocusPos);
            setFocusPos( currFocusPos );
        }
        else
        {
            ////////////////////////////////////////////////////////////////////////////////////////////////////////

            /// �������ǵ�λ��

            if ( CPlayer::getInstance().getActiveClan() )
            {
                IdType charID = CPlayer::getInstance().getActiveClan()->getMainGenreal()->getID();

				CPlayerCharacterEntity* playerEntity = 
					dynamic_cast<CPlayerCharacterEntity*>(CSceneManager::getInstance().getSceneEntity(charID, GOT_PLAYERCHARACTER));

				if ( playerEntity )
				{
					focusPos(playerEntity->getPos(false));
				}
            }

			////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
    }

    //-----------------------------------------------------------------------
    Bool SLGCameraOpCtrl::checkAndLimitCameraHeight()
    {
        if ( mCamera )
        {
            Vec3 pos;
            mCamera->getPosition( pos );


            IScene* scene   = ClientMain::getInstance().getScene();
            if ( scene == NULL )
                return false;

            ITerrainManager* terrain    = scene->getTerrainManager();
            if ( terrain == NULL )
                return false;

            Flt height;
            Vec3 worldPos = pos;
            if ( scene->getCollisionSystem()->getStickHeight( worldPos, height ) )
            {
                if ( (pos.y - height) <= mCamMinHeight )
                {
                    pos.y = height + mCamMinHeight;
                    mCamera->setPosition( pos );
                    return true;
                }
            }
        }
        return false;
    }

	//-----------------------------------------------------------------------
	Vec3 SLGCameraOpCtrl::getValidFocusDelta(Vec3 pos, Qua orientation, Vec3 delta, bool isLocal )
	{
		Vec3 world_trans = delta;

		if ( isLocal )
			world_trans = orientation * delta;

		Vec3 valid_trans = world_trans;
		Vec3 newPos = pos + valid_trans;
		Vec3 oldPos = pos;

		bool insect_positive_x = false;
		bool insect_positive_y = false;
		bool insect_positive_z = false;
		bool insect_negative_x = false;
		bool insect_negative_y = false;
		bool insect_negative_z = false;

		//�ж�xƽ���-xƽ��
		if ( newPos.x > mCamMaxBoard.x )
		{
			newPos.x = mCamMaxBoard.x;

			if ( world_trans.x > 0.0f )
				insect_positive_x = true;
		}
		else if ( newPos.x < mCamMinBoard.x )
		{
			newPos.x = mCamMinBoard.x;

			if ( world_trans.x < 0.0f )
				insect_negative_x = true;
		}

		if ( insect_positive_x ||
			insect_negative_x )
		{
			if ( world_trans.x == 0.0f )
				valid_trans.x = 0.0f;
			else 
			{
				valid_trans.x = ( newPos.x - oldPos.x );
			}
		}

		//�ж�yƽ���-yƽ��
		/*if ( newPos.y > mCamMaxBoard.y )
		{
			newPos.y = mCamMaxBoard.y;

			if ( world_trans.y > 0.0f )
				insect_positive_y = true;
		}
		else if ( newPos.y < mCamMinBoard.y )
		{
			newPos.y = mCamMinBoard.y;

			if ( world_trans.y < 0.0f )
				insect_negative_y = true;
		}*/

		if ( insect_positive_y ||
			insect_negative_y )
		{
			if ( world_trans.y == 0.0f )
				valid_trans.y = 0.0f;
			else
			{
				valid_trans.y = ( newPos.y - oldPos.y );
			}
		}

		//�ж�zƽ���-zƽ��
		if ( newPos.z > mCamMaxBoard.z )
		{
			newPos.z = mCamMaxBoard.z;

			if ( world_trans.z > 0.0f )
				insect_positive_z = true;
		}
		else if ( newPos.z < mCamMinBoard.z )
		{
			newPos.z = mCamMinBoard.z;

			if ( world_trans.z < 0.0f )
				insect_negative_z = true;
		}

		if ( insect_positive_z ||
			insect_negative_z )
		{
			if ( world_trans.z == 0.0f )
				valid_trans.z = 0.0f;
			else
			{
				valid_trans.z = ( newPos.z - oldPos.z );
			}
		}

		return valid_trans;
	}

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::switchViewportLock()
    {
        mViewportLock = !mViewportLock;

        if ( mViewportLock )
        {
			CPlayer* myPlayer = &(CPlayer::getInstance());
			{
				IdType id = 0;
				if ( CPlayer::getInstance().getActiveClan() )
					id = CPlayer::getInstance().getActiveClan()->getMainGenrealID();
				CPlayerCharacterEntity* playerEntity = CSceneManager::getInstance().getPlayerCharacterEntity( id );
				if ( playerEntity )
				{
					focusPos(playerEntity->getPos());
				}
				else
				{
					revertCamera();
				}
			}
        }
    }

	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::setTrackCamera(bool isTrack)
	{
		mIsTrackMode = isTrack;
	}

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::updateFreeCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta )
    {
        Flt d = (Flt)delta * mCameraSpeed;

        //ͨ�����ָı��������������
        Int	wheelRel = input->getMouseWheel();
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

            //camera->translate(getValidFocusDelta(camera_pos, Vec3(0, 0, final_wheel)));
			camera->translate(Vec3(0, 0, final_wheel));
        }

        //����м����Ʒ���
        //��������λ��
        if ( input->isMouseHolded(MB_Middle) )
        {
            bool camera_translate = false;
            Vec3 vec_trans;

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

            if ( camera_translate )
            {
                Flt  scale = 0.0005f;
                Vec3 camera_pos;
                camera->getPosition(camera_pos);

                scale *= camera_pos.y;

                vec_trans.x *= scale;
                vec_trans.y *= scale;
                vec_trans.z *= scale;

                camera->translate(vec_trans);
            }

            Vec2 rel =  input->getMouseMoveDelta();
            rel.x *= -2.0f;
            rel.y *= -2.0f;
            camera->yaw( rel.x );
            camera->pitch( rel.y );
        }
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::updateGameTrackCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta )
    {
        //TODO:
		Flt d = (Flt)delta * 1000;

		////////////////////////////////////////////////////////////////////////////////////////////////////////
		if ( input->isMouseHolded(MB_Middle) )
		{

			////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// �����ͷ����LOD��������ò���
			/// ����������UI���棬�򲻴���ò���
			if ( isCameraStretchLodActive() == false )
				//ClientMain::getInstance().getGui()->isCanHoldUI(VecI2((Int)mousePos.x,(Int)mousePos.y)) == false )
			{
				triggerGameCameraRotateOperation( input, terrain, camera, delta );
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		else
		{
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// ͨ�����ָı��������������
			Int	wheelRel = input->getMouseWheel();
			if(wheelRel != 0)
			{
				triggerGameCameraStretchLodOperation( input, camera, d, wheelRel < 0 );
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////

		updateFocusPos();

		////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::updateGameSLGCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta )
    {
        Flt d = (Flt)delta * 1000;
        Vec2 mousePos = input->getMousePos();
	  
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
		if ( input->isMouseHolded(MB_Middle) )
		{

            ////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// �����ͷ����LOD��������ò���
            /// ����������UI���棬�򲻴���ò���
            if ( isCameraStretchLodActive() == false )
				//ClientMain::getInstance().getGui()->isCanHoldUI(VecI2((Int)mousePos.x,(Int)mousePos.y)) == false )
            {
				triggerGameCameraRotateOperation( input, terrain, camera, delta );
            }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		else
		{
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            /// ͨ�����ָı��������������
            Int	wheelRel = input->getMouseWheel();
            if(wheelRel != 0)
            {
                triggerGameCameraStretchLodOperation( input, camera, d, wheelRel < 0 );
            }

			////////////////////////////////////////////////////////////////////////////////////////////////////////
			//�����ڴ��ڱ�Ե�ƶ������λ��, ���������²��ܶ�, ��ui��Ҳ���ܶ�
			if ( !input->isMouseHolded(MB_Left) )
			{
				triggerGameCameraBorderTranslateCheckOperation(  input, camera, d );
			}
			////////////////////////////////////////////////////////////////////////////////////////////////////////
			
		}
		//triggerGameCameraTestOperation(input, camera, d );
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::triggerGameCameraDragOperation( IInput* input, ITerrainManager* terrain, ICamera* camera )
    {
        if ( isCameraStretchLodActive() )
            return;

        Vec3 currMouseTerrainIntersection;
        if ( terrain->getMouseRayIntersection(currMouseTerrainIntersection) == false )
            return;
        if ( input->isMousePressed(MB_Middle) )
        {
            mLastMouseTerrainIntersection = currMouseTerrainIntersection;
        }
        else
        {
            Vec3 moveDis;
            moveDis = mLastMouseTerrainIntersection - currMouseTerrainIntersection ;

            Vec3 pos, oldPos;
            camera->getPosition(pos);
            oldPos = pos;

            Qua camera_orientation;
            camera->getOrientation(camera_orientation);

            Vec2 rel = input->getMouseMoveDelta();

            if ( rel.x != 0.00 || rel.y != 0.00 )
            {
                pos.x += (Flt)( moveDis.x );
				pos.z += (Flt)( moveDis.z );
            }

            camera->setPosition(oldPos + getValidFocusDelta(oldPos,camera_orientation, pos - oldPos,false) );

            terrain->getMouseRayIntersection(mLastMouseTerrainIntersection);

            stopCameraStretchLod();

            updateFocusPos();
        }
        
    }
	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::triggerGameCameraRotateOperation( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta )
	{
        if ( isCameraStretchLodActive() )
            return;

        // ���λ��
        Vec2 rel = input->getMouseMoveDelta();
        // ��ת�ٶ�
		Flt rotate_speed = 4.0;
        // ��ת�Ƕ�
        Flt yaw_angle = -rel.x * rotate_speed;
        Flt pitch_angle = -rel.y * rotate_speed;

		//��ȡ��ǰ�������������Խ���֮��ķ��� ���ȡ�
		Vec3 cam_pos,cam_dir;
		camera->getSceneNode()->getPosition(cam_pos);
		camera->getSceneNode()->getDirection(cam_dir);

		Vec3 currFocusPos       = getFocusPos();
		Vec3 focusReverseDir    = cam_pos - currFocusPos;
        Flt focusReverseDirLen  = focusReverseDir.length();

		bool change_dirty = false;

		//��y��λ��
		if ( rel.x != 0.0f )
		{
			Qua yawQua;
			yawQua.FromAngleAxis( yaw_angle, Vec3(0,1,0) );
			focusReverseDir = yawQua * focusReverseDir;
			change_dirty = true;
		}

		//��x��λ�ƣ� ע��y��λ������ɵı���x��ƫ��
		if ( rel.y != 0.0f )
		{
			Vec3 local_axis_y = Vec3(0.0f, 1.0f, 0.0f);

			//�����ǰ��λ�Ƶ�λ����
			Vec3 local_axis_x = local_axis_y.crossProduct(focusReverseDir);
			local_axis_x.y = 0.0f;
			local_axis_x.normalise();

			Qua pitchQua;
			pitchQua.FromAngleAxis( pitch_angle, local_axis_x );

			Vec3 resultDir;
			Vec3 normalResultDir;
			normalResultDir = resultDir = pitchQua * focusReverseDir;
			normalResultDir.normalise();

			Vec3 normalfocusReverseDirInPlan;
			normalfocusReverseDirInPlan.x = normalResultDir.x;
			normalfocusReverseDirInPlan.z = normalResultDir.z;
			normalfocusReverseDirInPlan.normalise();

			Flt cosAngle = normalfocusReverseDirInPlan.dotProduct( normalResultDir );

			if ( cosAngle > cos(mCamMinPitch) )
			{
				Qua pitchQua;
				pitchQua.FromAngleAxis( -mCamMinPitch, local_axis_x );

				resultDir = pitchQua * normalfocusReverseDirInPlan;
				resultDir.normalise();

				focusReverseDir = resultDir * focusReverseDir.length();
			}
			else if ( cosAngle < cos(mCamMaxPitch) )
			{
				Qua pitchQua;
				pitchQua.FromAngleAxis( -mCamMaxPitch, local_axis_x );

				resultDir = pitchQua * normalfocusReverseDirInPlan;
				resultDir.normalise();

				focusReverseDir = resultDir * focusReverseDir.length();
			}
			else
			{
				focusReverseDir = resultDir;
			}


			change_dirty = true; 			
		}

		if ( change_dirty )
		{
			cam_pos = currFocusPos + focusReverseDir;
			camera->getSceneNode()->setPosition(cam_pos);
			camera->getSceneNode()->lookAt(currFocusPos);
		}
	}
    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::triggerGameCameraPitchOperation( IInput* input, ICamera* camera, Dbl delta, Int pitchFactor )
    {
        if (pitchFactor!=0)
        {
            Flt pitchV = 0;

            Flt cPitch = camera->getPitch();

            pitchV = cPitch + pitchFactor * delta;

            if (pitchV>mCamMaxPitch)
            {
                pitchV = mCamMaxPitch;
            }
            else if (pitchV<mCamMinPitch)
            {
                pitchV = mCamMinPitch;
            }

            camera->setOrientation(Qua(1,0,0,0));
            camera->pitch( pitchV );
        }
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::triggerGameCameraBorderTranslateCheckOperation( IInput* input, ICamera* camera, Dbl d )
    {
        if ( isCameraStretchLodActive() )
            return;

        IEngineMain* engineMain = ClientMain::getInstance().getEngine();
		if ( !engineMain )
			return;

		ICollisionSystem* collisionSystem = ClientMain::getInstance().getScene()->getCollisionSystem();
		if ( !collisionSystem )
			return;

        UInt width = engineMain->display()->getWidth();
        UInt height = engineMain->display()->getHeight();
        Bool isFullScreen = engineMain->display()->isFullScreen();
        Vec2 mousePos = input->getMousePos();

        // �������ȫ�����ж��Ƿ��ڴ����⣬��������ƶ�
        if( !isFullScreen )
        {
            if ( !input->isFocusLastFrame() )
            {
                return;
            }
        }

        bool camera_translate = false;
        Vec3 vec_trans = Vec3(0,0,0);;

        if(mousePos.x <= mAutoMoveSize)
        { 
            vec_trans += Vec3(1,0,0);
            camera_translate = true;
        }
        if(mousePos.x >= width - mAutoMoveSize)
        {
            vec_trans += Vec3(-1,0,0);
            camera_translate = true;
        }
        if(mousePos.y <= mAutoMoveSize)
        {
            vec_trans += Vec3(0,0,1);
            camera_translate = true;
        }
        if(mousePos.y >= height - mAutoMoveSize)
        {
            vec_trans += Vec3(0,0,-1);
            camera_translate = true;
        }

        if ( camera_translate )
        {
            Vec3 camera_pos;
            camera->getPosition(camera_pos);
			Vec3 camera_dir;
			camera->getDirection(camera_dir);

			//������������˶�����
			Vec3 dir;
			dir = camera_dir;
			dir.y = 0;
			dir.normalise();

			Vec3 up = Vec3(0.0f, 1.0f, 0.0f);
			Vec3 left = up.crossProduct(dir);
			left.normalise();

			Qua camera_qua;
			camera_qua.FromAxis(left, Vec3(0.0f, 1.0f, 0.0f), dir);

            /////////////////////////////////////////////////////////////////////

            // ���ݸ߶ȵ����ƶ��ľ���
            Flt scale  = camera_pos.y;
            if ( scale < 1 )
                scale = 1;

            Flt rate   = 0.001;

			vec_trans.x *= rate * scale * d;
			vec_trans.z *= rate * scale * d;

			// �ƶ��۽���, ��ȡ�½���ĸ߶�
			vec_trans = getValidFocusDelta( camera_pos, camera_qua, vec_trans, true );
			camera_pos += vec_trans;

			// ����λ��
			camera->setPosition( camera_pos );

            // ���¾۽���
            updateFocusPos();
		}
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::triggerGameCameraStretchLodOperation( IInput* input, ICamera* camera, Dbl delta, Bool isRaise )
    {
        Flt dis = getHeightByFocusPos();
        activeCameraStretchLod( dis, isRaise );
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::triggerGameCameraStretchLodOperation2( IInput* input, ICamera* camera, Dbl delta, Bool isRaise )
    {
        //ͨ�����ָı��������������
 
        //mRaiseOrLowHeight = highOrLow;

        //Vec3 currCamPos;
        //camera->getPosition(currCamPos);

        //Vec3 camPos;
        //camera->getSceneNode()->getPosition(camPos);
        //Vec3 terrainIntersection = Vec3(camPos.x,0,camPos.z);
        ////terrain->getRayIntersection(camPos,camDir,terrainIntersection);

        //Vec3 moveDir = camPos - terrainIntersection;
        ////Flt moveLen = ClientMain::getInstance().getEngine()->engineUtil()->getVectorLenght(moveDir);
        ////moveDir = ClientMain::getInstance().getEngine()->engineUtil()->getNormaliseVector(moveDir);
        //Flt moveLen = moveDir.length();
        //Flt curPitch = camera->getPitch();
        //moveDir.normalise();

        ////�õ�Ŀ��߶�
        //Flt desHeight   = mCameraHeightSet[0];
        ////�õ�Ŀ��pitch
        //Flt desPitch	= mCameraPitchSet[0]; 
        //UInt heightSetCount = mCameraHeightSet.size();
        //UInt PitchSetCount = mCameraPitchSet.size();

        //if ( heightSetCount > 0 )
        //{
        //    if (mRaiseOrLowHeight)
        //    {
        //        desHeight = mCameraHeightSet[heightSetCount-1];
        //        desPitch = mCameraPitchSet[PitchSetCount-1];

        //        for (Int i=0;i<heightSetCount;i++)
        //        {
        //            if ( moveLen < mCameraHeightSet[i]-0.1 )
        //            {
        //                desHeight = mCameraHeightSet[i];
        //                break;
        //            }
        //        }

        //        for (Int i=0;i<PitchSetCount;i++)
        //        {
        //            if ( curPitch > mCameraPitchSet[i]+0.1 )
        //            {
        //                desPitch = mCameraPitchSet[i];
        //                break;
        //            }
        //        }
        //    }
        //    else
        //    {
        //        desHeight = mCameraHeightSet[0];
        //        desPitch = mCameraPitchSet[0];

        //        for (Int i=heightSetCount-1;i>=0;i--)
        //        {
        //            if ( moveLen > mCameraHeightSet[i]+0.1 )
        //            {
        //                desHeight = mCameraHeightSet[i];
        //                break;
        //            }
        //        }
        //        for (Int i=PitchSetCount-1;i>=0;i--)
        //        {
        //            if ( curPitch < mCameraPitchSet[i]-0.1 )
        //            {
        //                desPitch = mCameraPitchSet[i];
        //                break;
        //            }
        //        }
        //    }
        //}

        //Vec3 dest_pos;
        //// �ƶ������λ��
        //{

        //    ISceneNodeLineMoveToAction* action = ClientMain::getInstance().getScene()->getActionManager()->createSceneNodeLineMoveToAction( camera->getSceneNode() );

        //    action->setMoveSpeed( mCamGameRollSpeed );
        //    Vec3 movePos = terrainIntersection + moveDir*desHeight;

        //    Qua camera_orientation;
        //    camera->getOrientation(camera_orientation);

        //    action->setIgnoreHeight(false);

        //    dest_pos = currCamPos + getValidFocusDelta( currCamPos, camera_orientation, movePos - currCamPos, false );
        //    action->setMoveToDestination( dest_pos );

        //    camera->getSceneNode()->getLinedStateManager()->push( action );
        //}

        //// �ƶ����������
        //{
        //    ISceneNodePitchToAction* action = ClientMain::getInstance().getScene()->getActionManager()->createSceneNodePitchToAction( camera->getSceneNode() );

        //    Flt pitch_time = (dest_pos - currCamPos).length() / mCamGameRollSpeed;

        //    if ( pitch_time <= 0.0f )
        //        action->setIsImmediately( true );
        //    else
        //        action->setPitchSpeed( fabs( desPitch - camera->getPitch() ) / pitch_time );
        //    //action->setPitchSpeed( 0.25f );

        //    action->setDestAngle( desPitch );
        //    camera->getSceneNode()->getLinedStateManager()->push( action, false );
        //}
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::triggerGameCameraTestOperation( IInput* input, ICamera* camera, Dbl d )
    {
        // ������ �Ժ�ȥ��
        if ( input->isAltOn() )
        {
			//if ( input->isKeyHolded(KC_A) )
			//{
			//	Vec3 cam_pos;
			//	camera->getPosition(cam_pos);

			//	char msg[128];
			//	sprintf_s( msg, 128, "%f\n", (getFocusPos() - cam_pos).length());
			//	OutputDebugString(msg);
			//}

            Bool camera_translate = false;
            Vec3 vec_trans;

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

            if ( camera_translate )
            {
                Flt  scale = .1f;
                Vec3 camera_pos;
                Qua camera_orientation;
                camera->getPosition(camera_pos);
                camera->getOrientation(camera_orientation);

                scale *= camera_pos.y;

                vec_trans.x *= scale;
                vec_trans.y *= scale;
                vec_trans.z *= scale;

                vec_trans = getValidFocusDelta( camera_pos, camera_orientation, vec_trans);

                camera->setPosition(camera_pos + vec_trans);

                camera->getSceneNode()->getLinedStateManager()->clear();
            }
        }
    }


	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::setCameraDefaultPitch( Flt degree )
	{
		mCamDefaultPitch = -degree / 180.0f * MG_PI;
	}

	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::setCameraDefaultHeight( Flt height )
	{
		mCamDefaultHeight = height;
	}

	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::setCameraPitchRange( Flt degreeMin, Flt degreeMax )
	{
		mCamMinPitch = degreeMin / 180.0f * MG_PI;
		mCamMaxPitch = degreeMax  / 180.0f * MG_PI;
	}

	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::setCameraDefaultPos( Vec3 pos )
	{
		mCamDefaultPos = pos;
	}

	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::setCameraMoveBoard( Vec3 minBoard, Vec3 maxBoard )
	{
		mCamMaxBoard = maxBoard;
		mCamMinBoard = minBoard;
		mCamDefaultPos = (mCamMaxBoard + mCamMinBoard) * 0.5f;
	}

	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::setCameraSpeed( Flt transSpeed, Flt rollSpeed )
	{
		mCamGameMoveSpeed = transSpeed;
		mCamGameRollSpeed = rollSpeed;
	}

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::clearCameraStretchLods()
    {
        mCameraStretchLodList.clear();
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::addCameraStretchLod( SLGCameraStretchLod lod )
    {
		//��֤�¼����LOD�� �ǶȺ͸߶ȱ������ԭ�е�LOD
		std::map<UInt, SLGCameraStretchLod>::reverse_iterator iter = mCameraStretchLodList.rbegin();
		if ( iter != mCameraStretchLodList.rend() )
		{
			SLGCameraStretchLod& prelod = iter->second;
			if ( prelod.mHeight > lod.mHeight || prelod.mAngle > lod.mAngle )
				return;
		}

        mCameraStretchLodList[lod.mHeight] = lod;

        if ( lod.mHeight <  mCamMinHeight )
            mCamMinHeight = lod.mHeight;
    }

    //-----------------------------------------------------------------------
    Bool SLGCameraOpCtrl::isCameraStretchLodActive()
    {
        LinedStateObject* stateObj = mCamera->getSceneNode()->getLinedStateManager()->getState( SLGCameraStretchAction::STATE_NAME, true );
        if ( stateObj )
        {
            SLGCameraStretchAction* action = static_cast<SLGCameraStretchAction*>(stateObj);
            if (action)
            {
                return true;
            }
        }
        return false;
    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::activeCameraStretchLod(Flt camDis, Bool isRaise)
    {
        if ( ! mCamera )
            return;

        if ( mCameraStretchLodList.size() == 0 )
        {
			revertCamera();

            return;
        }
        
        ////////////////////////////////////////////////////////////////////////////////////

        std::map<UInt, SLGCameraStretchLod>::iterator iter =  mCameraStretchLodList.begin();
		SLGCameraStretchLod* destlod = &(iter->second);
		Flt camDisDiff = Flt(destlod->mHeight) - Flt(camDis);

		Flt camDisDiffRatio = 1.0f;
		Flt lodDisDiff = 1.0f;

		////////////////////////////////////////////////////////////////////////////////////

        //TODO,��Ҫ���߶Ȳ�����
		//��ȡĿ���Դ���LOD

		if ( isRaise )
		{
			 for ( ;iter != mCameraStretchLodList.end(); iter++ )
			 {
				 // ��ȡĿ��߶Ⱥ����ڱ�������lod�߶�֮��
				 lodDisDiff = Flt( iter->second.mHeight - destlod->mHeight );

				 destlod = &(iter->second);
				 // ����Ŀ��߶Ⱥ͵�ǰ�߶�֮��
				 camDisDiff = Flt(destlod->mHeight) - Flt(camDis);

				 if ( (iter->second).mHeight > camDis )
				 {
					 // ��������������Ļ��� ���ֵ�ǰ������lod�߶ȴ���������߶�
					 // ֱ���˳���ѭ�������ڸ�ѭ�����Ѿ���������Ҫ����ֵ

					 break;
				 } 
			 }
		}
		else
		{
			 for ( ;iter != mCameraStretchLodList.end(); iter++ )
			 {
				 // ��ȡĿ��߶Ⱥ����ڱ�������lod�߶�֮��
				 lodDisDiff = Flt( iter->second.mHeight - destlod->mHeight );
				 
				 if ( (iter->second).mHeight >= camDis )
				 {
					 // ������½������Ļ��� ���ֵ�ǰ������lod�߶ȴ���������߶�
					 // ֱ���˳���ѭ��, ���ϸ�ѭ�����Ѿ���������Ҫ����ֵ

					 break;
				 }

				 destlod = &(iter->second);
				 // ����Ŀ��߶Ⱥ͵�ǰ�߶�֮��
				 camDisDiff = Flt(destlod->mHeight) - Flt(camDis);

			 }
		}
       

        ////////////////////////////////////////////////////////////////////////////////////

        if ( camDis == destlod->mHeight )
        {
            return;
        }

        ////////////////////////////////////////////////////////////////////////////////////

        if ( lodDisDiff == 0 )
        {
            camDisDiffRatio = 1;
        }else
        {
            camDisDiffRatio = abs( camDisDiff / lodDisDiff );
            if ( camDisDiffRatio > 1 )
                camDisDiffRatio = 1;
        }

        // ��Ҫͨ���߶Ȳ�����ʱ��
        Flt lodTime = destlod->getRaiseOrLowTime( isRaise );
        //lodTime = lodTime * camDisDiffRatio;
        lodTime = lodTime;

        ////////////////////////////////////////////////////////////////////////////////////

		mCamMinPitch = destlod->getRadian( destlod->mAngle );

		////////////////////////////////////////////////////////////////////////////////////

        LinedStateObject* stateObj = mCamera->getSceneNode()->getLinedStateManager()->getState( SLGCameraStretchAction::STATE_NAME, true );
        if ( stateObj )
        {
            SLGCameraStretchAction* action = static_cast<SLGCameraStretchAction*>(stateObj);
            if (action)
            {
                if ( action )
                {
                    if ( action->getStretchLod().mHeight == destlod->mHeight )
                    {
                        return;
                    }
                }
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////
        
        mCamera->getSceneNode()->getLinedStateManager()->clear();

        mSLGCameraStretchAction->setStretchLod( *destlod, lodTime );

        mCamera->getSceneNode()->getLinedStateManager()->push( mSLGCameraStretchAction );

        ////////////////////////////////////////////////////////////////////////////////////

    }

    //-----------------------------------------------------------------------
    void SLGCameraOpCtrl::stopCameraStretchLod()
    {
        if ( mCamera )
        {
            mCamera->getSceneNode()->getLinedStateManager()->clear();
        }
    }

	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::applyCameraSetting( const GameCameraConfigInfo* camInfo )
	{
		setCameraDefaultPitch( camInfo->camera_default_pitch );
		setCameraDefaultHeight( camInfo->camera_default_height );
		setCameraPitchRange( camInfo->camera_min_pitch, camInfo->camera_max_pitch );
		setCameraMoveBoard( camInfo->camera_min_board, camInfo->camera_max_board );
		setCameraSpeed( camInfo->camera_move_speed, camInfo->camera_roll_speed );
		setTrackCamera( camInfo->camera_type == GAME_CAMERA_TYPE_TRACK );

		clearCameraStretchLods();

		for ( U32 i = 0; i < camInfo->camera_lod_height.size(); i++ )
		{
			SLGCameraStretchLod LOD;

			if ( i < camInfo->camera_lod_height.size() )
				LOD.mHeight = camInfo->camera_lod_height[i];
			if ( i < camInfo->camera_lod_angle.size() )
				LOD.mAngle = camInfo->camera_lod_angle[i];

			addCameraStretchLod( LOD );
		}

		revertCamera();
		
		if ( mSyncFocus2DPosDirDirty )
		{
			focusPos( mSyncFocus2DPos );
			focusDir( mSyncFocus2DDir );
			mSyncFocus2DPosDirDirty = false;
		}
	}
	//-----------------------------------------------------------------------
	void SLGCameraOpCtrl::updateGameTrackCameraCollision( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta )
	{
		Vec3 newCamDir;
		Vec3 newCamPos;

		Bool isPosChangeDirty = false;
		Bool isDirChangeDirty = false;

		if ( mCamera->getSceneNode()->getLinedStateManager()->isEmpty() )
		{
			Bool isCollisionDetected = false;

			Flt	 moveSpeed = 1.0f * delta;
			Flt  rotateSpeed = 1.0f * delta;

			Vec3 camPos;
			Vec3 camDir;

			mCamera->getPosition(camPos);
			mCamera->getDirection(camDir);

			///////////////////////////////////////////////////////////////////////////////////

			Vec3 intersectPos;

			// �鿴ģ��

			if ( !isCollisionDetected )
			{
						
			}
			
			// �鿴����

			if ( !isCollisionDetected )
			{
				Vec3 rayQueryStart;
				rayQueryStart = mFocusPos;
				rayQueryStart -= camDir * 3.0f;

				if ( terrain->getRayIntersection(rayQueryStart, Vec3(-camDir.x, -camDir.y, -camDir.z), intersectPos, true) )
				{
					if ( (intersectPos - rayQueryStart).length() < (camPos - rayQueryStart).length() )			
						isCollisionDetected = true; 
				}
			}

			// �Ƿ���Ҫ�ƶ��������λ�ã� ʹ�ӽ�Ŀ��
			Vec3 destPos = intersectPos;
			if ( !isCollisionDetected )
			{
				destPos = mFocusPos - mSLGCameraStretchAction->getDestDir();
			}

			if ( (destPos - camPos).length() < 0.001f )
			{
				isPosChangeDirty = false;
			}
			else 
			{
				Vec3 newPos;
				Vec3 moveDir;
				Vec3 resultDir;

				moveDir = destPos - camPos;
				moveDir.normalise();

				newPos = camPos + moveDir * moveSpeed;

				resultDir = destPos - newPos;
				resultDir.normalise();

				if ( ( destPos - newPos ).length() < 0.001f || moveDir.dotProduct(resultDir) < 0.0f )
				{
					isPosChangeDirty = false;
				}
				else
				{
					isPosChangeDirty = true;
					newCamPos = newPos;
				}
			}
		}

		if ( isPosChangeDirty )
		{
			mCamera->setPosition(newCamPos);
		}
	}
}

