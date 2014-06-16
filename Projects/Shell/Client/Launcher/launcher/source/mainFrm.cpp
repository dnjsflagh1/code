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

// ���̼������
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
	// �ж�launcher�Ƿ���
	HWND hwnd = ::FindWindow(NULL,"ɽ��־ Launcher");
	if(hwnd)
	{
		return false;
	}

	// ��ʼ����Ա
	initMember();
	//wxInitAllImageHandlers();

	/// ��ȡ��������Ŀ¼
#ifndef __WXMAC__
	wxFileName fname (wxApp::argv[0]);
	fname.MakeAbsolute();
	m_skinDir = fname.GetPath();
#else
	m_skinDir = wxFileName::GetCwd();
#endif

	/// ��ֹ˫��laucher
	if(IsSelfRun())
	{
		// Exit();
		return false;
	}

	// �����ʱ�ļ�
	wxRemoveFile( m_skinDir + "\\Launcher_bak.exe" );	
	wxRemoveFile( m_skinDir + "\\Launcher_new.exe" );	

	/// ��ȡƤ��ѹ���ļ� wxSkinSimpleFrame
	m_mainEngine = AllocateEngine();
	m_mainEngine->Load(m_skinDir + _T("/sdata.dat"), _T("mainSkin.xml"));
	m_frame = new wxSkinSimpleFrame(NULL, -1, _T("ɽ��־ Launcher"));

	/// wxIE	
	//m_ie = new wxIEHtmlWin(m_frame, -1,wxPoint(316,329), wxSize(362,224),wxBORDER_NONE);
	m_ie = new wxIEHtmlWin(m_frame, -1,wxPoint(25,202), wxSize(358,223),wxBORDER_NONE);
	m_ie->LoadUrl(_T("http://shz.kx1d.com/clientnews/"));
	m_ie->ClearBackground();

	/// ���۾��ؼ�
	m_bigEye = new wxIEHtmlWin(m_frame, -1, wxPoint(390,202), wxSize(193,221), wxBORDER_NONE);
	m_bigEye->LoadUrl(_T("http://shz.kx1d.com/larcher/"));
	m_bigEye->ClearBackground();

	/// wxSkinSlider ������
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


	/// �ؼ�����
	btn_run = new wxSkinButton(m_frame, EVENT_ID_RUNGAME);
	wxSkinButton *btn_reg = new wxSkinButton(m_frame, EVENT_ID_SHOWREG);
	wxSkinButton *btn_recharge = new wxSkinButton(m_frame, EVENT_ID_SHOWPAY);
	// wxSkinButton *btn_set = new wxSkinButton(m_frame, -1);							// ���ð�ť��Ҫ������
	wxSkinButton *btn_web = new wxSkinButton(m_frame, EVENT_ID_SHOWWEB);
	wxSkinButton *btn_forum = new wxSkinButton(m_frame, EVENT_ID_SHOWFORUM);
	wxSkinButton *btn_faq = new wxSkinButton(m_frame, EVENT_ID_SHOWFAQ);
	wxSkinButton *btn_services = new wxSkinButton(m_frame, EVENT_ID_SHOWSRV);
	wxSkinButton *btn_manual = new wxSkinButton(m_frame, EVENT_ID_SHOWUPDATE);
	//wxSkinButton *btn_news = new wxSkinButton(m_frame, EVENT_ID_SHOWNEWS);
	wxSkinButton *btn_close = new wxSkinButton(m_frame, EVENT_ID_LCLOSE);
	//xcl���¶�̬�����Ż����Ϸ����
	//<<<  �߻�Ҫ��������������ť������ҳ���
	//btn_latestnew = new wxSkinButton(m_frame, EVENT_ID_SHOWLATESTNEW);
	//btn_newsevent = new wxSkinButton(m_frame, EVENT_ID_SHOWNEWSEVENT);
	//btn_gamenote = new wxSkinButton(m_frame, EVENT_ID_SHOWGAMENOTE);
	//>>>
	//-xcl
	m_btnVersion = new wxSkinButton(m_frame, -1);				// �汾�ŵ��ȥ���ֶ����½���
	m_btnLastVersion = new wxSkinButton(m_frame, -1);			// �����������°汾
	//m_textVersion = new wxSkinStaticText(m_frame, -1);
	setServerVerion();
	setVersion();

	/// �����ν�����Ϸ�����º���ˢ��
	setButtonState(btn_run, false);
	// setButtonState(btn_set, false);								// ���ð�ť����������


	////showFlashWin();

	/// ����Ƥ��	
	m_mainEngine->AssignControl(wxT("LauncherFrame"), m_frame);
	m_mainEngine->AssignControl(wxT("btn_run"), btn_run);
	m_mainEngine->AssignControl(wxT("btn_reg"), btn_reg);
	m_mainEngine->AssignControl(wxT("btn_recharge"),btn_recharge);
	// m_mainEngine->AssignControl(wxT("btn_set"),btn_set);		// ���ð�ť����������
	m_mainEngine->AssignControl(wxT("btn_web"),btn_web);
	m_mainEngine->AssignControl(wxT("btn_forum"),btn_forum);
	m_mainEngine->AssignControl(wxT("btn_faq"),btn_faq);
	m_mainEngine->AssignControl(wxT("btn_services"),btn_services);
	m_mainEngine->AssignControl(wxT("btn_manual"),btn_manual);	// �ֶ�����
	//m_mainEngine->AssignControl(wxT("btn_news"),btn_news);
	m_mainEngine->AssignControl(wxT("btn_close"),btn_close);
	m_mainEngine->AssignControl(wxT("btn_version"),m_btnVersion);					// �汾
	m_mainEngine->AssignControl(wxT("btn_serverVersion"), m_btnLastVersion);	// ���������°汾
	////<<<xcl �߻�Ҫ��ر�		
	//m_mainEngine->AssignControl(wxT("btn_latestnew"),btn_latestnew);
	//m_mainEngine->AssignControl(wxT("btn_newsevent"),btn_newsevent);
	//m_mainEngine->AssignControl(wxT("btn_gamenote"),btn_gamenote);
	//>>>-xcl
	m_mainEngine->InitializeSkin();	

	/// ��ʼ������
	SetTopWindow(m_frame);
	//m_frame->SetSize(1095,850);
	m_frame->SetSize(621,583);

	/// �������
	m_frame->Show();
	m_frame->Refresh();	
	m_frame->Centre();


	/// �ȳ�ʼ�������ļ��汾
	//loadLocalFileVersion();

	/// launcher���ֲ���
	//playMusic();

	// ��ȡ�����ļ�
	initFromCfg();												// ��ȡ�����ļ�
	InitMainGauge();											// ��ȡ���½���

	// ���ͻ����Ƿ��Ѿ�����
	IsClientRun();
	threadUpdate();

	/// ����
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
	// Ƥ�������ͷ�
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
		// �ͷ������б�
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
	return(wxApp::OnExit());			// �����˳�
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
	m_accessedFlag = -1;		// δ���±�־λ
	m_updateVersion = 0;		// ��ǰ���°汾(GameVersion)
	m_inProcess = false;
	m_msgType = 0;
	m_thread = NULL;

	// progress bar
	m_subGauge = NULL;
	m_mainGauge = NULL;
	m_subProgressValue = 0;
	m_mainProgressValue = 0;
	m_mainAmountValue = 0;

	/// ��ʼ�������ļ�ֵ
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
/// APP����
void LauncherApp::OnRunGame(wxCommandEvent &event)
{	
	// @{{ �汾�����̵߳���
	if (m_accessedFlag == 0 || m_accessedFlag == 1)
	{
		wxMessageBox("��Ϸ���ڸ��£�����º��ٽ�����Ϸ...","ϵͳ��ʾ");
		return;
	}	
	// ���ڴ�����
	if (m_inProcess)
	{
		return;
	}	
	// }}@ end

	// �汾�˶�
	long localVersion = 0;
	wxString strVersion = wxEmptyString;
	loadConfig(_("SYSTEM/version"), &strVersion);
	strVersion.ToLong(&localVersion);

	// ����������
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
			// ������ȷ���˽�����Ϸ������Ӧ�ñ���������ѡ��
			if (m_cfgAddress.IsEmpty())				 
			{
				wxMessageBox("��ѡ�������¼����Ϸ������.", "ϵͳ��ʾ");
				return;
			}
			saveServerCfg();
				
			// ִ�пͻ���			
			wxString filePath = m_skinDir + wxString::Format(_T("\\bin\\Client.exe server=%s"), m_cfgAddress);
			long res = wxExecute(filePath, wxEXEC_ASYNC);
#ifdef _DEBUG
			// ��Ϣ����ʾ����ID���Լ�����·��
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
	// ��������	
	//playMusic();

	// �汾�������
	if (m_accessedFlag == 1)
	{
		// wxMessageBox("version update finished.");
		m_accessedFlag = 3;							// ������ɲ������κδ���
	}

	// ����������
	if(m_inProcess)
	{
		//m_subGauge->Show();
		//m_subGauge->SetValue(m_subProgressValue);
		//m_subGauge->SetToolTip(wxString::Format(wxT("%i"),m_subProgressValue) + _("/100"));		// �ٷֱȽ���
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

/// ��վ��ʾ
void LauncherApp::OnShowForum(wxCommandEvent &event)
{
	// ����̳
	if (m_cfgForum.IsEmpty())
		m_cfgForum = _("http://shz.kx1d.com/bbs/");
	ShellExecute(NULL, "open", m_cfgForum, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowWeb(wxCommandEvent &event)
{
	// �򿪹���
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
	// �ͷ�
	if (m_cfgServices.IsEmpty())
		m_cfgServices = _("http://www.kx1d.com/service/index.shtml");
	ShellExecute(NULL, "open", m_cfgServices, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowReg(wxCommandEvent &event)
{
	// ע��ҳ��
	if (m_cfgRegister.IsEmpty())
		m_cfgRegister = _("http://passport.kx1d.com/member/register?gourl=http://www.kx1d.com/");
	ShellExecute(NULL, "open", m_cfgRegister, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowNews(wxCommandEvent &event)
{
	// ����ҳ��
	if (m_cfgNews.IsEmpty())
		m_cfgNews = _("http://shz.kx1d.com/php/newslist.php");
	ShellExecute(NULL, "open", m_cfgNews, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowUpdate(wxCommandEvent &event)
{
	//m_textVersion->SetSize(wxSize(70,20));
	
	// �ֶ�����ҳ��
	if (m_cfgDownload.IsEmpty())
		m_cfgDownload = _("http://shz.kx1d.com/download.html");
	ShellExecute(NULL, "open", m_cfgDownload, NULL, NULL, SW_SHOWNORMAL); 
}

void LauncherApp::OnShowPay(wxCommandEvent &event)
{
	// ��ֵҳ��
	if (m_cfgPay.IsEmpty())
		m_cfgPay = _("http://www.kx1d.com/pay/index.shtml");
	ShellExecute(NULL, "open", m_cfgPay, NULL, NULL, SW_SHOWNORMAL); 
}

//xcl
void LauncherApp::OnShowLatestnew(wxCommandEvent &event)
{
	// �� ���¶�̬
	m_ie->LoadUrl(_T("http://shz.kx1d.com/clientnews/"));
	m_ie->ClearBackground();

	//btn_latestnew->SetStateFlag(2);
	//btn_newsevent->ShowNormalSkin();
	//btn_gamenote->ShowNormalSkin();
}
void LauncherApp::OnShowNewsevent(wxCommandEvent &event)
{
	// �� ���Ż
	m_ie->LoadUrl(_T("http://shz.kx1d.com/clientnews/"));
	m_ie->ClearBackground();

	//btn_newsevent->SetStateFlag(2);
	//btn_latestnew->ShowNormalSkin();
	//btn_gamenote->ShowNormalSkin();

}
void LauncherApp::OnShowGamenote(wxCommandEvent &event)
{
	// �� ��Ϸ����
	m_ie->LoadUrl(_T("http://shz.kx1d.com/clientnews/"));
	m_ie->ClearBackground();

	//btn_gamenote->SetStateFlag(2);
	//btn_newsevent->ShowNormalSkin();
	//btn_latestnew->ShowNormalSkin();
}
//-xcl

/// �������
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
	values.sprintf("ȡֵ�����\n\nȫ��ѡ��		%i \n\n������ȡֵ��		%i\n", 
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
	/// ��ѡ������ť����ʼ���������б�
	wxSkinButton *obj = (wxSkinButton*)event.GetEventObject();
	int index = obj->GetFlag();
	initServerList(index);
	m_cfgPart = wxString::Format(wxT("%i"),index);
}

void LauncherApp::OnServerClick(wxCommandEvent &event)
{
	/// ��ѡ�ķ�������ť����ȡ���ַ
	wxSkinButton *obj = (wxSkinButton*)event.GetEventObject();
	int index = obj->GetFlag();
	SPartEntry *spe = m_partList.at(m_lastPart);	
	/// TODO index �� ID֮����л�
	m_cfgServer = wxString::Format(wxT("%i"),index);
	m_cfgAddress = spe->serverList.at(index).address;

	//��ʾһ������״̬
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
		m_helpFrame = new wxSkinSimpleFrame(m_frame, -1, _T("��������"));

		// �ؼ�ʵ��
		wxSkinButton *btn_act_forum = new wxSkinButton(m_helpFrame, EVENT_ID_SHOWFORUM);		// ��̳
		wxSkinButton *btn_act_web	= new wxSkinButton(m_helpFrame, EVENT_ID_SHOWWEB);		// ��ҳ
		wxSkinButton *btn_act_info	= new wxSkinButton(m_helpFrame, EVENT_ID_SYSINFO);		// ϵͳ��Ϣ
		wxSkinButton *btn_help_hide	= new wxSkinButton(m_helpFrame, EVENT_ID_HELP_HIDE);		// ȷ����ť		

		// ��Ƥ��
		m_helpEngine = AllocateEngine();
		m_helpEngine->Load(m_skinDir + _T("/skinfiles/launcher.zip"), _T("helpSkin.xml"));
		m_helpEngine->AssignControl(wxT("helpFrame"), m_helpFrame);
		m_helpEngine->AssignControl(wxT("btn_forum"), btn_act_forum);
		m_helpEngine->AssignControl(wxT("btn_web"), btn_act_web);
		m_helpEngine->AssignControl(wxT("btn_sysinfo"), btn_act_info);
		m_helpEngine->AssignControl(wxT("btn_ok"), btn_help_hide);
		m_helpEngine->InitializeSkin();
	}	

	// �������	
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
		m_systemInfoFrame = new wxSkinSimpleFrame(m_frame, -1, _T("ϵͳ˵��"));

		// �ؼ�ʵ��
		wxSkinButton *btn_info_hide	= new wxSkinButton(m_systemInfoFrame, EVENT_ID_INFO_HIDE);		// ȷ����ť		

		// ��Ƥ��
		m_systemInfoEngine = AllocateEngine();
		m_systemInfoEngine->Load(m_skinDir + _T("/skinfiles/launcher.zip"), _T("systemInfoSkin.xml"));
		m_systemInfoEngine->AssignControl(wxT("systemInfoFrame"), m_systemInfoFrame);
		m_systemInfoEngine->AssignControl(wxT("btn_ok"), btn_info_hide);
		m_systemInfoEngine->InitializeSkin();
		
		// ����ϵͳ��Ϣ
		wxArrayString info = getSystemInfo();
		if (info.size())
		{			
			wxFont font(12,wxFONTFAMILY_ROMAN  ,wxNORMAL,wxBOLD);	// ��������
			wxBoxSizer *sizer  = new wxBoxSizer(wxVERTICAL);		// ����
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

	// �������	
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
		m_optionFrame = new wxSkinSimpleFrame(m_frame, -1, _T("����ѡ��"));

		// �ؼ�ʵ��
		wxSkinButton *btn_save_option	= new wxSkinButton(m_optionFrame, EVENT_ID_OPTION_SAVE);		// ȷ����ť,��������
		wxSkinButton *btn_cancel_option	= new wxSkinButton(m_optionFrame, EVENT_ID_OPTION_HIDE);		// ȡ����ť,���ؽ���
		m_chkFullScreen = new wxSkinCheckBox(m_optionFrame, -1);
		m_sliderVol = new wxSkinSlider(m_optionFrame, -1);								// ��ֵ

		// ��Ƥ��
		m_optionEngine = AllocateEngine();
		m_optionEngine->Load(m_skinDir + _T("/skinfiles/launcher.zip"), _T("optionSkin.xml"));
		m_optionEngine->AssignControl(wxT("optionFrame"), m_optionFrame);
		m_optionEngine->AssignControl(wxT("btn_ok"), btn_save_option);
		m_optionEngine->AssignControl(wxT("btn_cancel"), btn_cancel_option);
		m_optionEngine->AssignControl(wxT("chk_fullScreen"), m_chkFullScreen);
		m_optionEngine->AssignControl(wxT("sldTerrain"), m_sliderVol);
		m_optionEngine->InitializeSkin();

		// ����ѡ����Ϣ
		m_sliderVol->SetRange(100);
		m_sliderVol->SetValue(50);
			
	}	
	// �������	
	SetTopWindow(m_optionFrame);	
	m_optionFrame->SetSize(398, 366);
	m_optionFrame->Center();
	m_optionFrame->Show(true);
	m_optionFrame->Refresh();
}

void LauncherApp::showFlashWin()
{
	// ����gif��ʽͼƬ
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
		// �����ʼ��
		m_serverFrame = new wxSkinSimpleFrame(m_frame, -1, _T("������ѡ��"));

		/// �ؼ�ʵ��
		/// ��Ƥ��
		m_serverEngine = AllocateEngine();
		m_serverEngine->Load(m_skinDir + _T("/sdata.dat"), _T("ServerList.xml"));
		m_serverEngine->AssignControl(wxT("ServerFrame"), m_serverFrame);
		// ��ʾ�������б�
		if (m_partList.size())
		{
			wxFont font(8, wxFONTFAMILY_DEFAULT, wxNORMAL, wxFONTWEIGHT_BOLD, false);
			SPartEntry *spe;			
			char strName[256];
			bool res;
			for(size_t i=0; i<m_partList.size(); i++)
			{
				spe = m_partList.at(i);
				wxSkinButton *btn_part	= new wxSkinButton(m_serverFrame, EVENT_ID_SELECT_PART, spe->name);		// ȷ����ť,��������
				btn_part->SetSize(136,35);
				btn_part->SetFlag(i);					// ���ñ��
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
		

		// ��ťƤ��
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
		
		// ��ʼ��Ƥ��
		m_serverEngine->InitializeSkin();
	}	
	// �������	
	SetTopWindow(m_serverFrame);	
	//m_serverFrame->SetSize(1095,850); //del by xcl �������в��ܾ�����ʾ����
	m_serverFrame->SetSize(621,583); //del by xcl �������в��ܾ�����ʾ����
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


// ���ű�������
void LauncherApp::playMusic()
{	
	if (m_sound.IsOk() == false)
	{
		//��ʽ���ַ�ΪUTF��ʽ������wxString�ַ������� 
		wxString soundString(m_skinDir + g_bgSound, wxConvUTF8); 
		//����wxSound���� 	 
		m_sound.Create(soundString,false); 	
		m_sound.Play(true);	
	}
	// m_sound.IsPlaying();	// wxWidgets: This method is currently not implemented under Windows. so that backGroup music not loop.
}


////////////////////////////////////////////////////////////////////////// socket & update (useless) ��������ʱ����Ҫ�汾���·�����
void LauncherApp::checkGameVersion()
{
	wxString version;
	SystemInfo::GetFileVersionOfGame(m_skinDir + _("\\calc.exe"), &version);
	if (version.Trim().IsNull() || version.Trim().IsEmpty())
	{
		// δȡ���汾
		return;
	}
	if (canConnect() && m_inProcess == false)
	{
		m_inProcess = true;
		unsigned char len = 0;
		m_msgType = ENM_VERSION_CHECK;
		m_socket->Write(&m_msgType, 1);
		m_socket->SetFlags(wxSOCKET_WAITALL);
		// ������Ϸ����
		len = unsigned char((strlen(g_gameName)+1) * sizeof(char));
		m_socket->Write(&len,1);
		m_socket->Write(g_gameName, len);
		// ������Ϸ�汾
		len = unsigned char((wxStrlen(version.c_str())+1) * sizeof(wxChar));
		m_socket->Write(&len,1);
		m_socket->Write(version.c_str(), len);
		// �汾��Ϣȷ�ϻش�
		unsigned char msgBack = 0;
		m_socket->Read(&msgBack, 1);
		if (msgBack)
		{
			// ���ø��°�ťEnable ���� �����û�ȷ��ģ̬���塣
			wxMessageBox(_("��Ҫ���°汾."));
		}
		m_inProcess = false;
	}
}

// ��������
void LauncherApp::test1()
{
	///<<< MD5 ����
	const wxString file = "d:\\a.txt";
	//const wxString md5Str = "917b2c5c3d5cf2f013cf323a360dcc93";
	const wxString md5Str = "917B2C5C3D5CF2F013CF323A360DCC93";
	wxChar msg[256];
	if (checkFileMD5(file, md5Str))
	{				
		wxSprintf(msg, "�ļ�ƥ��ɹ���MD5��Ϊ��%s", md5Str);		
	}
	else
	{
		if (wxFile::Exists(file))
		{
			wxString md5Res = wxMD5::GetFileMD5(file);
			wxSprintf(msg, "�ļ�ƥ��ʧ�ܣ�����MD5��Ϊ��[%s],Զ��MD5��Ϊ[%s]", md5Res, md5Str);
		}
		else
		{
			wxSprintf(msg, "MD5�����ļ�[%s]������", file);
		}
	}
	wxMessageBox(msg, _T("�ļ�MD5�����"));
	///>>> MD5 ����

	/*
	if (m_inProcess)
	{
		wxMessageBox(_T("���緱æ���Ժ�����..."), _T("������ʾ"));
		return;
	}
	// ��λϵͳæ
	m_inProcess = true;

	// ������Ϣ
	unsigned char len = 0;
	const wxChar *msg = _T("��������...\n");
	wxChar *msgBack = new wxChar[wxStrlen(msg)+1];
	m_msgType = (unsigned char)ENM_TEST_1;

	// ����&������Ϣ
	m_socket->Write(&m_msgType, 1);
	m_socket->SetFlags(wxSOCKET_WAITALL);							// ����״̬λ�ȴ����л�Ӧ
	len = (unsigned char)((wxStrlen(msg)+1) * sizeof(wxChar));		// ������Ϣ�����ֽڳ��ȡ�
	m_socket->Write(&len, 1);
	m_socket->Write(msg, len);

	m_socket->Read(msgBack, len);
	wxMessageBox(wxString(msgBack));
	// ����
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
		wxMessageBox(_T("���緱æ���Ժ�����..."), _T("������ʾ"));
		return false;
	}
	if (m_socket && canConnect())
	{
		m_inProcess = true;
		unsigned char len = 0;
		wxArrayString resultContainer;
		// ��������
		m_msgType = ENM_GET_DOWNLOAD_URL;
		m_socket->Write(&m_msgType, 1);
		m_socket->SetFlags(wxSOCKET_WAITALL);
		// ������Ϸ����
		len = unsigned char((strlen(g_gameName)+1) * sizeof(char));
		m_socket->Write(&len,1);
		m_socket->Write(g_gameName, len);
		// ��ȡ������������
		long urlAmount = 0;
		m_socket->Read(&urlAmount, sizeof(long));		
		// ѭ����ȡ��������
		wxChar *temp = NULL;
		for (int i=0; i<(int)urlAmount; i++)
		{
			m_socket->Read(&len, 1);
			temp = new wxChar[len];
			m_socket->Read(temp, len);
			resultContainer.Add(wxString(temp));
			delete temp;
		}
		// �������س���
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
		// ��ȡ���������ļ�Ĭ�����ص�ַ����
	}
	return false;
}


////////////////////////////////////////////////////////////////////////// http & update (current use)
// ��ȡԶ���ļ�
bool LauncherApp::getUrlFile(const wxString &url,const wxString &md5, unsigned char urlType, const wxString dir, wxString saveName)
{	
	if (!m_inProcess)
		return false;

	// access ftp fileName
	wxString fileName = url.substr(url.Last('/')+1);	// ���û��ָ���ļ�������ʹ�����ӵ�ַ�ļ���
	if (saveName.IsEmpty())
		saveName = fileName;
	bool res = true;

	// access save file.

	// �ļ�Ԥ�ж�		
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
		wxSprintf(msg, "[%s] �뱾��MD5У��һ�£����º��ԡ�", fileName);
		wxMessageBox(msg, _T("������ʾ"));
#endif
	}		
	else
	{
		// ��ȡ�ļ�
		wxString savePath = dir.IsEmpty()? m_skinDir+"\\" + saveName:m_skinDir+"\\"+ dir+"\\" + saveName;		
		res = realGetUrlFile(url, urlType, savePath, md5);
		// �ж����Ҹ���
		if (res && saveName.CmpNoCase("launcher_new.exe") == 0)
		{
			UpgradeSelf();
		}
		if (res && saveName.StartsWith("patch") && saveName.EndsWith(".exe"))
		{
			proccessPatch(saveName);
		}		
	}	

	// ����ɹ��Ҵ������������㣬������������(�е������ж�)
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
	wxString lastError = "�ļ���ȡ�ɹ�.";
	// HTTP ģʽ
	if (urlType == EUT_HTTP)
	{			
		wxURL *purl = new wxURL(url);		
		wxInputStream *in = purl->GetInputStream();		
		if (!in)
		{
			lastError = "��Чhttp������.";
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
	// FTP ģʽ
	else if (urlType == EUT_FTP)
	{
		wxString fileName = url.substr(url.Last('/')+1);
		wxFTP ftp;
		// access ftp hostName
		wxString tempFtpAddr = url.substr(0, url.Index('/'));
		// access ftp Dir
		wxString fileDir = url.substr(tempFtpAddr.Len(), url.Len()-tempFtpAddr.Len()-fileName.Len());		
		//ftp.SetUser(_("Anonymous"));	//��������
		ftp.SetUser(_("guest"));
		//ftp.SetPassword(wxEmptyString);
		if ( !ftp.Connect(tempFtpAddr))
		{
			lastError = "ftp����������ʧ��.";
			res = false;
		}
		else
		{
			ftp.ChDir(fileDir);
			// �ļ�����С�ж�
			int size = ftp.GetFileSize(fileName);
			if ( size == -1 )
			{
				lastError = "��Чftp�ļ��ߴ�.";
				res = false;
			}
			else
			{
				// �ļ����ж�
				wxInputStream *in = ftp.GetInputStream(fileName);
				if ( !in )
				{
					lastError = "��Чftp������.";
					res = false;
				}
				else
				{
					// �����ļ�
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
		//TODO: ʵ��HTTPS,��������ļ�������ļ�
	}
#ifdef _DEBUG
	wxMessageBox(lastError, "ϵͳ��ʾ");
#endif
	return res;
}

// �����ļ�
bool LauncherApp::SaveFile(wxInputStream *in, const wxString& saveName, const wxString &md5, bool showGauge, const size_t fileSize)
{
	wxString lastError = "�ļ�����ɹ�.";
	bool res = true;
	m_subProgressValue = 0;
	size_t size = fileSize;
	if (size == 0)
		size = in->GetSize();
	if (size>0)
	{
		// �ļ�����
		char *data = new char[size];		// ���ݻ���
		if ( !in->Read(data, size) )
		{
			lastError = "��Ч�ļ�������.";
			res = false;
		}
		else
		{
			//////////////////////////////////////////////////////////////////////////  ֱ��д��
			wxFile sfile;			
			sfile.Open(saveName, wxFile::write, wxS_DEFAULT);
			sfile.Write(data, size);
			sfile.Flush();
			sfile.Close();
			//////////////////////////////////////////////////////////////////////////  ���ֽ�д��
			
#pragma region  // file data is in the buffer
			if (0)
			{
				size_t i;			
				wxFileOutputStream out(saveName);

				/*ofstream out(saveName, ios::out|ios::binary);*/
				if(!out) 
				{				
					lastError = "�ļ����������ʧ�ܣ�����Ŀ¼��дȨ��.";
					res = false;
				}
				else
				{									
					for(i=0; i<size; i++) 
					{
						/// 
						if (!m_inProcess)
						{
							lastError = "�ļ������ж��˳�.";
							res = false;
							break;
						}
						/*out.put(data[i]);*/
						out.PutC(data[i]);

						// �ļ�������
						if (showGauge)
						{						
							int mark = (i*100)/size; // ����ٷֱ�
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
								//m_subGauge->SetToolTip(wxString::Format(wxT("%i"),m_subProgressValue) + _("/100"));		// �ٷֱȽ���						
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

		// �ж�MD5��
		if (md5.IsEmpty() == false && wxFile::Exists(saveName))
		{
			if (!checkFileMD5(saveName, md5))
			{				
				lastError = "�ļ�У�鲻ƥ�䣬����ʧ��.";
				res = false;
			}
		}	
	}
	else
	{
		lastError = "��Ч�ļ��������ߴ�.";
		res = false;
	}

#ifdef _DEBUG
	if (res)
	{
		wxMessageBox(lastError, _T("ϵͳ��ʾ"));				
	} 
	else
	{
		wxMessageBox(saveName, _T("�ļ�����"));
	}
#endif	
	return res;	
}

// ����ļ�MD5
bool LauncherApp::checkFileMD5(const wxString &fileName, const wxString &md5str)
{
	if (wxFile::Exists(fileName))
	{
		wxString fileMD5 = wxMD5::GetFileMD5(fileName);
		return (fileMD5.CmpNoCase(md5str)==0);
	}
	return false;
}

// ���ذ汾���
bool LauncherApp::needUpdate(int remoteVersion)
{
	wxString values;
	bool res = loadConfig( _("SYSTEM/version"), &values);
	long lastVersion = 0;
	values.ToLong(&lastVersion);
	if(lastVersion < remoteVersion)
	{
		// ��Ҫ���£�����¼��Ҫ���µİ汾�ţ��Ա��д�����ļ���
		m_updateVersion = remoteVersion;
		return true;
	}
	return false;
}

// �����ļ���ȡ
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

// �����ļ�����
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


// ��ȡ�汾��������ַ
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
		// ֱ�ӻ�ȡʧ�ܣ��������ص������ٷ���
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

// �������
void LauncherApp::UpgradeSelf()
{
	// �Ƴ��ɰ汾�ļ�
	wxString temp = m_skinDir  + "\\Launcher_bak.exe";
	remove(temp.c_str());											// �Ƴ�������ʱ�����Ա����Ŀ�����������

	wxString src = m_skinDir + "\\Launcher_new.exe";		// Դ���򣬼����Ǵӷ��������������ĳ���
	wxString dst = m_skinDir + "\\Launcher.exe";				// Ŀ����򣬼�Ҫ�滻�ĳ���
	
	wxChar buffer[512];
	wxStrcpy(buffer, dst.c_str());								// ����Ŀ���ļ���	

	rename(dst.c_str(),temp.c_str());							// ����ǰ��������Ϊ��ʱ
	CopyFile(src.c_str(),dst.c_str(),false);					// �����³��򸲸�Ŀ�����

	// ���̴���API��ʼ��������������
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

// ��Ϸ���б����ļ����
bool LauncherApp::checkCoreFile()
{
	// ��ȡ����������xml	
	wxXmlDocument doc;	// XML�汾�ļ�		
	if (getRemoteVersionFile(&doc, "core.xml") == false)
	{					
		return true;		
	}

	//��������ʼ��
	m_coreFile.reserve(GAME_CORE_FILE_AMOUNT);	// ��ʼ�������ڴ棬�����׼��ı�������
	m_mainProgressValue = 0;
	m_subProgressValue = 0;

	// �汾�˶�
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
				// ��ȡ����
				fileName = subNode->GetPropVal(_("name"), wxEmptyString).Trim();
				path = subNode->GetPropVal(_("local"), wxEmptyString).Trim();
				md5 = subNode->GetPropVal(_("md5"), wxEmptyString).Trim();
				url = subNode->GetPropVal(_("url"), wxEmptyString).Trim();
				
				// md5�Ա�
				if (path.empty() == false)
					localFile = m_skinDir+ "\\" + path +"\\"+ fileName;
				else
					localFile = m_skinDir+ "\\" + fileName;
				// TODO: ����û������ļ�,��ǰ��ֱ�����أ����洢�����ء�
				if (wxFile::Exists(localFile) == false)
				{
					// launcher���⴦��
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
					// �����ļ�
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
		if (wxMessageBox("��Ϸ�����ļ�У�鲻ƥ�䣬���ܵ�����Ϸ�޷����У��Ƿ����?", "ϵͳ��ʾ", wxYES_NO) == wxYES)
		{
			m_inProcess = true;	// ��ʼ�����ļ���������
			// �����ļ�
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

// �汾���º��ĺ���
void LauncherApp::doUpdateVersion()
{
	if (m_accessedFlag == 3)
		return;
	// loadLocalFileVersion();	// �ȳ�ʼ�������ļ��汾
	bool processSuccess = true;

	// ��ȡ���·�������ַ
	if (true)
	{					
		wxXmlDocument doc;	// XML�汾�ļ�		
		if (getRemoteVersionFile(&doc) == false)
		{	
			wxMessageBox(_T("�汾�ļ�����ʧ�ܣ����Ժ����Ի���ϵ�ͷ�"), _T("ϵͳ��ʾ"),wxOK);
			return;		
		}

		// �ļ���������Ԥ��		
		if (m_mainAmountValue)
		{
			if(m_mainGauge->IsShown() == false)
				m_mainGauge->Show();
		}
		// �ļ�����
		wxXmlNode *root = doc.GetRoot();		
		wxXmlNode *baseRoot = NULL;					// ������ڵ�
		wxXmlNode *subRoot = NULL;						// �ļ��ڵ�
		wxString gameName;								// ��Ϸ����		
		baseRoot = root->GetChildren();
		root = root->GetChildren();
		m_inProcess = true;		

		// ��Ϸ�汾�ڵ�
		while(root)
		{
			m_accessedFlag = 0;		// �汾������
			// �ж�Game�ڵ����Ϸ�����Ƿ���ɽ��־
			root->GetAttribute(_("name"), &gameName);			
			if (root->GetName() == _("game") && gameName.IsSameAs(_("SHZ")))
			{
				// �жϵ�ǰ����Ϸ�汾���Ƿ���Ҫ���£� 
				wxString fileName, fileVersion, fileUrl, updateType, fileLocal, gameVersion, fileMD5;				
				gameVersion = root->GetPropVal(_("version"), _(""));									// ��ȡ�ø����б��Ӧ����Ϸ�汾
				m_remoteVerion = root->GetPropVal(_("gameVersion"), m_localVerion);				// ��ȡԶ�̷������汾��
				long remoteVersion;
				gameVersion.ToLong(&remoteVersion);						
				if (needUpdate(remoteVersion) == false)
				{
					root = root->GetNext();
					continue;
				}

				// ��Ϸ�汾���£���ȡGame�ڵ���ӽڵ������ļ�����
				subRoot = root->GetChildren();				
				while (subRoot)
				{
					updateType = subRoot->GetName();
					// �жϽڵ����ͣ�����[file/dir/zip/dat]������ע�ͣ������ע�ͣ���������һ�֡�
					// TODO: ��zip�ļ��Զ���ѹ
					if (updateType.IsSameAs(_("comment")))
					{
						subRoot = subRoot->GetNext();
						continue;
					}
					// �ļ���Ϣ��ȡ
					fileLocal = subRoot->GetPropVal(_("local"), wxEmptyString).Trim();							// ���ش��·��
					fileName = subRoot->GetPropVal(_("name"), wxEmptyString).Trim();								// �ļ�����
					fileVersion = subRoot->GetPropVal(_("version"),wxEmptyString).Trim();						// �ļ��汾
					fileUrl = subRoot->GetPropVal(_("url"),wxEmptyString).Trim();									// �ļ�����������λ��
					fileMD5 = subRoot->GetPropVal(_("md5"), wxEmptyString).Trim();									// ��ȡ�ļ�MD5��

					// �������ӵ�ַ����
					unsigned char urlType = getUrlType(&fileUrl);

					
					if (updateType.IsSameAs(_("dir")))// ����Ŀ¼
					{
						// �����ļ��У�
						wxString dir = m_skinDir + "\\" + fileName;
						if (!::wxDirExists(dir))
						{
							::wxMkDir(dir);
						}
					}
					else if (updateType.IsSameAs(_("exe")) || updateType.IsSameAs(_("dll")))// �ļ�����
					{
						// �ļ����£��汾У�����������MD5��
						//if (getFileVersion(fileName).IsSameAs(fileVersion.c_str()) == false || fileVersion.IsEmpty())
						//{
						//	processSuccess &= getUrlFile(fileUrl, urlType, fileLocal, fileName);
						//}
						processSuccess &= getUrlFile(fileUrl, fileMD5, urlType, fileLocal, fileName);
					}										
					else	// rar��dat ���������ļ����������¸���
					{
						if (fileUrl.IsEmpty()==false && urlType != EUT_NONE)
							processSuccess &= getUrlFile(fileUrl,fileMD5, urlType, fileLocal, fileName);
					}
					wxThread::Sleep(1);
					// һ�������ӿ鴦����ɣ�������һ��
					subRoot = subRoot->GetNext();
				}
			}
			// ����ɽ��־��Ϸ�Ľڵ�ģ�飬�������Ǹ�ģ�鴦������		
			root = root->GetNext();
		}
		m_inProcess = false;
	}

	// ������ɺ󣬺����ļ����
	checkCoreFile();

	// �汾�������
	m_accessedFlag = 1;		
	m_inProcess = false;
	if (m_updateVersion > 0 && processSuccess == true)
	{
		// �汾��ȫ���³ɹ�
		wxMessageBox(_T("��Ϸ�汾���³ɹ����"),_T("�汾����"));
		setConfig(_("SYSTEM/version"), wxString::Format(wxT("%i"),m_updateVersion));
		setConfig(_("SYSTEM/gameVersion"), m_remoteVerion);
		m_btnVersion->SetLabel(_T("���أ�") + m_remoteVerion);
	}	

	// ��ԭ��ʼ��Ϸ��ť
	setButtonState(btn_run, true);
	
#if 0
		// �ļ���ȡ����
		size_t sizes = inputStream->GetSize()+1;
		char *buff = new char[sizes];
		inputStream->Read(buff, sizes);
		delete[] buff;
#endif	
}

void LauncherApp::proccessPatch(const wxString &fileName)
{
	// �����Խ�ѹ�ļ�	
	wxString patchPath  = fileName.IsEmpty() ?m_skinDir + "\\patch.exe":m_skinDir + "\\" +fileName;
	if (wxFile::Exists(patchPath))
	{
		/* �Ϻ�����δ�ܴﵽ�ȴ�Ч��
		if (ShellExecute(NULL,_T("open"), patchPath, NULL, NULL, true))
		{
#ifdef _DEBUG		
			wxMessageBox("�Խ�ѹ�ļ�����ɹ���", "ϵͳ��ʾ");
#endif			
		}
		else
		{
#ifdef _DEBUG		
			wxMessageBox("�Խ�ѹ�ļ�����ʧ�ܡ�", "ϵͳ��ʾ");
#endif
		}
		wxThread::Sleep(1000);	// ��ѹ���ļ�����ʱ�䲻��
		*/

		//<<< MSDN��׼�ȴ�
		SHELLEXECUTEINFO   sei;
		//   ��������
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
		// �������������ǵȴ��ý��̽���
		WaitForSingleObject(sei.hProcess,   INFINITE);
		// Ҳ����ֱ�ӹر�������̣�ֻҪ����sei.hProcess����
		// TerminateProcess(sei.hProcess,   0); 
		//>>>
		
		bool result = wxRemoveFile(patchPath);
		short amount = 0;
		while (!result)
		{
			// ����ɾ10�Σ����10��ȫ��ʧ�ܣ������ɾ�����Ժ�����patch���������ǡ�
			result = wxRemoveFile(patchPath);
			if (amount >= 10)
				break;
			amount++;
		}
	}

}

// ��ȡ��������
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

// �˶�������
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

	// ��ʼ����
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
			gameVersion = root->GetPropVal(_("version"), _(""));									// ��ȡ�ø����б��Ӧ����Ϸ�汾
			m_lastShowVersion = root->GetPropVal(_("gameVersion"), _(""));						// ��ȡʵ�ʰ汾
			gameVersion.ToLong(&remoteVersion);
			if (needUpdate(remoteVersion) == false)
			{
				root = root->GetNext();
				continue;
			}
			subRoot = root->GetChildren();
			while (subRoot)
			{
				// �ж��Ƿ���ע�ͻ��ߴ���Ŀ¼
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
	m_lastVersion = remoteVersion;						// ��ȡ���������°汾
	m_btnLastVersion->SetLabel(_T("���£�") + m_lastShowVersion);	// ��ʾ���������°汾
	return true;
}

// �ͻ����Ƿ�������
bool LauncherApp::IsClientRun()
{
	HWND hwnd = ::FindWindow(NULL,"ɽ��־ ONLINE");
	if(hwnd)
	{
		wxMessageBox(_("ɽ��־�ͻ����Ѿ������������ȹرտͻ��ˡ�"),_("ϵͳ��ʾ"));
		// ::SendMessage(hwnd, WM_CLOSE, NULL,NULL);												// û��Ҫǿ�ƹرտͻ���
		return true;
	}
	// û��Ҫ��ô�鷳����������ƽ̨�ˣ�������ϷҲ����������ƽ̨���С�
	//std::vector<ProcessEntry> l;
	//GetProcessList(l);

	//for(size_t i=0; i<l.size(); i++){
	//	ProcessEntry pe = l.at(i) ;
	//	wxPrintf(wxT("%s %d\n"), pe.name.c_str(), pe.pid);
	//}
	return false;
}

// ����Ƿ�����launcher
bool LauncherApp::IsSelfRun()
{
	return false;	// Ӱ���Ը���ִ��
	HWND hwnd = ::FindWindow(NULL,"ɽ��־ Launcher");
	if(hwnd)
	{
		wxMessageBox(_("ɽ��־Launcher�Ѿ����С�"),_("ϵͳ��ʾ"));
		// ::SendMessage(hwnd, WM_CLOSE, NULL,NULL);
		return true;
	}
	return false;
}



// ��ȡ�����б�
void LauncherApp::GetProcessList(std::vector<ProcessEntry> &proclist)
{
#ifdef __WXMSW__
	OSVERSIONINFO osver ;

	// ϵͳ�汾��֧�־ͷ���
	osver.dwOSVersionInfoSize = sizeof( osver ) ;
	if(!GetVersionEx(&osver))
	{		
		return;
	}
	if(osver.dwPlatformId != VER_PLATFORM_WIN32_NT){
		return;
	}

	// ��ȡ���̽ڵ�
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

// ִ������
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

// ��ȡ����dll exe�ļ��Լ��汾
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

// �����ļ��汾��Ϣ��ȡ
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

// ���̸���
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


////////////////////////////////////////////////////////////////////////// �������б���ش���
void LauncherApp::loadPartList()
{
	m_partList.clear();
	wxString fileName = m_skinDir + _("//ServerList.xml");
	if (wxFile::Exists(fileName) == false)
	{
		// �������б��ļ�������
		return;
	}
	wxXmlDocument doc;
	if (doc.Load(fileName, "GB2312"))
	{
		/// ��������
		wxXmlNode *baseRoot = doc.GetRoot();		
		wxXmlNode *root = NULL;							// �����ڵ�
		wxXmlNode *subRoot = NULL;						// �ļ��ڵ�
		SServerEntry sse;									// �������ṹ
		SPartEntry *spe;									// ����ṹ
		wxString nodeName, serverName, address, state, partName, pid, sid, flag;
		long lpid = 0, lsid = 0, lstate = 0;
		
		/// �ڵ����
		root = baseRoot->GetChildren();		
		while (root)
		{
			nodeName = root->GetName();
			// ���ڵ�
			if (nodeName.IsSameAs(_("area")))
			{
				// ��ʼ������
				partName = root->GetPropVal(_("name"), wxEmptyString);
				pid = root->GetPropVal(_("pid"),_("0"));
				pid.ToLong(&lpid);
				spe = new SPartEntry;
				spe->name = partName;
				spe->id = lpid;

				// �������ӽڵ�
				subRoot = root->GetChildren();
				while(subRoot)
				{					
					nodeName = subRoot->GetName();
					// server�ڵ�
					if (nodeName.IsSameAs(_("server")))
					{
						// ��ȡ����
						serverName = subRoot->GetPropVal(_("name"), wxEmptyString);
						address = subRoot->GetPropVal(_("address"), wxEmptyString);
						state = subRoot->GetPropVal(_("state"), _("0"));
						sid = subRoot->GetPropVal(_("sid"), _("0"));
						flag = subRoot->GetPropVal(_("flag"), wxEmptyString);
						sid.ToLong(&lsid);
						state.ToLong(&lstate);
						// �������
						sse.name = serverName;
						sse.address = address;
						sse.state = (ESERVER_FLAG)lstate;
						sse.id = lsid;
						sse.flag = flag;
						// wxMessageBox(serverName, _("��Ϸ��ʾ"));
						// ��ӵ������ڷ������б�
						spe->serverList.push_back(sse);						
					}
					subRoot = subRoot->GetNext();
				}
				// ��ѭ��
				m_partList.push_back(spe);
			}
			root = root->GetNext();			
		}
	}
	else
	{
		wxMessageBox(_("��Ϸ�������б��ȡʧ�ܣ�"),_("��Ϸ��ʾ"));
	}
}

void LauncherApp::initServerList(int partIndex)
{
	if (m_partList.size())
	{
		/// �ж��������б��Ƿ��Ѿ����ع�
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
		//����״̬��Ƿ�����
		
		for (size_t i=0; i<m_btnPartList.size(); i++)
		{
			if (m_btnPartList.at(i)->GetFlag() == partIndex)
				m_btnPartList.at(i)->SetStateFlag(2);
			else
				m_btnPartList.at(i)->ShowNormalSkin();
		}


		/// ��ʼ���������б�
		SPartEntry *spe = m_partList.at(partIndex);
		wxFont font(8, wxFONTFAMILY_DEFAULT, wxNORMAL, wxBOLD, false);
		char strName[256];
		m_lastPart = partIndex;
		for (size_t i=0; i<spe->serverList.size(); i++)
		{	
			SServerEntry sse = spe->serverList.at(i);
			/// ��ʼ����������ť
			
			//wxSkinButton *btn = new wxSkinButton(m_serverFrame, EVENT_ID_SELECT_SERVER,sse.name);	//modify by xcl ,��ʼ״̬ʱ�������СΪ0���Ͳ���������Ͻ�Ĭ�ϵ�10x10�ķ�����˸
			wxSkinButton *btn = new wxSkinButton(m_serverFrame, EVENT_ID_SELECT_SERVER,sse.name,wxDefaultPosition,wxSize(0,0)); 
			btn->SetFlag(i);
			btn->Show(false);
			btn->SetFont(font);
			//btn->SetForegroundColour(wxColour(0,255,255,0));
			btn->SetFontColor(wxColour(230,218,169,0));	//modify by xcl
			btn->SetOverFontColor(wxColour(255,255,255,0));
			btn->SetActFontColor(wxColour(136,130,90,0));
			sprintf(strName,"%s%i",GetStateName(sse.state), i);
			// m_serverEngine->AssignControl(strName, btn);			// ȫ���ػ棬���������
			m_serverEngine->ReassignControlSkin(btn, strName);
			spe->buttonList.push_back(btn);
			
			/// ��ʼ�����
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
	m_btnVersion->SetLabel(_T("���أ�") + version);		
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
	m_btnLastVersion->SetLabel(_T("���£�") + m_lastShowVersion);
	m_btnLastVersion->SetFontColor(wxColour(92, 169, 182));
	m_btnLastVersion->SetBackgroundColour(wxColour(16, 78, 127));
	wxFont font = m_frame->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	font.SetPointSize(8);
	m_btnLastVersion->SetFont(font);
}

////////////////////////////////////////////////////////////////////////// �������ṹ����
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
