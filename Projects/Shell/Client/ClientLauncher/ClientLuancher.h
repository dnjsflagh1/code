
// ClientLuancher.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "DllLoader.h"
#include "Thread.h"
// CClientLuancherApp:
// �йش����ʵ�֣������ ClientLuancher.cpp
//

class CClientLuancherApp : public CWinAppEx
{
public:
	CClientLuancherApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

	//MG::CsvReader csv;
	//MG::DllLoader dllLoader;
public:
	OneThreadHandle		mGameThread;

	static void		    gameThread(MG::Ptr ptr);
	bool				mIsRun;
};

extern CClientLuancherApp theApp;