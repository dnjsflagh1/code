
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

//#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
//#include <afxcontrolbars.h> // MFC support for ribbons and control bars

#define CWinAppEx CWinApp 

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

////////////////////////////////////////////////////////////

#include "MGTypes.h"
#include "MGDefine.h"

#include "MGNet.h"
#include "MGMisc.h"
#include "MGMemory.h"
#include "MGDB.h"
#include "MGMath.h"
#include "MGFile.h"
#include "MGThread.h"

#include "ServerDllInterface.h"

////////////////////////////////////////////////////////////


#define LAUNCH_SERVER_START				1 + WM_USER
#define LAUNCH_SERVER_CONNECT			2 + WM_USER
#define LAUNCH_UPDATE					3 + WM_USER
#define LAUNCH_WRITE_DB_LOG				4 + WM_USER
#define LAUNCH_WRITE_CORE_LOG			5 + WM_USER
#define LAUNCH_WRITE_SHELL_LOG			6 + WM_USER
#define LAUNCH_SERVER_DISCONNECT		7 + WM_USER

struct LuanchUpdateInfo
{
	MG::Flt		recvSpeedBytes;
	MG::Flt		recvMaxSpeedBytes;
	MG::Flt		recvMinSpeedBytes;
	MG::I32		recvBytes;

	MG::Flt		recvSpeedPackets;
	MG::Flt		recvMaxSpeedPackets;
	MG::Flt		recvMinSpeedPackets;
	MG::I32		recvPackets;
	

	MG::Flt		sendSpeedBytes;
	MG::Flt		sendMaxSpeedBytes;
	MG::Flt		sendMinSpeedBytes;
	MG::I32		sendBytes;

	MG::Flt		sendSpeedPackets;
	MG::Flt		sendMaxSpeedPackets;
	MG::Flt		sendMinSpeedPackets;
	MG::I32		sendPackets;

	MG::I32		currConnectionCount;
};