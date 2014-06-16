/******************************************************************************/
#ifndef _CAIENTITYATTACKINADVANCE_H_
#define _CAIENTITYATTACKINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "CAI.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************
 	
	******************************************************************************/
	class CAIEntityAttack : public CAI, public LinedStateObject
	{
		enum AIAttackState
		{
			AIAS_NULL,
			AIAS_START,
			AIAS_END,
		};

	public:
		CAIEntityAttack( CCharacterSceneEntity* characterSceneEntity );
		virtual ~CAIEntityAttack();

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


		////////////////////////////////////////////////////////////////////////

	protected:

		void											updateAttack( Flt delta );

	protected:

		//ʹ�ü���
		void											useSkill( CSkillObject*	skillObject );

		//�Ƿ���Թ���
		Bool											isAttack( CCharacterSceneEntity* owner, CCharacterSceneEntity* target );
		////////////////////////////////////////////////////////////////////////

		void											aiEnd();

		////////////////////////////////////////////////////////////////////////

		void											notifyAttackEnd();

		void											notifyTargetDied();

	private:

		GAMEOBJ_TYPE									mTargetType;
		GameObjectIdType								mTargetId;
		UInt											mTargetIndex;
		Vec3											mTargetPos;
		IdType											mSkillId;
		Bool											mIsFinished;
		UInt											mMinIntervalAttackTime;
		UInt											mMaxIntervalAttackTime;
		Flt												mPauseThinkTime;

		AIAttackState									mAIAttackState;

		CSkillObject*									mSkillObject;
	};
}

#endif