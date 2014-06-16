/******************************************************************************/
#include "stdafx.h"
#include "LoginScreenOpCtrl.h"
#include "ClientMain.h"
#include "CSceneManager.h"
#include "LoginScreen.h"
#include "IActionManager.h"
#include "ICollisionSystem.h"
/******************************************************************************/
namespace MG
{

    //--------------------------------------------------------------------------
    LoginScreenOpCtrl::LoginScreenOpCtrl()
		:mCurrFocusIndex(0)
		,mTargetFocusIndex(0)
		,mNextFocusIndex(0)
		,mLeftMousePressEntity(NULL)
		,mMouseHoldEntity(NULL)
		,mCtrlState(CTRL_STATE_SEL_NONE)

	{	
    }

    //--------------------------------------------------------------------------
    LoginScreenOpCtrl::~LoginScreenOpCtrl()
    {
        clear();
    }

    //--------------------------------------------------------------------------
    void LoginScreenOpCtrl::update(Flt delta)
    {
		if ( getCtrlState() == CTRL_STATE_SEL_CLAN )
		{
			updateSelClanOperation(delta);
		}
		else if ( getCtrlState() == CTRL_STATE_SEL_CHAR )
		{
			updateSelCharOperation(delta);
		}
		else if ( getCtrlState() == CTRL_STATE_CREATE_CHAR )
		{
			updateCreateCharOperation(delta);
		}
    }

    //--------------------------------------------------------------------------
    void LoginScreenOpCtrl::clear()
    {
        
    }

    //--------------------------------------------------------------------------
    void LoginScreenOpCtrl::revert()
    {
		IScene* scene = ClientMain::getInstance().getScene();
		if ( !scene )
			return;

		ICamera* camera = ClientMain::getInstance().getScene()->getActiveCamera();
		if ( camera )
		{
			//////////////////////////////////////////////////////////////////////////////////

			camera->getSceneNode()->getLinedStateManager()->clear();

			//////////////////////////////////////////////////////////////////////////////////
			if ( getCtrlState() == CTRL_STATE_SEL_CLAN )
			{
				Vec3 direction;
				mCurrFocusIndex = 0;

				IEntity* targetEntity = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_SUSAKU + mCurrFocusIndex );
				if ( targetEntity )
				{
					Vec3 position;
					targetEntity->getSceneNode()->getPosition(position);

					direction = position - Vec3(0.0f,0.0f,0.0f);
				}

				camera->setDirection(direction);
				camera->setPosition(Vec3(0.0f,0.0f,0.0f));
				camera->setNearClipDistance(2.0f);
				camera->setFarClipDistance(2000.0);
				camera->setFov(45);
			}
			//////////////////////////////////////////////////////////////////////////////////
			else if ( getCtrlState() == CTRL_STATE_CREATE_CHAR )
			{
				Vec3 camPos;
				Vec3 camDir;

				IEntity* cameraTemplate = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_CAMERA_2 );
				if ( cameraTemplate )
				{
					cameraTemplate->getSceneNode()->getPosition(camPos);
				}

				IEntity* cameraTarget = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_CAMERA_TARGET_2 );
				if ( cameraTarget )
				{
					Vec3 targetPos;
					cameraTarget->getSceneNode()->getPosition(targetPos);

					camDir = targetPos - camPos;
					camDir.normalise();
				}

				camera->setPosition( camPos );
				camera->setDirection( camDir );

