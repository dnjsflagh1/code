
// ClientLuancherDlg.h : ͷ�ļ�
//
#include "Config.h"
//#include "explorer.h"
//#include "FTPUpdateDll.h"
//#include "GameUpdate.h"
#include "afxwin.h"
#include "SkinProgressCtrl.h"
#include "SkinButton.h"
#include "link.h"
//#include "CEndDlg.h"
#include "SkinDialog.h"
#include "UIConfig.h"
#include "SkinStatic.h"
#include "ExStaticCtrl.h"
#include <string>
#include "skinbutton.h"

#include "exstaticctrl.h"
#include "skinprogressctrl.h"
#include "explorer.h"
#include "RGNDLG.H"
using namespace std;
#pragma once


// CClientLuancherDlg �Ի���
class CClientLuancherDlg :  public CRGNDlg
{
// ����
public:
	CClientLuancherDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENTLUANCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnExit();
	//------------------------------------------------------------

	void		InitCtrlPos();
	void		UpdateExplorer();
	//------------------------------------------------------------
	// ���ע��
	CSkinButton mBtnFreeRegistration;
	// ������ֵ
	CSkinButton mBtnRecharge;
	// �ٷ���վ
	CSkinButton mBtnOfficialWebsite;
	// �ٷ���̳
	CSkinButton mBtnOfficialForum;
	// ��Ϸ����
	CSkinButton mBtnGameSetting;
	// ��Ϸ����
	CSkinButton mBtnDownload;
	// �汾˵��
	CSkinButton mBtnVerCaption;
	// ��Ϸ�޸�
	CSkinButton mBtnGameRepair;
	// �ֶ�����
	CSkinButton mBtnManualUpdate;
	// ��ʼ��Ϸ
	CSkinButton mBtnGameStart;
	// �˳�
	CSkinButton mBtnExit;
	// ��ǰ�汾
	CStatic mStaticCurrVer;
	// ���°汾
	CStatic mStaticNewVer;
	// �汾����
	CStatic mStaticVerDesc;
	// ��ǰ����
	CSkinProgressCtrl mProcessCurr;
	// �ܽ���
	CSkinProgressCtrl mProcessAll;
	// �����
	CExplorer mExplorer;
	afx_msg HBRUSH	OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void	OnClose();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void	OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void	OnTimer(UINT_PTR nIDEvent);
	afx_msg void	OnBnClickedBtn1();

	afx_msg void OnBnClickedBtnStart();
};
HBITMAP   LoadBitmapFromFile(char * szFile);
bool LoadBitmapFromFile(char * szFile,CBitmap & bitmap);