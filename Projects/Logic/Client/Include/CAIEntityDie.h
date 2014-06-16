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

	protected:
		// 停止思考
		void											stopThink( Flt time );
		// 恢复思考
		void											resumeThink();

		////////////////////////////////////////////////////////////////////////
		// 设置Block
		void											setEntityBlockEnable( IEntity* entity, Bool isEnable );
		// 设置Collision
		void											setEntityCollisionEnable( IEntity* entity, Bool isEnable );

		////////////////////////////////////////////////////////////////////////

		//换模型
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