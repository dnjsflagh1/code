/******************************************************************************/
#ifndef _FGAMETIMESYSTEM_H_
#define _FGAMETIMESYSTEM_H_
/******************************************************************************/
#include "FringeGameTimeSystem.h"
#include "Singleton.h"
/******************************************************************************/
namespace MG
{
	class FGameTimeSystem : public FringeGameTimeSystem
	{
	public:
		FGameTimeSystem();
		~FGameTimeSystem();
		SINGLETON_INSTANCE(FGameTimeSystem);
	public:
		virtual void	onTimer();
		virtual void	getCenterActualTime();

	};
}
#endif //_FGAMETIMESYSTEM_H_