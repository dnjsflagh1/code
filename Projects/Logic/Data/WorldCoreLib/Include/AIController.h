/******************************************************************************/
#ifndef _AICONTROLLER_H_
#define _AICONTROLLER_H_
/******************************************************************************/

#include "AIFightTrigger.h"

/******************************************************************************/

namespace MG
{
	enum AIControllerState
	{
		ACS_NULL,
		ACS_BIRTH,
		ACS_PEACE,
		ACS_STARTFIGHT,
		ACS_FIGHT,
		ACS_ENDFIGHT,
		ACS_RETURN,
	};

	class AIControllerListener
	{
	public:
		virtual void onFightTrigger( FightTriggerEvent& fightTriggerEvent ){};
		virtual void onSearchTarget( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex ){};
		virtual void onPursueResult( Bool isFinish ){};
		virtual void onSelectSkillResult( UInt skillId ){};
		virtual void onChangeTargetForHate( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex ){};
		virtual void onKeepDistance( Vec3 keepDisPos ){};
		virtual void onAttackEnd(){};
		virtual void onTargetDied(){};
		virtual void onReturnFinish(){};
		virtual void onEscapeEnd(){};
		virtual void onEnd( AI* ai ){};
	};


	/******************************************************************************/
	//AI¿ØÖÆ
	/******************************************************************************/
	class AIController : public AIControllerListener
	{
	public:

		enum FightState
		{
			FS_NULL,
			FS_PREPAR,
			FS_SELECTSKILL,
			FS_PURSUE,
			FS_ATTACK,
			FS_MOVETOKEEPDISPOS,
			FS_HELPMOVETO,
		};

		enum PursueState
		{
			PS_NULLVALUE,
			PS_STARTPURSUE,
			PS_PURSUEING,
			PS_ENDPURSUE,
		};

		enum AttackState
		{
			AS_NULLVALUE,
			AS_STARTATTACK,
			AS_ATTACKING,
			AS_ENDATTACK,
		};

		enum RetuenState
		{
			RS_NULL,
			RS_START,
			RS_RETURNING,
			RS_END,
		};


		///////////////////////////////////////////////////////////////////////////////////

		AIController();
		virtual ~AIController();

		virtual void								Init();

		virtual void								update( Flt delta );

		///////////////////////////////////////////////////////////////////////////////////

		virtual Flt									getAIPauseTime();

		///////////////////////////////////////////////////////////////////////////////////


		AIControllerState							getAIControllerState();

		///////////////////////////////////////////////////////////////////////////////////

		virtual void								setBirthState();

		virtual void								setFightState();

		virtual void								setHelpMoveToState();

	protected:

		virtual void								setPeaceState();

		virtual void								setReturnState();

		///////////////////////////////////////////////////////////////////////////////////

		virtual void								updateFightState( Flt delta );

		virtual void								updatePursue( Flt delta );

		virtual void								updateReturn( Flt delta );


		///////////////////////////////////////////////////////////////////////////////////

		virtual void 								onSearchTarget( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

		virtual void								onFightTrigger( FightTriggerEvent& fightTriggerEvent );

		virtual void 								onPursueResult( Bool isFinish );

		virtual void 								onSelectSkillResult( UInt skillId );

		virtual void 								onChangeTargetForHate( GAMEOBJ_TYPE targetType, IdType targetId, UInt targetIndex );

		virtual void 								onKeepDistance( Vec3 keepDisPos );

		virtual void								onReturnFinish();

		virtual void								onEscapeEnd();

		virtual void								onAttackEnd();

		virtual void								onTargetDied();

		virtual void								onEnd( AI* ai );

		///////////////////////////////////////////////////////////////////////////////////
		virtual Bool								isDead() = 0;

	protected:

		AIControllerState							mState;
		BaseAIGroup*								mBaseAIGroup;

		FightState									mFightState	;
		PursueState									mPursueState;
		RetuenState									mReturnState;
		AttackState									mAttackState;

		IdType										mUseSkillId;

		GAMEOBJ_TYPE								mTargetType;
		GameObjectIdType							mTargetId;
		UInt										mTargetIndex;

		Vec3										mCenterPos;
		Vec3										mMoveToPos;

		Bool										mIsContinuePursue;

		Flt											mPauseThinkTime;

		AIFightTrigger*								mAIFightTrigger;	
	};
}


#endif	