/***************************************************
** Copyright (C) 2006-2010 Orsh
** This file is part of the "Game Launcher".
** All rights reserved
****************************************************/
#ifndef _UPDATE_GAME_VERSION_H_
#define _UPDATE_GAME_VERSION_H_

////////////////////////////////////////////////////////////////////////// include head file.
#include <wx/socket.h>
#include <wx/url.h>
#include "msgDefine.h"

////////////////////////////////////////////////////////////////////////// event flag define.


////////////////////////////////////////////////////////////////////////// class define.
class CUpdateVersion
{
public:
	CUpdateVersion();
	CUpdateVersion(const wxString &host, unsigned int port);
	CUpdateVersion(wxSocketClient *socket);
	~CUpdateVersion();
		
	bool NeedUpdateVersion(const wxString &currentVersion);
	bool CanConnect();
	void SetAddr(const wxString &host, unsigned int port);
	void SetSocket(wxSocketClient *socket);
	bool IsNetWorkBusy(){ return m_inProcess; }

	// test
	void test1();
	void test2(){};
	void test3(){};

protected:
	wxArrayString GetUpdateGameHost();
	wxSocketClient *m_socket;
	wxIPV4address m_addr;
	bool m_inProcess;
	unsigned char m_msgType;
};

#endif