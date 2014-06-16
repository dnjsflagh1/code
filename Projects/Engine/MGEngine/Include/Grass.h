#ifndef __GRASS_H__
#define __GRASS_H__

#include "EnginePreqs.h"
#include "ITree.h"
#include "ISceneNode.h"
#include "OgreWireBoundingBox.h"

namespace MG
{

#define INVALID_ROWCOL	INT_MAX
#define INVALID_GRASS	0xFFFFFFFF
	/******************************************************************************/
	// 植被OGRE对象
	/******************************************************************************/
	class GrassMovable : public MovableObject
	{
	public:
		virtual const String& getMovableType(void) const;
		virtual const AxisAlignedBox& getBoundingBox(void) const ;
		virtual const AxisAlignedBox& getWorldBoundingBox(bool derive = false) const;
		virtual bool isInScene() const { return true; };
		virtual Real getBoundingRadius(void) const ;
		virtual void _updateRenderQueue(RenderQueue* queue);
		virtual void visitRenderables(Renderable::Visitor* visitor, bool debugRenderables = false);

	protected:

		AxisAlignedBox mAABB;
	};


	/******************************************************************************/
	// 植被对象
	/******************************************************************************/

	class Grass : public IGrass, public ISceneNode
	{
	public:

		Grass( Scene* scene, TreeManager* mgr, SpeedTreeSystem* speedTreeSys, 
			UInt grassID, const Vec3& vPos, Flt w, Flt h );
		virtual ~Grass();

	public:
		///初始化
		bool								init(Flt w, Flt h);
		/// 得到类型
		virtual SceneObjectTypes            getType();
		/// 得到空间节点
		virtual ISceneNode*                 getSceneNode();

		virtual UInt						getBaseGrassId() { return mGrassID;}

		virtual Flt							width();

		virtual void						width(Flt w);

		virtual Flt							height();

		virtual void						height(Flt h);
		//virtual Int							getInstanceId() { return mInstanceID; }

		//void								setInstanceId(Int id) { mInstanceID = id; }

		MovableObject*						getOgreMovable();

		Int									row() const { return mRow; }

		Int									col() const { return mCol; }

		UInt								grassID() const { return mGrassIndex; }
		
		void								grassID(UInt grassId) { mGrassIndex = grassId; }

	protected:

		void								createOgreMovable();
		void								destroyOgreMovable();

	public:

		/// 得到所属场景
		virtual IScene*                     getScene();

		/// 设置可见性
		virtual void                        setVisible(Bool visible) ;
		/// 得到可见性
		virtual Bool                        getVisible() ;

		/////////////////////////////////////////////////////////////////////////////////////

		/// 设置位置坐标.
		virtual void                        setPosition(Vec3& vPos) ;
		/// 得到位置坐标.
		virtual void                        getPosition(Vec3& vPos) ;
		/// 设置初始位置偏移. 
		virtual void						setPositionOffset(const Vec3& offset) { mPositionOffset = offset; };
		/// 获取初始位置偏移. 
		virtual const Vec3&					getPositionOffset() const { return mPositionOffset; };
		/// 得到屏幕坐标
		virtual void                        getScreenPosition(Vec2& outPos) ;

		/// 得到位置变化标签. 
		virtual Bool                        getPositionDirty();
		/// 清除位置变化标签. 
		virtual void                        clearPositionDirty();

		/// 相对位移.
		virtual void                        translate(Vec3& d, TransformSpace relativeTo = TS_PARENT) ;

		/////////////////////////////////////////////////////////////////////////////////////

		/// 设置缩放.
		virtual void                        setScale(Vec3& scale) ;
		/// 得到缩放.
		virtual void                        getScale(Vec3& scale) ;
		/// 设置初始缩放. 
		virtual void						setInitScale(const Vec3& scale) { mInitScale = scale; };
		/// 获取初始缩放. 
		virtual const Vec3&					getInitScale() const { return mInitScale; };
		/// 得到缩放变化标签. 
		virtual Bool                        getScaleDirty();
		/// 清除缩放变化标签. 
		virtual void                        clearScaleDirty() ;

		/////////////////////////////////////////////////////////////////////////////////////

		/// 设置4元数.
		virtual void                        setOrientation(Qua& quaternion) ;
		/// 得到4元数.
		virtual void                        getOrientation(Qua& quaternion) ;
		/// 得到4元数变化标签.  
		virtual Bool                        getOrientationDirty();
		/// 得到4元数变化标签.  
		virtual void                        clearOrientationDirty();

		/// 设置方向.
		virtual void                        setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) ;
		/// 得到方向.
		virtual void                        getDirection(Vec3& vec);

		/// 朝向某点.
		virtual void                        lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD) ;

		/// roll旋转.
		virtual void                        roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
		/// pitch旋转.
		virtual void                        pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
		/// yaw旋转，树的旋转不能为负
		virtual void                        yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;

		/// 沿着某轴方向旋转.
		virtual void                        rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL) ;

		/////////////////////////////////////////////////////////////////////////////////////

		/// 贴近地面
		virtual void                        stickTerrain();

		//void								updateBox(AxisAlignedBox& aabb);

		//void								renderBox();

		const AxisAlignedBox&				getWorldBoundingBox(void);

		const AxisAlignedBox&				getBoundingBox(void) const { return mBoundingBox; }

	protected:

		

	private:

		GrassMovable*		mGrassMovable;

		UInt				mGrassID;
		
		Int					mRow;

		Int					mCol;

		UInt				mGrassIndex;

		AxisAlignedBox		mBoundingBox;

		AxisAlignedBox		mWorldAABB;
		
		Vec3				mPos;
		
		Vec3				mScale;

		//策划定义的初始位置偏移
		Vec3				mPositionOffset;
		//策划定义的初始大小缩放
		Vec3				mInitScale;

		Scene*				mScene;

		TreeManager*		mMgr;

		SpeedTreeSystem*	mSpeedTreeSystem;
	};
}
#endif