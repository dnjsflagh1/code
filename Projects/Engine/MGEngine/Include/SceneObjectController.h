/******************************************************************************/
#ifndef _SCENEOBJECTCONTROLLER_H_
#define _SCENEOBJECTCONTROLLER_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "ISceneObjectController.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	//游戏场景对象控制器接口
	/******************************************************************************/
	class SceneObjectController : public ISceneObjectController, public ISceneNodeLisitener
	{
        friend class Scene;
	public:
		SceneObjectController(Scene* scene);
		~SceneObjectController();

		/// 更新
		void                    update( Flt delta );

		/// 设置是否控制 
		virtual void            setEnable(Bool enable);
		/// 是否已经控制 
		virtual Bool            getlEnable();

		/// 关闭选中操作
		virtual void			setFocusEnable( Bool enable );
		/// 获取是否选中操作
		virtual Bool			getFocusEnable() { return mFocusEnable; };

		/// 设置控制对象 
		virtual void            setFocus( ISceneObject* obj );
		/// 得到控制对象 
		virtual ISceneObject*   getFocus();
		/// 忽略选中的对象
		virtual void			setIgnoreFocus( ISceneObject* obj );

		/// 清除框选对象组
		virtual void			clearMultiFocus( Bool objectDeleted = false );
		/// 获取框选对象组
		virtual void			getMultiFocusList( std::vector<ISceneObject*>& objectList );
		/// 进行框选操作
		virtual void			multiSelect( RectF rectF );
		/// 加入选择
		virtual void			addToMultiSelect ( ISceneObject* object );
		/// 进行反选
		virtual void			unSelect( ISceneObject* object );

		/// 是否进行了框选移动操作
		virtual Bool			getObjectOperationDirty() { return mObjectOperationDirty; }

        /// 设置碰撞盒显示
        virtual void            setBoundingBoxVisible( Bool isVisible );

        /// 得到控制变化状态 
        virtual Bool            getChangedDirty(){return mChangedDirty;};

        /// 设置控制方式
        virtual void            setControlType( ControlType type );

        /// 贴住地面
        virtual void            stickTerrain();

		/// 判断是否锁定高度( 锁定高度)
		virtual bool			isTerrainSticked() { return mTerrainSticked; };

		virtual void			setTerrainSticked(bool terrainSticked ) { mTerrainSticked = terrainSticked; };

	protected:

        /// 检测场景对象选中
        Bool                    updateSceneObjectFocus();
        Bool                    updateSceneObjectRectFocus();

        /// 渲染事件
        void                    postFindVisibleObjects(Ogre::SceneManager* source, 
            Ogre::SceneManager::IlluminationRenderStage irs, Ogre::Viewport* v);

		//@{ AxisObjects 

			/// 创建坐标工具对象 
			void    createUtilObjects();
			/// 销毁坐标工具对象 
			void    destroyUtilObjects();

            /// 检测工具对象选中
            Bool    updateUtilObjectFocus();
            /// 更新坐标工具对象位置 
            void    updateUtilObjectsLocation();
			/// 更新坐标工具对象缩放 
			void	updateUtilObjectsScale();
            /// 更新坐标工具对象操作 
            void    updateUtilObjectsOp();

			/// 设置可见度
			void    setUtilObjectsVisible( Bool visible );
			/// 判断是否是坐标对象
			Bool    isUtilObject( ISceneObject* obj );
            
			/// 重新初始化重新出现的坐标对象的缩放
			void	reinitAllUtilObjectsScale();
            /// 设置被选中后的坐标工具对象的材质 
            void    setFocusedUtilObjectMaterial( Int index );
            /// 还原所有的坐标工具对象的材质 
            void    restoreAllUtilObjectsMaterial();

		//@{ 
            ///  对象操作方式SLG. 操作包括移动焦点物体的位置，高度，对物体旋转
            void    updateSLGOp();

			/// 不论那种操作方式都有效的操作
			void	updateCommonOp();

			/// 
			void	beginUpdateMultiFocusObjects();

			void	endUpdateMultiFocusObjects();

		//@}

	protected:

		/// 从sceneNodeListener继承过来
			void	onRemove(ISceneNode* node);

	protected:

		///场景管理
		Scene* mScene;
		///是否开启
		Bool mEnable;
		///是否开启选中操作
		Bool mFocusEnable;
		///控制变化状态 
		Bool mChangedDirty;
		///控制位置转向变化状态;
		Bool mObjectOperationDirty;
		///是否解锁高度操作;如果高度操作解锁， 那么可以自由控制物件的高度。 否则随着地表变化高度
		Bool mTerrainSticked;

		///需要忽略的对象
		ISceneObject* mIgnoreObject;
		///当前控制对象
		ISceneObject* mSceneObject;
		///单选队列( 射线查询重叠物件 )
		std::vector<ISceneObject*> mRayQueryRes;
		///框选队列
		std::vector<ISceneObject*> mMultiSelectRes;

        Vec3 mMouseRayTerrainIntersection;
        Bool mIsMouseRayTerrainIntersectionValid;
		Bool mIsMovingSceneObject;

	protected:

		///坐标工具类型
		enum AxisUtilType
		{
			Axis_X = 0,
			Axis_Y,
			Axis_Z,
			Axis_XY,
			Axis_XZ,
			Axis_YZ
		};
		static const Int AxisUtilCount = 6;
		/// 坐标对象模型名数组
		static const String AxisUtilObjectsMeshName[AxisUtilCount];
		/// 坐标对象名数组 
		static const String AxisUtilObjectsName[AxisUtilCount];
		/// 坐标对象数组
		MG::Entity* mAxisUtilObjects[AxisUtilCount];
        /// 选中的坐标对象索引
        Int mSelectUtilIndex;
		/// 坐标XYZ轴的原始长度
		Flt mUtilAxisLength;
		/// XY面，YZ面，XZ面的边长
		Flt	mUtilPlaneSize;
		/// 坐标XYZ轴的原始缩放
		Flt mUtilAxisBaseScale;

        /// 控制类型
        ControlType mControlType;
        /// 坐标工具移动速度
        Flt mMoveSpeed;
        /// 坐标工具旋转速度
        Flt mYawRotateSpeed;
        /// 鼠标点选世界坐标位置 
        Vector3 mLastMouse3DWorldPos;

        // 是否框选中
        Bool isFocusRect;
		Vec2 mRectPressedMousePos;
		Vec2 mRectPressedScreenPos;
        Vec2 mRectHoldMousePos;
		Vec2 mRectHoldScreenPos;

		/// 选中单位的位置变化
		Qua  mLastFrameSingleFocusOrientation;
		Vec3 mLastFrameSingleFocusPosition;
		Vec3 mLastFrameSingleFocusScale;

		Ogre::SceneNode* mTreeBoundingBoxRenderNode;
	};

}

/******************************************************************************/
#endif
