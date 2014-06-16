/******************************************************************************/

#include "stdafx.h"
#include "TreeManager.h"
#include "SpeedTreeSystem.h"
#include "scene.h"
#include "EngineMain.h"
#include "Ogre.h"
#include "OgreD3D9RenderSystem.h"
#include "Tree.h"

/******************************************************************************/
namespace MG
{
    #define TREEMOVABLE_POOL_CATEGORY 3311

	/******************************************************************************/
	// TreeMovable
	/******************************************************************************/
	const String& TreeMovable::getMovableType(void) const
	{
		return "Tree";
	}

	//-----------------------------------------------------------------------
	const AxisAlignedBox& TreeMovable::getBoundingBox(void) const 
	{
		ISceneObject* sceneObject = any_cast<ISceneObject*>( getUserAny() ) ;
		if ( sceneObject && sceneObject->getType() == SOT_TREE )
		{
			Tree* tree = dynamic_cast<Tree*>(sceneObject);
			if ( tree )
			{
				return tree->getBoundingBox();
			}
		}
		return AxisAlignedBox::BOX_NULL;
	}
	
	//-----------------------------------------------------------------------
	const AxisAlignedBox& TreeMovable::getWorldBoundingBox(bool derive/* = false*/) const
	{
		ISceneObject* sceneObject = any_cast<ISceneObject*>( getUserAny() ) ;
		if ( sceneObject && sceneObject->getType() == SOT_TREE )
		{
			Tree* tree = dynamic_cast<Tree*>(sceneObject);
			if ( tree )
			{
				return tree->getWorldBoundingBox();
			}
		}

		return AxisAlignedBox::BOX_NULL;;
	}

	//-----------------------------------------------------------------------
	Real TreeMovable::getBoundingRadius(void) const
	{
		return 1;
	}

	//-----------------------------------------------------------------------
	void TreeMovable::_updateRenderQueue(RenderQueue* queue)
	{
	}

	/******************************************************************************/
	// Tree
	/******************************************************************************/
	void TreeMovable::visitRenderables(Renderable::Visitor* visitor, bool debugRenderables)
	{

	}
	//-----------------------------------------------------------------------
	Tree::Tree( Scene* scene, TreeManager* mgr, MG::SpeedTreeSystem* speedTreeSys, 
		UInt baseTreeID, CChar* pBaseTreeName )
		:mScene(scene)
		,mMgr(mgr)
		,mSpeedTreeSystem(speedTreeSys)
		,mTreeModelID(baseTreeID)
		,mBaseTreeName(pBaseTreeName)
		,mTreeMovable(NULL)
	{
		mPositionOffset = Vec3(0,0,0);
		mInitScale = Vec3(1,1,1);
	}
    //-----------------------------------------------------------------------
    Tree::~Tree()
    {
        destroyInstance();
		destroyOgreMovable();
    }

	//-----------------------------------------------------------------------
	Bool Tree::createInstance( CChar* pBaseTreeName, const Vec3& pos )
	{
		Bool bAdd = mSpeedTreeSystem->addInstance(pBaseTreeName, pos, mTreeInstance);
		//float fHeight = mSpeedTreeSystem->getBaseTreeHeight(pBaseTreeName);
		Vec3 vMin, vMax;
		mSpeedTreeSystem->getTreeExtents(pBaseTreeName, vMin, vMax);
		Vec3 vMid = vMax - vMin;
		//mBoundingBox.setExtents(Vector3(-vMid.x / 2.f, 0.f, -vMid.z / 2.f), Vector3(vMid.x / 2.f, vMax.y, vMid.z / 2.f));
		mBoundingBox.setExtents(Vector3(vMin.x, vMin.y, vMin.z), Vector3(vMax.x, vMax.y, vMax.z));
		return bAdd;
	}

    //-----------------------------------------------------------------------
    Bool Tree::destroyInstance()
    {
        return mSpeedTreeSystem->deleteInstance(mTreeModelID, mTreeInstance);
    }

	//-----------------------------------------------------------------------
	MovableObject* Tree::getOgreMovable()
	{
		return mTreeMovable;
	}

	Bool Tree::init(const Vec3& pos)
	{
		Bool bCreated = createInstance( mBaseTreeName.c_str(), pos );
		createOgreMovable();

		return bCreated;
	}

