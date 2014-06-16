#include "systemInfo.h"
#include <IPHlpApi.h>
#include <comdef.h>
#include <WbemIdl.h>
#include <SetupApi.h>
#include <regstr.h>

#ifdef _DEBUG
#include <wx/msgdlg.h>
#endif

#pragma comment (lib, "Version.lib")
#pragma comment (lib, "Setupapi.lib")
#pragma comment( lib, "Winmm.lib" )

wxString SystemInfo::GetOSDisplayString()
{
	char pszOS[256];		// LPSTR
	OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;
	PGNSI pGNSI;
	PGPI pGPI;
	BOOL bOsVersionInfoEx;
	DWORD dwType;
	bIsNt = false;

	ZeroMemory(&si, sizeof(SYSTEM_INFO));
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
		return _T("");

	// Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
	pGNSI = (PGNSI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
	if(NULL != pGNSI)
		pGNSI(&si);
	else 
		GetSystemInfo(&si);

	if ( VER_PLATFORM_WIN32_NT == osvi.dwPlatformId && osvi.dwMajorVersion > 4 )
	{
		bIsNt = true;
		StringCchCopy(pszOS, BUFSIZE, TEXT("系统版本：Microsoft "));

		// Test for the specific product.
		if ( osvi.dwMajorVersion == 6 )
		{
			if( osvi.dwMinorVersion == 0 )
			{
				if( osvi.wProductType == VER_NT_WORKSTATION )
					StringCchCat(pszOS, BUFSIZE, TEXT("Windows Vista "));
				else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2008 " ));
			}

			if ( osvi.dwMinorVersion == 1 )
			{
				if( osvi.wProductType == VER_NT_WORKSTATION )
					StringCchCat(pszOS, BUFSIZE, TEXT("Windows 7 "));
				else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2008 R2 " ));
			}

			pGPI = (PGPI) GetProcAddress(
				GetModuleHandle(TEXT("kernel32.dll")), 
				"GetProductInfo");

			pGPI( osvi.dwMajorVersion, osvi.dwMinorVersion, 0, 0, &dwType);

			switch( dwType )
			{
			case PRODUCT_ULTIMATE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Ultimate Edition" ));
				break;
				//case PRODUCT_PROFESSIONAL:
				//	StringCchCat(pszOS, BUFSIZE, TEXT("Professional" ));
				//	break;
			case PRODUCT_HOME_PREMIUM:
				StringCchCat(pszOS, BUFSIZE, TEXT("Home Premium Edition" ));
				break;
			case PRODUCT_HOME_BASIC:
				StringCchCat(pszOS, BUFSIZE, TEXT("Home Basic Edition" ));
				break;
			case PRODUCT_ENTERPRISE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition" ));
				break;
			case PRODUCT_BUSINESS:
				StringCchCat(pszOS, BUFSIZE, TEXT("Business Edition" ));
				break;
			case PRODUCT_STARTER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Starter Edition" ));
				break;
			case PRODUCT_CLUSTER_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Cluster Server Edition" ));
				break;
			case PRODUCT_DATACENTER_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Datacenter Edition" ));
				break;
			case PRODUCT_DATACENTER_SERVER_CORE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Datacenter Edition (core installation)" ));
				break;
			case PRODUCT_ENTERPRISE_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition" ));
				break;
			case PRODUCT_ENTERPRISE_SERVER_CORE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition (core installation)" ));
				break;
			case PRODUCT_ENTERPRISE_SERVER_IA64:
				StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition for Itanium-based Systems" ));
				break;
			case PRODUCT_SMALLBUSINESS_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Small Business Server" ));
				break;
			case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
				StringCchCat(pszOS, BUFSIZE, TEXT("Small Business Server Premium Edition" ));
				break;
			case PRODUCT_STANDARD_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Standard Edition" ));
				break;
			case PRODUCT_STANDARD_SERVER_CORE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Standard Edition (core installation)" ));
				break;
			case PRODUCT_WEB_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Web Server Edition" ));
				break;
			}
		}

		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
		{
			if( GetSystemMetrics(SM_SERVERR2) )
				StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Server 2003 R2, "));
			else if ( osvi.wSuiteMask & VER_SUITE_STORAGE_SERVER )
				StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Storage Server 2003"));
			//else if ( osvi.wSuiteMask & VER_SUITE_WH_SERVER )
			//	StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Home Server"));
			else if( osvi.wProductType == VER_NT_WORKSTATION &&
				si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
			{
				StringCchCat(pszOS, BUFSIZE, TEXT( "Windows XP Professional x64 Edition"));
			}
			else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2003, "));

			// Test for the server type.
			if ( osvi.wProductType != VER_NT_WORKSTATION )
			{
				if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_IA64 )
				{
					if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Edition for Itanium-based Systems" ));
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise Edition for Itanium-based Systems" ));
				}

				else if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
				{
					if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter x64 Edition" ));
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise x64 Edition" ));
					else StringCchCat(pszOS, BUFSIZE, TEXT( "Standard x64 Edition" ));
				}

				else
				{
					if ( osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Compute Cluster Edition" ));
					else if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Edition" ));
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise Edition" ));
					else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Web Edition" ));
					else StringCchCat(pszOS, BUFSIZE, TEXT( "Standard Edition" ));
				}
			}
		}

		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
		{
			StringCchCat(pszOS, BUFSIZE, TEXT("Windows XP "));
			if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
				StringCchCat(pszOS, BUFSIZE, TEXT( "Home Edition" ));
			else StringCchCat(pszOS, BUFSIZE, TEXT( "Professional" ));
		}

		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
		{
			StringCchCat(pszOS, BUFSIZE, TEXT("Windows 2000 "));

			if ( osvi.wProductType == VER_NT_WORKSTATION )
			{
				StringCchCat(pszOS, BUFSIZE, TEXT( "Professional" ));
			}
			else 
			{
				if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
					StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Server" ));
				else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
					StringCchCat(pszOS, BUFSIZE, TEXT( "Advanced Server" ));
				else StringCchCat(pszOS, BUFSIZE, TEXT( "Server" ));
			}
		}

		// Include service pack (if any) and build number.

		if( _tcslen(osvi.szCSDVersion) > 0 )
		{
			StringCchCat(pszOS, BUFSIZE, TEXT(" ") );
			StringCchCat(pszOS, BUFSIZE, osvi.szCSDVersion);
		}

		TCHAR buf[80];

		StringCchPrintf( buf, 80, TEXT(" (build %d)"), osvi.dwBuildNumber);
		StringCchCat(pszOS, BUFSIZE, buf);

		if ( osvi.dwMajorVersion >= 6 )
		{
			if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
				StringCchCat(pszOS, BUFSIZE, TEXT( ", 64-bit" ));
			else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
				StringCchCat(pszOS, BUFSIZE, TEXT(", 32-bit"));
		}

		return pszOS; 
	}
	else
	{  
		printf( "This sample does not support this version of Windows.\n");
		return _T("");
	}
}

wxArrayString SystemInfo::GetMac()
{	
	wxArrayString arrayResult;
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();			// PIP_ADAPTER_INFO结构体指针存储本机网卡信息	
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);						// 得到结构体大小,用于GetAdaptersInfo参数	
	int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);					// 调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	if (ERROR_BUFFER_OVERFLOW==nRel)
	{
		/*	
			如果函数返回的是ERROR_BUFFER_OVERFLOW
			则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
			这也是说明为什么stSize既是一个输入量也是一个输出量
			释放原来的内存空间
		*/
		delete pIpAdapterInfo;		
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];			// 重新申请内存空间用来存储所有网卡信息		
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);					// 再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量    
	}
	if (ERROR_SUCCESS==nRel)
	{
		int amount = 0;
		// 获取网卡信息
		while (pIpAdapterInfo)
		{	
			IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
			char temp[256];
			sprintf(temp,"网卡%i：%s (%02X-%02X-%02X-%02X-%02X-%02X)",
				amount,
				pIpAddrString->IpAddress.String,
				pIpAdapterInfo->Address[0],
				pIpAdapterInfo->Address[1],
				pIpAdapterInfo->Address[2],
				pIpAdapterInfo->Address[3],
				pIpAdapterInfo->Address[4],
				pIpAdapterInfo->Address[5]
				);
			amount++;
			arrayResult.Add(wxString(temp));
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}
	if (pIpAdapterInfo)
	{	
		// 释放内存空间
		delete pIpAdapterInfo;
	}
	return arrayResult;
}

