/***************************************************
** Copyright (C) 2006-2010 Orsh
** This file is part of the "Game Launcher".
** All rights reserved
****************************************************/

#ifndef _LAUNCHER_MAIN_FRM_H_
#define _LAUNCHER_MAIN_FRM_H_

////////////////////////////////////////////////////////////////////////// include head file.
#include <wx/wx.h>
#include <wx/sound.h>
#include <wx/socket.h>
#include <wxSkin.h>
#include "IEHtmlWin.h"

//// predefine
class wxArrayString;
class LauncherApp;
class wxThread;
class wxURL;
const char g_bgSound[256] = "\\Audio2.dat";
const char *g_gameName = "SHZ";
#define GAME_CORE_FILE_AMOUNT 8

//// 进程结构
struct ProcessEntry {
	wxString name;
	long pid;
};

//// 文件结构
struct SFileVersion 
{
public:
	wxString fileName;
	wxString fileVersion;
};

//// 服务器结构
enum ESERVER_FLAG
{
	SERVER_STATE_FREE,
	SERVER_STATE_FULL,	
	SERVER_STATE_FULLEST,	
	SERVER_STATE_SERVICING,
};
// 区域结构体
struct BaseEntry
{
	int id;
	wxString name;
};
// 服务器结构
struct SServerEntry : BaseEntry
{
	wxString flag;
	wxString address;
	ESERVER_FLAG state;	
};
// 区域结构
struct SPartEntry : BaseEntry
{
	std::vector<SServerEntry> serverList;
	std::vector<wxSkinButton*> buttonList;
	std::vector<wxSkinButton*> flagList;
	void Hide();
	void Show();
};

// 下载文件结构
struct SServerFile 
{
	wxString md5;
	wxString url;
	wxString savePath;
	wxString fileName;
	unsigned char urlType;
};

////////////////////////////////////////////////////////////////////////// define event id
#define EVENT_ID_LCLOSE			20007
#define EVENT_ID_RUNGAME		20008
#define EVENT_ID_SHOWOPTION	20009
#define EVENT_ID_SHOWHELP		20010
#define EVENT_ID_SHOWFORUM		20011			// 论坛	
#define EVENT_ID_SHOWWEB		20012			// 官网
#define EVENT_ID_SYSINFO		20013
#define EVENT_ID_HELP_HIDE		20014
#define EVENT_ID_INFO_HIDE		20015
#define EVENT_ID_OPTION_HIDE	20016
#define EVENT_ID_SLIDER_DRAG	20017
#define EVENT_ID_OPTION_SAVE	20018
#define EVENT_ID_SOCKET_ACT	20019
#define EVENT_ID_TIMER_ACT		20020
#define EVENT_ID_SHOWFAQ		20021			// FAQ
#define EVENT_ID_SHOWREG		20022			// 注册
#define EVENT_ID_SHOWSRV		20023			// 客服
//#define EVENT_ID_SHOWNEWS		20024			// 新闻
#define EVENT_ID_SHOWPAY		20025			// 充值
#define EVENT_ID_SHOWUPDATE		20026			// 手动更新
#define EVENT_ID_SELECT_PART	20027			// 选区
#define EVENT_ID_SELECT_SERVER	20028		// 选服

#define EVENT_ID_SHOWLATESTNEW	20029			//最新动态
#define EVENT_ID_SHOWNEWSEVENT	20030			//新闻活动
#define EVENT_ID_SHOWGAMENOTE	20031			//游戏公告

////////////////////////////////////////////////////////////////////////// define WX application
class MyThread : public wxThread
{
public:
	MyThread(LauncherApp *app);
	virtual void *Entry();
	virtual void OnExit();
	void DoUpdate();

public:
	unsigned int m_count;
	LauncherApp *m_app;
};

class LauncherApp : public wxApp
{
public:	
	bool OnInit();
	virtual int OnExit();
	void initMember();
	wxSkinEngine *AllocateEngine(){ return new wxSkinEngine; }
	void GetProcessList(std::vector<ProcessEntry> &proclist);
	void ExecuteCommand(const wxString &command, wxArrayString &output, long flags = wxEXEC_NODISABLE| wxEXEC_SYNC);

