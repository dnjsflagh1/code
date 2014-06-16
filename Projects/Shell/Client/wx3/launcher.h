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
	// ������������ڳ���������ʱ�򱻵��� 
	virtual bool OnInit (); 
	virtual int OnExit();

private:
	// ������
	wxSkinSimpleFrame*	mMainFrame;
	// IE�ؼ�
	wxIEHtmlWin*		mIe;
	// skinEngine
	wxSkinEngine*		mMainEngine;

	// ���ע��
	wxSkinButton mBtnFreeRegistration;
	// ������ֵ
	wxSkinButton mBtnRecharge;
	// �ٷ���վ
	wxSkinButton mBtnOfficialWebsite;
	// �ٷ���̳
	wxSkinButton mBtnOfficialForum;
	// ��Ϸ����
	wxSkinButton mBtnGameSetting;
	// ��Ϸ����
	wxSkinButton mBtnDownload;
	// �汾˵��
	wxSkinButton mBtnVerCaption;
	// ��Ϸ�޸�
	wxSkinButton mBtnGameRepair;
	// �ֶ�����
	wxSkinButton mBtnManualUpdate;
	// ��ʼ��Ϸ
	wxSkinButton mBtnGameStart;
	// �˳�
	wxSkinButton mBtnExit;

	// ��ǰ�汾
	wxSkinButton mStaticCurrVer;
	// ���°汾
	wxSkinButton mStaticNewVer;
	// �汾����
	wxSkinButton mStaticVerDesc;

	// ��ǰ����
	wxGauge mProcessCurr;
	// �ܽ���
	wxGauge mProcessAll;
	wxImage mProgressImg;


}; 

IMPLEMENT_APP(LuancherApp)
///////////////////////////////////////////////////////////////////////////
#endif //__NONAME_H__