	//-----------------------------------------------------------------------
	void Tree::createOgreMovable()
	{
        mTreeMovable = MG_POOL_NEW_T(TreeMovable, TREEMOVABLE_POOL_CATEGORY)();
		//mTreeMovable = MG_NEW TreeMovable;

		//设置绑定实体对象的管理者
		mTreeMovable->setUserAny( Any( (ISceneObject*) this) );
		////设置查询标志位
		mTreeMovable->setQueryFlags (Scene::getQueryMask (this->getType()) );
	}

	//-----------------------------------------------------------------------
	void Tree::destroyOgreMovable()
	{
        MG_POOL_DELETE_T( mTreeMovable ,TreeMovable, TREEMOVABLE_POOL_CATEGORY);
		//MG_SAFE_DELETE(mTreeMovable);
	}

    //-----------------------------------------------------------------------
    SceneObjectTypes Tree::getType()
    {
        return SOT_TREE; 
    }

    //-----------------------------------------------------------------------
    ISceneNode* Tree::getSceneNode()
    {
        return this;
    }

	//-----------------------------------------------------------------------
	void Tree::setReflect(Bool bReflect)
	{
		if (!bReflect)
		{
			mSpeedTreeSystem->addExceptTreeInstance(mTreeModelID, mTreeInstance, SpeedTree::RENDER_PASS_REFLECT);
		}
		else
		{
			mSpeedTreeSystem->delExceptTreeInstance(mTreeModelID, mTreeInstance, SpeedTree::RENDER_PASS_REFLECT);
		}
	}

	//-----------------------------------------------------------------------
	Bool Tree::isNeedReflect()
	{
		return !mSpeedTreeSystem->isExceptTreeInstance(mTreeModelID, mTreeInstance, SpeedTree::RENDER_PASS_REFLECT);
	}
    //-----------------------------------------------------------------------
    IScene* Tree::getScene()
    {
        return mScene;
    }

    //-----------------------------------------------------------------------
    void Tree::setVisible(Bool visible)
    {
		if (visible)
		{
		}
		else
		{
			//mSpeedTreeSystem->addExceptTreeInstance(mTreeModelID, mTreeInstance, SpeedTree::RENDER_PASS_STANDARD);
		}
    }
    //-----------------------------------------------------------------------
    Bool Tree::getVisible()
    {
        return true;
    }
    //-----------------------------------------------------------------------
    void Tree::setPosition(Vec3& pos)
    {
		mSpeedTreeSystem->instancePosition(mTreeModelID, mTreeInstance, pos);
    }
    //-----------------------------------------------------------------------
    void Tree::getPosition(Vec3& pos)
    {
		SpeedTree::Vec3 stPos = mTreeInstance.GetPos();
		pos.x = stPos.x;
		pos.y = stPos.y;
		pos.z = stPos.z;
    }
    //-----------------------------------------------------------------------
    void Tree::getScreenPosition(Vec2& outPos)
    {
		Vec3 worldPos;
		getPosition(worldPos);

		IScene* pScene = getScene();
		ICamera* pCamera = pScene->getActiveCamera();
		pCamera->worldPointToScreenPoint(worldPos, outPos);
    }
    //-----------------------------------------------------------------------
    Bool Tree::getPositionDirty()
    {
        return false;
    }
    //-----------------------------------------------------------------------
    void Tree::clearPositionDirty()
    {
    }
    //-----------------------------------------------------------------------
    void Tree::setScale(Vec3& scale)
    {
		//mBoundingBox.scale(Vector3(scale.x, scale.x, scale.x));
		mSpeedTreeSystem->instanceScale(mTreeModelID, mTreeInstance, scale.x);
    }
    //-----------------------------------------------------------------------
    void  Tree::getScale(Vec3& scale)
    {
		float fScale = mTreeInstance.GetScale();
		scale.x = scale.y = scale.z = fScale;
    }
    //----------------------------------------------------------------------- 
    Bool  Tree::getScaleDirty()
    {
        return false;
    }
    //-----------------------------------------------------------------------
    void  Tree::clearScaleDirty()
    {

    }
    //-----------------------------------------------------------------------
    void  Tree::setOrientation(Qua& quaternion)
    {
		//Ogre::Quaternion q(quaternion.w, quaternion.x, quaternion.y, quaternion.z);

		//Radian rValue;
		//q.ToAngleAxis(rValue, Ogre::Vector3(0.f, 1.f, 0.f));
		MG::Vec3 axis;
		MG::Flt angle;
		quaternion.ToAngleAxis(angle,axis);
		mSpeedTreeSystem->instanceRotate(mTreeModelID, mTreeInstance, angle);
    }
    //-----------------------------------------------------------------------
    void  Tree::getOrientation(Qua& quaternion)
    {
		SpeedTree::Vec3 vRotateAxis = mTreeInstance.GetRotationVector();
		quaternion.FromAngleAxis(mTreeInstance.GetRotationAngle(), MG::Vec3(vRotateAxis.x, vRotateAxis.y, vRotateAxis.z));
    }
    //-----------------------------------------------------------------------
    Bool  Tree::getOrientationDirty()
    {
        return false;
    }

