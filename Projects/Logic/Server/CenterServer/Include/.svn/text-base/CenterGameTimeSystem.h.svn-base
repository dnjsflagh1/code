/******************************************************************************/
#ifndef _TIMESYSTEM_H_
#define _TIMESYSTEM_H_
/******************************************************************************/
#include "Singleton.h"
#include "QueryPerformanceFrequency.h"
/******************************************************************************/
namespace MG
{
	class CenterGameTimeSystem
	{
	public:
		SINGLETON_INSTANCE(CenterGameTimeSystem);
		CenterGameTimeSystem();
		~CenterGameTimeSystem();

		Bool initialize();
		void update();
		Bool unInitialize();
		
	public:
		//-----------------------------------------------------
		/*						真实时间					*/
		//-----------------------------------------------------
		// 获取当前真实时刻 精度秒
		U64			getCurrActualTime();
		// 获取游戏开始后偏移时刻
		Dbl			getCurrGameStartActualTick();
		
		static void	timerThread(Ptr ptr);  

		void		syncTimeToAllServer(U64 currTime);
		//-----------------------------------------------------
		/*						虚拟时间					*/
		//-----------------------------------------------------

		

	private:
		
		// 游戏起始时标准时间 现用本地系统时间，后会改成格林时间
		U64							mGameStartTime;

		// 游戏起始后 游戏偏移时刻
		Dbl							mGameStartGameTick;

		// 高精度计时器
		QueryPerformanceFrequency	mTimer;
		// 时间系统线程
		OneThreadHandle				mThread;
	};
}
#endif //_TIMESYSTEM_H_