	///<<< event define
	void OnRunGame(wxCommandEvent &event);
	void OnShowOption(wxCommandEvent &event);
	void OnShowHelp(wxCommandEvent &event);
	void OnIdle(wxIdleEvent &event);
	void OnExitLaunher(wxCommandEvent &event);

	// event web
	void OnShowForum(wxCommandEvent &event);
	void OnShowWeb(wxCommandEvent &event);
	void OnShowFAQ(wxCommandEvent &event);
	void OnShowService(wxCommandEvent &event);
	void OnShowReg(wxCommandEvent &event);
	void OnShowNews(wxCommandEvent &event);
	void OnShowPay(wxCommandEvent &event);
	void OnShowUpdate(wxCommandEvent &event);

	void OnShowInfo(wxCommandEvent &event);
	void OnHideHelp(wxCommandEvent &event);	
	void OnHideInfo(wxCommandEvent &event);
	void OnHideOption(wxCommandEvent &event);
	void OnSaveOption(wxCommandEvent &event);
	void OnSliderUpdate(wxCommandEvent &event);
	void OnSocketAct(wxSocketEvent &event);
	void OnPartClick(wxCommandEvent &event);
	void OnServerClick(wxCommandEvent &event);

	//xcl
	void OnShowLatestnew(wxCommandEvent &event);
	void OnShowNewsevent(wxCommandEvent &event);
	void OnShowGamenote(wxCommandEvent &event);
	std::vector<wxSkinButton*> m_btnPartList;
	//-xcl
	///>>> event define

	/// show sub window.
	void showHelpWin();
	void showSysinfoWin();
	void showOptionWin();
	void showFlashWin();
	void showServerWin();

	/// update version entry
	bool getRemoteVersionFile(wxXmlDocument *doc, const wxString &xmlName = wxEmptyString);	// 获得有效的版本文件流
	void doUpdateVersion();						// 更新版本
	bool IsClientRun();							// 客户端是否在运行
	bool IsSelfRun();								// 检测自己是否在运行
	void loadPartList();							// 获取区域列表

protected:	
	/// skinFrame
	wxSkinSimpleFrame *m_frame;				// 主窗体
	wxIEHtmlWin *m_ie;							// 浏览器IE
	wxIEHtmlWin *m_bigEye;						// 大眼睛
	wxSkinSimpleFrame *m_helpFrame;			// 帮助窗体
	wxSkinSimpleFrame *m_systemInfoFrame;	// 系统说明窗体
	wxSkinSimpleFrame *m_optionFrame;		// 选项窗体
	wxSkinSimpleFrame *m_serverFrame;		// 服务器列表窗体

	/// skinEngine
	wxSkinEngine *m_mainEngine;
	wxSkinEngine *m_helpEngine;
	wxSkinEngine *m_systemInfoEngine;
	wxSkinEngine *m_optionEngine;
	wxSkinEngine *m_serverEngine;

	/// control
	wxSkinCheckBox *m_chkFullScreen;
	wxSkinSlider *m_sliderVol;
	wxSound m_sound;

	// 两个更新进度条
	int m_subProgressValue;
	int m_mainProgressValue;
	int m_mainAmountValue;						// 总共需要更新的文件个数
	wxImage m_progress;
	wxGauge *m_subGauge;
	wxGauge *m_mainGauge;

	//xcl
	//wxSkinButton *btn_latestnew;
	//wxSkinButton *btn_newsevent;
	//wxSkinButton *btn_gamenote;
	wxSkinButton *m_btnVersion;
	wxSkinButton *m_btnLastVersion;
	wxSkinButton *btn_run;

	//-xcl

	/// configFile
	wxString m_skinDir;
	wxString m_configFile;
	int m_updateVersion;							// 当前正在更新的版本

