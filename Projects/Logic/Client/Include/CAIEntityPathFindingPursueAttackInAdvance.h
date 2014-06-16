/******************************************************************************/
#ifndef _CAIENTITYPATHFINDINGPURSUEATTACKINADVANCE_H_
#define _CAIENTITYPATHFINDINGPURSUEATTACKINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

    /******************************************************************************
      # ���� AI
	  # ��������СAI:
			1.˲������
			2.Ŀ��㹥��
			3.�Ŀ�깥��
	  #  	
    ******************************************************************************/
    class CAIEntityPathFindingPursueAttackInAdvance : public LinedStateObject
    {
		enum PursueAttackAIState
		{
			PAS_NULL,
			PAS_PURSUE,
			PAS_ATTACK,
			PAS_THINK,
		};

    public:
        CAIEntityPathFindingPursueAttackInAdvance( CCharacterSceneEntity* characterSceneEntity );
        virtual ~CAIEntityPathFindingPursueAttackInAdvance();

        //״̬����
        static Str STATE_NAME;

        ///�����¼�
        virtual void        							update( Flt delta );
        ///�Ƿ������
        virtual Bool        							isFinished();
        ///��ȥ״̬�¼�
        virtual void        							onEnter();
        ///�뿪״̬�¼�
        virtual void        							onLeave();

	public:

		//����Ŀ��
		void											setTarget( Vec3 pos );
		void											setTarget( GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index = 0 );

		//����Ҫʹ�õļ���
		void											setUseSkillId( IdType skillId );

		void											setAIEntityGroup( CAIEntityGroup* aiEntityGroup );

		//�Ƿ���������
		void											setIsLoopAttack( Bool isLoopAttack );

		//�Ƿ�����ѡ��Ŀ��
		void											setIsSelectTargetObject( Bool isSelectTargetObject );

        ////////////////////////////////////////////////////////////////////////

		void											getTarget( GAMEOBJ_TYPE& gameType, GameObjectIdType& id, UInt& index );

	protected:

		void											updatePursue( Flt delta );

		void											updateAttack( Flt delta );

		void											updateThink( Flt delta );

		// ֹͣ˼��
		void											stopThink( Flt time );
		// �ָ�˼��
		void											resumeThink();

    protected:

		//���Ĭ�ϼ���
		IdType											getDefaultSkill();

		//ѡ��Ŀ��
		void											selectTargetObject();

		//ʹ�ü���
		void											useSkill( CSkillObject*	skillObject, SkillInfo*	skillInfo );

		//�Ƿ���Թ���
		Bool											isAttack( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );

		////////////////////////////////////////////////////////////////////////

		Flt												getAttackRange();

		////////////////////////////////////////////////////////////////////////

		Bool											isTroopCompanionTarget( GAMEOBJ_TYPE gameType, GameObjectIdType id, UInt index = 0 );

		////////////////////////////////////////////////////////////////////////

		Flt												clacPursueTime( CCharacterSceneEntity* owner, CCharacterSceneEntity* target, Vec3& pursuePos );

	private:
		
		CAIEntityPathFindingMoveInAdvance*				mPathFindingMoveAI;
		CCharacterSceneEntity*							mCharacterSceneEntity;
		SkillInfo*										mSkillInfo;
		GAMEOBJ_TYPE									mTargetType;
		GameObjectIdType								mTargetId;
		UInt											mTargetIndex;
		Vec3											mTargetPos;
		Vec3											mTargetTargetPos;
		UInt											mSkillId;
		Bool											mIsFinished;
		Flt												mAttackIntervalTime;
		CSkillObject*									mSkillObject;
		Vec3											mMoveToPos;
		Vec3											mLastTargetPos;
		Vec3											mLastTargetTargetPos;
		CAIEntityGroup*									mAIEntityGroup;
		Int												mBlockDiameter;
		PursueAttackAIState								mState;
		Bool											mIsLoopAttack;
		Bool											mIsSelectTargetObject;
		Flt												mPauseThinkTime;
		Flt												mPausePursueThinkTime;
		Flt												mAttackRange;
    };
}

#endif