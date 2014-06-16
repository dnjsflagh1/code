/******************************************************************************/
#include "stdafx.h"
#include "MGSceneNode.h"
#include "EngineMain.h"
#include "SceneObjectController.h"
#include "InputManager.h"
#include "Scene.h"
#include "ICollisionSystem.h"
#include "TerrainManager.h"

/******************************************************************************/

namespace MG
{


	//-----------------------------------------------------------------------
	const String SceneObjectController::AxisUtilObjectsMeshName[AxisUtilCount] = {
		"axes_x.mesh",  //Axis_X
		"axes_y.mesh",  //Axis_Y
		"axes_z.mesh",  //Axis_Z
		"axes_z_alpha.mesh",  //Axis_XY
		"axes_x_alpha.mesh",  //Axis_XZ
		"axes_y_alpha.mesh"   //Axis_YX
	};

	//-----------------------------------------------------------------------
	const String SceneObjectController::AxisUtilObjectsName[AxisUtilCount] = {
		"_GObjAxisCon_Axis_x",  //Axis_X
		"_GObjAxisCon_Axis_y",  //Axis_Y
		"_GObjAxisCon_Axis_z",  //Axis_Z
		"_GObjAxisCon_Axis_xy",  //Axis_XY
		"_GObjAxisCon_Axis_xz",  //Axis_XZ
		"_GObjAxisCon_Axis_yz"   //Axis_YX
	};

