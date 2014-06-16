/******************************************************************************/
#ifndef _CAIMANAGER_H_
#define _CAIMANAGER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "LinedState.h"
#include "ObjectPool.h"

#include "CAIEntityGroupPathFindingGatherInAdvance.h"
#include "CAIEntityGroupPathFindingMoveInAdvance.h"
#include "CAIEntityGroupPathFindingPursueAttackInAdvance.h"

#include "CAIEntityPathFindingMoveInAdvance.h"
#include "CAIEntityGuard.h"
#include "CAIEntityRandomPathFindingMove.h"
#include "CAIEntityPathFindingMoveAndGuardInAdvance.h"
#include "CAIEntityPathFindingPursueAttackInAdvance.h"

#include "CAIEntityAttack.h"
#include "CAIEntityFightTrigger.h"
#include "CAIEntityKeepDistance.h"
#include "CAIEntityPathFindingPursue.h"
#include "CAIEntitySelectSkill.h"
#include "CAIEntityReturn.h"
#include "CAIEntityEscape.h"

#include "CAIEntityGroupInteractiveInAdvance.h"
#include "CAIEntityInteractiveInAdvance.h"

#include "CAITroopObjectSendSkillPacket.h"

#include "CAIEntityDie.h"


/******************************************************************************/

namespace MG
{


    /******************************************************************************/
    // 实体组AI管理
    /******************************************************************************/
    class CAIManager : public LinedStateObjectListener
    {
    public:
        CAIManager();
        virtual ~CAIManager();
        SINGLETON_INSTANCE(CAIManager)

        void        revert();
        void        update( Flt delta );

        void        addUpdateAIMgr( LinedStateManager* mgr );
        void        removeUpdateAIMgr( LinedStateManager* mgr );
        void        clear();

		void		addLimitCount();
		Bool		isOverMaxLimitCount();

        ///////////////////////////////////////////////////////////////////////////////////

        CAIEntityGroupPathFindingGatherInAdvance*		createCAIEntityGroupPathFindingGatherInAdvance();
        void		destroyCAIEntityGroupPathFindingGatherInAdvance(CAIEntityGroupPathFindingGatherInAdvance* ai);

        CAIEntityGroupPathFindingMoveInAdvance*		    createCAIEntityGroupPathFindingMoveInAdvance();
        void		destroyCAIEntityGroupPathFindingMoveInAdvance(CAIEntityGroupPathFindingMoveInAdvance* ai);

        CAIEntityGroupPathFindingPursueAttackInAdvance* createCAIEntityGroupPathFindingPursueAttackInAdvance();
        void		destroyCAIEntityGroupPathFindingPursueAttackInAdvance(CAIEntityGroupPathFindingPursueAttackInAdvance* ai);

		CAIEntityGroupInteractiveInAdvance* createCAIEntityGroupInteractiveInAdvance();
		void		destroyCAIEntityGroupInteractiveInAdvance(CAIEntityGroupInteractiveInAdvance* ai);

        ///////////////////////////////////////////////////////////////////////////////////

        CAIEntityPathFindingMoveInAdvance*		createCAIEntityPathFindingMoveInAdvance( CCharacterSceneEntity* characterSceneEntity );
        void		destroyCAIEntityPathFindingMoveInAdvance(CAIEntityPathFindingMoveInAdvance* ai);

        CAIEntityGuard*		createCAIEntityGuard( CCharacterSceneEntity* characterSceneEntity );
        void		destroyCAIEntityGuard(CAIEntityGuard* ai);
           
        CAIEntityRandomPathFindingMove*		createCAIEntityRandomPathFindingMove( CCharacterSceneEntity* characterSceneEntity );
        void		destroyCAIEntityRandomPathFindingMove(CAIEntityRandomPathFindingMove* ai);

        CAIEntityPathFindingMoveAndGuardInAdvance*		createCAIEntityPathFindingMoveAndGuardInAdvance( CCharacterSceneEntity* characterSceneEntity );
        void		destroyCAIEntityPathFindingMoveAndGuardInAdvance(CAIEntityPathFindingMoveAndGuardInAdvance* ai);

		CAIEntityAttack*		createCAIEntityAttack( CCharacterSceneEntity* characterSceneEntity );
		void		destroyCAIEntityAttack(CAIEntityAttack* ai);

		CAIEntityFightTrigger*		createCAIEntityFightTrigger( CCharacterSceneEntity* characterSceneEntity );
		void		destroyCAIEntityFightTrigger(CAIEntityFightTrigger* ai);

		CAIEntityKeepDistance*		createCAIEntityKeepDistance( CCharacterSceneEntity* characterSceneEntity );
		void		destroyCAIEntityKeepDistance(CAIEntityKeepDistance* ai);

