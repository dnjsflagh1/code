/******************************************************************************/
#ifndef _FRINGEGAMETIMESYSTEM_H_
#define _FRINGEGAMETIMESYSTEM_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "Singleton.h"
/******************************************************************************/
namespace MG
{
	struct CalendarInfo;
	class FringeGameTimeSystem
	{
	public:
		//SINGLETON_INSTANCE(FringeGameTimeSystem);
		FringeGameTimeSystem();
		virtual ~FringeGameTimeSystem();

		Bool initialize();
		void update();
		Bool unInitialize();

		virtual void	onTimer() = 0;
		// 向中心时间服务器索要时间
		virtual void	getCenterActualTime();
	public:
		// 获取当前真实时刻 精度秒
		U64		getCurrActualTime();
		void	setCurrActualTime(U64 actualTime);

		Bool	getCurrGameTime(U32& year,U32&season,U32& mon,U32& day,U32& hour);
		Str16	getCurrGameTime();

		Bool	getGameTimeByActualTime(U64 actualTime,U32& year,U32&season,U32& mon,U32& day,U32& hour);
		Str16	getGameTimeByActualTime(U64 actualTime);

	private:
		// 被同步后的时间
		U64		mBaseTime;

		// 被同步后的系统偏移时间
		U32		mSystemTick;

		// 游戏开始运行的现实时间
		U64		mGameStartActualTime;

		// 系统是否有效
		Bool	mIsValid;

		// 历法
		const CalendarInfo* mCalendarInfo;

	};
}
#endif //_TIMESYSTEM_H_