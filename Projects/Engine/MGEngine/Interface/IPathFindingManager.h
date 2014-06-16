/******************************************************************************/
#ifndef _IPATHFINDINGMANAGER_H_
#define _IPATHFINDINGMANAGER_H_
/******************************************************************************/

#include "MGEngineInterfacePreqs.h"

/******************************************************************************/

namespace MG
{


	/******************************************************************************/
	//”Œœ∑Actionπ‹¿Ì
	/******************************************************************************/
	class IPathFindingManager
	{
	public:
		virtual IPathFinder*				getStaticPathFinder() = 0;
		virtual IPathFinder*				getDynamicPathFinder() = 0;

		virtual void						load() = 0;
        virtual void						unLoad() = 0;

	};

}

/******************************************************************************/
#endif