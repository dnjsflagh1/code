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
    //SLG���������
    /******************************************************************************/
    class SLGCameraOpCtrl : public IOpCtrl
    {
	public:
		SINGLETON_INSTANCE(SLGCameraOpCtrl)
        SLGCameraOpCtrl();
        virtual ~SLGCameraOpCtrl();

        //////////////////////////////////////////////////////////////////////////////////////////

        /// ��������
        virtual void	update( Flt delta );

        /// �������������
        void			setCamera(ICamera* cam);

        /// ��ԭ�����״̬
        void			revertCamera();
        /// �л������Ϊ���ɿ��ƻ�����Ϸ����
        void            switchViewportLock();
		/// �л������ģʽΪ����ģʽ
		void			setTrackCamera(bool isTrack);
		/// ��õ�ǰ�����ģʽ
		bool			isTrackCamera() { return mIsTrackMode; }

        //////////////////////////////////////////////////////////////////////////////////////////

		/// ���о�ͷ�������ڵ�ͼ�趨�ľ�ͷ��Χ�ڽ���

	public:

		/// ���ⲿͬ��һ������
		void			syncFocusPosDirFromServer(Vec2 worldPos, Vec2 worldDir);
        /// �۽��ر���ĳһ����
        void			focusPos(Vec2 worldPos);
		/// �۽�ĳ��
		void			focusPos(Vec3 pos);
        /// �۽�ĳ����ɫ
		void			focusPos(IdType id);
		/// �����������ĳ�������ע��ɫ
		void			focusDir(Vec2 worldDir);
        /// �õ��۽��ĵ�
        Vec3			getFocusPos();
        /// �õ��߶ȸ��ݹ�ע��
        Flt             getHeightByFocusPos();
        /// ���¾۽���
        void            updateFocusPos();
        /// ������ʾ������߶�
        Bool            checkAndLimitCameraHeight();

	private:

		/// �ýӿڽ�������������б���focus position��һ���������������������
		void			setFocusPos(Vec3 pos);

        //////////////////////////////////////////////////////////////////////////////////////////

	public:
        //###########################################################
        // ���������
        //###########################################################

        /// �����������������
        void            updateFreeCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );

        //###########################################################
        // SLG�����
        //###########################################################

        /// ������ϷSLG���������
        void            updateGameSLGCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );

		/// ����һ��������Ļ��ƶ���
		void			triggerGameCameraRotateOperation( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );
        /// ����һ���������Ʋ���
        void            triggerGameCameraDragOperation( IInput* input, ITerrainManager* terrain, ICamera* camera );
        /// ����һ���������ת����
        void            triggerGameCameraPitchOperation( IInput* input, ICamera* camera, Dbl delta, Int pitchFactor );
        /// ����һ����������ڱ�Ե�ƶ�����ʵʩ����
        void            triggerGameCameraBorderTranslateCheckOperation( IInput* input, ICamera* camera, Dbl d );
        /// ����һ�������Lod�л�����
        void            triggerGameCameraStretchLodOperation( IInput* input, ICamera* camera, Dbl delta, Bool isRaise );
        /// ����һ�������Lod�л�����
        void            triggerGameCameraStretchLodOperation2( IInput* input, ICamera* camera, Dbl delta, Bool isRaise );

        /// ����һ����������Բ���
        void            triggerGameCameraTestOperation( IInput* input, ICamera* camera, Dbl delta );


        //###########################################################
        // ��ɫ׷��RPG�����
        //###########################################################

        /// ���½�ɫ׷��RPG�����
        void            updateGameTrackCameraOp( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );
		/// ���½�ɫ׷��RPG���������ײ
		void			updateGameTrackCameraCollision( IInput* input, ITerrainManager* terrain, ICamera* camera, Dbl delta );

        //////////////////////////////////////////////////////////////////////////////////////////

		/// ����һ���Ϸ��������localλ��
		Vec3			getValidFocusDelta(Vec3 pos, Qua orientation, Vec3 delta, bool isLocal = true);

        /// �����������Ĭ��λ��
        void			setCameraDefaultPos( Vec3 pos );
        /// �����������Ĭ�ϽǶ�
        void			setCameraDefaultPitch( Flt degree );
		/// ���������Ĭ�ϸ߶�
		void			setCameraDefaultHeight( Flt height );

        /// ��������ڴ��ڱ߽紥���ƶ��ķ�Χ
        void			setAutoMoveSize(UInt size);
        /// ����������ƶ��ı߽�
        void			setCameraMoveBoard( Vec3 minBoard, Vec3 maxBoard );
        /// �����������ת�ı߽�
		void			setCameraPitchRange( Flt degreeMin, Flt degreeMax );

        /// ���������ƽ���ٶȺͶ�����ת�ٶ�
		void			setCameraSpeed( Flt transSpeed, Flt rollSpeed );
		
		//// �������������
		void			applyCameraSetting( const GameCameraConfigInfo* config );

        /// �������Lod�б�
        void            clearCameraStretchLods();
        /// ����һ������Lod
        void            addCameraStretchLod( SLGCameraStretchLod lod );
        /// ����ָ��������Lod
        void            activeCameraStretchLod(Flt height, Bool isRaise);
        /// ָֹͣ��������Lod
        void            stopCameraStretchLod();
        /// �Ƿ�����Lod���ڼ���״̬
        Bool            isCameraStretchLodActive();

    private:

        ///��Ϸ���������
        ICamera*		mCamera;
		///�Ƿ�Ϊ����ģʽ
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
