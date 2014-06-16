
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

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

//信息框可显示的最大行数
#define EDIT_MAX_VISIBLE_LINE 19
//家族数量限制
#define CLAN_LIST_MAXNUM 3
//角色数量限制
#define ROLE_LIST_MAXNUM 15
//帐号数最限制
#define ACCOUNT_MAXNUM 1000
//信息记录限制-废弃
#define SYSTEM_INFORMATION_MAXNUM 100
//信息显示的最大限制
#define MESSAGE_VISIBLE_MAXNUM 4000
//信息记录限制
#define MESSAGE_INFORMATION_MAXNUM 1000
//自动移动坐标列表大小限制
#define AUTO_TELE_TABLE_MAXNUM 200
//每一项聊天记录的最大限制>100
#define CHAT_CHANNEL_INFORMATION_MAXNUM 1000
//每个聊天记录显示列表的最大限制>100
#define CHAT_CHANNEL_LIST_MAXNUM 1000
//客户端对象最多操作数
#define	CLIENT_OPERATE_MAX 16

// 多线程切换开关
//#define ONE_THREAD

// 每个线程处理客户端 数量
#define MAX_CLIENT_COUNT_PRE_THREAD	100

// LoginServer 端口
#define LOGINSERVER_PORT 2000

#define INVALID_NET_ID -1
//通知主窗口刷新新添加的系统消息
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