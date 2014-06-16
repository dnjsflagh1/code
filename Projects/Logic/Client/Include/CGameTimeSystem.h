/******************************************************************************/
#ifndef _CGAMETIMESYSTEM_H_
#define _CGAMETIMESYSTEM_H_
/******************************************************************************/
#include "FringeGameTimeSystem.h"
#include "Singleton.h"
/******************************************************************************/
namespace MG
{
	class CGameTimeSystem : public FringeGameTimeSystem
	{
	public:
		CGameTimeSystem();
		~CGameTimeSystem();
		SINGLETON_INSTANCE(CGameTimeSystem);
		virtual void onTimer();

	};
}
#endif //_CGAMETIMESYSTEM_H_