wxString SystemInfo::GetVideo()
{
	wxString result;
	char szValueData[256];	
	HDEVINFO  hDevInfo = SetupDiGetClassDevs(NULL, REGSTR_KEY_PCIENUM, 0, DIGCF_PRESENT|DIGCF_ALLCLASSES);  
	if  (hDevInfo == INVALID_HANDLE_VALUE)      
		return  _T("");

	//  Show  all  related  device  in  the  PCI  set   
	{  
		SP_DEVINFO_DATA  DeviceInfoData;  
		DeviceInfoData.cbSize  =  sizeof(SP_DEVINFO_DATA);  
		TCHAR  buffer[MAX_PATH];  
		ZeroMemory(buffer, MAX_PATH);  
		HKEY  hCurKey;  
		DWORD dwVDataSize;
		wxString strConstKey,strKey;		
		HKEY  hRootKey  =  HKEY_LOCAL_MACHINE;  
		if (bIsNt)	//bIsNt  
			strConstKey = "SYSTEM\\CurrentControlSet\\Control\\Class\\";  
		else  
			strConstKey = "SYSTEM\\CurrentControlSet\\Services\\Class\\"; 

		for (DWORD i=0; SetupDiEnumDeviceInfo(hDevInfo,i,&DeviceInfoData); i++)  
		{  
			SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_DRIVER, NULL, (PBYTE)buffer, MAX_PATH, NULL);  
			strKey  =  strConstKey;  
			strKey += buffer; 
			if (CheckDisplay(strKey) == false)
				continue;
			if (ERROR_SUCCESS != ::RegOpenKey(hRootKey, (LPCSTR)strKey, &hCurKey))  
			{  
				GetLastError();  
				return _T("");  
			}
			// Get the driver description  
			DWORD dwType = REG_SZ;  
			if (ERROR_SUCCESS != ::RegQueryValueEx(hCurKey, "DriverDesc", NULL, &dwType, (LPBYTE)szValueData, &dwVDataSize))  //Device Description
				return _T("");
			if (strlen(szValueData))
				break;
#if 0
			// Get provider name  
			if (ERROR_SUCCESS != ::RegQueryValueEx(hCurKey, "ProviderName", NULL, &dwType, (LPBYTE)szValueData, &dwVDataSize))  
				return _T("");  
			//  Retrieve  version:  
			if (ERROR_SUCCESS != ::RegQueryValueEx(hCurKey, "Ver", NULL, &dwType, (LPBYTE)szValueData, &dwVDataSize))  
				return _T("");  
#endif //0
		} 
		RegCloseKey(hCurKey);
		RegCloseKey(hRootKey);
	}  
	result.sprintf(_T("显卡：%s"), szValueData);
	return result;
}

