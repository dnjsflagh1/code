// ServerNetTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientNetApplyManager.h"
using namespace MG;
extern InterLocked netId[5000];
void OneFun1(Ptr p,U32 threadId)
{
	OneThreadHandleNew *oneThread = (OneThreadHandleNew*)p;
	U64 i = 0;
	while(oneThread->isRun())
	{
		i++;
		if (i == 999999999)
		{
			i = 0;
			Sleep(1);
		}
		U64 k = i;
		k = k * k;
		k = k * i;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	LogSystem::getInstance().setSysLogPath("Log");
	LogSystem::getInstance().setGameLogicLogPath("Log");
	LogSystem::getInstance().setPartName("abc");
	LogSystem::getInstance().setLogLevel(1023);
	LogSystem::getInstance().setEnableConsole(true);
	//LogSystem::getInstance().setSaveToFile(true);
	ThreadMonitor::getInstance().initialize();
	ThreadMonitor::getInstance().setPrintLog(true);
	ThreadMonitor::getInstance().setCalcFrequency(5);
	ThreadMonitor::getInstance().start();

	DWORD threadId = ::GetCurrentThreadId();
	HANDLE threadHandle = NULL;;
	DuplicateHandle(
		GetCurrentProcess(),                   // 进程的伪句柄
		GetCurrentThread(),         // 线程的伪句柄
		GetCurrentProcess(),                   // 进程的实句柄
		&threadHandle,             // 线程转换后的实句柄
		0,                       //Ignored due to DUPLICATE_SAME_ACCESS
		FALSE,                   // 新线程不被继承
		DUPLICATE_SAME_ACCESS);  // Newthread handle has same

	START_MONITOR_THREAD((U32)threadId,"Main",threadHandle);
	Bool res = ClientNetApplyManager::getInstance().initialize();
	ClientNetApplyManager::getInstance().startThreadAutoHandle();

	//OneThreadHandle onethreadhandlenew1;
	//OneThreadHandle onethreadhandlenew2;
	//OneThreadHandleNew onethreadhandlenew3;
	//OneThreadHandleNew onethreadhandlenew4;
	//I32 index = 1;
	//onethreadhandlenew1.create(OneFun1,&index,"onethreadhandlenew1");
	//onethreadhandlenew2.create(OneFun1,&index,"onethreadhandlenew2");


	while (true)
	{
		Sleep(10);
	}

	return 0;
}

