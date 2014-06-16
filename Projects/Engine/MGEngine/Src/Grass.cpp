#include "stdafx.h"
#include "TreeManager.h"
#include "scene.h"
#include "EngineMain.h"
#include "Ogre.h"
#include "OgreD3D9RenderSystem.h"
#include "Grass.h"
#include "SpeedTreeSystem.h"

namespace MG
{
    #define GRASSMOVABLE_POOL_CATEGORY 3312

	//---------------------------------------------------------------------------------------------
	const String& GrassMovable::getMovableType(void) const
	{
		return "Grass";
	}

	//---------------------------------------------------------------------------------------------
	const AxisAlignedBox& GrassMovable::getBoundingBox(void) const 
	{
		ISceneObject* sceneObject = any_cast<ISceneObject*>( getUserAny() ) ;
		if ( sceneObject && sceneObject->getType() == SOT_GRASS )
		{
			Grass* grass = dynamic_cast<Grass*>(sceneObject);
			if ( grass )
				return grass->getBoundingBox();
		}

		return AxisAlignedBox::BOX_NULL;
	}

	//---------------------------------------------------------------------------------------------
	const AxisAlignedBox& GrassMovable::getWorldBoundingBox(bool derive/* = false*/) const
	{
		ISceneObject* sceneObject = any_cast<ISceneObject*>( getUserAny() ) ;
		if ( sceneObject && sceneObject->getType() == SOT_GRASS )
		{
			Grass* grass = dynamic_cast<Grass*>(sceneObject);
			if ( grass )
				return grass->getWorldBoundingBox();
		}

		return AxisAlignedBox::BOX_NULL;
	}

	//---------------------------------------------------------------------------------------------
	Real GrassMovable::getBoundingRadius(void) const
	{
		return 1;
	}

	//---------------------------------------------------------------------------------------------
	void GrassMovable::_updateRenderQueue(RenderQueue* queue)
	{

	}

	//---------------------------------------------------------------------------------------------
	void GrassMovable::visitRenderables(Renderable::Visitor* visitor, bool debugRenderables)
	{

	}

	//---------------------------------------------------------------------------------------------
	Grass::Grass( Scene* scene, TreeManager* mgr, SpeedTreeSystem* speedTreeSys, 
		UInt grassID, const Vec3& vPos, Flt w, Flt h)
		:mScene(scene)
		,mMgr(mgr)
		,mSpeedTreeSystem(speedTreeSys)
		,mGrassID(grassID)
		,mGrassMovable(NULL)
		,mGrassIndex(INVALID_GRASS)
		,mPos(vPos)
		,mRow(INVALID_ROWCOL)
		,mCol(INVALID_ROWCOL)
		,mScale(Vec3(1.f, 1.f, 1.f))
	{
		mPositionOffset = Vec3(0,0,0);
		mInitScale = Vec3(1,1,1);
	}

	//--------------------------------------------------------------------------------------------
	bool Grass::init(Flt w, Flt h)
	{
		GrassDeclaration* pDecl = mMgr->getGrassDeclarationByIndex(mGrassID);
		if (pDecl == NULL)
		{
			return false;
		}
		Bool bRet = mSpeedTreeSystem->addGrass(pDecl->uImageId, mPos, w, h, pDecl->fRTWindWeight, pDecl->fLTWindWeight,
			pDecl->fLBWindWeight, pDecl->fRBWindWeight, mGrassIndex, mRow, mCol);

		if (!bRet)
			return false;

		mBoundingBox.setExtents(Vector3(-1.f, 0.f, -1.f), Vector3(1.f, 2.f, 1.f));

		createOgreMovable();

		return bRet;
	}

	//---------------------------------------------------------------------------------------------
	Grass::~Grass()
	{
		if (mRow != INVALID_ROWCOL && mCol != INVALID_ROWCOL)
		{
			mSpeedTreeSystem->deleteGrass(mRow, mCol, mGrassIndex);
			destroyOgreMovable();
		}
	}

	//---------------------------------------------------------------------------------------------
	SceneObjectTypes Grass::getType()
	{
		return SOT_GRASS;
	}

	//---------------------------------------------------------------------------------------------
	ISceneNode* Grass::getSceneNode()
	{
		return this;
	}

	//---------------------------------------------------------------------------------------------
	MovableObject*	Grass::getOgreMovable()
	{
		return mGrassMovable;
	}

	//---------------------------------------------------------------------------------------------
	void Grass::createOgreMovable()
	{
        mGrassMovable = MG_POOL_NEW_T(GrassMovable, GRASSMOVABLE_POOL_CATEGORY)();
		//mGrassMovable = MG_NEW GrassMovable;

		//设置绑定实体对象的管理者
		mGrassMovable->setUserAny( Any( (ISceneObject*) this) );
		////设置查询标志位
		mGrassMovable->setQueryFlags (Scene::getQueryMask (this->getType()) );
	}

	//---------------------------------------------------------------------------------------------
	void Grass::destroyOgreMovable()
	{
        MG_POOL_DELETE_T( mGrassMovable ,GrassMovable, GRASSMOVABLE_POOL_CATEGORY);
		//MG_SAFE_DELETE(mGrassMovable);
	}

	//---------------------------------------------------------------------------------------------
	IScene* Grass::getScene()
	{
		return mScene;
	}

