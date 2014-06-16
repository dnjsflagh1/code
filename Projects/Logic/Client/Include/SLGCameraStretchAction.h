/******************************************************************************/
#ifndef _SLGCAMERASTRETCHACTION_H_
#define _SLGCAMERASTRETCHACTION_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    //SLG摄像机控制伸缩Lod
    /******************************************************************************/
    struct SLGCameraStretchLod
    {
        UInt mHeight;       // 离地高度

        Flt mAngle;         // 和地平面的角度(0-90度)
        Flt mRaiseTime;     // 切换时间
        Flt mLowTime;       // 切换时间

        //--------------------------------------------------------------------------
        SLGCameraStretchLod()
            :mHeight(80.0f),mAngle(30.0f),mRaiseTime(0.3f),mLowTime(0.3f)
        {
        }

        //--------------------------------------------------------------------------
        SLGCameraStretchLod(UInt height, Flt angle, Flt raiseTime, Flt lowTime)
            :mHeight(height),mAngle(angle),mRaiseTime(raiseTime),mLowTime(lowTime)
        {
        }

        //--------------------------------------------------------------------------
        Flt getRaiseOrLowTime( Bool raiseOrLow )
        {
            if ( raiseOrLow )
            {
                return mRaiseTime;
            }
            return mLowTime;
        }

        //--------------------------------------------------------------------------
        Flt getRadian( Flt angle )
        {
            return angle / 180 * 3.14;
        }
        //--------------------------------------------------------------------------
        Flt calculateDirLengh( Flt radian )
        {
            Flt dirLen = mHeight;

            Flt radianSin = sin( radian );

            if ( radianSin != 0 )
            {
                dirLen = mHeight / radianSin;
            }

            return dirLen;
        }
        //--------------------------------------------------------------------------
        Vec3 calculateDir( Vec3 camDir )
        {
            //标准化输入的摄像机方向
            Vec3 xzDir = camDir;
            xzDir.y = 0;
            xzDir.normalise();

			//获取所需要的目标角度的弧度值
            Flt radian = getRadian( mAngle );

			//获取摄像机的local旋转轴
            Vec3 xAxis = xzDir.crossProduct(Vec3(0.0f,1.0f,0.0f));

			//通过local旋转轴和弧度值计算出这次action完成所需要的旋转四元数值
            Qua q = Qua(1,0,0,0);
            q.FromAngleAxis(-radian,xAxis);
            q.normalise();

			//获取最终的旋转方向
            Vec3 newDir = q * xzDir;
            newDir.normalise();

			//获得了摄像机和锁定目标的向量差值
            Vec3 camDelta = newDir * (Flt)calculateDirLengh( radian );

            return camDelta;
        }
    };


    /******************************************************************************/
    //摄像机伸缩行为
    /******************************************************************************/
    class SLGCameraStretchAction : public LinedStateObject
    {
    public:
        SLGCameraStretchAction( SLGCameraOpCtrl* owner );
        virtual ~SLGCameraStretchAction();

    public:

        //状态名字
        static Str STATE_NAME;

    public:

        void                    setCamera( ICamera* camera );

        /// 设置伸缩LOD
        void                    setStretchLod( SLGCameraStretchLod destlod, Flt time );
        SLGCameraStretchLod&    getStretchLod();

		Vec3					getDestDir() { return mDestDir; }

    protected:

        ///更新事件
        virtual void            update( Flt delta );
        ///是否结束了
        virtual Bool            isFinished();
        ///进去状态事件
        virtual void            onEnter();
        ///离开状态事件
        virtual void            onLeave();

    private:

		Bool					mIsImmediately;
		Bool					mIsHeightLimited;

		Flt						mTime;
		Vec3					mDestDir;
		SLGCameraStretchLod		mDestLod;

        ICamera*				mCamera;
        SLGCameraOpCtrl*		mOwner;       
    };

}

/******************************************************************************/
#endif
