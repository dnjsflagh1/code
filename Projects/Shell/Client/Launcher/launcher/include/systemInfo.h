/***************************************************
** Copyright (C) 2006-2010 Orsh
** This file is part of the "Game Launcher".
** All rights reserved
****************************************************/

#ifndef _LAUNCHER_SYSTEMINFO_H_
#define _LAUNCHER_SYSTEMINFO_H_

#include <windows.h>
#include <tchar.h>
#include <wx/arrstr.h>
#include <stdio.h>
#include <strsafe.h>

#define BUFSIZE 256
typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);
typedef BOOL (WINAPI *PGPI)(DWORD, DWORD, DWORD, DWORD, PDWORD);

typedef struct   
{   
	int   cntShare;                 // 共享目录总数   
	wxString  shareDir[30];         // 共享目录名称   
	wxString  ComputerName;         // 计算机名称   
	wxString  IPAddr;               // IP
	wxString  Group;                // 组别   
	wxString  Comment;              // 职务   

	wxString  P_WorkedMemory;		// 已用物理内存   
	wxString  P_AllMemory;			// 所有物理内存   
	wxString  V_WorkedMemory;		// 已用虚拟内存   
	wxString  V_AllMemory;			// 所有虚拟内存   

	int   DiskNumber;               // 磁盘数目   
	wxString  DiskDrive[26][2];		// 所有磁盘信息   

	wxString  NetCard;              // 网卡   
	wxString  VGACard;              // 显卡   
	wxString  SoundCard;            // 声卡   
	wxString  CD_ROM;				// 光驱   
	wxString  Floppy;				// 软驱   
	wxString  HardDisk;             // 硬盘控制器   
	wxString  CPU;                  // CPU
	wxString  Mouse;                // 鼠标   
	wxString  Keyboard;             // 键盘   
	wxString  OSVersion;            // 操作系统版本   

}USER_INFO;

class SystemInfo
{
public:
	SystemInfo()
	{
		bIsNt = false;
	}
	static wxString GetOSDisplayString();
	static wxArrayString GetMac();
	static wxString GetVideo();
	static wxString GetDXVersion();
	static wxString GetOpenGLVersion();
	static wxString GetCPUInfo();
	static wxString GetIEInfo();
	static void GetFileVersionOfGame(const wxString &fileName, wxString *resulte);

	/// only show on _DEBUG state.
	static void ShowMessage(const wxString& msg);
	static void GetUserInfo(USER_INFO& userInfo);	
	static bool bIsNt;

protected:
	static bool CheckDisplay(wxString strKey);
};

#endif