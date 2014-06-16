/******************************************************************************/
#include "stdafx.h"
#include "CenterGameTimeSystem.h"
#include "ServerManager.h"
#include "CenterServerMain.h"
#include "TimeNetPacket.h"
/******************************************************************************/
#define TIMESYSTE_UPDATE_TIME 10.0f
namespace MG
{

	//-----------------------------------------------------------------------------
	CenterGameTimeSystem::CenterGameTimeSystem()
	{
		
	}
	//-----------------------------------------------------------------------------
	CenterGameTimeSystem::~CenterGameTimeSystem()
	{

	}
	//-----------------------------------------------------------------------------
	MG::U64 CenterGameTimeSystem::getCurrActualTime()
	{
		return mGameStartTime + (U64)mGameStartGameTick;
	}
	//-----------------------------------------------------------------------------
	MG::Dbl CenterGameTimeSystem::getCurrGameStartActualTick()
	{
		// ��Ϸ��ǰƫ��ʱ��
		return mGameStartGameTick;
	}
	//-----------------------------------------------------------------------------
	void CenterGameTimeSystem::update()
	{
		//-------------------------------------------------
		static Dbl costTime = 0;
		static Dbl deltaTime = 0;

		deltaTime = mTimer.getTimeOffset();

		mGameStartGameTick += deltaTime;
		costTime += deltaTime;
		if (costTime > 0.0f)
		{
			if (costTime - TIMESYSTE_UPDATE_TIME >= 0.0f)
			{
				Dbl tempCost = costTime ;
				while((tempCost -= TIMESYSTE_UPDATE_TIME) >= 0.0f)
				{
					syncTimeToAllServer(getCurrActualTime());
					SYSTEMTIME actualTime = MGTimeOp::getLocalTime(getCurrActualTime());
					printf("����ʱ�� %d-%d-%d %d:%d:%d\n",
						actualTime.wYear,actualTime.wMonth,actualTime.wDay,
						actualTime.wHour,actualTime.wMinute,actualTime.wSecond);
				}
				costTime = tempCost + TIMESYSTE_UPDATE_TIME;
			}
		}
		else
		{
			DYNAMIC_ASSERT(false);
		}
		//--------------------------------------------------
		//static U32 currTick = getCurrTick;
		//static U32 lastTick = currTick;
		//currTick = getCurrTick();

		//static U32 costTime = 0;
		//static U32 deltaTime = 0;

		//// ÿ�θ���ʱ���
		//deltaTime = currTick - lastTick;
		//// �ۼƸ���ʱ���
		//costTime += deltaTime;
		////MG_LOG(out_error,"�ۼ�ʱ��%d\n",costTime);
		//// ������Ϸ��ʼ���ƫ��ʱ��
		//mGameStartGameTick = currTick - mGameStartSystemTick;

		//if (deltaTime < 0)
		//// �����������������49.7������ʱ��ϵͳ ʱ��� <= 0
		//{
		//	costTime = costTime - deltaTime;
		//	_resetTimeSystem(currTick);
		//}

		//if (costTime >= TIMESYSTE_UPDATE_TIME)
		//// ÿTIMESYSTE_UPDATE_TIME�����룩����һ��
		//{
		//	I32 tempCost = costTime;
		//	while((tempCost -= TIMESYSTE_UPDATE_TIME) >= 0)
		//	{
		//		// ��������ʱ��
		//		SYSTEMTIME actualTime = MGTimeOp::getLocalTime(getCurrActualTime());
		//		printf("����ʱ�� %d-%d-%d %d:%d:%d\n",
		//			actualTime.wYear,actualTime.wMonth,actualTime.wDay,
		//			actualTime.wHour,actualTime.wMinute,actualTime.wSecond);
		//	}
		//	costTime %= TIMESYSTE_UPDATE_TIME;
		//}
		//lastTick = currTick;

	}
	//-----------------------------------------------------------------------------
	MG::Bool CenterGameTimeSystem::initialize()
	{
		// �Ժ󽫸ĳɻ�ȡ����ʱ��	
		mGameStartTime = time(NULL);
		mGameStartGameTick = 0.0f;

		if(!mTimer.initialize(true))
			return false;
		
		if (mGameStartTime == -1)
		{
			return false;
		}
		
		//if(!mThread.create(timerThread,this))
		//	return false;

#ifdef _DEBUG
		Thread::SetThreadName(mThread.getThreadId(),"CenterGameTimeSystem::timerThread");
#endif

		SetThreadAffinityMask(mThread.getHandle(),1);

		return true;
		
	}
	//-----------------------------------------------------------------------------
	MG::Bool CenterGameTimeSystem::unInitialize()
	{
        mThread.destory();

		return true;
	}
	//-----------------------------------------------------------------------------
	void CenterGameTimeSystem::timerThread( Ptr ptr )
	{
		DYNAMIC_ASSERT(ptr);
		OneThreadHandle* thd = (OneThreadHandle*)ptr;	
		if (thd)
		{
			if (thd->getParam())
			{
				CenterGameTimeSystem* timeSystem = (CenterGameTimeSystem*)thd->getParam();

				while(!CenterServerMain::getInstance().getServerLauncher()->isNetAvailable())
				{
					Sleep(100);
				}

				while(thd->isRun())
				{
					timeSystem->update();
					Sleep(5);
				}
			}
		}
	}
	//-----------------------------------------------------------------------------
	void CenterGameTimeSystem::syncTimeToAllServer(U64 currTime)
	{
		GameNetSendDataBufferPtr dataPtr; 
        CenterServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer(dataPtr);
		GameNetPacketData* packet = (GameNetPacketData*) dataPtr->getLogicData();
		if ( NULL == packet )
		{
			DYNAMIC_ASSERT(0);
			return;
		}

		packet->channel = GNPC_TIME;
		packet->type    = PT_TIME_E2S_SYNC;
		PT_TIME_E2S_SYNC_DATA* data = (PT_TIME_E2S_SYNC_DATA*)(packet->data);
		if (NULL == data)
		{
			DYNAMIC_ASSERT(0);
			return;
		}
		data->currTime = currTime;
		//ServerManager::getInstance().boardcastNetPacketToServers(dataPtr,GameNetPacketData_INFO::headSize + PT_TIME_E2S_SYNC_DATA_INFO::dataSize);
	}



	//-----------------------------------------------------------------------------
	

	

}