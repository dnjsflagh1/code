#pragma once
#include "resource.h"


// CMainView ������ͼ

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
	virtual	void	DoDataExchange(CDataExchange* pDX);		// DDX/DDV ֧��
					CMainView();							// ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


