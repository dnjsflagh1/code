/******************************************************************************/
#ifndef _SFIGHTHEARTBEATMANAGER_H_
#define _SFIGHTHEARTBEATMANAGER_H_
/******************************************************************************/
#include "MapServerPreqs.h"
#include "FightManager.h"
#include "HeartBeatObject.h"

/******************************************************************************/

/******************************************************************************/
//’Ω∂∑π‹¿Ì
/******************************************************************************/

namespace MG
{
	class SFightHeartBeatManager : public HeartBeatObject
	{
	public:
		SFightHeartBeatManager( SCharacter* owner );
		~SFightHeartBeatManager();

	public:

		void								init();

		virtual void						update();

		SFightManager*						getFightManager();

	protected:
		SFightManager*						mFightManager;
		SCharacter*							mOwner;
		Flt									mPursueRadius;
	};

}

#endif