	//---------------------------------------------------------------------------------------------
	void Grass::setVisible(Bool visible)
	{

	}

	//---------------------------------------------------------------------------------------------
	Bool Grass::getVisible() 
	{
		return true;
	}

	//---------------------------------------------------------------------------------------------
	Flt	Grass::width()
	{
		return mSpeedTreeSystem->getGrassW(mRow, mCol, mGrassIndex);
	}

	//---------------------------------------------------------------------------------------------
	void Grass::width(Flt w)
	{
		GrassDeclaration* pDecl = mMgr->getGrassDeclarationByIndex(mGrassID);
		if (pDecl == NULL)
		{
			return;
		}
		Flt fStandW = pDecl->fWidth;
		if (fStandW == 0.f)
		{
			fStandW = 1.f;
		}
		if (mSpeedTreeSystem->setGrassW(mRow, mCol, mGrassIndex, w))
		{
			mScale.x = w / fStandW;
		}
	}

	//---------------------------------------------------------------------------------------------
	Flt Grass::height()
	{
		return mSpeedTreeSystem->getGrassH(mRow, mCol, mGrassIndex);
	}

	//---------------------------------------------------------------------------------------------
	void Grass::height(Flt h)
	{
		GrassDeclaration* pDecl = mMgr->getGrassDeclarationByIndex(mGrassID);
		if (pDecl == NULL)
		{
			return;
		}
		Flt fStandH = pDecl->fHeight;
		if (fStandH == 0.f)
		{
			fStandH = 1.f;
		}
		if (mSpeedTreeSystem->setGrassH(mRow, mCol, mGrassIndex, h))
		{
			mScale.y = h / fStandH;
		}
	}

	//---------------------------------------------------------------------------------------------
	void Grass::setPosition(Vec3& vPos) 
	{
		if (mSpeedTreeSystem->setGrassPosition(mRow, mCol, mGrassIndex, vPos))
		{
			mPos = vPos;
		}
		else
		{
			//跨格子
		}
	}

	//---------------------------------------------------------------------------------------------
	void Grass::getPosition(Vec3& vPos)
	{
		vPos = mPos;
	}

	//---------------------------------------------------------------------------------------------
	void Grass::getScreenPosition(Vec2& outPos) 
	{
		Vec3 worldPos;
		getPosition(worldPos);

		IScene* pScene = getScene();
		ICamera* pCamera = pScene->getActiveCamera();
		pCamera->worldPointToScreenPoint(worldPos, outPos);
	}

	//---------------------------------------------------------------------------------------------
	Bool Grass::getPositionDirty()
	{
		return true;
	}

	//---------------------------------------------------------------------------------------------
	void Grass::clearPositionDirty()
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::translate(Vec3& d, TransformSpace relativeTo)
	{
		if (mSpeedTreeSystem->setGrassPosition(mRow, mCol, mGrassIndex, mPos))
		{
			mPos += d;
		}
	}

	//---------------------------------------------------------------------------------------------
	void Grass::setScale(Vec3& scale)
	{
		TreeManager* pMgr = mScene->getTreeManager();
		if (pMgr)
		{
			GrassDeclaration* pDecl = pMgr->getGrassDeclarationByIndex(mGrassID);
			if (pDecl != NULL)
			{
				Flt w = pDecl->fWidth * scale.x;
				Flt h = pDecl->fHeight * scale.y;
				if (mSpeedTreeSystem->setGrassSize(mRow, mCol, mGrassIndex, w, h))
				{
					mScale = scale;
				}
			}
		}
	}

	//---------------------------------------------------------------------------------------------
	void Grass::getScale(Vec3& scale)
	{
		scale = mScale;
	}

	//---------------------------------------------------------------------------------------------
	Bool Grass::getScaleDirty()
	{
		return true;
	}

	//---------------------------------------------------------------------------------------------
	void Grass::clearScaleDirty()
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::setOrientation(Qua& quaternion)
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::getOrientation(Qua& quaternion)
	{

	}

	//---------------------------------------------------------------------------------------------
	Bool Grass::getOrientationDirty()
	{
		return true;
	}

	//---------------------------------------------------------------------------------------------
	void Grass::clearOrientationDirty()
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::setDirection(Vec3& vec, TransformSpace relativeTo)
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::getDirection(Vec3& vec)
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::lookAt(Vec3& targetPoint, TransformSpace relativeTo)
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::roll( Flt angle, TransformSpace relativeTo)
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::pitch( Flt angle, TransformSpace relativeTo)
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::yaw( Flt angle, TransformSpace relativeTo)
	{

	}

	//---------------------------------------------------------------------------------------------
	void Grass::rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo)
	{

	}		

	//---------------------------------------------------------------------------------------------
	void Grass::stickTerrain()
	{

	}

	//---------------------------------------------------------------------------------------------
	const AxisAlignedBox& Grass::getWorldBoundingBox(void)
	{
		mWorldAABB = mBoundingBox;
		
		//float scale = mTreeInstance.GetScale();

		Vector3 vMax = mBoundingBox.getMaximum() + Vector3(mPos.x, mPos.y, mPos.z);
		Vector3 vMin = mBoundingBox.getMinimum() + Vector3(mPos.x, mPos.y, mPos.z);

		mWorldAABB.setExtents(vMin, vMax);

		return mWorldAABB;
	}
}