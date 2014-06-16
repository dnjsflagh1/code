
/******************************************************************************/
#ifndef __TREE_H__
#define __TREE_H__
/******************************************************************************/

#include "EnginePreqs.h"
#include "ITree.h"
#include "ISceneNode.h"
#include "OgreWireBoundingBox.h"
#include "Forest/Forest.h"

namespace MG
{


	/******************************************************************************/
	// 植被OGRE对象
	/******************************************************************************/
	class TreeMovable : public MovableObject
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
	// SpeedTree Instance
	/******************************************************************************/

	class TreeInstance : public SpeedTree::CInstance
	{
	
	};

    /******************************************************************************/
    // 植被对象
    /******************************************************************************/

    class Tree : public ITree, public ISceneNode
    {
    public:
		Tree( Scene* scene, TreeManager* mgr, MG::SpeedTreeSystem* speedTreeSys, 
			UInt baseTreeID, CChar* pBaseTreeName);

        virtual ~Tree();
        
    public:

        /// 得到类型
        virtual SceneObjectTypes            getType();
        /// 得到空间节点
        virtual ISceneNode*                 getSceneNode();

		virtual UInt						getBaseTreeId() { return mTreeModelID;}

		virtual	void						setReflect(Bool bReflect);

		virtual Bool						isNeedReflect();

		//virtual Int							getInstanceId() { return mInstanceID; }

		//void								setInstanceId(Int id) { mInstanceID = id; }

		MovableObject*						getOgreMovable();
		
		Bool								init(const Vec3& pos);

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
        virtual void                        setPosition(Vec3& pos) ;
        /// 得到位置坐标.
        virtual void                        getPosition(Vec3& pos) ;
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

        // 创建实体
		Bool	createInstance( CChar* pBaseTreeName, const Vec3& pos );

        // 销毁实体
        Bool    destroyInstance();

    private:

		TreeMovable*		mTreeMovable;

		UInt				mTreeModelID;

		std::string			mBaseTreeName;

		TreeInstance		mTreeInstance;
		//Int					mInstanceID;

		AxisAlignedBox		mBoundingBox;

		AxisAlignedBox		mWorldAABB;

		//Ogre::WireBoundingBox*	mWireBoundingBox;

        Scene*				mScene;

        TreeManager*		mMgr;

        SpeedTreeSystem*	mSpeedTreeSystem;

		//策划定义的初始位置偏移
		Vec3				mPositionOffset;
		//策划定义的初始大小缩放
		Vec3				mInitScale;
    };
}
#endif