bool SystemInfo::CheckDisplay(wxString strKey)
{
	// member
	char szValueData[256];
	memset(szValueData, 0, 256);
	HKEY  hRootKey  =  HKEY_LOCAL_MACHINE; 
	HKEY  hCurKey;
	DWORD dwVDataSize;

	// get
	wxString temp = strKey.SubString(0, strKey.Last('\\')-1);
	if  (ERROR_SUCCESS != ::RegOpenKey(hRootKey, (LPCSTR)temp, &hCurKey))  
		return false;
	// Get the driver description  
	DWORD dwType = REG_SZ;  
	if (ERROR_SUCCESS != ::RegQueryValueEx(hCurKey, "Class", NULL, &dwType, (LPBYTE)szValueData, &dwVDataSize))  //Device Description
		return _T("");

	//compare 
	if (strcmp(szValueData,"Display") == 0)	
		return true;
	return false;
}

wxString SystemInfo::GetDXVersion()
{
	wxString result;
	HKEY hKey;
	char dx[50] = "\0";		// 返回DX版本
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\DirectX", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{   
		DWORD dwStyle=REG_SZ;   
		int len=50;                               
		if(ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"Version", NULL, &dwStyle,(LPBYTE)dx,(LPDWORD)&len))   
			ShowMessage(_T("Get DX version failed."));   
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get DX version failed")); 
	result.sprintf(_T("DirectX：%s"), _T(dx));
	return result;
}

