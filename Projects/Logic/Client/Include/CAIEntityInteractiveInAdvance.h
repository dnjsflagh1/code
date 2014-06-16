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
	// 实体 交互 AI
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

		//状态名字
		static Str STATE_NAME;

		///更新事件
		virtual void        							update( Flt delta );
		///是否结束了
		virtual Bool        							isFinished();
		///进去状态事件
		virtual void        							onEnter();
		///离开状态事件
		virtual void        							onLeave();

		////////////////////////////////////////////////////////////////////////

        // 设置目标实体
        void									        setTargetSceneEntity(CSceneEntity* sceneEntity);
        // 得到目标实体
        CSceneEntity*									getTargetSceneEntity();

    protected:

        virtual void                                    onLinedStateLifeTimeOver(LinedStateObject* obj);

		////////////////////////////////////////////////////////////////////////
		//得到可以交互的距离
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