/******************************************************************************/
#ifndef _SAICONTROLLER_H_
#define _SAICONTROLLER_H_
/******************************************************************************/

#include "MapServerPreqs.h"
#include "AIController.h"
#include "HeartBeatObject.h"
#include "SFightManager.h"


/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//AI¿ØÖÆ
	/******************************************************************************/
	class SAIController : public AIController, public FightManagerListener, public HeartBeatObject
	{
	public:
		SAIController( SCharacter* owner );
		virtual ~SAIController();

		void								Init();

		virtual void						update();

		
	protected:

		void								setPeaceState();

		///////////////////////////////////////////////////////////////////////////////////

		void								updateFightState( Flt delta );

		void								updatePursue( Flt delta );

		void								updateReturn( Flt delta );

		void								updateAttack( Flt delta );

		///////////////////////////////////////////////////////////////////////////////////

		void								onEnterFight( GameObject* fightObject );

		void								onEndFight( GameObject* fightObject );


		///////////////////////////////////////////////////////////////////////////////////

		virtual Bool						isDead();

	protected:

		SCharacter*							mOwner;
		std::vector<SkillRatio>				mSkillRatioList;
		Flt									mLastUpdateTime;
		Flt									mCurrGuardRadius;
		Flt									mKeepDistance;
		Flt									mPursueRadius;
	};
}


#endif	