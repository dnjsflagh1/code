/******************************************************************************/
#include "StdAfx.h"
#include "CoreManager.h"
#include "GlobalOptions.h"
#include "OperationManager.h"
#include "IEditorSystem.h"
#include "IEditorOperation.h"
#include "IActionManager.h"
#include "IEntity.h"
#include "CharacterList.h"
#include "PointTemplate.h"
#include "TroopTemplate.h"
#include "CharacterBuildList.h"
#include "PlaceListCsv.h"
#include "GameFileDefine.h"
#include "WorldCoreDefine.h"
/******************************************************************************/


namespace GameMapEditor {

    //-----------------------------------------------------------------------
    OperationManager::OperationManager()
        :mOpType(OT_NULL)
        ,mCameraSpeed(1000.0f)
        ,mViewportLock(true)
		,mIsMouseStateCheck(false)
		,mTimeMouseHold(0)
		,mOpInterval(0.05f)
		,mCursorObject(NULL)
    {
        mCameraHeightSet.push_back(20);
        mCameraHeightSet.push_back(40);
        mCameraHeightSet.push_back(60);
        mCameraHeightSet.push_back(80);

		mAutoMoveSize = 100;

		mCamMaxPitch = -30.0f / 180.0f * 3.14f;
		mCamMinPitch = -89.0f / 180.0f * 3.14f;

		mCamDefaultPitch = -45.0f / 180.0f * 3.14f;

		mCamMaxBoard = Vec3( 100.0f, 100.0f, 100.0f);
		mCamMinBoard = Vec3( -100.0f, -100.0f, -100.0f);

		mCamGameRollSpeed = 30.0f;
		mCamGameMoveSpeed = 50.0f;
    }
    //-----------------------------------------------------------------------
    OperationManager::~OperationManager()
    {

    }

	//-----------------------------------------------------------------------
	void OperationManager::preSaveEntity()
	{
		IScene* scene = CoreManager::getInstance().getScene();
		if ( !scene )
			return;

		///////////////////////////////////////////////////////////////////////////
		//获取格式有误的entity
		///////////////////////////////////////////////////////////////////////////

		std::vector<Str> entityNameList;
		entityNameList.clear();

		U32 count = scene->getEntityCount();

		for ( U32 index = 0; index < count; index++ )
		{
			IEntity* entity = scene->getEntity(index);
			if ( entity )
			{
				if ( !isCustomAttributeComplete(entity) )
				{
					entityNameList.push_back( entity->getName() );
				}
			}
		}

		///////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////
		///删除格式有误的ENTITY
		///////////////////////////////////////////////////////////////////////////

		count = entityNameList.size();

		for ( U32 index = 0; index < count; index++ )
		{
			scene->getXmlSerializer()->removeSceneObjectFormat( entityNameList[index].c_str(), SOT_ENTITY, true, true);
		}

		///////////////////////////////////////////////////////////////////////////
	}

    //-----------------------------------------------------------------------
    void OperationManager::update( Dbl delta )
    {
        updateCameraOp( delta );
        updateEditorOp( delta );
		updateCursorElement();
    }

    //-----------------------------------------------------------------------
    void OperationManager::switchViewportLock()
    {
        mViewportLock = !mViewportLock;

        if ( mViewportLock )
        {
            focusCamera( ( mCamMaxBoard + mCamMinBoard ) * 0.5f );
        }
    }

	//-----------------------------------------------------------------------
	Vec3 OperationManager::getValidCameraDelta(Vec3 pos, Qua orientation, Vec3 delta, bool isLocal )
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

		//判断x平面和-x平面
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

		//y平面不判断
		//判断y平面和-y平面
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

		//判断z平面和-z平面
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
				pos = ( mCamMaxBoard + mCamMinBoard ) * 0.5f;
                camera->getPosition(pos);
				pos.y = 100;
                camera->setPosition(pos);

				//camera->setPosition(Vec3(0,0,0));

