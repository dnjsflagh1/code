
/************************************************************************
    自动更新接口
	应用程序仅需要使用CLiveUpdate类,并且将对应的LiveUpdate.dll/LiveUpdate_d.dll
	放置在可以被查询到的位置即可,实现采用动态加载的方式处理,无需相应的lib库文件

	getSingleton:获取应用程序实例
	initialize:初始化自动更新模块
	destroy:释放自动更新模块
	setUpdateVersion:设置自动更新模块下载连接和客户端当前版本号
	checkLiveUpdate:检查自动更新模块实现需要更新,是则将先释放自动更新模块,然后将相应的dll进行更新,然后重新初始化
	setLiveUpdateProcess:设置自动更新回调接口,用于检测自动更新下载进度
	updateResource:开始进行更新,返回true,表示需要更新的资源全部下载成功
	getCurrentVersion:返回自动更新完成以后,当前资源的版本号
************************************************************************/

#pragma once

#ifndef __LIVEUPDATE_HPP__
#define __LIVEUPDATE_HPP__

#    if defined(LIVEUPDATE_EXPORTS)
#        define LIVEUPDATE_EXPORT __declspec(dllexport)
#        define LIVEUPDATE_IMPORT __declspec(dllimport)
#    else /* compiler doesn't support __declspec() */
#        define LIVEUPDATE_EXPORT
#        define LIVEUPDATE_IMPORT
#    endif

#include <assert.h>
#include <windows.h>
#include <tchar.h>

//web服务器下载功能接口
class CLivePatch
{
public:
	//当前文件更新百分比,lpszFile为NULL,表示资源更新完成
	typedef void (*LPLiveUpdateProcess)(const char* lpszFile,int downLoadSize, float fPercent,bool bIsFinished ,void* m_updateManager);

public:
	CLivePatch(void) : m_lpLiveUpdateProcess(NULL), m_fPercent(.0) {};
	virtual ~CLivePatch(void) {};

	//检查LiveUpdate是否需要进行自我更新
	virtual bool checkLiveUpdate(void) const = 0;

	//设置版本更新服务器信息
	virtual bool setUpdateVersion(const char* lpszURL, const char* currentVersion) = 0;

	//更新下载资源信息
	virtual bool updateResource(void) const = 0;

	//获取更新后的最新版本号
	virtual wxString getCurrentVersion(void) const = 0;

	//获取服务器上最新版本号
	virtual wxString getLatestVersion(void) const = 0;

	virtual	int		getCurrPatchSize(void) const = 0;

	//清理资源
	virtual void destroy(void) {};

	//设置管理对象
	inline void setUpdateManager(void* manager)
	{
		m_updateManager = manager;
	}

	//文件下载信息
	inline void setLiveUpdateProcess(LPLiveUpdateProcess lpLiveUpdateProcess = NULL)
	{
		m_lpLiveUpdateProcess = lpLiveUpdateProcess;
	}
	inline bool getLiveUpdateProcessInfo(const char*& lpszDownLoadFile, float& fPercent)
	{
		lpszDownLoadFile = (const char*)m_szDownLoadFile;
		fPercent = m_fPercent;
	}

protected:
	volatile LPLiveUpdateProcess m_lpLiveUpdateProcess;
	void*	m_updateManager;
	mutable volatile char m_szDownLoadFile[1024];
	mutable volatile float m_fPercent;
};

//自动更新类
class CLiveUpdate
{
private:
	CLiveUpdate(const CLiveUpdate&);
	CLiveUpdate& operator=(const CLiveUpdate&);

	CLiveUpdate(void) {};
public:
	~CLiveUpdate(void)
	{
		destroy();
	};

	static CLiveUpdate& getSingleton(void)
	{
		static CLiveUpdate s_nLiveUpdate;
		return s_nLiveUpdate;
	}

	//加载函数库
	inline bool initialize()
	{
		destroy();

#ifdef _DEBUG
		m_hLiveUpdateLibrary = ::LoadLibrary(_T("launcher/LiveUpdate_d.dll"));
#else
		m_hLiveUpdateLibrary = ::LoadLibrary(_T("launcher/LiveUpdate.dll"));
#endif
		assert(m_hLiveUpdateLibrary != NULL);
		if (m_hLiveUpdateLibrary != NULL)
		{
			typedef CLivePatch* (*LPGetLivePatch)(void);
			LPGetLivePatch lpGetLivePatch = (LPGetLivePatch)::GetProcAddress(m_hLiveUpdateLibrary, "GetLivePatch");
			if (lpGetLivePatch != NULL)
			{
				m_lpLivePatch = lpGetLivePatch();
				if (m_lpLivePatch != NULL)
				{
					return true;
				}
			}
		}

		destroy();
		return false;
	}
	inline void destroy(void)
	{
		if (m_lpLivePatch != NULL)
		{
			m_lpLivePatch->destroy();
			m_lpLivePatch = NULL;
		}

		if (m_hLiveUpdateLibrary != NULL)
		{
			::FreeLibrary(m_hLiveUpdateLibrary);
			m_hLiveUpdateLibrary = NULL;
		}
	}

	inline int getCurrPatchSize()
	{
		assert(m_lpLivePatch != NULL);
		if (m_lpLivePatch != NULL)
		{
			return m_lpLivePatch->getCurrPatchSize();
		}
		return 0;
	}
	//设置版本更新服务器信息
	inline bool setUpdateVersion(const char* lpszURL,  const char* szCurrentVersion)
	{
		assert(m_lpLivePatch != NULL);
		if (m_lpLivePatch != NULL)
		{
			if (m_lpLivePatch->setUpdateVersion(lpszURL, szCurrentVersion) != false)
			{
				::strncpy_s(m_szURL, lpszURL, sizeof(m_szURL));
				m_szCurrentVersion = szCurrentVersion;
				return true;
			}
		}

		return false;
	}

	//返回false表示没有进行更新
	inline bool checkLiveUpdate(void) const
	{
		assert(m_lpLivePatch != NULL);
		return m_lpLivePatch != NULL ? m_lpLivePatch->checkLiveUpdate() : false;
	}

	//进行版本资源更新
	inline bool updateResource(void) const
	{
		assert(m_lpLivePatch != NULL);
		return m_lpLivePatch != NULL ? m_lpLivePatch->updateResource() : false;
	}

	inline void setLiveUpdateProcess(CLivePatch::LPLiveUpdateProcess lpLiveUpdateProcess = NULL)
	{
		assert(m_lpLivePatch != NULL);
		if (m_lpLivePatch != NULL)
		{
			m_lpLivePatch->setLiveUpdateProcess(lpLiveUpdateProcess);
		}
	}
	inline void setUpdateManager(void* manager)
	{
		assert(manager != NULL);
		if (manager != NULL)
		{
			m_lpLivePatch->setUpdateManager(manager);
		}
	}

	inline wxString  getCurrentVersion(void) const
	{
		assert(m_lpLivePatch != NULL);
		return m_lpLivePatch != NULL ? m_lpLivePatch->getCurrentVersion() : "0";
	};

	inline wxString  getLatestVersion(void) const
	{
		assert(m_lpLivePatch != NULL);
		return m_lpLivePatch != NULL ? m_lpLivePatch->getLatestVersion() : "0";
	};

private:
	HMODULE m_hLiveUpdateLibrary;
	CLivePatch* m_lpLivePatch;

	char m_szURL[1024];                            //版本控制地址
	wxString m_szCurrentVersion;				   //客户端当前版本
};

#endif

