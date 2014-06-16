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
	int   cntShare;                 // ����Ŀ¼����   
	wxString  shareDir[30];         // ����Ŀ¼����   
	wxString  ComputerName;         // ���������   
	wxString  IPAddr;               // IP
	wxString  Group;                // ���   
	wxString  Comment;              // ְ��   

	wxString  P_WorkedMemory;		// ���������ڴ�   
	wxString  P_AllMemory;			// ���������ڴ�   
	wxString  V_WorkedMemory;		// ���������ڴ�   
	wxString  V_AllMemory;			// ���������ڴ�   

	int   DiskNumber;               // ������Ŀ   
	wxString  DiskDrive[26][2];		// ���д�����Ϣ   

	wxString  NetCard;              // ����   
	wxString  VGACard;              // �Կ�   
	wxString  SoundCard;            // ����   
	wxString  CD_ROM;				// ����   
	wxString  Floppy;				// ����   
	wxString  HardDisk;             // Ӳ�̿�����   
	wxString  CPU;                  // CPU
	wxString  Mouse;                // ���   
	wxString  Keyboard;             // ����   
	wxString  OSVersion;            // ����ϵͳ�汾   

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