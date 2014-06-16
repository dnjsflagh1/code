//**************************************************************************************************
#include "MyThread.h"
#include "launcher.h"
//**************************************************************************************************
MyThread::MyThread(void *param,ThreadFun fun) : wxThread()
{
	wxASSERT(param);
	wxASSERT(fun);
	mCount = 0;
	mParam = param;
	mFun = fun;

}

void* MyThread::Entry()
{
	mFun(mParam);
	return mParam;
}

void MyThread::OnExit()
{
	mCount = 0;
}
//**************************************************************************************************