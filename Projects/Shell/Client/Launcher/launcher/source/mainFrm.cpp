#include "mainFrm.h"
#include <wx/image.h>
#include <wx/html/htmlwin.h>

// file operator support
#include <wx/filedlg.h>
#include <wx/filename.h>
#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/utils.h>
#include <wx/animate.h>
#include <wx/protocol/http.h>
#include <wx/protocol/ftp.h>
//#include <iostream>
//#include <fstream>
#include <wx/url.h>
#include <wx/xml/xml.h>
#include <wx/thread.h>
#include <wx/stream.h>
#include <wx/sstream.h>
#include "md5.h"

#include "systemInfo.h"
#include "wxIEFrm.h"
#include "CTransparentStaticText.h"
#include "msgDefine.h"

// 进程检测依赖
#include <wx/init.h>
#include <vector>

//#include <wxSkinBitmap.h>

#ifdef __WXMSW__
#include "wx/msw/private.h"
#include <Tlhelp32.h>
#include <Windows.h>
#include <process.h>
#endif

////////////////////////////////////////////////////////////////////////// WX Implement
IMPLEMENT_APP( LauncherApp )

//IMPLEMENT_CLASS( LauncherApp, wxApp )

BEGIN_EVENT_TABLE( LauncherApp, wxApp )
EVT_BUTTON(EVENT_ID_RUNGAME, LauncherApp::OnRunGame)
EVT_BUTTON(EVENT_ID_LCLOSE, LauncherApp::OnExitLaunher)
EVT_BUTTON(EVENT_ID_SHOWOPTION, LauncherApp::OnShowOption)
EVT_BUTTON(EVENT_ID_SHOWHELP, LauncherApp::OnShowHelp)
EVT_BUTTON(EVENT_ID_SHOWFORUM, LauncherApp::OnShowForum)
EVT_BUTTON(EVENT_ID_SHOWWEB, LauncherApp::OnShowWeb)
EVT_BUTTON(EVENT_ID_SHOWFAQ, LauncherApp::OnShowFAQ)
EVT_BUTTON(EVENT_ID_SHOWREG, LauncherApp::OnShowReg)
EVT_BUTTON(EVENT_ID_SHOWSRV, LauncherApp::OnShowService)
//EVT_BUTTON(EVENT_ID_SHOWNEWS, LauncherApp::OnShowNews)
EVT_BUTTON(EVENT_ID_SHOWPAY, LauncherApp::OnShowPay)
EVT_BUTTON(EVENT_ID_SHOWUPDATE, LauncherApp::OnShowUpdate)
EVT_BUTTON(EVENT_ID_SYSINFO, LauncherApp::OnShowInfo)
EVT_BUTTON(EVENT_ID_HELP_HIDE, LauncherApp::OnHideHelp)
EVT_BUTTON(EVENT_ID_INFO_HIDE, LauncherApp::OnHideInfo)
EVT_BUTTON(EVENT_ID_OPTION_HIDE, LauncherApp::OnHideOption) 
EVT_BUTTON(EVENT_ID_OPTION_SAVE, LauncherApp::OnSaveOption)
EVT_SOCKET(EVENT_ID_SOCKET_ACT, LauncherApp::OnSocketAct)
EVT_BUTTON(EVENT_ID_SELECT_PART, LauncherApp::OnPartClick)
EVT_BUTTON(EVENT_ID_SELECT_SERVER, LauncherApp::OnServerClick)
//xcl
EVT_BUTTON(EVENT_ID_SHOWLATESTNEW, LauncherApp::OnShowLatestnew)
EVT_BUTTON(EVENT_ID_SHOWNEWSEVENT, LauncherApp::OnShowNewsevent)
EVT_BUTTON(EVENT_ID_SHOWGAMENOTE, LauncherApp::OnShowGamenote)
//-xcl
EVT_IDLE(LauncherApp::OnIdle)
END_EVENT_TABLE()

////////////////////////////////////////////////////////////////////////// LauncherApp
bool SystemInfo::bIsNt = false;

bool LauncherApp::OnInit()
{
	// 判断launcher是否开启
	HWND hwnd = ::FindWindow(NULL,"山海志 Launcher");
	if(hwnd)
	{
		return false;
	}

	// 初始化成员
	initMember();
	//wxInitAllImageHandlers();

	/// 获取程序启动目录
#ifndef __WXMAC__
	wxFileName fname (wxApp::argv[0]);
	fname.MakeAbsolute();
	m_skinDir = fname.GetPath();
#else
	m_skinDir = wxFileName::GetCwd();
#endif

	/// 防止双开laucher
	if(IsSelfRun())
	{
		// Exit();
		return false;
	}

	// 清除临时文件
	wxRemoveFile( m_skinDir + "\\Launcher_bak.exe" );	
	wxRemoveFile( m_skinDir + "\\Launcher_new.exe" );	

	/// 获取皮肤压缩文件 wxSkinSimpleFrame
	m_mainEngine = AllocateEngine();
	m_mainEngine->Load(m_skinDir + _T("/sdata.dat"), _T("mainSkin.xml"));
	m_frame = new wxSkinSimpleFrame(NULL, -1, _T("山海志 Launcher"));

	/// wxIE	
	//m_ie = new wxIEHtmlWin(m_frame, -1,wxPoint(316,329), wxSize(362,224),wxBORDER_NONE);
	m_ie = new wxIEHtmlWin(m_frame, -1,wxPoint(25,202), wxSize(358,223),wxBORDER_NONE);
	m_ie->LoadUrl(_T("http://shz.kx1d.com/clientnews/"));
	m_ie->ClearBackground();

	/// 大眼睛控件
	m_bigEye = new wxIEHtmlWin(m_frame, -1, wxPoint(390,202), wxSize(193,221), wxBORDER_NONE);
	m_bigEye->LoadUrl(_T("http://shz.kx1d.com/larcher/"));
	m_bigEye->ClearBackground();

	/// wxSkinSlider 进度条
	// m_progress.LoadFile(_("progress.png"),wxBITMAP_TYPE_PNG);
	// m_frame->SetSubImg(m_progress, wxPoint(388,577));
	/*m_subGauge = new wxGauge(m_frame,-1, 100, wxPoint(29,460), wxSize(348,9), wxGA_HORIZONTAL|wxGA_SMOOTH|wxBORDER_NONE);
	m_subGauge->SetForegroundColour(wxColour(0,225,9,0));
	m_subGauge->SetBackgroundColour(wxColour(6,6,6,0));
	m_subGauge->SetForegroundColour(wxColour(195,4,203,0));
	m_subGauge->SetBackgroundColour(wxColour(21,56,85,0));*/
	
	m_mainGauge = new wxGauge(m_frame,-1, 100, wxPoint(29,481), wxSize(348,9), wxGA_HORIZONTAL|wxGA_SMOOTH|wxBORDER_NONE);
	/*m_mainGauge->SetForegroundColour(wxColour(0,225,9,0));
	m_mainGauge->SetBackgroundColour(wxColour(6,6,6,0));*/
	m_mainGauge->SetForegroundColour(wxColour(194,123,0,0));
	m_mainGauge->SetBackgroundColour(wxColour(21,56,85,0));


	/// 控件设置
	btn_run = new wxSkinButton(m_frame, EVENT_ID_RUNGAME);
	wxSkinButton *btn_reg = new wxSkinButton(m_frame, EVENT_ID_SHOWREG);
	wxSkinButton *btn_recharge = new wxSkinButton(m_frame, EVENT_ID_SHOWPAY);
	// wxSkinButton *btn_set = new wxSkinButton(m_frame, -1);							// 设置按钮，要求屏蔽
	wxSkinButton *btn_web = new wxSkinButton(m_frame, EVENT_ID_SHOWWEB);
	wxSkinButton *btn_forum = new wxSkinButton(m_frame, EVENT_ID_SHOWFORUM);
	wxSkinButton *btn_faq = new wxSkinButton(m_frame, EVENT_ID_SHOWFAQ);
	wxSkinButton *btn_services = new wxSkinButton(m_frame, EVENT_ID_SHOWSRV);
	wxSkinButton *btn_manual = new wxSkinButton(m_frame, EVENT_ID_SHOWUPDATE);
	//wxSkinButton *btn_news = new wxSkinButton(m_frame, EVENT_ID_SHOWNEWS);
	wxSkinButton *btn_close = new wxSkinButton(m_frame, EVENT_ID_LCLOSE);
	//xcl最新动态，新闻活动，游戏公告
	//<<<  策划要求屏蔽这三个按钮，由网页完成
	//btn_latestnew = new wxSkinButton(m_frame, EVENT_ID_SHOWLATESTNEW);
	//btn_newsevent = new wxSkinButton(m_frame, EVENT_ID_SHOWNEWSEVENT);
	//btn_gamenote = new wxSkinButton(m_frame, EVENT_ID_SHOWGAMENOTE);
	//>>>
	//-xcl
	m_btnVersion = new wxSkinButton(m_frame, -1);				// 版本号点击去往手动更新界面
	m_btnLastVersion = new wxSkinButton(m_frame, -1);			// 服务器上最新版本
	//m_textVersion = new wxSkinStaticText(m_frame, -1);
	setServerVerion();
	setVersion();

	/// 先屏蔽进入游戏，更新后再刷新
	setButtonState(btn_run, false);
	// setButtonState(btn_set, false);								// 设置按钮，需求屏蔽


	////showFlashWin();

	/// 设置皮肤	
	m_mainEngine->AssignControl(wxT("LauncherFrame"), m_frame);
	m_mainEngine->AssignControl(wxT("btn_run"), btn_run);
	m_mainEngine->AssignControl(wxT("btn_reg"), btn_reg);
	m_mainEngine->AssignControl(wxT("btn_recharge"),btn_recharge);
	// m_mainEngine->AssignControl(wxT("btn_set"),btn_set);		// 设置按钮，需求屏蔽
	m_mainEngine->AssignControl(wxT("btn_web"),btn_web);
	m_mainEngine->AssignControl(wxT("btn_forum"),btn_forum);
	m_mainEngine->AssignControl(wxT("btn_faq"),btn_faq);
	m_mainEngine->AssignControl(wxT("btn_services"),btn_services);
	m_mainEngine->AssignControl(wxT("btn_manual"),btn_manual);	// 手动更新
	//m_mainEngine->AssignControl(wxT("btn_news"),btn_news);
	m_mainEngine->AssignControl(wxT("btn_close"),btn_close);
	m_mainEngine->AssignControl(wxT("btn_version"),m_btnVersion);					// 版本
	m_mainEngine->AssignControl(wxT("btn_serverVersion"), m_btnLastVersion);	// 服务器最新版本
	////<<<xcl 策划要求关闭		
	//m_mainEngine->AssignControl(wxT("btn_latestnew"),btn_latestnew);
	//m_mainEngine->AssignControl(wxT("btn_newsevent"),btn_newsevent);
	//m_mainEngine->AssignControl(wxT("btn_gamenote"),btn_gamenote);
	//>>>-xcl
	m_mainEngine->InitializeSkin();	

	/// 初始化窗体
	SetTopWindow(m_frame);
	//m_frame->SetSize(1095,850);
	m_frame->SetSize(621,583);

	/// 窗体呈现
	m_frame->Show();
	m_frame->Refresh();	
	m_frame->Centre();


	/// 先初始化本地文件版本
	//loadLocalFileVersion();

	/// launcher音乐播放
	//playMusic();

	// 读取配置文件
	initFromCfg();												// 读取配置文件
	InitMainGauge();											// 获取更新进度

	// 检测客户端是否已经运行
	IsClientRun();
	threadUpdate();

	/// 测试
	// test1();
	return true;
}