	//-----------------------------------------------------------------------
	SceneObjectController::SceneObjectController(Scene* scene)
		:mScene(scene)
		,mEnable(false)
		,mChangedDirty(false)
		,mObjectOperationDirty(false)
		,mTerrainSticked(true)
		,mSceneObject(NULL)
        ,mControlType(SOC_SLG)
		,mIsMovingSceneObject(false)
		,mIsMouseRayTerrainIntersectionValid(false)
        ,mSelectUtilIndex(-1)
        ,mMoveSpeed(1)
        ,mYawRotateSpeed(1)
		,mUtilPlaneSize(0)
		,mUtilAxisLength(0)
		,mUtilAxisBaseScale(0)
        ,isFocusRect(false)
		,mTreeBoundingBoxRenderNode(NULL)
		,mIgnoreObject(NULL)
		,mFocusEnable(true)
	{
		createUtilObjects();
	}
	//-----------------------------------------------------------------------
	SceneObjectController::~SceneObjectController()
	{
		destroyUtilObjects();
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::update( Flt delta )
	{
        if ( mEnable )
        {
            mChangedDirty = false;

			if ( getFocusEnable() )
			{
				if ( !updateSceneObjectRectFocus() )
					updateSceneObjectFocus();
			}
		
            if ( mSceneObject )
            {
				beginUpdateMultiFocusObjects();

				updateCommonOp();

                if ( mControlType == SOC_SLG )
                {
                    updateSLGOp();
                }
				else
				{
					if ( updateUtilObjectFocus() == true )
						updateUtilObjectsOp();			
				}

				endUpdateMultiFocusObjects();

				updateUtilObjectsLocation();
				updateUtilObjectsScale();
            }
        }
	}
    //-----------------------------------------------------------------------
    Bool SceneObjectController::updateUtilObjectFocus()
    {
        if ( mSceneObject )
        {
            if ( InputManager::getSingletonPtr()->isMousePressed(MB_Right))
            {
                Vec3 pos,dir;
                mScene->getActiveCamera()->getMouseViewportRay(pos,dir);
                Ogre::Ray ray(Vector3(pos.x,pos.y,pos.z),Vector3(dir.x,dir.y,dir.z));
				mSelectUtilIndex = -1;

                for(Int i = 0; i < AxisUtilCount; ++i)
                {
                    const AxisAlignedBox& box = mAxisUtilObjects[i]->getModelObject()->getOgreEntity()->getWorldBoundingBox();
                    std::pair< bool, Real > intersect = ray.intersects( box );
                    if (intersect.first == true)
                    {
                        mSelectUtilIndex = i;
                        break;
                    }
                }

				if ( mSelectUtilIndex >= 0 )
					setFocusedUtilObjectMaterial( mSelectUtilIndex );
				else
					restoreAllUtilObjectsMaterial();
            }
			else if ( InputManager::getSingletonPtr()->isMouseReleased(MB_Right) )
			{
				mSelectUtilIndex = -1;
				restoreAllUtilObjectsMaterial();
			}
        }

		return mSelectUtilIndex != -1;
    }
	//-----------------------------------------------------------------------
	void SceneObjectController::beginUpdateMultiFocusObjects()
	{
		mObjectOperationDirty = false;

		if ( mSceneObject && mSceneObject->getSceneNode() )
		{
			ISceneNode* sceneNode = mSceneObject->getSceneNode();

			sceneNode->getOrientation(mLastFrameSingleFocusOrientation);
			sceneNode->getScale(mLastFrameSingleFocusScale);
			sceneNode->getPosition(mLastFrameSingleFocusPosition);
		}
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::endUpdateMultiFocusObjects()
	{
		if ( !mObjectOperationDirty )
			return;

		if ( mSceneObject && mSceneObject->getSceneNode() )
		{
			ISceneNode* focusNode = mSceneObject->getSceneNode();

			Qua  currSingleFocusOrientation;
			Vec3 currSingleFocusPosition;
			Vec3 currSingleFocusScale;

			focusNode->getOrientation(currSingleFocusOrientation);
			focusNode->getScale(currSingleFocusScale);
			focusNode->getPosition(currSingleFocusPosition);

			Qua deltaOrientation = currSingleFocusOrientation * mLastFrameSingleFocusOrientation.Inverse();
			Vec3 deltaScale = currSingleFocusScale - mLastFrameSingleFocusScale;
			Vec3 deltaPos = currSingleFocusPosition - mLastFrameSingleFocusPosition;
			
			for ( int index = 0; index < mMultiSelectRes.size(); index++ )
			{
				if ( mMultiSelectRes[index] )
				{
					ISceneNode* node = mMultiSelectRes[index]->getSceneNode();

					if ( node )
					{
						/// 设置每个物件的缩放
						Vec3 oldScale;
						node->getScale(oldScale);
						node->setScale(oldScale + deltaScale);

						/// 设置每个物件的旋转
						Qua oldOrientation;
						node->getOrientation(oldOrientation);
						node->setOrientation(deltaOrientation * oldOrientation);

						/// 设置每个物件的位移
						Vec3 oldPos;
						node->getPosition(oldPos);

						if ( isTerrainSticked() )
						{
							deltaPos.y = 0.0f;
						}

						node->setPosition(oldPos + deltaPos);

						if ( isTerrainSticked() )
						{
							node->stickTerrain();
						}
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::updateCommonOp()
	{
		//快捷键设置物件在SLG操作中是否贴地
		if ( InputManager::getSingletonPtr()->isKeyPressed(KC_H) && InputManager::getSingletonPtr()->isCtrlOn() )
		{
			mTerrainSticked = !mTerrainSticked;
		}

		if ( mSelectUtilIndex == -1 &&
			InputManager::getSingletonPtr()->isKeyHolded(KC_LSHIFT) && 
			InputManager::getSingletonPtr()->isMousePressed(MB_Right) )
		{
			ObjectState state;
			state.name = mSceneObject->getName();
			state.type = mSceneObject->getType();
			mSceneObject->getSceneNode()->getPosition(state.pos);
			mSceneObject->getSceneNode()->getOrientation(state.qua);
			mSceneObject->getSceneNode()->getScale(state.scale);

			OperationRecord record;
			record.type = 2;
			record.state = state;

			mRedoOperations.clear();
			mUndoOperations.push_front(record);
		}

		//物件变大Shift+鼠标操作
		if ( mSelectUtilIndex == -1 &&
			InputManager::getSingletonPtr()->isKeyHolded(KC_LSHIFT) && 
			InputManager::getSingletonPtr()->isMouseHolded(MB_Right) )
		{
			ISceneNode* sceneNode = mSceneObject->getSceneNode();
			if ( sceneNode )
			{

				bool isScaleUp = true;
				Vec2 mouseDelta = InputManager::getSingletonPtr()->getMouseMoveDelta();
				Vector2 normalDelta( mouseDelta.x, mouseDelta.y );
				normalDelta.normalise();

				//以 y - x = 0，这条直线为界划分变大区域和变小的区域
				if ( normalDelta.y != 0.0f  ||  normalDelta.x != 0.0f )
				{
					Flt result = normalDelta.y - normalDelta.x;

					// 在直线上
					if ( result == 0.0f )
					{
						isScaleUp = ( normalDelta.y > 0.0f && normalDelta.x > 0.0f );
					}
					else
					{
						isScaleUp = ( result < 0.0f );
					}

					Flt mouseDis = mouseDelta.length() * mMoveSpeed * 10.0f;

					if ( !isScaleUp )
						mouseDis = -mouseDis;

					Vec3 scale;
					sceneNode->getScale(scale);

					scale.x += (mouseDis * scale.x);
					if ( scale.x < 0.0f )
						scale.x = 0.0f;

					scale.y += (mouseDis * scale.y);
					if ( scale.y < 0.0f )
						scale.y = 0.0f;

					scale.z += (mouseDis * scale.z);
					if ( scale.z < 0.0f )
						scale.z = 0.0f;

					sceneNode->setScale(scale);

					mObjectOperationDirty = true;
				}	
			}
		}
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::updateSLGOp()
	{
		if ( InputManager::getSingletonPtr()->isMouseReleased(MB_Right) )
		{
			mChangedDirty = true;
			mIsMouseRayTerrainIntersectionValid = false;
			mIsMovingSceneObject = false;
		}

		if  ( !InputManager::getSingletonPtr()->isKeyHolded(KC_LSHIFT) && 
			InputManager::getSingletonPtr()->isMousePressed(MB_Right) )
		{
			// 判断当前对象是否仍在鼠标射线之下
			Vec3 pos, dir;
			AxisAlignedBox aabb;
			mScene->getActiveCamera()->getMouseViewportRay( pos, dir );
			Ogre::Ray ray(Vector3(pos.x,pos.y,pos.z),Vector3(dir.x,dir.y,dir.z));
			
			if ( mSceneObject->getType() == SOT_ENTITY )
			{
				Entity* entity = dynamic_cast<Entity*>(mSceneObject);
				if ( entity && entity->getModelObject() &&
					entity->getModelObject()->getOgreEntity() )
				{
					aabb = entity->getModelObject()->getOgreEntity()->getWorldBoundingBox();
				}
			}
			else if ( mSceneObject->getType() == SOT_EFFECTENTITY )
			{
				EffectEntity* effect = dynamic_cast<EffectEntity*>(mSceneObject);
				if ( effect && effect->getSceneNode() &&
					effect->getSceneNode()->getOgreSceneNode() )
				{
					aabb = effect->getSceneNode()->getOgreSceneNode()->_getWorldAABB();
				}
			}
			else if ( mSceneObject->getType() == SOT_ENTITY_GROUP_UNIT )
			{
				EntityGroupInstance* groupInstance = dynamic_cast<EntityGroupInstance*>(mSceneObject);
				if ( groupInstance && groupInstance->getModelObject() &&
					groupInstance->getModelObject()->getOgreEntity() )
				{
					aabb = groupInstance->getModelObject()->getOgreEntity()->getWorldBoundingBox();
				}
			}
			else if ( mSceneObject->getType() == SOT_TREE )
			{
				Tree* tree = dynamic_cast<Tree*>(mSceneObject);
				if ( tree )
				{
					aabb = tree->getWorldBoundingBox();
				}
			}
			else if ( mSceneObject->getType() == SOT_GRASS )
			{
				Grass* grass = dynamic_cast<Grass*>(mSceneObject);
				if (grass)
				{
					aabb = grass->getWorldBoundingBox();
				}
			}
			//如果该物件仍然在鼠标物件之下， 那么就触发之后hold时候的移动操作
			if ( ray.intersects( aabb ).first )
			{
				ISceneNode* sceneNode = mSceneObject->getSceneNode();
				if ( !sceneNode )
					return;

				ObjectState state;
				state.name = mSceneObject->getName();
				state.type = mSceneObject->getType();
				mSceneObject->getSceneNode()->getPosition(state.pos);
				mSceneObject->getSceneNode()->getOrientation(state.qua);
				mSceneObject->getSceneNode()->getScale(state.scale);

				OperationRecord record;
				record.type = 2;
				record.state = state;

				mRedoOperations.clear();
				mUndoOperations.push_front(record);

				if ( isTerrainSticked() )
				{
					mIsMouseRayTerrainIntersectionValid = mScene->getTerrainManager()->getMouseRayIntersection(mMouseRayTerrainIntersection,true);
					mIsMovingSceneObject = mIsMouseRayTerrainIntersectionValid;
				}
				else
				{
					//查询一个平面上的交点
					Vec3 pos,dir;
					mScene->getActiveCamera()->getMouseViewportRay(pos,dir);

					//获得一个要查询的平面
					Vec3 node_pos;
					sceneNode->getPosition(node_pos);
					Vector3 planePos(node_pos.x, node_pos.y, node_pos.z);
					Vector3 planeNormal(0.0,1.0f,0.0);

					//射线查询基础平面
					Ogre::Ray ray(Vector3(pos.x,pos.y,pos.z),Vector3(dir.x,dir.y,dir.z));
					Plane plane( planeNormal, planePos );

					std::pair< bool, Real > intersect = ray.intersects(plane);
					if ( mIsMovingSceneObject = intersect.first )
					{
						// convert distance to vector
						mIsMouseRayTerrainIntersectionValid = mIsMovingSceneObject;

						Vector3 intersection = ray.getPoint( intersect.second );
						mMouseRayTerrainIntersection.x = intersection.x;
						mMouseRayTerrainIntersection.y = intersection.y;
						mMouseRayTerrainIntersection.z = intersection.z;
					}
				}
			}
		}
		else if ( InputManager::getSingletonPtr()->isKeyHolded(KC_LMENU) && 
			InputManager::getSingletonPtr()->isMouseHolded(MB_Right) )
		{
			ISceneNode* sceneNode = mSceneObject->getSceneNode();
			if ( sceneNode )
			{	
				Vec2 moveDelta = InputManager::getSingletonPtr()->getMouseMoveDelta();
				float delta = moveDelta.x * 2.0f * MG_PI;
				if (delta != 0.f)
				{
					sceneNode->yaw(delta, MG::ISceneNode::TS_WORLD);	
				}
				mObjectOperationDirty = true;
			}
		}
		// press LShift to control the height of scene object	
		else if ( InputManager::getSingletonPtr()->isKeyHolded(KC_LCONTROL) && 
			InputManager::getSingletonPtr()->isMouseHolded(MB_Right) )
		{
			ISceneNode* sceneNode = mSceneObject->getSceneNode();
			if ( sceneNode )
			{
				Vec2 moveDelta = InputManager::getSingletonPtr()->getMouseMoveDelta();
				sceneNode->translate(Vec3(0, -moveDelta.y * 100.0f, 0));

				mObjectOperationDirty = true;
			}
		}
		else if ( mIsMovingSceneObject && 
			InputManager::getSingletonPtr()->isMouseHolded(MB_Right) )
		{
			ISceneNode* sceneNode = mSceneObject->getSceneNode();
			if ( !sceneNode )
				return;

			Vec2 moveDelta = InputManager::getSingletonPtr()->getMouseMoveDelta();

			if ( isTerrainSticked() )
			{
				Vec3 terrain_insection;
				if ( mIsMouseRayTerrainIntersectionValid = mScene->getTerrainManager()->getMouseRayIntersection(terrain_insection,true) )
				{
					Vec3 dir = terrain_insection - mMouseRayTerrainIntersection;
					mMouseRayTerrainIntersection = terrain_insection;
					sceneNode->translate(dir,ISceneNode::TS_WORLD);
					sceneNode->stickTerrain();

					mObjectOperationDirty = true;
				}
			}
			else
			{
				Vec3 pos,dir;
				mScene->getActiveCamera()->getMouseViewportRay(pos,dir);

				//获得一个要查询的平面
				Vec3 node_pos;
				sceneNode->getPosition(node_pos);
				Vector3 planePos(node_pos.x, node_pos.y, node_pos.z);
				Vector3 planeNormal(0.0,1.0f,0.0);

				//射线查询基础平面
				Ogre::Ray ray(Vector3(pos.x,pos.y,pos.z),Vector3(dir.x,dir.y,dir.z));
				Plane plane( planeNormal, planePos );

				std::pair< bool, Real > intersect = ray.intersects(plane);
				if ( mIsMouseRayTerrainIntersectionValid = intersect.first )
				{
					// convert distance to vector
					Vector3 intersection = ray.getPoint( intersect.second );
					Vec3 vec_intersection;
					vec_intersection.x = intersection.x;
					vec_intersection.y = intersection.y;
					vec_intersection.z = intersection.z;

					Vec3 dir = vec_intersection - mMouseRayTerrainIntersection;
					mMouseRayTerrainIntersection = vec_intersection;
					sceneNode->translate(dir,ISceneNode::TS_WORLD);

					mObjectOperationDirty = true;
				}
			}
		}
	}
    //-----------------------------------------------------------------------
    void SceneObjectController::updateUtilObjectsOp()
    {
        if ( mSelectUtilIndex < 0 )
            return;

        if ( InputManager::getSingletonPtr()->isMouseReleased(MB_Left) || 
			InputManager::getSingletonPtr()->isMouseReleased(MB_Right) )
        {
            mChangedDirty = true;
        }

        if ( InputManager::getSingletonPtr()->isMousePressed(MB_Right) ||
            InputManager::getSingletonPtr()->isMouseHolded(MB_Right) )
        {
            Vec3 sceneObjPos;
            mSceneObject->getSceneNode()->getPosition(sceneObjPos);
            Qua sceneObjQua;
            mSceneObject->getSceneNode()->getOrientation(sceneObjQua);

            //@
            Vector3 sceneOgreObjPos(sceneObjPos.x,sceneObjPos.y,sceneObjPos.z);
            Quaternion sceneOgreObjQua(sceneObjQua.w, sceneObjQua.x, sceneObjQua.y, sceneObjQua.z);

            const Matrix4& view = mScene->getActiveCamera()->getOgreCamera()->getViewMatrix();
            const Matrix4& proj = mScene->getActiveCamera()->getOgreCamera()->getProjectionMatrix();
            Matrix4 viewproj  = proj * view;

            Vector3 objViewPos   = viewproj * sceneOgreObjPos;
            Vector2 obj2DViewPos = Vector2( objViewPos.x, objViewPos.y ) ;

            Vector3 camPos = mScene->getActiveCamera()->getOgreCamera()->getPosition();
            Real disScale = camPos.distance( sceneOgreObjPos );

            //注意了， 越靠屏幕上方鼠标Y值越小， 和3D世界中不一样的， y值要取负值
            Vec2 mouseDelta = InputManager::getSingletonPtr()->getMouseMoveDelta();
            Vector2 moveRel2DViewVec(mouseDelta.x, -mouseDelta.y);
            
            Vector3 axisPos;
            Vector3 axisViewPos;
            Vector2 axis2DViewPos;
            Vector2 axis2DViewVec;
            Real moveDis;
            Radian radian;
            if ( (mSelectUtilIndex == Axis_X) ||
                (mSelectUtilIndex == Axis_Y) ||
                (mSelectUtilIndex == Axis_Z) )
            {
                if ( mSelectUtilIndex == Axis_X )
                    axisPos = Vector3(1.0,0,0);
                else if ( mSelectUtilIndex == Axis_Y )
                    axisPos = Vector3(0.0,1.0,0);
                else if ( mSelectUtilIndex == Axis_Z )
                    axisPos = Vector3(0.0,0.0,1.0);

				// 首先计算出世界坐标
                axisPos = sceneOgreObjPos + sceneOgreObjQua * axisPos;

				// 把该坐标系投射到屏幕上， 和物体坐标做减法， 获取一个在屏幕上的2D向量
                axisViewPos   = viewproj * axisPos;
                axis2DViewPos = Vector2( axisViewPos.x, axisViewPos.y );
                axis2DViewVec = axis2DViewPos - obj2DViewPos;
                axis2DViewVec.normalise();

				// 获取一个移动量？
                moveDis = axis2DViewVec.dotProduct( moveRel2DViewVec );
                moveDis = moveDis * mMoveSpeed * 10.0f;

                radian = axis2DViewVec.crossProduct( moveRel2DViewVec );
                radian = radian * mYawRotateSpeed;
            }

            Vector3 moveVector;
            if ( (mSelectUtilIndex == Axis_XY) ||
                (mSelectUtilIndex == Axis_XZ) ||
                (mSelectUtilIndex == Axis_YZ) )
            {
                Ogre::Plane axisPlane;
                if ( mSelectUtilIndex == Axis_XY )
                {
                    axisPlane = Ogre::Plane(Ogre::Vector3::UNIT_Z, sceneOgreObjPos);
                }
                else if ( mSelectUtilIndex == Axis_XZ )
                {
                    axisPlane = Ogre::Plane(Ogre::Vector3::UNIT_Y, sceneOgreObjPos);
                }
                else if ( mSelectUtilIndex == Axis_YZ )
                {
                    axisPlane = Ogre::Plane(Ogre::Vector3::UNIT_X, sceneOgreObjPos);
                }

                Vec3 pos,dir;
                mScene->getActiveCamera()->getMouseViewportRay(pos,dir);
                Ogre::Ray ray(Vector3(pos.x,pos.y,pos.z),Vector3(dir.x,dir.y,dir.z));

                std::pair<bool, Real> intersectsResult;
                intersectsResult = ray.intersects( axisPlane );

                Vector3 currMouse3DWorldPos;
                if( intersectsResult.first ) {
                    currMouse3DWorldPos = ray.getPoint(intersectsResult.second);
                }else
                {
                    currMouse3DWorldPos = sceneOgreObjPos;
                }

                if ( InputManager::getSingletonPtr()->isMousePressed(MB_Left) )
                {
                    mLastMouse3DWorldPos = currMouse3DWorldPos;
                }
                moveVector = currMouse3DWorldPos - mLastMouse3DWorldPos;
                mLastMouse3DWorldPos = currMouse3DWorldPos;
            }


            ISceneNode* sceneNode = mSceneObject->getSceneNode();
            DYNAMIC_ASSERT(sceneNode!=NULL);

            switch (mSelectUtilIndex)
            {
            case Axis_X:
                if (mControlType == SOC_POSITION)
                {
					sceneNode->translate( Vec3( moveDis, 0, 0 ), ISceneNode::TS_LOCAL );

					mChangedDirty = true;
					mObjectOperationDirty = true;
                }
                else if (mControlType == SOC_SCALE)
                {
                    Vec3 scale;
                    sceneNode->getScale(scale);
                    sceneNode->setScale( Vec3( scale.x + moveDis, scale.y, scale.z ) );

					mChangedDirty = true;
					mObjectOperationDirty = true;
                }else
                {
                    Flt degree = radian.valueDegrees();
                    sceneNode->pitch( degree );

					mChangedDirty = true;
					mObjectOperationDirty = true;
                }
                break;
            case Axis_Y:
                if (mControlType == SOC_POSITION)
                {
                    sceneNode->translate( Vec3( 0, moveDis, 0 ), ISceneNode::TS_LOCAL );

					mChangedDirty = true;
					mObjectOperationDirty = true;
                }
                else if (mControlType == SOC_SCALE)
                {
                    Vec3 scale;
                    sceneNode->getScale(scale);
                    sceneNode->setScale( Vec3( scale.x, scale.y + moveDis, scale.z ) );

					mChangedDirty = true;
					mObjectOperationDirty = true;
                }else
                {
                    Flt degree = radian.valueDegrees();
                    sceneNode->yaw( degree );

					mChangedDirty = true;
					mObjectOperationDirty = true;
                }
                break;
            case Axis_Z:
                if (mControlType == SOC_POSITION)
                {
                    sceneNode->translate( Vec3( 0, 0, moveDis ), ISceneNode::TS_LOCAL );

					mChangedDirty = true;
					mObjectOperationDirty = true;
                }
                else if (mControlType == SOC_SCALE)
                {
                    Vec3 scale;
                    sceneNode->getScale(scale);
                    sceneNode->setScale( Vec3( scale.x, scale.y, scale.z -moveDis ) );

					mChangedDirty = true;
					mObjectOperationDirty = true;
                }else
                {
                    Flt degree = radian.valueDegrees();
                    sceneNode->roll( degree );

					mChangedDirty = true;
					mObjectOperationDirty = true;
                }
                break;
            //case Axis_XY:
            //    if (mControlType == SOC_POSITION)
            //        sceneNode->translate( Vec3( moveVector.x, moveVector.y, moveVector.z ) );
            //    break;
            //case Axis_XZ:
            //    if (mControlType == SOC_POSITION)
            //        sceneNode->translate( Vec3( moveVector.x, moveVector.y, moveVector.z ) );
            //    break;
            //case Axis_YZ:
            //    if (mControlType == SOC_POSITION)
            //        sceneNode->translate( Vec3( moveVector.x, moveVector.y, moveVector.z ) );
            //    break;
            }
        }
    }

    //-----------------------------------------------------------------------
    Bool SceneObjectController::updateSceneObjectRectFocus()
    {
		if ( !mScene )
			return false;

		if ( InputManager::getSingletonPtr()->isMousePressed(MB_Left) )
		{
			mRectPressedMousePos = InputManager::getSingleton().getMousePos();
			mRectPressedScreenPos = InputManager::getSingleton().getMouseScreenPos();

			isFocusRect = false;
		}
		else if ( InputManager::getSingletonPtr()->isMouseHolded(MB_Left) )
		{
			Vec2 pos = InputManager::getSingleton().getMousePos();

			if ( (mRectPressedMousePos - pos).length() > 2 )
			{
				isFocusRect = true;
			}
		}
		else if ( InputManager::getSingletonPtr()->isMouseReleased(MB_Left) )
		{
			if ( isFocusRect )
			{
				isFocusRect = false;

				//////////////////////////////////////////////////////////////////////////////

				//清空单选
				setFocus(NULL);

				//清空框选
				clearMultiFocus();

				//////////////////////////////////////////////////////////////////////////////

				//////////////////////////////////////////////////////////////////////////////

				//进行框选
				mRectHoldScreenPos = InputManager::getSingleton().getMouseScreenPos();

				RectF rect;
				rect.left           = mRectPressedScreenPos.x;
				rect.top            = mRectPressedScreenPos.y;
				rect.right          = mRectHoldScreenPos.x;
				rect.bottom         = mRectHoldScreenPos.y;

				multiSelect( rect );

				//////////////////////////////////////////////////////////////////////////////

				return true;
			}
		}

		//绘制绿色框选框
        if ( isFocusRect )
        {
            mRectHoldMousePos = InputManager::getSingleton().getMousePos();
			
            IScreenRectWireframeDecorator* decoratorShadow = mScene->getWireframeManager()->createScreenRectWireframeDecorator( "RectSelectShadow_ScreenRectWireframeDecorator" );
            IScreenRectWireframeDecorator* decorator = mScene->getWireframeManager()->createScreenRectWireframeDecorator( "RectSelect_ScreenRectWireframeDecorator" );

            RectF rect;
            rect.left           = mRectPressedMousePos.x;
            rect.top            = mRectPressedMousePos.y;
            rect.right          = mRectHoldMousePos.x;
            rect.bottom         = mRectHoldMousePos.y;

            RectF rectShadow;
            rectShadow.left     = mRectPressedMousePos.x + 1;
            rectShadow.top      = mRectPressedMousePos.y + 1;
            rectShadow.right    = mRectHoldMousePos.x + 1;
            rectShadow.bottom   = mRectHoldMousePos.y + 1;

            if ( decorator && decoratorShadow )
            {
                decorator->setRect( rect, true );
                decoratorShadow->setRect( rectShadow, true );
                decoratorShadow->setColour( Color(0.5,0.5,0.5,1) );
            }
        }

        return isFocusRect;
    }

	//-----------------------------------------------------------------------
	Bool SceneObjectController::updateSceneObjectFocus()
	{
		if ( InputManager::getSingletonPtr()->isMouseReleased(MB_Left) && InputManager::getSingletonPtr()->isCtrlOn() )
		{
			//反选
			ISceneObjectCollisionCallback callback;
			callback.isCheckQueryFlagsMask = false;
			callback.isCheckSingle = false;

			//忽略检测
			if ( mIgnoreObject )
				callback.ignoreList.push_back(mIgnoreObject);

			if ( mScene->getCollisionSystem()->checkMouseRayCollision( &callback ) )
			{
				ISceneObject* sceneObject = callback.collisionList[0].second;
				if ( !sceneObject )
					return false;

				Bool isFocus = false;

				if ( mSceneObject == sceneObject )
					isFocus = true;
				
				if ( !isFocus )
				{
					for ( U32 n = 0; n < mMultiSelectRes.size(); n++ )
					{
						if ( mMultiSelectRes[n] == sceneObject )
						{
							isFocus = true;
							break;
						}
					}
				}

				if ( isFocus )
					unSelect( sceneObject );
				else
					addToMultiSelect( sceneObject );

				return true;
			}
		}
		else if ( InputManager::getSingletonPtr()->isMouseReleased(MB_Left) )
		{
			//单选， 要去掉原来的多选或单选的结果
            ISceneObjectCollisionCallback callback;
            callback.isCheckQueryFlagsMask = false;
            callback.isCheckSingle = false;

			//忽略检测
			if ( mIgnoreObject )
				callback.ignoreList.push_back(mIgnoreObject);

			setFocus( NULL );

			clearMultiFocus();

            if ( mScene->getCollisionSystem()->checkMouseRayCollision( &callback ) )
            {
				mRayQueryRes.clear();
				
				for ( UInt i = 0; i < callback.collisionList.size(); i++  )
				{
					mRayQueryRes.push_back( callback.collisionList[i].second );
				}

                setFocus( mRayQueryRes[0] );				
					
                return true;
            }
		}
		else if ( InputManager::getSingletonPtr()->isKeyPressed(KC_UP) )
		{
			int count = mRayQueryRes.size();
			for ( int i = 0; i < count; i++ )
			{
				if ( mSceneObject == mRayQueryRes[i] )
				{
					setFocus( mRayQueryRes[( i - 1 + count ) % count] );
					break;
				}
			}
		}
		else if ( InputManager::getSingletonPtr()->isKeyPressed(KC_DOWN) )
		{
			int count = mRayQueryRes.size();
			for ( int i = 0; i < count; i++ )
			{
				if ( mSceneObject == mRayQueryRes[i] )
				{
					setFocus( mRayQueryRes[( i + 1 + count ) % count] );
					break;
				}
			}
		}
		
        return false;
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::setEnable(Bool enable)
	{
		mEnable = enable;
	}
	//-----------------------------------------------------------------------
	Bool SceneObjectController::getlEnable()
	{
		return mEnable;
	}	
	//-----------------------------------------------------------------------
	void SceneObjectController::setFocus( ISceneObject* obj )
	{
        if (obj && obj->getSceneNode() == NULL )
            return;

		setBoundingBoxVisible( false );

        mChangedDirty = true;

        mSceneObject = obj;

		setUtilObjectsVisible( mSceneObject != NULL );

		setBoundingBoxVisible( true );
	}

    //-----------------------------------------------------------------------
    void SceneObjectController::setBoundingBoxVisible( Bool isVisible )
    {
        if ( mSceneObject )
        {
			if (mSceneObject->getType() == SOT_TREE)
			{
				return;
			}
			if (mSceneObject->getType() == SOT_GRASS)
			{
				return;
			}
            MGSceneNode* sceneNode = dynamic_cast<MGSceneNode*>( mSceneObject->getSceneNode() );
            DYNAMIC_ASSERT(sceneNode!=NULL);
            Ogre::SceneNode* node = sceneNode->getOgreSceneNode();

            node->showBoundingBox( isVisible );
        }
    }

	//-----------------------------------------------------------------------
	ISceneObject* SceneObjectController::getFocus()
	{
        return mSceneObject;
	}

	//-----------------------------------------------------------------------
	void SceneObjectController::setIgnoreFocus( ISceneObject* obj )
	{
		mIgnoreObject = obj;
	}

	//-----------------------------------------------------------------------
	void SceneObjectController::clearMultiFocus( Bool isObjectDeleted )
	{
		if ( !isObjectDeleted )
		{
			for ( int i = 0; i < mMultiSelectRes.size(); i++ )
			{
				if ( mMultiSelectRes[i]->getSceneNode() )
				{
					Entity* entity = dynamic_cast<Entity*>(mMultiSelectRes[i]);
					if ( entity )
					{
						Ogre::SceneNode* node = entity->getSceneNode()->getOgreSceneNode();
						if ( node )
							node->showBoundingBox( false );
					}
				}
			}
		}
		
		mMultiSelectRes.clear();
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::getMultiFocusList( std::vector<ISceneObject*>& objectList )
	{
		objectList.clear();
		objectList = mMultiSelectRes;
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::addToMultiSelect( ISceneObject* object )
	{
		Entity* entity = dynamic_cast<Entity*>(object);
		if ( !entity )
			return;

		if ( mSceneObject )
		{
			if ( entity && entity->getSceneNode() )
			{
				mMultiSelectRes.push_back( entity );

				if ( entity->getSceneNode()->getOgreSceneNode() )
				{
					entity->getSceneNode()->getOgreSceneNode()->showBoundingBox(true);
				}
			}
		}
		else 
		{
			clearMultiFocus();
			setFocus( entity );	
		}
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::unSelect( ISceneObject* object )
	{
		if ( !object )
			return;

		if ( object == mSceneObject )
		{
			setFocus(NULL);

			//假设这个焦点物件是通过多选获得的， 那么要从原来多选的物件列表中再选择一个最大物件
			if ( mMultiSelectRes.size() > 0 )
			{
				//选择一个最大的物件作为单选物件
				U32 max_index = 0;
				Flt max_volume = 0.0f;

				for ( U32 i = 0; i < mMultiSelectRes.size(); i++ )
				{
					Entity* entity = dynamic_cast<Entity*>(mMultiSelectRes[i]);

					if ( entity && 
						entity->getModelObject() )
					{
						Vec3 boundingSize = entity->getModelObject()->getBoundingBoxSize();
						Flt  boundingVolume = boundingSize.x * boundingSize.y * boundingSize.z;

						if ( boundingVolume >= max_volume )
						{
							max_index = i;
							max_volume = boundingVolume;
						}
					}
				}

				if ( max_index < mMultiSelectRes.size())
				{
					mSceneObject = mMultiSelectRes[max_index];

					//把单选的物体从框选列表中删除
					std::vector<ISceneObject*>::iterator iter = mMultiSelectRes.begin();
					std::advance(iter, max_index);
					mMultiSelectRes.erase( iter );

					setUtilObjectsVisible( mSceneObject != NULL );

					mChangedDirty = true;
				}
			}
		}
		else
		{
			for ( U32 i = 0; i < mMultiSelectRes.size(); i++ )
			{
				if ( mMultiSelectRes[i] == object )
				{
					Entity* entity = dynamic_cast<Entity*>(object);
					if ( entity )
					{
						Ogre::SceneNode* node = entity->getSceneNode()->getOgreSceneNode();
						if ( node )
							node->showBoundingBox( false );
					}

					std::vector<ISceneObject*>::iterator iter = mMultiSelectRes.begin();
					std::advance(iter,  i);
					mMultiSelectRes.erase( iter );

					return;
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::multiSelect( RectF rectF )
	{
		//将所有物件放入框选列表
		for ( std::map<String, Entity*>::iterator iter = mScene->mEntitys.begin(); 
			iter != mScene->mEntitys.end(); iter++ )
		{
			Entity* entity = iter->second;

			if ( entity && entity != mIgnoreObject && entity->getSceneNode() )
			{
				Vec2 screenPos;
				entity->getSceneNode()->getScreenPosition(screenPos);
				
				if ( rectF.inRect(screenPos) )
				{
					mMultiSelectRes.push_back( entity );

					if ( entity->getSceneNode()->getOgreSceneNode() )
					{
						entity->getSceneNode()->getOgreSceneNode()->showBoundingBox(true);
					}
				}
			}
		}

		
		TreeManager* pTreeMgr = mScene->getTreeManager();
		if (pTreeMgr != NULL)
		{
			//tree
			const std::map<String, Tree*>& treeMap = pTreeMgr->getAllTrees();
			for (std::map<String, Tree*>::const_iterator it = treeMap.begin(); it != treeMap.end(); ++it)
			{
				Tree* tree = it->second;

				if (tree && tree != mIgnoreObject && tree->getSceneNode())
				{
					Vec2 screenPos;
					tree->getSceneNode()->getScreenPosition(screenPos);

					if ( rectF.inRect(screenPos) )
					{
						mMultiSelectRes.push_back( tree );
/*
						if ( tree->getSceneNode()->getOgreSceneNode() )
						{
							tree->getSceneNode()->getOgreSceneNode()->showBoundingBox(true);
						}*/
					}
				}
			}

			//grass
			const std::map<String, Grass*>& grassMap = pTreeMgr->getAllGrasses();
			for (std::map<String, Grass*>::const_iterator it = grassMap.begin(); it != grassMap.end(); ++it)
			{
				Grass* grass = it->second;
				if (grass && grass != mIgnoreObject && grass->getSceneNode())
				{
					Vec2 screenPos;
					grass->getSceneNode()->getScreenPosition(screenPos);

					if ( rectF.inRect(screenPos) )
					{
						mMultiSelectRes.push_back( grass );
/*
						if ( tree->getSceneNode()->getOgreSceneNode() )
						{
							tree->getSceneNode()->getOgreSceneNode()->showBoundingBox(true);
						}*/
					}
				}
			}
		}
		
		

		//选择一个最大的物件作为单选物件
		U32 max_index = 0;
		Flt max_volume = 0.0f;

		for ( U32 i = 0; i < mMultiSelectRes.size(); i++ )
		{
			Entity* entity = dynamic_cast<Entity*>(mMultiSelectRes[i]);
			Tree* tree = NULL;
			Grass* grass = NULL;
			
			if (entity == NULL)
			{
				tree = dynamic_cast<Tree*>(mMultiSelectRes[i]);
				if (tree == NULL)
				{
					grass = dynamic_cast<Grass*>(mMultiSelectRes[i]);
					if (grass == NULL)
					{
						assert(0);
					}
				}
/*
				else
				{
					assert(0);
				}*/
			}
			if ( entity && 
				entity->getModelObject() )
			{
				Vec3 boundingSize = entity->getModelObject()->getBoundingBoxSize();
				Flt  boundingVolume = boundingSize.x * boundingSize.y * boundingSize.z;

				if ( boundingVolume >= max_volume )
				{
					max_index = i;
					max_volume = boundingVolume;
				}
			}
			else if ( tree != NULL)
			{

			}
			else if (grass != NULL)
			{

			}
		}

		if ( max_index < mMultiSelectRes.size())
		{
			mSceneObject = mMultiSelectRes[max_index];

			//把单选的物体从框选列表中删除
			std::vector<ISceneObject*>::iterator iter = mMultiSelectRes.begin();
			std::advance(iter, max_index);
			mMultiSelectRes.erase( iter );

			setUtilObjectsVisible( mSceneObject != NULL );

			mChangedDirty = true;
		}
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::createUtilObjects()
	{
		for(Int i = 0; i < AxisUtilCount; ++i)
		{
			mAxisUtilObjects[i] = MG_NEW Entity(AxisUtilObjectsName[i].c_str(), "", AxisUtilObjectsMeshName[i].c_str(), mScene); 
			mAxisUtilObjects[i]->getSceneNode()->setVisible(false);

            mAxisUtilObjects[i]->getModelObject()->getOgreEntity()->setQueryFlags(0);
			mAxisUtilObjects[i]->getModelObject()->getOgreEntity()->setRenderQueueGroup( Ogre::RENDER_QUEUE_OVERLAY - 1 );
			mAxisUtilObjects[i]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setDepthCheckEnabled(false);
            mAxisUtilObjects[i]->getModelObject()->getOgreEntity()->setCastShadows( false );
		}

		if ( mAxisUtilObjects[Axis_X] )
		{
			Vec3 boxSize = Vec3( 1.0f, 1.0f, 1.0f );
			IModelObject* object = mAxisUtilObjects[Axis_X]->getModelObject();
			if ( object )
				boxSize = object->getBoundingBoxSize();

			mUtilAxisLength = boxSize.x;
			if ( boxSize.y > mUtilAxisLength )
				mUtilAxisLength = boxSize.y;
			if ( boxSize.z > mUtilAxisLength )
				mUtilAxisLength = boxSize.z;
		}

		if ( mAxisUtilObjects[Axis_XY] )
		{
			Vec3 boxSize = Vec3( 1.0f, 1.0f, 1.0f );
			IModelObject* object = mAxisUtilObjects[Axis_XY]->getModelObject();
			if ( object )
				boxSize = object->getBoundingBoxSize();

			mUtilPlaneSize = boxSize.x;
			if ( boxSize.y > mUtilPlaneSize )
				mUtilPlaneSize = boxSize.y;
			if ( boxSize.z > mUtilPlaneSize )
				mUtilPlaneSize = boxSize.z;
		}

		restoreAllUtilObjectsMaterial();
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::destroyUtilObjects()
	{
		//

		for(Int i = 0; i < AxisUtilCount; ++i)
		{
			MG_SAFE_DELETE( mAxisUtilObjects[i] );
		}
	}
    //-----------------------------------------------------------------------
    void SceneObjectController::postFindVisibleObjects(Ogre::SceneManager* source, 
        Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v)
    {
        if ( mSceneObject )
        {
			RenderQueue *queue = source->getRenderQueue();
			if ( mSceneObject->getType() != SOT_TREE && mSceneObject->getType() != SOT_GRASS)
			{
				MGSceneNode* sceneNode = dynamic_cast<MGSceneNode*>( mSceneObject->getSceneNode() );
				DYNAMIC_ASSERT(sceneNode!=NULL);
				Ogre::SceneNode* node = sceneNode->getOgreSceneNode();
				node->_addBoundingBoxToQueue( queue );
			}else
			{
				if (mTreeBoundingBoxRenderNode == NULL)
				{
					if (source->hasSceneNode("TreeBoundingBox"))
						mTreeBoundingBoxRenderNode = source->getSceneNode("TreeBoundingBox");
					else
						mTreeBoundingBoxRenderNode = source->createSceneNode("TreeBoundingBox");
				}
				//mTreeBoundingBoxRenderNode->_addBoundingBoxToQueue()
				//mTreeBoundingBoxRenderNode->setPosition();
				mTreeBoundingBoxRenderNode->_addBoundingBoxToQueue( queue );

			}

        }
    }
    //-----------------------------------------------------------------------
    void SceneObjectController::updateUtilObjectsLocation()
    {
        if ( mSceneObject )
        {	
            Vec3 sceneObjectPos;
            mSceneObject->getSceneNode()->getPosition(sceneObjectPos);
            Vector3 endPos(sceneObjectPos.x,sceneObjectPos.y,sceneObjectPos.z);

            Vector3 dir = endPos;
            dir.normalise();

            Vector3 utilOgrePos = endPos;
            Vec3 utilPos = Vec3(utilOgrePos.x,utilOgrePos.y,utilOgrePos.z);
            Qua utilsQua;
            mSceneObject->getSceneNode()->getOrientation(utilsQua);

            for(Int i = 0; i < AxisUtilCount; ++i)
            {
                mAxisUtilObjects[i]->getSceneNode()->setOrientation( utilsQua );
                mAxisUtilObjects[i]->getSceneNode()->setPosition( utilPos );
            }
        }
    }
	//-----------------------------------------------------------------------
	void SceneObjectController::updateUtilObjectsScale()
	{
		if ( mSceneObject && mSceneObject->getSceneNode() )
		{
			ISceneNode* sceneNode = mSceneObject->getSceneNode();

			/*
			Vec3 obj_scale(3.0f,3.0f,3.0f);
			sceneNode->getScale(obj_scale);	
			obj_scale *= mUtilAxisBaseScale;

			mAxisUtilObjects[Axis_X]->getSceneNode()->setScale(Vec3(obj_scale.x, obj_scale.x, obj_scale.x));
			mAxisUtilObjects[Axis_Y]->getSceneNode()->setScale(Vec3(obj_scale.y, obj_scale.y, obj_scale.y));
			mAxisUtilObjects[Axis_Z]->getSceneNode()->setScale(Vec3(obj_scale.z, obj_scale.z, obj_scale.z));

			std::wstring text, textX, textY, textZ;
			MG::MGStrOp::toString(obj_scale.x, textX);
			MG::MGStrOp::toString(obj_scale.y, textY);
			MG::MGStrOp::toString(obj_scale.z, textZ);

			text = textX + L":" + textY + L":" + textZ;
			text += L"			ewrqerqwer:\n";
			
			OutputDebugStringW(text.c_str());

			mAxisUtilObjects[Axis_XY]->getSceneNode()->setScale(Vec3(obj_scale.x, obj_scale.y, 1.0f));
			mAxisUtilObjects[Axis_XZ]->getSceneNode()->setScale(Vec3(obj_scale.x, 1.0f, obj_scale.z));
			mAxisUtilObjects[Axis_YZ]->getSceneNode()->setScale(Vec3(1.0f, obj_scale.y, obj_scale.z));
			*/

			Flt scale(1.0);

			//根据相机与物体距离缩放坐标轴 [Costa 2012-08-10]
			if ( mScene )
			{
				ICamera* camera = mScene->getActiveCamera();
				if ( camera )
				{
					Vec3 nodePos,camPos,dir,boxSize(1.0f,1.0f,1.0f);
					sceneNode->getPosition(nodePos);
					camera->getPosition(camPos);
					dir = nodePos - camPos;
					Flt distance = dir.length();

					IModelObject* modelAxis_X = dynamic_cast<IEntity*>(mAxisUtilObjects[Axis_X])->getModelObject();
					if ( modelAxis_X )
						boxSize = modelAxis_X->getBoundingBoxSize();

					Flt length = max(boxSize.x,boxSize.y) ? max(boxSize.x,boxSize.z) : max(boxSize.y,boxSize.z);

					scale *= distance/(10*length); //设坐标轴的长度为镜头到物体距离的10分之一
				}
			}

			Vec3 scaleVec(scale,scale,scale);
			mAxisUtilObjects[Axis_X]->getSceneNode()->setScale(scaleVec);
			mAxisUtilObjects[Axis_Y]->getSceneNode()->setScale(scaleVec);
			mAxisUtilObjects[Axis_Z]->getSceneNode()->setScale(scaleVec);

			mAxisUtilObjects[Axis_XY]->getSceneNode()->setScale(Vec3(scale, scale, 1.0f));
			mAxisUtilObjects[Axis_XZ]->getSceneNode()->setScale(Vec3(scale, 1.0f, scale));
			mAxisUtilObjects[Axis_YZ]->getSceneNode()->setScale(Vec3(1.0f, scale, scale));
		}
	}
    //-----------------------------------------------------------------------
    void SceneObjectController::setControlType( ControlType type )
    {
        mControlType = type;
    }
    //-----------------------------------------------------------------------
    void SceneObjectController::stickTerrain()
    {
        if ( mSceneObject )
        {
            Vec3 pos;
            mSceneObject->getSceneNode()->getPosition( pos );

            Vec3 intersectPos;
            if ( mScene->getTerrainManager()->getRayIntersection( Vec3(pos.x, TerrainManager::MaxHeight, pos.z), Vec3(0,-1,0), intersectPos ) )
            {
                mSceneObject->getSceneNode()->setPosition( intersectPos );
                mChangedDirty = true;
            }

			for ( int n = 0; n < mMultiSelectRes.size(); n++ )
			{
				ISceneObject* sceneObject = mMultiSelectRes[n];
				if ( sceneObject )
				{
					Vec3 pos;
					sceneObject->getSceneNode()->getPosition( pos );

					Vec3 intersectPos;
					if ( mScene->getTerrainManager()->getRayIntersection( Vec3(pos.x, TerrainManager::MaxHeight, pos.z), Vec3(0,-1,0), intersectPos ) )
					{
						sceneObject->getSceneNode()->setPosition( intersectPos );
					}
				}
			}
        }
    }
    //-----------------------------------------------------------------------
    void SceneObjectController::setUtilObjectsVisible( Bool visible )
    {
        for(Int i = 0; i < AxisUtilCount; ++i)
        {
            mAxisUtilObjects[i]->getSceneNode()->setVisible( visible );
        }
		
		if ( visible )
			reinitAllUtilObjectsScale();
    }
    //-----------------------------------------------------------------------
    Bool SceneObjectController::isUtilObject( ISceneObject* obj )
    {
        
        return false;
    }
    //-----------------------------------------------------------------------
	void SceneObjectController::reinitAllUtilObjectsScale()
	{
		if ( mSceneObject && mSceneObject->getSceneNode() )
		{
			IEntity* entity = dynamic_cast<IEntity*>(mSceneObject);

			if ( !entity )
				return;

			ISceneNode* sceneNode = mSceneObject->getSceneNode();

			if ( !sceneNode )
				return;

			Vec3 obj_scale;
			sceneNode->getScale(obj_scale);

			Vec3 boxSize = Vec3(1.0f,1.0f,1.0f);
			IModelObject* modelObject = entity->getModelObject();
			if ( modelObject )
				boxSize = modelObject->getBoundingBoxSize();

			//将size恢复成scale之前的原始大小，计算最短axis长度用
			Flt max_length = boxSize.x;
			Flt base_axis_scale = 1.0f;

			if ( boxSize.y > mUtilAxisLength )
				max_length = boxSize.y;
			if ( boxSize.z > mUtilAxisLength )
				max_length = boxSize.z;

			//如果选中的包围盒， 包围盒的最大边长超过1，则四舍五入。不超过1， 则选择长度1.0f
			if ( max_length < 1.0f )
				max_length = 1.0f;

			mUtilAxisBaseScale = max_length / mUtilAxisLength;
			obj_scale *= mUtilAxisBaseScale;

			{

				/*std::wstring text, textX, textY, textZ;
				MG::MGStrOp::toString(obj_scale.x, textX);
				MG::MGStrOp::toString(obj_scale.y, textY);
				MG::MGStrOp::toString(obj_scale.z, textZ);

				text = textX + L":" + textY + L":" + textZ;
				text += L":\n";

				OutputDebugStringW(text.c_str());*/

				mAxisUtilObjects[Axis_X]->getSceneNode()->setScale(Vec3(obj_scale.x, obj_scale.x, obj_scale.x));
				mAxisUtilObjects[Axis_Y]->getSceneNode()->setScale(Vec3(obj_scale.y, obj_scale.y, obj_scale.y));
				mAxisUtilObjects[Axis_Z]->getSceneNode()->setScale(Vec3(obj_scale.z, obj_scale.z, obj_scale.z));

				/*mAxisUtilObjects[Axis_XY]->getSceneNode()->setScale(Vec3(obj_scale.x, obj_scale.y, 1.0f));
				mAxisUtilObjects[Axis_XZ]->getSceneNode()->setScale(Vec3(obj_scale.x, 1.0f,	obj_scale.z));
				mAxisUtilObjects[Axis_YZ]->getSceneNode()->setScale(Vec3(1.0f, obj_scale.y, obj_scale.z));*/
			}
		}
	}
	//-----------------------------------------------------------------------
    void SceneObjectController::setFocusedUtilObjectMaterial( Int index )
    {
        restoreAllUtilObjectsMaterial();

        mAxisUtilObjects[index]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->setReceiveShadows( false );

        if ((index==Axis_X)||(index==Axis_Y)||(index==Axis_Z))
        {
            mAxisUtilObjects[index]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setAmbient(1.0,1.0,0.0);
            mAxisUtilObjects[index]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setDiffuse(1.0,1.0,0.0,1.0);
            mAxisUtilObjects[index]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setSelfIllumination(1.0,1.0,0.0);
        }else
        {
            mAxisUtilObjects[index]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setColourWriteEnabled(true);
        }
    }
    //-----------------------------------------------------------------------
    void SceneObjectController::restoreAllUtilObjectsMaterial()
    {
        mAxisUtilObjects[Axis_X]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setAmbient(Ogre::ColourValue::Red);
        mAxisUtilObjects[Axis_X]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setDiffuse(Ogre::ColourValue::Red);
        mAxisUtilObjects[Axis_X]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setSelfIllumination(Ogre::ColourValue::Red);
        mAxisUtilObjects[Axis_X]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->setReceiveShadows(false);

        mAxisUtilObjects[Axis_Y]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setAmbient(Ogre::ColourValue::Green);
        mAxisUtilObjects[Axis_Y]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setDiffuse(Ogre::ColourValue::Green);
        mAxisUtilObjects[Axis_Y]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setSelfIllumination(Ogre::ColourValue::Green);
        mAxisUtilObjects[Axis_Y]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->setReceiveShadows(false);

        mAxisUtilObjects[Axis_Z]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setAmbient(Ogre::ColourValue::Blue);
        mAxisUtilObjects[Axis_Z]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setDiffuse(Ogre::ColourValue::Blue);
        mAxisUtilObjects[Axis_Z]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setSelfIllumination(Ogre::ColourValue::Blue);
        mAxisUtilObjects[Axis_Z]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->setReceiveShadows(false);

        mAxisUtilObjects[Axis_XY]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setColourWriteEnabled(false);
        mAxisUtilObjects[Axis_XZ]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setColourWriteEnabled(false);
        mAxisUtilObjects[Axis_YZ]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->getBestTechnique()->getPass(0)->setColourWriteEnabled(false);

        mAxisUtilObjects[Axis_XY]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->setReceiveShadows(false);
        mAxisUtilObjects[Axis_XZ]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->setReceiveShadows(false);
        mAxisUtilObjects[Axis_YZ]->getModelObject()->getOgreEntity()->getSubEntity(0)->getMaterial()->setReceiveShadows(false);
    }
	//-----------------------------------------------------------------------
	void SceneObjectController::onRemove( ISceneNode* node )
	{
		if ( mSceneObject && mSceneObject->getSceneNode() == node )
		{
			mSceneObject = NULL;
		}
	}
	//-----------------------------------------------------------------------
	void SceneObjectController::setFocusEnable( Bool enable )
	{
		mFocusEnable = enable;

		if ( !enable )
		{
			setFocus(NULL);
			clearMultiFocus();

			isFocusRect = false;
		}
	}
	//-----------------------------------------------------------------------

}