wxString SystemInfo::GetIEInfo()
{
	wxString result;
	HKEY hKey;
	char ie[50] = "\0";		// 返回CPU型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Internet Explorer", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{   
		DWORD dwStyle=REG_SZ;   
		int len=50;                               
		if(ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"Version", NULL, &dwStyle,(LPBYTE)ie,(LPDWORD)&len))   
			ShowMessage(_T("Get IE version failed."));   
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get IE version failed")); 
	result.sprintf(_T("IE：%s"), _T(ie));
	return result;
}

wxString SystemInfo::GetOpenGLVersion()
{		
	char pszOS[256];		// LPSTR
	OSVERSIONINFOEX osvi;
	BOOL bOsVersionInfoEx;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
		return _T("");
	sprintf(pszOS, "OpenGL：%i.%i.%i", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
	return wxString(pszOS);
}

wxString SystemInfo::GetCPUInfo()
{
	wxString result;
	HKEY hKey;
	char CPU[50] = "\0";		//返回CPU型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Hardware\\Description\\System\\CentralProcessor\\0", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{   
		DWORD dwStyle=REG_SZ;   
		int len=50;                               
		if(ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"ProcessorNameString", NULL, &dwStyle,(LPBYTE)CPU,(LPDWORD)&len))   
			ShowMessage(_T("Get CPU failed."));   
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get CPU failed")); 
	result.sprintf(_T("CPU:%s"), _T(CPU));
	return result;
}

void SystemInfo::ShowMessage(const wxString& msg)
{
#ifdef _DEBUG
	// wxLogError(msg);
	wxMessageBox(msg, _T("系统提示"));
#endif
}

void SystemInfo::GetUserInfo(USER_INFO& userInfo)
{   	
#if 0
	HKEY hKey;  
	// ======================   取得操作系统版本     ===================================================   
	wxString  VersionInfo;		//返回版本号   
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,"software\\microsoft\\windows\\CurrentVersion",0,KEY_QUERY_VALUE,&hKey) == ERROR_SUCCESS)   
	{   
		int len = 50;
		char Version[50];   
		DWORD dwStyle=REG_SZ;   
		if(ERROR_SUCCESS == RegQueryValueEx(hKey,(LPTSTR)"Version",NULL,&dwStyle,(LPBYTE)Version,(LPDWORD)&len))   
		{   
			OSVERSIONINFO osInfo;     // 取得版本号
			osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);     
			::GetVersionEx(&osInfo);     
			VersionInfo.sprintf(_T("%s     %ld.%ld版"), Version,osInfo.dwMajorVersion,osInfo.dwMinorVersion,osInfo.szCSDVersion);   
		}   
		else 
			ShowMessage(_T("Get VersionNumber failed."));   		
		RegCloseKey(hKey);   
	}   
	else  
		ShowMessage(_T("Get VersionInfo failed"));   
#if 0
	if(VersionInfo.Find(_T("98"),0)==-1)     //判断是否为Windows   98   OS   
	{        
		ShowMessage(_T("not   windows   98   OS"));   
		return;   
	}  
