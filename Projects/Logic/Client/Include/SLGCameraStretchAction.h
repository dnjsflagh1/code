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
    //SLG�������������Lod
    /******************************************************************************/
    struct SLGCameraStretchLod
    {
        UInt mHeight;       // ��ظ߶�

        Flt mAngle;         // �͵�ƽ��ĽǶ�(0-90��)
        Flt mRaiseTime;     // �л�ʱ��
        Flt mLowTime;       // �л�ʱ��

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
            //��׼����������������
            Vec3 xzDir = camDir;
            xzDir.y = 0;
            xzDir.normalise();

			//��ȡ����Ҫ��Ŀ��ǶȵĻ���ֵ
            Flt radian = getRadian( mAngle );

			//��ȡ�������local��ת��
            Vec3 xAxis = xzDir.crossProduct(Vec3(0.0f,1.0f,0.0f));

			//ͨ��local��ת��ͻ���ֵ��������action�������Ҫ����ת��Ԫ��ֵ
            Qua q = Qua(1,0,0,0);
            q.FromAngleAxis(-radian,xAxis);
            q.normalise();

			//��ȡ���յ���ת����
            Vec3 newDir = q * xzDir;
            newDir.normalise();

			//����������������Ŀ���������ֵ
            Vec3 camDelta = newDir * (Flt)calculateDirLengh( radian );

            return camDelta;
        }
    };


    /******************************************************************************/
    //�����������Ϊ
    /******************************************************************************/
    class SLGCameraStretchAction : public LinedStateObject
    {
    public:
        SLGCameraStretchAction( SLGCameraOpCtrl* owner );
        virtual ~SLGCameraStretchAction();

    public:

        //״̬����
        static Str STATE_NAME;

    public:

        void                    setCamera( ICamera* camera );

        /// ��������LOD
        void                    setStretchLod( SLGCameraStretchLod destlod, Flt time );
        SLGCameraStretchLod&    getStretchLod();

		Vec3					getDestDir() { return mDestDir; }

    protected:

        ///�����¼�
        virtual void            update( Flt delta );
        ///�Ƿ������
        virtual Bool            isFinished();
        ///��ȥ״̬�¼�
        virtual void            onEnter();
        ///�뿪״̬�¼�
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
