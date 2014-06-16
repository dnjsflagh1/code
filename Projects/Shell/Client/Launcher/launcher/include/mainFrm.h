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

//// ���̽ṹ
struct ProcessEntry {
	wxString name;
	long pid;
};

//// �ļ��ṹ
struct SFileVersion 
{
public:
	wxString fileName;
	wxString fileVersion;
};

//// �������ṹ
enum ESERVER_FLAG
{
	SERVER_STATE_FREE,
	SERVER_STATE_FULL,	
	SERVER_STATE_FULLEST,	
	SERVER_STATE_SERVICING,
};
// ����ṹ��
struct BaseEntry
{
	int id;
	wxString name;
};
// �������ṹ
struct SServerEntry : BaseEntry
{
	wxString flag;
	wxString address;
	ESERVER_FLAG state;	
};
// ����ṹ
struct SPartEntry : BaseEntry
{
	std::vector<SServerEntry> serverList;
	std::vector<wxSkinButton*> buttonList;
	std::vector<wxSkinButton*> flagList;
	void Hide();
	void Show();
};

// �����ļ��ṹ
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
#define EVENT_ID_SHOWFORUM		20011			// ��̳	
#define EVENT_ID_SHOWWEB		20012			// ����
#define EVENT_ID_SYSINFO		20013
#define EVENT_ID_HELP_HIDE		20014
#define EVENT_ID_INFO_HIDE		20015
#define EVENT_ID_OPTION_HIDE	20016
#define EVENT_ID_SLIDER_DRAG	20017
#define EVENT_ID_OPTION_SAVE	20018
#define EVENT_ID_SOCKET_ACT	20019
#define EVENT_ID_TIMER_ACT		20020
#define EVENT_ID_SHOWFAQ		20021			// FAQ
#define EVENT_ID_SHOWREG		20022			// ע��
#define EVENT_ID_SHOWSRV		20023			// �ͷ�
//#define EVENT_ID_SHOWNEWS		20024			// ����
#define EVENT_ID_SHOWPAY		20025			// ��ֵ
#define EVENT_ID_SHOWUPDATE		20026			// �ֶ�����
#define EVENT_ID_SELECT_PART	20027			// ѡ��
#define EVENT_ID_SELECT_SERVER	20028		// ѡ��

#define EVENT_ID_SHOWLATESTNEW	20029			//���¶�̬
#define EVENT_ID_SHOWNEWSEVENT	20030			//���Ż
#define EVENT_ID_SHOWGAMENOTE	20031			//��Ϸ����

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
	bool getRemoteVersionFile(wxXmlDocument *doc, const wxString &xmlName = wxEmptyString);	// �����Ч�İ汾�ļ���
	void doUpdateVersion();						// ���°汾
	bool IsClientRun();							// �ͻ����Ƿ�������
	bool IsSelfRun();								// ����Լ��Ƿ�������
	void loadPartList();							// ��ȡ�����б�

protected:	
	/// skinFrame
	wxSkinSimpleFrame *m_frame;				// ������
	wxIEHtmlWin *m_ie;							// �����IE
	wxIEHtmlWin *m_bigEye;						// ���۾�
	wxSkinSimpleFrame *m_helpFrame;			// ��������
	wxSkinSimpleFrame *m_systemInfoFrame;	// ϵͳ˵������
	wxSkinSimpleFrame *m_optionFrame;		// ѡ���
	wxSkinSimpleFrame *m_serverFrame;		// �������б���

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

	// �������½�����
	int m_subProgressValue;
	int m_mainProgressValue;
	int m_mainAmountValue;						// �ܹ���Ҫ���µ��ļ�����
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
	int m_updateVersion;							// ��ǰ���ڸ��µİ汾

	// socket & update
	wxSocketClient *m_socket;
	wxIPV4address m_addr;
	bool m_inProcess;
	unsigned char m_msgType;
	SFileVersion *m_fileList;
	unsigned int m_fileSize;
	int m_accessedFlag;							// -1 δ���£� 0 �����У� 1�������, 3���¹��������κδ���
	MyThread *m_thread;
	//wxSkinStaticText *m_textVersion;
	// const volatile

	void checkGameVersion();
	bool updateVersion();
	bool getNewestVersion(const wxArrayString& downLoadUrls);	
	bool getUrlFile(const wxString &url,		// ��������
						 const wxString &md5,		// Զ��MD5
						 unsigned char urlType = 0,// �������� 
						 const wxString dir = "",	// ���·��
						 const wxString saveName = "");	// ��������
	// �ļ���ȡ
	bool realGetUrlFile(const wxString &url,		// ��������
							  unsigned char urlType,	// ��������
							  const wxString &savePath,// �浽���� 
							  const wxString &md5,		// ������У��һ��
							  bool showGauge = true);	// ��ʾ������
	bool canConnect();
	bool needUpdate(int remoteVersion);																								// ������
	bool setConfig(const wxString& key, const wxString& values, wxString fileName = wxEmptyString);				// ��ȡ�����ļ�
	bool loadConfig(const wxString& key, wxString* values, wxString fileName = wxEmptyString);					// ���������ļ�
	// �ļ�����
	bool SaveFile( wxInputStream *in,						// �ļ���
						const wxString& saveName,				// ����·��
						const wxString &md5 = wxEmptyString,// Զ��MD5
						bool showGauge = true,					// ��ʾ������
						const size_t fileSize = 0);			// �ļ���С
	void initFromCfg();
	bool InitMainGauge();	// wxURL& url
	void initServerList(int partIndex);
	wxString GetStateName(int state);
	void saveServerCfg();
	void setVersion();			// �汾����
	void setServerVerion();		// �������汾
	bool checkFileMD5(const wxString &fileName, const wxString &md5str);	/// MD5�Ƿ�ƥ��
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
	unsigned char getUrlType(wxString *url);	// ��ȡ��������
	void setButtonState(wxSkinButton* btn, bool enable = true);

private:
	//// �����ļ���ȡ
	wxString m_cfgForum;				// ��̳
	wxString m_cfgOfficial;			// �ٷ�
	wxString m_cfgFAQ;				// FAQ
	wxString	m_cfgServices;			// �ͷ�
	wxString m_cfgRegister;			// ע��
	wxString	m_cfgNews;				// ����
	wxString m_cfgDownload;			// ����
	wxString m_cfgPay;				// ֧��
	wxString m_cfgVersionURL;		// ���·�����
	wxString m_remoteVerion;		// ��������Ϸ�汾
	wxString m_localVerion;			// ����Ϸ�ذ汾
	// system
	wxString m_cfgLanguage;			// ����
	wxString m_cfgPart;				// ����ID
	wxString m_cfgServer;			// ������ID
	wxString m_cfgAddress;			// ��������ַ		
	// �������б�
	std::vector<SPartEntry*> m_partList;
	std::vector<SServerFile> m_coreFile;		// ������Ҫ���صĺ����ļ�
	int m_lastPart;
	int m_lastVersion;					// �汾���·������ϵ����°汾
	wxString m_lastShowVersion;		// �汾���·������ϵ�������ʾ�汾

	DECLARE_EVENT_TABLE();
};

DECLARE_APP(LauncherApp)

#endif	// end of _LAUNCHER_MAIN_FRM_H_