#endif	

	//===================== 取得共享目录 ===============================================   
	wxString  dirname[30];		//返回值   
	int cntDirTotal;			//返回值   
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\NetWork\\LanMan", 0,KEY_ALL_ACCESS,&hKey) == ERROR_SUCCESS)   
	{   
		char name1[50];   
		DWORD len=50;   
		DWORD index=0;		
		// 查询所有共享目录
		while(ERROR_SUCCESS == RegEnumKeyEx(hKey, index, name1, &len, NULL, NULL, NULL, NULL))   
		{     
			len = 50;   
			dirname[index] = name1;   
			index++;   
		}   
		cntDirTotal=index;   
		RegCloseKey(hKey);   
	}   
	else 	
		ShowMessage(_T("get share directory failed"));

	char ComputerName[50];	//返回计算机名   
	char IPAddress[50];		//返回IP地址   
	char Comment[50];		//返回职务   
	char Workgroup[50];		//返回工作组   

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\VxD\\VNETSUP", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)   
	{   
		DWORD dwStyle=REG_SZ;
		int len = 50;                               
		if(ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"ComputerName",NULL,&dwStyle,(LPBYTE)ComputerName,(LPDWORD)&len))		
			ShowMessage(_T("get computer name failed"));		
		len = 50;   
		if (ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"Comment",NULL,&dwStyle,(LPBYTE)Comment,(LPDWORD)&len))   
			ShowMessage(_T("Get comment failed"));
		len = 50;   
		if(ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"Workgroup",NULL,&dwStyle,(LPBYTE)Workgroup,(LPDWORD)&len))
			ShowMessage(_T("Get WorkGroup failed"));   
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get share computer name failed"));

	//****************   取得IP地址   *******************   
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\class\\nettrans\\0000", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)   
	{   
		DWORD dwStyle=REG_SZ;   
		int len=50;                               
		if(ERROR_SUCCESS!=RegQueryValueEx(hKey,(LPTSTR)"IPAddress",NULL,&dwStyle,(LPBYTE)IPAddress,(LPDWORD)&len))   
			ShowMessage(_T("get   IPAddress   faile"));   		
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get IPAddress failed"));     

	//====================  取得网卡型号 ============================================   
	char NetCard[100];		//返回网卡型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\Class\\Net\\0000", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)   
	{   
		DWORD dwStyle = REG_SZ;   
		int len = 100;
		if(ERROR_SUCCESS!=RegQueryValueEx(hKey,(LPTSTR)"DriverDesc",NULL,&dwStyle,(LPBYTE)NetCard,(LPDWORD)&len))
			ShowMessage(_T("Get NetCard failed"));
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get NetCard failed"));   

	//==================== 取得声卡型号 ============================================   
	char SoundCard[100];	//返回声卡型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\Class\\Media\\0001", 0,KEY_QUERY_VALUE,&hKey)==ERROR_SUCCESS)   
	{   
		DWORD   dwStyle=REG_SZ;   
		int   len=100;                               
		if(ERROR_SUCCESS!=RegQueryValueEx(hKey,(LPTSTR)"DriverDesc",NULL,&dwStyle,(LPBYTE)SoundCard,(LPDWORD)&len))   
			ShowMessage(_T("Get SoundCard failed");
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get SoundCard failed"));   

	//==================== 取得光驱型号  ============================================   
	char CD_ROM[100];	//返回光驱型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\Class\\CDROM\\0000", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)   
	{   
		DWORD dwStyle=REG_SZ;
		int len=100;                               
		if(ERROR_SUCCESS!=RegQueryValueEx(hKey,(LPTSTR)"DriverDesc",NULL,&dwStyle,(LPBYTE)CD_ROM,(LPDWORD)&len))
			ShowMessage(_T("Get CD_ROM failed."));   
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get CD_ROM failed."));   

	//==================== 取得软驱型号 ============================================   
	char Floppy[100];		//返盘软驱型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\Class\\fdc\\0000", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{   
		DWORD dwStyle=REG_SZ;   
		int len=100;                               
		if(ERROR_SUCCESS!=RegQueryValueEx(hKey,(LPTSTR)"DriverDesc",NULL,&dwStyle,(LPBYTE)Floppy,(LPDWORD)&len))  
			ShowMessage(_T("Get Floppy failed.");   
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get Floppy failed"));

	//====================     取得硬盘驱动器型号     ============================================   
	char HardDisk[100];     //返回硬盘驱动器型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\Class\\hdc\\0000", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)   
	{   
		DWORD dwStyle=REG_SZ;
		int len = 100;
		if(ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"DriverDesc",NULL,&dwStyle,(LPBYTE)HardDisk,(LPDWORD)&len))   
			ShowMessage(_T("Get HardDisk failed");   
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get HardDisk faile"));

	//==================== 取得键盘型号 ============================================   
	char Keyboard[100];		//返回键盘型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\Class\\Keyboard\\0000", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)   
	{   
		DWORD dwStyle = REG_SZ;
		int len = 100;
		if(ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"DriverDesc",NULL,&dwStyle,(LPBYTE)Keyboard,(LPDWORD)&len))   
			ShowMessage(_T("Get Keyboard failed"));
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get Keyboard failed"));

	//==================== 取得鼠标型号 ============================================   
	char Mouse[100];		//返回鼠标型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\Class\\Mouse\\0000", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{   
		DWORD dwStyle = REG_SZ;   
		int len = 100;                               
		if(ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"DriverDesc",NULL,&dwStyle,(LPBYTE)Mouse,(LPDWORD)&len))   
			ShowMessage(_T("Get Mouse failed"));
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get Mouse failed"));

	//==================== 取得 CPU 型号  ============================================   
	char CPU[50];		//返回CPU型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Hardware\\Description\\System\\CentralProcessor\\0", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{   
		DWORD dwStyle=REG_SZ;   
		int len=50;                               
		if(ERROR_SUCCESS != RegQueryValueEx(hKey,(LPTSTR)"ProcessorNameString", NULL, &dwStyle,(LPBYTE)CPU,(LPDWORD)&len))   
			ShowMessage(_T("Get CPU failed."));   
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get CPU failed"));   

	//==================== 取得显卡型号 ============================================   
	char VGACard[50];	//返回显卡型号           
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,"system\\CurrentControlSet\\Services\\Class\\Display\\0000", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)   
	{
		DWORD dwStyle = REG_SZ;   
		int len=50;                               
		if(ERROR_SUCCESS!=RegQueryValueEx(hKey,(LPTSTR)"DriverDesc",NULL,&dwStyle,(LPBYTE)VGACard,(LPDWORD)&len)) 
			ShowMessage(_T("Get VGACard failed"));   
		RegCloseKey(hKey);   
	}   
	else   
		ShowMessage(_T("Get VGACard failed")); 

	userInfo.CPU = wxString(CPU);
	userInfo.VGACard = wxString(VGACard);
#endif
}   

void SystemInfo::GetFileVersionOfGame(const wxString &fileName,wxString *resulte)
{		
	DWORD dwVerSize;   
	DWORD dwHandle;	

	dwVerSize = GetFileVersionInfoSize(fileName, &dwHandle);   
	if (dwVerSize == 0)   
		return;

	LPVOID szVersionBuffer = (LPVOID)new char[dwVerSize];	// or TCHAR array.	
	if (GetFileVersionInfo(fileName, 0, dwVerSize, szVersionBuffer))   
	{   
		VS_FIXEDFILEINFO *pInfo;   
		unsigned int nInfoLen;   		
		if (VerQueryValue(szVersionBuffer, _T("\\"), (void**)&pInfo, &nInfoLen))
		{			
			resulte->sprintf(_T("%d.%d.%d.%d"),   
				HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS),   
				HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));     
		}   
	}
	delete szVersionBuffer;
	return;
}