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
///////////////////////////////////////////////////////////////////////////

class LuancherApp : public wxApp 
{ 
public : 
	// 这个函数将会在程序启动的时候被调用 
	virtual bool OnInit (); 
	virtual int OnExit();

private:
	// 主窗体
	wxSkinSimpleFrame*	mMainFrame;
	// IE控件
	wxIEHtmlWin*		mIe;
	// skinEngine
	wxSkinEngine*		mMainEngine;

	// 免费注册
	wxSkinButton mBtnFreeRegistration;
	// 购卡充值
	wxSkinButton mBtnRecharge;
	// 官方网站
	wxSkinButton mBtnOfficialWebsite;
	// 官方论坛
	wxSkinButton mBtnOfficialForum;
	// 游戏设置
	wxSkinButton mBtnGameSetting;
	// 游戏下载
	wxSkinButton mBtnDownload;
	// 版本说明
	wxSkinButton mBtnVerCaption;
	// 游戏修复
	wxSkinButton mBtnGameRepair;
	// 手动更新
	wxSkinButton mBtnManualUpdate;
	// 开始游戏
	wxSkinButton mBtnGameStart;
	// 退出
	wxSkinButton mBtnExit;

	// 当前版本
	wxSkinButton mStaticCurrVer;
	// 最新版本
	wxSkinButton mStaticNewVer;
	// 版本描述
	wxSkinButton mStaticVerDesc;

	// 当前进度
	wxGauge mProcessCurr;
	// 总进度
	wxGauge mProcessAll;
	wxImage mProgressImg;


}; 

IMPLEMENT_APP(LuancherApp)
///////////////////////////////////////////////////////////////////////////
#endif //__NONAME_H__