    //-----------------------------------------------------------------------
    void  Tree::clearOrientationDirty()
    {

    }

    //-----------------------------------------------------------------------
    void  Tree::setDirection(Vec3& vec, TransformSpace relativeTo)
    {
        
    }

    //-----------------------------------------------------------------------
    void  Tree::getDirection(Vec3& vec)
    {

    }

    //-----------------------------------------------------------------------
    void  Tree::lookAt(Vec3& targetPoint, TransformSpace relativeTo)
    {

    }

    //-----------------------------------------------------------------------
    void  Tree::translate(Vec3& d, TransformSpace relativeTo)
    {
		SpeedTree::Vec3 pos = mTreeInstance.GetPos();
		pos.x += d.x;
		pos.y += d.y;
		pos.z += d.z;
		mSpeedTreeSystem->instancePosition(mTreeModelID, mTreeInstance, Vec3(pos.x, pos.y, pos.z));
    }

    //-----------------------------------------------------------------------
    void  Tree::roll( Flt angle, TransformSpace relativeTo)
    {

    }
    //-----------------------------------------------------------------------
    void  Tree::pitch( Flt angle, TransformSpace relativeTo)
    {

    }
    //-----------------------------------------------------------------------
    void  Tree::yaw( Flt angle, TransformSpace relativeTo )
    {
		float oldAngle = mTreeInstance.GetRotationAngle();
		//float addAngle = angle * 0.25f;
		float newAngle = oldAngle + angle;

		bool bRotateSuccess = mSpeedTreeSystem->instanceRotate(mTreeModelID, mTreeInstance, newAngle);

/*
		const char* RESULT[] = 
		{
			"false",
			"true",
		};
		char szAngle[256] = {0};
		sprintf(szAngle, "Old:%f Add:%f New:%f %s\n", oldAngle, addAngle, newAngle, RESULT[bRotateSuccess]);
		OutputDebugString(szAngle);*/
    }

    //-----------------------------------------------------------------------
    void  Tree::rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo)
    {

    }

    //-----------------------------------------------------------------------
    void  Tree::stickTerrain()
    {

    }

	//void Tree::updateBox(AxisAlignedBox& aabb)
	//{
	//	CInstance instance;
	//	if (!mSpeedTreeSystem->getInstance(mTreeModelID, mInstanceID, instance))
	//	{
	//		return;
	//	}
	//	const SpeedTree::Vec3& pos = instance.GetPos();
	//	float scale = instance.GetScale();

	//	aabb = mBoundingBox;

	//	Vector3 vMin = aabb.getMinimum() + Vector3(pos.x, pos.y, pos.z);
	//	Vector3 vMax = aabb.getMaximum() + Vector3(pos.x, pos.y, pos.z);
	//	aabb.setExtents(vMin, vMax);
	//}

	const AxisAlignedBox& Tree::getWorldBoundingBox(void)
	{
		mWorldAABB = mBoundingBox;
		
		const SpeedTree::Vec3& pos = mTreeInstance.GetPos();
		float scale = mTreeInstance.GetScale();

		//Matrix4 matWorld;
		//matWorld.setTrans(Vector3(pos.x, pos.y, pos.z));
		//matWorld.setScale(Vector3(scale, scale, scale));
		//mWorldAABB.transform(matWorld);
		
		SpeedTree::st_float32 fScale = mTreeInstance.GetScale();
		mWorldAABB.scale(Vector3(fScale, fScale, fScale));

		Vector3 vMax = mWorldAABB.getMaximum() + Vector3(pos.x, pos.y, pos.z);
		Vector3 vMin = mWorldAABB.getMinimum() + Vector3(pos.x, pos.y, pos.z);

		mWorldAABB.setExtents(vMin, vMax);

		

		return mWorldAABB;
	}

