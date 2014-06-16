/******************************************************************************/
#include "StdAfx.h"
#include "CoreManager.h"
#include "GlobalOptions.h"
#include "OperationManager.h"
#include "IEditorSystem.h"
#include "IEditorOperation.h"
#include "IActionManager.h"
#include "GameFileDefine.h"
#include "ISceneDebuger.h"
#include "IScene.h"
//#include "Tree.h"
/******************************************************************************/


namespace SceneEditor {

    //-----------------------------------------------------------------------
    OperationManager::OperationManager()
        :mOpType(OT_NULL)
        ,mCameraSpeed(1000.0f)
        ,mViewportLock(true)
		,mIsMouseStateCheck(false)
		,mTimeMouseHold(0)
		,mOpInterval(0.05f)
        ,mSampleSceneObj(NULL)
		,mTreeType(TYPE_TREE)
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
        updateCameraOp( delta );
        updateEditorOp( delta );
    }

    //-----------------------------------------------------------------------
    void OperationManager::switchViewportLock()
    {
        mViewportLock = !mViewportLock;

        if ( mViewportLock )
        {
            revertCamera();
        }
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
				FormSet::main_form->onEventCamspeedChanged( U32(mCameraSpeed / 10.0f) );
            }else
            if ( input->isKeyPressed(KC_EQUALS) )
            {
                mCameraSpeed += 100.0f;
				if ( mCameraSpeed > 2000.0f )
                    mCameraSpeed = 2000.0f;
				FormSet::main_form->onEventCamspeedChanged( U32(mCameraSpeed / 10.0f) );
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

		Flt d = (Flt)delta * mCameraSpeed;

		//鼠标右键控制位置
		if ( input->isMousePressed(MB_Right) || input->isMouseHolded(MB_Right) )
		{
			Vec3 currMouseTerrainIntersection;
			if ( terrain->getMouseRayIntersection(currMouseTerrainIntersection) )
			{
				if ( input->isMousePressed(MB_Right) )
				{
					mLastMouseTerrainIntersection = currMouseTerrainIntersection;
				}else
				{
					Vec3 moveDis;
					moveDis = mLastMouseTerrainIntersection - currMouseTerrainIntersection ;

					Vec3 pos;
					camera->getPosition(pos);
					Vec2 rel = input->getMouseMoveDelta();

					if ( abs(rel.x) > 0.00 )
					{
						pos.x += (Flt)( moveDis.x );
					}
					if ( abs(rel.y) > 0.00 )
					{
						pos.z += (Flt)( moveDis.z );
					}

					camera->setPosition(pos);

					terrain->getMouseRayIntersection(mLastMouseTerrainIntersection);

					camera->getSceneNode()->getLinedStateManager()->clear();
				}
			}
		}

		//控制角度
		{
			Flt pitchV = 0;
			if ( input->isKeyHolded(KC_HOME) )
			{
				pitchV = 1;
			}
			else
				if ( input->isKeyHolded(KC_END) )
				{
					pitchV = -1;
				}

				if (pitchV!=0)
				{
					Flt cPitch = camera->getPitch();
					pitchV = cPitch + pitchV * delta;

					if (pitchV>mMaxPitch)
					{
						pitchV = mMaxPitch;
					}
					else
						if (pitchV<mMinPitch)
						{
							pitchV = mMinPitch;
						}

						camera->setOrientation(Qua(1,0,0,0));
						camera->pitch( pitchV );

						///////////////////////////////////////////////
				}
		}

		//通过滚轮改变摄像机离地面距离
		Int	wheelRel = 0;
		if ( input->isMouseHolded(MB_Left) == false )
			wheelRel = input->getMouseWheel();

		if(wheelRel != 0)
		{
			mRaiseOrLowHeight = wheelRel < 0;
			Flt camSpeed    = 200;
			Vec3 currCamPos;
			camera->getPosition(currCamPos);

			IEngineUtil* engineUtil = CoreManager::getInstance().getEngineMain()->engineUtil();

			Vec3 camDir;
			camera->getSceneNode()->getDirection(camDir);

			Vec3 camPos;
			camera->getSceneNode()->getPosition(camPos);
			Vec3 terrainIntersection = Vec3(camPos.x,0,camPos.y);
			terrain->getRayIntersection(camPos,camDir,terrainIntersection);

			Vec3 moveDir = camPos - terrainIntersection;
			Flt moveLen = moveDir.length();
			moveDir = MGMath::normaliseVector(moveDir);

			//得到目标高度
			Flt desHeight   = 20;
			UInt setCount = mCameraHeightSet.size();
			if ( setCount > 0 )
			{
				if (mRaiseOrLowHeight)
				{
					desHeight = mCameraHeightSet[setCount-1];
					for (UInt i=0;i<setCount;i++)
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

				action->setMoveSpeed( camSpeed );
				Vec3 movePos = terrainIntersection + moveDir*desHeight;
				action->setMoveToDestination( movePos );

				camera->getSceneNode()->getLinedStateManager()->push( action );
			}
		}

		//if ( input->isAltOn() )
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
				Flt  scale = 0.0005f;
				Vec3 camera_pos;
				camera->getPosition(camera_pos);

				scale *= camera_pos.y;

				vec_trans.x *= scale;
				vec_trans.y *= scale;
				vec_trans.z *= scale;

				camera_pos = camera_pos + vec_trans;

				camera->setPosition(camera_pos);

				camera->getSceneNode()->getLinedStateManager()->clear();
			}
		}
    }

    //-----------------------------------------------------------------------
    void OperationManager::prepareCreateObject( Int objectDeclID )
    {
        if ( mOpType == OT_CREATE_ENTITY )
        {
            mCurrModelDeclID = objectDeclID;
        }
		else if ( mOpType == OT_CREATE_TREE )
        {
            mCurrTreeDeclID = objectDeclID;
        }
		else if ( mOpType == OT_CREATE_EFFECTENTITY )
		{
			mCurrEffectDeclID = objectDeclID;
		}

		//让原本在编辑视图选中的物件先失去焦点
		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene )
		{
			ISceneObjectController* sceneObjCtrl = scene->getSceneObjectController();
			if ( sceneObjCtrl )
			{
				sceneObjCtrl->setFocus(NULL);
				sceneObjCtrl->setIgnoreFocus(NULL);
			}

			destroyCursorElement();
			createCursorElement(objectDeclID);

			if ( mSampleSceneObj )
				sceneObjCtrl->setIgnoreFocus(mSampleSceneObj);
		}
    }

	//-----------------------------------------------------------------------
	void OperationManager::createSampleObject( Int objectDeclID )
	{
        destroySampleObject();

		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene )
		{
            if ( mOpType == OT_CREATE_ENTITY )
            {
                mSampleSceneObj = scene->createEntity( "SampleEntity", objectDeclID );
				mSampleSceneObj->setQueryFlags(0);
            }
			else if ( mOpType == OT_CREATE_TREE )
            {
				if (mTreeType == 0)
				{
					mSampleSceneObj = scene->getTreeManager()->createTree( "SampleEntity", objectDeclID, Vec3(0,0,0));
					mSampleSceneObj->setQueryFlags(0);
				}
				else if (mTreeType == 1)
				{
					mSampleSceneObj = scene->getTreeManager()->createGrass( "SampleEntity", objectDeclID, Vec3(0,0,0));
					mSampleSceneObj->setQueryFlags(0);
				}
            }
			else if ( mOpType == OT_CREATE_EFFECTENTITY )
			{
				mSampleSceneObj = scene->createEffectEntity( "SampleEntity", objectDeclID, false );
				mSampleSceneObj->setQueryFlags(0);
			}
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::updateSampleObject()
	{
		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene && scene->getTerrainManager() )
		{
			ITerrainManager* terrain = scene->getTerrainManager();

			Vec3 entity_pos;
			terrain->getMouseRayIntersection( entity_pos, false );
			
			if ( mSampleSceneObj )
			{
				ISceneNode* sceneNode = mSampleSceneObj->getSceneNode();
				if ( sceneNode )
					sceneNode->setPosition(entity_pos);
			}
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::destroySampleObject()
	{
        if ( mSampleSceneObj == NULL )
            return;

		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene )
		{
			ISceneObject* object = scene->getSceneObjectController()->getFocus();
			if ( object )
			{
				if ( object->getName().compare( "SampleEntity" ) == 0 )
					 scene->getSceneObjectController()->setFocus(NULL);
			}

			scene->destroySceneObject( mSampleSceneObj->getName().c_str(), mSampleSceneObj->getType() );
		}

		mSampleSceneObj = NULL;
	}

    //-----------------------------------------------------------------------
    void OperationManager::setActiveEditorOp(OperationType type)
    {
        ////////////////////////////////////////////////////////

        mOpType = type;

        ////////////////////////////////////////////////////////

        IEditorSystem* editorSys    = CoreManager::getInstance().getEngineMain()->editorSystem();
        if ( editorSys == NULL )
            return;

        ////////////////////////////////////////////////////////

        switch (mOpType)
        {
            case OT_TERRAIN_BATCH_ADD:
            case OT_TERRAIN_BATCH_REMOVE:
            case OT_TERRAIN_BATCH_DEFINE:

            case OT_TERRAIN_REGION_ADD:
            case OT_TERRAIN_REGION_REMOVE:

            case OT_TERRAIN_HEIGHT_LEVEL:
            case OT_TERRAIN_HEIGHT_UNIFORM:
            case OT_TERRAIN_HEIGHT_FLAT:
            case OT_TERRAIN_HEIGHT_NOISE:

            case OT_TERRAIN_TEXTURE_ADD:
            case OT_TERRAIN_TEXTURE_REMOVE:
            case OT_TERRAIN_TEXTURE_UNIFORM:
            case OT_TERRAIN_TEXTURE_MOP:
            case OT_TERRAIN_TEXTURE_BLUR:

            case OT_TERRAIN_WATER_HEIGHT_LEVEL:
            case OT_TERRAIN_WATER_HEIGHT_UNIFORM:
            case OT_TERRAIN_WATER_HEIGHT_FLAT:
            case OT_TERRAIN_WATER_SHOW:
            case OT_TERRAIN_WATER_HIDE:
				{
					editorSys->getBrushSystem()->setFacadeVisible( true );

					//选择到地形页面就取消物件选中
					IScene* scene       = CoreManager::getInstance().getScene();
					if ( scene )
					{
						ISceneObjectController* objCtrl = scene->getSceneObjectController();
						if ( objCtrl )
						{
							objCtrl->setFocus(NULL);
						}
					}
				}
                break;
            default:
                editorSys->getBrushSystem()->setFacadeVisible( false );
        }

        ////////////////////////////////////////////////////////
    }

    //-----------------------------------------------------------------------
    void OperationManager::execCreateOrCopyModel()
    {
        Vec3 pos;
        Int declID = mCurrModelDeclID;
        if ( CoreManager::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true) )
        {
            IScene* scene = CoreManager::getInstance().getScene();
            if ( !scene )
                return;

            // 复制的对象
            ISceneObject* copyObj = NULL;
            // 创建的对象
            ISceneObject* newObj = NULL;


            ISceneObjectController* sceneObjCtrl =  scene->getSceneObjectController();
            if ( sceneObjCtrl )
            {
                copyObj = sceneObjCtrl->getFocus();
            }


            // 复制
            if ( copyObj )
            {
                if ( copyObj->getType() == SOT_ENTITY )
                {
                    IEntity* srcEntity = dynamic_cast<IEntity*>( copyObj );

                    if ( srcEntity && srcEntity->getModelObject() )
                    {
                        newObj = execCreateOrCopyEntity( pos, srcEntity, srcEntity->getModelObject()->getModelDeclarationID() );
                    }
				}
				else if ( copyObj->getType() == SOT_TREE )
                {
                    ITree* srcEntity = dynamic_cast<ITree*>( copyObj );

					if ( srcEntity )
					{
						newObj = execCreateOrCopyTree( pos, srcEntity, srcEntity->getBaseTreeId());
					}
                }
				else if ( copyObj->getType() == SOT_GRASS )
				{
					IGrass* srcEntity = dynamic_cast<IGrass*>( copyObj );
					if ( srcEntity )
					{
						newObj = execCreateOrCopyGrass( pos, srcEntity, srcEntity->getBaseGrassId());
					}
				}
				else if ( copyObj->getType() == SOT_EFFECTENTITY )
				{
					IEffectEntity* srcEntity = dynamic_cast<IEffectEntity*>( copyObj );

					if ( srcEntity )
					{
						newObj = execCreateOrCopyEffectEntity(  pos, srcEntity, srcEntity->getEffectResourceID() );
					}
				}
            }
			else
            {
                if ( mOpType == OT_CREATE_ENTITY )
                {
                    newObj = execCreateOrCopyEntity( pos, NULL, mCurrModelDeclID );
                }
				else if ( mOpType == OT_CREATE_TREE )
                {
					if (mTreeType == TYPE_TREE)
					{
						newObj = execCreateOrCopyTree( pos, NULL, mCurrTreeDeclID );
					}
					else if (mTreeType == TYPE_GRASS)
					{
						newObj = execCreateOrCopyGrass( pos, NULL, mCurrTreeDeclID );
					}
					else
					{
						assert(0);
					}
                }
				else if ( mOpType == OT_CREATE_EFFECTENTITY )
				{
					newObj = execCreateOrCopyEffectEntity( pos, NULL, mCurrEffectDeclID );
				}
            }


            if ( newObj )
            {
                ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat(newObj->getName().c_str(), newObj->getType());
                if ( format )
                {
                    FormSet::main_form->loadSceneElementProps( format, false );
                }

                destroySampleObject();
            }
        }

    }

    //-----------------------------------------------------------------------
    ISceneObject* OperationManager::execCreateOrCopyTree( Vec3 pos, ITree* srcTree, Int modelDeclID )
    {
        IScene* scene = CoreManager::getInstance().getScene();
        ITree* desTree = NULL;
		
		if (srcTree)
		{
			ISceneNode* pNode = srcTree->getSceneNode();
			if (pNode != NULL)
			{
				Vec3 scale;
				pNode->getScale(scale);
				Qua q;
				pNode->getOrientation(q);
				desTree = scene->getTreeManager()->createTree(modelDeclID, pos/* + Vec3(1.f, 0.f, 1.f)*/);
				ISceneNode* pDesTree = desTree->getSceneNode();
				pDesTree->setOrientation(q);
				pDesTree->setScale(scale);

				if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
				{
					desTree->getSceneNode()->stickTerrain();
				}
				CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desTree);
			}
		}
		else
		{
			desTree = scene->getTreeManager()->createTree(modelDeclID, pos);

			if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
			{
			    desTree->getSceneNode()->stickTerrain();
			}
			CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desTree);
		}

        return desTree;
    }

	//-----------------------------------------------------------------------
	ISceneObject* OperationManager::execCreateOrCopyGrass( Vec3 pos , IGrass* srcGrass,Int textureID )
	{
		IScene* scene = CoreManager::getInstance().getScene();
		IGrass* desGrass = NULL;

		if (srcGrass != NULL)
		{
			ISceneNode* pNode = srcGrass->getSceneNode();
			if (pNode != NULL)
			{
				Vec3 scale;
				pNode->getScale(scale);
				Qua q;
				pNode->getOrientation(q);
				desGrass = scene->getTreeManager()->createGrass(textureID, pos/* + Vec3(1.f, 0.f, 1.f)*/);
				if (desGrass != NULL)
				{
					ISceneNode* pDesGrass = desGrass->getSceneNode();
					pDesGrass->setOrientation(q);
					pDesGrass->setScale(scale);

					if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
					{
						desGrass->getSceneNode()->stickTerrain();
					}
					CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desGrass);
				}
			}
		}
		else
		{
			desGrass = scene->getTreeManager()->createGrass(textureID, pos);

			if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
			{
				desGrass->getSceneNode()->stickTerrain();
			}
			CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desGrass);
		}

		return desGrass;
	}

    //-----------------------------------------------------------------------
	ISceneObject* OperationManager::execCreateOrCopyEffectEntity( Vec3 pos , IEffectEntity* srcEntity,Int effectDeclID )
	{
		IScene* scene = CoreManager::getInstance().getScene();
		IEffectEntity* desEntity = NULL;
		Str groupName = SCENE_OBJECT_GROUP_STR_EFFECT;

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

				CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desEntity,false);
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

							CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desEntity,false);
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

			desEntity	= CoreManager::getInstance().getScene()->createEffectEntity(mCurrEffectDeclID, false);

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

				CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desEntity,false);
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
    ISceneObject* OperationManager::execCreateOrCopyEntity( Vec3 pos , IEntity* srcEntity,Int modelDeclID )
    {
        IScene* scene = CoreManager::getInstance().getScene();
        IEntity* desEntity = NULL;

		// 如果有选中物体， 需要拷贝选中物体的属性， 包括这个物体的属性
		if ( srcEntity && 
			srcEntity->getModelObject() && 
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
			desEntity = CoreManager::getInstance().getScene()->createEntity( 
                            srcEntity->getModelObject()->getModelDeclarationID(), prefix.c_str() );
			
			//设置新物件的属性
			if ( desEntity && 
				desEntity->getModelObject() && 
				desEntity->getSceneNode() )
			{
				copyEntityBaseAttribute( desEntity, srcEntity );
				scene->createEntityStaticAccessorys(desEntity, desEntity->getModelObject()->getModelDeclarationID());
				desEntity->getSceneNode()->setPosition( oldPos + trans );

				if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
				{
					desEntity->getSceneNode()->stickTerrain();
				}

				CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desEntity);
			}

			//复制复选物件
			std::vector<ISceneObject*> multiSelectObjects;
			CoreManager::getInstance().getScene()->getSceneObjectController()->getMultiFocusList( multiSelectObjects );

			for ( U32 n = 0; n < multiSelectObjects.size(); n++  )
			{
				ISceneObject* srcObject = multiSelectObjects[n];

				if ( srcObject && srcObject->getType() == SOT_ENTITY )
				{
					IEntity* srcEntity = dynamic_cast<IEntity*>(srcObject);
					IEntity* desEntity = NULL;

					Str prefix = srcEntity->getGroup() + "_";
					
					if ( srcEntity && 
						srcEntity->getModelObject() && 
						srcEntity->getSceneNode() )
					{
						desEntity = CoreManager::getInstance().getScene()->createEntity( srcEntity->getModelObject()->getModelDeclarationID(), prefix.c_str() );
						

						if ( desEntity && 
							desEntity->getModelObject() && 
							desEntity->getSceneNode() )
						{
							copyEntityBaseAttribute( desEntity, srcEntity );
							scene->createEntityStaticAccessorys(desEntity, desEntity->getModelObject()->getModelDeclarationID());

							Vec3 oldPos;
							srcEntity->getSceneNode()->getPosition(oldPos);

							Vec3 newPos = oldPos + trans;
							desEntity->getSceneNode()->setPosition(newPos);

							if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
							{
								desEntity->getSceneNode()->stickTerrain();
							}

							CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desEntity);
						}
					
					}
				}
			}
		}
		// 没有选中物体则自己创建
		else
		{
			if ( modelDeclID == 0 )
				return NULL;

			//和GameMapEditor产生的静态物件区分开来
			Str groupName = "ART_"SCENE_OBJECT_GROUP_STR_STATIC;
			Str prefix = groupName + "_";
			desEntity	= CoreManager::getInstance().getScene()->createEntity(modelDeclID, prefix.c_str());

			if ( desEntity && 
				desEntity->getModelObject() && 
				desEntity->getSceneNode() )
			{
				//设置组别
				desEntity->setGroup(groupName);

				//设置渲染状态
				desEntity->getDeclaration().isLoadWhenGame = true;
				desEntity->getDeclaration().batchGroup = desEntity->getName();

				//设置属性
				scene->createEntityStaticAccessorys(desEntity, desEntity->getModelObject()->getModelDeclarationID());
				desEntity->getSceneNode()->setPosition( pos );
				desEntity->getModelObject()->setShadowCastType(SCT_DYNAMIC);
				desEntity->getModelObject()->setDynamicShadowReceiveEnable(true);

				if ( CoreManager::getInstance().getScene()->getSceneObjectController()->isTerrainSticked() )
				{
					desEntity->getSceneNode()->stickTerrain();
				}

				CoreManager::getInstance().getScene()->getXmlSerializer()->addSceneObjectFormat(desEntity);
			}
		}

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG

        static Bool CoreManager_ColorSwith = true;
        if ( CoreManager::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true) )
        {
            if ( FormSet::main_form->isTestCreateBatchEntity() == true )
            {
                UInt testIndex = 1;

                if ( testIndex == 1 )
                {
                    IScene* scene = CoreManager::getInstance().getScene();
                    ISceneObjectController* sceneObjCtrl =  scene->getSceneObjectController();
                    if ( sceneObjCtrl )
                    {
                        UInt halfNum    = FormSet::main_form->getTestBatchEntityNum();
                        UInt num        = halfNum * halfNum;
                        IEntityGroup* group = CoreManager::getInstance().getScene()->createEntityGroup(modelDeclID, num);
                        num = group->getEntityNum();

                        group->getModelObject()->setEmissive(MG::Color(0,0,0,0));

                      /*  if ( CoreManager_ColorSwith )
                        {
                            group->getModelObject()->setEmissive(MG::Color(222.0/255,198.0/255,61.0/255,255.0/255));
                        }else
                        {
                            group->getModelObject()->setEmissive(MG::Color(222.0/255,198.0/255,61.0/255,255.0/255));
                        }*/

                        CoreManager_ColorSwith = !CoreManager_ColorSwith;

                        //group->getModelObject()->setHightLight(1.2,false);

                        Vec3 newPos = pos;
                        UInt i = 0;
                        for ( UInt x=0; x<halfNum; x++ )
                        {
                            newPos.x = pos.x + x * 1;

                            for ( UInt z=0; z<halfNum; z++ )
                            {
                                newPos.z = pos.z + z * 1;

                                if (i<num)
                                {
                                    group->getEntity(i)->getSceneNode()->setVisible(true);
                                    group->getEntity(i)->getSceneNode()->setPosition(newPos);
                                    //group->getEntity(i)->getSceneNode()->setScale(Vec3(3,3,3));

                                    //if ( (i % 2) == 0)
                                    {
                                        //Str animName = "Walk";
                                        //Str animName = "walk";
                                        //Str animName = "Sneak";
                                        group->getEntity(i)->getAnimationController()->setIsIdle( true, "qiang_none_attack1" );

                                        //group->getEntity(i)->getAnimationController()->play( "normal_run001" );
                                        //group->getEntity(i)->getAnimationController()->setLoop( "normal_run001", true );
                                        //group->getEntity(i)->getAnimationController()->setLastFrameStopEnable( "normal_run001", false );

                                        //group->getEntity(i)->getAnimationController()->stop( "normal_run001" );

                                        //group->getEntity(i)->getAnimationController()->play( "normal_run001" );
                                        //group->getEntity(i)->getAnimationController()->setLoop( "normal_run001", true );
                                        //group->getEntity(i)->getAnimationController()->setLastFrameStopEnable( "normal_run001", false );
                                    }
                                }
                                i++;
                            }
                        }
                        //group->getEntity(num-1)->getSceneNode()->setPosition(Vec3(0,0,0));
                        //group->getEntity(num-1)->getSceneNode()->setVisible(false);
                    }
                }else
                if ( testIndex == 2 )
                {
                    UInt halfNum = FormSet::main_form->getTestBatchEntityNum();
                    UInt num = halfNum*halfNum;
                    IDecalSet* group = CoreManager::getInstance().getScene()->createDecalSet(num,"S_huoyanyu_attack_01.DDS",DT_SIMPLE);
                    num = group->getDecalNum();

                    Vec3 newPos = pos;
                    UInt i = 0;
                    for ( UInt x=0; x<halfNum; x++)
                    {
                        newPos.x = pos.x + x*1;
                        for ( UInt z=0; z<halfNum; z++)
                        {
                            newPos.z = pos.z + z*1;

                            if (i<num)
                            {
                                group->getDecal(i)->setPosition(newPos);
                            }

                            i++;
                        }
                    }
                }
            }
        }
