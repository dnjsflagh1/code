/******************************************************************************/
#ifndef _SAIOBJECTMANAGER_H_
#define _SAIOBJECTMANAGER_H_
/******************************************************************************/

#include "MapServerPreqs.h"

#include "LinedState.h"
#include "ObjectPool.h"


#include "SAIGuard.h"
#include "SAIRandomMove.h"
#include "SAIAttack.h"
#include "SAIFightTrigger.h"
#include "SAIKeepDistance.h"
#include "SAIPursue.h"
#include "SAISelectSkill.h"
#include "SAIReturn.h"
#include "SAIHateDetect.h"
#include "SAISeekHelp.h"
#include "SAIEscape.h"


/******************************************************************************/

namespace MG
{


	/******************************************************************************/
	// 实体组AI管理
	/******************************************************************************/
	class SAIObjectManager : public LinedStateObjectListener
	{
	public:
		SAIObjectManager();
		virtual ~SAIObjectManager();
		SINGLETON_INSTANCE(SAIObjectManager)

		void				revert();
		void				update( Flt delta );

		void				addUpdateAIMgr( LinedStateManager* mgr );
		void				removeUpdateAIMgr( LinedStateManager* mgr );
		void				clear();

		void				addLimitCount();
		Bool				isOverMaxLimitCount();


		///////////////////////////////////////////////////////////////////////////////////

		SAIGuard*			createSAIGuard( SCharacter* character );
		void				destroySAIGuard( SAIGuard* ai);

		SAIRandomMove*		createSAIRandomMove( SCharacter* character );
		void				destroySAIRandomMove( SAIRandomMove* ai );

		SAIAttack*			createSAIAttack( SCharacter* character );
		void				destroySAIAttack( SAIAttack* ai );

		SAISeekHelp*		createSAISeekHelp( SCharacter* character );
		void				destroySAISeekHelp( SAISeekHelp* ai );

		SAIEscape*			createSAIEscape( SCharacter* character );
		void				destroySAIEscape( SAIEscape* ai );

		SAIFightTrigger*	createSAIFightTrigger( SCharacter* character );
		void				destroySAIFightTrigger( SAIFightTrigger* ai );

		SAIKeepDistance*	createSAIKeepDistance( SCharacter* character );
		void				destroySAIKeepDistance( SAIKeepDistance* ai );

		SAIHateDetect*		createSAIHateDetect( SCharacter* character );
		void				destroySAIHateDetect( SAIHateDetect* ai );

		SAIPursue*			createSAIPursue( SCharacter* character );
		void				destroySAIPursue( SAIPursue* ai );

		SAISelectSkill*		createSAISelectSkill( SCharacter* character );
		void				destroySAISelectSkill( SAISelectSkill* ai );

		SAIReturn*			createSAIReturn( SCharacter* character );
		void				destroySAIReturn( SAIReturn* ai );


		///////////////////////////////////////////////////////////////////////////////////

	protected:

		virtual void		onLinedStateLifeTimeOver(LinedStateObject* obj);

	protected:

		ObjectPool<SAIAttack>										mSAIAttackPool;
		ObjectPool<SAIFightTrigger>	                				mSAIFightTriggerPool;
		ObjectPool<SAIKeepDistance>									mSAIKeepDistancePool;
		ObjectPool<SAIHateDetect>									mSAIHateDetectPool;
		ObjectPool<SAIPursue>										mSAIPursuePool;
		ObjectPool<SAISelectSkill>									mSAISelectSkillPool;
		ObjectPool<SAIReturn>										mSAIReturnPool;
		ObjectPool<SAIGuard>	                        			mSAIGuardPool;
		ObjectPool<SAISeekHelp>										mSAISeekHelpPool;
		ObjectPool<SAIEscape>	                        			mSAIEscapePool;
		ObjectPool<SAIRandomMove>									mSAIRandomMovePool;

		std::map< LinedStateManager*, Bool>                         mUpdateLinedStateManagerList;
		UInt                                                        mUpdateCurrIndex;
		UInt                                                        mMaxUpdateLimitCount;
		UInt														mUpdateLimitCount;
	};
}


#endif	