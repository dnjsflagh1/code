/******************************************************************************/
#ifndef _CAICONTROLLER_H_
#define _CAICONTROLLER_H_
/******************************************************************************/

#include "ClientPreqs.h"
#include "AIController.h"


/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//AI¿ØÖÆ
	/******************************************************************************/
	class CAIController : public AIController
	{
	public:
		CAIController( CCharacterSceneEntity* owner );
		virtual ~CAIController();

		void								Init();

		void								update( Flt delta );

		///////////////////////////////////////////////////////////////////////////////////

		void								setIsPause( Bool isPause );

		Bool								getIsPause();

	protected:

		virtual void						setPeaceState();

		virtual void						setFightState();

		virtual void						setReturnState();


		///////////////////////////////////////////////////////////////////////////////////

		void								updateFightState( Flt delta );

		void								updatePursue( Flt delta );

		void								updateReturn( Flt delta );

		void								updateAttack( Flt delta );

		///////////////////////////////////////////////////////////////////////////////////

		virtual Bool						isDead();


	protected:

		CCharacterSceneEntity*				mOwner;
		std::vector<SkillRatio>				mSkillRatioList;
		Flt									mCurrGuardRadius;
		Flt									mKeepDistance;
		Flt									mPursueRadius;
		Bool								mIsPause;
	};
}


#endif	