#endif


   //     Vec3 pos;
   //     if ( CoreManager::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true) )
   //     {
   //         //if ( FormSet::main_form->isTestCreateBatchEntity() == false )
   //         {
			//	IScene* scene = CoreManager::getInstance().getScene();
			//	ISceneObjectController* sceneObjCtrl =  scene->getSceneObjectController();
			//	if ( sceneObjCtrl )
			//	{
			//		ISceneObject* sceneObj = sceneObjCtrl->getFocus();
			//		//如果有选中的物件， 则拷贝一份副本
			//		if ( sceneObj && 
			//			sceneObj->getType() == SOT_ENTITY )
			//		{
			//			IEntity* sceneEntity = dynamic_cast<IEntity*>( sceneObj );
			//			if ( sceneEntity && sceneEntity->getModelObject() )
			//			{
			//				IEntity* entity = CoreManager::getInstance().getScene()->createEntity( sceneEntity->getModelObject()->getModelDeclarationID() );
			//				if ( entity )
			//				{
			//					scene->createEntityAccessorys( entity, sceneEntity->getModelObject()->getModelDeclarationID() );
   //                             entity->getSceneNode()->setPosition( pos );
			//					onCopyModel( entity, sceneEntity );
			//				}
			//			}
			//		}
			//		else
			//		{
			//			//如果没有选中的物件， 以控件中选中的模型ID为蓝本创建一个物件
			//			IEntity* entity = CoreManager::getInstance().getScene()->createEntity( mCurrModelDeclID );
			//			if ( entity && entity->getSceneNode() )
			//			{
			//				scene->createEntityAccessorys( entity, mCurrModelDeclID );
			//				entity->getSceneNode()->setPosition( pos );
			//				onCreateModel( entity );
			//			}
			//		}
			//	}
   //         }
			//else
   //         {
   //             UInt testIndex = 1;

   //             if ( testIndex == 0 )
   //             {
   //                 UInt halfNum = FormSet::main_form->getTestBatchEntityNum();
   //                 UInt num = halfNum*halfNum;
   //                 ITerrainDecalSet* group = CoreManager::getInstance().getScene()->createTerrainDecalSet(num,"SelectedCircle.png");
   //                 num = group->getDecalNum();

   //                 Vec3 newPos = pos;
   //                 UInt i = 0;
   //                 for ( UInt x=0; x<halfNum; x++)
   //                 {
   //                     newPos.x = pos.x + x*1;
   //                     for ( UInt z=0; z<halfNum; z++)
   //                     {
   //                         newPos.z = pos.z + z*1;

   //                         if (i<num)
   //                         {
   //                             group->getDecal(i)->setPosition(newPos);
   //                         }

   //                         i++;
   //                     }
   //                 }
   //             }else
   //             if ( testIndex == 1 )
   //             {
   //                 UInt halfNum = FormSet::main_form->getTestBatchEntityNum();
   //                 UInt num = halfNum*halfNum;
   //                 IEntityGroup* group = CoreManager::getInstance().getScene()->createEntityGroup(mCurrModelDeclID, num);
   //                 num = group->getEntityNum();

   //                 group->getModelObject()->setEmissive(MG::Color(0,1,0));
   //                 //group->getModelObject()->setHightLight(1.2,false);

   //                 Vec3 newPos = pos;
   //                 UInt i = 0;
   //                 for ( UInt x=0; x<halfNum; x++)
   //                 {
   //                     newPos.x = pos.x + x*1;
   //                     for ( UInt z=0; z<halfNum; z++)
   //                     {
   //                         newPos.z = pos.z + z*1;

   //                         if (i<num)
   //                         {
   //                             group->getEntity(i)->getSceneNode()->setVisible(true);
   //                             group->getEntity(i)->getSceneNode()->setPosition(newPos);

   //                             if ( (i % 2) == 0)
   //                             {
   //                                 //Str animName = "Walk";
   //                                 Str animName = "walk";
   //                                 //Str animName = "Sneak";
   //                                 group->getEntity(i)->getAnimationController()->setIsIdle(animName.c_str(),true);
   //                             }
   //                         }
   //                         i++;
   //                     }
   //                 }
   //                 //group->getEntity(num-1)->getSceneNode()->setPosition(Vec3(0,0,0));
   //                 //group->getEntity(num-1)->getSceneNode()->setVisible(false);

   //             }
   //         }
   //     }

        return desEntity;
    }

	//-----------------------------------------------------------------------
	void OperationManager::copyEntityBaseAttribute(IEntity* targetObj, IEntity* srcObj)
	{
		if ( srcObj && targetObj )
		{
			////////////////////////////////////////////////
			bool enable = srcObj->getModelObject()->getDynamicShadowReceiveEnable();
			targetObj->getModelObject()->setDynamicShadowReceiveEnable(enable);

			ShadowCasterType castType = srcObj->getModelObject()->getShadowCastType();
			targetObj->getModelObject()->setShadowCastType(castType);



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
		IScene* scene = CoreManager::getInstance().getScene();
		if ( !scene )
			return;

        ISceneObject* object = scene->getSceneObjectController()->getFocus();
        if ( object && object != mSampleSceneObj )
        {
			ISceneObjectController* controller = scene->getSceneObjectController();

			//添加删除物件历史记录
			if (controller)
			{
				U32 objectDeclID;
				SceneObjectTypes sceneObjType = object->getType();
				if (sceneObjType == SOT_ENTITY)
				{
					IEntity* srcEntity = dynamic_cast<IEntity*>( object );
					objectDeclID = srcEntity->getModelObject()->getModelDeclarationID();
				}
				else if ( sceneObjType == SOT_TREE )
				{
					ITree* srcEntity = dynamic_cast<ITree*>( object );
					objectDeclID = srcEntity->getBaseTreeId();
				}
				else if (sceneObjType == SOT_GRASS)
				{
					IGrass* srcEntity = dynamic_cast<IGrass*>( object );
					objectDeclID = srcEntity->getBaseGrassId();
				}
				else if ( sceneObjType == SOT_EFFECTENTITY )
				{
					IEffectEntity* srcEntity = dynamic_cast<IEffectEntity*>(object);
					objectDeclID = srcEntity->getEffectResourceID();
				}
				ObjectState state;
				state.objectDeclID = objectDeclID;
				state.name = object->getName();
				state.type = object->getType();
				object->getSceneNode()->getPosition(state.pos);
				object->getSceneNode()->getOrientation(state.qua);
				object->getSceneNode()->getScale(state.scale);

				OperationRecord record;
				record.type = 3;
				record.state = state;

				controller->mRedoOperations.clear();
				controller->mUndoOperations.push_front(record);
			}
			
			//删除单选物体
            FormSet::main_form->revert();
			controller->setFocus(NULL);
			scene->getXmlSerializer()->removeSceneObjectFormat( object->getName().c_str(), object->getType(), true);

			//删除框选物体
			std::vector<ISceneObject*> objectList;
			controller->getMultiFocusList( objectList );
			if (objectList.size() > 0)
			{
				for ( U32 i = 0; i < objectList.size(); i++ )
				{
					scene->getXmlSerializer()->removeSceneObjectFormat( (objectList[i]->getName()).c_str(), objectList[i]->getType(), true);
				}

				controller->clearMultiFocus(true);
			}
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
			//快捷键Ctrl+Z撤销操作
			if ( (input->isKeyHolded(KC_LCONTROL)|| input->isKeyHolded(KC_RCONTROL)) && input->isKeyPressed(KC_Z) )
			{	
				undoOp();
			}

			//快捷键Ctrl+Y撤销操作
			if ( (input->isKeyHolded(KC_LCONTROL)|| input->isKeyHolded(KC_RCONTROL)) && input->isKeyPressed(KC_Y) )
			{	
				redoOp();
			}

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

				/*IEntity* entity = CoreManager::getInstance().getScene()->getEntity("_Entity7");
				entity->setRenderGroup(5);

				entity = CoreManager::getInstance().getScene()->getEntity("_Entity8");
				entity->setRenderGroup(6);

				entity = CoreManager::getInstance().getScene()->getEntity("_Entity9");
				entity->setRenderGroup(7);*/

				/*entity = CoreManager::getInstance().getScene()->getEntity("_Entity17");
				entity->setRenderGroup(5);

				entity = CoreManager::getInstance().getScene()->getEntity("_Entity18");
				entity->setRenderGroup(6);

				entity = CoreManager::getInstance().getScene()->getEntity("_Entity19");
				entity->setRenderGroup(7);*/
			}

			//快捷键随机选取创建的模型
			//if ( input->isKeyPressed( KC_LSHIFT ) )
			//{
			//	FormSet::main_form->randonprepareCreateEntity();
			//}

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

			//快捷键Insert插入创建实体
			if ( input->isKeyPressed(KC_INSERT) )
			{		
				//this->execCreateOrCopyModel();
				this->dropCursorElement();
			}
			
			if (input->isKeyPressed(KC_I))
			{
				 //ITreeManager* pMgr = CoreManager::getInstance().getScene()->getTreeManager();
				 //if (pMgr)
				 //{
					// ITree* pTree = pMgr->getTree("Tree2");
					// if (pTree)
					// {
					//	 //static float angle = 0;
					//	 //angle += 3.14f / 4.f;
					//	 pTree->getSceneNode()->yaw(3.14f / 4.f);
					// }
				 //}
				static bool bShow = true;
				ITerrainManager* pTerrainMgr = CoreManager::getInstance().getScene()->getTerrainManager();
				ITreeManager* pMgr = CoreManager::getInstance().getScene()->getTreeManager();
				if (pMgr)
				{
					if (bShow)
					{
						int h = pTerrainMgr->getTerrainHeight();
						int w = pTerrainMgr->getTerrainWidth();
						for (int i = 0; i < h; i += 50.f)
						{
							for (int j = 0; j < w; j += 50.f)
							{
								pMgr->createTree(MGRandom::getInstance().rand_ab_One(0, 11), Vec3(j, 0.f, -i));
							}
						}
						for (int i = 0; i < h; i += 10.f)
						{
							for (int j = 0; j < w; j += 10.f)
							{
								pMgr->createGrass(0, Vec3(j, 0.f, -i));
							}
						}
					}
					else
					{
						pMgr->destroyAllTree();
						pMgr->destroyAllGrass();
					}
					bShow = !bShow;
				}
			}

			//左键单击创建物体
			if ( input->isMousePressed(MB_Left) )
			{	
				if (mSampleSceneObj)
				{
					this->dropCursorElement();
				}
				else if (FormSet::main_form->mIsSceneLoaded)
				{
					ITerrainManager* terrain = CoreManager::getInstance().getScene()->getTerrainManager();

					Vec3 perturbPos;
					terrain->getMouseRayIntersection( perturbPos, true );
					CoreManager::getInstance().getScene()->getTreeManager()->setGrassPerturbCircle(perturbPos, 2.0f);
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

			//快捷键切换显示水
			if ( input->isKeyPressed(KC_O) )
			{
				IEngineMain* engineMain = CoreManager::getInstance().getEngineMain();
				if ( engineMain && engineMain->display() )
				{
					IDisplay* idisplay = engineMain->display();
					idisplay->setTerrainWaterVisible(!idisplay->getTerrainWaterVisible(), true);
				}
			}

			//快捷键切换显示物件
			if ( input->isKeyPressed(KC_U) )
			{
				IEngineMain* engineMain = CoreManager::getInstance().getEngineMain();
				if ( engineMain && engineMain->display() )
				{
					IDisplay* idisplay = engineMain->display();
					idisplay->setEntityVisible(!idisplay->getEntityVisible(), true);
				}
			}

			//快捷键切换tab
			if ( input->isKeyPressed(KC_1) )
			{
				FormSet::main_form->onEventSelectTab(1);
			}
			else if ( input->isKeyPressed(KC_2) )
			{
				FormSet::main_form->onEventSelectTab(2);
			}
			else if ( input->isKeyPressed(KC_3) )
			{
				FormSet::main_form->onEventSelectTab(3);
			}			 

			//笔刷、衰减、幅度变化
			Int	wheelRel = 0;
			wheelRel = input->getMouseWheel();
			if ( wheelRel != 0 )
			{
				if ( input->isKeyHolded(KC_LSHIFT) )
				{
					if ( input->isKeyHolded(KC_LCONTROL))
						FormSet::main_form->onEventBrushSoftenChanged(wheelRel);
					else
						FormSet::main_form->onEventBrushSizeChanged(wheelRel);

				}
				else if ( input->isKeyHolded(KC_LCONTROL) && input->isKeyHolded(KC_LMENU) )
				{
					FormSet::main_form->onEventBrushAmplitudeChanged(wheelRel);
				}
			}

            if ( input->isKeyHolded(KC_LMENU) )
            {
                ISceneDebuger* debug = scene->getSceneDebuger();

                if ( input->isKeyHolded(KC_Z) )
                {
                    debug->hideTexture();
                }
                if ( input->isKeyHolded(KC_X) )
                {
                    debug->showTexture( "shadow" );
                }
                if ( input->isKeyHolded(KC_C) )
                {
                    debug->showTexture( "reflect" );
                }
            }
		}

		//if ( input->isKeyPressed(KC_Y) )
		//{
		//	IEntity* entity = scene->createEntity( "test", 20002 );
		//	scene->createEntityStaticAccessorys( entity, 20002 );
		//}

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
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_ENTITY, formatList);

			//trees
			std::vector<ISceneObjectXmlFormat*> treeFormatList;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_TREE, treeFormatList);
			formatList.insert(formatList.end(),treeFormatList.begin(),treeFormatList.end());

			//grass
			std::vector<ISceneObjectXmlFormat*> grassFormatList;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_GRASS, grassFormatList);
			formatList.insert(formatList.end(),grassFormatList.begin(),grassFormatList.end());

			//特效
			std::vector<ISceneObjectXmlFormat*> effectFormatList;
			scene->getXmlSerializer()->getSceneObjectXmlFormatList(SOT_EFFECTENTITY, effectFormatList);
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
		///////////////////////////////////////////////////////////////////////////////////////


		//更新编辑器样本模型
		if (mSampleSceneObj != NULL)
			updateCursorElement();

        //开始激活一次编辑操作
        if( input->isMousePressed( MB_Left) )
        {
            switch (mOpType)
            {
            //    ////////////////////////////////////////////////////////
            //case OT_CREATE_ENTITY:
            //    execCreateEntity();
            //    break;

                ////////////////////////////////////////////////////////
            case OT_TERRAIN_BATCH_ADD:
                updateTerrainBatchAddOp(input,scene,terrain,editorSys);
                break;

            case OT_TERRAIN_BATCH_REMOVE:
                updateTerrainBatchRemoveOp(input,scene,terrain,editorSys);
                break;

			case OT_TERRAIN_BATCH_DEFINE:
				updateTerrainBatchDefineOp(input,scene,terrain,editorSys);
				break;

                ////////////////////////////////////////////////////////
            case OT_TERRAIN_REGION_ADD:
                updateTerrainBlockAddOp(input,scene,terrain,editorSys);
                break;

            case OT_TERRAIN_REGION_REMOVE:
                updateTerrainBlockRemoveOp(input,scene,terrain,editorSys);
                break;

                ////////////////////////////////////////////////////////

            case OT_TERRAIN_WATER_SHOW:
                updateTerrainWaterShowOp(input,scene,terrain,editorSys);
                break;

            case OT_TERRAIN_WATER_HIDE:
                updateTerrainWaterHideOp(input,scene,terrain,editorSys);
                break;
            }
        }

        // 更新brush
        {
            switch (mOpType)
            {
                ////////////////////////////////////////////////////////
            case OT_TERRAIN_BATCH_ADD:
            case OT_TERRAIN_BATCH_REMOVE:
            case OT_TERRAIN_BATCH_DEFINE:

            case OT_TERRAIN_REGION_ADD:
            case OT_TERRAIN_REGION_REMOVE:

            case OT_TERRAIN_HEIGHT_LEVEL:
            case OT_TERRAIN_HEIGHT_UNIFORM:
            case OT_TERRAIN_HEIGHT_FLAT:
            case OT_TERRAIN_HEIGHT_NOISE:

            case OT_TERRAIN_TEXTURE_ADD:
            case OT_TERRAIN_TEXTURE_REMOVE:
            case OT_TERRAIN_TEXTURE_UNIFORM:
            case OT_TERRAIN_TEXTURE_MOP:
            case OT_TERRAIN_TEXTURE_BLUR:
                
            case OT_TERRAIN_WATER_HEIGHT_LEVEL:
            case OT_TERRAIN_WATER_HEIGHT_UNIFORM:
            case OT_TERRAIN_WATER_HEIGHT_FLAT:
            case OT_TERRAIN_WATER_SHOW:
            case OT_TERRAIN_WATER_HIDE:

                updateBrushOp(input,scene,terrain,editorSys);
            }
        }

		if ( isUpdateTerrainOperation(delta) )
		{
			//开始激活一次编辑操作
			switch (mOpType)
			{
            ////////////////////////////////////////////////////////
            // 地形高度相关
			case OT_TERRAIN_HEIGHT_LEVEL:
				updateTerrainHeightDeformOp(input,scene,terrain,editorSys);
				break;
			case OT_TERRAIN_HEIGHT_UNIFORM:
				updateTerrainHeightUniformOp(input,scene,terrain,editorSys);
				break;
			case OT_TERRAIN_HEIGHT_FLAT:
				updateTerrainHeightFlatOp(input,scene,terrain,editorSys);
				break;
			case OT_TERRAIN_HEIGHT_NOISE:
				updateTerrainHeightNoiseOp(input,scene,terrain,editorSys);
				break;
            ////////////////////////////////////////////////////////
            // 地形贴图相关
			case OT_TERRAIN_TEXTURE_ADD:
				updateTerrainTextureAddOp(input,scene,terrain,editorSys);
				break;
			case OT_TERRAIN_TEXTURE_REMOVE:
				updateTerrainTextureRemoveOp(input,scene,terrain,editorSys);
				break;
			case OT_TERRAIN_TEXTURE_UNIFORM:
				updateTerrainTextureUniformOp(input,scene,terrain,editorSys);
				break;
			case OT_TERRAIN_TEXTURE_MOP:
				updateTerrainTextureMopOp(input,scene,terrain,editorSys);
				break;
			case OT_TERRAIN_TEXTURE_BLUR:
				updateTerrainTextureBlurOp(input,scene,terrain,editorSys);
				break;
            ////////////////////////////////////////////////////////
			// 水相关
			case OT_TERRAIN_WATER_HEIGHT_LEVEL:
				updateTerrainWaterHeightDeformOp(input,scene,terrain,editorSys);
				break;

			case OT_TERRAIN_WATER_HEIGHT_UNIFORM:
				updateTerrainWaterHeightUniformOp(input,scene,terrain,editorSys);
				break;

			case OT_TERRAIN_WATER_HEIGHT_FLAT:
				updateTerrainWaterHeightFlatOp(input,scene,terrain,editorSys);
				break;
			}
		}
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateBrushOp( IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys )
    {
        Vec3 mouseTerrainIntersection;
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainHeightDeformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
		Vec3 mouseTerrainIntersection;

		if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
		{
			editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

			IEditorOperation* op = NULL;

			if ( input->isMouseHolded(MB_Left) )
			{
                editorSys->getTerrainRaiseHeightOperationManager()->setTerrainSurfaceType( TST_GROUND );
				op = editorSys->getTerrainRaiseHeightOperationManager()->createOneOperation();
			}
			else if ( input->isMouseHolded( MB_Right ) )
			{
                editorSys->getTerrainLowerHeightOperationManager()->setTerrainSurfaceType( TST_GROUND );
				op = editorSys->getTerrainLowerHeightOperationManager()->createOneOperation();
			}

			if ( op )
				editorSys->push( op );
		}
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainHeightUniformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            editorSys->getTerrainUniformHeightOperationManager()->setTerrainSurfaceType( TST_GROUND );
            IEditorOperation* op = editorSys->getTerrainUniformHeightOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainHeightNoiseOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;
        
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            editorSys->getTerrainNoiseHeightOperationManager()->setTerrainSurfaceType( TST_GROUND );
            IEditorOperation* op = editorSys->getTerrainNoiseHeightOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainHeightFlatOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;
        
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            editorSys->getTerrainSmoothHeightOperationManager()->setTerrainSurfaceType( TST_GROUND );
            IEditorOperation* op = editorSys->getTerrainSmoothHeightOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }


    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainTextureAddOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;
        
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

			if ( input->isMouseHolded(MB_Right) )
			{
				IEditorOperation* op = editorSys->getTerrainAddTextureOperationManager()->createOneOperation();
				editorSys->push( op );
			}
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainTextureRemoveOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;
        
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

			if ( input->isMouseHolded(MB_Right) )
			{
				IEditorOperation* op = editorSys->getTerrainRemoveTextureOperationManager()->createOneOperation();
				editorSys->push( op );
			}
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainTextureUniformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;
        
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

			if ( input->isMouseHolded(MB_Right) )
			{
				IEditorOperation* op = editorSys->getTerrainUniformHeightOperationManager()->createOneOperation();
				editorSys->push( op );
			}
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainTextureMopOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;
        
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

			if ( input->isMouseHolded(MB_Right) )
			{
				IEditorOperation* op = editorSys->getTerrainMopTextureOperationManager()->createOneOperation();
				editorSys->push( op );
			}
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainTextureBlurOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;
        
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

			if ( input->isMouseHolded(MB_Right) )
			{
				IEditorOperation* op = editorSys->getTerrainBlurTextureOperationManager()->createOneOperation();
				editorSys->push( op );
			}
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainBatchAddOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;

        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            //IEditorOperation* op = editorSys->getTerrainAddBatchEntityOperationManager()->createOneOperation();
			IEditorOperation* op = editorSys->getTerrainAddTreeOperationManager()->createOneOperation();
            editorSys->push( op );

			//op = editorSys->getTerrainDefineBatchEntityOperationManager()->createOneOperation();
			op = editorSys->getTerrainDefineTreeOperationManager()->createOneOperation();
			editorSys->push( op );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainBatchRemoveOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;

        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            //IEditorOperation* op = editorSys->getTerrainRemoveBatchEntityOperationManager()->createOneOperation();
			IEditorOperation* op = editorSys->getTerrainRemoveTreeOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }

	//-----------------------------------------------------------------------
	void OperationManager::updateTerrainBatchDefineOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
	{
		Vec3 mouseTerrainIntersection;

		if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
		{
			editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

			//IEditorOperation* op = editorSys->getTerrainDefineBatchEntityOperationManager()->createOneOperation();
			IEditorOperation* op = editorSys->getTerrainDefineTreeOperationManager()->createOneOperation();
			editorSys->push( op );
		}
	}

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainBlockAddOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;

        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            IEditorOperation* op = editorSys->getTerrainAddRegionOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainBlockRemoveOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;

        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            IEditorOperation* op = editorSys->getTerrainRemoveRegionOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainWaterHeightDeformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;

        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            IEditorOperation* op = NULL;

            if ( input->isMouseHolded(MB_Left) )
            {
                editorSys->getTerrainRaiseHeightOperationManager()->setTerrainSurfaceType( TST_WATER );
                op = editorSys->getTerrainRaiseHeightOperationManager()->createOneOperation();
            }
            else if ( input->isMouseHolded( MB_Right ) )
            {
                editorSys->getTerrainLowerHeightOperationManager()->setTerrainSurfaceType( TST_WATER );
                op = editorSys->getTerrainLowerHeightOperationManager()->createOneOperation();
            }

            if ( op )
                editorSys->push( op );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainWaterHeightUniformOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;
        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            editorSys->getTerrainUniformHeightOperationManager()->setTerrainSurfaceType( TST_WATER );
            IEditorOperation* op = editorSys->getTerrainUniformHeightOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainWaterHeightFlatOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;

        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            editorSys->getTerrainSmoothHeightOperationManager()->setTerrainSurfaceType( TST_WATER );
            IEditorOperation* op = editorSys->getTerrainSmoothHeightOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainWaterShowOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;

        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            IEditorOperation* op = editorSys->getTerrainWaterShowOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }

    //-----------------------------------------------------------------------
    void OperationManager::updateTerrainWaterHideOp(IInput* input, IScene* scene, ITerrainManager* terrain, IEditorSystem* editorSys)
    {
        Vec3 mouseTerrainIntersection;

        if ( terrain->getMouseRayIntersection(mouseTerrainIntersection, true) )
        {
            editorSys->getBrushSystem()->setStartPos( mouseTerrainIntersection );

            IEditorOperation* op = editorSys->getTerrainWaterHideOperationManager()->createOneOperation();
            editorSys->push( op );
        }
    }

	//-----------------------------------------------------------------------
	bool OperationManager::isUpdateTerrainOperation(Flt delta)
	{
		Bool isUpdateOp = false;

		IInput* input = CoreManager::getInstance().getEngineMain()->input();
		if ( input == NULL )
			return isUpdateOp;

		if ( input->isMousePressed(MB_Left) ||
			input->isMousePressed(MB_Right))
		{
			mIsMouseStateCheck = true;
			mTimeMouseHold = 0.0f;
			isUpdateOp = true;
		}
		else if ( mIsMouseStateCheck && 
			( input->isMouseHolded(MB_Left) || input->isMouseHolded(MB_Right) ) )
		{
			if ( mTimeMouseHold > mOpInterval )
			{
				/*static int lower_time = 0;
				std::wstring text;
				MG::MGStrOp::toString(lower_time++, text);
				text += L":terrain_down\n";
				OutputDebugString(text.c_str())*/

				mTimeMouseHold = 0.0f;
				isUpdateOp = true;
			}
			else
			{
				mTimeMouseHold += delta;
			}
		}
		else if ( mIsMouseStateCheck && 
			!input->isMouseHolded(MB_Left) && 
			!input->isMouseHolded(MB_Right) ) 
		{
			mIsMouseStateCheck = false;
		}

		return isUpdateOp;
	}


	//-----------------------------------------------------------------------
	void OperationManager::updateCursorElement()
	{
		if (mSampleSceneObj)
		{
			//mSampleSceneObj->getSceneNode()->setVisible(true);

			//如果是模型则更新发光信息
			if (mSampleSceneObj->getType() == SOT_ENTITY)
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
				IEntity* entity = dynamic_cast<IEntity*>(mSampleSceneObj);
				entity->getModelObject()->setHightLight(curHLValue);
			}

			//更新位置
			IScene* scene = CoreManager::getInstance().getScene();
			if ( scene && scene->getTerrainManager() )
			{
				Vec3 entity_pos;
				if (FormSet::scene_form->Focused)
				{
					ITerrainManager* terrain = scene->getTerrainManager();

					terrain->getMouseRayIntersection( entity_pos, true );
					if (mSampleSceneObj->getType() == SOT_ENTITY)
					{
						static clock_t lastTime = clock();
						if (clock() - lastTime > 100)
						{
							IEntity* pEntity = static_cast<IEntity*>(mSampleSceneObj);
							Flt width = pEntity->getModelObject()->getWidth();
							Flt radiu = width/2.0f*3;
							scene->getTreeManager()->setGrassPerturbCircle(entity_pos, radiu);
							lastTime = clock();
						}
					}
				}
				else
				{
					Vec3 camPos,camDir;
					CoreManager::getInstance().getScene()->getActiveCamera()->getPosition(camPos);
					CoreManager::getInstance().getScene()->getActiveCamera()->getDirection(camDir);
					CoreManager::getInstance().getScene()->getTerrainManager()->getRayIntersection(camPos,camDir,entity_pos,true);
				}


				ISceneNode* sceneNode = mSampleSceneObj->getSceneNode();
				if ( sceneNode )
					sceneNode->setPosition(entity_pos);
			}
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::showCursorElement()
	{
		if (mSampleSceneObj)
		{
			mSampleSceneObj->getSceneNode()->setVisible(true);
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::hideCursorElement()
	{
		if (mSampleSceneObj)
		{
			mSampleSceneObj->getSceneNode()->setVisible(false);
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::dropCursorElement()
	{
		if ( !mSampleSceneObj )
			return;

		Vec3 pos;
		Int declID = mCurrModelDeclID;
		if ( CoreManager::getInstance().getScene()->getTerrainManager()->getMouseRayIntersection(pos,true) )
		{
			IScene* scene = CoreManager::getInstance().getScene();
			if ( !scene )
				return;

			// 创建的对象
			ISceneObject* newObj = NULL;
			U32 objectDeclID;

			SceneObjectTypes sceneObjType = mSampleSceneObj->getType();
			if (sceneObjType == SOT_ENTITY)
			{
				IEntity* srcEntity = dynamic_cast<IEntity*>( mSampleSceneObj );
				//newObj = execCreateOrCopyEntity( pos, NULL, mCurrModelDeclID );
				objectDeclID = srcEntity->getModelObject()->getModelDeclarationID();
				newObj = execCreateOrCopyEntity( pos, srcEntity,  objectDeclID);
			}
			else if ( sceneObjType == SOT_TREE )
			{
				ITree* srcEntity = dynamic_cast<ITree*>( mSampleSceneObj );

				if ( srcEntity )
				{
					objectDeclID = srcEntity->getBaseTreeId();
					newObj = execCreateOrCopyTree( pos, srcEntity, objectDeclID );
					//随机旋转
					float w = ((rand() % 199)-100)*0.01;
					float y = ((rand() % 199)-100)*0.01;
					MG::Qua qua(w,0,y,0);
					newObj->getSceneNode()->setOrientation(qua);
				}
			}
			else if (sceneObjType == SOT_GRASS)
			{
				IGrass* srcEntity = dynamic_cast<IGrass*>( mSampleSceneObj );
				if ( srcEntity )
				{
					objectDeclID = srcEntity->getBaseGrassId();
					newObj = execCreateOrCopyGrass( pos, srcEntity, objectDeclID );
					//随机一个大小
					GrassDeclaration* pDecl = scene->getTreeManager()->getGrassDeclarationByIndex(srcEntity->getBaseGrassId());
					MG::Flt width = pDecl->fWMin + (rand() % int((pDecl->fWMax - pDecl->fWMin)*10000))/10000.0;
					MG::Flt height = pDecl->fHMin + (rand() % int((pDecl->fHMax - pDecl->fHMin)*10000))/10000.0;
					srcEntity->width(width);
					srcEntity->height(height);
				}
			}
			else if ( sceneObjType == SOT_EFFECTENTITY )
			{
				objectDeclID = mCurrEffectDeclID;
				newObj = execCreateOrCopyEffectEntity( pos, dynamic_cast<IEffectEntity*>(mSampleSceneObj), mCurrEffectDeclID );
			}
			else
			{
				assert(0);
			}

			if ( newObj )
			{
				//添加创建物件历史记录
				ISceneObjectController* controller = scene->getSceneObjectController();
				if (controller)
				{
					ObjectState state;
					state.objectDeclID = objectDeclID;
					state.name = newObj->getName();
					state.type = newObj->getType();
					newObj->getSceneNode()->getPosition(state.pos);
					newObj->getSceneNode()->getOrientation(state.qua);
					newObj->getSceneNode()->getScale(state.scale);

					OperationRecord record;
					record.type = 1;
					record.state = state;

					controller->mRedoOperations.clear();
					controller->mUndoOperations.push_front(record);
				}

				ISceneObjectXmlFormat* format = CoreManager::getInstance().getScene()->getXmlSerializer()->getSceneObjectFormat(newObj->getName().c_str(), newObj->getType());
				if ( format )
				{
					FormSet::main_form->loadSceneElementProps( format, false );
				}
			}
		}

	}

	//-----------------------------------------------------------------------
	ISceneObject* OperationManager::createCursorElement(Int objectDeclID)
	{
		IScene* scene = CoreManager::getInstance().getScene();
		if ( scene )
		{
			if ( mOpType == OT_CREATE_ENTITY )
			{
				IEntity* entity = scene->createEntity( "SampleEntity", objectDeclID );
				entity->getModelObject()->setShadowCastType(SCT_DYNAMIC);
				entity->getModelObject()->setDynamicShadowReceiveEnable(true);
				mSampleSceneObj = entity;
				mSampleSceneObj->setQueryFlags(0);
			}
			else if ( mOpType == OT_CREATE_TREE )
			{
				Vec3 entity_pos;
				IScene* scene = CoreManager::getInstance().getScene();
				if ( scene && scene->getTerrainManager() )
				{
					ITerrainManager* terrain = scene->getTerrainManager();	
					terrain->getMouseRayIntersection( entity_pos, false );
				}

				if (mTreeType == TYPE_TREE)
				{
					mSampleSceneObj = scene->getTreeManager()->createTree( "SampleEntity", objectDeclID, entity_pos);
					if (mSampleSceneObj == NULL)
					{
						return NULL;
					}
					mSampleSceneObj->setQueryFlags(0);
					//随机旋转
					float w = ((rand() % 199)-100)*0.01;
					float y = ((rand() % 199)-100)*0.01;
					MG::Qua qua(w,0,y,0);
					mSampleSceneObj->getSceneNode()->setOrientation(qua);
				}
				else
				{
					mSampleSceneObj = scene->getTreeManager()->createGrass( "SampleEntity", objectDeclID, entity_pos);
					mSampleSceneObj->setQueryFlags(0);
					//随机一个大小
					GrassDeclaration* pDecl = scene->getTreeManager()->getGrassDeclarationByIndex(objectDeclID);
					MG::Flt width = pDecl->fWMin + (rand() % int((pDecl->fWMax - pDecl->fWMin)*10000))/10000.0;
					MG::Flt height = pDecl->fHMin + (rand() % int((pDecl->fHMax - pDecl->fHMin)*10000))/10000.0;
					dynamic_cast<IGrass*>(mSampleSceneObj)->width(width);
					dynamic_cast<IGrass*>(mSampleSceneObj)->height(height);
				}
			}
			else if ( mOpType == OT_CREATE_EFFECTENTITY )
			{
				mSampleSceneObj = scene->createEffectEntity( "SampleEntity", objectDeclID,false);
				mSampleSceneObj->setQueryFlags(0);
			}
		}

		if (mSampleSceneObj)
		{
			//mSampleSceneObj->getSceneNode()->setVisible(false);
			scene->getSceneObjectController()->setIgnoreFocus( mSampleSceneObj);
			scene->getSceneObjectController()->setFocusEnable(false);
		}

		return mSampleSceneObj;
	}

	//-----------------------------------------------------------------------
	void OperationManager::destroyCursorElement(void)
	{
		if (mSampleSceneObj != NULL)
		{
			IScene* scene = CoreManager::getInstance().getScene();
			if ( scene )
			{
				scene->getSceneObjectController()->setIgnoreFocus(NULL);
				scene->getSceneObjectController()->setFocusEnable(true);

				scene->getXmlSerializer()->removeSceneObjectFormat(mSampleSceneObj->getName().c_str(), mSampleSceneObj->getType(),true);
			}
		}

		mSampleSceneObj = NULL;
	}

	//-----------------------------------------------------------------------
	void OperationManager::copyElementToCursor()
	{
		Vec3 pos;
		Int declID = mCurrModelDeclID;
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
				if (mSampleSceneObj)
					destroyCursorElement();

				if ( copyObj->getType() == SOT_ENTITY )
				{
					IEntity* srcEntity = dynamic_cast<IEntity*>( copyObj );

					if ( srcEntity && srcEntity->getModelObject() )
					{
						mSampleSceneObj = execCreateOrCopyEntity( pos, srcEntity, srcEntity->getModelObject()->getModelDeclarationID() );
					}
				}
				else if ( copyObj->getType() == SOT_TREE )
				{
					ITree* srcEntity = dynamic_cast<ITree*>( copyObj );

					if ( srcEntity )
					{
						//createCursorElement(srcEntity->getModelObject()->getModelDeclarationID());
						mSampleSceneObj = execCreateOrCopyTree( pos, srcEntity, srcEntity->getBaseTreeId() );
					}
				}
				else if ( copyObj->getType() == SOT_GRASS )
				{
					IGrass* srcEntity = dynamic_cast<IGrass*>( copyObj );
					if ( srcEntity )
					{
						mSampleSceneObj = execCreateOrCopyGrass( pos, srcEntity, srcEntity->getBaseGrassId() );
					}
				}
				else if ( copyObj->getType() == SOT_EFFECTENTITY )
				{
					IEffectEntity* srcEntity = dynamic_cast<IEffectEntity*>( copyObj );

					if ( srcEntity )
					{
						//createCursorElement(srcEntity->getModelObject()->getModelDeclarationID());
						mSampleSceneObj = execCreateOrCopyEffectEntity(  pos, srcEntity, srcEntity->getEffectResourceID() );
						mOpType = OT_CREATE_EFFECTENTITY;
					}
				}
			}

			if ( sceneObjCtrl )
				sceneObjCtrl->setIgnoreFocus( mSampleSceneObj );
		}

	}

	void OperationManager::undoOp()
	{
		IScene* scene = CoreManager::getInstance().getScene();
		ISceneObjectController* controller = scene->getSceneObjectController();
		if (!controller->mUndoOperations.empty())
		{
			OperationRecord record = controller->mUndoOperations.front();
			ISceneObject* object;
			ObjectState state = record.state;
			OperationRecord newRecord;
			switch (record.type)
			{
			case 1: //创建
				//添加一个创建记录到重做栈
				controller->mRedoOperations.push_front(record);

				//删除创建的物体
				FormSet::main_form->revert();
				controller->setFocus(NULL);
				scene->getXmlSerializer()->removeSceneObjectFormat( record.state.name.c_str(), record.state.type, true);

				//从撤销栈中删除一个记录
				controller->mUndoOperations.pop_front();
				break;
			case 2: //修改
				//撤销修改前先保存当前操作状态
				object = scene->getXmlSerializer()->getSceneObjectFormat(record.state.name.c_str(),record.state.type)->getSceneObject();
				object->getSceneNode()->getPosition(state.pos);
				object->getSceneNode()->getOrientation(state.qua);
				object->getSceneNode()->getScale(state.scale);

				
				newRecord.type = 2;
				newRecord.state = state;

				//添加一个创建记录到重做栈
				controller->mRedoOperations.push_front(newRecord);

				//回滚到修改前状态
				object->getSceneNode()->setPosition(record.state.pos);
				object->getSceneNode()->setOrientation(record.state.qua);
				object->getSceneNode()->setScale(record.state.scale);
				controller->setFocus(object);
				//从撤销栈中删除一个记录
				controller->mUndoOperations.pop_front();
				break;
			case 3: //删除
				//撤销删除前先创建一个物件
				ISceneObject* newObj;
				U32 objectDeclID = record.state.objectDeclID;
				Vec3 pos = record.state.pos;
				Qua qua = record.state.qua;
				Vec3 scale = record.state.scale;
				if (record.state.type == SOT_ENTITY)
				{
					newObj = execCreateOrCopyEntity( pos, NULL,  objectDeclID);
				}
				else if ( record.state.type == SOT_TREE )
				{
					newObj = execCreateOrCopyTree( pos, NULL, objectDeclID );
				}
				else if (record.state.type == SOT_GRASS)
				{
					newObj = execCreateOrCopyGrass( pos, NULL, objectDeclID );
				}
				else if ( record.state.type == SOT_EFFECTENTITY )
				{
					newObj = execCreateOrCopyEffectEntity( pos, NULL, objectDeclID );
				}
				else
				{
					assert(0);
				}

				if ( newObj )
				{
					//更新栈中物体名字
					Str newName = newObj->getName();
					for (int i=0; i<controller->mUndoOperations.size(); i++)
					{
						if (controller->mUndoOperations.at(i).state.name == record.state.name)
						{
							controller->mUndoOperations.at(i).state.name = newName;
						}
					}
					//添加一个创建记录到重做栈
					{
						//ObjectState state;
						state.objectDeclID = objectDeclID;
						state.name = newName;
						state.type = newObj->getType();
						newObj->getSceneNode()->getPosition(state.pos);
						newObj->getSceneNode()->getOrientation(state.qua);
						newObj->getSceneNode()->getScale(state.scale);

						//OperationRecord newRecord;
						newRecord.type = 3;
						newRecord.state = state;

						controller->mRedoOperations.push_front(newRecord);
					}

					ISceneObjectXmlFormat* format = scene->getXmlSerializer()->getSceneObjectFormat(newObj->getName().c_str(), newObj->getType());
					if ( format )
					{
						FormSet::main_form->loadSceneElementProps( format, false );
						controller->setFocus(newObj);
					}
					//从撤销栈中删除一个记录
					controller->mUndoOperations.pop_front();
				}
				break;
			}
		}
	}

	//-----------------------------------------------------------------------
	void OperationManager::redoOp()
	{
		IScene* scene = CoreManager::getInstance().getScene();
		ISceneObjectController* controller = scene->getSceneObjectController();
		if (!controller->mRedoOperations.empty())
		{
			OperationRecord record = controller->mRedoOperations.front();
			ISceneObject* object;

			ObjectState state = record.state;
			OperationRecord newRecord;
			U32 objectDeclID = record.state.objectDeclID;
			Vec3 pos = record.state.pos;
			Qua qua = record.state.qua;
			Vec3 scale = record.state.scale;

			switch (record.type)
			{
			case 1: //创建
				//重做创建
				if (record.state.type == SOT_ENTITY)
				{
					object = execCreateOrCopyEntity( pos, NULL,  objectDeclID);
				}
				else if ( record.state.type == SOT_TREE )
				{
					object = execCreateOrCopyTree( pos, NULL, objectDeclID );
				}
				else if (record.state.type == SOT_GRASS)
				{
					object = execCreateOrCopyGrass( pos, NULL, objectDeclID );
				}
				else if ( record.state.type == SOT_EFFECTENTITY )
				{
					object = execCreateOrCopyEffectEntity( pos, NULL, objectDeclID );
				}
				else
				{
					assert(0);
				}

				if ( object )
				{
					//恢复删除前状态
					object->getSceneNode()->setPosition(pos);
					object->getSceneNode()->setOrientation(qua);
					object->getSceneNode()->setScale(scale);

					//更新数据到编辑器UI
					ISceneObjectXmlFormat* format = scene->getXmlSerializer()->getSceneObjectFormat(object->getName().c_str(), object->getType());
					if ( format )
					{
						FormSet::main_form->loadSceneElementProps( format, false );
						controller->setFocus(object);
					}

					//更新栈中物体名字
					Str newName = object->getName();
					for (int i=0; i<controller->mRedoOperations.size(); i++)
					{
						if (controller->mRedoOperations.at(i).state.name == record.state.name)
						{
							controller->mRedoOperations.at(i).state.name = newName;
						}
					}


					//添加一个创建记录到撤销栈
					{
						//ObjectState state;
						state.objectDeclID = objectDeclID;
						state.name = object->getName();
						state.type = object->getType();
						object->getSceneNode()->getPosition(state.pos);
						object->getSceneNode()->getOrientation(state.qua);
						object->getSceneNode()->getScale(state.scale);

						//OperationRecord newRecord;
						newRecord.type = 1;
						newRecord.state = state;

						controller->mUndoOperations.push_front(newRecord);
					}

					//从做栈中删除一个记录
					controller->mRedoOperations.pop_front();
				}
				break;
			case 2: //修改
				//重做修改前先保存当前操作状态
				object = scene->getXmlSerializer()->getSceneObjectFormat(record.state.name.c_str(),record.state.type)->getSceneObject();
				object->getSceneNode()->getPosition(state.pos);
				object->getSceneNode()->getOrientation(state.qua);
				object->getSceneNode()->getScale(state.scale);

				newRecord.type = 2;
				newRecord.state = state;

				//添加一个修改记录到撤销栈
				controller->mUndoOperations.push_front(newRecord);

				//重做修改
				object->getSceneNode()->setPosition(record.state.pos);
				object->getSceneNode()->setOrientation(record.state.qua);
				object->getSceneNode()->setScale(record.state.scale);
				controller->setFocus(object);
				//从重做栈中删除一个记录
				controller->mRedoOperations.pop_front();
				break;
			case 3: //删除
				//重做删除物件前先保存物件状态
				//ObjectState state;
				object = scene->getXmlSerializer()->getSceneObjectFormat(record.state.name.c_str(),record.state.type)->getSceneObject();
				state.objectDeclID = record.state.objectDeclID;
				state.type = object->getType();
				object->getSceneNode()->getPosition(state.pos);
				object->getSceneNode()->getOrientation(state.qua);
				object->getSceneNode()->getScale(state.scale);

				//OperationRecord newRecord;
				newRecord.type = 3;
				newRecord.state = state;

				//添加一个删除记录到撤销栈
				controller->mUndoOperations.push_front(newRecord);

				//删除创建的物体
				FormSet::main_form->revert();
				controller->setFocus(NULL);
				scene->getXmlSerializer()->removeSceneObjectFormat( object->getName().c_str(), object->getType(), true);
				//从重做栈中删除一个记录
				controller->mRedoOperations.pop_front();
				break;
			}
		}
	}
}

