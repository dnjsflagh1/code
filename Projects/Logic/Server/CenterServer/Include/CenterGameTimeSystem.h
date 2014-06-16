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
		/*						��ʵʱ��					*/
		//-----------------------------------------------------
		// ��ȡ��ǰ��ʵʱ�� ������
		U64			getCurrActualTime();
		// ��ȡ��Ϸ��ʼ��ƫ��ʱ��
		Dbl			getCurrGameStartActualTick();
		
		static void	timerThread(Ptr ptr);  

		void		syncTimeToAllServer(U64 currTime);
		//-----------------------------------------------------
		/*						����ʱ��					*/
		//-----------------------------------------------------

		

	private:
		
		// ��Ϸ��ʼʱ��׼ʱ�� ���ñ���ϵͳʱ�䣬���ĳɸ���ʱ��
		U64							mGameStartTime;

		// ��Ϸ��ʼ�� ��Ϸƫ��ʱ��
		Dbl							mGameStartGameTick;

		// �߾��ȼ�ʱ��
		QueryPerformanceFrequency	mTimer;
		// ʱ��ϵͳ�߳�
		OneThreadHandle				mThread;
	};
}
#endif //_TIMESYSTEM_H_