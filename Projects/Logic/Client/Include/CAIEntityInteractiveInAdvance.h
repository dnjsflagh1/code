/******************************************************************************/
#ifndef _CAIENTITYINTERACTIVEINADVANCE_H_
#define _CAIENTITYINTERACTIVEINADVANCE_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"

/******************************************************************************/

namespace MG
{

	/******************************************************************************/
	// ʵ�� ���� AI
	/******************************************************************************/
	class CAIEntityInteractiveInAdvance : public LinedStateObject, public LinedStateObjectListener
	{
		enum InteractiveAIState
		{
			IAS_NULL,
			IAS_MOVETO,
			IAS_INTERACTIVE,
		};

	public:

		CAIEntityInteractiveInAdvance( CCharacterSceneEntity* characterSceneEntity );
		virtual ~CAIEntityInteractiveInAdvance();

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

        // ����Ŀ��ʵ��
        void									        setTargetSceneEntity(CSceneEntity* sceneEntity);
        // �õ�Ŀ��ʵ��
        CSceneEntity*									getTargetSceneEntity();

    protected:

        virtual void                                    onLinedStateLifeTimeOver(LinedStateObject* obj);

		////////////////////////////////////////////////////////////////////////
		//�õ����Խ����ľ���
		Flt												getInteractiveDis( CCharacterSceneEntity* owner, CSceneEntity* target );

		/////////////////////////////////////////////////////////////////////////

		void											updateMoveToPos();

		void											updateInteractive();

	protected:

		 Flt											mInteractiveDis;
		 Vec3											mDestination;
		 CCharacterSceneEntity*							mCharacterSceneEntity;
		 CAIEntityPathFindingMoveInAdvance*				mPathFindingMoveAI;

         GAMEOBJ_TYPE                                   mTargetSceneEntityType;
         GameObjectIdType                               mTargetSceneEntityID;
		 CSceneEntity*									mTargetSceneEntity;

         Bool                                           mIsFinished;
		 InteractiveAIState								mState;
	};
}

#endif