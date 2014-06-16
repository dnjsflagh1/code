#include "stdafx.h"
#include "afxdao.h"
#include "ServerConfig.h"


CList<CServerConfig::sServerInfo*,CServerConfig::sServerInfo*> CServerConfig::m_ServerInfoList;
CString	CServerConfig::mDbPsw = ";PWD=tdxh";

CServerConfig::CServerConfig(void)
{
}

CServerConfig::~CServerConfig(void)
{
}

bool CServerConfig::loadServerInfo()
{
	static int nVerify=0;
	CDaoDatabase dbItems;
	CDaoRecordset rdItems(&dbItems);
	try
	{
		dbItems.Open("MGRobotData.mdb",FALSE,TRUE,mDbPsw);
		rdItems.Open(dbOpenSnapshot,"SELECT * FROM ServerList;",dbReadOnly);
		while (!rdItems.IsEOF())
		{ 
			COleVariant varServerName=rdItems.GetFieldValue("SERVERNAME");
			if (varServerName.vt!=VT_BSTR)
			{
				rdItems.MoveNext();
				continue;
			}
			COleVariant varServerIP=rdItems.GetFieldValue("SERVERADDRESS");
			if (varServerIP.vt!=VT_BSTR)
			{
				rdItems.MoveNext();
				continue;
			}
			
			sServerInfo *pServerInfo=new sServerInfo;
			pServerInfo->strServerName=(char*)varServerName.bstrVal;
			pServerInfo->strServerIP=(char*)varServerIP.bstrVal;
			m_ServerInfoList.AddTail(pServerInfo);
			rdItems.MoveNext();
		}
	}
	catch(CDaoException * e)
	{
		if (rdItems.IsOpen())
		{
			rdItems.Close();
		}
		if (dbItems.IsOpen())
		{
			dbItems.Close();
		}
		return false;
	}
	dbItems.Close();
	return true;
}

void CServerConfig::freeServerInfo()
{
	POSITION pos;
	while (pos=m_ServerInfoList.GetHeadPosition())
	{
		sServerInfo *pServerInfo=m_ServerInfoList.GetAt(pos);
		m_ServerInfoList.RemoveAt(pos);
		delete pServerInfo;
	}
}

CString CServerConfig::getServerName(DWORD index)
{
	DWORD n=(DWORD)m_ServerInfoList.GetCount();
	if (index < n)
	{
		POSITION pos=m_ServerInfoList.FindIndex(index);
		if (pos==NULL) return NULL;
		return m_ServerInfoList.GetAt(pos)->strServerName;
	}
	return NULL;
}

CString CServerConfig::getServerIP(DWORD index)
{
	DWORD n=(DWORD)m_ServerInfoList.GetCount();
	if (index < n)
	{
		POSITION pos=m_ServerInfoList.FindIndex(index);
		if (pos==NULL) return NULL;
		return m_ServerInfoList.GetAt(pos)->strServerIP;
	}
	return NULL;
}

CString CServerConfig::getServerIP(CString strServerName)
{
	POSITION pos=m_ServerInfoList.GetHeadPosition();
	while (pos)
	{
		sServerInfo *pServerInfo=m_ServerInfoList.GetNext(pos);
		if (pServerInfo->strServerName==strServerName)
		{
			return pServerInfo->strServerIP;
		}
	}
	return NULL;
}

