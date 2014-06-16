#include "stdafx.h"
#include "config.h"
//#include <xnfile.h>
//#include <UINI.h>

StarterConfig::StarterConfig()
{
	m_IsUpdate = TRUE;
};

StarterConfig::~StarterConfig()
{
	m_msgList.clear();
}
void StarterConfig::ReadConfig(char * fileName)
{
//	if (!fileName)
//		return;
//	int fsize=0;
//	char* pSrc = (char*)xnFileRead(fileName, &fsize);
//	if (!pSrc)
//		return;
//	UINI ini;
//	bool bResult = ini.CreateFromMemory(pSrc, fsize, L"");
//	free(pSrc);
//	pSrc = NULL;
//	if (!bResult)
//		return;
//	ini.SetGroup(L"MAIN");
//	m_HttpUrl		= ini.GetValue(L"URL");
//	m_szUpdateURL	= ini.GetValue(L"UpdateURL");
//	m_ClientName	= ini.GetValue(L"Client");
//	m_IsDll			= _wtoi(ini.GetValue(L"ClientType", L"1").c_str());
//	int language	= _wtoi(ini.GetValue(L"Language",L"0").c_str());
//	m_IsUpdate		= _wtoi(ini.GetValue(L"Update",L"1").c_str());
//
//	ini.SetGroup(L"EndAction");
//	m_StrEndAction	= ini.GetValue(L"URL");
//	m_eaPosW		= _wtoi(ini.GetValue(L"POSW",L"100").c_str());
//	m_eaPosH		= _wtoi(ini.GetValue(L"POSH",L"100").c_str());	
//	m_eaDelay		= _wtoi(ini.GetValue(L"Delay",L"5").c_str());
//
//	WCHAR strTmp[MAX_PATH];
//
//
//	ini.SetGroup(L"StateServer");
//	m_szStateURL	= ini.GetValue(L"URL");
//
//
///*	LANGID langID = GetSystemDefaultLangID();
//	switch(langID)
//	{
//	case 0x0404:
//	case 0x1404:
//	case 0x1004:
//		ini.SetGroup(L"TCHINESE_MSG");
//		break;
//	case 0x0804:
//		ini.SetGroup(L"SCHINESE_MSG");
//		break;
//	case 0x0411:
//		ini.SetGroup(L"JAPANESE_MSG");
//		break;
//	default:
//		ini.SetGroup(L"ENGLISH_MSG");
//		break;
//	}
//*/
//	switch(language)
//	{
//	case 0:
//		ini.SetGroup(L"TCHINESE_MSG");
//		break;
//	case 1:
//		ini.SetGroup(L"SCHINESE_MSG");
//		break;
//	case 2:
//		ini.SetGroup(L"JAPANESE_MSG");
//		break;
//	default:
//		ini.SetGroup(L"ENGLISH_MSG");
//		break;
//	}
//	m_StrCaption = ini.GetValue(L"Caption");
//	int count = _wtoi(ini.GetValue(L"MSGCOUNT", L"0").c_str());
//	for (int i=0;i<count;i++)
//	{
//		swprintf(strTmp, _countof(strTmp), L"MSG%d",i+1);
//		m_msgList.push_back(ini.GetValue(strTmp));
//	}
//	m_szConfigCaption = ini.GetValue(L"ConfigCaption");
//	m_szRenderName = ini.GetValue(L"ConfigRenderName");
//	m_szRenderH = ini.GetValue(L"ConfigRenderH");
//	m_szRenderN = ini.GetValue(L"ConfigRenderN");
//	m_szRenderL = ini.GetValue(L"ConfigRenderL");
//	ini.Destroy();
}


WCHAR* StarterConfig::GetMsg(int index)
{
	if (index > 0 && index <= m_msgList.size())
		return (WCHAR*)m_msgList[index-1].c_str();
	return NULL;
}
void toString( char* src, std::wstring& dest, int size /*= -1*/, unsigned int codePage /*= CP_ACP*/ )
{
	dest = L'\0';
	if (!src)
	{
		return;
	}
	if (size <= 0)
	{
		size = (int)strlen(src);
		if (size <= 0)
			return;
	}

	int maxsize = sizeof(wchar_t) * (size + 1);
	wchar_t* pML = (wchar_t*)malloc(maxsize);
	if (!pML)
	{
		return;
	}

	pML[size] = 0;//it is wide char, so the size is (char size / 2)

	int value = MultiByteToWideChar(codePage, 0, src, size, pML, size);
	if (value>=0 && value<=size)
	{
		pML[value] = 0;
	}
	dest = pML;
	free(pML);
}