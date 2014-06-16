/******************************************************************************/
#ifndef _FORMATIONMANAGER_H_
#define _FORMATIONMANAGER_H_
/******************************************************************************/
#include "WorldCorePreqs.h"
/******************************************************************************/

namespace MG
{
	class FormationManager
	{
	public:
		FormationManager();
		virtual ~FormationManager();

	public:
		virtual Formation* createFormation( FormationType formationType );
		virtual void	   destroyFormation();
		virtual Formation* getCurrFormation();

	protected:
		Formation*			mFormaion;

	private:
		
	};
}


#endif