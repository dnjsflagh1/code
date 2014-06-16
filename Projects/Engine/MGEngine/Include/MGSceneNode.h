/******************************************************************************/
#ifndef _MGSCENENODE_H_
#define _MGSCENENODE_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISceneNode.h"
#include "LinedState.h"
#include "OgreAnimationState.h"

/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	//游戏场景节点
	/******************************************************************************/
    class MGSceneNode : public ISceneNode 
	{
	public:
        MGSceneNode( Ogre::SceneNode* parent, Scene* scene );
        virtual ~MGSceneNode();

        /// 得到场景对象
        virtual IScene*     				getScene();

        ////////////////////////////////////////////////////////////////////////////////////////


        /// 临时设置可见性
                void        				tempSetVisible(Bool visible) ;
                void        				revertVisible() ;

        /// 设置可见性
        virtual void        				setVisible(Bool visible) ;
        /// 得到可见性 
        virtual Bool        				getVisible();

        ////////////////////////////////////////////////////////////////////////////////////////


        /// 设置位置坐标.
        virtual void        				setPosition(Vec3& pos) ;
        /// 得到位置坐标.
		virtual void        				getPosition(Vec3& pos) ;
		/// 设置初始位置偏移. 
		virtual void						setPositionOffset(const Vec3& offset);
		/// 获取初始位置偏移. 
		virtual const Vec3&					getPositionOffset() const;
		/// 获得屏幕坐标
		virtual void						getScreenPosition(Vec2& screenPos);
		/// 得到位置变化标签. 
		virtual Bool						getPositionDirty();
        /// 清除位置变化标签. 
        virtual void						clearPositionDirty();

        /// 相对位移.
        virtual void        				translate(Vec3& d, TransformSpace relativeTo = TS_PARENT) ;


        ////////////////////////////////////////////////////////////////////////////////////////


        /// 设置缩放.
        virtual void        				setScale(Vec3& scale) ;
        /// 得到缩放.
		virtual void        				getScale(Vec3& scale) ;
		/// 设置初始缩放. 
		virtual void						setInitScale(const Vec3& scale);
		/// 获取初始缩放. 
		virtual const Vec3&					getInitScale() const;
		/// 得到缩放变化标签. 
		virtual Bool        				getScaleDirty();
        /// 清除缩放变化标签. 
        virtual void       			 		clearScaleDirty() ;

        ////////////////////////////////////////////////////////////////////////////////////////


        /// 设置4元数.
        virtual void       			 		setOrientation(Qua& quaternion) ;
        /// 得到4元数.
		virtual void       			 		getOrientation(Qua& quaternion) ;
		/// 得到4元数变化标签.  
		virtual Bool						getOrientationDirty();
        /// 得到4元数变化标签.  
        virtual void        				clearOrientationDirty();


        ////////////////////////////////////////////////////////////////////////////////////////

        /// 设置方向.
        virtual void        				setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) ;
        /// 得到方向.
		virtual void        				getDirection(Vec3& vec);

        /// 朝向某点.
        virtual void        				lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD) ;

        /// roll旋转.
		virtual void        				roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
        /// pitch旋转.
		virtual void        				pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;
        /// yaw旋转.
		virtual void        				yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL) ;

        /// 沿着某轴方向旋转.
		virtual void						rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL) ;


		////////////////////////////////////////////////////////////////////////////////////////

		virtual void						playNodeAnimation( Str8 name, Bool isLoop = false, Bool isReverse = false );

		virtual void						updateNodeAnimations(Flt delta);

		virtual void						clearNodeAnimations();

        ////////////////////////////////////////////////////////////////////////////////////////

        /// 贴近地面
        virtual void        				stickTerrain() ;
        virtual void        				setStickTerrainEnable(Bool enable);

        ////////////////////////////////////////////////////////////////////////////////////////


        /// 更新
        void                				update( Flt delta );

	    ////////////////////////////////////////////////////////////////////////////////////////

	public:

        Ogre::SceneNode*					getOgreSceneNode();

    protected:

        /// 设置本地坐标中当前面对的方向, dir为local transform, 默认Z轴
        void								setLocalDirectionVector( const Vector3& dir );
        /// 得到本地坐标中当前面对的方向
        const Vector3&						getLocalDirectionVector();
        /// 得到世界坐标中当前面对的方向 
        const Vector3&						getWorldDirectionVector();
        
    protected:

        Scene*								mScene;

        ///Ogre的摄像机节点对象
		Ogre::SceneNode*					mOgreParentSceneNode;
        ///Ogre的摄像机节点对象
		Ogre::SceneNode*					mOgreSceneNode;

        /////////////////////////////////////////////////////////////////////

		Bool 								mPositionDirty;
		Bool 								mScaleDirty;
		Bool 								mOrientationDirty;


        /////////////////////////////////////////////////////////////////////

        //正朝向
        Vector3 							mLocalDirectionVector;
        Vector3 							mWorldDirectionNormalisedVector;

        /// 地面射线方向
        Vec3								mTerrainRayDir1;
        /// 地面射线方向
        Vec3								mTerrainRayDir2;
        
        /////////////////////////////////////////////////////////////////////

		//策划定义的初始位置偏移
		Vec3								mPositionOffset;

		//策划定义的初始大小缩放
		Vec3								mInitScale;

		/////////////////////////////////////////////////////////////////////

        // 可见度
        Bool 								mVisible;

        // 是否贴地
        Bool 								mStickTerrainEnable;

        // 实体列表
		std::vector<IEntity*>				mEntityList;

        /////////////////////////////////////////////////////////////////////

		/// 动画列表 
		typedef std::map<Str, AnimationState*> AnimationMap;
		typedef AnimationMap::iterator AnimationMap_iter;
		typedef AnimationMap::const_iterator AnimationMap_constIter;
		AnimationMap						mAnimations;

		/////////////////////////////////////////////////////////////////////

	};
}

/******************************************************************************/

#endif
