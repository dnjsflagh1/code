
// ServerLauncherDlg.h : ͷ�ļ�
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


// CServerLauncherDlg �Ի���
class CServerLauncherDlg : public CDialog
{
// ����
public:
	CServerLauncherDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LAUNCHER_DLG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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