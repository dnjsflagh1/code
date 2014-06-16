#pragma once
#include "resource.h"


// CMainView 窗体视图

class CMainView : public CFormView
{
	DECLARE_DYNCREATE(CMainView)
public:
	enum { IDD = IDD_MAIN_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool			initView();
protected:
	virtual	void	DoDataExchange(CDataExchange* pDX);		// DDX/DDV 支持
					CMainView();							// 动态创建所使用的受保护的构造函数
					virtual ~CMainView();
private:
	CRichEditCtrl	mRichEditInformation;
	MG::U32			mLastRefreshTick;
public:
	LRESULT			onRefreshMessage(WPARAM wParam,LPARAM lParam);
	void			refreshMessage();
	void			refreshAllMessages();

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonClearMessage();
};


