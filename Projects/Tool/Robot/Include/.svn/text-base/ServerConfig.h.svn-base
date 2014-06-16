#ifndef _SERVERMANAGER_H_
#define _SERVERMANAGER_H_
class CServerConfig
{
public:
	CServerConfig(void);
	~CServerConfig(void);

	static bool loadServerInfo();
	static void freeServerInfo();

	static CString getServerName(DWORD index);
	static CString getServerIP(DWORD index);
	static CString getServerIP(CString strServerName);
	static	CString mDbPsw;
private:
	struct sServerInfo
	{
		CString strServerName;
		CString strServerIP;
	};
	static CList<sServerInfo*,sServerInfo*> m_ServerInfoList;
};
#endif //_SERVERMANAGER_H_