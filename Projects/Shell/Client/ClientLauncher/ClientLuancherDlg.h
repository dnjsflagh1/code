
// ClientLuancherDlg.h : 头文件
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


// CClientLuancherDlg 对话框
class CClientLuancherDlg :  public CRGNDlg
{
// 构造
public:
	CClientLuancherDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLIENTLUANCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	// 免费注册
	CSkinButton mBtnFreeRegistration;
	// 购卡充值
	CSkinButton mBtnRecharge;
	// 官方网站
	CSkinButton mBtnOfficialWebsite;
	// 官方论坛
	CSkinButton mBtnOfficialForum;
	// 游戏设置
	CSkinButton mBtnGameSetting;
	// 游戏下载
	CSkinButton mBtnDownload;
	// 版本说明
	CSkinButton mBtnVerCaption;
	// 游戏修复
	CSkinButton mBtnGameRepair;
	// 手动更新
	CSkinButton mBtnManualUpdate;
	// 开始游戏
	CSkinButton mBtnGameStart;
	// 退出
	CSkinButton mBtnExit;
	// 当前版本
	CStatic mStaticCurrVer;
	// 最新版本
	CStatic mStaticNewVer;
	// 版本描述
	CStatic mStaticVerDesc;
	// 当前进度
	CSkinProgressCtrl mProcessCurr;
	// 总进度
	CSkinProgressCtrl mProcessAll;
	// 浏览器
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