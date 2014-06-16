/******************************************************************************/
#ifndef _FORMATION_H_
#define _FORMATION_H_
/******************************************************************************/
#include "WorldCorePreqs.h"
/******************************************************************************/

namespace MG
{

	class Formation
	{
	public:
		Formation( FormationType formationType );
		virtual~Formation();
	public:
		///
		virtual void	  setFormationType( FormationType formationType );
		///
		virtual void	  changeFormationType( FormationType formationType );
		///
		virtual void	  yawToDir( Vec3 dir );
		///
		virtual void	  moveTo( Vec3 pos, Bool isBreakAction = true, Str actionName = "EntityMoveToAction");
		///
		virtual void	  update( Flt delta ){};

	protected:
		FormationType	  mFormationType;
	};
}


#endif