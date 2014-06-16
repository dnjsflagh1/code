/***************************************************
** Copyright (C) 2006-2012 ORSHSOFT
** This file is part of the "Game Launcher".
** All rights reserved
** FilePath e:\Launcher\Core\source\systemInfo.cpp
** 功能：实现自动更新相关辅助函数
****************************************************/
#ifndef _AUTOUPDATE_UPDATE_H_
#define _AUTOUPDATE_UPDATE_H_

#ifdef LAUNCHER_APP
#define DllExport   __declspec(dllimport)
#else
#define DllExport   __declspec(dllexport)
#endif

#include <wx/wx.h>
#include <wx/sound.h>

// predefine
class wxArrayString;
class CUpdate;
class wxThread;
class wxURL;



// 多线程类
class MyThread : public wxThread
{
public:
	MyThread(CUpdate *app);
	virtual void *Entry();
	virtual void OnExit();
	void DoUpdate();

public:
	unsigned int m_count;
	CUpdate *m_app;
};

// 远程文件类型
enum EURLType
{
	EUT_NONE,
	EUT_HTTP,
	EUT_FTP,
	EUT_HTTPS,
};

// 更新状态
enum EUPDATE_STATE
{
	EUS_INITIAL,
	EUS_UPDATE,
	EUS_UPDATE_FINISHED,
};

// 版本更新类
class DllExport CUpdate
{
public:
	CUpdate();
	inline void setMainPath(wxString mainPath){ m_skinDir = mainPath; }
	void initFromCfg();
	///////////////////////////////////////////////////////////////////////////////////////// 类型转换
	std::string static ToString(wxString wxStr){ return std::string(wxStr.mb_str()); }
	wxString static ToWString(std::string str){ return  wxString( str.c_str(), wxConvUTF8);}

	void playMusicStr(const std::string fileName){ playMusic(ToWString(fileName)); }
	std::string getFileVersionStr(const std::string &fileName){ return ToString(getFileVersion(ToWString(fileName))); }

	///////////////////////////////////////////////////////////////////////////////////////// 辅助函数
	// 音乐播放
	void playMusic(const wxString fileName);
	// 配置文件读写	
	bool setConfig(const wxString& key, const wxString& values, wxString fileName = wxEmptyString);
	bool loadConfig(const wxString& key, wxString* values, wxString fileName = wxEmptyString);
	// 检测客户端是否运行
	bool IsClientRun();

	///////////////////////////////////////////////////////////////////////////////////////// 版本更新函数
	// 更新检测函数
	bool needUpdate(int remoteVersion);
	// 获取文件版本
	wxString getFileVersion(const wxString &fileName);
	// 多线程版本更新
	void threadUpdate();

	///////////////////////////////////////////////////////////////////////////////////////// 更新进度
	// 获取文件子进度
	inline int getSubPercentage(){ return m_subPercentage; }
	// 获取整体进度
	inline int getMainPercentage(){ return m_mainPercentage; }
	// 获取需要更新文件总数
	inline int getNeedUpdateFileAmount(){ return m_mainAmountValue; }

protected:
	// 初始化进度以及百分比
	bool InitMainGauge();
	// 获取远程文件
	bool getUrlFile(const wxString &url, unsigned char urlType = 0, const wxString dir = "", wxString saveName = "");
	// 文件保存
	bool SaveFile(wxInputStream *in, const wxString& fileName, const wxString dir, size_t size = 0);
	// 获取远程版本文件
	wxInputStream *getRemoteVersionFile(const wxString url = wxEmptyString);
	// 版本更新核心函数
	void doUpdateVersion();
	friend class MyThread;

private:
	wxSound m_sound;					// 背景音乐
	wxString m_soundFile;			// 背景音乐文件
	wxString m_skinDir;				// 工程主目录
	wxString m_configFile;			// 配置文件路径
	wxString m_cfgVersionURL;		// 配置的版本服务器地址
	wxString m_cfgCoreFileURL;		// 配置的核心文件地址
	// 进度
	int m_mainAmountValue;			// 需要更新的总文件数量
	int m_mainPercentage;			// 总文件数量处理进度百分比
	int m_subPercentage;				// 当前文件保存进度百分比
	// config
	long m_updateVersion;			// 需要更新到的版本
	long m_localVersion;				// 本地版本
	unsigned char m_updateState;	// 状态标志
	bool m_newestVersion;			// 最新版本
	wxString m_showVersion;			// 游戏最新显示版本
	// thread
	MyThread *m_thread;
};
#endif