/******************************************************************************/
#ifndef _SLGCAMERAOPCTRL_H_
#define _SLGCAMERAOPCTRL_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "GameCameraConfig.h"
#include "SLGCameraStretchAction.h"

/******************************************************************************/

namespace MG
{
    
    /******************************************************************************/
    //SLG摄像机控制
    /******************************************************************************/
    class SLGCameraOpCtrl : public IOpCtrl
    {
	public:
		SINGLETON_INSTANCE(SLGCameraOpCtrl)
        SLGCameraOpCtrl();
        virtual ~SLGCameraOpCtrl();

        //////////////////////////////////////////////////////////////////////////////////////////

        /// 操作更新
        virtual void	update( Flt delta );

        /// 设置摄像机对象
        void			setCamera(ICamera* cam);

        /// 还原摄像机状态
        void			revertCamera();
        /// 切换摄像机为自由控制还是游戏控制
        void            switchViewportLock();
		/// 切换摄像机模式为跟踪模式
		void			setTrackCamera(bool isTrack);
		/// 获得当前摄像机模式
		bool			isTrackCamera() { return mIsTrackMode; }

        //////////////////////////////////////////////////////////////////////////////////////////

		/// 下列镜头锁定会在地图设定的镜头范围内进行

	public:

		/// 从外部同步一个坐标
		void			syncFocusPosDirFromServer(Vec2 worldPos, Vec2 worldDir);
        /// 聚焦地表上某一个点
        void			focusPos(Vec2 worldPos);
		/// 聚焦某点
		void			focusPos(Vec3 pos);
        /// 聚焦某个角色
		void			focusPos(IdType id);
		/// 设置摄像机从某个方向关注角色
		void			focusDir(Vec2 worldDir);
        /// 得到聚焦的点
        Vec3			getFocusPos();
        /// 得到高度根据关注点
        Flt             getHeightByFocusPos();
        /// 更新聚焦点
        void            updateFocusPos();
        /// 检测和显示摄像机高度
        Bool            checkAndLimitCameraHeight();

	private:

		/// 该接口仅仅更新这个类中保存focus position的一个副本，并不操作相机。
		void			setFocusPos(Vec3 pos);

        //////////////////////////////////////////////////////////////////////////////////////////

	public:
        //###########################################################
        // 自由摄像机
        //###########################################################

        /// 更新自由摄像机操作
        void            updateFreeCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );

        //###########################################################
        // SLG摄像机
        //###########################################################

        /// 更新游戏SLG摄像机操作
        void            updateGameSLGCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );

		/// 更新一个摄像机的环绕动作
		void			triggerGameCameraRotateOperation( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );
        /// 触发一个摄像拖移操作
        void            triggerGameCameraDragOperation( IInput* input, ITerrainManager* terrain, ICamera* camera );
        /// 触发一个摄像机旋转操作
        void            triggerGameCameraPitchOperation( IInput* input, ICamera* camera, Dbl delta, Int pitchFactor );
        /// 触发一个摄像机窗口边缘移动检测和实施操作
        void            triggerGameCameraBorderTranslateCheckOperation( IInput* input, ICamera* camera, Dbl d );
        /// 触发一个摄像机Lod切换操作
        void            triggerGameCameraStretchLodOperation( IInput* input, ICamera* camera, Dbl delta, Bool isRaise );
        /// 触发一个摄像机Lod切换操作
        void            triggerGameCameraStretchLodOperation2( IInput* input, ICamera* camera, Dbl delta, Bool isRaise );

        /// 触发一个摄像机测试操作
        void            triggerGameCameraTestOperation( IInput* input, ICamera* camera, Dbl delta );


        //###########################################################
        // 角色追踪RPG摄像机
        //###########################################################

        /// 更新角色追踪RPG摄像机
        void            updateGameTrackCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );
		/// 更新角色追踪RPG摄像机的碰撞
		void			updateGameTrackCameraCollision( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );

        //////////////////////////////////////////////////////////////////////////////////////////

		/// 返回一个合法的摄像机local位移
		Vec3			getValidFocusDelta(Vec3 pos, Qua orientation, Vec3 delta, bool isLocal = true);

        /// 设置摄像机的默认位置
        void			setCameraDefaultPos( Vec3 pos );
        /// 设置摄像机的默认角度
        void			setCameraDefaultPitch( Flt degree );
		/// 设置摄像机默认高度
		void			setCameraDefaultHeight( Flt height );

        /// 设置鼠标在窗口边界触发移动的范围
        void			setAutoMoveSize(UInt size);
        /// 设置摄像机移动的边界
        void			setCameraMoveBoard( Vec3 minBoard, Vec3 maxBoard );
        /// 设置摄像机旋转的边界
		void			setCameraPitchRange( Flt degreeMin, Flt degreeMax );

        /// 设置摄像机平移速度和独立旋转速度
		void			setCameraSpeed( Flt transSpeed, Flt rollSpeed );
		
		//// 配置摄像机参数
		void			applyCameraSetting( const GameCameraConfigInfo* config );

        /// 清空伸缩Lod列表
        void            clearCameraStretchLods();
        /// 增加一个伸缩Lod
        void            addCameraStretchLod( SLGCameraStretchLod lod );
        /// 激活指定的伸缩Lod
        void            activeCameraStretchLod(Flt height, Bool isRaise);
        /// 停止指定的伸缩Lod
        void            stopCameraStretchLod();
        /// 是否伸缩Lod正在激活状态
        Bool            isCameraStretchLodActive();

    private:

        ///游戏摄像机对象
        ICamera*		mCamera;
		///是否为跟踪模式
		Bool			mIsTrackMode;
        Vec3            mFocusPos;

		Bool			mSyncFocus2DPosDirDirty;
		Vec2			mSyncFocus2DPos;
		Vec2			mSyncFocus2DDir;

		Flt				mCameraSpeed;
		UInt			mAutoMoveSize;
        Vec3            mLastMouseTerrainIntersection;

        Vec3            mLastCameraMoveDis;
        Vec2            mLastMouseMoveDis;
		Bool            mViewportLock;

        Bool            mRaiseOrLowHeight;
        Bool            mMoveHeight;

		Flt             mCamMaxPitch;
		Flt             mCamMinPitch;
		Flt				mCamDefaultPitch;
        Flt             mCamMinHeight;

		Vec3			mCamMinBoard;
		Vec3			mCamMaxBoard;
		Vec3			mCamDefaultPos;
        Flt             mCamDefaultHeight;

		Flt				mCamGameRollSpeed;
		Flt				mCamGameMoveSpeed;

        std::map<UInt, SLGCameraStretchLod> mCameraStretchLodList;

        SLGCameraStretchAction*         mSLGCameraStretchAction;
    };	

}

/******************************************************************************/
#endif
