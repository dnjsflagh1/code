/******************************************************************************/
#include "stdafx.h"
#include "Thread.h"
/******************************************************************************/
//-------------------------------------------------------------------------------
OneThreadHandle::OneThreadHandle()
:mHandle(NULL),
mCallback(NULL),
mPtr(NULL)
{

}

//-------------------------------------------------------------------------------
OneThreadHandle::~OneThreadHandle()
{
	destory();
}

//-------------------------------------------------------------------------------
MG::Bool OneThreadHandle::create(void (*callback)(MG::Ptr),MG::Ptr ptr)
{
	destory();
	mCallback = callback;
	mPtr = ptr;
	mHandle = CreateThread( NULL, 0, threadFunction, (LPVOID)this, 0, NULL );
	if (mHandle > 0)
	{
		mIsRun = true;
		return true;
	}
	else
	{
		mIsRun = false;
	}
	return false;
}

//-------------------------------------------------------------------------------
MG::Bool OneThreadHandle::destory()
{
	if ( mHandle )
	{
		mIsRun = false;
		if(mHandle)
		{
			Sleep(10);
			CloseHandle(mHandle);
			mHandle = NULL;
			Sleep(5);
		}
	}
	return true;
}

//-------------------------------------------------------------------------------
DWORD API OneThreadHandle::threadFunction(MG::Ptr p)
{
	OneThreadHandle* mgr = (OneThreadHandle*)p;
	if (mgr)
	{
		mgr->mCallback(p);
		mgr->mHandle = NULL;
	}
	ExitThread( 0 );
	return 0;
}
//-------------------------------------------------------------------------------
void* OneThreadHandle::getParam()
{
	return mPtr;
}
//-------------------------------------------------------------------------------
MG::Bool OneThreadHandle::isRun()
{
	return mIsRun;
}
//-------------------------------------------------------------------------------
MG::Ptr OneThreadHandle::getHandle()
{
	return mHandle;
}