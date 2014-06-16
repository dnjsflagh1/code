/******************************************************************************/
#ifndef _SFIGHTMANAGER_H_
#define _SFIGHTMANAGER_H_
/******************************************************************************/

#include "FightManager.h"

/******************************************************************************/

/******************************************************************************/
//’Ω∂∑π‹¿Ì
/******************************************************************************/

namespace MG
{

	class SFightManager : public FightManager
	{
	public:
		SFightManager( GameObject* owner );
		~SFightManager();

	public:
		virtual void						notifyEnterFight( GameObject* fightObject );

		virtual void						notifyEndFight( GameObject* fightObject );

	protected:

		////////////////////////////////////////////////////////////////////////////////////////////////////

		virtual FightInfo*					addFightInfo( IdType fightInfoID, GameObject* fightObject, UInt hateVal );

		////////////////////////////////////////////////////////////////////////////////////////////////////
	};

}

#endif