		CAIEntityPathFindingPursue*	createCAIEntityPathFindingPursue( CCharacterSceneEntity* characterSceneEntity );
		void		destroyCAIEntityPathFindingPursue(CAIEntityPathFindingPursue* ai);

		CAIEntitySelectSkill*	createCAIEntitySelectSkill( CCharacterSceneEntity* characterSceneEntity );
		void		destroyCAIEntitySelectSkill(CAIEntitySelectSkill* ai);

		CAIEntityEscape*	createCAIEntityEscape( CCharacterSceneEntity* characterSceneEntity );
		void		destroyCAIEntityEscape(CAIEntityEscape* ai);

		CAIEntityReturn*	createCAIEntityReturn( CCharacterSceneEntity* characterSceneEntity );
		void		destroyCAIEntityReturn(CAIEntityReturn* ai);

        CAIEntityPathFindingPursueAttackInAdvance*		createCAIEntityPathFindingPursueAttackInAdvance( CCharacterSceneEntity* characterSceneEntity );
        void		destroyCAIEntityPathFindingPursueAttackInAdvance(CAIEntityPathFindingPursueAttackInAdvance* ai);

		CAIEntityInteractiveInAdvance*		createCAIEntityInteractiveInAdvance( CCharacterSceneEntity* characterSceneEntity );
		void		destroyCAIEntityInteractiveInAdvance(CAIEntityInteractiveInAdvance* ai);

		CAIEntityDie*		createCAIEntityDie( CCharacterSceneEntity* characterSceneEntity );
		void		destroyCAIEntityDie(CAIEntityDie* ai);

		CAITroopObjectSendSkillPacket*		createCAITroopObjectSendSkillPacket();
		void		destroyCAITroopObjectSendSkillPacket(CAITroopObjectSendSkillPacket* ai);


        ///////////////////////////////////////////////////////////////////////////////////

    protected:

        virtual void    onLinedStateLifeTimeOver(LinedStateObject* obj);

    protected:

        ObjectPool<CAIEntityGroupPathFindingGatherInAdvance>	    mCAIEntityGroupPathFindingGatherInAdvancePool;
        ObjectPool<CAIEntityGroupPathFindingMoveInAdvance>	        mCAIEntityGroupPathFindingMoveInAdvancePool;
        ObjectPool<CAIEntityGroupPathFindingPursueAttackInAdvance>	mCAIEntityGroupPathFindingPursueAttackInAdvancePool;
		ObjectPool<CAIEntityGroupInteractiveInAdvance>				mCAIEntityGroupInteractiveInAdvancePool;

		ObjectPool<CAIEntityAttack>									mCAIEntityAttackPool;
		ObjectPool<CAIEntityFightTrigger>	                        mCAIEntityFightTriggerPool;
		ObjectPool<CAIEntityKeepDistance>							mCAIEntityKeepDistanceInAdvancePool;
		ObjectPool<CAIEntityPathFindingPursue>						mCAIEntityPathFindingPursueInAdvancePool;
		ObjectPool<CAIEntitySelectSkill>							mCAIEntitySelectSkillInAdvancePool;
		ObjectPool<CAIEntityReturn>									mCAIEntityReturnPool;
		ObjectPool<CAIEntityEscape>									mCAIEntityEscapePool;
        ObjectPool<CAIEntityPathFindingMoveInAdvance>	            mCAIEntityPathFindingMoveInAdvancePool;
        ObjectPool<CAIEntityGuard>									mCAIEntityGuardInAdvancePool;
        ObjectPool<CAIEntityRandomPathFindingMove>					mCAIEntityRandomPathFindingMoveInAdvancePool;
        ObjectPool<CAIEntityPathFindingMoveAndGuardInAdvance>       mCAIEntityPathFindingMoveAndGuardInAdvancePool;
        ObjectPool<CAIEntityPathFindingPursueAttackInAdvance>	    mCAIEntityPathFindingPursueAttackInAdvancePool;
		ObjectPool<CAIEntityInteractiveInAdvance>					mCAIEntityInteractiveInAdvancePool;
		ObjectPool<CAIEntityDie>									mCAIEntityDiePool;

		ObjectPool<CAITroopObjectSendSkillPacket>					mCAITroopObjectSendSkillPacketPool;

        std::map< LinedStateManager*, Bool>                         mUpdateLinedStateManagerList;
        UInt                                                        mUpdateCurrIndex;
        UInt                                                        mMaxUpdateLimitCount;
		UInt														mUpdateLimitCount;
    };
}


#endif	