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
	// ������������ڳ���������ʱ�򱻵��� 
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
	// ������
	wxSkinSimpleFrame*	mMainFrame;
	// IE�ؼ�
	wxIEHtmlWin*		mIe;
	// skinEngine
	wxSkinEngine*		mMainEngine;

	// ���ע��
	wxSkinButton* mBtnFreeRegistration;
	// ������ֵ
	wxSkinButton* mBtnRecharge;
	// �ٷ���վ
	wxSkinButton* mBtnOfficialWebsite;
	// �ٷ���̳
	wxSkinButton* mBtnOfficialForum;
	// ��Ϸ����
	wxSkinButton* mBtnGameSetting;
	// ��Ϸ����
	wxSkinButton* mBtnDownload;
	// �汾˵��
	wxSkinButton* mBtnVerCaption;
	// ��Ϸ�޸�
	wxSkinButton* mBtnGameRepair;
	// �ֶ�����
	wxSkinButton* mBtnManualUpdate;
	// ��ʼ��Ϸ
	wxSkinButton* mBtnGameStart;
	// �˳�
	wxSkinButton* mBtnExit;

	
	// ��ǰ�汾
	wxStaticText* mStaticCurrVer;
	// ���°汾
	wxStaticText* mStaticNewVer;
	// �汾����
	wxStaticText* mStaticVerDesc;

	// ��ǰ����
	wxGauge*	mProcessCurr;
	// �ܽ���
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