int LauncherApp::OnExit()
{
	if (m_fileList)
		delete[] m_fileList;
	if (m_socket)
	{
		m_socket->Close();
		delete m_socket;
	}
	// 皮肤引擎释放
	if (m_mainEngine)
	{
		m_mainEngine->ClearSkin();
		m_mainEngine->ClearAssignments();		
		m_mainEngine->Destroy();
		delete m_mainEngine;
	}
	if (m_helpEngine)
	{
		m_helpEngine->ClearSkin();
		m_helpEngine->ClearAssignments();		
		m_helpEngine->Destroy();
		delete m_helpEngine;
	}
	if (m_systemInfoEngine)
	{
		m_systemInfoEngine->ClearSkin();
		m_systemInfoEngine->ClearAssignments();		
		m_systemInfoEngine->Destroy();
		delete m_systemInfoEngine;
	}	
	if (m_optionEngine)
	{
		m_optionEngine->ClearSkin();
		m_optionEngine->ClearAssignments();		
		m_optionEngine->Destroy();
		delete m_optionEngine;
	}
	if (m_serverEngine)
	{
		m_serverEngine->ClearSkin();
		m_serverEngine->ClearAssignments();		
		m_serverEngine->Destroy();
		delete m_serverEngine;
		// 释放区域列表
		for (size_t i=0; i<m_partList.size(); i++)
		{
			SPartEntry *obj =  m_partList.at(i);
			obj->buttonList.clear();
			obj->flagList.clear();
			delete obj;
		}
		m_partList.clear();
	}	
	
	if (m_inProcess)
	{
		m_inProcess = false;
		exit(0);
	}	
	/// 
	return(wxApp::OnExit());			// 程序退出
}

void LauncherApp::initMember()
{
	m_configFile = _T("\\Launcher.ini");
	m_ie = NULL;
	m_bigEye = NULL;
	m_helpFrame = NULL;
	m_systemInfoFrame = NULL;
	m_optionFrame = NULL;
	m_serverFrame = NULL;

	m_mainEngine = NULL;
	m_helpEngine = NULL;
	m_systemInfoEngine = NULL;
	m_optionEngine = NULL;
	m_serverEngine = NULL;

	//config
	m_chkFullScreen = NULL;
	m_sliderVol = NULL;

	// update version
	m_socket = NULL;
	m_fileList = NULL;
	m_fileSize = 0;
	m_accessedFlag = -1;		// 未更新标志位
	m_updateVersion = 0;		// 当前更新版本(GameVersion)
	m_inProcess = false;
	m_msgType = 0;
	m_thread = NULL;

	// progress bar
	m_subGauge = NULL;
	m_mainGauge = NULL;
	m_subProgressValue = 0;
	m_mainProgressValue = 0;
	m_mainAmountValue = 0;

	/// 初始化配置文件值
	m_cfgForum = wxEmptyString;
	m_cfgOfficial = wxEmptyString;
	m_cfgFAQ = wxEmptyString;
	m_cfgServices = wxEmptyString;
	m_cfgRegister = wxEmptyString;
	m_cfgNews = wxEmptyString;
	m_cfgDownload = wxEmptyString;		
	m_cfgPay = wxEmptyString;
	m_cfgVersionURL = wxEmptyString;
	// system
	m_cfgLanguage = wxEmptyString;
	m_cfgPart = wxEmptyString;
	m_cfgServer = wxEmptyString;
	m_cfgAddress = wxEmptyString;
	// partList
	m_partList.clear();
	m_lastPart = -1;
	m_lastVersion = 0;
	m_lastShowVersion = wxEmptyString;
	//xcl
	m_btnPartList.clear();
	//-xcl
}

void LauncherApp::initSocket()
{	
	m_addr.Hostname(_("192.168.1.181"));
	m_addr.Service(g_addrPort);
	m_socket = new wxSocketClient;
	m_socket->SetEventHandler(*this, EVENT_ID_SOCKET_ACT);
	m_socket->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
	m_socket->Notify(true);	
}

void LauncherApp::initFromCfg()
{
	loadConfig(_("WEB/forum"), &m_cfgForum);
	loadConfig(_("WEB/official"), &m_cfgOfficial);
	loadConfig(_("WEB/FAQ"), &m_cfgFAQ);
	loadConfig(_("WEB/services"), &m_cfgServices);
	loadConfig(_("WEB/register"), &m_cfgRegister);
	loadConfig(_("WEB/news"), &m_cfgNews);
	loadConfig(_("WEB/download"), &m_cfgDownload);
	loadConfig(_("WEB/pay"), &m_cfgPay);

	loadConfig(_("SYSTEM/versionUrl"), &m_cfgVersionURL);
	loadConfig(_("SYSTEM/language"), &m_cfgLanguage);
	loadConfig(_("SYSTEM/partID"), &m_cfgPart);
	loadConfig(_("SYSTEM/serverID"), &m_cfgServer);
	loadConfig(_("SYSTEM/serverURL"), &m_cfgAddress);
	loadConfig(_("SYSTEM/gameVerion"), &m_localVerion);
}

void LauncherApp::setButtonState(wxSkinButton* btn, bool enable)
{
	btn->Enable(enable);
	if (enable)
		btn->ShowNormalSkin();
	else	
		btn->SetStateFlag(3);
}

////////////////////////////////////////////////////////////////////////// event
/// APP函数
void LauncherApp::OnRunGame(wxCommandEvent &event)
{	
	// @{{ 版本更新线程调用
	if (m_accessedFlag == 0 || m_accessedFlag == 1)
	{
		wxMessageBox("游戏正在更新，请更新后再进入游戏...","系统提示");
		return;
	}	
	// 正在处理中
	if (m_inProcess)
	{
		return;
	}	
	// }}@ end

	// 版本核对
	long localVersion = 0;
	wxString strVersion = wxEmptyString;
	loadConfig(_("SYSTEM/version"), &strVersion);
	strVersion.ToLong(&localVersion);

	// 服务器配置
	if (m_accessedFlag == 3 || localVersion == m_lastVersion)
	{
		if (!m_serverFrame  || m_serverFrame->IsShown() == false)
		{
			loadPartList();
			showServerWin();
			m_frame->Hide();			
		}
		else
		{
			// 如果玩家确认了进入游戏，我们应该保存其最后的选择。
			if (m_cfgAddress.IsEmpty())				 
			{
				wxMessageBox("请选择您想登录的游戏服务器.", "系统提示");
				return;
			}
			saveServerCfg();
				
			// 执行客户端			
			wxString filePath = m_skinDir + wxString::Format(_T("\\bin\\Client.exe server=%s"), m_cfgAddress);
			long res = wxExecute(filePath, wxEXEC_ASYNC);
#ifdef _DEBUG
			// 消息框提示进程ID，以及程序路径
			wxMessageBox(wxString::Format("execute result is %i, %s", res, filePath), "system");
#endif
			Exit();
		}
	}
}

void LauncherApp::OnIdle(wxIdleEvent &event)
{
	if (m_helpFrame && m_helpFrame->IsVisible())
	{		
		m_helpFrame->Show();
		m_helpFrame->SetFocus();
	}
	if (m_systemInfoFrame && m_systemInfoFrame->IsVisible())
	{		
		m_systemInfoFrame->Show();
		m_systemInfoFrame->SetFocus();
	}
	if (m_optionFrame && m_optionFrame->IsVisible())
	{		
		m_optionFrame->Show();
		m_optionFrame->SetFocus();
	}
	// 背景音乐	
	//playMusic();

	// 版本更新完毕
	if (m_accessedFlag == 1)
	{
		// wxMessageBox("version update finished.");
		m_accessedFlag = 3;							// 更新完成不再做任何处理
	}

	// 进度条处理
	if(m_inProcess)
	{
		//m_subGauge->Show();
		//m_subGauge->SetValue(m_subProgressValue);
		//m_subGauge->SetToolTip(wxString::Format(wxT("%i"),m_subProgressValue) + _("/100"));		// 百分比进度
		//m_mainGauge->Show();
		//m_mainGauge->SetValue(m_mainProgressValue);
	}
	else
	{
		// m_subGauge->Hide();
		m_mainGauge->Hide();
	}
	//m_frame->Refresh();
}

void LauncherApp::OnExitLaunher(wxCommandEvent &event)
{
	Exit();
}

