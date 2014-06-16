#include "StdAfx.h"
#include "UIConfig.h"
#include <assert.h>
#include "Xml.h"
UIConfig::UIConfig()
{
	
}

UIConfig::~UIConfig()
{
	for (std::vector<UICell*>::iterator it = mList.begin(); it != mList.end(); it++)
	{
		delete *it;
	}
	mList.clear();
}

bool UIConfig::OpenUIConfig(const char* fileName)
{
	std::string		szFileFath;
	char			szFileName[256]; 

	char			szDrive[256]; 
	char			szDir[256]; 
	char			szPath[256]; 

	GetModuleFileNameA(NULL,szFileName,256); 

	_splitpath(szFileName,szDrive,szDir,NULL,NULL); 
	sprintf(szPath, "%s%s",szDrive,szDir);
	szFileFath = szPath;                       //当前应用程序所在路径
	szFileFath += fileName;                     //CSV文件所在路径

	XmlDocument xDoc;
	if(!xDoc.Open(szFileFath.c_str()))
	{
		return false;
	}
	//parse here ...
	const XmlNode* pRoot = xDoc.GetRoot();
	if(pRoot == NULL)
	{
		xDoc.Close();
		return false;
	}
	int nCnt = pRoot->GetChildNodeCount();
	for(int i = 0; i < nCnt; i++)
	{
		const XmlNode* pChildNode	=	pRoot->GetChildNode(i);
		if(pChildNode == NULL) continue;
		UICell* pCell = new UICell;
		const char* szAttrib = NULL;
		if(!_stricmp(pChildNode->GetName(),"Dialog"))
		{
			szAttrib = pChildNode->QueryAttrib("Name");
			if(szAttrib != NULL)
			pCell->m_szName = _strdup(szAttrib);
			szAttrib = pChildNode->QueryAttrib("Img");
			if(szAttrib)
				pCell->m_szPicName = _strdup(szAttrib);
			szAttrib = pChildNode->QueryAttrib("BackgroundColor");
			if(szAttrib != NULL)
			{
				int r,g,b;
				sscanf(szAttrib,"RGB(%d,%d,%d)",&r,&g,&b);
				pCell->m_xBackgroundColor = RGB(r,g,b);
			}
		}
		else if(!_stricmp(pChildNode->GetName(),"Button"))
		{
			szAttrib = pChildNode->QueryAttrib("Name");
			if(szAttrib != NULL)
				pCell->m_szName = _strdup(szAttrib);
			szAttrib = pChildNode->QueryAttrib("Img");
			if(szAttrib)
				pCell->m_szPicName = _strdup(szAttrib);
			pCell->m_rcPosInWnd.left = atoi(pChildNode->QueryAttrib("Left"));
			pCell->m_rcPosInWnd.top = atoi(pChildNode->QueryAttrib("Top"));
			int nW = atoi(pChildNode->QueryAttrib("Width"));
			int nH = atoi(pChildNode->QueryAttrib("Height"));
			pCell->m_rcPosInWnd.right = pCell->m_rcPosInWnd.left + nW;
			pCell->m_rcPosInWnd.bottom = pCell->m_rcPosInWnd.top + nH;
			for(int j = 0; j < btn_max; j++)
			{
				pCell->m_rcOffsetInImg[j].left = j*nW;
				pCell->m_rcOffsetInImg[j].right = j*nW + nW;
				pCell->m_rcOffsetInImg[j].top = 0;
				pCell->m_rcOffsetInImg[j].bottom = nH;
			}

			szAttrib = pChildNode->QueryAttrib("BackgroundColor");
			if(szAttrib != NULL)
			{
				int r,g,b;
				sscanf(szAttrib,"RGB(%d,%d,%d)",&r,&g,&b);
				pCell->m_xBackgroundColor = RGB(r,g,b);
			}
		}
		else if(!_stricmp(pChildNode->GetName(),"Rgn"))
		{
			szAttrib = pChildNode->QueryAttrib("Name");
			if(szAttrib != NULL)
				pCell->m_szName = _strdup(szAttrib);
			szAttrib = pChildNode->QueryAttrib("Img");
			if(szAttrib)
				pCell->m_szPicName = _strdup(szAttrib);
			szAttrib = pChildNode->QueryAttrib("BkgndImg");
			if(szAttrib != NULL)
				pCell->m_szBkgndPicName = _strdup(szAttrib);
			szAttrib = pChildNode->QueryAttrib("Color");
			if(szAttrib != NULL)
			{
				int r,g,b;
				sscanf(szAttrib,"RGB(%d,%d,%d)",&r,&g,&b);
				pCell->m_xKeyColor = RGB(r,g,b);
			}
			pCell->m_rcPosInWnd.left = atoi(pChildNode->QueryAttrib("Left"));
			pCell->m_rcPosInWnd.top = atoi(pChildNode->QueryAttrib("Top"));
			int nW = atoi(pChildNode->QueryAttrib("Width"));
			int nH = atoi(pChildNode->QueryAttrib("Height"));
			pCell->m_rcPosInWnd.right = pCell->m_rcPosInWnd.left + nW;
			pCell->m_rcPosInWnd.bottom = pCell->m_rcPosInWnd.top + nH;
			szAttrib = pChildNode->QueryAttrib("BackgroundColor");
			if(szAttrib != NULL)
			{
				int r,g,b;
				sscanf(szAttrib,"RGB(%d,%d,%d)",&r,&g,&b);
				pCell->m_xBackgroundColor = RGB(r,g,b);
			}
		}
		mList.push_back(pCell);
	}
	xDoc.Close();
	return true;
}

UICell* UIConfig::GetUIConfig(const char* szName)
{
	for(std::vector<UICell*>::iterator it = mList.begin(); it != mList.end(); it++)
	{
		UICell* pCell = (UICell*)*it;
		if(pCell != NULL && pCell->m_szName != NULL && !_stricmp(pCell->m_szName,szName))
			return pCell;
	}
	return NULL;
}