	// socket & update
	wxSocketClient *m_socket;
	wxIPV4address m_addr;
	bool m_inProcess;
	unsigned char m_msgType;
	SFileVersion *m_fileList;
	unsigned int m_fileSize;
	int m_accessedFlag;							// -1 未更新， 0 更新中， 1更新完成, 3更新过不再做任何处理
	MyThread *m_thread;
	//wxSkinStaticText *m_textVersion;
	// const volatile

	void checkGameVersion();
	bool updateVersion();
	bool getNewestVersion(const wxArrayString& downLoadUrls);	
	bool getUrlFile(const wxString &url,		// 下载链接
						 const wxString &md5,		// 远程MD5
						 unsigned char urlType = 0,// 链接类型 
						 const wxString dir = "",	// 相对路径
						 const wxString saveName = "");	// 保存名字
	// 文件获取
	bool realGetUrlFile(const wxString &url,		// 下载链接
							  unsigned char urlType,	// 链接类型
							  const wxString &savePath,// 存到哪里 
							  const wxString &md5,		// 下完再校验一次
							  bool showGauge = true);	// 显示进度条
	bool canConnect();
	bool needUpdate(int remoteVersion);																								// 检测更新
	bool setConfig(const wxString& key, const wxString& values, wxString fileName = wxEmptyString);				// 读取配置文件
	bool loadConfig(const wxString& key, wxString* values, wxString fileName = wxEmptyString);					// 更新配置文件
	// 文件保存
	bool SaveFile( wxInputStream *in,						// 文件流
						const wxString& saveName,				// 保存路径
						const wxString &md5 = wxEmptyString,// 远程MD5
						bool showGauge = true,					// 显示进度条
						const size_t fileSize = 0);			// 文件大小
	void initFromCfg();
	bool InitMainGauge();	// wxURL& url
	void initServerList(int partIndex);
	wxString GetStateName(int state);
	void saveServerCfg();
	void setVersion();			// 版本设置
	void setServerVerion();		// 服务器版本
	bool checkFileMD5(const wxString &fileName, const wxString &md5str);	/// MD5是否匹配
	void UpgradeSelf();
	bool checkCoreFile();
	void proccessPatch(const wxString &fileName = wxEmptyString);

	// test
	void test1();
	
	// protected function
	void initSocket();
	wxArrayString getSystemInfo();
	void hideSubWin();
	void playMusic();

	// new http access update version
	wxString getFileVersion(const wxString &fileName);	
	void loadLocalFileVersion();
	void processMainGauge();
	void threadUpdate();
	unsigned char getUrlType(wxString *url);	// 获取链接类型
	void setButtonState(wxSkinButton* btn, bool enable = true);

private:
	//// 配置文件读取
	wxString m_cfgForum;				// 论坛
	wxString m_cfgOfficial;			// 官方
	wxString m_cfgFAQ;				// FAQ
	wxString	m_cfgServices;			// 客服
	wxString m_cfgRegister;			// 注册
	wxString	m_cfgNews;				// 新闻
	wxString m_cfgDownload;			// 下载
	wxString m_cfgPay;				// 支付
	wxString m_cfgVersionURL;		// 更新服务器
	wxString m_remoteVerion;		// 服务器游戏版本
	wxString m_localVerion;			// 本游戏地版本
	// system
	wxString m_cfgLanguage;			// 语言
	wxString m_cfgPart;				// 分区ID
	wxString m_cfgServer;			// 服务器ID
	wxString m_cfgAddress;			// 服务器地址		
	// 服务区列表
	std::vector<SPartEntry*> m_partList;
	std::vector<SServerFile> m_coreFile;		// 缓存需要下载的核心文件
	int m_lastPart;
	int m_lastVersion;					// 版本更新服务器上的最新版本
	wxString m_lastShowVersion;		// 版本更新服务器上的最新显示版本

	DECLARE_EVENT_TABLE();
};

DECLARE_APP(LauncherApp)

#endif	// end of _LAUNCHER_MAIN_FRM_H_