/// 网站显示
void LauncherApp::OnShowForum(wxCommandEvent &event)
{
	// 打开论坛
	if (m_cfgForum.IsEmpty())
		m_cfgForum = _("http://shz.kx1d.com/bbs/");
	ShellExecute(NULL, "open", m_cfgForum, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowWeb(wxCommandEvent &event)
{
	// 打开官网
	if (m_cfgOfficial.IsEmpty())
		m_cfgOfficial = _("http://shz.kx1d.com/");
	ShellExecute(NULL, "open", m_cfgOfficial, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowFAQ(wxCommandEvent &event)
{
	// FAQ
	if (m_cfgFAQ.IsEmpty())
		m_cfgFAQ = _("http://shz.kx1d.com/faq.php");
	ShellExecute(NULL, "open", m_cfgFAQ, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowService(wxCommandEvent &event)
{
	// 客服
	if (m_cfgServices.IsEmpty())
		m_cfgServices = _("http://www.kx1d.com/service/index.shtml");
	ShellExecute(NULL, "open", m_cfgServices, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowReg(wxCommandEvent &event)
{
	// 注册页面
	if (m_cfgRegister.IsEmpty())
		m_cfgRegister = _("http://passport.kx1d.com/member/register?gourl=http://www.kx1d.com/");
	ShellExecute(NULL, "open", m_cfgRegister, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowNews(wxCommandEvent &event)
{
	// 新闻页面
	if (m_cfgNews.IsEmpty())
		m_cfgNews = _("http://shz.kx1d.com/php/newslist.php");
	ShellExecute(NULL, "open", m_cfgNews, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowUpdate(wxCommandEvent &event)
{
	//m_textVersion->SetSize(wxSize(70,20));
	
	// 手动更新页面
	if (m_cfgDownload.IsEmpty())
		m_cfgDownload = _("http://shz.kx1d.com/download.html");
	ShellExecute(NULL, "open", m_cfgDownload, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowPay(wxCommandEvent &event)
{
	// 充值页面
	if (m_cfgPay.IsEmpty())
		m_cfgPay = _("http://www.kx1d.com/pay/index.shtml");
	ShellExecute(NULL, "open", m_cfgPay, NULL, NULL, SW_SHOWNORMAL); 
}

//xcl
void LauncherApp::OnShowLatestnew(wxCommandEvent &event)
{
	// 打开 最新动态
	m_ie->LoadUrl(_T("http://shz.kx1d.com/clientnews/"));
	m_ie->ClearBackground();

	//btn_latestnew->SetStateFlag(2);
	//btn_newsevent->ShowNormalSkin();
	//btn_gamenote->ShowNormalSkin();
}
void LauncherApp::OnShowNewsevent(wxCommandEvent &event)
{
	// 打开 新闻活动
	m_ie->LoadUrl(_T("http://shz.kx1d.com/clientnews/"));
	m_ie->ClearBackground();

	//btn_newsevent->SetStateFlag(2);
	//btn_latestnew->ShowNormalSkin();
	//btn_gamenote->ShowNormalSkin();

}
void LauncherApp::OnShowGamenote(wxCommandEvent &event)
{
	// 打开 游戏公告
	m_ie->LoadUrl(_T("http://shz.kx1d.com/clientnews/"));
	m_ie->ClearBackground();

	//btn_gamenote->SetStateFlag(2);
	//btn_newsevent->ShowNormalSkin();
	//btn_latestnew->ShowNormalSkin();
}
//-xcl

/// 界面控制
void LauncherApp::OnShowOption(wxCommandEvent &event)
{
	hideSubWin();
	showOptionWin();
}

void LauncherApp::OnShowHelp(wxCommandEvent &event)
{
	hideSubWin();
	showHelpWin();
}

void LauncherApp::OnShowInfo(wxCommandEvent &event)
{
	hideSubWin();
	showSysinfoWin();
}

void LauncherApp::OnHideHelp(wxCommandEvent &event)
{
	if (m_helpFrame)
	{
		m_helpFrame->Hide();
		SetTopWindow(m_frame);
	}
}

// info m_frame
void LauncherApp::OnHideInfo(wxCommandEvent &event)
{
	if (m_systemInfoFrame)
	{
		m_systemInfoFrame->Hide();
		SetTopWindow(m_frame);
	}
}
// option m_frame
void LauncherApp::OnHideOption(wxCommandEvent &event)
{
	if (m_optionFrame)
	{
		m_optionFrame->Hide();
		SetTopWindow(m_frame);
	}
}

// trigger a exception.
void LauncherApp::OnSliderUpdate(wxCommandEvent &event)
{
	wxMessageBox("Get it!");
}

void LauncherApp::OnSaveOption(wxCommandEvent &event)
{
	wxString values;		
	values.sprintf("取值结果：\n\n全屏选项		%i \n\n滑动条取值：		%i\n", 
		m_chkFullScreen->GetValue(), 
		m_sliderVol->GetValue());
	wxMessageBox(values);
}

void LauncherApp::OnSocketAct(wxSocketEvent &event)
{
	wxString s = _("OnSocketEvent: ");
	switch(event.GetSocketEvent())
	{
	case wxSOCKET_INPUT      : s.Append(_("wxSOCKET_INPUT\n")); break;
	case wxSOCKET_LOST       : s.Append(_("wxSOCKET_LOST\n")); break;
	case wxSOCKET_CONNECTION : s.Append(_("wxSOCKET_CONNECTION\n")); break;
	default                  : s.Append(_("Unexpected event !\n")); break;
	}
	//wxMessageBox(s);
}

void LauncherApp::OnPartClick(wxCommandEvent &event)
{	
	/// 点选分区按钮，初始化服务器列表
	wxSkinButton *obj = (wxSkinButton*)event.GetEventObject();
	int index = obj->GetFlag();
	initServerList(index);
	m_cfgPart = wxString::Format(wxT("%i"),index);
}

void LauncherApp::OnServerClick(wxCommandEvent &event)
{
	/// 点选的服务器按钮，获取其地址
	wxSkinButton *obj = (wxSkinButton*)event.GetEventObject();
	int index = obj->GetFlag();
	SPartEntry *spe = m_partList.at(m_lastPart);	
	/// TODO index 与 ID之间的切换
	m_cfgServer = wxString::Format(wxT("%i"),index);
	m_cfgAddress = spe->serverList.at(index).address;

	//显示一个按下状态
	for (size_t i=0; i<spe->buttonList.size(); i++)
	{
		spe->buttonList.at(i)->ShowNormalSkin();
	}
	obj->SetStateFlag(2);
}

////////////////////////////////////////////////////////////////////////// show sub window.
void LauncherApp::showHelpWin()
{
	if (!m_helpFrame)
	{	
		m_helpFrame = new wxSkinSimpleFrame(m_frame, -1, _T("帮助窗体"));

		// 控件实例
		wxSkinButton *btn_act_forum = new wxSkinButton(m_helpFrame, EVENT_ID_SHOWFORUM);		// 论坛
		wxSkinButton *btn_act_web	= new wxSkinButton(m_helpFrame, EVENT_ID_SHOWWEB);		// 主页
		wxSkinButton *btn_act_info	= new wxSkinButton(m_helpFrame, EVENT_ID_SYSINFO);		// 系统信息
		wxSkinButton *btn_help_hide	= new wxSkinButton(m_helpFrame, EVENT_ID_HELP_HIDE);		// 确定按钮		

		// 绑定皮肤
		m_helpEngine = AllocateEngine();
		m_helpEngine->Load(m_skinDir + _T("/skinfiles/launcher.zip"), _T("helpSkin.xml"));
		m_helpEngine->AssignControl(wxT("helpFrame"), m_helpFrame);
		m_helpEngine->AssignControl(wxT("btn_forum"), btn_act_forum);
		m_helpEngine->AssignControl(wxT("btn_web"), btn_act_web);
		m_helpEngine->AssignControl(wxT("btn_sysinfo"), btn_act_info);
		m_helpEngine->AssignControl(wxT("btn_ok"), btn_help_hide);
		m_helpEngine->InitializeSkin();
	}	

	// 窗体呈现	
	SetTopWindow(m_helpFrame);	
	m_helpFrame->SetSize(398, 366);
	m_helpFrame->Center();
	m_helpFrame->Show();
	m_helpFrame->Refresh();
}

void LauncherApp::showSysinfoWin()
{
	if (!m_systemInfoFrame)
	{	
		m_systemInfoFrame = new wxSkinSimpleFrame(m_frame, -1, _T("系统说明"));

		// 控件实例
		wxSkinButton *btn_info_hide	= new wxSkinButton(m_systemInfoFrame, EVENT_ID_INFO_HIDE);		// 确定按钮		

		// 绑定皮肤
		m_systemInfoEngine = AllocateEngine();
		m_systemInfoEngine->Load(m_skinDir + _T("/skinfiles/launcher.zip"), _T("systemInfoSkin.xml"));
		m_systemInfoEngine->AssignControl(wxT("systemInfoFrame"), m_systemInfoFrame);
		m_systemInfoEngine->AssignControl(wxT("btn_ok"), btn_info_hide);
		m_systemInfoEngine->InitializeSkin();
		
		// 加载系统信息
		wxArrayString info = getSystemInfo();
		if (info.size())
		{			
			wxFont font(12,wxFONTFAMILY_ROMAN  ,wxNORMAL,wxBOLD);	// 字体设置
			wxBoxSizer *sizer  = new wxBoxSizer(wxVERTICAL);		// 容器
			CTransparentStaticText *text = NULL;
			unsigned int arraySize = unsigned int(info.GetCount());			
			for (unsigned int i=0; i<arraySize; i++)
			{				
				text = new CTransparentStaticText(m_systemInfoFrame, -1, info.Item(i));				
				text->SetForegroundColour(*wxWHITE);
				text->SetFont(font);
				sizer->Add(text);
				sizer->Add(new CTransparentStaticText(m_systemInfoFrame, -1, _T("")));				
			}		
			m_systemInfoFrame->SetSizer(sizer);
		}

	}	

	// 窗体呈现	
	SetTopWindow(m_systemInfoFrame);	
	m_systemInfoFrame->SetSize(398, 366);
	m_systemInfoFrame->Center();
	m_systemInfoFrame->Show(true);
	m_systemInfoFrame->Refresh();
}

void LauncherApp::showOptionWin()
{
	if (!m_optionFrame)
	{	
		m_optionFrame = new wxSkinSimpleFrame(m_frame, -1, _T("配置选项"));

		// 控件实例
		wxSkinButton *btn_save_option	= new wxSkinButton(m_optionFrame, EVENT_ID_OPTION_SAVE);		// 确定按钮,保存设置
		wxSkinButton *btn_cancel_option	= new wxSkinButton(m_optionFrame, EVENT_ID_OPTION_HIDE);		// 取消按钮,隐藏界面
		m_chkFullScreen = new wxSkinCheckBox(m_optionFrame, -1);
		m_sliderVol = new wxSkinSlider(m_optionFrame, -1);								// 滑值

		// 绑定皮肤
		m_optionEngine = AllocateEngine();
		m_optionEngine->Load(m_skinDir + _T("/skinfiles/launcher.zip"), _T("optionSkin.xml"));
		m_optionEngine->AssignControl(wxT("optionFrame"), m_optionFrame);
		m_optionEngine->AssignControl(wxT("btn_ok"), btn_save_option);
		m_optionEngine->AssignControl(wxT("btn_cancel"), btn_cancel_option);
		m_optionEngine->AssignControl(wxT("chk_fullScreen"), m_chkFullScreen);
		m_optionEngine->AssignControl(wxT("sldTerrain"), m_sliderVol);
		m_optionEngine->InitializeSkin();

		// 加载选项信息
		m_sliderVol->SetRange(100);
		m_sliderVol->SetValue(50);
			
	}	
	// 窗体呈现	
	SetTopWindow(m_optionFrame);	
	m_optionFrame->SetSize(398, 366);
	m_optionFrame->Center();
	m_optionFrame->Show(true);
	m_optionFrame->Refresh();
}

void LauncherApp::showFlashWin()
{
	// 设置gif格式图片
	wxAnimationCtrl* animationGif = new wxAnimationCtrl(m_frame, -1);
	animationGif->SetPosition(wxPoint(0,0));
	wxString fileName = m_skinDir + _T("/001.gif");
	animationGif->LoadFile(fileName);
	animationGif->Show(true);
	animationGif->Play(true);
}

void LauncherApp::showServerWin()
{
	if (!m_serverFrame)
	{
		// 窗体初始化
		m_serverFrame = new wxSkinSimpleFrame(m_frame, -1, _T("服务器选择"));

		/// 控件实例
		/// 绑定皮肤
		m_serverEngine = AllocateEngine();
		m_serverEngine->Load(m_skinDir + _T("/sdata.dat"), _T("ServerList.xml"));
		m_serverEngine->AssignControl(wxT("ServerFrame"), m_serverFrame);
		// 显示服务器列表
		if (m_partList.size())
		{
			wxFont font(8, wxFONTFAMILY_DEFAULT, wxNORMAL, wxFONTWEIGHT_BOLD, false);
			SPartEntry *spe;			
			char strName[256];
			bool res;
			for(size_t i=0; i<m_partList.size(); i++)
			{
				spe = m_partList.at(i);
				wxSkinButton *btn_part	= new wxSkinButton(m_serverFrame, EVENT_ID_SELECT_PART, spe->name);		// 确定按钮,保存设置
				btn_part->SetSize(136,35);
				btn_part->SetFlag(i);					// 设置标记
				res = btn_part->SetFont(font);
				//res = btn_part->SetForegroundColour(wxColour(0,255,255,0));
				btn_part->SetFontColor(wxColour(230,218,169,0));	//modify by xcl
				btn_part->SetOverFontColor(wxColour(255,255,255,0));
				btn_part->SetActFontColor(wxColour(136,130,90,0));
				sprintf(strName,"btn_part%i", i);
				res = m_serverEngine->AssignControl(strName, btn_part);
				m_btnPartList.push_back(btn_part);
			}
			//TODO
		}
		

		// 按钮皮肤
		wxSkinButton *btn_reg = new wxSkinButton(m_serverFrame, EVENT_ID_SHOWREG);
		wxSkinButton *btn_recharge = new wxSkinButton(m_serverFrame, EVENT_ID_SHOWPAY);
		wxSkinButton *btn_run = new wxSkinButton(m_serverFrame, EVENT_ID_RUNGAME);
		wxSkinButton *btn_close = new wxSkinButton(m_serverFrame, EVENT_ID_LCLOSE);
		//xcl
		wxSkinButton *btn_web = new wxSkinButton(m_serverFrame, EVENT_ID_SHOWWEB);
		wxSkinButton *btn_forum = new wxSkinButton(m_serverFrame, EVENT_ID_SHOWFORUM);
		wxSkinButton *btn_faq = new wxSkinButton(m_serverFrame, EVENT_ID_SHOWFAQ);
		wxSkinButton *btn_services = new wxSkinButton(m_serverFrame, EVENT_ID_SHOWSRV);
		//-xcl

		m_serverEngine->AssignControl(wxT("btn_reg"), btn_reg);
		m_serverEngine->AssignControl(wxT("btn_recharge"),btn_recharge);
		m_serverEngine->AssignControl(wxT("btn_run"), btn_run);
		m_serverEngine->AssignControl(wxT("btn_close"), btn_close);
		//xcl
		m_serverEngine->AssignControl(wxT("btn_web"), btn_web);
		m_serverEngine->AssignControl(wxT("btn_forum"), btn_forum);
		m_serverEngine->AssignControl(wxT("btn_faq"), btn_faq);
		m_serverEngine->AssignControl(wxT("btn_services"), btn_services);
		//-xcl
		
		// 初始化皮肤
		m_serverEngine->InitializeSkin();
	}	
	// 窗体呈现	
	SetTopWindow(m_serverFrame);	
	//m_serverFrame->SetSize(1095,850); //del by xcl 加了这行不能居中显示界面
	m_serverFrame->SetSize(621,583); //del by xcl 加了这行不能居中显示界面
	m_serverFrame->Center();
	m_serverFrame->Show(true);
	m_serverFrame->Refresh();
}

////////////////////////////////////////////////////////////////////////// help function
wxArrayString LauncherApp::getSystemInfo()
{
	wxArrayString information;
	information = SystemInfo::GetMac();	
	information.Add(SystemInfo::GetOSDisplayString());	
	information.Add(SystemInfo::GetCPUInfo());
	information.Add(SystemInfo::GetIEInfo());
	information.Add(SystemInfo::GetVideo());
	information.Add(SystemInfo::GetDXVersion());
	information.Add(SystemInfo::GetOpenGLVersion());
	return information;		
}

void LauncherApp::hideSubWin()
{
	if (m_helpFrame)
		m_helpFrame->Hide();
	if (m_systemInfoFrame)
		m_systemInfoFrame->Hide();
	if (m_optionFrame)
		m_optionFrame->Hide();
	SetTopWindow(m_frame);
}


// 播放背景音乐
void LauncherApp::playMusic()
{	
	if (m_sound.IsOk() == false)
	{
		//格式化字符为UTF格式并创建wxString字符串对象 
		wxString soundString(m_skinDir + g_bgSound, wxConvUTF8); 
		//创建wxSound对象 	 
		m_sound.Create(soundString,false); 	
		m_sound.Play(true);	
	}
	// m_sound.IsPlaying();	// wxWidgets: This method is currently not implemented under Windows. so that backGroup music not loop.
}


////////////////////////////////////////////////////////////////////////// socket & update (useless) 废弃，暂时不需要版本更新服务器
void LauncherApp::checkGameVersion()
{
	wxString version;
	SystemInfo::GetFileVersionOfGame(m_skinDir + _("\\calc.exe"), &version);
	if (version.Trim().IsNull() || version.Trim().IsEmpty())
	{
		// 未取到版本
		return;
	}
	if (canConnect() && m_inProcess == false)
	{
		m_inProcess = true;
		unsigned char len = 0;
		m_msgType = ENM_VERSION_CHECK;
		m_socket->Write(&m_msgType, 1);
		m_socket->SetFlags(wxSOCKET_WAITALL);
		// 传输游戏名称
		len = unsigned char((strlen(g_gameName)+1) * sizeof(char));
		m_socket->Write(&len,1);
		m_socket->Write(g_gameName, len);
		// 传输游戏版本
		len = unsigned char((wxStrlen(version.c_str())+1) * sizeof(wxChar));
		m_socket->Write(&len,1);
		m_socket->Write(version.c_str(), len);
		// 版本信息确认回传
		unsigned char msgBack = 0;
		m_socket->Read(&msgBack, 1);
		if (msgBack)
		{
			// 设置更新按钮Enable 或者 弹出用户确认模态窗体。
			wxMessageBox(_("需要更新版本."));
		}
		m_inProcess = false;
	}
}

// 测试网络
void LauncherApp::test1()
{
	///<<< MD5 测试
	const wxString file = "d:\\a.txt";
	//const wxString md5Str = "917b2c5c3d5cf2f013cf323a360dcc93";
	const wxString md5Str = "917B2C5C3D5CF2F013CF323A360DCC93";
	wxChar msg[256];
	if (checkFileMD5(file, md5Str))
	{				
		wxSprintf(msg, "文件匹配成功，MD5码为：%s", md5Str);		
	}
	else
	{
		if (wxFile::Exists(file))
		{
			wxString md5Res = wxMD5::GetFileMD5(file);
			wxSprintf(msg, "文件匹配失败，本地MD5码为：[%s],远程MD5码为[%s]", md5Res, md5Str);
		}
		else
		{
			wxSprintf(msg, "MD5测试文件[%s]不存在", file);
		}
	}
	wxMessageBox(msg, _T("文件MD5码测试"));
	///>>> MD5 测试

	/*
	if (m_inProcess)
	{
		wxMessageBox(_T("网络繁忙请稍候重试..."), _T("网络提示"));
		return;
	}
	// 置位系统忙
	m_inProcess = true;

	// 定义消息
	unsigned char len = 0;
	const wxChar *msg = _T("测试连接...\n");
	wxChar *msgBack = new wxChar[wxStrlen(msg)+1];
	m_msgType = (unsigned char)ENM_TEST_1;

	// 发送&接收消息
	m_socket->Write(&m_msgType, 1);
	m_socket->SetFlags(wxSOCKET_WAITALL);							// 设置状态位等待所有回应
	len = (unsigned char)((wxStrlen(msg)+1) * sizeof(wxChar));		// 计算消息发送字节长度。
	m_socket->Write(&len, 1);
	m_socket->Write(msg, len);

	m_socket->Read(msgBack, len);
	wxMessageBox(wxString(msgBack));
	// 结束
	delete[] msgBack;	
	m_inProcess = false;
	*/
}

bool LauncherApp::canConnect()
{
	if (m_socket)
	{	
		if (m_socket->IsConnected())
			return true;
		m_socket->Connect(m_addr, false);
		m_socket->WaitOnConnect(10);		// 10s wait for response;
		if (m_socket->IsConnected())
			return true;
		m_socket->Close();
	}
	return false;
}

bool LauncherApp::updateVersion()
{
	if (m_inProcess)
	{
		wxMessageBox(_T("网络繁忙请稍候重试..."), _T("网络提示"));
		return false;
	}
	if (m_socket && canConnect())
	{
		m_inProcess = true;
		unsigned char len = 0;
		wxArrayString resultContainer;
		// 发送请求
		m_msgType = ENM_GET_DOWNLOAD_URL;
		m_socket->Write(&m_msgType, 1);
		m_socket->SetFlags(wxSOCKET_WAITALL);
		// 传输游戏名称
		len = unsigned char((strlen(g_gameName)+1) * sizeof(char));
		m_socket->Write(&len,1);
		m_socket->Write(g_gameName, len);
		// 获取下载链接数量
		long urlAmount = 0;
		m_socket->Read(&urlAmount, sizeof(long));		
		// 循环获取下载链接
		wxChar *temp = NULL;
		for (int i=0; i<(int)urlAmount; i++)
		{
			m_socket->Read(&len, 1);
			temp = new wxChar[len];
			m_socket->Read(temp, len);
			resultContainer.Add(wxString(temp));
			delete temp;
		}
		// 调用下载程序
		m_inProcess = false;
		return getNewestVersion(resultContainer);
	}
	return false;
}

bool LauncherApp::getNewestVersion(const wxArrayString& downLoadUrls)
{
	if (downLoadUrls.Count())
	{
		for (unsigned int i=0; i<downLoadUrls.Count(); i++)
		{
			wxMessageBox(downLoadUrls.Item(i));
		}
	}
	else
	{
		// 读取本地配置文件默认下载地址下载
	}
	return false;
}


////////////////////////////////////////////////////////////////////////// http & update (current use)
// 获取远程文件
bool LauncherApp::getUrlFile(const wxString &url,const wxString &md5, unsigned char urlType, const wxString dir, wxString saveName)
{	
	if (!m_inProcess)
		return false;

	// access ftp fileName
	wxString fileName = url.substr(url.Last('/')+1);	// 如果没有指定文件名，则使用链接地址文件名
	if (saveName.IsEmpty())
		saveName = fileName;
	bool res = true;

	// access save file.

	// 文件预判断		
	wxString checkFile = dir.IsEmpty() ? (m_skinDir+"\\" + fileName):(m_skinDir+"\\"+ dir+"\\" + saveName);		
	if (saveName.CmpNoCase("launcher_new.exe") == 0)
	{
		checkFile.Replace("launcher_new.exe", "Launcher.exe");
		checkFile.Replace("Launcher_new.exe", "Launcher.exe");
	}	
	if (checkFileMD5(checkFile, md5))
	{
#ifdef _DEBUG
		wxChar msg[256];
		wxSprintf(msg, "[%s] 与本地MD5校验一致，更新忽略。", fileName);
		wxMessageBox(msg, _T("更新提示"));
#endif
	}		
	else
	{
		// 获取文件
		wxString savePath = dir.IsEmpty()? m_skinDir+"\\" + saveName:m_skinDir+"\\"+ dir+"\\" + saveName;		
		res = realGetUrlFile(url, urlType, savePath, md5);
		// 判断自我更新
		if (res && saveName.CmpNoCase("launcher_new.exe") == 0)
		{
			UpgradeSelf();
		}
		if (res && saveName.StartsWith("patch") && saveName.EndsWith(".exe"))
		{
			proccessPatch(saveName);
		}		
	}	

	// 传输成功且传输总数大于零，避免零作除数(有点冗余判断)
	if (res && m_mainAmountValue>0)
	{
		m_mainProgressValue++;
		int percentage = m_mainProgressValue*100/m_mainAmountValue;
		m_mainGauge->SetValue(percentage);
	}
	return res;
}

bool LauncherApp::realGetUrlFile(const wxString &url, unsigned char urlType, const wxString &savePath, const wxString &md5, bool showGauge)
{
	bool res = true;
	wxString lastError = "文件获取成功.";
	// HTTP 模式
	if (urlType == EUT_HTTP)
	{			
		wxURL *purl = new wxURL(url);		
		wxInputStream *in = purl->GetInputStream();		
		if (!in)
		{
			lastError = "无效http数据流.";
			res = false;			
		}
		else
		{
			res &= SaveFile(in, savePath, md5, showGauge);
			delete in;
		}
		in = NULL;
		delete purl;
	}
	// FTP 模式
	else if (urlType == EUT_FTP)
	{
		wxString fileName = url.substr(url.Last('/')+1);
		wxFTP ftp;
		// access ftp hostName
		wxString tempFtpAddr = url.substr(0, url.Index('/'));
		// access ftp Dir
		wxString fileDir = url.substr(tempFtpAddr.Len(), url.Len()-tempFtpAddr.Len()-fileName.Len());		
		//ftp.SetUser(_("Anonymous"));	//匿名访问
		ftp.SetUser(_("guest"));
		//ftp.SetPassword(wxEmptyString);
		if ( !ftp.Connect(tempFtpAddr))
		{
			lastError = "ftp服务器连接失败.";
			res = false;
		}
		else
		{
			ftp.ChDir(fileDir);
			// 文件包大小判断
			int size = ftp.GetFileSize(fileName);
			if ( size == -1 )
			{
				lastError = "无效ftp文件尺寸.";
				res = false;
			}
			else
			{
				// 文件流判断
				wxInputStream *in = ftp.GetInputStream(fileName);
				if ( !in )
				{
					lastError = "无效ftp数据流.";
					res = false;
				}
				else
				{
					// 保存文件
					res &= SaveFile(in, savePath, md5, showGauge, size);
					delete in;
				}
				in = NULL;
			}
		}
		// gracefully close the connection to the server
		ftp.Close();
	}
	else if (urlType == EUT_HTTPS)
	{
		//TODO: 实现HTTPS,传输机密文件或核心文件
	}
#ifdef _DEBUG
	wxMessageBox(lastError, "系统提示");
#endif
	return res;
}

// 保存文件
bool LauncherApp::SaveFile(wxInputStream *in, const wxString& saveName, const wxString &md5, bool showGauge, const size_t fileSize)
{
	wxString lastError = "文件保存成功.";
	bool res = true;
	m_subProgressValue = 0;
	size_t size = fileSize;
	if (size == 0)
		size = in->GetSize();
	if (size>0)
	{
		// 文件保存
		char *data = new char[size];		// 数据缓存
		if ( !in->Read(data, size) )
		{
			lastError = "无效文件数据流.";
			res = false;
		}
		else
		{
			//////////////////////////////////////////////////////////////////////////  直接写入
			wxFile sfile;			
			sfile.Open(saveName, wxFile::write, wxS_DEFAULT);
			sfile.Write(data, size);
			sfile.Flush();
			sfile.Close();
			//////////////////////////////////////////////////////////////////////////  逐字节写入
			
#pragma region  // file data is in the buffer
			if (0)
			{
				size_t i;			
				wxFileOutputStream out(saveName);

				/*ofstream out(saveName, ios::out|ios::binary);*/
				if(!out) 
				{				
					lastError = "文件输出流创建失败，请检查目录读写权限.";
					res = false;
				}
				else
				{									
					for(i=0; i<size; i++) 
					{
						/// 
						if (!m_inProcess)
						{
							lastError = "文件传输中断退出.";
							res = false;
							break;
						}
						/*out.put(data[i]);*/
						out.PutC(data[i]);

						// 文件进度条
						if (showGauge)
						{						
							int mark = (i*100)/size; // 计算百分比
							if (mark>0)
							{
								if (mark == 100)
								{
									m_subProgressValue = 0;
									// m_subGauge->SetValue(0);
									continue;
								}
								m_subProgressValue = mark;
								//if(m_subGauge->IsShown() == false)
								//	m_subGauge->Show();
								//m_subGauge->SetValue(m_subProgressValue);
								//m_subGauge->SetToolTip(wxString::Format(wxT("%i"),m_subProgressValue) + _("/100"));		// 百分比进度						
							}	
						}				
					}
				}
				/*out.flush();*/
				/*out.close();*/
				out.Sync();
				out.Close();
			}
#pragma endregion 

		}
		delete [] data;

		// 判断MD5码
		if (md5.IsEmpty() == false && wxFile::Exists(saveName))
		{
			if (!checkFileMD5(saveName, md5))
			{				
				lastError = "文件校验不匹配，更新失败.";
				res = false;
			}
		}	
	}
	else
	{
		lastError = "无效文件数据流尺寸.";
		res = false;
	}

#ifdef _DEBUG
	if (res)
	{
		wxMessageBox(lastError, _T("系统提示"));				
	} 
	else
	{
		wxMessageBox(saveName, _T("文件保存"));
	}
#endif	
	return res;	
}

// 检测文件MD5
bool LauncherApp::checkFileMD5(const wxString &fileName, const wxString &md5str)
{
	if (wxFile::Exists(fileName))
	{
		wxString fileMD5 = wxMD5::GetFileMD5(fileName);
		return (fileMD5.CmpNoCase(md5str)==0);
	}
	return false;
}

// 本地版本检测
bool LauncherApp::needUpdate(int remoteVersion)
{
	wxString values;
	bool res = loadConfig( _("SYSTEM/version"), &values);
	long lastVersion = 0;
	values.ToLong(&lastVersion);
	if(lastVersion < remoteVersion)
	{
		// 需要更新，并记录需要更新的版本号，以便回写配置文件。
		m_updateVersion = remoteVersion;
		return true;
	}
	return false;
}

// 配置文件读取
bool LauncherApp::loadConfig(const wxString& key, wxString* values, wxString fileName)
{
	if(fileName.IsEmpty())
	{
		fileName = m_configFile;
	}
	wxString	realFileName = m_skinDir +fileName;
	wxFileInputStream fis(realFileName);
	if (!fis.Ok())
	{
		assert("Config file not found.");
		return false;
	}
	wxFileConfig *conf = new wxFileConfig(fis);
	bool result = conf->Read(key, values);
	delete conf;
	return result;
}

// 配置文件更新
bool LauncherApp::setConfig(const wxString& key, const wxString& values, wxString fileName)
{
	if(fileName.IsEmpty())
	{
		fileName = m_configFile;
	}
	wxString	realFileName = m_skinDir +fileName;
	wxFileInputStream fis(realFileName);
	if (!fis.Ok())
	{
		assert("Config file not found.");
		return false;
	}
	wxFileConfig *conf = new wxFileConfig(fis);
	bool result = conf->Write(key, values);
	wxFileOutputStream os(realFileName);
	conf->Save(os);
	os.Close();	
	delete conf;
	return result;
}


// 获取版本服务器地址
bool LauncherApp::getRemoteVersionFile(wxXmlDocument *doc, const wxString &xmlName)
{	
	bool res = false;
	wxURL url;
	wxInputStream *stream = NULL;
	if (m_cfgVersionURL.Index(";") != -1)
	{
		wxStringTokenizer tkz(m_cfgVersionURL, wxT(";"));
		while ( tkz.HasMoreTokens() )
		{
			wxString token = tkz.GetNextToken();
			if (token.EndsWith(_(".xml")) == false)
			{
				token += _("/updateVersion.xml");
			}
			if (!xmlName.empty())
				token.Replace("updateVersion.xml", xmlName);
			// process token here
			url.SetURL(token);
			if (url.GetError() == wxURL_NOERR)
			{				
				stream = url.GetInputStream();
				if (stream)
					res = doc->Load(*stream);
				break;
			}
			else
			{
				res = false;				
			}
		}
	}
	else
	{
		if (m_cfgVersionURL.IsEmpty() == false)
		{
			if (m_cfgVersionURL.EndsWith(_(".xml")) == false)
			{
				m_cfgVersionURL += _("/updateVersion.xml");
			}
			if (!xmlName.empty())
				m_cfgVersionURL.Replace("updateVersion.xml", xmlName);
			url.SetURL(m_cfgVersionURL);
			if (url.GetError() == wxURL_NOERR)
			{
				stream = url.GetInputStream();
				if (stream)
					res = doc->Load(*stream);
			}				
		}
	}
	if (res == false)
	{
		// 直接获取失败，尝试下载到本地再访问
		wxString xmlFile = m_skinDir + "temp.xml";
		realGetUrlFile(m_cfgVersionURL,EUT_HTTP, xmlFile, wxEmptyString, false);
		if (wxFile::Exists(xmlFile))
		{
			res = doc->Load(xmlFile);
			wxRemoveFile(xmlFile);
		}
	}
	if (stream)
	{
		delete stream;
		stream = NULL;
	}
	return res;
}

// 自身更新
void LauncherApp::UpgradeSelf()
{
	// 移除旧版本文件
	wxString temp = m_skinDir  + "\\Launcher_bak.exe";
	remove(temp.c_str());											// 移除已有临时对象，以便后续目标程序重命名

	wxString src = m_skinDir + "\\Launcher_new.exe";		// 源程序，及我们从服务器上下下来的程序
	wxString dst = m_skinDir + "\\Launcher.exe";				// 目标程序，及要替换的程序
	
	wxChar buffer[512];
	wxStrcpy(buffer, dst.c_str());								// 缓存目标文件名	

	rename(dst.c_str(),temp.c_str());							// 将当前程序命名为临时
	CopyFile(src.c_str(),dst.c_str(),false);					// 拷贝新程序覆盖目标程序

	// 进程创建API初始化，并重启程序
	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

	::CreateProcess(buffer, // application name/path
		NULL, // command line (optional)
		NULL, // no process attributes (default)
		NULL, // default security attributes
		false,
		CREATE_DEFAULT_ERROR_MODE | CREATE_NEW_CONSOLE,
		NULL, // default env
		NULL, // default working dir
		&siStartupInfo,
		&piProcessInfo);

	::TerminateProcess( GetCurrentProcess(),0);
	::ExitProcess(0); // exit this process

	// this does not return.
}

// 游戏运行必须文件检查
bool LauncherApp::checkCoreFile()
{
	// 获取服务器配置xml	
	wxXmlDocument doc;	// XML版本文件		
	if (getRemoteVersionFile(&doc, "core.xml") == false)
	{					
		return true;		
	}

	//进度条初始化
	m_coreFile.reserve(GAME_CORE_FILE_AMOUNT);	// 初始化连续内存，避免标准库的倍数扩容
	m_mainProgressValue = 0;
	m_subProgressValue = 0;

	// 版本核对
	wxXmlNode *root = doc.GetRoot();	
	wxXmlNode *subNode = NULL;
	SServerFile cachFile;
	bool processSuccess = true;
	while (root)
	{
		if (root->GetName() == "SHZ")
		{
			subNode = root->GetChildren();
			wxString fileName, md5, path, url, localFile, filePath;
			unsigned char urlType = 0;
			while (subNode)
			{	
				// 获取属性
				fileName = subNode->GetPropVal(_("name"), wxEmptyString).Trim();
				path = subNode->GetPropVal(_("local"), wxEmptyString).Trim();
				md5 = subNode->GetPropVal(_("md5"), wxEmptyString).Trim();
				url = subNode->GetPropVal(_("url"), wxEmptyString).Trim();
				
				// md5对比
				if (path.empty() == false)
					localFile = m_skinDir+ "\\" + path +"\\"+ fileName;
				else
					localFile = m_skinDir+ "\\" + fileName;
				// TODO: 本地没有这个文件,当前是直接下载，并存储到本地。
				if (wxFile::Exists(localFile) == false)
				{
					// launcher特殊处理
					if (fileName.CmpNoCase("Launcher_new.exe") == 0)
					{
						wxString temp(localFile);
						temp.Replace("Launcher_new.exe", "Launcher.exe");
						if (checkFileMD5(temp, md5) == false)
						{
							urlType = getUrlType(&url);
							cachFile.fileName = fileName;
							cachFile.md5 = md5;
							cachFile.savePath = localFile;
							cachFile.url = url;
							cachFile.urlType = urlType;
							m_coreFile.push_back(cachFile);
						}
						subNode = subNode->GetNext();
						continue;
					}				
				}
				if(checkFileMD5(localFile, md5) == false)
				{
					// 下载文件
					urlType = getUrlType(&url);
					cachFile.fileName = fileName;
					cachFile.md5 = md5;
					cachFile.savePath = localFile;
					cachFile.url = url;
					cachFile.urlType = urlType;
					m_coreFile.push_back(cachFile);
				}							
				subNode = subNode->GetNext();
			}
		}
		root = root->GetNext();
	}

	if (m_coreFile.size())
	{
		m_mainAmountValue = m_coreFile.size();
		if (wxMessageBox("游戏核心文件校验不匹配，可能导致游戏无法运行，是否更新?", "系统提示", wxYES_NO) == wxYES)
		{
			m_inProcess = true;	// 开始下载文件处理流程
			// 更新文件
			for (size_t idx=0; idx<m_coreFile.size(); ++idx)
			{		
				processSuccess &= realGetUrlFile(m_coreFile[idx].url, 
															m_coreFile[idx].urlType,
															m_coreFile[idx].savePath,
															m_coreFile[idx].md5,
															true);
				if (m_coreFile[idx].savePath.EndsWith("Launcher_new.exe"))
					UpgradeSelf();

			}
		}
		m_inProcess = false;
		m_coreFile.clear();
	}	

	return processSuccess;
}

// 版本更新核心函数
void LauncherApp::doUpdateVersion()
{
	if (m_accessedFlag == 3)
		return;
	// loadLocalFileVersion();	// 先初始化本地文件版本
	bool processSuccess = true;

	// 获取更新服务器地址
	if (true)
	{					
		wxXmlDocument doc;	// XML版本文件		
		if (getRemoteVersionFile(&doc) == false)
		{	
			wxMessageBox(_T("版本文件解析失败，请稍后重试或联系客服"), _T("系统提示"),wxOK);
			return;		
		}

		// 文件更新数量预计		
		if (m_mainAmountValue)
		{
			if(m_mainGauge->IsShown() == false)
				m_mainGauge->Show();
		}
		// 文件更新
		wxXmlNode *root = doc.GetRoot();		
		wxXmlNode *baseRoot = NULL;					// 保存根节点
		wxXmlNode *subRoot = NULL;						// 文件节点
		wxString gameName;								// 游戏名称		
		baseRoot = root->GetChildren();
		root = root->GetChildren();
		m_inProcess = true;		

		// 游戏版本节点
		while(root)
		{
			m_accessedFlag = 0;		// 版本更新中
			// 判断Game节点的游戏名称是否是山海志
			root->GetAttribute(_("name"), &gameName);			
			if (root->GetName() == _("game") && gameName.IsSameAs(_("SHZ")))
			{
				// 判断当前的游戏版本，是否需要更新： 
				wxString fileName, fileVersion, fileUrl, updateType, fileLocal, gameVersion, fileMD5;				
				gameVersion = root->GetPropVal(_("version"), _(""));									// 获取该更新列表对应的游戏版本
				m_remoteVerion = root->GetPropVal(_("gameVersion"), m_localVerion);				// 获取远程服务器版本号
				long remoteVersion;
				gameVersion.ToLong(&remoteVersion);						
				if (needUpdate(remoteVersion) == false)
				{
					root = root->GetNext();
					continue;
				}

				// 游戏版本更新，获取Game节点的子节点所有文件属性
				subRoot = root->GetChildren();				
				while (subRoot)
				{
					updateType = subRoot->GetName();
					// 判断节点类型，包括[file/dir/zip/dat]，还有注释，如果是注释，则跳到下一轮。
					// TODO: 将zip文件自动解压
					if (updateType.IsSameAs(_("comment")))
					{
						subRoot = subRoot->GetNext();
						continue;
					}
					// 文件信息获取
					fileLocal = subRoot->GetPropVal(_("local"), wxEmptyString).Trim();							// 本地存放路径
					fileName = subRoot->GetPropVal(_("name"), wxEmptyString).Trim();								// 文件名称
					fileVersion = subRoot->GetPropVal(_("version"),wxEmptyString).Trim();						// 文件版本
					fileUrl = subRoot->GetPropVal(_("url"),wxEmptyString).Trim();									// 文件服务器下载位置
					fileMD5 = subRoot->GetPropVal(_("md5"), wxEmptyString).Trim();									// 获取文件MD5码

					// 下载链接地址处理
					unsigned char urlType = getUrlType(&fileUrl);

					
					if (updateType.IsSameAs(_("dir")))// 创建目录
					{
						// 创建文件夹：
						wxString dir = m_skinDir + "\\" + fileName;
						if (!::wxDirExists(dir))
						{
							::wxMkDir(dir);
						}
					}
					else if (updateType.IsSameAs(_("exe")) || updateType.IsSameAs(_("dll")))// 文件更新
					{
						// 文件更新，版本校验废弃，采用MD5码
						//if (getFileVersion(fileName).IsSameAs(fileVersion.c_str()) == false || fileVersion.IsEmpty())
						//{
						//	processSuccess &= getUrlFile(fileUrl, urlType, fileLocal, fileName);
						//}
						processSuccess &= getUrlFile(fileUrl, fileMD5, urlType, fileLocal, fileName);
					}										
					else	// rar、dat 或者其它文件，立即更新覆盖
					{
						if (fileUrl.IsEmpty()==false && urlType != EUT_NONE)
							processSuccess &= getUrlFile(fileUrl,fileMD5, urlType, fileLocal, fileName);
					}
					wxThread::Sleep(1);
					// 一个更新子块处理完成，处理下一个
					subRoot = subRoot->GetNext();
				}
			}
			// 不是山海志游戏的节点模块，或者是那个模块处理完了		
			root = root->GetNext();
		}
		m_inProcess = false;
	}

	// 更新完成后，核心文件检测
	checkCoreFile();

	// 版本更新完成
	m_accessedFlag = 1;		
	m_inProcess = false;
	if (m_updateVersion > 0 && processSuccess == true)
	{
		// 版本完全更新成功
		wxMessageBox(_T("游戏版本更新成功完成"),_T("版本更新"));
		setConfig(_("SYSTEM/version"), wxString::Format(wxT("%i"),m_updateVersion));
		setConfig(_("SYSTEM/gameVersion"), m_remoteVerion);
		m_btnVersion->SetLabel(_T("本地：") + m_remoteVerion);
	}	

	// 复原开始游戏按钮
	setButtonState(btn_run, true);
	
#if 0
		// 文件读取测试
		size_t sizes = inputStream->GetSize()+1;
		char *buff = new char[sizes];
		inputStream->Read(buff, sizes);
		delete[] buff;
#endif	
}

void LauncherApp::proccessPatch(const wxString &fileName)
{
	// 处理自解压文件	
	wxString patchPath  = fileName.IsEmpty() ?m_skinDir + "\\patch.exe":m_skinDir + "\\" +fileName;
	if (wxFile::Exists(patchPath))
	{
		/* 老函数，未能达到等待效果
		if (ShellExecute(NULL,_T("open"), patchPath, NULL, NULL, true))
		{
#ifdef _DEBUG		
			wxMessageBox("自解压文件处理成功。", "系统提示");
#endif			
		}
		else
		{
#ifdef _DEBUG		
			wxMessageBox("自解压文件处理失败。", "系统提示");
#endif
		}
		wxThread::Sleep(1000);	// 大压缩文件可能时间不够
		*/

		//<<< MSDN标准等待
		SHELLEXECUTEINFO   sei;
		//   启动进程
		ZeroMemory(&sei,   sizeof(SHELLEXECUTEINFO));
		sei.cbSize   =   sizeof(SHELLEXECUTEINFO);
		sei.fMask   =   SEE_MASK_NOCLOSEPROCESS;
		sei.hwnd   =   NULL;
		sei.lpVerb   =   NULL;
		sei.lpFile   =   patchPath;
		sei.lpParameters   =   " ";
		sei.lpDirectory   =   NULL;
		sei.nShow   =   SW_SHOW;
		sei.hInstApp   =   NULL;
		ShellExecuteEx(&sei);
		// 加入下面这句就是等待该进程结束
		WaitForSingleObject(sei.hProcess,   INFINITE);
		// 也可以直接关闭这个进程，只要保留sei.hProcess就行
		// TerminateProcess(sei.hProcess,   0); 
		//>>>
		
		bool result = wxRemoveFile(patchPath);
		short amount = 0;
		while (!result)
		{
			// 尝试删10次，如果10次全部失败，则放弃删除；以后用新patch补丁包覆盖。
			result = wxRemoveFile(patchPath);
			if (amount >= 10)
				break;
			amount++;
		}
	}

}

// 获取连接类型
unsigned char LauncherApp::getUrlType(wxString *fileUrl)
{
	unsigned char urlType = EUT_NONE;
	if (fileUrl->IsEmpty() == false)
	{							
		if (fileUrl->StartsWith(_("ftp://")))
		{
			urlType = EUT_FTP;
			*fileUrl = fileUrl->substr(6);
		}
		else if(fileUrl->StartsWith(_("http://"))) 
		{
			urlType = EUT_HTTP;
		}
		else if (fileUrl->StartsWith(_("https://")))
		{
			urlType = EUT_HTTPS;
		}
		else
		{
			assert("Invalid url for update...");
		}
	}
	return urlType;
}

// 核对主进度
bool LauncherApp::InitMainGauge()
{
	wxXmlDocument doc;
	if (getRemoteVersionFile(&doc) == false)
	{
		return false;
	}
	wxXmlNode *root = doc.GetRoot();
	wxXmlNode *subRoot;
	if (root)
		root = root->GetChildren();
	wxString name,gameVersion, gameName;
	long remoteVersion = 0;

	// 开始处理
	while (root)
	{
		name = root->GetName();
		if (name.IsSameAs(_("comment")))
		{
			root = root->GetNext();
			continue;
		}
		gameName = root->GetPropVal(_("name"),wxEmptyString);
		if (root->GetName() == _("game") && gameName.IsSameAs(_("SHZ")))
		{
			gameVersion = root->GetPropVal(_("version"), _(""));									// 获取该更新列表对应的游戏版本
			m_lastShowVersion = root->GetPropVal(_("gameVersion"), _(""));						// 获取实际版本
			gameVersion.ToLong(&remoteVersion);
			if (needUpdate(remoteVersion) == false)
			{
				root = root->GetNext();
				continue;
			}
			subRoot = root->GetChildren();
			while (subRoot)
			{
				// 判断是否是注释或者创建目录
				name = subRoot->GetName();
				if (name.IsSameAs(_("comment")) || name.IsSameAs(_("dir")))
				{
					subRoot = subRoot->GetNext();
					continue;
				}								
				m_mainAmountValue++;
				subRoot = subRoot->GetNext();
			}			
		}
		root = root->GetNext();
	}
	m_lastVersion = remoteVersion;						// 获取服务器最新版本
	m_btnLastVersion->SetLabel(_T("最新：") + m_lastShowVersion);	// 显示服务器最新版本
	return true;
}

// 客户端是否在运行
bool LauncherApp::IsClientRun()
{
	HWND hwnd = ::FindWindow(NULL,"山海志 ONLINE");
	if(hwnd)
	{
		wxMessageBox(_("山海志客户端已经开启，请您先关闭客户端。"),_("系统提示"));
		// ::SendMessage(hwnd, WM_CLOSE, NULL,NULL);												// 没必要强制关闭客户端
		return true;
	}
	// 没必要那么麻烦，懒得做跨平台了，估计游戏也不会再其它平台运行。
	//std::vector<ProcessEntry> l;
	//GetProcessList(l);

	//for(size_t i=0; i<l.size(); i++){
	//	ProcessEntry pe = l.at(i) ;
	//	wxPrintf(wxT("%s %d\n"), pe.name.c_str(), pe.pid);
	//}
	return false;
}

// 检测是否开启了launcher
bool LauncherApp::IsSelfRun()
{
	return false;	// 影响自更新执行
	HWND hwnd = ::FindWindow(NULL,"山海志 Launcher");
	if(hwnd)
	{
		wxMessageBox(_("山海志Launcher已经运行。"),_("系统提示"));
		// ::SendMessage(hwnd, WM_CLOSE, NULL,NULL);
		return true;
	}
	return false;
}



// 获取进程列表
void LauncherApp::GetProcessList(std::vector<ProcessEntry> &proclist)
{
#ifdef __WXMSW__
	OSVERSIONINFO osver ;

	// 系统版本不支持就返回
	osver.dwOSVersionInfoSize = sizeof( osver ) ;
	if(!GetVersionEx(&osver))
	{		
		return;
	}
	if(osver.dwPlatformId != VER_PLATFORM_WIN32_NT){
		return;
	}

	// 获取进程节点
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hProcessSnap) 
	{
		return;
	}

	//Fill in the size of the structure before using it.
	PROCESSENTRY32 pe;
	memset(&pe, 0, sizeof(pe));
	pe.dwSize = sizeof(PROCESSENTRY32);

	// Walk the snapshot of the processes, and for each process,
	// kill it if its parent is pid.
	if (!Process32First(hProcessSnap, &pe)) {
		// Can't get first process.
		CloseHandle (hProcessSnap);
		return;
	}

	do 
	{
		ProcessEntry entry;
		entry.name = pe.szExeFile;
		entry.pid = (long)pe.th32ProcessID;
		proclist.push_back(entry);
	} while (Process32Next (hProcessSnap, &pe));
	// 
	CloseHandle (hProcessSnap);
#else
	//GTK and other
	wxArrayString output;
#if defined (__WXGTK__)
	ExecuteCommand(wxT("ps -A -o pid,command  --no-heading"), output);
#elif defined (__WXMAC__)
	// Mac does not like the --no-heading...
	ExecuteCommand(wxT("ps -A -o pid,command "), output);
#endif
	for (size_t i=0; i< output.GetCount(); i++) {
		wxString line = output.Item(i);
		//remove whitespaces
		line = line.Trim().Trim(false);

		//get the process ID
		ProcessEntry entry;
		wxString spid = line.BeforeFirst(wxT(' '));
		spid.ToLong( &entry.pid );
		entry.name = line.AfterFirst(wxT(' '));

		if (entry.pid == 0 && i > 0) {
			//probably this line belongs to the provious one
			ProcessEntry e = proclist.back();
			proclist.pop_back();
			e.name << entry.name;
			proclist.push_back( e );
		} else {
			proclist.push_back( entry );
		}
	}
#endif
}

// 执行命令
void LauncherApp::ExecuteCommand(const wxString &command, wxArrayString &output, long flags)
{
#ifdef __WXMSW__
	wxExecute(command, output, flags);
#else
	FILE *fp;
	char line[512];
	memset(line, 0, sizeof(line));
	fp = popen(command.mb_str(wxConvUTF8), "r");
	while ( fgets( line, sizeof line, fp)) {
		output.Add(wxString(line, wxConvUTF8));
		memset(line, 0, sizeof(line));
	}

	pclose(fp);
#endif
}

// 获取所有dll exe文件以及版本
void LauncherApp::loadLocalFileVersion()
{
	if (m_fileList)
	{
		delete[] m_fileList;
		m_fileList = NULL;
	}
	m_fileSize = 0;	
#ifndef _DEBUG
	wxLogNull logNull;
#endif
	wxDir dir(m_skinDir);
	if (!dir.IsOpened())
	{
		// warning: directory is not exists, and get version failed.
		return;
	}	
	wxString filename;
	wxArrayString fileContainer;
	wxString filespec = _("*.exe");									// warning: file's ext must be lower
	int flags = wxDIR_FILES;										// add "|wxDIR_DIRS", if you want to get directory both.
	bool cont = dir.GetFirst(&filename, filespec , flags );
	while (cont)
	{			
		fileContainer.Add(filename);
		cont = dir.GetNext(&filename);
	}
	filespec = _("*.dll");											// warning: file's ext must be lower
	cont = dir.GetFirst(&filename, filespec, flags);
	while (cont)
	{
		fileContainer.Add(filename);
		cont = dir.GetNext(&filename);
	}
	wxString appName = GetAppName()+_(".exe");
	fileContainer.Remove(appName.c_str());
	m_fileSize = fileContainer.Count();
	m_fileList = new SFileVersion[m_fileSize];						// init fileVersion container.
	SFileVersion fileVersion;
	for (unsigned int i=0; i<m_fileSize; i++)
	{		
		// wxMessageBox(fileContainer.Item(i));		
		fileVersion.fileName = fileContainer.Item(i);
		SystemInfo::GetFileVersionOfGame(m_skinDir +"/" +fileVersion.fileName, &fileVersion.fileVersion);
		m_fileList[i] = fileVersion;
	}	
}

// 单个文件版本信息获取
wxString LauncherApp::getFileVersion(const wxString &fileName)
{
	wxString result = _("");
	if (m_fileList)
	{
		for (unsigned int i=0; i<m_fileSize; i++) 
		{
			if (m_fileList[i].fileName == fileName)
			{
				result = m_fileList[i].fileVersion;
				break;
			}
		}
	}
	return result;
}

// 进程更新
void LauncherApp::threadUpdate()
{
	m_thread = new MyThread(this);
	if (m_thread->Create() != wxTHREAD_NO_ERROR )
	{
		wxLogError("Can't create the thread!");
		delete m_thread;
		m_thread = NULL;
	}
	else
	{
		if (m_thread->Run() != wxTHREAD_NO_ERROR)
		{
			wxLogError("Can't create the thread!");
			delete m_thread;
			m_thread = NULL;
		}
		else
		{
		}
	}	
}


////////////////////////////////////////////////////////////////////////// 服务器列表相关处理
void LauncherApp::loadPartList()
{
	m_partList.clear();
	wxString fileName = m_skinDir + _("//ServerList.xml");
	if (wxFile::Exists(fileName) == false)
	{
		// 服务器列表文件不存在
		return;
	}
	wxXmlDocument doc;
	if (doc.Load(fileName, "GB2312"))
	{
		/// 变量定义
		wxXmlNode *baseRoot = doc.GetRoot();		
		wxXmlNode *root = NULL;							// 操作节点
		wxXmlNode *subRoot = NULL;						// 文件节点
		SServerEntry sse;									// 服务器结构
		SPartEntry *spe;									// 区域结构
		wxString nodeName, serverName, address, state, partName, pid, sid, flag;
		long lpid = 0, lsid = 0, lstate = 0;
		
		/// 节点操作
		root = baseRoot->GetChildren();		
		while (root)
		{
			nodeName = root->GetName();
			// 区节点
			if (nodeName.IsSameAs(_("area")))
			{
				// 初始化区域
				partName = root->GetPropVal(_("name"), wxEmptyString);
				pid = root->GetPropVal(_("pid"),_("0"));
				pid.ToLong(&lpid);
				spe = new SPartEntry;
				spe->name = partName;
				spe->id = lpid;

				// 服务器子节点
				subRoot = root->GetChildren();
				while(subRoot)
				{					
					nodeName = subRoot->GetName();
					// server节点
					if (nodeName.IsSameAs(_("server")))
					{
						// 获取属性
						serverName = subRoot->GetPropVal(_("name"), wxEmptyString);
						address = subRoot->GetPropVal(_("address"), wxEmptyString);
						state = subRoot->GetPropVal(_("state"), _("0"));
						sid = subRoot->GetPropVal(_("sid"), _("0"));
						flag = subRoot->GetPropVal(_("flag"), wxEmptyString);
						sid.ToLong(&lsid);
						state.ToLong(&lstate);
						// 填充数据
						sse.name = serverName;
						sse.address = address;
						sse.state = (ESERVER_FLAG)lstate;
						sse.id = lsid;
						sse.flag = flag;
						// wxMessageBox(serverName, _("游戏提示"));
						// 添加到区域内服务器列表
						spe->serverList.push_back(sse);						
					}
					subRoot = subRoot->GetNext();
				}
				// 区循环
				m_partList.push_back(spe);
			}
			root = root->GetNext();			
		}
	}
	else
	{
		wxMessageBox(_("游戏服务器列表读取失败！"),_("游戏提示"));
	}
}

void LauncherApp::initServerList(int partIndex)
{
	if (m_partList.size())
	{
		/// 判定服务器列表是否已经加载过
		if (m_lastPart != -1)
		{
			if (m_lastPart == partIndex)
			{
				return;
			}
			else
			{
				SPartEntry *spe = m_partList.at(m_lastPart);
				spe->Hide();
			}
		}
		//按下状态标记服务区
		
		for (size_t i=0; i<m_btnPartList.size(); i++)
		{
			if (m_btnPartList.at(i)->GetFlag() == partIndex)
				m_btnPartList.at(i)->SetStateFlag(2);
			else
				m_btnPartList.at(i)->ShowNormalSkin();
		}


		/// 初始化服务器列表
		SPartEntry *spe = m_partList.at(partIndex);
		wxFont font(8, wxFONTFAMILY_DEFAULT, wxNORMAL, wxBOLD, false);
		char strName[256];
		m_lastPart = partIndex;
		for (size_t i=0; i<spe->serverList.size(); i++)
		{	
			SServerEntry sse = spe->serverList.at(i);
			/// 初始化服务器按钮
			
			//wxSkinButton *btn = new wxSkinButton(m_serverFrame, EVENT_ID_SELECT_SERVER,sse.name);	//modify by xcl ,初始状态时设置其大小为0，就不会出现左上角默认的10x10的方块闪烁
			wxSkinButton *btn = new wxSkinButton(m_serverFrame, EVENT_ID_SELECT_SERVER,sse.name,wxDefaultPosition,wxSize(0,0)); 
			btn->SetFlag(i);
			btn->Show(false);
			btn->SetFont(font);
			//btn->SetForegroundColour(wxColour(0,255,255,0));
			btn->SetFontColor(wxColour(230,218,169,0));	//modify by xcl
			btn->SetOverFontColor(wxColour(255,255,255,0));
			btn->SetActFontColor(wxColour(136,130,90,0));
			sprintf(strName,"%s%i",GetStateName(sse.state), i);
			// m_serverEngine->AssignControl(strName, btn);			// 全局重绘，会出现屏闪
			m_serverEngine->ReassignControlSkin(btn, strName);
			spe->buttonList.push_back(btn);
			
			/// 初始化标记
			wxSkinButton *flag = new wxSkinButton(m_serverFrame, -1, wxEmptyString, wxDefaultPosition, wxSize(0,0));
			sprintf(strName, "btn_%s%i", sse.flag, i);
			m_serverEngine->ReassignControlSkin(flag, strName);
			spe->flagList.push_back(flag);
		}
		m_serverFrame->Refresh();
		//m_serverEngine->InitializeSkin();
	}
}

wxString LauncherApp::GetStateName(int state)
{
	wxString res = wxEmptyString;
	switch (state)
	{
	case 0:
		res = _("btn_free");
		break;
	case 1:
		res = _("btn_full");
		break;
	case 2:
		res = _("btn_fullest");
		break;
	case 3:
		res = _("btn_servicing");
		break;
	default:
		break;
	}
	return res;
}

void LauncherApp::saveServerCfg()
{
	setConfig("SYSTEM/partID", m_cfgPart);
	setConfig("SYSTEM/serverID", m_cfgServer);
	setConfig("SYSTEM/serverURL", m_cfgAddress);
}

void LauncherApp::setVersion()
{
	wxString version = "Ver 0.0.0.0";
	loadConfig("SYSTEM/gameVersion", &version);
	m_btnVersion->SetLabel(_T("本地：") + version);		
	m_btnVersion->SetFontColor(wxColour(92, 169, 182));
	m_btnVersion->SetOwnBackgroundColour(wxColour(16, 78, 127));
	wxFont font = m_frame->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	font.SetPointSize(8);
	m_btnVersion->SetFont(font);

	//m_textVersion->SetLabel(version);
	//m_textVersion->SetFontColor(wxColour(92, 169, 182));
	//m_textVersion->SetFont(font);
}

void LauncherApp::setServerVerion()
{
	wxString version = "Ver 0.0.0.0";
	if (m_lastShowVersion.IsEmpty())
	{
		loadConfig("SYSTEM/gameVersion", &version);
		m_lastShowVersion = version;
	}	
	m_btnLastVersion->SetLabel(_T("最新：") + m_lastShowVersion);
	m_btnLastVersion->SetFontColor(wxColour(92, 169, 182));
	m_btnLastVersion->SetBackgroundColour(wxColour(16, 78, 127));
	wxFont font = m_frame->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	font.SetPointSize(8);
	m_btnLastVersion->SetFont(font);
}

////////////////////////////////////////////////////////////////////////// 服务器结构操作
void SPartEntry::Hide()
{
	if (buttonList.size())
	{
		for (size_t i=0; i<buttonList.size(); i++)
		{
			wxSkinButton *obj = buttonList.at(i);
			obj->Hide();
		}
	}
	if (flagList.size())
	{
		for (size_t i=0; i<flagList.size(); i++)
		{
			wxSkinButton *obj = flagList.at(i);
			obj->Hide();
		}
	}
}

void SPartEntry::Show()
{
	if (buttonList.size())
	{
		for (size_t i=0; i<buttonList.size(); i++)
		{
			wxSkinButton *obj = buttonList.at(i);
			obj->Show();
		}			
	}
	if (flagList.size())
	{
		for (size_t i=0; i<flagList.size(); i++)
		{
			wxSkinButton *obj = flagList.at(i);			
			obj->Show();
		}			
	}
}

////////////////////////////////////////////////////////////////////////// MyThread implementation.
MyThread::MyThread(LauncherApp *app) : wxThread()
{
	m_count = 0;
	m_app = app;
}

void *MyThread::Entry()
{
	m_app->doUpdateVersion();
	return m_app;
}

void MyThread::OnExit()
{
	m_count = 0;
}

void MyThread::DoUpdate()
{

}
