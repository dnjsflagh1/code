/******************************************************************************/
#ifndef _CAIENTITYDIE_H_
#define _CAIENTITYDIE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	// 
	/******************************************************************************/
	class CAIEntityDie : public LinedStateObject
	{
		enum DieAIState
		{
			DAS_NULL,
			DAS_STARTPLAYDIEANIM,
			DAS_ENDPLAYDIEANIM,
		};
	public:
		CAIEntityDie( CCharacterSceneEntity* characterSceneEntity );
		virtual ~CAIEntityDie();

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

		////////////////////////////////////////////////////////////////////////

	protected:
		// ֹͣ˼��
		void											stopThink( Flt time );
		// �ָ�˼��
		void											resumeThink();

		////////////////////////////////////////////////////////////////////////
		// ����Block
		void											setEntityBlockEnable( IEntity* entity, Bool isEnable );
		// ����Collision
		void											setEntityCollisionEnable( IEntity* entity, Bool isEnable );

		////////////////////////////////////////////////////////////////////////

		//��ģ��
		void											changeMesh( IEntity* entity, UInt meshId );

		////////////////////////////////////////////////////////////////////////

		void											startPlayAnim();

		void											endPlayAnim();

		////////////////////////////////////////////////////////////////////////

		//void											dellFightInfo();

	protected:
		CCharacterSceneEntity*							mCharacterSceneEntity;
		Str												mAnimName;
		Flt												mPauseThinkTime;
		DieAIState										mState;
		Bool											mIsFinished;
		const CharacterVisionEventInfo*					mCharacterVisionEventInfo;


	};
}

#endif