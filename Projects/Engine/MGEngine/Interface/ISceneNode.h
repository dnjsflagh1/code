/******************************************************************************/
#ifndef _ISCENENODE_H_
#define _ISCENENODE_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //
    /******************************************************************************/
    class ISceneNodeLisitener
    {
    public:

        virtual void    onRemove(ISceneNode* node){};

        virtual void    onPositionChanged( Vec3& oldPos, Vec3 newPos ){};
        virtual void    onOrientationChanged( Qua& oldQua, Qua newQua ){};
        virtual void    onScaleChanged( Vec3& oldScale, Vec3 newPosScale ){};
        virtual void    onVisibleChanged( Bool visible ){};
    };


    /******************************************************************************/
	//游戏场景中节点
	/******************************************************************************/
	class ISceneNode
	{
	public:
        /// 空间类型
        enum TransformSpace
        {
            /// Transform is relative to the local space
            TS_LOCAL,
            /// Transform is relative to the space of the parent node
            TS_PARENT,
            /// Transform is relative to world space
            TS_WORLD
        };
	public:

        //////////////////////////////////////////////////////////////////////////////////////////////////

        virtual ~ISceneNode()
        {
            notifyRemove();
        }
        
        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 得到所属场景
        virtual IScene*                 getScene() = 0;
        /// 设置可见性 
		virtual void                    setVisible(Bool visible) = 0;
        /// 得到可见性 
        virtual Bool                    getVisible() = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 设置位置坐标. 
        virtual void                    setPosition(Vec3& pos) = 0;
        /// 得到位置坐标. 
		virtual void                    getPosition(Vec3& pos) = 0;
		/// 设置初始位置偏移. 
		virtual void                    setPositionOffset(const Vec3& offset) = 0;
		/// 获取初始位置偏移. 
		virtual const Vec3&				getPositionOffset() const = 0;
		/// 获得屏幕坐标
		virtual void					getScreenPosition(Vec2& outPos){};
		/// 得到位置变化标签. 
		virtual Bool                    getPositionDirty() = 0;
		/// 清除位置变化标签. 
		virtual void                    clearPositionDirty(){};

        /// 相对位移. 
        virtual void                    translate(Vec3& d, TransformSpace relativeTo = TS_LOCAL) = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

        /// 设置缩放. 
        virtual void                    setScale(Vec3& scale) = 0;
        /// 得到缩放. 
		virtual void                    getScale(Vec3& scale) = 0;
		/// 设置初始缩放. 
		virtual void                    setInitScale(const Vec3& scale) = 0;
		/// 获取初始缩放. 
		virtual const Vec3&				getInitScale() const = 0;
		/// 得到缩放变化标签. 
		virtual Bool                    getScaleDirty() = 0;
        /// 清除缩放变化标签. 
        virtual void                    clearScaleDirty(){};


        //////////////////////////////////////////////////////////////////////////////////////////////////


        /// 设置4元数. 
        virtual void                    setOrientation(Qua& quaternion) = 0;
        /// 得到4元数. 
		virtual void                    getOrientation(Qua& quaternion) = 0;
        /// 得到4元数变化标签.  
		virtual Bool                    getOrientationDirty() = 0;
        /// 清除4元数变化标签. 
        virtual void                    clearOrientationDirty(){};

        /// 设置方向. 
        virtual void                    setDirection(Vec3& vec, TransformSpace relativeTo = TS_WORLD) = 0;
        /// 得到方向. 
		virtual void                    getDirection(Vec3& vec) = 0;

        /// 朝向某点. 
        virtual void                    lookAt(Vec3& targetPoint, TransformSpace relativeTo = TS_WORLD) = 0;


        //////////////////////////////////////////////////////////////////////////////////////////////////


        /// roll旋转. 
		virtual void                    roll( Flt angle, TransformSpace relativeTo = TS_LOCAL) = 0;
        /// pitch旋转. 
		virtual void                    pitch( Flt angle, TransformSpace relativeTo = TS_LOCAL) = 0;
        /// yaw旋转. 
		virtual void                    yaw( Flt angle, TransformSpace relativeTo = TS_LOCAL) = 0;
        /// 得到yaw旋转 
        virtual Flt                     getYaw() {return 0;};
        /// 得到pitch旋转 
        virtual Flt                     getPitch() {return 0;};
        
        /// 沿着某轴方向旋转. 
		virtual void                    rotate( Vec3& axis, Flt& angle, TransformSpace relativeTo = TS_LOCAL) = 0;

        //////////////////////////////////////////////////////////////////////////////////////////////////

		virtual void					playNodeAnimation( Str8 name, Bool isLoop = false, Bool isReverse = false ){};

		//////////////////////////////////////////////////////////////////////////////////////////////////


        /// 贴近地面
        virtual void                    stickTerrain() = 0;
        /// 设置贴近地面
        virtual void                    setStickTerrainEnable(Bool enable){};

        //////////////////////////////////////////////////////////////////////////////////////////////////

        // 得到状态管理器, 需要子类更新状态管理器
        LinedStateManager*              getLinedStateManager() { return &mLinedStateManager; };

        //////////////////////////////////////////////////////////////////////////////////////////////////

        // 增加监听器
        void                            addSceneNodeLisitener( Str name, ISceneNodeLisitener* lisitener )
        {
            mLisiteners[name] = lisitener;
        }
        
        // 移除监听器
        void                            removeSceneNodeLisitener( Str name )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.find( name );
            if ( iter!=mLisiteners.end() )
            {
                mLisiteners.erase( iter );
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////

    protected:

        // 通知事件，子类调用
        void    notifyPositionChanged( Vec3& oldPos, Vec3 newPos )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onPositionChanged( oldPos, newPos );
            }
        }
        void    notifyOrientationChanged( Qua& oldQua, Qua newQua )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onOrientationChanged( oldQua, newQua );
            }
        }
        void    notifyScaleChanged( Vec3& oldScale, Vec3 newPosScale )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onScaleChanged( oldScale, newPosScale );
            }
        }
        void    notifyVisibleChanged( Bool visible )
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onVisibleChanged( visible );
            }
        }
        void    notifyRemove()
        {
            std::map<Str,ISceneNodeLisitener*>::iterator iter = mLisiteners.begin();
            for ( ;iter!=mLisiteners.end(); iter++)
            {
				if ( iter->second )
					iter->second->onRemove(this);
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////

    protected:

        LinedStateManager                   mLinedStateManager;

        std::map<Str,ISceneNodeLisitener*>  mLisiteners;

	};


}

/******************************************************************************/
#endif
