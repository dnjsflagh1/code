
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


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include <windows.h>

#include "MGTypes.h"
#include "MGDefine.h"

#include "MGNet.h"
#include "MGMisc.h"
#include "MGMemory.h"
#include "MGMath.h"
#include "MGFile.h"
#include "MGThread.h"
#include "MGLua.h"

#include <afxdlgs.h>
#include "Resource.h"
#include "GameNetPacket.h"

//��Ϣ�����ʾ���������
#define EDIT_MAX_VISIBLE_LINE 19
//������������
#define CLAN_LIST_MAXNUM 3
//��ɫ��������
#define ROLE_LIST_MAXNUM 15
//�ʺ���������
#define ACCOUNT_MAXNUM 1000
//��Ϣ��¼����-����
#define SYSTEM_INFORMATION_MAXNUM 100
//��Ϣ��ʾ���������
#define MESSAGE_VISIBLE_MAXNUM 4000
//��Ϣ��¼����
#define MESSAGE_INFORMATION_MAXNUM 1000
//�Զ��ƶ������б��С����
#define AUTO_TELE_TABLE_MAXNUM 200
//ÿһ�������¼���������>100
#define CHAT_CHANNEL_INFORMATION_MAXNUM 1000
//ÿ�������¼��ʾ�б���������>100
#define CHAT_CHANNEL_LIST_MAXNUM 1000
//�ͻ��˶�����������
#define	CLIENT_OPERATE_MAX 16

// ���߳��л�����
//#define ONE_THREAD

// ÿ���̴߳���ͻ��� ����
#define MAX_CLIENT_COUNT_PRE_THREAD	100

// LoginServer �˿�
#define LOGINSERVER_PORT 2000

#define INVALID_NET_ID -1
//֪ͨ������ˢ������ӵ�ϵͳ��Ϣ
#define THREAD_MSG_ADD_SYSTEM_MESSAGE		WM_USER+104
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


//#define TEST_THREAD_USE