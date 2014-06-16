/******************************************************************************/
#ifndef _SCENENODEACTION_H_
#define _SCENENODEACTION_H_
/******************************************************************************/

#include "EnginePreqs.h"
#include "LinedState.h"
#include "ISceneNodeAction.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //�����ڵ�����ƶ���Ϊ
    /******************************************************************************/
    class SceneNodeLineMoveToAction : public ISceneNodeLineMoveToAction
    {
    public:
        SceneNodeLineMoveToAction( ISceneNode* object );
		SceneNodeLineMoveToAction( ISceneNode* object, Str SUBSTATE_NAME );

        virtual ~SceneNodeLineMoveToAction();
        //״̬����
        static Str STATE_NAME;

    public:

        /// �����ƶ��ٶ�
        void                            setMoveSpeed( Flt speed );
        /// �ƶ���ָ��λ��
        void                            setMoveToDestination( const Vec3& dest );
        /// �����Ƿ�������
        void                            setStickTerrain( Bool isStickTerrain );
		/// �����Ƿ���Ը߶Ȳ�, ֻ����2ά����
		void				            setIgnoreHeight( Bool isIgnoreHeight );
		// �����Ƿ������Ŷ���
		void							setPerturbEnable( Bool isPerturb );
		// �����Ŷ��ݰ뾶
		void							setPerturbRadiu( Flt radiu );
		// �����Ŷ���Ƶ��
		void							setPerturbFrequnce( UInt freq );

    protected:

        ///�����¼�
        virtual void                    update( Flt delta );
        ///�Ƿ������
        virtual Bool                    isFinished();
        ///��ȥ״̬�¼�
        virtual void                    onEnter();
        ///�뿪״̬�¼�
        virtual void                    onLeave();

	protected:

		ISceneNode*			    mSceneNode;
        /// �Ƿ��ƶ�
        Bool				    mIsMoving;
        /// �ƶ���ʼ��λ��
        Vector3				    mMoveStartPosition;
        /// �ƶ���Ŀ��λ��
        Vector3				    mMoveDestination;
        /// �ƶ��ĳ���
        Flt					    mMoveLength;
        /// ��ǰ�ƶ��ĳ���
        Flt					    mCurrMoveLength;
        /// �ƶ��ķ���
        Vector3				    mMoveVelocity;
        /// �ƶ����ٶ�
        Flt					    mMoveSpeed;
        /// �Ƿ�������
        Bool				    mIsStickTerrain;
		/// �Ƿ���Ը߶�
		Bool				    mIsIgnoreHeight;
		/// �Ƿ������Ŷ���
		Bool                             mIsPerturbGrass;
		/// �Ŷ��뾶
		Flt								 mPerturbRadiu;
		/// �Ŷ�Ƶ��(ÿ�뼸��)
		UInt							 mPerturbFrequnce;
		/// ���һ���Ŷ�ʱ��
		clock_t							 mLastPerturbTime;

    };

    /******************************************************************************/
    //�����ڵ����ת����Ϊ
    /******************************************************************************/
    class SceneNodeYawToAction : public ISceneNodeYawToAction
    {
    public:
        SceneNodeYawToAction( ISceneNode* object );
        virtual ~SceneNodeYawToAction();
        //״̬����
        static Str STATE_NAME;

    public:

        /// ����Y��ת���ٶ�
        void                setYawSpeed( Flt speed );
        /// Χ��Y��ת��ָ������������ʾ��ʱ��ת����������ʾ˳ʱ��ת��
        void                setYawToDirection( const Vec3& dir );
        void                setYawToDirection( const Vec3& startPos, const Vec3& endPos );
        /// Χ��Y��ת��ָ��λ��
        void                setYawToPosition( const Vec3& pos );
		/// �����Ƿ�����
		void                setIsImmediately( Bool isImmediately ){mIsImmediately=isImmediately;}

    protected:

        ///�����¼�
        virtual void        update( Flt delta );
        ///�Ƿ������
        virtual Bool        isFinished();
        ///��ȥ״̬�¼�
        virtual void        onEnter();
        ///�뿪״̬�¼�
        virtual void        onLeave();

    private:

        ISceneNode* mSceneNode;

        /// �Ƿ�ת��
        Bool mIsYawing;
        /// Y��ת��Ŀ�귽��
        Vector3 mDstDirection;
        /// Y��ת��Ŀ�귽��
        Flt mYawDir;
        /// Y��ת��Ŀ���ٶ�
        Flt mYawRotateSpeed;
		/// �Ƿ�����
		Bool mIsImmediately;
    };

	/******************************************************************************/
	//�����ڵ����PITCHת����Ϊ
	/******************************************************************************/
	class SceneNodePitchToAction : public ISceneNodePitchToAction
	{
	public:
		SceneNodePitchToAction( ISceneNode* object );
		virtual ~SceneNodePitchToAction();
		//״̬����
		static Str STATE_NAME;

	public:

		/// ����X��ת���ٶ�
		void                setPitchSpeed( Flt speed );
		/// Χ��X��ת��ķ���
		void                setDestAngle( Flt radian );
		/// �����Ƿ�����
		void                setIsImmediately( Bool isImmediately ){mIsImmediately=isImmediately;}

	protected:

		///�����¼�
		virtual void        update( Flt delta );
		///�Ƿ������
		virtual Bool        isFinished();
		///��ȥ״̬�¼�
		virtual void        onEnter();
		///�뿪״̬�¼�
		virtual void        onLeave();

	private:

		ISceneNode* mSceneNode;

		/// �Ƿ�ת��
		Bool mIsPitching;
		/// X��ת��ķ���
		Flt mPitchDir;
		/// Xת���ٶ�
		Flt mPitchRotateSpeed;
		/// X��ԭ�еĽǶ�
		Flt mSrcPitch;
		/// X��ת��ĽǶ�
		Flt mDstPitch;
		/// �Ƿ�����
		Bool mIsImmediately;
	};

	/******************************************************************************/
	//�����ڵ����ת��������Ϊ
	/******************************************************************************/
	class SceneNodeDirectToAction : public ISceneNodeDirectToAction
	{
	public:

		SceneNodeDirectToAction( ISceneNode* object );
		virtual ~SceneNodeDirectToAction();
		//״̬����
		static Str STATE_NAME;

	public: 

		/// ����ת���ٶ�
		void				setShiftSpeed( Flt speed ) { mShiftSpeed = speed; }
		
		/// ��ȡת���ٶ�
		Flt					getShiftSpeed() { return mShiftSpeed; }

		/// ����Ŀ�귽��
		void				setDestDirection( Vec3 dir );

		/// ��ȡĿ�귽��
		Vec3				getDestDirection() { return mDestDirection; }

		/// �Ƿ�������Ч
		void				setImmediately(bool immediately) { mIsImmediately = immediately; }

		/// �Ƿ������
		Bool				isFinished();

	protected:

		/// �����¼�
		virtual void        update( Flt delta );
		/// ��ȥ״̬�¼�
		virtual void        onEnter();
		/// �뿪״̬�¼�
		virtual void        onLeave();

	private:

		/// �����ڵ�
		ISceneNode*			mSceneNode;
		/// ת����ٶ�, ��λ�ǻ���
		Flt					mShiftSpeed;
		/// �ⲿ�����Ŀ��ָ��
		Vec3				mDestDirection;
		/// ��ʼ����
		Vec3				mOriginalDirection;	
		/// ��ת��
		Vec3				mRotateAxis;
		/// �ܵľ���
		Flt					mTotalRadianDist;
		/// ��ǰ�ľ���
		Flt					mCurrRadianDist;
		/// �Ƿ�����ת�Ƶ�Ŀ��Ƕ�
		Bool				mIsImmediately;
	};


}

/******************************************************************************/

#endif