//	void Tree::renderBox()
//	{
//		//DX_BeginPerfEvent(0xffffffff, L"BoundBox");
//		//AxisAlignedBox aabb;
//		//updateBox(aabb);
//		// Create a WireBoundingBox if needed.
//		//if (mWireBoundingBox == NULL)
//		//{
//		//	mWireBoundingBox = MG_NEW Ogre::WireBoundingBox();
//		//}
//		//mWireBoundingBox->setupBoundingBox(aabb);
//
//
//		Ogre::RenderSystem* mRenderSystem = OgreMainInterface::root->getRenderSystem();
///*
//		// set-up matrices
//		//mRenderSystem->_setWorldMatrix(Ogre::Matrix4::IDENTITY);
//		//mRenderSystem->_setViewMatrix(Ogre::Matrix4::IDENTITY);
//		//mRenderSystem->_setProjectionMatrix(Ogre::Matrix4::IDENTITY);
//
//		// initialise render settings
//		mRenderSystem->setLightingEnabled(false);
//		//mRenderSystem->_setDepthBufferParams(false, false);
//		mRenderSystem->_setDepthBias(0, 0);
//		mRenderSystem->_setCullingMode(Ogre::CULL_NONE);
//		mRenderSystem->_setFog(Ogre::FOG_NONE);
//		//mRenderSystem->_setColourBufferWriteEnabled(true, true, true, true);
//		mRenderSystem->unbindGpuProgram(Ogre::GPT_FRAGMENT_PROGRAM);
//		mRenderSystem->unbindGpuProgram(Ogre::GPT_VERTEX_PROGRAM);
//		//mRenderSystem->setShadingType(Ogre::SO_GOURAUD);
//
//		// initialise texture settings
//		//mRenderSystem->_setTextureCoordCalculation(0, Ogre::TEXCALC_NONE);
//		//mRenderSystem->_setTextureCoordSet(0, 0);
//		//mRenderSystem->_setTextureUnitFiltering(0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_NONE);
//		//mRenderSystem->_setTextureAddressingMode(0, mTextureAddressMode);
//		//mRenderSystem->_setTextureMatrix(0, Ogre::Matrix4::IDENTITY);
//
//		//mRenderSystem->_setAlphaRejectSettings(Ogre::CMPF_ALWAYS_PASS, 0, false);
//
//		IDirect3DDevice9* pd3dDevice = D3D9RenderSystem::getActiveD3D9Device();
//		pd3dDevice->SetTexture(0, NULL);
//		pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
//		pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
//		pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFFFFFFF);
//		pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TFACTOR);
//		pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
//		pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
//		pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
//		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
//		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
//		//LayerBlendModeEx lb;
//		//lb.blendType = LBT_COLOUR;
//		//lb.operation = LBX_SOURCE1;
//		////lb.colourArg1 = ColourValue::White;
//		//
//		//mRenderSystem->_setTextureBlendMode(0, lb);
//
//		//LayerBlendModeEx lbAlpha;
//		//lbAlpha.blendType = LBT_ALPHA;
//		//lbAlpha.operation = LBX_SOURCE1;
//		//mRenderSystem->_setTextureBlendMode(0, lbAlpha);
//
//		//mRenderSystem->_disableTextureUnitsFrom(1);
//
//		// enable alpha blending
//		//mRenderSystem->_setSceneBlending(Ogre::SBF_SOURCE_ALPHA, Ogre::SBF_ONE_MINUS_SOURCE_ALPHA);
//
//		// always use wireframe
//		// TODO: add option to enable wireframe mode in platform
//		mRenderSystem->_setPolygonMode(Ogre::PM_WIREFRAME);
//*/
//
//		RenderOperation op;
//		mWireBoundingBox->getRenderOperation(op);
//		mRenderSystem->_render(op);
//		//DX_EndPerfEvent();
//	}
}

