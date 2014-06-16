
// MGRobot.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CMGRobotApp:
// 有关此类的实现，请参阅 MGRobot.cpp
//

class CMGRobotApp : public CWinAppEx
{
public:
	CMGRobotApp();
// 重写
public:
	virtual BOOL	InitInstance();
	virtual int		ExitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

// 载入游戏资源			
	bool				loadGameRes();
	void				unLoadGameRes();

// 游戏主线程
public:
	MG::OneThreadHandleNew	mThreadHandle;
	MG::InterLocked			mIsThreadActive;
	bool					mIsUpdate;
	static void				gameRun(MG::Ptr ptr) ;

};

extern CMGRobotApp theApp;