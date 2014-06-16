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
		// ������ʱ���������Ҫʱ��
		virtual void	getCenterActualTime();
	public:
		// ��ȡ��ǰ��ʵʱ�� ������
		U64		getCurrActualTime();
		void	setCurrActualTime(U64 actualTime);

		Bool	getCurrGameTime(U32& year,U32&season,U32& mon,U32& day,U32& hour);
		Str16	getCurrGameTime();

		Bool	getGameTimeByActualTime(U64 actualTime,U32& year,U32&season,U32& mon,U32& day,U32& hour);
		Str16	getGameTimeByActualTime(U64 actualTime);

	private:
		// ��ͬ�����ʱ��
		U64		mBaseTime;

		// ��ͬ�����ϵͳƫ��ʱ��
		U32		mSystemTick;

		// ��Ϸ��ʼ���е���ʵʱ��
		U64		mGameStartActualTime;

		// ϵͳ�Ƿ���Ч
		Bool	mIsValid;

		// ����
		const CalendarInfo* mCalendarInfo;

	};
}
#endif //_TIMESYSTEM_H_