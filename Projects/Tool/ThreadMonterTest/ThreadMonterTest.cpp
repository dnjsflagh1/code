// ThreadMonterTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientNetApplyManager.h"
using namespace MG;


NetAddress addr("192.168.1.101",5555);
Int connectCountPerThread;
InterLocked netId[MAX_CONNECT];
Critical connectLock;
std::map<I32,Int> connectIndexs;
Int flag = 6;
void OneFun(Ptr p,U32 threadId)
{
	OneThreadHandleNew *oneThread = (OneThreadHandleNew*)p;
	while(oneThread->isRun())
	{	
		for (Int i = 0; i < MAX_CONNECT; i++)
		{
			for (Int j = 0; j < SEND_COUNT; j++)
			{
				GameNetSendDataBufferPtr sendPtr = ClientNetApplyManager::getInstance().getSendDataBuffer();
				ClientNetApplyManager::getInstance().sendFrontServerPacket(netId[i],sendPtr,1000);
			}
		}
		ClientNetApplyManager::getInstance().update();
		Sleep(10);
	}
}
void OneFun1(Ptr p,U32 threadId)
{
	OneThreadHandleNew *oneThread = (OneThreadHandleNew*)p;
	Int index = *(Int*)oneThread->getParam();
	Sleep(index * 100);

	DWORD lastTime = timeGetTime();
	while(oneThread->isRun())
	{	
		for (Int i = index * connectCountPerThread; i < (index + 1) * connectCountPerThread; i++)
		{
			//CriticalArmor csArmor(connectLock[i]);
			if (netId[i] == -1)
			{
				netId[i] = ClientNetApplyManager::getInstance().connectLoginServer(addr);
			}
			else
			{
				
			}
			if (netId[i] == -1)
			{
				DYNAMIC_ASSERT_LOG(false,"连接失败");
			}
			else if ( netId[i] > -1 && SEND_COUNT > 0)
			{
				while(true)
				{
					DWORD currTime = timeGetTime();
					if(currTime - lastTime > 5)
					{
						lastTime = currTime;
						for (Int j = 0; j < SEND_COUNT; j++)
						{
							GameNetSendDataBufferPtr sendPtr = ClientNetApplyManager::getInstance().getSendDataBuffer();
							ClientNetApplyManager::getInstance().sendFrontServerPacket(netId[i],sendPtr,100);
						}
						break;
					}
					else
					{
						Sleep(1);
					}

				}
				
			}
		}
		if (flag == 5)
		{
			for (Int i = index * connectCountPerThread; i < (index + 1) * connectCountPerThread; i++)
			{
				if (netId[i] > -1)
				{
					ClientNetApplyManager::getInstance().close(0,netId[i]);
					netId[i]  = -1;
				}
			}
			flag = 0;
		}
		if (flag == 6)
		{
			for (Int i = index * connectCountPerThread; i < (index + 1) * connectCountPerThread; i++)
			{
				if (netId[i] > -1)
				{
					ClientNetApplyManager::getInstance().close(0,netId[i]);
					netId[i]  = -1;

				}
			}
		}
		if (flag == 9)
		{
			for (Int i = index * connectCountPerThread; i < (index + 1) * connectCountPerThread; i++)
			{
				if (netId[i] > -1)
				{
					ClientNetApplyManager::getInstance().close(0,netId[i]);
					netId[i]  = -1;

				}
			}
			while(flag == 9)
			{
				Sleep(100);
			}
		}

	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	LogSystem::getInstance().setSysLogPath("Log");
	LogSystem::getInstance().setGameLogicLogPath("Log");
	LogSystem::getInstance().setPartName("abc");
	LogSystem::getInstance().setLogLevel(1023);
	LogSystem::getInstance().setEnableConsole(false);
	//LogSystem::getInstance().setSaveToFile(true);
	ThreadMonitor::getInstance().initialize();
	ThreadMonitor::getInstance().setPrintLog(false);
	ThreadMonitor::getInstance().setCalcFrequency(5);
	ThreadMonitor::getInstance().start();
	DWORD threadId = ::GetCurrentThreadId();
	HANDLE threadHandle = NULL;
	DuplicateHandle(
		GetCurrentProcess(),        // 进程的伪句柄
		GetCurrentThread(),         // 线程的伪句柄
		GetCurrentProcess(),        // 进程的实句柄
		&threadHandle,              // 线程转换后的实句柄
		0,                          //Ignored due to DUPLICATE_SAME_ACCESS
		FALSE,						// 新线程不被继承
		DUPLICATE_SAME_ACCESS);		// Newthread handle has same
	START_MONITOR_THREAD((U32)threadId,"Main",threadHandle);

	connectCountPerThread = MAX_CONNECT / THREAD_COUNT;

	OneThreadHandleNew onethreadhandlenew[THREAD_COUNT];
	Int threadIndex[THREAD_COUNT];
	for (Int i = 0; i < THREAD_COUNT; i++)
	{
		threadIndex[i] = i;
	}
	
	
	Bool res = ClientNetApplyManager::getInstance().initialize();
	if (!res)
	{
		return -1;
	}
	for (Int i = 0; i < MAX_CONNECT; i++)
	{
		netId[i] = -1;
	}

	//----------------------------
	/*for (Int i = 0; i < MAX_CONNECT; i++)
	{
		netId[i] = ClientNetApplyManager::getInstance().connectLoginServer(addr);
	}
	Int updateCount = 0;
	while(true)
	{
		updateCount++;
		for (Int i = 0; i < SEND_COUNT; i++)
		{
			GameNetSendDataBufferPtr sendPtr = ClientNetApplyManager::getInstance().getSendDataBuffer();
			ClientNetApplyManager::getInstance().sendFrontServerPacket(netId[i],sendPtr,100);
		}
		ClientNetApplyManager::getInstance().update();
		if (updateCount == 1000)
		{
			Sleep(5);
			updateCount = 0;
		}
	}*/
	//----------------------------
	

	ClientNetApplyManager::getInstance().startThreadAutoHandle();
	
	onethreadhandlenew[0].create(OneFun1,&threadIndex[0],"TEST_THREAD1");
	onethreadhandlenew[1].create(OneFun1,&threadIndex[1],"TEST_THREAD2");
	onethreadhandlenew[2].create(OneFun1,&threadIndex[2],"TEST_THREAD3");
	onethreadhandlenew[3].create(OneFun1,&threadIndex[3],"TEST_THREAD4");
/**/

	while(true)
	{
		std::cin>>flag;
		if (flag == 10)
		{
			break;
		}
		Sleep(100);
	
	}

	for (Int i = 0; i < THREAD_COUNT; i++)
	{
		onethreadhandlenew[i].destory();
	}
	
	//WaitForSingleObject((HANDLE)onethreadhandlenew->getHandle(),INFINITE);
	for (Int i = 0; i < MAX_CONNECT; i++)
	{
		if (netId[i] != -1)
		{
			ClientNetApplyManager::getInstance().close(0,netId[i]);
			netId[i] = -1;
		}
	}
	
	
	ClientNetApplyManager::getInstance().endThreadAutoHandle();

	ClientNetApplyManager::getInstance().unInitialize();

	return 0;
}

