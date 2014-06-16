#ifndef _JCH_UI_CONFIG_H
#define _JCH_UI_CONFIG_H
#include <vector>
enum
{
	btn_mouseout,
	btn_mousein,
	btn_mousedown,
	btn_disable,
	btn_max
};

struct UICell
{
	char*		m_szName;
	char*		m_szPicName;
	char*		m_szBkgndPicName;
	CRect		m_rcOffsetInImg[btn_max];
	CRect		m_rcPosInWnd;
	COLORREF	m_xKeyColor;
	COLORREF	m_xBackgroundColor;
	UICell()
	{
		m_szName = NULL;
		m_szPicName = NULL;
		m_szBkgndPicName = NULL;
		memset(m_rcOffsetInImg,0,sizeof(CRect)*btn_max);
		memset(&m_rcPosInWnd,0,sizeof(CRect));
		m_xKeyColor = RGB(255,255,255);
		m_xBackgroundColor = RGB(255,255,255);
	}
	~UICell()
	{
		if(m_szName != NULL)
		{
			free(m_szName);
			m_szName = NULL;
		}
		if(m_szPicName != NULL)
		{
			free(m_szPicName);
			m_szPicName = NULL;
		}
		if(m_szBkgndPicName != NULL)
		{
			free(m_szBkgndPicName);
			m_szBkgndPicName = NULL;
		}
	}
};


class	UIConfig
{
	std::vector<UICell*>		mList;
public:
	UIConfig();
	~UIConfig();
	bool		OpenUIConfig(const char* szFileName);
	UICell*		GetUIConfig(const char* szName);
	
};
#endif