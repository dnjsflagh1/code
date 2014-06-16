#ifndef _LAUNCHER_H_
#define _LAUNCHER_H_
///////////////////////////////////////////////////////////////////////////
#include <wx/wx.h> 
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>

#include "IEHtmlWin.h"
#include <wxSkin.h>
#include "GameFilePackPreqs.h"
#include "MGPackUpdateManager.h"
#include "MGTypes.h"
#include "MGDefine.h"
#include "Thread.h"
///////////////////////////////////////////////////////////////////////////
#define EVENT_ID_BTNFREEREGISTRATION	20010
#define EVENT_ID_BTNRECHARGE			20011
#define EVENT_ID_BTNOFFICIALWEBSITE		20012
#define EVENT_ID_BTNOFFICIALFORUM		20013
#define EVENT_ID_BTNGAMESETTING			20014
#define EVENT_ID_BTNDOWNLOAD			20015
#define EVENT_ID_BTNVERCAPTION			20016
#define EVENT_ID_BTNGAMEREPAIR			20017
#define EVENT_ID_BTNMANUALUPDATE		20018
#define EVENT_ID_BTNGAMESTART			20019
#define EVENT_ID_BTNEXIT				20020
#define EVENT_ID_STATICCURRVER			20021
#define EVENT_ID_STATICNEWVER			20022
#define EVENT_ID_STATICVERDESC			20023
#define EVENT_ID_PROCESSCURR			20024
#define EVENT_ID_SPROCESSALL			20025
///////////////////////////////////////////////////////////////////////////
class MyThread;
class LauncherApp : public wxApp 
{ 
public: 
	// 这个函数将会在程序启动的时候被调用 
	virtual bool OnInit (); 
	virtual int OnExit();
	virtual	void OnIdle(wxIdleEvent &event);

public:
	void skip(wxMouseEvent &event);

public:
	//-------------------------------------------------------------
	// events
	void OnBtnFreeRegistration(wxCommandEvent &event);
	void OnBtnRecharge(wxCommandEvent &event);
	void OnBtnOfficialWebsite(wxCommandEvent &event);
	void OnBtnOfficialForum(wxCommandEvent &event);
	void OnBtnGameSetting(wxCommandEvent &event);
	void OnBtnDownload(wxCommandEvent &event);
	void OnBtnVerCaption(wxCommandEvent &event);
	void OnBtnGameRepair(wxCommandEvent &event);
	void OnBtnManualUpdate(wxCommandEvent &event);
	void OnBtnGameStart(wxCommandEvent &event);
	void OnBtnExit(wxCommandEvent &event);
	
public:
	//-------------------------------------------------------------
	// logic
	bool			checkVersion();
	static	void	liveUpdateProcess(const char* lpszFile,int downLoadSize, float fPercent,bool bIsFinished ,void* manager );
	
	bool			setVersion(wxString& currVersion,wxString& latestVersion);

	void			gameStart();

	MG::MGPackUpdateManager* getPackUpdateMgr();

public:
	// UI
	//-------------------------------------------------------------
	void			setWholeProcessVal(int val);
	void			setCurrProcessVal(int val);
	void			enableStartWindow(bool enable);
	void			hide(bool isHide = true);


	// thread 
	//-------------------------------------------------------------
	static void	updateVersion(MG::Ptr manager);
	static void	gameRun(MG::Ptr manager);



	int				mPachSize;
	int				mDownSize;
	int				mTempDownSize;
private:
	// 主窗体
	wxSkinSimpleFrame*	mMainFrame;
	// IE控件
	wxIEHtmlWin*		mIe;
	// skinEngine
	wxSkinEngine*		mMainEngine;

	// 免费注册
	wxSkinButton* mBtnFreeRegistration;
	// 购卡充值
	wxSkinButton* mBtnRecharge;
	// 官方网站
	wxSkinButton* mBtnOfficialWebsite;
	// 官方论坛
	wxSkinButton* mBtnOfficialForum;
	// 游戏设置
	wxSkinButton* mBtnGameSetting;
	// 游戏下载
	wxSkinButton* mBtnDownload;
	// 版本说明
	wxSkinButton* mBtnVerCaption;
	// 游戏修复
	wxSkinButton* mBtnGameRepair;
	// 手动更新
	wxSkinButton* mBtnManualUpdate;
	// 开始游戏
	wxSkinButton* mBtnGameStart;
	// 退出
	wxSkinButton* mBtnExit;

	
	// 当前版本
	wxStaticText* mStaticCurrVer;
	// 最新版本
	wxStaticText* mStaticNewVer;
	// 版本描述
	wxStaticText* mStaticVerDesc;

	// 当前进度
	wxGauge*	mProcessCurr;
	// 总进度
	wxGauge*	mProcessAll;
	wxImage*	mProgressImg;

	wxSkinGauge* mProcess1;
	wxSkinGauge* mProcess2;

	bool			mExit;
public:
	wxString mTempVersion;

private:
	wxString mDir;
	
	MyThread* mUpdateVersionThread;
	MyThread* mGameThread;
	MG::OneThreadHandle mUpdateVersionThread1;
	MG::OneThreadHandle mGameThread1;
	MG::MGPackUpdateManager* mPacketUpdateMgr;

	
	DECLARE_EVENT_TABLE();

}; 

DECLARE_APP(LauncherApp)

///////////////////////////////////////////////////////////////////////////
#endif //__NONAME_H__