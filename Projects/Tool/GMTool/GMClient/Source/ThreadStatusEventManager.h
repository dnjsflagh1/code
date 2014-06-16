/******************************************************************************/
#ifndef _THREADSTATUSEVENTMANAGER_H_
#define _THREADSTATUSEVENTMANAGER_H_
/******************************************************************************/
#include "Lock.h"

/******************************************************************************/
namespace MG
{
	class ThreadStatusEventManager
	{
	public:
		SINGLETON_INSTANCE(ThreadStatusEventManager)

		static const U64 LittleTime       = 5; 
		static const U64 ShortTime        = 2*30; 
		static const U64 NormalTime       = 10*30; 
		static const U64 LongTime         = 20*30; 
		static const U64 EndLessTime      = 30*30; 
		static const U64 WaitDelta        = 1000;

		Bool        waitDirtyOverTime(std::string name);    
		void        setDirty(std::string name, U64 time=NormalTime);
		void        clearDirty(std::string name);
		void        clearAllDirty();
		Bool        hasDirty(std::string name,Bool timed=true);
		Bool        isDirtyOverTime(std::string name,Bool isLock=true);

	private:
		typedef std::map<std::string, std::pair<Bool, U64>> ThreadDirtyStatusMap;
		ThreadDirtyStatusMap	mDirtyStatusMap;
		Critical				mLock;
	};
}


/******************************************************************************/

#endif //_UTILITY_H_