				camera->setFov(45.705f);
				camera->setNearClipDistance(0.01f);
				camera->setFarClipDistance(30.0f);
			}
			//////////////////////////////////////////////////////////////////////////////////
			else if ( getCtrlState() == CTRL_STATE_SEL_CHAR )
			{
				Vec3 camPos;
				Vec3 camDir;

				IEntity* cameraTemplate = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_CAMERA_1 );
				if ( cameraTemplate )
				{
					cameraTemplate->getSceneNode()->getPosition(camPos);
				}

				IEntity* cameraTarget = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_CAMERA_TARGET_1 );
				if ( cameraTarget )
				{
					Vec3 targetPos;
					cameraTarget->getSceneNode()->getPosition(targetPos);

					camDir = targetPos - camPos;
					camDir.normalise();
				}

				camera->setPosition( camPos );
				camera->setDirection( camDir );

				camera->setFov(30.705f);
				camera->setNearClipDistance(0.01f);
				camera->setFarClipDistance(30.0f);
			}

			//////////////////////////////////////////////////////////////////////////////////	
		}
    }

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::updateSelClanOperation(Flt delta)
	{

	}

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::updateSelCharOperation(Flt delta)
	{
		
	}

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::updateCreateCharOperation(Flt delta)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////

		// ���������
		IInput* input = ClientMain::getInstance().getEngine()->input();

		// ���߲�ѯ����
		ISceneObject* sceneObject       =   NULL;
		ILogicBinder* logicBinder       =   NULL;
		CCharacterSceneEntity* entity   =   NULL;

		/////////////////////////////////////////////////////////////////////////////////////////////////

		// ʰȡʵ��ļ��
		ISceneObjectCollisionCallback callback;
		callback.queryFlagsMask = GQT_SOLDIER | GQT_PLAYERCHARACTER;
		callback.isCheckSingle = false;

		if ( ClientMain::getInstance().getScene()->getCollisionSystem()->checkMouseRayCollision(&callback) )
		{
			sceneObject = callback.collisionList[callback.collisionList.size() - 1].second;

			if(sceneObject)
			{
				// ������Ϸ�߼��󶨶��������Ϣ
				logicBinder =  sceneObject->getLogicBinder();

				if( logicBinder )
				{
					/////////////////////////////////////////////////////////////////////////////////////////

					if(logicBinder->type != GOT_TROOP)
					{
						entity = (CCharacterSceneEntity*)logicBinder->manager;
					}

					/////////////////////////////////////////////////////////////////////////////////////////

					if ( !entity )
						return;
				}
			}
		}
	
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( ClientMain::getInstance().getGui()->isMouseCanHoldUI() )
		{
			entity = NULL;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( entity )
		{
			if ( input->isMousePressed(MB_Left) )
			{
				mLeftMousePressEntity = entity;
				onLeftMousePress( entity );
			}
			else if ( input->isMouseReleased(MB_Left) )
			{
				onLeftMouseReleased( entity );

				if ( mLeftMousePressEntity == entity )
					onLeftMouseClick( entity );
			}

			mMouseHoldEntity = entity;
			onMouseOver( entity );
		}

		if ( !entity && mMouseHoldEntity )
		{
			mMouseHoldEntity = NULL;
			onMouseLeave( mMouseHoldEntity );
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////

		if ( input->isMouseReleased(MB_Left) )
		{
			mLeftMousePressEntity = NULL;

		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
	}

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::turnCamera(Bool isReverse,Flt turnSpeed)
	{
		///////////////////////////////////////////////////////////////////////////

		// ������������˶�״̬�� ���ء�
		IScene* scene = ClientMain::getInstance().getScene();
		ICamera* camera = scene->getActiveCamera();

		if ( !camera->getSceneNode()->getLinedStateManager()->isEmpty() )
			return;

		///////////////////////////////////////////////////////////////////////////

		// ����0�ŵ�3��ģ��( ������ �׻��� ��ȸ�� ���� )

		mNextFocusIndex = mCurrFocusIndex;

		if ( isReverse )
			mNextFocusIndex = mCurrFocusIndex - 1;
		else
			mNextFocusIndex = mCurrFocusIndex + 1;

		if ( mTargetFocusIndex < 0 )
			mTargetFocusIndex = LoginScreen::FOCUS_ENTITY_MAX - 1;
		else if ( mTargetFocusIndex >= LoginScreen::FOCUS_ENTITY_MAX )
			mTargetFocusIndex = 0;
		
		///////////////////////////////////////////////////////////////////////////

		// ��ת���������׼�µ�ģ��	
		IEntity* targetEntity = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_SUSAKU + mNextFocusIndex );
		if ( targetEntity )
		{
			Vec3 camPos;
			Vec3 targetPos;

			camera->getPosition(camPos);
			targetEntity->getSceneNode()->getPosition(targetPos);

			Vec3 newDir = targetPos - camPos;
			newDir.normalise();

			ISceneNodeDirectToAction* action = scene->getActionManager()->createSceneNodeDirectToAction(camera);
			action->addListener(this);

			action->setDestDirection(newDir);
			//action->setShiftSpeed(0.5f);
			action->setShiftSpeed(turnSpeed);

			camera->getSceneNode()->getLinedStateManager()->push(action);
		}

		///////////////////////////////////////////////////////////////////////////
	}
	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::turnCameraImmediately( Str entityName )
	{
		///////////////////////////////////////////////////////////////////////////

		IEntity* targetEntity = LoginScreen::getInstance().getEntity( entityName );
		if ( !targetEntity )
			return;

		for ( int i = 0; i < LoginScreen::FOCUS_ENTITY_MAX; i++ )
		{
			IEntity* entity = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_SUSAKU + i );

			if ( !entity->getName().compare( entityName ) )
			{	
				mTargetFocusIndex = i;
				mNextFocusIndex = i;
				break;
			}
		}

		///////////////////////////////////////////////////////////////////////////

		// ������������˶�״̬�� ���
		IScene* scene = ClientMain::getInstance().getScene();
		ICamera* camera = scene->getActiveCamera();

		////////////////////////////////////////////////////////////////////////////////////

		Vec3 camPos;
		Vec3 targetPos;

		camera->getPosition(camPos);
		targetEntity->getSceneNode()->getPosition(targetPos);

		Vec3 newDir = targetPos - camPos;
		newDir.normalise();

		ISceneNodeDirectToAction* action = scene->getActionManager()->createSceneNodeDirectToAction(camera);
		action->addListener(this);

		action->setDestDirection(newDir);
		action->setImmediately(true);

		camera->getSceneNode()->getLinedStateManager()->clear();
		camera->getSceneNode()->getLinedStateManager()->push(action);

		///////////////////////////////////////////////////////////////////////////

	}

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::turnCamera( Str entityName, Flt turnSpeed )
	{
		///////////////////////////////////////////////////////////////////////////

		// ������������˶�״̬�� ���
		IScene* scene = ClientMain::getInstance().getScene();
		ICamera* camera = scene->getActiveCamera();

		////////////////////////////////////////////////////////////////////////////////////

		IEntity* targetEntity = LoginScreen::getInstance().getEntity( entityName );
		if ( !targetEntity )
			return;

		for ( int i = 0; i < LoginScreen::FOCUS_ENTITY_MAX; i++ )
		{
			IEntity* entity = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_SUSAKU + i );

			if ( !entity->getName().compare( entityName ) )
			{	
				mTargetFocusIndex = i;
				break;
			}
		}

		////////////////////////////////////////////////////////////////////////////////////

		// �������������ת����

		int  TargetDir = mTargetFocusIndex - mNextFocusIndex;
		int  MovingDir = mNextFocusIndex - mCurrFocusIndex;

		// ���ϴε���ת����ͬ, �ͼٶ����Ѿ���������һ����Ҫ��ת����λ�á�
		if ( TargetDir * MovingDir < 0 )
		{
			mCurrFocusIndex = mNextFocusIndex;
		}

		Bool isReverse = false;

		// Ѱ����̻��ȣ�

		{
			/*if ( LoginScreen::FOCUS_ENTITY_MAX - abs(dist) < abs(dist) )
			{
			if ( dist > 0 )
			isReverse = true;
			}
			else
			{
			if ( dist < 0 )
			isReverse = true;
			}*/
		}
		
		// ���չ̶�������ת��
		{
			if ( TargetDir < 0 )
				isReverse = true;
		}

		if ( !isReverse )
		{
			if (mNextFocusIndex == 0 && mTargetFocusIndex == LoginScreen::FOCUS_ENTITY_MAX -1)
			{
				mNextFocusIndex = LoginScreen::FOCUS_ENTITY_MAX -1; //��0ֱ��ת�����һ��
			}
			else
				mNextFocusIndex = mCurrFocusIndex + 1;
		}
		else
			// ѭ��ת������0->1->2->3->0
		{
			if (mNextFocusIndex == LoginScreen::FOCUS_ENTITY_MAX -1 && mTargetFocusIndex == 0)
			{
				mNextFocusIndex = 0;  //�����һ��ֱ��ת��0
			}
			else
				mNextFocusIndex = mCurrFocusIndex - 1;
		}

		////////////////////////////////////////////////////////////////////////////////////

		// ��ת���������׼�µ�ģ��	
		targetEntity = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_SUSAKU + mNextFocusIndex );
		if ( targetEntity )
		{
			Vec3 camPos;
			Vec3 targetPos;

			camera->getPosition(camPos);
			targetEntity->getSceneNode()->getPosition(targetPos);

			Vec3 newDir = targetPos - camPos;
			newDir.normalise();

			ISceneNodeDirectToAction* action = scene->getActionManager()->createSceneNodeDirectToAction(camera);
			action->addListener(this);

			action->setDestDirection(newDir);
			//action->setShiftSpeed(0.5f);
			action->setShiftSpeed(turnSpeed);

			camera->getSceneNode()->getLinedStateManager()->clear();
			camera->getSceneNode()->getLinedStateManager()->push(action);
		}

		///////////////////////////////////////////////////////////////////////////
	}
    //--------------------------------------------------------------------------
    void LoginScreenOpCtrl::onStartLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {

    }

    //--------------------------------------------------------------------------
    void LoginScreenOpCtrl::onEndLoadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {

    }

    //--------------------------------------------------------------------------
    void LoginScreenOpCtrl::onUnloadScene( RegionIdType regionId, REGION_OBJ_TYPE regionType )
    {
        clear();
    }

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::onLinedStateLeave( LinedStateObject* obj )
	{
		if ( mCtrlState == CTRL_STATE_SEL_CLAN )
		{
			ISceneNodeDirectToAction* action = dynamic_cast<ISceneNodeDirectToAction*>(obj);
			if ( action->isFinished() )
			{
				mCurrFocusIndex = mNextFocusIndex;

				if ( mTargetFocusIndex != mCurrFocusIndex )
				{
					IEntity* targetEntity = LoginScreen::getInstance().getEntity( LoginScreen::ENTITY_SUSAKU + mTargetFocusIndex );
					if ( targetEntity )
					{
						turnCamera( targetEntity->getName(), action->getShiftSpeed());
					}
				}
			}
		}
	}

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::onLeftMouseClick(CCharacterSceneEntity* entity)
	{
		if ( mCtrlState == CTRL_STATE_CREATE_CHAR )
		{
			LoginScreen::getInstance().selectGeneral( entity );
		}
	}

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::onLeftMousePress(CCharacterSceneEntity* entity)
	{
		
	}

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::onLeftMouseHold(CCharacterSceneEntity* entity)
	{

	}

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::onLeftMouseReleased(CCharacterSceneEntity* entity)
	{

	}

	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::onMouseOver( CCharacterSceneEntity*	entity )
	{
		if ( mCtrlState == CTRL_STATE_CREATE_CHAR )
		{
			LoginScreen::getInstance().prepareSelectGeneral( entity );
		}
	}
	//--------------------------------------------------------------------------
	void LoginScreenOpCtrl::onMouseLeave( CCharacterSceneEntity*	entity )
	{
		if ( mCtrlState == CTRL_STATE_CREATE_CHAR )
		{
			LoginScreen::getInstance().prepareSelectGeneral( NULL );
		}
	}
	


}