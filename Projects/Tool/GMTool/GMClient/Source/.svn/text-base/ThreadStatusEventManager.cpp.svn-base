/******************************************************************************/
#include "stdafx.h"
#include <ThreadStatusEventManager.h>
/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//class ThreadStatusEventManager 
	/******************************************************************************/
	//-----------------------------------------------------------------------------
	bool ThreadStatusEventManager::waitDirtyOverTime(std::string name)
	{
		int LIMIT_LOOP = 30;
		while(--LIMIT_LOOP>=0)
		{   
			if (!hasDirty(name))
				return false;
			if (isDirtyOverTime(name))
			{
				clearDirty(name);
				return true;
			}
			Sleep(WaitDelta);
		}
		return true;
	}
	//-----------------------------------------------------------------------------
	void ThreadStatusEventManager::setDirty(std::string name, U64 time)
	{
		mLock.lock();
		{
			U64 futureTime       = MGTimeOp::getFutureTime(0,0,time);
			mDirtyStatusMap[name]  = std::pair<bool, U64>(true, futureTime);
		}
		mLock.unlock();
	}
	//-----------------------------------------------------------------------------
	void ThreadStatusEventManager::clearDirty(std::string name)
	{
		mLock.lock();
		{
			ThreadDirtyStatusMap::iterator it = mDirtyStatusMap.find(name);
			if ( it != mDirtyStatusMap.end() )
			{
				it->second.first = false;
			}
		}
		mLock.unlock();
	}
	//-----------------------------------------------------------------------------
	void ThreadStatusEventManager::clearAllDirty()
	{
		mLock.lock();
		{
			ThreadDirtyStatusMap::iterator it = mDirtyStatusMap.begin();
			for (;it!=mDirtyStatusMap.end();it++)
			{
				it->second.first = false;
			}
		}
		mLock.unlock();
	}
	//-----------------------------------------------------------------------------
	bool ThreadStatusEventManager::hasDirty(std::string name, bool timed)
	{
		bool result = false;
		mLock.lock();
		{
			ThreadDirtyStatusMap::iterator it = mDirtyStatusMap.find(name);
			if ( it != mDirtyStatusMap.end() )
			{
				if (timed&&isDirtyOverTime(name,false))
				{
					it->second.first = false;
				}
				result = it->second.first;
			}
		}
		mLock.unlock();
		return result;
	}
	//-----------------------------------------------------------------------------
	bool ThreadStatusEventManager::isDirtyOverTime(std::string name,bool isLock)
	{
		bool result = true;
		if (isLock) mLock.lock();
		{
			ThreadDirtyStatusMap::iterator it = mDirtyStatusMap.find(name);
			if ( it != mDirtyStatusMap.end() )
			{
				result = MGTimeOp::timePass(it->second.second);
			}
		}
		if (isLock) mLock.unlock();
		return result;
	}
}
