//**************************************************************************************************
#ifndef _MYTHREAD_H_
#define _MYTHREAD_H_
//**************************************************************************************************
#include "wx/thread.h"
class LauncherApp;
typedef void* (*ThreadFun)(void* param);
class MyThread : public wxThread
{
public:
	MyThread(void *param,ThreadFun fun);
	virtual void *Entry();
	virtual void OnExit();

public:
	unsigned int	mCount;
	void *			mParam;
	ThreadFun		mFun;
};
//**************************************************************************************************
#endif