                camera->pitch(mCamDefaultPitch);
            }
        }
    }

	//-----------------------------------------------------------------------
	void OperationManager::focusCamera(Vec3 pos)
	{
		IInput* input = CoreManager::getInstance().getEngineMain()->input();
		IScene* scene = CoreManager::getInstance().getScene();

		if ( scene )
		{
			ICamera* camera = scene->getActiveCamera();
			if ( camera )
			{
				//清空动作
				camera->getSceneNode()->getLinedStateManager()->clear();
				//获得未聚焦镜头位置
				revertCamera();

				Vec3 cur_pos;
				Flt cur_pitch;
				camera->getPosition(cur_pos);
				cur_pitch = camera->getPitch();

				//获取聚焦镜头位置
				camera->focusPosition(pos);

				Vec3 focus_pos;
				Flt focus_pitch;
				camera->getPosition(focus_pos);
				focus_pitch = camera->getPitch();

				//获取在范围内的位置
				Vec3 valid_trans = getValidCameraDelta( cur_pos, Qua(1,0,0,0), focus_pos - cur_pos, false );
				camera->setPosition( cur_pos + valid_trans );

				if ( focus_pitch > mCamMaxPitch )
					camera->pitch( mCamMaxPitch );
				else if ( focus_pitch < mCamMinPitch )
					camera->pitch( mCamMinPitch );
			}
		}
	}

    //-----------------------------------------------------------------------
    void OperationManager::updateCameraOp( Dbl delta )
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

		if ( camera )
		{
			//切换控制方式
			if ( input->isKeyPressed(KC_F1) )
			{
				switchViewportLock();
			}

			//改变摄像机速度
			if ( input->isKeyPressed(KC_MINUS) )
			{
				mCameraSpeed -= 100.0f;
				if ( mCameraSpeed < 0.0f )
					mCameraSpeed = 100.0f;
				//FormSet::main_form->onEventCamspeedChanged( U32(mCameraSpeed / 10.0f) );
			}else
				if ( input->isKeyPressed(KC_EQUALS) )
				{
					mCameraSpeed += 100.0f;
					if ( mCameraSpeed > 2000.0f )
						mCameraSpeed = 2000.0f;
					//FormSet::main_form->onEventCamspeedChanged( U32(mCameraSpeed / 10.0f) );
				}

				if ( mViewportLock )
				{
					updateGameCameraOp(input,terrain,camera,delta);
				}else
				{
					updateFreeCameraOp(input,terrain,camera,delta);
				}
		}
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateFreeCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta )
    {   
		if (!input->isFocusLastFrame())
			return;

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

    //-----------------------------------------------------------------------
    void OperationManager::updateGameCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta )
    {
		if (!input->isFocusLastFrame())
			return;

		Flt d = (Flt)delta * mCamGameMoveSpeed;
		//Flt	d_roll = (Flt)mCamGameMoveSpeed;
		Vec2 mousePos = input->getMousePos();
		//鼠标右键控制位置
		if ( input->isMousePressed(MB_Middle) || input->isMouseHolded(MB_Middle) )
		{
			// 如果鼠标是在UI上面，则不处理游戏对象操作
			//if ( CoreManager::getInstance().getGui()->isCanHoldUI(VecI2(mousePos.x,mousePos.y)) == false )
			{
				Vec3 currMouseTerrainIntersection;
				if ( terrain->getMouseRayIntersection(currMouseTerrainIntersection) == false )
					return;
				if ( input->isMousePressed(MB_Left) )
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

					if ( abs(rel.x) > 0.00 )
					{
						pos.x += (Flt)( moveDis.x );
					}
					if ( abs(rel.y) > 0.00 )
					{
						pos.z += (Flt)( moveDis.z );
					}

					camera->setPosition(oldPos + getValidCameraDelta(oldPos,camera_orientation, pos - oldPos,false) );

					terrain->getMouseRayIntersection(mLastMouseTerrainIntersection);

					camera->getSceneNode()->getLinedStateManager()->clear();
				}
			}
		}
		else
		{
			//控制角度
			{
				Flt pitchV = 0;
				if ( input->isKeyHolded(KC_HOME) )
				{
					pitchV = 1;
				}
				else if ( input->isKeyHolded(KC_END) )
				{
					pitchV = -1;
				}

				if (pitchV!=0)
				{
					Flt cPitch = camera->getPitch();
					pitchV = cPitch + pitchV * delta;

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
					///////////////////////////////////////////////
				}
			}

			//通过滚轮改变摄像机离地面距离
			Int	wheelRel = input->getMouseWheel();
			if(wheelRel != 0)
			{
				mRaiseOrLowHeight = wheelRel < 0;
				Vec3 currCamPos;
				camera->getPosition(currCamPos);

				//Vec3 camDir = Vec3( 0.0f, -1.0f, 0.0f );
				//camera->getSceneNode()->getDirection(camDir);

				Vec3 camPos;
				camera->getSceneNode()->getPosition(camPos);
				Vec3 terrainIntersection = Vec3(camPos.x,0,camPos.z);
				//terrain->getRayIntersection(camPos,camDir,terrainIntersection);

				Vec3 moveDir = camPos - terrainIntersection;
				//Flt moveLen = ClientMain::getInstance().getEngine()->engineUtil()->getVectorLenght(moveDir);
				//moveDir = ClientMain::getInstance().getEngine()->engineUtil()->getNormaliseVector(moveDir);
				Flt moveLen = moveDir.length();
				moveDir.normalise();

				//得到目标高度
				Flt desHeight   = 20;
				UInt setCount = mCameraHeightSet.size();
				if ( setCount > 0 )
				{
					if (mRaiseOrLowHeight)
					{
						desHeight = mCameraHeightSet[setCount-1];
						for (Int i=0;i<setCount;i++)
						{
							if ( moveLen < mCameraHeightSet[i]-0.1 )
							{
								desHeight = mCameraHeightSet[i];
								break;
							}
						}
					}else
					{
						desHeight = mCameraHeightSet[0];
						for (Int i=setCount-1;i>=0;i--)
						{
							if ( moveLen > mCameraHeightSet[i]+0.1 )
							{
								desHeight = mCameraHeightSet[i];
								break;
							}
						}
					}
				}

				// 移动摄像机
				{

					ISceneNodeLineMoveToAction* action = CoreManager::getInstance().getScene()->getActionManager()->createSceneNodeLineMoveToAction( camera->getSceneNode() );

					action->setMoveSpeed( mCamGameRollSpeed );
					Vec3 movePos = terrainIntersection + moveDir*desHeight;

					Qua camera_orientation;
					camera->getOrientation(camera_orientation);

					action->setMoveToDestination( currCamPos + getValidCameraDelta( currCamPos, camera_orientation, movePos - currCamPos, false ) );

					camera->getSceneNode()->getLinedStateManager()->push( action );
				}
			}
		}

		//鼠标放在窗口边缘移动摄像机位置, 鼠标左键摁下不能动, 在ui上也不能动
		if ( !input->isMouseHolded(MB_Left) )
		{
			IEngineMain* engineMain = CoreManager::getInstance().getEngineMain();

			UInt width = engineMain->display()->getWidth();
			UInt height = engineMain->display()->getHeight();
			Bool isFullScreen = engineMain->display()->isFullScreen();
			Vec2 mousePos = input->getMousePos();

			// 如果不是全屏则判断是否在窗口外，如果是则不移动
			if( !isFullScreen )
			{
				if ( !input->isFocusLastFrame() )
				{
					return;
				}
			}

			bool camera_translate = false;
			Vec3 vec_trans;

			if(mousePos.x <= mAutoMoveSize)
			{
				//Flt rate = (mAutoMoveSize - mousePos.x) / mAutoMoveSize;
				Flt rate = 0.5f;
				vec_trans = vec_trans + Vec3(-d * rate * 2.0f,0,0);
				camera_translate = true;
			}
			if(mousePos.x >= width - mAutoMoveSize)
			{
				//Flt rate = (mousePos.x - width + mAutoMoveSize ) / mAutoMoveSize;
				Flt rate = 0.5f;
				vec_trans = vec_trans + Vec3(d * rate * 2.0f,0,0);
				camera_translate = true;
			}
			if(mousePos.y <= mAutoMoveSize)
			{
				//Flt rate = (mAutoMoveSize - mousePos.y) / mAutoMoveSize;
				Flt rate = 0.5f;
				vec_trans = vec_trans + Vec3(0,0,-d * rate * 2.0f);
				camera_translate = true;
			}
			if(mousePos.y >= height - mAutoMoveSize)
			{
				//Flt rate = (mousePos.y - height + mAutoMoveSize ) / mAutoMoveSize;
				Flt rate = 0.5f;
				vec_trans = vec_trans + Vec3(0,0,d * rate * 2.0f);
				camera_translate = true;
			}

			if ( camera_translate )
			//if ( 0 )
			{
				Flt  scale = 1.0f;
				Vec3 camera_pos;
				Qua camera_orientation;
				camera->getPosition(camera_pos);
				camera->getOrientation(camera_orientation);

				//scale *= fabs( camera_pos.y ) / mCamMaxBoard.y ;

				vec_trans.x *= scale;
				vec_trans.y *= scale;
				vec_trans.z *= scale;

				vec_trans = getValidCameraDelta( camera_pos, camera_orientation, vec_trans, false );			
				camera->getSceneNode()->getLinedStateManager()->clear();
				camera->setPosition(camera_pos+vec_trans);
			}

		}

		// 测试用 以后去掉
		if ( input->isAltOn() )
		{
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
				Flt  scale = 1.0f;
				Vec3 camera_pos;
				Qua camera_orientation;
				camera->getPosition(camera_pos);
				camera->getOrientation(camera_orientation);

				scale *= camera_pos.y;

				vec_trans.x *= scale;
				vec_trans.y *= scale;
				vec_trans.z *= scale;

				vec_trans = getValidCameraDelta( camera_pos, camera_orientation, vec_trans);

				camera->setPosition(camera_pos + vec_trans);

				camera->getSceneNode()->getLinedStateManager()->clear();
			}
		}
    }

    //-----------------------------------------------------------------------
    void OperationManager::prepareCreateSceneObject( U32 objectDeclID )
    {
		mCurrOperationID = objectDeclID;

		//让原本在编辑视图选中的物件先失去焦点
		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene )
		{
			ISceneObjectController* sceneObjCtrl = scene->getSceneObjectController();
			if ( sceneObjCtrl )
				sceneObjCtrl->setFocus(NULL);
			destroyCursorElement();
			createCursorElement(objectDeclID);
		}
    }

    //-----------------------------------------------------------------------
    void OperationManager::setActiveEditorOp(OperationType type)
    {
        mOpType = type;
    }

	//-----------------------------------------------------------------------
	IEntity* OperationManager::createObject()
	{
		//和美术用SceneEditor制作的静态文件区分开来
		Str groupName = SCENE_OBJECT_GROUP_STR_OBJECT;
		Str prefix = groupName + "_";
		IEntity* entity	= CoreManager::getInstance().getScene()->createEntity(mCurrOperationID, prefix.c_str());

		if ( entity )
		{
			//设置组别
			entity->setGroup(groupName);
			
			//设置渲染状态
			entity->getDeclaration().isLoadWhenGame = true;
			entity->getDeclaration().batchGroup = entity->getName();

			//设置自定义参数
			Str attribute;
			MG::MGStrOp::toString(mCurrOperationID, attribute);
			entity->setCustomAttr("CharID",attribute);
		}

		return entity;
	}


	//-----------------------------------------------------------------------
	IEntity* OperationManager::createNpc()
	{
		const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( mCurrOperationID );
		if ( !charInfo )
			return NULL;

		Str groupName = SCENE_OBJECT_GROUP_STR_NPC;
		Str prefix = groupName + "_";

		IEntity* entity = CoreManager::getInstance().getScene()->createEntity(charInfo->getCharacterArtMashId(), prefix.c_str());
		if ( entity )
		{
			//播放默认动画
			IAnimationController* animCtrl = entity->getAnimationController();
			if ( animCtrl )
			{
				//animCtrl->play("idle");
			}
			//设置组别
			entity->setGroup(groupName);

			//设置渲染状态
			entity->getDeclaration().isLoadWhenGame = false;
			entity->getDeclaration().batchGroup = "";

			//设置自定义参数
			Str attribute;
			MG::MGStrOp::toString(mCurrOperationID, attribute);
			entity->setCustomAttr("CharID",attribute);
		}

		return entity;
	}
	//-----------------------------------------------------------------------
	IEntity* OperationManager::createMonster()
	{
		const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( mCurrOperationID );
		if ( !charInfo )
			return NULL;

		Str groupName = SCENE_OBJECT_GROUP_STR_MONSTER;
		Str prefix = groupName + "_";

		IEntity* entity = CoreManager::getInstance().getScene()->createEntity(charInfo->getCharacterArtMashId(), prefix.c_str());
		if ( entity )
		{
			//播放默认动画
			IAnimationController* animCtrl = entity->getAnimationController();
			if ( animCtrl )
			{
				//animCtrl->play("normal_idle001");
			}

			//设置组别
			entity->setGroup(groupName);

			//设置渲染状态
			entity->getDeclaration().isLoadWhenGame = false;
			entity->getDeclaration().batchGroup = "";

			//设置自定义参数
			Str attribute;
			MG::MGStrOp::toString(mCurrOperationID, attribute);
			entity->setCustomAttr("CharID",attribute);
		}

		return entity;
	}
	//-----------------------------------------------------------------------
	IEntity* OperationManager::createPoint()
	{
		const PointTempInfo* pointInfo = PointTemplate::getInstance().getPointTempInfo( mCurrOperationID );
		if ( !pointInfo )
			return NULL;

		Str groupName = SCENE_OBJECT_GROUP_STR_POINT;
		Str prefix = groupName + "_";

		IEntity* entity	= CoreManager::getInstance().getScene()->createEntity(pointInfo->ArtMashId, prefix.c_str());

		if ( entity )
		{
			//设置组别
			entity->setGroup(groupName);

			//设置渲染状态
			entity->getDeclaration().isLoadWhenGame = false;
			entity->getDeclaration().batchGroup = "";

			//设置自定义参数
			Str attribute;
			MG::MGStrOp::toString(mCurrOperationID, attribute);
			entity->setCustomAttr("PointID",attribute);
			
			MG::MGStrOp::toString(pointInfo->UseType, attribute);
			entity->setCustomAttr("UseType",attribute);
		}

		return entity;
	}
	//-----------------------------------------------------------------------
	IEntity* OperationManager::createPlace()
	{
		Str groupName = SCENE_OBJECT_GROUP_STR_PLACE;
		Str prefix = groupName + "_";

		const PlaceListCsvInfo* csvInfo = PlaceListCsv::getInstance().getPlaceListInfo( mCurrOperationID);
		if ( !csvInfo )
			return NULL;

		IEntity* entity	= CoreManager::getInstance().getScene()->createEntity(csvInfo->artMashResId, prefix.c_str());
		if ( entity )
		{
			//设置组别
			entity->setGroup(groupName);

			//设置渲染状态
			entity->getDeclaration().isLoadWhenGame = false;
			entity->getDeclaration().batchGroup = "";

			//设置自定义参数
			Str attribute;
			MG::MGStrOp::toString(mCurrOperationID, attribute);
			entity->setCustomAttr("PlaceID",attribute);
		}

		return entity;
	}
	//-----------------------------------------------------------------------
	IEntity* OperationManager::createTroop()
	{
		Str groupName = SCENE_OBJECT_GROUP_STR_TROOP;
		Str prefix = groupName + "_";

		const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( mCurrOperationID);
		if ( !charInfo )
			return NULL;

		IEntity* entity = CoreManager::getInstance().getScene()->createEntity( charInfo->getCharacterArtMashId(), prefix.c_str() );
		if ( entity )
		{
			ISceneNode* sceneNode = entity->getSceneNode();
			if ( sceneNode )
			{
				sceneNode->setScale(Vec3(5.0f,5.0f,5.0f));
			}

			//播放默认动画
			IAnimationController* animCtrl = entity->getAnimationController();
			if ( animCtrl )
			{
				//animCtrl->play("run");
			}
			//设置组别
			entity->setGroup(groupName);

			//设置渲染状态
			entity->getDeclaration().isLoadWhenGame = false;
			entity->getDeclaration().batchGroup = "";

			//设置自定义参数
			Str attribute;

			MG::MGStrOp::toString(mCurrOperationID, attribute);
			entity->setCustomAttr("CharID",attribute);
		}

		return entity;
	}
	//-----------------------------------------------------------------------
	IEntity* OperationManager::createRegion()
	{
		//const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( mCurrOperationID );
		//if ( !charInfo )
		//	return NULL;

		//Str groupName = STR_OBJECT_GROUP_REGION;
		//Str prefix = groupName + "_";

		//IEntity* entity = CoreManager::getInstance().getScene()->createEntity(charInfo->ArtMashId, prefix.c_str());
		//if ( entity )
		//{
		//	//设置组别
		//	entity->setGroup(groupName);

		//	//设置渲染状态
		//	entity->getDeclaration().isLoadWhenGame = false;
		//	entity->getDeclaration().batchGroup = "";

		//	//设置自定义参数
		//	Str attribute;
		//	MG::MGStrOp::toString(mCurrOperationID, attribute);
		//	entity->setCustomAttr("CharID",attribute);
		//}

		//return entity;
		return NULL;
	}
	//-----------------------------------------------------------------------
	IEntity* OperationManager::createStaticObject()
	{
		//和美术用SceneEditor制作的静态文件区分开来
		Str groupName = Str("DESIGN_") + SCENE_OBJECT_GROUP_STR_STATIC;
		Str prefix = groupName + "_";
		IEntity* entity	= CoreManager::getInstance().getScene()->createEntity(mCurrOperationID, prefix.c_str());

		if ( entity )
		{
			//设置组别
			entity->setGroup(groupName);

			//设置渲染状态
			entity->getDeclaration().isLoadWhenGame = true;
			entity->getDeclaration().batchGroup = entity->getName();
		}

		return entity;
	}
	//-----------------------------------------------------------------------
	IEntity* OperationManager::createBuilding()
	{
		const CharacterTempInfo* charInfo = CharacterTemplate::getInstance().getCharacterTempInfo( mCurrOperationID );
		if ( !charInfo || charInfo->CharacterType != CHARACTER_TYPE_BUILD )
			return NULL;

		const CharacterBuildInfo* buildInfo = CharacterBuildList::getInstance().getCharacterBuildInfo(charInfo->CharacterListId);
		if ( !buildInfo )
			return NULL;

		Str groupName = SCENE_OBJECT_GROUP_STR_BUILDING;
		Str prefix = groupName + "_";

		IEntity* entity = CoreManager::getInstance().getScene()->createEntity(charInfo->getCharacterArtMashId(), prefix.c_str());
		if ( entity )
		{
			//播放默认动画
			IAnimationController* animCtrl = entity->getAnimationController();
			if ( animCtrl )
			{
				//animCtrl->play("idle");
			}
			//设置组别
			entity->setGroup(groupName);

			//设置渲染状态
			entity->getDeclaration().isLoadWhenGame = false;
			entity->getDeclaration().batchGroup = "";

			//设置自定义参数
			Str attribute;
			MG::MGStrOp::toString(mCurrOperationID, attribute);
			entity->setCustomAttr("CharID",attribute);

			MG::MGStrOp::toString(buildInfo->BuildType, attribute);
			entity->setCustomAttr("BuildType", attribute);

			MG::MGStrOp::toString(FORCE_INIT, attribute);
			entity->setCustomAttr("Forces", attribute);
		}

		return entity;
	}


	//-----------------------------------------------------------------------
	ISceneObject* OperationManager::execCreateOrCopyEffectEntity( Vec3 pos , IEffectEntity* srcEntity,Int effectDeclID )
	{
		IScene* scene = CoreManager::getInstance().getScene();
		IEffectEntity* desEntity = NULL;
		Str groupName = Str("DESIGN_") + SCENE_OBJECT_GROUP_STR_EFFECT;

		// 如果有选中物体， 需要拷贝选中物体的属性， 包括这个物体的属性
		if ( srcEntity && 
			srcEntity->getSceneNode() )
		{
			//位移
			Vec3 oldPos;
			srcEntity->getSceneNode()->getPosition(oldPos);
			pos.y = oldPos.y;

			Vec3 trans = pos - oldPos;
			trans.y = 0.0f;

			//复制单选物件
			Str prefix = srcEntity->getGroup() + "_";
			desEntity = CoreManager::getInstance().getScene()->createEffectEntity( srcEntity->getEffectResourceID(), false );

			//设置新物件的属性
			if ( desEntity &&  
				desEntity->getSceneNode() )
			{
				copyEffectEntityBaseAttribute( desEntity, srcEntity );

				desEntity->getSceneNode()->setPosition( oldPos + trans );

				if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
				{
					desEntity->getSceneNode()->stickTerrain();
				}

				//CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desEntity);
			}

			//复制复选物件
			std::vector<ISceneObject*> multiSelectObjects;

			CoreManager::getInstance().getScene()->getSceneObjectController()->getMultiFocusList( multiSelectObjects );

			for ( U32 n = 0; n < multiSelectObjects.size(); n++  )
			{
				ISceneObject* srcObject = multiSelectObjects[n];

				if ( srcObject && srcObject->getType() == SOT_EFFECTENTITY )
				{
					IEffectEntity* srcEntity = dynamic_cast<IEffectEntity*>(srcObject);
					IEffectEntity* desEntity = NULL;

					Str prefix = srcEntity->getGroup() + "_";

					if ( srcEntity && 
						srcEntity->getSceneNode() )
					{
						desEntity = CoreManager::getInstance().getScene()->createEffectEntity( srcEntity->getEffectResourceID(), false );

						if ( desEntity &&  
							desEntity->getSceneNode() )
						{
							copyEffectEntityBaseAttribute( desEntity, srcEntity );

							Vec3 oldPos;
							srcEntity->getSceneNode()->getPosition(oldPos);

							Vec3 newPos = oldPos + trans;
							desEntity->getSceneNode()->setPosition(newPos);

							if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
							{
								desEntity->getSceneNode()->stickTerrain();
							}

							//CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desEntity);
						}

					}
				}
			}
		}
		// 没有选中物体则自己创建
		else
		{
			if ( effectDeclID == 0 )
				return NULL;

			desEntity	= CoreManager::getInstance().getScene()->createEffectEntity(mCurrOperationID, false);

			if ( desEntity && 
				desEntity->getSceneNode() )
			{
				//设置组别
				desEntity->setGroup(groupName);

				//设置自定义参数
				//Str attribute;
				//MG::MGStrOp::toString(mCurrOperationID, attribute);
				//desEntity->setCustomAttr("CharID",attribute);

				desEntity->getSceneNode()->setPosition( pos );

				if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
				{
					desEntity->getSceneNode()->stickTerrain();
				}

				//CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desEntity);
			}
		}

		return desEntity;
	}
	//-----------------------------------------------------------------------
	void OperationManager::copyEffectEntityBaseAttribute(IEffectEntity* targetObj, IEffectEntity* srcObj)
	{
		if ( srcObj && targetObj )
		{
			ISceneNode* srcSceneNode = srcObj->getSceneNode();
			ISceneNode* targetSceneNode = targetObj->getSceneNode();

			if ( srcSceneNode && 
				targetSceneNode )
			{
				////////////////////////////////////////////

				Vec3 scale;
				srcSceneNode->getScale(scale);
				targetSceneNode->setScale(scale);

				////////////////////////////////////////////

				Qua quaternion;
				srcSceneNode->getOrientation(quaternion);
				targetSceneNode->setOrientation(quaternion);

				////////////////////////////////////////////

				targetObj->setGroup(srcObj->getGroup());
				srcObj->copyCustomAttrTo(targetObj);
			}
		}
	}

	//-----------------------------------------------------------------------
	bool OperationManager::isCustomAttributeComplete(IEntity* entity)
	{
		bool isComplete = true;

		if ( !entity )
			return false;

		if ( entity->getType() != SOT_ENTITY )
			return isComplete;

		Str& group = entity->getGroup();
		std::map<Str,Str>& attrlist = entity->getCustomAttrList();

		/////////////////////////////////////////////////////////////////////////////////////////////////
		//检查基本属性
		/////////////////////////////////////////////////////////////////////////////////////////////////

		if( group.compare( SCENE_OBJECT_GROUP_STR_OBJECT ) == 0 ||
			group.compare( SCENE_OBJECT_GROUP_STR_NPC ) == 0 || 
			group.compare( SCENE_OBJECT_GROUP_STR_MONSTER ) == 0 ||
			group.compare( SCENE_OBJECT_GROUP_STR_TROOP ) == 0 ||
			group.compare( SCENE_OBJECT_GROUP_STR_BUILDING ) == 0 ||
			group.compare( SCENE_OBJECT_GROUP_STR_GENERAL ) == 0 )
		{
			if ( attrlist.find("CharID") == attrlist.end() )
				isComplete = false;
		}
		else if ( group.compare( SCENE_OBJECT_GROUP_STR_PLACE ) == 0 )
		{
			if ( attrlist.find("PlaceID") == attrlist.end() )
				isComplete = false;
		}
		else if ( group.compare( SCENE_OBJECT_GROUP_STR_POINT ) == 0  )
		{
			if ( attrlist.find("PointID") == attrlist.end() )
				isComplete = false;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////
		//检查Building
		/////////////////////////////////////////////////////////////////////////////////////////////////
		if ( isComplete && group.compare( SCENE_OBJECT_GROUP_STR_BUILDING) == 0 )
		{
			//是否有buildType属性， 属性值是否正确
			std::map<Str,Str>::iterator iter = attrlist.find("BuildType");
			if ( iter != attrlist.end() )
			{
				I32 buildType = 0;
				MGStrOp::toI32( iter->second.c_str(), buildType );

				if ( buildType < (I32)CHAR_BUILD_TYPE_NULL || buildType >= (I32)CHAR_BUILD_TYPE_MAX )
					isComplete = false;
			}
			else
			{
				isComplete = false;
			}

			//是否有Force属性， 属性值是否正确
			if ( isComplete )
			{
				iter = attrlist.find("Forces");
				if ( iter != attrlist.end() )
				{
					I32 Force = 0;
					MGStrOp::toI32( iter->second.c_str(), Force );

					if ( Force < (I32)FORCE_ATTACK || Force >= (I32)FORCE_MAX )
						isComplete = false;
				}
				else
				{
					isComplete = false;
				}
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////
		//检查point
		/////////////////////////////////////////////////////////////////////////////////////////////////
		if ( isComplete && group.compare( SCENE_OBJECT_GROUP_STR_POINT) == 0 )
		{
			//是否有useType属性， 属性值是否正确
			std::map<Str,Str>::iterator iter = attrlist.find("UseType");
			if ( iter != attrlist.end() )
			{
				I32 UseType = 0;
				MGStrOp::toI32( iter->second.c_str(), UseType );

				if ( UseType < (I32)point_rpg_jump_in || UseType > (I32)point_slg_born_defender_troop )
					isComplete = false;
			}
			else
			{
				isComplete = false;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
	
		return isComplete;
	}
	//-----------------------------------------------------------------------
	void OperationManager::copyEntityBaseAttribute(IEntity* targetObj, IEntity* srcObj)
	{
		if ( srcObj && targetObj )
		{
			ISceneNode* srcSceneNode = srcObj->getSceneNode();
			ISceneNode* targetSceneNode = targetObj->getSceneNode();

			if ( srcSceneNode && 
				targetSceneNode )
			{
				////////////////////////////////////////////

				Vec3 scale;
				srcSceneNode->getScale(scale);
				targetSceneNode->setScale(scale);

				////////////////////////////////////////////

				Qua quaternion;
				srcSceneNode->getOrientation(quaternion);
				targetSceneNode->setOrientation(quaternion);

				////////////////////////////////////////////

				////////////////////////////////////////////
				targetObj->getDeclaration() = srcObj->getDeclaration();
				////////////////////////////////////////////
				
				////////////////////////////////////////////
				targetObj->setGroup(srcObj->getGroup());
				srcObj->copyCustomAttrTo(targetObj);
				////////////////////////////////////////////

				if ( targetObj->getDeclaration().autoAnimation.empty() == false )
				{
					targetObj->getAnimationController()->play( targetObj->getDeclaration().autoAnimation.c_str() );
				}
			}
		}
	}
    //-----------------------------------------------------------------------
    void OperationManager::clearEditorOp()
    {
		destroyCursorElement();
        mOpType = OT_NULL;

    }

    //-----------------------------------------------------------------------
    void OperationManager::stickSelectElementToTerrain()
    {
        CoreManager::getInstance().getScene()->getSceneObjectController()->stickTerrain();
    }

    //-----------------------------------------------------------------------
    void OperationManager::destroySelectElement()
    {
        ISceneObject* object = CoreManager::getInstance().getScene()->getSceneObjectController()->getFocus();
        if ( object && object != mCursorObject )
        {
			FormSet::main_form->revert();
            CoreManager::getInstance().getScene()->getXmlSerializer()->removeSceneObjectFormat(object->getName().c_str(), object->getType(), true, true);
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateEditorOp( Dbl delta )
    {
		IInput* input               = CoreManager::getInstance().getEngineMain()->input();
		if ( input == NULL )
			return;

		IScene* scene               = CoreManager::getInstance().getScene();
		if ( scene == NULL )
			return;

		ITerrainManager* terrain           = scene->getTerrainManager();
		if ( terrain == NULL )
			return;

		IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();
		if ( editorSys == NULL )
			return;

		{
			//快捷键退出编辑操作
			if ( input->isKeyReleased( KC_ESCAPE ) )
			{
				//clearEditorOp();
				destroyCursorElement();
			}

			//Debug信息
			if ( input->isKeyReleased( KC_1 ) )
			{
				FormSet::main_form->updateDebugInfo();
			}

			//快捷键随机选取创建的模型
			if ( input->isKeyPressed( KC_LSHIFT ) )
			{
				//FormSet::main_form->randonPrepareCreateEntityByModelDeclList();
			}

			//快捷键对选中的物件贴地
			if ( input->isKeyReleased( KC_D ) && input->isAltOn() )
			{
				this->stickSelectElementToTerrain();
			}

			//快捷键对选中的物件删除
			if ( input->isKeyReleased( KC_DELETE ) )
			{
				this->destroySelectElement();
			}


			//左键单击创建物体
			if ( input->isMousePressed(MB_Left) )
			{	
				if (mCursorObject)
				{
					this->dropCursorElement();
				}
			}

			//ctrl+c拷贝物体到鼠标
			if ( (input->isKeyHolded(KC_LCONTROL)|| input->isKeyHolded(KC_RCONTROL)) && input->isKeyPressed(KC_C) )
			{	
				this->copyElementToCursor();
			}

			//快捷键网格模式
			if ( input->isKeyPressed(KC_G) )
			{
				IEngineMain* engineMain = CoreManager::getInstance().getEngineMain();
				if ( engineMain && engineMain->display() )
				{
					IDisplay* idisplay = engineMain->display();
					idisplay->setWireframeMode((!idisplay->getWireframeMode()));
				}
			}

			//快捷键网格模式
			if ( input->isKeyPressed(KC_T) )
			{
				IEngineMain* engineMain = CoreManager::getInstance().getEngineMain();
				if ( engineMain && engineMain->display() )
				{
					IDisplay* idisplay = engineMain->display();
					idisplay->setTerrainGridsVisible((!idisplay->getTerrainGridsVisible()));
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////
			//快捷键整体移动场景物件
			static Dbl sceneObjectMoveSpeed = 10.0;
			Vec3 moveVec;
			Bool needTranslate = false;
			if (input->isShiftOn() )
			{
				if (input->isKeyPressed(KC_MINUS))
				{
					if (sceneObjectMoveSpeed > 0.1)
						sceneObjectMoveSpeed /= 2;
				}
				else if (input->isKeyPressed(KC_EQUALS))
				{
					if (sceneObjectMoveSpeed < 1000.0)
						sceneObjectMoveSpeed *= 2;
				}

				if ( input->isKeyReleased(KC_LEFT) )
				{
					moveVec = Vec3(-sceneObjectMoveSpeed,0.0,0.0);
					needTranslate = true;
				}
				else if (input->isKeyReleased(KC_RIGHT))
				{
					moveVec = Vec3(sceneObjectMoveSpeed,0.0,0.0);
					needTranslate = true;
				}
				else if (input->isKeyReleased(KC_UP))
				{
					moveVec = Vec3(0.0,0.0,-sceneObjectMoveSpeed);
					needTranslate = true;
				}
				else if (input->isKeyReleased(KC_DOWN))
				{
					moveVec = Vec3(0.0,0.0,sceneObjectMoveSpeed);
					needTranslate = true;
				}
			}

			if (needTranslate)
			{
				std::vector<ISceneObjectXmlFormat*> formatList;
				std::vector<ISceneObjectXmlFormat*>::iterator iter;
				Vec3 pos;
				scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_ENTITY, formatList,true);

				//trees
				std::vector<ISceneObjectXmlFormat*> treeFormatList;
				scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_TREE, treeFormatList,true);
				formatList.insert(formatList.end(),treeFormatList.begin(),treeFormatList.end());

				//grass
				std::vector<ISceneObjectXmlFormat*> grassFormatList;
				scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_GRASS, grassFormatList,true);
				formatList.insert(formatList.end(),grassFormatList.begin(),grassFormatList.end());

				//特效
				std::vector<ISceneObjectXmlFormat*> effectFormatList;
				scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_EFFECTENTITY, effectFormatList,true);
				formatList.insert(formatList.end(),effectFormatList.begin(),effectFormatList.end());

				for (  iter= formatList.begin(); iter!=formatList.end(); iter++ )
				{
					ISceneObjectXmlFormat* format = *iter;
					ISceneObject* obj = format->getSceneObject();
					ISceneNode* sceneNode = obj->getSceneNode();
					sceneNode->getPosition(pos);
					pos.x += moveVec.x;
					pos.y += moveVec.y;
					pos.z += moveVec.z;
					sceneNode->setPosition(pos);
					format->fill();
					//sceneNode->translate(moveVec,MG::ISceneNode::TS_WORLD);
				}
			}
		}
    }

	//-----------------------------------------------------------------------
	void OperationManager::setCameraDefaultPitch( Flt degree )
	{
		mCamDefaultPitch = -degree / 180.0f * MG_PI;
	}

	//-----------------------------------------------------------------------
	void OperationManager::setCameraPitchRange( Flt degreeMin, Flt degreeMax )
	{
		mCamMaxPitch = -degreeMin / 180.0f * MG_PI;
		mCamMinPitch = -degreeMax  / 180.0f * MG_PI;
	}

	//-----------------------------------------------------------------------
	void OperationManager::setCameraDefaultPos( Vec3 pos )
	{
		mCamDefaultPos = pos;
	}

	//-----------------------------------------------------------------------
	void OperationManager::setCameraMoveBoard( Vec3 minBoard, Vec3 maxBoard )
	{
		mCamMaxBoard = maxBoard;
		mCamMinBoard = minBoard;
		mCamDefaultPos = maxBoard + minBoard;
	}

	//-----------------------------------------------------------------------
	void OperationManager::setCameraSpeed( Flt transSpeed, Flt rollSpeed )
	{
		mCamGameMoveSpeed = transSpeed;
		mCamGameRollSpeed = rollSpeed;
	}

	//-----------------------------------------------------------------------
	ISceneObject* OperationManager::createCursorElement(U32 objectDeclID)
	{
		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene )
		{
			Vec3 pos;
			scene->getTerrainManager()->getMouseRayIntersection(pos,true);
			switch( mOpType )
			{
			case OT_CREATE_OBJECT:
				{
					mCursorObject = createObject();
					break;
				}
			case OT_CREATE_PLACE:
				{
					mCursorObject = createPlace();
					break;
				}
			case OT_CREATE_POINT:
				{
					mCursorObject = createPoint();
					break;
				}
			case OT_CREATE_MONSTER:
				{
					mCursorObject = createMonster();
					break;
				}
			case OT_CREATE_NPC:
				{
					mCursorObject = createNpc();
					break;
				}
			case OT_CREATE_TROOP:
				{
					mCursorObject = createTroop();
					break;
				}
			case OT_CREATE_REGION:
				{
					mCursorObject = createRegion();
					break;
				}
			case OT_CREATE_STATIC_OBJECT:
				{
					mCursorObject = createStaticObject();
					break;
				}
			case OT_CREATE_BUILDING:
				{
					mCursorObject = createBuilding();
					break;
				}
			case OT_CREATE_EFFECT:
				{
					//mCursorObject = scene->createEffectEntity( "SampleEntity", objectDeclID,false);
					mCursorObject = execCreateOrCopyEffectEntity(pos,NULL,objectDeclID);
					break;
				}
			}

			if (mCursorObject)
			{
				mCursorObject->setQueryFlags(0);
				//mCursorObject->getSceneNode()->setVisible(false);
			}
		}

		return mCursorObject;
	}

	//-----------------------------------------------------------------------
	void OperationManager::destroyCursorElement(void)
	{
		if ( mCursorObject != NULL )
		{
			IScene* scene = CoreManager::getInstance().getScene();
			if (scene)
			{
				ISceneObject* object = CoreManager::getInstance().getScene()->getSceneObjectController()->getFocus(); 
				if (object == mCursorObject)
				{
					CoreManager::getInstance().getScene()->getSceneObjectController()->setFocus( NULL );
				}
				scene->getXmlSerializer()->removeSceneObjectFormat(mCursorObject->getName().c_str(), mCursorObject->getType(),true);
			}
		}
		mCursorObject = NULL;
		
	}

	//-----------------------------------------------------------------------
	void OperationManager::updateCursorElement()
	{
		if (mCursorObject != NULL)
		{
			if (mCursorObject->getType() == SOT_ENTITY)
			{
				Flt minHLValue = 1.0f;
				Flt maxHLValue = 1.5f;
				static Flt delta = 0.01f; //每次变化量
				static Flt curHLValue = 1.0f; //当前高光值

				//控制高光值在minHLValue到maxHLValue间来回变化
				if (delta > 0)
				{
					if (curHLValue < maxHLValue)
						curHLValue += delta;
					else
					{
						curHLValue = maxHLValue;
						delta *= -1;
					}
				}
				else
				{
					if (curHLValue > minHLValue)
						curHLValue += delta;
					else
					{
						curHLValue = minHLValue;
						delta *= -1;
					}
				}

				IEntity* entity = static_cast<IEntity*>(mCursorObject);
				entity->getModelObject()->setHightLight(curHLValue);
			}
			else
			{
				int i = 0;
			}
			
			//获取当前鼠标位置
			Vec3 pos;
			//mCursorObject->getSceneNode()->setVisible(true);
			if (FormSet::scene_form->Focused)
			{
				CoreManager::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true);
			}
			else
			{
				Vec3 camPos,camDir;
				CoreManager::getInstance().getScene()->getActiveCamera()->getPosition(camPos);
				CoreManager::getInstance().getScene()->getActiveCamera()->getDirection(camDir);
				CoreManager::getInstance().getScene()->getTerrainManager()->getRayIntersection(camPos,camDir,pos,true);
			}

			mCursorObject->getSceneNode()->setPosition(pos);
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::showCursorElement()
	{
		if (mCursorObject)
		{
			mCursorObject->getSceneNode()->setVisible(true);
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::hideCursorElement()
	{
		if (mCursorObject)
		{
			mCursorObject->getSceneNode()->setVisible(false);
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::dropCursorElement()
	{
		Vec3 pos;
		ISceneObject *newObj = NULL;
		if ( CoreManager::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true) )
		{
			IScene* scene = CoreManager::getInstance().getScene();
			if ( !scene )
				return;

			if (mCursorObject != NULL)
			{
				//拷贝鼠标物体
				U32 objectDeclID;
				//OperationType optype = mCursorObject->getType();
				switch( mOpType )
				{
				case OT_CREATE_OBJECT:
					{
						IEntity* entity = static_cast<IEntity*>(mCursorObject);
						newObj = createObject();
						copyEntityBaseAttribute(static_cast<IEntity*>(newObj),entity);
						break;
					}
				case OT_CREATE_PLACE:
					{
						IEntity* entity = static_cast<IEntity*>(mCursorObject);
						newObj = createPlace();
						copyEntityBaseAttribute(static_cast<IEntity*>(newObj),entity);
						break;
					}
				case OT_CREATE_POINT:
					{
						IEntity* entity = static_cast<IEntity*>(mCursorObject);
						newObj = createPoint();
						copyEntityBaseAttribute(static_cast<IEntity*>(newObj),entity);
						break;
					}
				case OT_CREATE_MONSTER:
					{
						IEntity* entity = static_cast<IEntity*>(mCursorObject);
						newObj = createMonster();
						copyEntityBaseAttribute(static_cast<IEntity*>(newObj),entity);
						break;
					}
				case OT_CREATE_NPC:
					{
						IEntity* entity = static_cast<IEntity*>(mCursorObject);
						newObj = createNpc();
						copyEntityBaseAttribute(static_cast<IEntity*>(newObj),entity);
						break;
					}
				case OT_CREATE_TROOP:
					{
						IEntity* entity = static_cast<IEntity*>(mCursorObject);
						newObj = createTroop();
						copyEntityBaseAttribute(static_cast<IEntity*>(newObj),entity);
						break;
					}
				case OT_CREATE_REGION:
					{
						IEntity* entity = static_cast<IEntity*>(mCursorObject);
						newObj = createRegion();
						copyEntityBaseAttribute(static_cast<IEntity*>(newObj),entity);
						break;
					}
				case OT_CREATE_STATIC_OBJECT:
					{
						IEntity* entity = static_cast<IEntity*>(mCursorObject);
						newObj = createStaticObject();
						copyEntityBaseAttribute(static_cast<IEntity*>(newObj),entity);
						break;
					}
				case OT_CREATE_BUILDING:
					{
						IEntity* entity = static_cast<IEntity*>(mCursorObject);
						newObj = createBuilding();
						copyEntityBaseAttribute(static_cast<IEntity*>(newObj),entity);
						break;
					}
				case OT_CREATE_EFFECT:
					{
						IEffectEntity* effectEntity = static_cast<IEffectEntity*>(mCursorObject);
						objectDeclID = static_cast<IEffectEntity*>(mCursorObject)->getEffectResourceID();
						newObj = execCreateOrCopyEffectEntity( pos, effectEntity, objectDeclID );
						break;
					}
				}

				if ( newObj )
				{
					ISceneNode* node = newObj->getSceneNode();
					if (node)
					{
						node->setPosition(pos);
					}

					//加入xml
					ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(newObj, true);
					//ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat(newObj->getName().c_str(), newObj->getType());
					if ( format )
					{
						FormSet::main_form->loadSceneElementProps( format, false );
						FormSet::main_form->loadSceneElementList();
					}
				}
			}	
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::copyElementToCursor()
	{
		Vec3 pos;
		U32 objectDeclID;
		if ( CoreManager::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true) )
		{
			IScene* scene = CoreManager::getInstance().getScene();
			if ( !scene )
				return;

			// 复制的对象
			ISceneObject* copyObj = NULL;

			ISceneObjectController* sceneObjCtrl =  scene->getSceneObjectController();
			if ( sceneObjCtrl )
			{
				copyObj = sceneObjCtrl->getFocus();
			}

			// 复制
			if ( copyObj )
			{
				if (mCursorObject)
					destroyCursorElement();

				//OperationType optype = copyObj->getType();
				switch( mOpType )
				{
				case OT_CREATE_OBJECT:
					{
						IEntity* entity = static_cast<IEntity*>(copyObj);
						mCursorObject = createObject();
						copyEntityBaseAttribute(static_cast<IEntity*>(mCursorObject),entity);
						break;
					}
				case OT_CREATE_PLACE:
					{
						IEntity* entity = static_cast<IEntity*>(copyObj);
						mCursorObject = createPlace();
						copyEntityBaseAttribute(static_cast<IEntity*>(mCursorObject),entity);
						break;
					}
				case OT_CREATE_POINT:
					{
						IEntity* entity = static_cast<IEntity*>(copyObj);
						mCursorObject = createPoint();
						copyEntityBaseAttribute(static_cast<IEntity*>(mCursorObject),entity);
						break;
					}
				case OT_CREATE_MONSTER:
					{
						IEntity* entity = static_cast<IEntity*>(copyObj);
						mCursorObject = createMonster();
						copyEntityBaseAttribute(static_cast<IEntity*>(mCursorObject),entity);
						break;
					}
				case OT_CREATE_NPC:
					{
						IEntity* entity = static_cast<IEntity*>(copyObj);
						mCursorObject = createNpc();
						copyEntityBaseAttribute(static_cast<IEntity*>(mCursorObject),entity);
						break;
					}
				case OT_CREATE_TROOP:
					{
						IEntity* entity = static_cast<IEntity*>(copyObj);
						mCursorObject = createTroop();
						copyEntityBaseAttribute(static_cast<IEntity*>(mCursorObject),entity);
						break;
					}
				case OT_CREATE_REGION:
					{
						IEntity* entity = static_cast<IEntity*>(copyObj);
						mCursorObject = createRegion();
						copyEntityBaseAttribute(static_cast<IEntity*>(mCursorObject),entity);
						break;
					}
				case OT_CREATE_STATIC_OBJECT:
					{
						IEntity* entity = static_cast<IEntity*>(copyObj);
						mCursorObject = createStaticObject();
						copyEntityBaseAttribute(static_cast<IEntity*>(mCursorObject),entity);
						break;
					}
				case OT_CREATE_BUILDING:
					{
						IEntity* entity = static_cast<IEntity*>(copyObj);
						mCursorObject = createBuilding();
						copyEntityBaseAttribute(static_cast<IEntity*>(mCursorObject),entity);
						break;
					}
				case OT_CREATE_EFFECT:
					{
						IEffectEntity* effectEntity = static_cast<IEffectEntity*>(copyObj);
						objectDeclID = effectEntity->getEffectResourceID();
						mCursorObject = execCreateOrCopyEffectEntity( pos, effectEntity, objectDeclID );
						break;
					}
				}

				ISceneNode* node = mCursorObject->getSceneNode();
				if (node)
				{
					node->setPosition(pos);
				}
			}
		}
	}
}

