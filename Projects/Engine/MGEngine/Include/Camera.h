/******************************************************************************/
#ifndef _CAMERA_H_
#define _CAMERA_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ICamera.h"
#include "LinedState.h"
/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//摄像机
	/******************************************************************************/
    class Camera : public ICamera
	{
        friend class Scene;

	public:
        Camera(CChar* camName, Scene* scene);
        virtual ~Camera();

        /// 更新
        void                        update( Flt delta );

        /// 得到类型
        virtual SceneObjectTypes    getType();

        /// 设置和得到Fov 
        virtual void                setFov(Flt degree) ;
        virtual Flt                 getFov() ;

		/// 设置远近横截平面
		virtual void				setFarClipDistance(Flt farDist) ;
		virtual void				setNearClipDistance(Flt nearDist) ;

        /// 世界坐标点转换为屏幕坐标点
        virtual void	            worldPointToScreenPoint(const Vec3& worldPos, Vec2& screenPos) ;

        /// 得到世界坐标点离摄像机位置
        virtual Flt	                getWorldDistance(const Vec3& worldPos) ;

		/// 得到鼠标点转换为世界射线值
		virtual void                getMouseViewportRay(Vec3& pos, Vec3& dir, Vec2 offset=Vec2(0,0));

        /// 得到场景对象
        virtual IScene*             getScene() {return NULL;};

        ///////////////////////////////////////////////////////////////////////////

		/// 设置可见性 
		virtual void                setVisible(Bool visible);
        /// 得到可见性 
        virtual Bool                getVisible();

        ///////////////////////////////////////////////////////////////////////////

        /// 关注某一点
        virtual void                focusPosition(Vec3& pos);

		/// 设置位置坐标. 
		virtual void                setPosition(Vec3& pos);
		/// 得到位置坐标. 
		virtual void                getPosition(Vec3& pos) ;
		/// 设置初始位置偏移. 
		virtual void				setPositionOffset(const Vec3& offset) { mPositionOffset = offset;};
		/// 获取初始位置偏移. 
		virtual const Vec3&			getPositionOffset() const {return mPositionOffset;};
		/// 得到位置变化标签. 
		virtual Bool                getPositionDirty(){return mPositionDirty;};

        /// 相对位移. 
        virtual void                translate(Vec3& d, TransformSpace relativeTo = TS_LOCAL) ;

        ///////////////////////////////////////////////////////////////////////////

		/// 设置缩放. 
		virtual void                setScale(Vec3& scale) ;
		/// 得到缩放. 
		virtual void                getScale(Vec3& scale) ;
		/// 设置初始缩放. 
		virtual void				setInitScale(const Vec3& scale) { mInitScale = scale; };
		/// 获取初始缩放. 
		virtual const Vec3&			getInitScale() const { return mInitScale; };
		/// 得到缩放变化标签. 
		virtual Bool                getScaleDirty(){return mScaleDirty;};

        ///////////////////////////////////////////////////////////////////////////

		/// 设置4元数. 
		virtual void                setOrientation(Qua& quaternion) ;
		/// 得到4元数. 
		virtual void                getOrientation(Qua& quaternion) ;
		/// 得到4元数变化标签.  
		virtual Bool                getOrientationDirty(){return mOrientationDirty;};

		/// 设置方向. 
		virtual void                setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) ;
		/// 得到方向. 
		virtual void                getDirection(Vec3& vec);

		/// 朝向某点. 
		virtual void                lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD);

		/// roll旋转. 
		virtual void                roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
		/// pitch旋转. 
		virtual void                pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
		/// yaw旋转. 
		virtual void                yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL);
        /// 得到yaw旋转 
        virtual Flt                 getYaw();
        /// 得到pitch旋转 
        virtual Flt                 getPitch();

		/// 沿着某轴方向旋转. 
		virtual void                rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL);

        ///////////////////////////////////////////////////////////////////////////

        /// 贴近地面
        virtual void                stickTerrain() {};

        ///////////////////////////////////////////////////////////////////////////

        /// 得到Ogre摄像机对象
        Ogre::Camera*               getOgreCamera(){return mOgreCamera;};

    protected:
        ///摄像机节点对象
		MGSceneNode* mSceneNode;
        /// Ogre摄像机对象
        Ogre::Camera* mOgreCamera;
        /// 所属场景对象
        Scene* mScene;
        //LinedStateManager mLinedStateManager;

        /////////////////////////////////////////////////////////////////////

        Bool 								mPositionDirty;
        Bool 								mScaleDirty;
        Bool 								mOrientationDirty;

		//策划定义的初始位置偏移
		Vec3								mPositionOffset;
		//策划定义的初始大小缩放
		Vec3								mInitScale;
	};
	
}

/******************************************************************************/

#endif
