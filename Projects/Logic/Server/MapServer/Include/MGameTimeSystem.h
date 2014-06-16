/******************************************************************************/
#ifndef _MGAMETIMESYSTEM_H_
#define _MGAMETIMESYSTEM_H_
/******************************************************************************/
#include "FringeGameTimeSystem.h"
#include "Singleton.h"
/******************************************************************************/
namespace MG
{
	class MGameTimeSystem : public FringeGameTimeSystem
	{
	public:
		SINGLETON_INSTANCE(MGameTimeSystem);
		MGameTimeSystem();
		~MGameTimeSystem();

	public:
		virtual void	onTimer();
		virtual void	getCenterActualTime();

	};
}
#endif //_MGAMETIMESYSTEM_H_