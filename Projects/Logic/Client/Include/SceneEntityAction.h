/******************************************************************************/
#ifndef _SCENEENTITYACTION_H_
#define _SCENEENTITYACTION_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "ISceneNodeAction.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************/
    // �ƶ�״̬
    // ��ʱ�����������й������ƶ������õĵط�
    /******************************************************************************/
    enum CMoveAcionState
    {
        MAS_NULL,
        MAS_MOVING,
        MAS_MOVEWAIT,
        MAS_MOVESTOP
    };


    /******************************************************************************/
    //��Ϸ����ֱ���ƶ���Ϊ
    /******************************************************************************/
    class CCSEntityLineMoveAcion : public LinedStateObject, public LinedStateObjectListener
    {
    public:
        CCSEntityLineMoveAcion( CSceneEntity* entity, Vec3 startPos, Vec3 endPos, Flt startTime );
        virtual ~CCSEntityLineMoveAcion();

    public:

        //״̬����
        static Str STATE_NAME;

        ///�����¼�
        virtual void        update( Flt delta );
        ///�Ƿ������
        virtual Bool        isFinished();
        ///��ȥ״̬�¼�
        virtual void        onEnter();
        ///�뿪״̬�¼�
        virtual void        onLeave();
        ///״̬�ı��¼�
        virtual void        onMoveAcionStateChanged( CMoveAcionState state );

        ////////////////////////////////////////////////////////////////////////////////////

        void                setAnimation( Str animName, Bool isAutoAnimEnd = true );
        void				setMoveSpeed(Flt speed);
        void				setYawSpeed(Flt speed);

		////////////////////////////////////////////////////////////////////////////////////

		void				setBlockCheck( Bool isBlockCheck );

		void				setMoveToPathFindType( ISceneNodeGridLineMoveToAction::MoveToPathFindType moveToPathFindType );

        ////////////////////////////////////////////////////////////////////////////////////

        CMoveAcionState     getMoveAcionState();
        void                setMoveAcionState( CMoveAcionState state );

        ////////////////////////////////////////////////////////////////////////////////////

		void				setIsWait( Bool isWait );

		////////////////////////////////////////////////////////////////////////////////////

		Vec3				getDestination();

		void				addEntityLineMoveAcionListener( CCSEntityLineMoveAcion* moveAcion );

		////////////////////////////////////////////////////////////////////////////////////

		ISceneNodeGridLineMoveToAction* getCurrSceneNodeGridLineMoveToAction();
        
    protected:

        Bool                isNeedMoveToStartPos();
        void                moveToStartPos();
        void                moveToEndPos();


        virtual void        onLinedStateEnter(LinedStateObject* obj);
        virtual void        onLinedStateLeave(LinedStateObject* obj);
        virtual void        onLinedStateChanged(LinedStateObject* obj);

    protected:

        // ����ʵ���ٶ�
        void                calculateRealMoveSpeed( );

        // ����Ƿ�ʵ������ʼ�㲢������������ײ�ƶ�Action

        // ����������ײֱ���ƶ�Acion


    private:

        CSceneEntity*  mEntity;

        CMoveAcionState mCMoveAcionState;

        Vec3        mStartPos;
        Vec3        mEndPos;
        Flt         mDelayPushTime;

        Str         mAnimName;
        Bool        mIsAutoAnimEnd;
        Bool        mAnimPlaying;

		Bool		mIsBlockCheck;

        Flt         mMoveSpeed;
        Flt         mRealMoveSpeed;
        Flt         mYawSpeed;

		Flt			mPathRadius;

		Bool		mIsStartMove;

        ISceneNodeGridLineMoveToAction* mSceneNodeLineMoveToStartPosAction;
        ISceneNodeGridLineMoveToAction* mSceneNodeLineMoveToEndPosAction;
        Bool        mIsPrepareMoveEndPos;
        Bool        mIsAlreadyMoveEndPos;
		Str			mSceneNodeLineMoveToActionName;

		IBlockManager*	mBlockManager;

		std::vector<CCSEntityLineMoveAcion*> mMoveAcionListenerList;

		ISceneNodeGridLineMoveToAction::MoveToPathFindType mMoveToPathFindType;

		Flt			mWaitTime;
		Bool		mIsWaitMove;
		Flt			mWaitMoveTime;

        // �ƶ��ҳ���Ч����
        //MoveDustEffectCollection

    };


    /******************************************************************************/
    //���󽻻���Ϊ
    /******************************************************************************/

    class CCSEntityRequestInteractAcion : public LinedStateObject
    {
    public:
        
        CCSEntityRequestInteractAcion( CSceneEntity* requestEntity, CSceneEntity* desEntity );
        virtual ~CCSEntityRequestInteractAcion();

    public:

        //״̬����
        static Str STATE_NAME;


        ///�����¼�
        virtual void        update( Flt delta );
        ///�Ƿ������
        virtual Bool        isFinished();
        ///��ȥ״̬�¼�
        virtual void        onEnter();
        ///�뿪״̬�¼�
        virtual void        onLeave();

        /////////////////////////////////////////////////////////////////////

        // �õ����ʵĽ�����λ��
        Vec3                getSuitableInteractPosition();

    private:

        // ���󽻻�����
        CSceneEntity*  mRequestEntity;

        // ����Ŀ�����
        CSceneEntity*  mDesEntity;
    };


    


}


/******************************************************************************/

#endif //