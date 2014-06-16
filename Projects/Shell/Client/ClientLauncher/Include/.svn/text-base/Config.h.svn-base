#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "stdafx.h"
#include <vector>
#include <string>
//#include "xnExtstr.h"

struct FTP_DATA
{
	std::wstring ip;
	std::wstring userName;
	std::wstring password;
	std::wstring updatePath;
};

struct LABEL_DATA
{
	int				posx,posy;
	std::wstring	strLabel;
	std::wstring	strUrl;
	COLORREF		txtColor1;
	COLORREF		txtColor2;
};
enum
{
	renderH,
	renderN,
	renderL,
};

enum
{
	txt_connecttoserver = 1,
	txt_curdownloading = 4,
	txt_checkmyself = 14,
	txt_checkmyself_failed = 15,
	txt_getingmyself,
	txt_getingupdatedat,
};
struct StarterConfig
{
	bool						m_IsUpdate;
	std::wstring				m_HttpUrl;
	std::wstring				m_szUpdateURL;
	std::wstring				m_ClientName;
	std::wstring				m_StrEndAction;
	std::wstring				m_StrCaption;
	bool						m_IsDll;
	int							m_eaPosW;
	int							m_eaPosH;
	int							m_eaDelay;
	std::wstring				m_szConfigCaption;
	std::wstring				m_szRenderName;
	std::wstring				m_szRenderH;
	std::wstring				m_szRenderN;
	std::wstring				m_szRenderL;

	std::wstring				m_szStateURL;

	std::vector<std::wstring>	m_msgList;



	StarterConfig();
	~StarterConfig();
	void	ReadConfig(char * fileName);
	void	RandFtp(bool stateFtp);
	WCHAR*	GetMsg(int index);
};
void toString( char* src, std::wstring& dest, int size = -1, unsigned int codePage = CP_ACP);
//-----------------------------------------------------------------------------

#endif
