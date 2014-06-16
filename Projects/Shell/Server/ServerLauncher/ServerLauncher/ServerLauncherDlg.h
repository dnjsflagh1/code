
// ServerLauncherDlg.h : 头文件
//

#pragma once
#include "Resource.h"
#include "TabCtrlSSL.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "ServerSetTab.h"
#include "ServerStatusTab.h"
#include "CoreMsgTab.h"
#include "ShellMsgTab.h"
#include "NetStatesTab.h"
#include "NetSearchTab.h"
#include "DbMsgTab.h"
#include "ThreadMsgTab.h"


// CServerLauncherDlg 对话框
class CServerLauncherDlg : public CDialog
{
// 构造
public:
	CServerLauncherDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LAUNCHER_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL	OnInitDialog();
	afx_msg void	OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	void	writeCoreLog(CString str);
	void	writeDbLog(CString str);
	void	writeShellLog(CString str);



private:
	CTabCtrlSSL			mTab;
	ServerSetTab		mServerSetTab;
	ServerStatusTab		mServerStatusTab;
	NetStatesTab		mNetStatesTab;
	NetSearchTab		mNetSearchTab;
	CoreMsgTab			mCoreMsgTab;
	ShellMsgTab			mShellMsgTab;
	DbMsgTab			mDbMsgTab;
	ThreadMsgTab		mThreadMsgTab;
	CButton				mCloseBtn;
	CButton				mStartBtn;

public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStope();
	afx_msg void OnDlgClose();
};


extern CServerLauncherDlg* gLauncherDlg;