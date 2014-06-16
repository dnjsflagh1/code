/******************************************************************************/
#ifndef _CAIENTITYPATHFINDINGMOVEINADVANCE_H_
#define _CAIENTITYPATHFINDINGMOVEINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "SceneEntityAction.h"

/******************************************************************************/

namespace MG
{

    //******************************************************************************

	enum AIEntityMoveType
	{
        /// ��ͨ״̬��
		AIEMT_NORMAL,
        /// ��̬�ϰ�Ѱ·�ƶ���
		AIEMT_DYNAMICMOVE,
        /// ��̬�ϰ�Ѱ·�ƶ���
		AIEMT_STATICMOVE,
	};
     
    //******************************************************************************
    /** ʵ��Ѱ·�ƶ�AI 
    */

    /** Ѱ·����
        @   ʹ�á���̬�����ϰ����ݡ���A*�㷨�������Ѱ·�����ߡ�·��
        @   Ȼ�����·�ߵ�ֱ�߶��ࡾ�۵㡿��Ȼ���ȥ���ࡾ�۵㡿,�����µġ����ߡ�
        @   Ȼ����ȡ���2�۵㣬��ʼѰ·�����ƶ�
        @   ׼���ƶ�����Ѱ·�����ʱ�������ռʽռ��ģʽ
        @   ����Ѱ·�����ж�̬�ϰ���ʱ�򣬸��ݶ�̬�ϰ��ϵ�Ԫ��״̬�ж��Ƿ�ֹͣ���߶�̬�����µ�Ѱ··��
    */
    //******************************************************************************/
    class CAIEntityPathFindingMoveInAdvance : public LinedStateObject, public LinedStateManagerListener
    {
    public:
        CAIEntityPathFindingMoveInAdvance( CCharacterSceneEntity* characterSceneEntity );
        virtual ~CAIEntityPathFindingMoveInAdvance();

        //״̬����
        static Str STATE_NAME;

        ///�����¼�
        virtual void									update( Flt delta );
        ///�Ƿ������
        virtual Bool									isFinished();
        ///��ȥ״̬�¼�
        virtual void									onEnter();
        ///�뿪״̬�¼�
        virtual void									onLeave();


        ////////////////////////////////////////////////////////////////////////

		// �õ���ǰ״̬
        CMoveAcionState                                 getMoveAcionState();

		// �õ�������ȫ��Ŀ���
        void											setDestination(Vec3 pos);

		void											setUnblockPosDestination(Vec3 pos);

		Vec3											getDestination();

		// �õ��߼���ɫ����
		CCharacterSceneEntity*							getOwner();

		// ����AI�����
		void											setAIEntityGroup( CAIEntityGroup* aiEntityGroup );

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		Bool											getIsStaticMove();

	protected:

		// ���͸���״̬
		void											checkAndUpdateState( Flt delta );

		// ���µ�����̬Ѱ·
		PathFindingResult                               calculateAndDoStaticPathFinding();
        // ���µ�����̬Ѱ·
        PathFindingResult                               calculateAndDoDynamicPathFinding();

		/////////////////////////////////////////////////////////////////////////////////////////////////////

		// ֹͣ˼��
		void											stopThink( Flt time );
		// �ָ�˼��
		void											resumeThink();


		// �Ƿ񵽴ﵱǰĿ��� 
		Bool											isArriveOnDestination( Vec3 des );
		// �õ�����ɽ���ĵ�
		Bool											getNearestAccessiblePos( Vec3 centerPos, Vec3& nearestAccessiblePos );

		// ֹͣ�ƶ���������Ϣ�������
		void											requestStopMove();
		// �����ƶ���������Ϣ�������
		void											requestMoveTo( Vec3 moveToPos, Bool isBlockCheck );

    protected:

		virtual void									onLinedStateAdd(LinedStateObject* obj);
		virtual void									onLinedStateRemove(LinedStateObject* obj);

    protected:

		// �߼����ɫ
		CCharacterSceneEntity*							mCharacterSceneEntity;
		// Ѱ·�㷨����
		ISceneNodePathFindingMoveInAdvanceAction*		mPathFindingMoveInAdvanceAction;
		// AI���ƶ�״̬
		AIEntityMoveType								mState;
		// ������AI
		CAIEntityGroup*									mAIEntityGroup;

        // ��˼��ʱ��
        Flt												mTotleThinkTime;
		// ֹͣ˼��ʱ��
		Flt												mPauseThinkTime;
		// ʵ�ʿ����ߵ�Ŀ�ĵ�
		Vec3											mRealDestination;
		// ����Ŀ�ĵ�
        Vec3											mDestination;
		// ��̬�ڵ�λ��
		Vec3											mStaticCurrDestinationNodePos;
		// ��̬�ڵ�λ��
		Vec3											mDynamicCurrDestinationNodePos;

        // ����ʼ�ĵ�
        Vec3                                            mRequestStartPosition;

		Flt												mMoveLength;
		Flt												mPatherRadius;
		Int												mBlockDiameter;

		Flt												mCheckBlockTime;
		Bool											mIsBlockCheck;

		Flt												mStartPathFindTime;
		Bool											mIsStartDynamicFind;

		Bool											mIsPathFinderWait;

		Bool											mIsStaticMove;
    };
}

#endif